#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int Win_Width = 1920;
int Win_Height = 1080;

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

    /* Initialize the library */
    if (!glfwInit()){
        std::cout << "glfw not load" << std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(Win_Width, Win_Height, "Game_Engine", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(!gladLoadGL()){
        std::cout << "Glad not load" << std::endl;
        return -1;
    }

    const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    std::cout << "OpenGL version: " << version << std::endl;

    glClearColor(0, 0, 255, 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}