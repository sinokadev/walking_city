#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {

public:
    unsigned int ID;
    Shader(const char *vertex_path, const char *frag_path) {
        // Load
        std::string vertex_code_str = load_file(vertex_path);
        std::string frag_code_str   = load_file(frag_path);

        const char *vertex_code = vertex_code_str.c_str();
        const char *frag_code   = frag_code_str.c_str();

        // Compile
        unsigned int vertex, fragment;

        // vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertex_code, NULL);
        glCompileShader(vertex);
        verifyShader(vertex);

        // fragment Shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &frag_code, NULL);
        glCompileShader(fragment);
        verifyShader(fragment);

        // Make Shader
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        verifyShaderProgram(ID);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }


    void use() 
    { 
        glUseProgram(ID); 
    }

    void setUniform(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }

    void setUniform(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }

    void setUniform(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }
    
    void setUniform(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setUniform(const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
    }
    
    void setUniform(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setUniform(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
    }
    
    void setUniform(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setUniform(const std::string &name, float x, float y, float z, float w) 
    { 
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
    }
    
    void setUniform(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    
    void setUniform(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    
    void setUniform(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
private:
    std::string load_file(const char *file_path) {
        std::string shader_code;

        std::ifstream shader_file;

        shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            shader_file.open(file_path);
            std::stringstream shader_stream;

            shader_stream << shader_file.rdbuf();

            shader_file.close();

            shader_code = shader_stream.str();
        }
        catch (std::ifstream::failure& e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }

        return shader_code;
    }

    void verifyShader(GLuint shaderID) const
    {
        GLint compileSuccess = 0;
        char logBuffer[1024];

        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileSuccess);
        if (compileSuccess == GL_FALSE) {
            glGetShaderInfoLog(shaderID, sizeof(logBuffer), nullptr, logBuffer);
            std::cerr << "[Shader Error] Compilation failed:\n"
                        << logBuffer << "\n---------------------------------\n";
        }
    }

    void verifyShaderProgram(GLuint shaderID) const
    {
        GLint compileSuccess = 0;
        char logBuffer[1024];

        glGetProgramiv(shaderID, GL_LINK_STATUS, &compileSuccess);
        if (compileSuccess == GL_FALSE) {
            glGetProgramInfoLog(shaderID, sizeof(logBuffer), nullptr, logBuffer);
            std::cerr << "[Shader Program Error] Linking failed:\n"
                        << logBuffer << "\n---------------------------------\n";
        }
    }
};

#endif