#ifndef CANNONBALL_H
#define CANNONBALL_H

#include "model.h"

class Cannonball
{
private:
	glm::mat4 transform;
	glm::vec3 direction;
	Model ourModel;

public:
	bool display;
	bool whoShot;
	Cannonball(glm::vec3 position, glm::vec3 direction, Shader &sh) : ourModel("../Glitter/Models/Cannonball/ball.obj")
	{
		this->direction = direction;
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position + glm::vec3(0.04f, 0.0f, 0.1f) + direction);
		transform = glm::scale(transform, glm::vec3(0.01f));
		display = false;
		draw(sh);
	}

	Cannonball() : ourModel("../Glitter/Models/Cannonball/ball.obj")
	{
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, glm::vec3(0.04f, 0.1f, 0.1f));
		transform = glm::scale(transform, glm::vec3(0.01f));
		display = false;
	}

	void cannonball(glm::vec3 position, glm::vec3 direction, Shader &sh)
	{
		this->direction = direction;
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position + glm::vec3(0.04f, 0.0f, 0.1f) + direction);
		transform = glm::scale(transform, glm::vec3(0.01f));
		display = false;
		draw(sh);
	}

	void draw(Shader &sh)
	{
		sh.setMat4("transform", transform);
		ourModel.Draw(sh);
	}

	float dist(glm::mat4 infinite)
	{
		if (whoShot == true)
		{
			glm::vec4 pos = infinite * transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			return sqrt(pow(pos.x, 2) + pow(pos.y, 2));
		}
		else
		{
			glm::vec4 pos = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			return sqrt(pow(pos.x, 2) + pow(pos.y, 2));
		}
	}

	float dist(glm::mat4 infinite, glm::mat4 enemy)
	{
		if (whoShot == true)
		{
			glm::vec4 pos = infinite * glm::translate(transform, glm::vec3(-0.04f, 0.0f, -0.1f)) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			glm::vec4 posEnem = infinite * enemy * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			return sqrt(pow(pos.x - posEnem.x, 2) + pow(pos.y - posEnem.y, 2));
		}
		else 
		{
			glm::vec4 pos = glm::translate(transform, glm::vec3(-0.04f, 0.0f, -0.1f)) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			glm::vec4 posEnem = infinite * enemy * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			return sqrt(pow(pos.x - posEnem.x, 2) + pow(pos.y - posEnem.y, 2));
		}
	}

	void translate(glm::vec3 t) { transform = glm::translate(transform, t); }

	void rotate(float angle)
	{
		transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1));
	}

	void move()
	{
		transform = glm::translate(transform, direction);
	}

	glm::mat4 getModel()
	{
		return transform;
	}
};
#endif