#include <glad/glad.h> // <glad/glad.h> Ҫ�� <GLFW/glfw3.h> ֮ǰ���� GL/gl.h ��������ϵ��glad ��Э������ʹ����ȷ������������ OpenGL �ĺ���ָ�롣
#include <GLFW/glfw3.h> // glfw ����Э���������������ڵ�
#include <Shader/Shader.h>
#include <iostream>

using namespace std;
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


	float vertices[] = { // ����һ�� 2D �����Σ���Ҫ���ñ�׼���豸����
		// ����			// ��ɫ
		-0.5,-0.5,0,	1,0,0,
		0.5,-0.5,0,		0,1,0,
		0,0.5,0,		0,0,1,
		0.5,0.5,0,		1,1,1,
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


	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
	//����������ɫ�����Ķ�������
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	// ���ú��˾ͽ����
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // VAO �����õ�ʱ�� ���ܽ�� EBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	////// ��Ⱦ���� End

	// �����ѭ��
	while (!glfwWindowShouldClose(window))
	{
		// esc �˳�
		processInput(window);

		// ��Ⱦ��� Start
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ���������������ɫֵ
		glClear(GL_COLOR_BUFFER_BIT); // �����ɫ����



									  // ������ɫ���������
		shader->use();
		glBindVertexArray(VAO);
		//float t = glfwGetTime();
		//GLint pos = glGetUniformLocation(program, "ourColor");
		//glUniform4f(pos, 0.5, sin(t)/3 + 0.5, 0.2, 1);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // ָ��ͼԪ���ͣ�ָ������������ָ���������ͣ�ָ�� EBO ƫ����
		//glDrawArrays(GL_TRIANGLES, 0, 3); // ָ��ͼԪ���ͣ�ָ�������������ʼ�����ͻ��ƵĶ�������



		// ��Ⱦ��� End

		glfwSwapBuffers(window); // ��������
		glfwPollEvents(); // ��ȡ�¼�
	}

	// �����˾�ɾ����
	glDeleteVertexArrays(1, &VAO);
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