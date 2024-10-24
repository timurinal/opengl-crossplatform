#include <iostream>
#include <vector>
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "shader.h"

void framebuffer_resized(GLFWwindow* window, int width, int height);

int main() {
    if (glfwInit() == GLFW_FALSE) {
        throw std::runtime_error("[GLFW] Failed to initialise");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(800, 600, "OpenGL Demo", nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("[GLFW] Failed to create window");
    }

    std::cout << "[GLFW] Window created" << std::endl;

    glfwMakeContextCurrent(window);

    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("[GLFW] Failed to initialise GLAD");
    }

    std::cout << "[GLFW] OpenGL initialised" << std::endl;

    glfwSetFramebufferSizeCallback(window, framebuffer_resized);

    glViewport(0, 0, 800, 600);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    const std::vector vertices = {
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f
    };
    const std::vector triangles = {
        0, 2, 1
    };

    unsigned int vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * triangles.size(), triangles.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

    Shader shader = Shader("../runtime/shaders/shader.vert", "../runtime/shaders/shader.frag");

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void framebuffer_resized(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
