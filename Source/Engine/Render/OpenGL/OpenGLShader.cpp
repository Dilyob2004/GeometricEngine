#include <Engine/Render/OpenGL/OpenGLShader.h>
#include <Engine/Platform/Win32/OpenGLSupport.h>
#include <fstream>
#include <vector>
#include <map>
namespace MeteorEngine
{
    bool ReadFileToBuffer(const std::string& filename, std::string& buffer)
    {
        std::ifstream file(filename.c_str(), std::ios_base::binary);
        if (file)
        {
            file.seekg(0, std::ios_base::end);
            std::streamsize size = file.tellg();
            if (size > 0)
            {
                file.seekg(0, std::ios_base::beg);
                buffer.resize(static_cast<std::size_t>(size));
                file.read(&buffer[0], buffer.size());
            }
            buffer.push_back('\0');
            file.close();
            return true;
        }
        else
            return false;
    }
    bool getFileContents(const std::string& file, std::map<std::string, std::string>& listOfShader)
    {
        std::string beginType = "#shader";

        std::size_t pos = file.find(beginType, 0);
        while(pos != std::string::npos)
        {
            std::size_t eol = file.find_first_of("\r\n", pos);
            std::size_t begin = pos + beginType.size() + 1;
            std::string type  = file.substr(begin, eol - begin);
            std::size_t nextLinePos = file.find_first_of("\r\n", eol);
            pos = file.find(beginType, nextLinePos);
            listOfShader[type]  = file.substr(nextLinePos, pos - (nextLinePos == std::string::npos? file.size()-1:nextLinePos));

        }

        return true;
    }
    OpenGLShader::OpenGLShader():
        m_shaderProgram(0)
    {

    }
    OpenGLShader::OpenGLShader(const std::string & shader, ShaderType type) :
		m_shaderProgram(0)
    {
        switch(type)
        {
            case ShaderType::FragmentShader:    Compile(shader.c_str(), NULL);
            case ShaderType::VertexShader:      Compile(NULL, shader.c_str());
            default: break;
        }
    }
    OpenGLShader::OpenGLShader(const std::string &shader) :
		m_shaderProgram(0)
    {
        std::string buffer;
        if(ReadFileToBuffer(shader, buffer))
        {
            std::map<std::string, std::string> type;
            if(getFileContents(buffer, type))
                Compile(type["fragment"].c_str(), type["vertex"].c_str());
            else
                std::cerr << "Failed to load asset file: " << shader << "\n";
        }
        else
            std::cerr << "Failed to load asset file: " << shader << "\n";
    }
    OpenGLShader::OpenGLShader(const std::string &fragment, const std::string &vertex) :
		m_shaderProgram(0)
    {
        Compile(fragment.c_str(), vertex.c_str());
    }
    OpenGLShader::~OpenGLShader()
    {
        if(m_shaderProgram)
            glDeleteProgram(m_shaderProgram);
    }
    void OpenGLShader::Bind() const
    {
        glUseProgram(m_shaderProgram);
    }
    void OpenGLShader::UnBind() const
    {
        glUseProgram(0);
    }
    void OpenGLShader::SetUniformMat4(const std::string& name, const Matrix4f& mat)
    {
        GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, &(mat[0].x));
    }
    void OpenGLShader::SetUniformFloat4(const std::string& name, const Vector4f& v)
    {
        GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());
        glUniform4f(location, v.x, v.y, v.z, v.w);
    }
    void OpenGLShader::SetUniformFloat3(const std::string& name, const Vector3f& v)
    {
        GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());
        glUniform3f(location, v.x, v.y, v.z);
    }
    void OpenGLShader::SetUniformFloat2(const std::string& name, const Vector2f& v)
    {
        GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());
        glUniform2f(location, v.x, v.y);
    }
    void OpenGLShader::SetUniformFloat(const std::string& name, float v)
    {
        GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());
        glUniform1f(location, v);
    }


    void OpenGLShader::SetUniformInt4(const std::string& name, const Vector4i& v)
    {
        GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());
        glUniform4i(location, v.x, v.y, v.z, v.w);
    }
    void OpenGLShader::SetUniformInt3(const std::string& name, const Vector3i& v)
    {
        GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());
        glUniform3i(location, v.x, v.y, v.z);
    }
    void OpenGLShader::SetUniformInt2(const std::string& name, const Vector2i& v)
    {
        GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());
        glUniform2i(location, v.x, v.y);
    }
    void OpenGLShader::SetUniformInt(const std::string& name, int v)
    {
        GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());
        glUniform1i(location, v);
    }

    void OpenGLShader::Compile(const char* frag, const char* vert)
    {
        GLuint program = glCreateProgram();
        if(frag)
        {
            GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &frag, 0);
            glCompileShader(fragmentShader);

            GLint isCompiled = 0;
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
            if (!isCompiled)
            {
                GLint maxLength = 0;
                glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
                for(size_t i = 0; i < infoLog.size(); i++)
                    std::cout << infoLog[i];
                glDeleteShader(fragmentShader);
                glDeleteProgram(program);
                return;
            }
            glAttachShader(program, fragmentShader);
        }
        if(vert)
        {
            GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vert, 0);
            glCompileShader(vertexShader);

            GLint isCompiled = 0;
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
            if(!isCompiled)
            {
                GLint maxLength = 0;
                glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
                for(size_t i = 0; i < infoLog.size(); i++)
                    std::cout << infoLog[i];
                glDeleteShader(vertexShader);
                glDeleteProgram(program);
                return;
            }
            glAttachShader(program, vertexShader);
        }
        glLinkProgram(program);
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
        if (!isLinked)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
            glDeleteProgram(program);
            return;
        }
        m_shaderProgram = program;

        return;
    }
}
