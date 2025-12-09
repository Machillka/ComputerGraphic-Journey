#version 330 core
layout(location = 0) in vec3 aPos;
void main() {
    // 再顶点着色器的时候把所有顶点的y取相反数，得到上下颠倒的形状
    gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);
}
