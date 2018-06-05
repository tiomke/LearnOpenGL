// ��ѧ��
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h> // <glad/glad.h> Ҫ�� <GLFW/glfw3.h> ֮ǰ���� GL/gl.h ��������ϵ��glad ��Э������ʹ����ȷ������������ OpenGL �ĺ���ָ�롣
#include <GLFW/glfw3.h> // glfw ����Э���������������ڵ�
#include <Shader/Shader.h>
#include <iostream>

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
	GLFWwindow* window = glfwCreateWindow(600, 600, "LearnOpenGL via tangyikejun", NULL, NULL); // ���ߣ�����
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
	glViewport(0, 0, 600, 600); // ����ԭ�������½ǡ��ӿڿ��Աȴ���С����ô�������ӿ�������������OpenGL֮��Ķ�����
								// OpenGL �����귶Χ [-1,1]


								// ע�ᴰ�� resize �Ļص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // ��������Ĥ����width �� height �����ԭ����ֵ�ߣ����ž��ǻ�ģ����ԭ��

	////// ��Ⱦ���� Start
	Shader* shader = new Shader("../First/Shader/vshader.glsl", "../First/Shader/fshader.glsl");
	Shader* lightShader = new Shader("../First/Shader/vshader.glsl", "../First/Shader/fLightShader.glsl");



	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};


	 //1.�� VAO
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


	// 4.�趨��������
	// �趨����Ķ�����������ɫ��֮ǰ�Ķ�Ӧ��ϵ��Ҳ���Ƕ��� VBO �����ݵ�����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	// ע��
	// index �������ö���������ԣ������������õ� 0 λ�á�ǰ�涥����ɫ���� layout(location = 0) �ͱ�ʾ�����±�Ϊ0�Ķ������ԵĶ���
	// size �������ԵĴ�С�����ǵĶ��������� vec3 ,������ 3
	// type ����Ԫ�ص����� vec3 �е��������Ͷ��� float
	// normalized �Ƿ���Ҫ��һ��
	// stride ����������������������֮�������ֽ���
	// pointer �����б�ʾλ����������ڻ�����ʼλ�õ�ƫ����

	// ���� 0 �Ŷ�������
	glEnableVertexAttribArray(0);

	GLuint LightVAO;
	glGenVertexArrays(1,&LightVAO);
	glBindVertexArray(LightVAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO); // ��� VBO ����ŵ���һ��������
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(void *)0);

	glEnableVertexAttribArray(0);

	// ���ú��˾ͽ����
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // VAO �����õ�ʱ�� ���ܽ�� EBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	glEnable(GL_DEPTH_TEST);// ������Ȳ��ԣ�Ĭ���ǹرյġ����ֵ�洢��ÿ��Ƭ�ε� z ֵ�У�������openglͨ��һ����Ȼ������жϵ�ǰƬ���Ƿ�������Ƭ�κ��棬����ǵĻ��ͻᱻ�õ�
	////// ��Ⱦ���� End

	// �����ѭ��
	while (!glfwWindowShouldClose(window))
	{
		// esc �˳�
		processInput(window);

		// ��Ⱦ��� Start
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // ���������������ɫֵ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vec3 lightPos(1.2f, 1.0f, 2.0f);
		// �۲����
		mat4 view;
		view = translate(view, vec3(0.0f, 0.0f, -10.0f));
		// ͸��ͶӰ����
		mat4 proj;
		proj = perspective((float)radians(45.0f), (float)600 / 600, 0.1f, 100.0f);
		// ģ�;���
		mat4 model;
		model = mat4();
		model = translate(model, lightPos); // �ƶ��� lightPos
		model = scale(model, vec3(0.2f)); // Ȼ����С

		mat4 omodel;
		omodel = rotate(omodel, (float)radians(45.0),vec3(1,1,0));

		lightShader->use(); // ��ִ��shader
		// �����õ�uniform
		lightShader->setMat4("proj", proj);
		lightShader->setMat4("view", view);
		lightShader->setMat4("model", model);
		glBindVertexArray(LightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);// ָ��ͼԪ���ͣ�ָ�������������ʼ�����ͻ��ƵĶ�������

		shader->use(); // ��ִ��shader
					   // �����õ�uniform
		shader->setVec3("objectColor", vec3(1.0f, 0.5f, 0.31f));
		shader->setVec3("lightColor", vec3(1.0f, 1.0f, 1.0f));
		shader->setMat4("view", view);
		shader->setMat4("proj", proj);
		shader->setMat4("model", omodel);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);// ָ��ͼԪ���ͣ�ָ�������������ʼ�����ͻ��ƵĶ�������
		// ��Ⱦ��� End

		glfwSwapBuffers(window); // ��������
		glfwPollEvents(); // ��ȡ�¼�
	}

	// �����˾�ɾ����
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &LightVAO);
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