#version 330 core // �õ��� 3.3 �汾�ĺ���ģʽ
layout(location = 0) in vec3 aPos; // in ��������Ķ�������� ��Input Vertex Attribute����aPos �Ƕ���ı���
layout(location = 1) in vec3 aNormal; // ������
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	// ���ö�����ɫ�������
	gl_Position = proj * view * model * vec4(aPos, 1.0);
	// ע��ʵ�ʹ����еĳ������������������Ǳ�׼�豸���꣬��Ҫ��ת��Ϊ��׼�豸����
	Normal = mat3(transpose(inverse(model)))*aNormal; // mat3(transpose(inverse(model))) �Ƿ��߾���mat3 �Ѿ���ת���� 3��3 ����ȥ��λ�����ԡ� ���߾���������ǰѾֲ������µķ������任����������ķ�����
	// ���õķ�ʽ����cpu����÷��߾����ٴ���������Ϊд�����ÿ��Ƭ�ζ�Ҫ��һ����㣬��������������㿪���ǱȽϴ�ġ�
	FragPos = vec3(model * vec4(aPos, 1.0)); // �Ѿֲ�����ת������������
}