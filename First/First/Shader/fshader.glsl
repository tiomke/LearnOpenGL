#version 330 core
in vec4 ourColor; // ����Ҫ�� ������ɫ����һ��
in vec2 TexCoord;

uniform sampler2D ourTexture1; // ͨ����������������
uniform sampler2D ourTexture2;

out vec4 fragColor;
void main()
{
	 vec4 ret1 = texture(ourTexture1,TexCoord); // ���� TexCoord ��������� ourTexture ������в���
	 vec4 ret2 = texture(ourTexture2, TexCoord);
	 fragColor = mix(ret1,ret2,1); // 0.4 ��ʾ�ڶ��������Ĺ���ռ 40%
}