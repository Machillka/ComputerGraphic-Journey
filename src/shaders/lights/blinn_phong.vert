#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;

void main() {
    // 设置位置
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    // 计算世界坐标系下顶点法线
    FragPos = vec3(model * vec4(aPos, 1.0));
    // 顶点在世界空间的法线
    Normal = mat3(transpose(inverse(model))) * aPos;
}
