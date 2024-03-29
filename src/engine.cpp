#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Render/ShaderProgram.h"
//#include "Math/Math.h"

GLfloat point[] = {
    -0.5f, 0.0f, 0.0f,
    0.5f, 0.0f, 0.0f,
    0.0f, 0.5f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

const char* vertex_shader =
"#version 420\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 1.0);"    
"}";

const char* fragment_shader =
"#version 420\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color, 1.0);"
"}";

int Win_Width = 640;
int Win_Height = 480;

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height){
    int Win_Width = width;
    int Win_Height = height;
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(void){
    GLFWwindow* window;

    if (!glfwInit()){
        std::cout << "glfw not load" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(Win_Width, Win_Height, "Game_Engine", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);

    glfwMakeContextCurrent(window);

    if(!gladLoadGL()){
        std::cout << "Glad not load" << std::endl;
        return -1;
    }

    const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    std::cout << "OpenGL version: " << version << std::endl;

    glClearColor(1, 1, 1, 1);

    std::string vertexShader(vertex_shader);
    std::string fragmentShader(fragment_shader);
    Render::ShaderProgram shaderProgram(vertexShader, fragmentShader);
    
    if (!shaderProgram.isCompiled()){
        std::cerr << "cant compile shader in main program!";
        return -1;
    }

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    while (!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}