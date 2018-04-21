#include <glad/glad.h> // <glad/glad.h> 要在 <GLFW/glfw3.h> 之前，有 GL/gl.h 等依赖关系。glad 库协助我们使用正确的驱动，管理 OpenGL 的函数指针。
#include <GLFW/glfw3.h> // glfw 库是协助我们来创建窗口的
#include <iostream>

using namespace std;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	glfwInit(); // 初始化 glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // glfwWindowHint 用于配置
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 这两行表示使用的是 3.3 版本的 OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //使用核心模式
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // OS X 上需要加上这句

	// 创建窗口对象
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL via tangyikejun", NULL, NULL); // 宽，高，标题
	if (window == NULL)
	{
		cout << "Fail Create Window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // 将窗口的上下文设置成当前线程的主上下文。

	// 使用 OpenGL 的函数前要先初始化 GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Fail to Init GLAD" << endl;
		return -1;
	}

	// 定义视口
	glViewport(0,0,800,600); // 坐标原点在左下角。视口可以比窗口小，那么可以在视口以外的区域绘制OpenGL之外的东西。
	// OpenGL 的坐标范围 [-1,1]

	
	// 注册窗口 resize 的回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 对于视网膜屏，width 和 height 都会比原输入值高，这大概就是会模糊的原因？

	// 添加主循环
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window); // 交换缓冲
		glfwPollEvents(); // 拉取事件
	}


	glfwTerminate();//正确释放所有资源
	return 0;
}

// 设置窗口大小变化的回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height) 
{
	glViewport(0,0,width,height);
}