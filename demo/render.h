#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>

#include "prisca.h"

namespace GLRender {

    struct Context {

        const GLchar* vertex_shader_source = 
            "#version 330 core\n"
            "layout (location = 0) in vec2 position;\n"
            "layout (location = 1) in vec4 color;\n"
            "out vec4 frag_color;\n"
            "uniform float width;\n"
            "uniform float height;\n"
            "void main()\n"
            "{\n"
            "gl_Position = vec4(position.x * 2 / width - 1, position.y * 2 / height - 1, 0, 1.0);\n"
            "frag_color = color;\n"
            "}\0";

        const GLchar* fragment_shader_source = "#version 330 core\n"
            "in vec4 frag_color;\n"
            "out vec4 color;\n"
            "void main()\n"
            "{\n"
            "color = vec4(frag_color);\n"
            "}\n\0";
        
        int width, height;

        GLuint vbo_id;
        GLuint ebo_id;
        GLuint vao_id;
        GLuint shader_program;
    } g_Context;

    void Init(int width, int height) {

        glViewport(0, 0, width, height);

        g_Context.width = width;
        g_Context.height = height;

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
        glGenBuffers(1, &g_Context.ebo_id);

        glBindVertexArray(g_Context.vao_id);

        glBindBuffer(GL_ARRAY_BUFFER, g_Context.vbo_id);
        glBufferData(GL_ARRAY_BUFFER, 99 * sizeof(Prisca::RenderVertex) , NULL, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (2 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_Context.ebo_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 99 * sizeof(Prisca::RenderIndex), NULL, GL_DYNAMIC_DRAW);
        // Todo glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    
    }

    void Render() {
        // Render
        // Clear the colorbuffer
        glUseProgram(g_Context.shader_program);
        glBindVertexArray(g_Context.vao_id);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Render(Prisca::RenderOutput* render_output) {
        Prisca::RenderOutput& ro = *render_output;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(g_Context.shader_program);
        
        GLint width_uniform_loc = glGetUniformLocation(g_Context.shader_program, "width");
        glUniform1f(width_uniform_loc, g_Context.width);
        GLint height_uniform_loc = glGetUniformLocation(g_Context.shader_program, "height");
        glUniform1f(height_uniform_loc, g_Context.height);
        int vertex_offset = 0;
        int index_offset = 0;

        glBindVertexArray(g_Context.vao_id);
        for (int i = 0; i < Prisca::Array::Size(ro.commands); ++i) {
            Prisca::RenderOutput& ro = (*render_output);
            Prisca::RenderCommand& command = ro.commands.element[i];

            glBindBuffer(GL_ARRAY_BUFFER, g_Context.vbo_id);
            glBufferSubData(GL_ARRAY_BUFFER, 
                            vertex_offset, 
                            command.n_vertex * sizeof(Prisca::RenderVertex), 
                            &ro.vertexes.element[vertex_offset]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_Context.ebo_id);
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 
                            index_offset, 
                            command.n_index * sizeof(Prisca::RenderIndex),
                            &ro.indexes.element[vertex_offset]);
            vertex_offset += command.n_vertex;
            index_offset += command.n_index;

            glDrawElements(GL_TRIANGLES, command.n_index, GL_UNSIGNED_INT, 0);
        }

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }
    
    void Cleanup() {
        glDeleteVertexArrays(1, &g_Context.vao_id);
        glDeleteBuffers(1, &g_Context.vbo_id);
    }
}