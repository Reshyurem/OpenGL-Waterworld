#ifndef SHIP_H
#define SHIP_H

#include "model.h"

class Ship
{
private:
	glm::mat4 transform;
	Model ourModel;

public:
	bool display;
	Ship(glm::vec3 position, float rotation, Shader &sh) : ourModel("../Glitter/Models/Ship/source/ship.fbx")
	{
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::scale(transform, glm::vec3(0.002f));
		// transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		display = true;
		draw(sh);
	}

	Ship() : ourModel("../Glitter/Models/Ship/source/ship.fbx")
	{
		transform = glm::mat4(1.0f);
		// transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		transform = glm::scale(transform, glm::vec3(0.002f));
		display = true;
	}

	void ship(glm::vec3 position, float rotation, Shader &sh)
	{
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::scale(transform, glm::vec3(0.002f));
		// transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		display = true;
		draw(sh);
	}

	void draw(Shader &sh)
	{
		sh.setMat4("transform", transform);
		ourModel.Draw(sh);
	}

	float dist(glm::mat4 infinite)
	{
		glm::vec4 pos = infinite * transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		return sqrt(pow(pos.x, 2) + pow(pos.y, 2));
	}

	void translateTowards(glm::mat4 inf)
	{
		glm::vec4 pos = inf * transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		// std::cout << pos.x << " " << pos.y << std::endl;
		// glm::vec3 pos3 = glm::vec3(pos.x, pos.y, pos.z);
		// glm::vec3 pos4 = glm::vec3(pos2.x, pos2.y, pos2.z);
		glm::vec3 dir = glm::normalize(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f) - pos) / 10.0f;
		// std::cout << dir.x << " " << dir.y << std::endl;
		glm::vec3 dir2 = glm::normalize(inf * transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f) - pos) / 10.0f;
		// std::cout << dir.x << " " << dir.y << " " << dir.z << std::endl;
		// std::cout << dir2.x << " " << dir2.y << " " << dir2.z << std::endl;
		if(glm::cross(dir, dir2).z > 0.0f)
			transform = glm::rotate(transform, glm::radians(0.1f), glm::vec3(0.0f, 0.0f, 1.0f));
		else if(glm::cross(dir, dir2).z < 0.0f)
			transform = glm::rotate(transform, glm::radians(-0.1f), glm::vec3(0.0f, 0.0f, 1.0f));
		if(pos.y > 0.0f)
			transform = glm::translate(transform, dir);
		else if(pos.y < 0.0f)
			transform = glm::translate(transform, glm::vec3(dir.x, -dir.y, dir.z));
	}

	glm::mat4 getModel()
	{
		return transform;
	}

	void translate(glm::vec3 t) { transform = glm::translate(transform, t); }

	void rotate(float angle)
	{
		transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1));
	}

	void teleport(glm::vec3 t) { transform = glm::translate(glm::mat4(1.0f), t); }
};
// class Ship {
//    private:
// 	glm::mat4 transform;
// 	float shape[108];
// 	unsigned int VAO;
// 	unsigned int VBO;

//    public:
// 	void ship(glm::vec3 position, float rotation, Shader &sh) {
// 		transform = glm::mat4(1.0f);
// 		transform = glm::translate(transform, position);
// 		transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
// 		shape[0] = 0.0f;
// 		shape[1] = 0.1f;
// 		shape[2] = 0.02f;
// 		shape[3] = 0.5f;
// 		shape[4] = 0.5f;
// 		shape[5] = 0.5f;
// 		shape[6] = 0.0f;
// 		shape[7] = -0.1f;
// 		shape[8] = 0.02f;
// 		shape[9] = 0.5f;
// 		shape[10] = 0.5f;
// 		shape[11] = 0.5f;
// 		shape[12] = 0.02f;
// 		shape[13] = 0.0f;
// 		shape[14] = 0.02f;
// 		shape[15] = 0.5f;
// 		shape[16] = 0.5f;
// 		shape[17] = 0.5f;
// 		shape[18] = 0.0f;
// 		shape[19] = 0.1f;
// 		shape[20] = 0.02f;
// 		shape[21] = 0.5f;
// 		shape[22] = 0.5f;
// 		shape[23] = 0.5f;
// 		shape[24] = 0.0f;
// 		shape[25] = -0.1f;
// 		shape[26] = 0.02f;
// 		shape[27] = 0.5f;
// 		shape[28] = 0.5f;
// 		shape[29] = 0.5f;
// 		shape[30] = -0.02f;
// 		shape[31] = 0.0f;
// 		shape[32] = 0.02f;
// 		shape[33] = 0.5f;
// 		shape[34] = 0.5f;
// 		shape[35] = 0.5f;
// 		shape[36] = 0.0f;
// 		shape[37] = 0.1f;
// 		shape[38] = 0.02f;
// 		shape[39] = 0.5f;
// 		shape[40] = 0.5f;
// 		shape[41] = 0.5f;
// 		shape[42] = 0.02f;
// 		shape[43] = 0.0f;
// 		shape[44] = 0.02f;
// 		shape[45] = 0.5f;
// 		shape[46] = 0.5f;
// 		shape[47] = 0.5f;
// 		shape[48] = 0.0f;
// 		shape[49] = 0.0f;
// 		shape[50] = -0.02f;
// 		shape[51] = 0.0f;
// 		shape[52] = 0.0f;
// 		shape[53] = 0.0f;
// 		shape[54] = 0.0f;
// 		shape[55] = 0.1f;
// 		shape[56] = 0.02f;
// 		shape[57] = 0.5f;
// 		shape[58] = 0.5f;
// 		shape[59] = 0.5f;
// 		shape[60] = -0.02f;
// 		shape[61] = 0.0f;
// 		shape[62] = 0.02f;
// 		shape[63] = 0.5f;
// 		shape[64] = 0.5f;
// 		shape[65] = 0.5f;
// 		shape[66] = 0.0f;
// 		shape[67] = 0.0f;
// 		shape[68] = -0.02f;
// 		shape[69] = 0.0f;
// 		shape[70] = 0.0f;
// 		shape[71] = 0.0f;
// 		shape[72] = 0.0f;
// 		shape[73] = -0.1f;
// 		shape[74] = 0.02f;
// 		shape[75] = 0.5f;
// 		shape[76] = 0.5f;
// 		shape[77] = 0.5f;
// 		shape[78] = 0.02f;
// 		shape[79] = 0.0f;
// 		shape[80] = 0.02f;
// 		shape[81] = 0.5f;
// 		shape[82] = 0.5f;
// 		shape[83] = 0.5f;
// 		shape[84] = 0.0f;
// 		shape[85] = 0.0f;
// 		shape[86] = -0.02f;
// 		shape[87] = 0.0f;
// 		shape[88] = 0.0f;
// 		shape[89] = 0.0f;
// 		shape[90] = 0.0f;
// 		shape[91] = -0.1f;
// 		shape[92] = 0.02f;
// 		shape[93] = 0.5f;
// 		shape[94] = 0.5f;
// 		shape[95] = 0.5f;
// 		shape[96] = -0.02f;
// 		shape[97] = 0.0f;
// 		shape[98] = 0.02f;
// 		shape[99] = 0.5f;
// 		shape[100] = 0.5f;
// 		shape[101] = 0.5f;
// 		shape[102] = 0.0f;
// 		shape[103] = 0.0f;
// 		shape[104] = -0.02f;
// 		shape[105] = 0.0f;
// 		shape[106] = 0.0f;
// 		shape[107] = 0.0f;
// 		glGenVertexArrays(1, &(this->VAO));
// 		glGenBuffers(1, &(this->VBO));

// 		buffers(sh);
// 	}
// 	void buffers(Shader &sh) {
// 		glBindVertexArray((this->VAO));

// 		glBindBuffer(GL_ARRAY_BUFFER, (this->VBO));
// 		glBufferData(GL_ARRAY_BUFFER, 432, shape, GL_STATIC_DRAW);
// 		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
// 							  (void *)0);
// 		glEnableVertexAttribArray(0);
// 		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
// 							  (void *)(3 * sizeof(float)));
// 		glEnableVertexAttribArray(1);
// 		glBindBuffer(GL_ARRAY_BUFFER, 0);
// 		glBindVertexArray(0);

// 		draw(sh);
// 	}

// 	void draw(Shader &sh) {
// 		sh.setMat4("transform", transform);
// 		glBindVertexArray((this->VAO));
// 		glDrawArrays(GL_TRIANGLES, 0, 36);
// 		glBindVertexArray(0);
// 	}

// 	void del() {
// 		glDeleteVertexArrays(1, &(this->VAO));
// 		glDeleteBuffers(1, &(this->VBO));
// 	}

// 	float dist(glm::mat4 infinite)
// 	{
// 		glm::vec4 pos = infinite * transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
// 		return sqrt(pow(pos.x, 2) + pow(pos.y, 2));
// 	}

// 	void translate(glm::vec3 t) { transform = glm::translate(transform, t); }

// 	void rotate(float angle) {
// 		transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1));
// 	}
// };
#endif