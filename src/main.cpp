#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int HEIGHT = 480;
int WIDTH = 640;

void glfwWindowSizeChangeEvent(GLFWwindow* window, int width, int height)
{
    HEIGHT = height;
    WIDTH = width;
    glViewport(0, 0, WIDTH, HEIGHT);
    std::cout << "Window change!" << std::endl;
}

void glfwKeyPressedEvent(GLFWwindow* window, int key, int scanecode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE)
    {
        if (action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
}

int main(void)
{

    if (!glfwInit())
    {
        std::cout << "glfw no Init!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);

    if (!window)
    {
        std::cout << "No window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, glfwWindowSizeChangeEvent);
    glfwSetKeyCallback(window, glfwKeyPressedEvent);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cout << "No glad!" << std::endl;
        return -1;
    }

    std::cout << "Render " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0, 1, 0, 1);

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