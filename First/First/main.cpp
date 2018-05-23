#include <glad/glad.h> // <glad/glad.h> Ҫ�� <GLFW/glfw3.h> ֮ǰ���� GL/gl.h ��������ϵ��glad ��Э������ʹ����ȷ������������ OpenGL �ĺ���ָ�롣
#include <GLFW/glfw3.h> // glfw ����Э���������������ڵ�
#include <Shader/Shader.h>
#include <iostream>
// ��ѧ��
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
using namespace glm;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow * window);

int main()
{

	glfwInit(); // ��ʼ�� glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // glfwWindowHint ��������
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // �����б�ʾʹ�õ��� 3.3 �汾�� OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //ʹ�ú���ģʽ
																   //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // OS X ����Ҫ�������

																   // �������ڶ���
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL via tangyikejun", NULL, NULL); // ���ߣ�����
	if (window == NULL)
	{
		cout << "Fail Create Window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // �����ڵ����������óɵ�ǰ�̵߳��������ġ�

									// ʹ�� OpenGL �ĺ���ǰҪ�ȳ�ʼ�� GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Fail to Init GLAD" << endl;
		return -1;
	}

	// �����ӿ�
	glViewport(0, 0, 800, 600); // ����ԭ�������½ǡ��ӿڿ��Աȴ���С����ô�������ӿ�������������OpenGL֮��Ķ�����
								// OpenGL �����귶Χ [-1,1]


								// ע�ᴰ�� resize �Ļص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // ��������Ĥ����width �� height �����ԭ����ֵ�ߣ����ž��ǻ�ģ����ԭ��

	////// ��Ⱦ���� Start
	Shader* shader = new Shader("../First/Shader/vshader.glsl", "../First/Shader/fshader.glsl");
	//Shader* shader = new Shader("", "");


	float vertices[] = { // ֱ��ʹ�����ظ�����Ķ��巽ʽ
		// ����λ��				//uv����
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	GLuint indices[] = { // ������ָ������Ļ���˳��
		0,1,2,
		1,2,3,
	};


	// 1.�� VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO); // ����һ�� VAO
	glBindVertexArray(VAO); // �� VAO��֮��� VBO ��
							// 2.�趨 VBO
	GLuint VBO;
	glGenBuffers(1, &VBO); // Vertice Buffer Object,���㻺������� GPU �д���һƬ�ڴ����ڴ洢���嶥��
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // �� VBO ��Ϊ �������黺�� ����
										// GL_STATIC_DRAW  ��ʾ���ݼ�������
										// GL_DYNAMIC_DRAW ��ʾ���ݶ��
										// GL_STREAM_DRAW ��ʾ����ÿ�ζ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //�����ݸ��Ƶ����壬���һ������ָ�� GPU �����ݵĹ�����ԡ�ִ������һ����˵�������Ѿ������Դ�����ȥ��

																			   // �ִ� OpenGL ���ṩĬ�ϵ� �����Ƭ����ɫ����������Ҫ�Լ�ߣһ��


	/*GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/
	// 4.�趨��������
	// �趨����Ķ�����������ɫ��֮ǰ�Ķ�Ӧ��ϵ��Ҳ���Ƕ��� VBO �����ݵ�����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
	// ע��
	// index �������ö���������ԣ������������õ� 0 λ�á�ǰ�涥����ɫ���� layout(location = 0) �ͱ�ʾ�����±�Ϊ0�Ķ������ԵĶ���
	// size �������ԵĴ�С�����ǵĶ��������� vec3 ,������ 3
	// type ����Ԫ�ص����� vec3 �е��������Ͷ��� float
	// normalized �Ƿ���Ҫ��һ��
	// stride ����������������������֮�������ֽ���
	// pointer �����б�ʾλ����������ڻ�����ʼλ�õ�ƫ����

	// ���� 0 �Ŷ�������
	glEnableVertexAttribArray(0);
	//����������������Ķ�������
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	// ���ú��˾ͽ����
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // VAO �����õ�ʱ�� ���ܽ�� EBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// ��������
	stbi_set_flip_vertically_on_load(true);//ͼƬy��������ԭ�������棬��Ҫ�ڼ���ͼ��ǰ��һ�·�ת
	int width, height, nChannel;
	unsigned char *data = stbi_load("../First/wall.jpg", &width, &height, &nChannel, 0); // ����Դͼ
	int width2, height2, nChannel2;
	unsigned char *data2 = stbi_load("../First/test.png", &width2, &height2, &nChannel2, 0); // ����Դͼ
	if (!data || !data2)
	{
		cout << "texture data load fail" << endl;
		return -1;
	}

	GLuint texture; // ����һ���������
	glGenTextures(1, &texture); // ����һ��ʾ��Ҫ���ɵ���������
	glBindTexture(GL_TEXTURE_2D,texture);
	// ��������Ļ��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//�����ں���Ļ���ģʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// mipmap ��ʱ����õ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// mipmap ��ʱ����õ�
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//����������������
	//ע��
	//����һ ��ʾͨ�� GL_TEXTURE_2D ���������ɵ� texuture ��
	//������ ��ʾ����mipmap��level��0��ʾ������
	//���������ġ��� ���ɵ�����Ĵ洢��ʽ����ȡ��߶�
	//������ ����Ϊ0����������
	//������ Դͼ�Ĵ洢��ʽ
	//������ Դͼ����������
	//������ Դͼ������

	GLuint texture2; // �����ڶ����������
	glGenTextures(1, &texture2); // 
	glBindTexture(GL_TEXTURE_2D, texture2);//�󶨵��ڶ�������
	// ��������Ļ��ơ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//�����ں���Ļ���ģʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);// mipmap ��ʱ����õ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);// mipmap ��ʱ����õ�
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);//��rgba-rgb



	//glGenerateMipmap(GL_TEXTURE_2D);//����mipmap��Ҳ�����ظ��������䣬�ı� mipmap�� level
	stbi_image_free(data); // �ͷ�ͼ���ڴ�
	stbi_image_free(data2);

	shader->use(); // ��ִ��shader
	// �����õ�uniform
	glUniform1i(glGetUniformLocation(shader->ID, "ourTexture1"), 0);
	glUniform1i(glGetUniformLocation(shader->ID, "ourTexture2"), 1); 
	//shader->setInt("ourTexture2", 1);// Ҳ����ֱ�Ӹ�����������

	////// ��Ⱦ���� End

	// �����ѭ��
	while (!glfwWindowShouldClose(window))
	{
		// esc �˳�
		processInput(window);

		// ��Ⱦ��� Start
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ���������������ɫֵ
		glClear(GL_COLOR_BUFFER_BIT); // �����ɫ����


		// ������
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		// ������ɫ���������
		shader->use();
		glBindVertexArray(VAO);
		//float t = glfwGetTime();
		//GLint pos = glGetUniformLocation(program, "ourColor");
		//glUniform4f(pos, 0.5, sin(t)/3 + 0.5, 0.2, 1);


		// ģ�;���
		mat4 model;
		model = rotate(model, (float)glfwGetTime(), vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, GL_FALSE, value_ptr(model));
		// �۲����
		mat4 view;
		view = translate(view, vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader->ID, "view"), 1, GL_FALSE, value_ptr(view));
		// ͸��ͶӰ����
		mat4 proj;
		proj = perspective((float)radians(45.0f), (float)800 / 600, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader->ID, "proj"), 1, GL_FALSE, value_ptr(proj));

		glDrawArrays(GL_TRIANGLES,0,36);// ָ��ͼԪ���ͣ�ָ�������������ʼ�����ͻ��ƵĶ�������



		// ��Ⱦ��� End

		glfwSwapBuffers(window); // ��������
		glfwPollEvents(); // ��ȡ�¼�
	}

	// �����˾�ɾ����
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &texture);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();//��ȷ�ͷ�������Դ
	return 0;
}

// ���ô��ڴ�С�仯�Ļص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}