#include "shaderClass.h"

std::string get_file_contents(const char *filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;        // An alt would be something like this for the size
        in.seekg(0, std::ios::end);  // auto size= std::filesystem::file_size(filename);
        contents.resize(in.tellg()); // std::string contents(size, '\0');
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size()); // in.read(contents.dat(), size);
        in.close();
        return (contents);
    }
    throw std::runtime_error("Failed to open shader file.");
}

Shader::Shader(const char *vertexFile, const char *fragmentFile)
{
    std::string vertexCode = get_file_contents(vertexFile);
    std::string fragmentCode = get_file_contents(fragmentFile);

    const char *vertexSource = vertexCode.c_str();
    const char *fragmentSource = fragmentCode.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Check vertex shader compile
    GLint hasCompiled;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE)
    {
        char infoLog[1024];
        glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
        std::cout << "Vertex Shader Compilation Failed:\n"
                  << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Check fragment shader compile
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &hasCompiled);
    if (hasCompiled == GL_FALSE)
    {
        char infoLog[1024];
        glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
        std::cout << "Fragment Shader Compilation Failed:\n"
                  << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Check linking
    GLint hasLinked;
    glGetProgramiv(ID, GL_LINK_STATUS, &hasLinked);
    if (hasLinked == GL_FALSE)
    {
        char infoLog[1024];
        glGetProgramInfoLog(ID, 1024, NULL, infoLog);
        std::cout << "Shader Program Linking Failed:\n"
                  << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Delete()
{
    glDeleteProgram(ID);
}