#version 330 core
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor; // 物体的颜色，相当于是对每个光分量的不吸收系数，不是眼睛看到的颜色
uniform vec3 lightColor; // 灯的颜色，是眼睛看到的颜色
uniform vec3 lightPos; // 光源位置

out vec4 fragColor;
void main()
{
	// 环境光
	float ambientFactor = 0.1;
	vec3 ambient = lightColor*ambientFactor;
	// 漫反射
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos-FragPos);
	//vec3 lightDir = normalize(vec3(1,1,1));
	float diff = max(dot(norm,lightDir),0);
	vec3 diffuse = diff * lightColor;

	fragColor = vec4( (ambient+diffuse)*objectColor ,1.0f);// 
	
}