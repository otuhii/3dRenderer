#include "include/Parser.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <math.h>


void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void UserInputCallBack(GLFWwindow* window, float& xOffset, float& yOffset);





int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello, world!", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);


    uint32_t 
        VAO{},
        VBO{};

    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };


    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    int success{};
    char infoLog[512]{};

    unsigned int
        shaderProgram1{ glCreateProgram()};



    Parser::ParseAndLinkShader("shaders/base.vert", shaderProgram1, GL_VERTEX_SHADER);
    Parser::ParseAndLinkShader("shaders/yellow.frag", shaderProgram1, GL_FRAGMENT_SHADER);
    glLinkProgram(shaderProgram1);
    glGetProgramiv(
            shaderProgram1, 
            GL_LINK_STATUS, 
            &success
        );
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n\n" << infoLog << std::endl;
    }


    float 
        xOffset{},
        yOffset{};
        

    while (!glfwWindowShouldClose(window))
    {
        bool 
            changeArrayBuffer{};

        UserInputCallBack(window, xOffset, yOffset);

        glClearColor(0.3f, 0.3f, 0.3f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shaderProgram1);

        
        int positionOffset = glGetUniformLocation(shaderProgram1, "positionOffset");
        glUniform3f(positionOffset, xOffset, yOffset, 0.0f);
            

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram1);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    //std::cout << "BUFFER RESIZED WITH: " << width << " " << height << std::endl;

}

void UserInputCallBack(GLFWwindow* window, float& xOffset, float& yOffset)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        yOffset += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        yOffset -= 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        xOffset -= 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        xOffset += 0.01f;
    }
}

