#version 330 core // �õ��� 3.3 �汾�ĺ���ģʽ
layout(location = 0) in vec3 aPos; // in ��������Ķ�������� ��Input Vertex Attribute����aPos �Ƕ���ı���
layout(location = 1) in vec3 aColor;
out vec4 ourColor;
void main()
{
	// ���ö�����ɫ�������
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	// ע��ʵ�ʹ����еĳ������������������Ǳ�׼�豸���꣬��Ҫ��ת��Ϊ��׼�豸����
	ourColor = vec4(aColor,1.0);
}