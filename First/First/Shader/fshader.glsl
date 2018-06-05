#version 330 core

uniform vec3 objectColor; // 物体的颜色，相当于是对每个光分量的不吸收系数，不是眼睛看到的颜色
uniform vec3 lightColor; // 灯的颜色，是眼睛看到的颜色


out vec4 fragColor;
void main()
{
	fragColor = vec4( lightColor*objectColor ,1.0f);// 
}