#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

// 摄像机参数
float camX = 0.0f, camY = 0.0f, camZ = 3.0f;

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camZ -= 0.05f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camZ += 0.05f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camX -= 0.05f;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camX += 0.05f;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Transform Demo", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);

    // 顶点数据：立方体
    float vertices[] = {
        -0.5f,-0.5f,-0.5f,  0.5f,-0.5f,-0.5f,  0.5f, 0.5f,-0.5f,
        0.5f, 0.5f,-0.5f, -0.5f, 0.5f,-0.5f, -0.5f,-0.5f,-0.5f,
        // ... 其他面省略，可用完整立方体数据
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 着色器编译与链接（略，和之前三角形示例类似）
    GLuint shaderProgram = ...;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(0.1f,0.1f,0.15f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // 模型矩阵：旋转
        glm::mat4 model = glm::rotate(glm::mat4(1.0f),
                                      (float)glfwGetTime(),
                                      glm::vec3(0.0f,1.0f,0.0f));

        // 视图矩阵：摄像机位置
        glm::mat4 view = glm::lookAt(glm::vec3(camX, camY, camZ),
                                     glm::vec3(0.0f,0.0f,0.0f),
                                     glm::vec3(0.0f,1.0f,0.0f));

        // 投影矩阵：透视投影
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                800.0f/600.0f,
                                                0.1f, 100.0f);

        // 上传到着色器
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"model"),1,GL_FALSE,&model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"view"),1,GL_FALSE,&view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,&projection[0][0]);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
