#include <GL/glew.h>
#include <iostream>

#pragma once

namespace GLRender {

    struct Context {

        const GLchar* vertex_shader_source = "#version 330 core\n"
            "layout (location = 0) in vec3 position;\n"
            "void main()\n"
            "{\n"
            "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
            "}\0";

        const GLchar* fragment_shader_source = "#version 330 core\n"
            "out vec4 color;\n"
            "void main()\n"
            "{\n"
            "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";
        
        int width, height;

        GLuint vbo_id;
        GLuint vao_id;
        GLuint shader_program;
    } g_Context;

    void Init(int width, int height) {

        glViewport(0, 0, width, height);

        GLint success;
        GLchar infoLog[512];

        GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &g_Context.vertex_shader_source, NULL);
        glCompileShader(vertex_shader);
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &g_Context.fragment_shader_source, NULL);
        glCompileShader(fragment_shader);
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        g_Context.shader_program = glCreateProgram();
        glAttachShader(g_Context.shader_program, vertex_shader);
        glAttachShader(g_Context.shader_program, fragment_shader);
        glLinkProgram(g_Context.shader_program);
        glGetProgramiv(g_Context.shader_program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(g_Context.shader_program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        
        glGenVertexArrays(1, &g_Context.vao_id);
        glGenBuffers(1, &g_Context.vbo_id);
        
        GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f 
        };

        glBindVertexArray(g_Context.vao_id);
        glBindBuffer(GL_ARRAY_BUFFER, g_Context.vbo_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    
    }

    void Render() {
        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(g_Context.shader_program);
        glBindVertexArray(g_Context.vao_id);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }
    
    void Cleanup() {
        glDeleteVertexArrays(1, &g_Context.vao_id);
        glDeleteBuffers(1, &g_Context.vbo_id);
    }
}