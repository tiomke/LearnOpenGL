#version 330 core // 用的是 3.3 版本的核心模式
layout(location = 0) in vec3 aPos; // in 表明输入的顶点的属性 （Input Vertex Attribute），aPos 是定义的变量
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;
out vec4 ourColor;
out vec2 TexCoord;

void main()
{
	// 设置顶点着色器的输出
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	// 注：实际工程中的程序，输入数据往往不是标准设备坐标，需要先转换为标准设备坐标
	ourColor = vec4(aColor,1.0);
	TexCoord = aTexCoord;
}