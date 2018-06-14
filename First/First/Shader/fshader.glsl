#version 330 core
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor; // �������ɫ���൱���Ƕ�ÿ��������Ĳ�����ϵ���������۾���������ɫ
uniform vec3 lightColor; // �Ƶ���ɫ�����۾���������ɫ
uniform vec3 lightPos; // ��Դλ��
uniform vec3 viewPos; // �۲���λ��

out vec4 fragColor;
void main()
{
	// ������
	float ambientFactor = 0.1;
	vec3 ambient = lightColor*ambientFactor;
	// ������
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos-FragPos);
	float diff = max(dot(norm,lightDir),0);
	diff = 0; // ��ʱ��������Ĺ���ȡ���������㿴���淴��
	vec3 diffuse = diff * lightColor;
	
	// ���淴��
	float specularStrength = 1;//����ǿ��
	// 
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm); // ��ȡ���ߵķ��䵥λ���� reflect(����������������)
	float spec = pow(max(dot(viewDir, reflectDir), 0),256); // pow ���ݳ� ��256�Ǹ߹�ķ����(Shininess)��Խ�߷���Խǿ��
	vec3 specular = specularStrength * spec * lightColor;
	fragColor = vec4( (ambient+diffuse+specular)*objectColor ,1.0f);// 
	
}