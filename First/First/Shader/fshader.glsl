#version 330 core
in vec4 ourColor; // ����Ҫ�� ������ɫ����һ��
in vec2 TexCoord;

uniform sampler2D ourTexture; // ͨ����������������

out vec4 fragColor;
void main()
{
	fragColor = texture(ourTexture,TexCoord); // ���� TexCoord ��������� ourTexture ������в���
}