#version 330 core // 用的是 3.3 版本的核心模式
layout(location = 0) in vec3 aPos; // in 表明输入的顶点的属性 （Input Vertex Attribute），aPos 是定义的变量
layout(location = 1) in vec3 aNormal; // 法向量
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	// 设置顶点着色器的输出
	gl_Position = proj * view * model * vec4(aPos, 1.0);
	// 注：实际工程中的程序，输入数据往往不是标准设备坐标，需要先转换为标准设备坐标
	Normal = mat3(transpose(inverse(model)))*aNormal; // mat3(transpose(inverse(model))) 是法线矩阵，mat3 把矩阵转换成 3×3 矩阵，去除位移属性。 法线矩阵的作用是把局部坐标下的法向量变换成世界坐标的法向量
	// 更好的方式是在cpu计算好法线矩阵再传进来，因为写在这里，每个片段都要做一遍计算，而进行逆矩阵运算开销是比较大的。
	FragPos = vec3(model * vec4(aPos, 1.0)); // 把局部坐标转换成世界坐标
}