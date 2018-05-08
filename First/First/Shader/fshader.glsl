#version 330 core
in vec4 ourColor; // 名字要与 顶点着色器的一致
in vec2 TexCoord;

uniform sampler2D ourTexture; // 通过采样器传入纹理

out vec4 fragColor;
void main()
{
	fragColor = texture(ourTexture,TexCoord); // 根据 TexCoord 纹理坐标对 ourTexture 纹理进行采样
}