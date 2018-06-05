// 数学库
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h> // <glad/glad.h> 要在 <GLFW/glfw3.h> 之前，有 GL/gl.h 等依赖关系。glad 库协助我们使用正确的驱动，管理 OpenGL 的函数指针。
#include <GLFW/glfw3.h> // glfw 库是协助我们来创建窗口的
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

	glfwInit(); // 初始化 glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // glfwWindowHint 用于配置
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 这两行表示使用的是 3.3 版本的 OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //使用核心模式
																   //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // OS X 上需要加上这句

																   // 创建窗口对象
	GLFWwindow* window = glfwCreateWindow(600, 600, "LearnOpenGL via tangyikejun", NULL, NULL); // 宽，高，标题
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
	glViewport(0, 0, 600, 600); // 坐标原点在左下角。视口可以比窗口小，那么可以在视口以外的区域绘制OpenGL之外的东西。
								// OpenGL 的坐标范围 [-1,1]


								// 注册窗口 resize 的回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 对于视网膜屏，width 和 height 都会比原输入值高，这大概就是会模糊的原因？

	////// 渲染配置 Start
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


	 //1.绑定 VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO); // 创建一个 VAO
	glBindVertexArray(VAO); // 绑定 VAO，之后的 VBO 和 
	
	// 2.设定 VBO
	GLuint VBO;
	glGenBuffers(1, &VBO); // Vertice Buffer Object,顶点缓冲对象，在 GPU 中创建一片内存用于存储缓冲顶点
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // 把 VBO 绑定为 顶点数组缓冲 类型
										// GL_STATIC_DRAW  表示数据几乎不变
										// GL_DYNAMIC_DRAW 表示数据多变
										// GL_STREAM_DRAW 表示数据每次都会变
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //把数据复制到缓冲，最后一个参数指定 GPU 对数据的管理策略。执行完这一步，说明数据已经传到显存里面去了

																			   // 现代 OpenGL 不提供默认的 顶点和片段着色器，所以需要自己撸一个


	// 4.设定顶点属性
	// 设定传入的顶点数据与着色器之前的对应关系，也就是定义 VBO 中数据的意义
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	// 注：
	// index 可以配置多个顶点属性，我们这里配置到 0 位置。前面顶点着色器的 layout(location = 0) 就表示采用下标为0的顶点属性的定义
	// size 顶点属性的大小，我们的顶点属性是 vec3 ,所以是 3
	// type 数据元素的类型 vec3 中的数据类型都是 float
	// normalized 是否需要归一化
	// stride 步长，相邻两个顶点属性之间相差的字节数
	// pointer 本例中表示位置数据相对于缓冲起始位置的偏移量

	// 启用 0 号顶点属性
	glEnableVertexAttribArray(0);

	GLuint LightVAO;
	glGenVertexArrays(1,&LightVAO);
	glBindVertexArray(LightVAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO); // 这个 VBO 里面放的是一个立方体
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(void *)0);

	glEnableVertexAttribArray(0);

	// 设置好了就解除绑定
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // VAO 还在用的时候 不能解绑 EBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	glEnable(GL_DEPTH_TEST);// 开启深度测试，默认是关闭的。深度值存储在每个片段的 z 值中，开启后opengl通过一个深度缓存来判断当前片段是否在其他片段后面，如果是的话就会被裁掉
	////// 渲染配置 End

	// 添加主循环
	while (!glfwWindowShouldClose(window))
	{
		// esc 退出
		processInput(window);

		// 渲染相关 Start
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // 设置用于清除的颜色值
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vec3 lightPos(1.2f, 1.0f, 2.0f);
		// 观察矩阵
		mat4 view;
		view = translate(view, vec3(0.0f, 0.0f, -10.0f));
		// 透视投影矩阵
		mat4 proj;
		proj = perspective((float)radians(45.0f), (float)600 / 600, 0.1f, 100.0f);
		// 模型矩阵
		mat4 model;
		model = mat4();
		model = translate(model, lightPos); // 移动到 lightPos
		model = scale(model, vec3(0.2f)); // 然后缩小

		mat4 omodel;
		omodel = rotate(omodel, (float)radians(45.0),vec3(1,1,0));

		lightShader->use(); // 先执行shader
		// 再设置到uniform
		lightShader->setMat4("proj", proj);
		lightShader->setMat4("view", view);
		lightShader->setMat4("model", model);
		glBindVertexArray(LightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);// 指定图元类型，指定顶点数组的起始索引和绘制的顶点数量

		shader->use(); // 先执行shader
					   // 再设置到uniform
		shader->setVec3("objectColor", vec3(1.0f, 0.5f, 0.31f));
		shader->setVec3("lightColor", vec3(1.0f, 1.0f, 1.0f));
		shader->setMat4("view", view);
		shader->setMat4("proj", proj);
		shader->setMat4("model", omodel);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);// 指定图元类型，指定顶点数组的起始索引和绘制的顶点数量
		// 渲染相关 End

		glfwSwapBuffers(window); // 交换缓冲
		glfwPollEvents(); // 拉取事件
	}

	// 不用了就删除掉
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &LightVAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();//正确释放所有资源
	return 0;
}

// 设置窗口大小变化的回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}