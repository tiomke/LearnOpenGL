#version 330 core

uniform vec3 objectColor; // �������ɫ���൱���Ƕ�ÿ��������Ĳ�����ϵ���������۾���������ɫ
uniform vec3 lightColor; // �Ƶ���ɫ�����۾���������ɫ


out vec4 fragColor;
void main()
{
	fragColor = vec4( lightColor*objectColor ,1.0f);// 
}