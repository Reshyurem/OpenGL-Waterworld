#ifndef SEA_H
#define SEA_H
class Sea {
   private:
	float shape[36];
	unsigned int VAO, VBO;

   public:
	void init() {
		shape[0] = -1.0f;
		shape[1] = -1.0f;
		shape[2] = 0.0f;
		shape[3] = 0.0f;
		shape[4] = 0.418f;
		shape[5] = 0.58f;
		shape[6] = 1.0f;
		shape[7] = 1.0f;
		shape[8] = 0.0f;
		shape[9] = 0.0f;
		shape[10] = 0.418f;
		shape[11] = 0.58f;

		shape[12] = -1.0f;
		shape[13] = 1.0f;
		shape[14] = 0.0f;
		shape[15] = 0.0f;
		shape[16] = 0.418f;
		shape[17] = 0.58f;
		shape[18] = -1.0f;
		shape[19] = -1.0f;
		shape[20] = 0.0f;
		shape[21] = 0.0f;
		shape[22] = 0.418f;
		shape[23] = 0.58f;

		shape[24] = 1.0f;
		shape[25] = 1.0f;
		shape[26] = 0.0f;
		shape[27] = 0.0f;
		shape[28] = 0.418f;
		shape[29] = 0.58f;
		shape[30] = 1.0f;
		shape[31] = -1.0f;
		shape[32] = 0.0f;
		shape[33] = 0.0f;
		shape[34] = 0.418f;
		shape[35] = 0.58f;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
	}
	void buffers() {
		glBindVertexArray((this->VAO));

		glBindBuffer(GL_ARRAY_BUFFER, (this->VBO));
		glBufferData(GL_ARRAY_BUFFER, 144, shape, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
							  (void *)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
							  (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		draw();
	}
	void draw() {
		glBindVertexArray((this->VAO));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}
	void del() {
		glDeleteVertexArrays(1, &(this->VAO));
		glDeleteBuffers(1, &(this->VBO));
	}
};
#endif