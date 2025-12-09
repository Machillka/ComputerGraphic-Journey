#version 330 core
out vec4 FragColor;
uniform vec4 testColor;

void main()
{
    // 使得pixel当前颜色设置为testColor
    FragColor = testColor;
}
