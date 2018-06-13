#version 330 core
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor; // �������ɫ���൱���Ƕ�ÿ��������Ĳ�����ϵ���������۾���������ɫ
uniform vec3 lightColor; // �Ƶ���ɫ�����۾���������ɫ
uniform vec3 lightPos; // ��Դλ��

out vec4 fragColor;
void main()
{
	// ������
	float ambientFactor = 0.1;
	vec3 ambient = lightColor*ambientFactor;
	// ������
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos-FragPos);
	//vec3 lightDir = normalize(vec3(1,1,1));
	float diff = max(dot(norm,lightDir),0);
	vec3 diffuse = diff * lightColor;

	fragColor = vec4( (ambient+diffuse)*objectColor ,1.0f);// 
	
}