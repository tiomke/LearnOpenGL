#version 330 core
in vec4 ourColor; // 名字要与 顶点着色器的一致
in vec2 TexCoord;

uniform sampler2D ourTexture1; // 通过采样器传入纹理
uniform sampler2D ourTexture2;

out vec4 fragColor;
void main()
{
	 vec4 ret1 = texture(ourTexture1,TexCoord); // 根据 TexCoord 纹理坐标对 ourTexture 纹理进行采样
	 vec4 ret2 = texture(ourTexture2, 0.1*TexCoord+0.4); // 取图形中间1/4长宽的区域
	 fragColor = mix(ret1,ret2,0.4); // 0.4 表示第二个参数的贡献占 40%
}