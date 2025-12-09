#version 330 core
out vec4 FragColor;
uniform vec4 lightColor;

void main()
{
    // 定义全局光照
    FragColor = lightColor;
}