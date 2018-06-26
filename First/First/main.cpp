// ��ѧ��
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h> // <glad/glad.h> Ҫ�� <GLFW/glfw3.h> ֮ǰ���� GL/gl.h ��������ϵ��glad ��Э������ʹ����ȷ������������ OpenGL �ĺ���ָ�롣
#include <GLFW/glfw3.h> // glfw ����Э���������������ڵ�
#include <Shader/Shader.h>
#include <LearnOpenGL/Camera.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
using namespace glm;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow * window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

Camera camera(vec3(0.0f,0.0f,3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

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
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	////// ��Ⱦ���� Start
	Shader* shader = new Shader("../First/Shader/vshader.glsl", "../First/Shader/fshader.glsl");
	Shader* lightShader = new Shader("../First/Shader/vshader.glsl", "../First/Shader/fLightShader.glsl");



	float vertices[] = {
		// ��������				// ��������ͬһ���㣬�ڲ�ͬ��Ƭ���У��в�ͬ�ķ�������
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
	// ע��
	// index �������ö���������ԣ������������õ� 0 λ�á�ǰ�涥����ɫ���� layout(location = 0) �ͱ�ʾ�����±�Ϊ0�Ķ������ԵĶ���
	// size �������ԵĴ�С�����ǵĶ��������� vec3 ,������ 3
	// type ����Ԫ�ص����� vec3 �е��������Ͷ��� float
	// normalized �Ƿ���Ҫ��һ��
	// stride ����������������������֮�������ֽ���
	// pointer �����б�ʾλ����������ڻ�����ʼλ�õ�ƫ����

	// ���� 0 �Ŷ�������
	glEnableVertexAttribArray(0);		

	// �趨������
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	GLuint LightVAO;
	glGenVertexArrays(1,&LightVAO);
	glBindVertexArray(LightVAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO); // ��� VBO ����ŵ���һ��������
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(void *)0);

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
		// 
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// esc �˳�
		processInput(window);

		// ��Ⱦ��� Start
		glClearColor(0.1f, 0.1f, 0.1f, 5.0f); // ���������������ɫֵ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float rad = radians(glfwGetTime()*30.0f);
		vec3 lightPos(0.0f, cos(rad)*6.0f,sin(rad)*6.0f);
		// �۲����
		vec3 viewPos = camera.Position;
		mat4 view = camera.GetViewMatrix();
		// ͸��ͶӰ����
		mat4 proj;
		proj = perspective((float)radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		// ģ�;���
		mat4 model;
		model = mat4();
		model = translate(model, lightPos); // �ƶ��� lightPos
		model = scale(model, vec3(0.2f)); // Ȼ����С

		mat4 omodel;
		omodel = rotate(omodel, (float)radians(glfwGetTime()*10.0f), vec3(1, 0, 0)); // ��������ת

		// ���߾���
		mat3 normalMatrix;
		normalMatrix = mat3(transpose(inverse(omodel)));

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
		shader->setVec3("lightPos", lightPos);
		shader->setMat3("normalMatrix", normalMatrix);
		shader->setVec3("viewPos", viewPos);
		shader->setVec3("material.ambient", vec3(1,0.5,0.31));
		shader->setVec3("material.diffuse", vec3(1, 0.5, 0.31));
		shader->setVec3("material.specular", vec3(0.5, 0.5, 0.5));
		shader->setFloat("material.shininess", 32);
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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}