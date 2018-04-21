#include <glad/glad.h> // <glad/glad.h> Ҫ�� <GLFW/glfw3.h> ֮ǰ���� GL/gl.h ��������ϵ��glad ��Э������ʹ����ȷ������������ OpenGL �ĺ���ָ�롣
#include <GLFW/glfw3.h> // glfw ����Э���������������ڵ�
#include <iostream>

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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
	glViewport(0,0,800,600); // ����ԭ�������½ǡ��ӿڿ��Աȴ���С����ô�������ӿ�������������OpenGL֮��Ķ�����
	// OpenGL �����귶Χ [-1,1]

	
	// ע�ᴰ�� resize �Ļص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // ��������Ĥ����width �� height �����ԭ����ֵ�ߣ����ž��ǻ�ģ����ԭ��

	// �����ѭ��
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window); // ��������
		glfwPollEvents(); // ��ȡ�¼�
	}


	glfwTerminate();//��ȷ�ͷ�������Դ
	return 0;
}

// ���ô��ڴ�С�仯�Ļص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0,0,width,height);
}