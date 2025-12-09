#include "utilities.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Utilities
{

    Shader::Shader(const char *vertexPath, const char *fragmentPath)
    {
        std::string vsrc = load_file(vertexPath);
        std::string fsrc = load_file(fragmentPath);
        GLuint vs = compile_shader(GL_VERTEX_SHADER, vsrc.c_str());
        GLuint fs = compile_shader(GL_FRAGMENT_SHADER, fsrc.c_str());
        this->program = link_program(vs, fs);
    }

    std::string Shader::load_file(const char *path)
    {
        std::ifstream ifs(path);
        std::stringstream ss;
        ss << ifs.rdbuf();
        return ss.str();
    }

    GLuint Shader::compile_shader(GLenum type, const char *src)
    {
        GLuint s = glCreateShader(type);
        glShaderSource(s, 1, &src, nullptr);
        glCompileShader(s);
        GLint ok;
        glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
        if (!ok)
        {
            char log[512];
            glGetShaderInfoLog(s, 512, nullptr, log);
            std::cerr << "Shader error: " << log << std::endl;
        }
        return s;
    }

    GLuint Shader::link_program(GLuint vs, GLuint fs)
    {
        GLuint p = glCreateProgram();
        glAttachShader(p, vs);
        glAttachShader(p, fs);
        glLinkProgram(p);
        GLint ok;
        glGetProgramiv(p, GL_LINK_STATUS, &ok);
        if (!ok)
        {
            char log[512];
            glGetProgramInfoLog(p, 512, nullptr, log);
            std::cerr << "Program error: " << log << std::endl;
        }
        glDeleteShader(vs);
        glDeleteShader(fs);
        return p;
    }

    void Shader::use() const
    {
        glUseProgram(program);
    }

    void Shader::setBool(const std::string &name, bool value) const
    {
        GLint loc = glGetUniformLocation(program, name.c_str());
        glUniform1i(loc, (int)value);
    }

    void Shader::setInt(const std::string &name, int value) const
    {
        GLint loc = glGetUniformLocation(program, name.c_str());
        glUniform1i(loc, value);
    }

    void Shader::setFloat(const std::string &name, float value) const
    {
        GLint loc = glGetUniformLocation(program, name.c_str());
        glUniform1f(loc, value);
    }

    void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
    {
        GLint loc = glGetUniformLocation(program, name.c_str());
        glUniform2fv(loc, 1, &value[0]);
    }

    void Shader::setVec2(const std::string &name, float x, float y) const
    {
        GLint loc = glGetUniformLocation(program, name.c_str());
        glUniform2f(loc, x, y);
    }

    void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
    {
        GLint loc = glGetUniformLocation(program, name.c_str());
        glUniform3fv(loc, 1, &value[0]);
    }

    void Shader::setVec3(const std::string &name, float x, float y, float z) const
    {
        GLint loc = glGetUniformLocation(program, name.c_str());
        glUniform3f(loc, x, y, z);
    }

    void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
    {
        GLint loc = glGetUniformLocation(program, name.c_str());
        glUniform4fv(loc, 1, &value[0]);
    }

    void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
    {
        GLint loc = glGetUniformLocation(program, name.c_str());
        glUniform4f(loc, x, y, z, w);
    }

    void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        GLint loc = glGetUniformLocation(program, name.c_str());
        glUniformMatrix2fv(loc, 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        GLint loc = glGetUniformLocation(program, name.c_str());
        glUniformMatrix3fv(loc, 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        GLint loc = glGetUniformLocation(program, name.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
    }

} // namespace Utilities