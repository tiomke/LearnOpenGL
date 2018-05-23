#include <glad/glad.h> // <glad/glad.h> 要在 <GLFW/glfw3.h> 之前，有 GL/gl.h 等依赖关系。glad 库协助我们使用正确的驱动，管理 OpenGL 的函数指针。
#include <GLFW/glfw3.h> // glfw 库是协助我们来创建窗口的
#include <Shader/Shader.h>
#include <iostream>
// 数学库
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
	glViewport(0, 0, 800, 600); // 坐标原点在左下角。视口可以比窗口小，那么可以在视口以外的区域绘制OpenGL之外的东西。
								// OpenGL 的坐标范围 [-1,1]


								// 注册窗口 resize 的回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // 对于视网膜屏，width 和 height 都会比原输入值高，这大概就是会模糊的原因？

	////// 渲染配置 Start
	Shader* shader = new Shader("../First/Shader/vshader.glsl", "../First/Shader/fshader.glsl");
	//Shader* shader = new Shader("", "");


	float vertices[] = { // 直接使用有重复顶点的定义方式
		// 顶点位置				//uv坐标
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
	GLuint indices[] = { // 索引，指明顶点的绘制顺序
		0,1,2,
		1,2,3,
	};


	// 1.绑定 VAO
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


	/*GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/
	// 4.设定顶点属性
	// 设定传入的顶点数据与着色器之前的对应关系，也就是定义 VBO 中数据的意义
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
	// 注：
	// index 可以配置多个顶点属性，我们这里配置到 0 位置。前面顶点着色器的 layout(location = 0) 就表示采用下标为0的顶点属性的定义
	// size 顶点属性的大小，我们的顶点属性是 vec3 ,所以是 3
	// type 数据元素的类型 vec3 中的数据类型都是 float
	// normalized 是否需要归一化
	// stride 步长，相邻两个顶点属性之间相差的字节数
	// pointer 本例中表示位置数据相对于缓冲起始位置的偏移量

	// 启用 0 号顶点属性
	glEnableVertexAttribArray(0);
	//设置用于纹理参数的顶点属性
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);


	// 设置好了就解除绑定
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // VAO 还在用的时候 不能解绑 EBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 创建纹理
	stbi_set_flip_vertically_on_load(true);//图片y坐标往往原点在上面，需要在加载图像前做一下翻转
	int width, height, nChannel;
	unsigned char *data = stbi_load("../First/wall.jpg", &width, &height, &nChannel, 0); // 加载源图
	int width2, height2, nChannel2;
	unsigned char *data2 = stbi_load("../First/test.png", &width2, &height2, &nChannel2, 0); // 加载源图
	if (!data || !data2)
	{
		cout << "texture data load fail" << endl;
		return -1;
	}

	GLuint texture; // 声明一个纹理对象
	glGenTextures(1, &texture); // 参数一表示需要生成的纹理数量
	glBindTexture(GL_TEXTURE_2D,texture);
	// 设置纹理的环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//纹理在横向的环绕模式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// mipmap 的时候才用到
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// mipmap 的时候才用到
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//往纹理对象绑上纹理
	//注：
	//参数一 表示通过 GL_TEXTURE_2D 作用在生成的 texuture 上
	//参数二 表示生成mipmap的level，0表示基础的
	//参数三、四、五 生成的纹理的存储格式、宽度、高度
	//参数六 设置为0，遗留参数
	//参数七 源图的存储格式
	//参数八 源图的数据类型
	//参数九 源图的数据

	GLuint texture2; // 声明第二个纹理对象
	glGenTextures(1, &texture2); // 
	glBindTexture(GL_TEXTURE_2D, texture2);//绑定到第二个纹理
	// 设置纹理的环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//纹理在横向的环绕模式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);// mipmap 的时候才用到
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);// mipmap 的时候才用到
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);//从rgba-rgb



	//glGenerateMipmap(GL_TEXTURE_2D);//生成mipmap，也可以重复上面的语句，改变 mipmap的 level
	stbi_image_free(data); // 释放图像内存
	stbi_image_free(data2);

	shader->use(); // 先执行shader
	// 再设置到uniform
	glUniform1i(glGetUniformLocation(shader->ID, "ourTexture1"), 0);
	glUniform1i(glGetUniformLocation(shader->ID, "ourTexture2"), 1); 
	//shader->setInt("ourTexture2", 1);// 也可以直接辅助函数调用

	////// 渲染配置 End

	// 添加主循环
	while (!glfwWindowShouldClose(window))
	{
		// esc 退出
		processInput(window);

		// 渲染相关 Start
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置用于清除的颜色值
		glClear(GL_COLOR_BUFFER_BIT); // 清除颜色缓存


		// 绑定纹理
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		// 激活着色器程序对象
		shader->use();
		glBindVertexArray(VAO);
		//float t = glfwGetTime();
		//GLint pos = glGetUniformLocation(program, "ourColor");
		//glUniform4f(pos, 0.5, sin(t)/3 + 0.5, 0.2, 1);


		// 模型矩阵
		mat4 model;
		model = rotate(model, (float)glfwGetTime(), vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, GL_FALSE, value_ptr(model));
		// 观察矩阵
		mat4 view;
		view = translate(view, vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader->ID, "view"), 1, GL_FALSE, value_ptr(view));
		// 透视投影矩阵
		mat4 proj;
		proj = perspective((float)radians(45.0f), (float)800 / 600, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader->ID, "proj"), 1, GL_FALSE, value_ptr(proj));

		glDrawArrays(GL_TRIANGLES,0,36);// 指定图元类型，指定顶点数组的起始索引和绘制的顶点数量



		// 渲染相关 End

		glfwSwapBuffers(window); // 交换缓冲
		glfwPollEvents(); // 拉取事件
	}

	// 不用了就删除掉
	glDeleteVertexArrays(1, &VAO);
	glDeleteTextures(1, &texture);
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