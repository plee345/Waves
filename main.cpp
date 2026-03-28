#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shader_s.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void debugPrint();

float xPosition = 0.0f;
float yPosition = 0.0f;

int main()
{
    int shapeState;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800,600, "adrian", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initalize GLAD" << std::endl;
        return -1;
    }

    //include shader files
    Shader ourShader ("/Users/plee/Waves/shader.vs", "/Users/plee/Waves/shader.fs");
    //Get location of uniform float/setup position float for CPU
    int horizontalPos = glGetUniformLocation(ourShader.ID, "xTransform");
    int verticalPos = glGetUniformLocation(ourShader.ID, "yTransform");

    float vertices[] = {
        0.10f,  0.25f, 0.0f,  // top right
        0.10f, -0.25f, 0.0f,  // bottom right
        -0.10f, -0.25f, 0.0f,  // bottom left
        -0.10f,  0.25f, 0.0f   // top left 
    };
    
    unsigned int indices[]
    {
        0, 1, 3,
        1, 2, 3
    };

    //initialize vertex array object and bind it for later use in render loop
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //initialize vertex buffer object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    //bind vertex data to the vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // initialize element buffer object
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    //rendering loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.00f, 0.00f, 0.00f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();
        glUniform1f(horizontalPos, xPosition);
        glUniform1f(verticalPos, yPosition);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        std::cout << "\nClosing Window...\n";
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if (xPosition <= -1.0f)
        {
            std::cout << "xPosition at left bounds." << "\n";
        }
        else
        {
            xPosition -= 0.01f;
            debugPrint();
        }
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if (xPosition >= 1.0f)
        {
            std::cout << "xPosition at right bounds." << "\n";
        }
        else
        {
            xPosition += 0.01f;
            debugPrint();
        }
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        if (yPosition >= 1.0f)
        {
            std::cout << "yPosition at upper bounds." << "\n";
        }
        else
        {
            yPosition += 0.01f;
            debugPrint();
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (yPosition <= -1.0f)
        {
            std::cout << "yPosition at lower bounds." << "\n";
        }
        else
        {
            yPosition -= 0.01f;
            debugPrint();
        }
    }
}

void debugPrint()
{
    std::cout << "\r\033[KxPosition: " << xPosition << " | yPosition: " << yPosition << std::flush;
}