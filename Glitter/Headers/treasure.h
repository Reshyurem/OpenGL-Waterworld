#ifndef TREASURE_H
#define TREASURE_H

#include "model.h"

class Treasure {
   private:
	glm::mat4 transform;
	Model ourModel;

   public:
	bool display;
	Treasure(glm::vec3 position, float rotation, Shader &sh) : ourModel("../Glitter/Models/Treasure/scene.gltf") {
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::scale(transform, glm::vec3(0.08f));
		// transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		display = true;
		draw(sh);
	}

	Treasure() : ourModel("../Glitter/Models/Treasure/scene.gltf") {
		transform = glm::mat4(1.0f);
		transform = glm::scale(transform, glm::vec3(0.08f));
		display = true;
	}

	void treasure(glm::vec3 position, float rotation, Shader &sh) {
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::scale(transform, glm::vec3(0.08f));
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

	void translate(glm::vec3 t) { transform = glm::translate(transform, t); }

	void rotate(float angle)
	{
		transform = glm::rotate(transform, angle, glm::vec3(0, 0, 1));
	}
	void teleport(glm::vec3 t) { transform = glm::translate(glm::mat4(1.0f), t); }
};

// class Treasure {
//    private:
// 	glm::mat4 transform;
// 	float shape[216];
// 	unsigned int VAO;
// 	unsigned int VBO;

//    public:
// 	void treasure(glm::vec3 position, float rotation, Shader &sh) {
// 		transform = glm::mat4(1.0f);
// 		transform = glm::translate(transform, position);
// 		transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
// 		// Top
// 		shape[0] = 0.02f;
// 		shape[1] = 0.02f;
// 		shape[2] = 0.02f;
// 		shape[3] = 1.0f;
// 		shape[4] = 0.841f;
// 		shape[5] = 0.0f;
// 		shape[6] = -0.02f;
// 		shape[7] = -0.02f;
// 		shape[8] = 0.02f;
// 		shape[9] = 1.0f;
// 		shape[10] = 0.841f;
// 		shape[11] = 0.0f;
// 		shape[12] = 0.02f;
// 		shape[13] = -0.02f;
// 		shape[14] = 0.02f;
// 		shape[15] = 1.0f;
// 		shape[16] = 0.841f;
// 		shape[17] = 0.0f;
// 		shape[18] = -0.02f;
// 		shape[19] = -0.02f;
// 		shape[20] = 0.02f;
// 		shape[21] = 1.0f;
// 		shape[22] = 0.841f;
// 		shape[23] = 0.0f;
// 		shape[24] = 0.02f;
// 		shape[25] = 0.02f;
// 		shape[26] = 0.02f;
// 		shape[27] = 1.0f;
// 		shape[28] = 0.841f;
// 		shape[29] = 0.0f;
// 		shape[30] = -0.02f;
// 		shape[31] = 0.02f;
// 		shape[32] = 0.02f;
// 		shape[33] = 1.0f;
// 		shape[34] = 0.841f;
// 		shape[35] = 0.0f;

// 		// Bottom
// 		shape[36] = 0.02f;
// 		shape[37] = 0.02f;
// 		shape[38] = -0.02f;
// 		shape[39] = 1.0f;
// 		shape[40] = 0.841f;
// 		shape[41] = 0.0f;
// 		shape[42] = -0.02f;
// 		shape[43] = -0.02f;
// 		shape[44] = -0.02f;
// 		shape[45] = 1.0f;
// 		shape[46] = 0.841f;
// 		shape[47] = 0.0f;
// 		shape[48] = 0.02f;
// 		shape[49] = -0.02f;
// 		shape[50] = -0.02f;
// 		shape[51] = 1.0f;
// 		shape[52] = 0.841f;
// 		shape[53] = 0.0f;
// 		shape[54] = -0.02f;
// 		shape[55] = -0.02f;
// 		shape[56] = -0.02f;
// 		shape[57] = 1.0f;
// 		shape[58] = 0.841f;
// 		shape[59] = 0.0f;
// 		shape[60] = 0.02f;
// 		shape[61] = 0.02f;
// 		shape[62] = -0.02f;
// 		shape[63] = 1.0f;
// 		shape[64] = 0.841f;
// 		shape[65] = 0.0f;
// 		shape[66] = -0.02f;
// 		shape[67] = 0.02f;
// 		shape[68] = -0.02f;
// 		shape[69] = 1.0f;
// 		shape[70] = 0.841f;
// 		shape[71] = 0.0f;

// 		// Left
// 		shape[72] = -0.02f;
// 		shape[73] = 0.02f;
// 		shape[74] = 0.02f;
// 		shape[75] = 1.0f;
// 		shape[76] = 0.841f;
// 		shape[77] = 0.0f;
// 		shape[78] = -0.02f;
// 		shape[79] = -0.02f;
// 		shape[80] = -0.02f;
// 		shape[81] = 1.0f;
// 		shape[82] = 0.841f;
// 		shape[83] = 0.0f;
// 		shape[84] = -0.02f;
// 		shape[85] = -0.02f;
// 		shape[86] = 0.02f;
// 		shape[87] = 1.0f;
// 		shape[88] = 0.841f;
// 		shape[89] = 0.0f;
// 		shape[90] = -0.02f;
// 		shape[91] = 0.02f;
// 		shape[92] = 0.02f;
// 		shape[93] = 1.0f;
// 		shape[94] = 0.841f;
// 		shape[95] = 0.0f;
// 		shape[96] = -0.02f;
// 		shape[97] = -0.02f;
// 		shape[98] = -0.02f;
// 		shape[99] = 1.0f;
// 		shape[100] = 0.841f;
// 		shape[101] = 0.0f;
// 		shape[102] = -0.02f;
// 		shape[103] = 0.02f;
// 		shape[104] = -0.02f;
// 		shape[105] = 1.0f;
// 		shape[106] = 0.841f;
// 		shape[107] = 0.0f;

// 		// Right
// 		shape[108] = 0.02f;
// 		shape[109] = 0.02f;
// 		shape[110] = 0.02f;
// 		shape[111] = 1.0f;
// 		shape[112] = 0.841f;
// 		shape[113] = 0.0f;
// 		shape[114] = 0.02f;
// 		shape[115] = -0.02f;
// 		shape[116] = -0.02f;
// 		shape[117] = 1.0f;
// 		shape[118] = 0.841f;
// 		shape[119] = 0.0f;
// 		shape[120] = 0.02f;
// 		shape[121] = -0.02f;
// 		shape[122] = 0.02f;
// 		shape[123] = 1.0f;
// 		shape[124] = 0.841f;
// 		shape[125] = 0.0f;
// 		shape[126] = 0.02f;
// 		shape[127] = 0.02f;
// 		shape[128] = 0.02f;
// 		shape[129] = 1.0f;
// 		shape[130] = 0.841f;
// 		shape[131] = 0.0f;
// 		shape[132] = 0.02f;
// 		shape[133] = -0.02f;
// 		shape[134] = -0.02f;
// 		shape[135] = 1.0f;
// 		shape[136] = 0.841f;
// 		shape[137] = 0.0f;
// 		shape[138] = 0.02f;
// 		shape[139] = 0.02f;
// 		shape[140] = -0.02f;
// 		shape[141] = 1.0f;
// 		shape[142] = 0.841f;
// 		shape[143] = 0.0f;

// 		// Front
// 		shape[144] = 0.02f;
// 		shape[145] = 0.02f;
// 		shape[146] = 0.02f;
// 		shape[147] = 1.0f;
// 		shape[148] = 0.841f;
// 		shape[149] = 0.0f;
// 		shape[150] = -0.02f;
// 		shape[151] = 0.02f;
// 		shape[152] = -0.02f;
// 		shape[153] = 1.0f;
// 		shape[154] = 0.841f;
// 		shape[155] = 0.0f;
// 		shape[156] = -0.02f;
// 		shape[157] = 0.02f;
// 		shape[158] = 0.02f;
// 		shape[159] = 1.0f;
// 		shape[160] = 0.841f;
// 		shape[161] = 0.0f;
// 		shape[162] = 0.02f;
// 		shape[163] = 0.02f;
// 		shape[164] = 0.02f;
// 		shape[165] = 1.0f;
// 		shape[166] = 0.841f;
// 		shape[167] = 0.0f;
// 		shape[168] = -0.02f;
// 		shape[169] = 0.02f;
// 		shape[170] = -0.02f;
// 		shape[171] = 1.0f;
// 		shape[172] = 0.841f;
// 		shape[173] = 0.0f;
// 		shape[174] = 0.02f;
// 		shape[175] = 0.02f;
// 		shape[176] = -0.02f;
// 		shape[177] = 1.0f;
// 		shape[178] = 0.841f;
// 		shape[179] = 0.0f;

// 		// Back
// 		shape[180] = 0.02f;
// 		shape[181] = -0.02f;
// 		shape[182] = 0.02f;
// 		shape[183] = 1.0f;
// 		shape[184] = 0.841f;
// 		shape[185] = 0.0f;
// 		shape[186] = -0.02f;
// 		shape[187] = -0.02f;
// 		shape[188] = -0.02f;
// 		shape[189] = 1.0f;
// 		shape[190] = 0.841f;
// 		shape[191] = 0.0f;
// 		shape[192] = -0.02f;
// 		shape[193] = -0.02f;
// 		shape[194] = 0.02f;
// 		shape[195] = 1.0f;
// 		shape[196] = 0.841f;
// 		shape[197] = 0.0f;
// 		shape[198] = 0.02f;
// 		shape[199] = -0.02f;
// 		shape[200] = 0.02f;
// 		shape[201] = 1.0f;
// 		shape[202] = 0.841f;
// 		shape[203] = 0.0f;
// 		shape[204] = -0.02f;
// 		shape[205] = -0.02f;
// 		shape[206] = -0.02f;
// 		shape[207] = 1.0f;
// 		shape[208] = 0.841f;
// 		shape[209] = 0.0f;
// 		shape[210] = 0.02f;
// 		shape[211] = -0.02f;
// 		shape[212] = -0.02f;
// 		shape[213] = 1.0f;
// 		shape[214] = 0.841f;
// 		shape[215] = 0.0f;
// 		glGenVertexArrays(1, &(this->VAO));
// 		glGenBuffers(1, &(this->VBO));

// 		buffers(sh);
// 	}
// 	void buffers(Shader &sh) {
// 		glBindVertexArray((this->VAO));

// 		glBindBuffer(GL_ARRAY_BUFFER, (this->VBO));
// 		glBufferData(GL_ARRAY_BUFFER, 864, shape, GL_STATIC_DRAW);
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
// 		glDrawArrays(GL_TRIANGLES, 0, 72);
// 		glBindVertexArray(0);
// 	}

// 	void del() {
// 		glDeleteVertexArrays(1, &(this->VAO));
// 		glDeleteBuffers(1, &(this->VBO));
// 	}

// 	void rotate(float angle) {
// 		transform = glm::rotate(transform, angle, glm::vec3(0.0f, 0.0f, 1.0f));
// 	}

// 	float dist(glm::mat4 infinite)
// 	{
// 		glm::vec4 pos = infinite * transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
// 		return sqrt(pow(pos.x, 2) + pow(pos.y, 2));
// 	}
// };
#endif