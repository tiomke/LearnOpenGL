#version 330 core // �õ��� 3.3 �汾�ĺ���ģʽ
layout(location = 0) in vec3 aPos; // in ��������Ķ�������� ��Input Vertex Attribute����aPos �Ƕ���ı���


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	// ���ö�����ɫ�������
	gl_Position = proj * view * model * vec4(aPos, 1.0);
	// ע��ʵ�ʹ����еĳ������������������Ǳ�׼�豸���꣬��Ҫ��ת��Ϊ��׼�豸����

}