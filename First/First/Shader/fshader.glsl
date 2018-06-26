#version 330 core
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor; // 物体的颜色，相当于是对每个光分量的不吸收系数，不是眼睛看到的颜色
uniform vec3 lightColor; // 灯的颜色，是眼睛看到的颜色
uniform vec3 viewPos; // 观察者位置

// 材质，材质通过设置冯氏光照模型的三个不同的分量+闪度来定义物体的视觉特性
struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

uniform vec3 lightPos;
// 光源特性
//struct Light
//{
//	float position;
//
//	vec3 ambient;
//	vec3 diffuse;
//	vec3 specular;
//};

out vec4 fragColor;
void main()
{
	// 环境光
	float ambientFactor = 0.1;
	vec3 ambient = lightColor*material.ambient*ambientFactor;
	// 漫反射
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos-FragPos);
	float diff = max(dot(norm,lightDir),0);
	diff = 0; // 临时把漫反射的贡献取消掉，方便看镜面反射
	vec3 diffuse = diff * lightColor * material.diffuse;
	
	// 镜面反射
	float specularStrength = 1;//镜面强度
	// 
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm); // 获取光线的反射单位向量 reflect(入射向量，法向量)
	float spec = pow(max(dot(viewDir, reflectDir), 0),material.shininess); // pow 是幂乘 ，256是高光的反光度(Shininess)，越高反光越强烈
	vec3 specular = specularStrength * spec * lightColor * material.specular;
	fragColor = vec4( (ambient+diffuse+specular)*objectColor ,1.0f);// 
	
}