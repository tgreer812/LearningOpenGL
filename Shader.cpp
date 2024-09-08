#include "Shader.h"


Shader::~Shader() {
    if (programID != 0) {
        glDeleteProgram(programID);        
    }
}

bool Shader::LoadShaderSource(const std::string& vertexSource, const std::string& fragmentSource) {
    vertexSourceCode = vertexSource;
    fragmentSourceCode = fragmentSource;
    return true;
}

bool Shader::LoadShaderFiles(const std::string& vertexFilePath, const std::string& fragmentFilePath) {
    vertexSourceCode = ReadFile(vertexFilePath);
    fragmentSourceCode = ReadFile(fragmentFilePath);
    return !vertexSourceCode.empty() && !fragmentSourceCode.empty();
}

std::string Shader::ReadFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool Shader::Compile() {
    if (vertexSourceCode.empty() || fragmentSourceCode.empty()) {
        std::cerr << "Error: Shader source code is empty. Please load shader source." << std::endl;
        return false;
    }

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSourceCStr = vertexSourceCode.c_str();
    glShaderSource(vertexShader, 1, &vertexSourceCStr, nullptr);
    glCompileShader(vertexShader);
    if (!CheckShaderCompileStatus(vertexShader)) {
        glDeleteShader(vertexShader);
        return false;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSourceCStr = fragmentSourceCode.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourceCStr, nullptr);
    glCompileShader(fragmentShader);
    if (!CheckShaderCompileStatus(fragmentShader)) {
        glDeleteShader(fragmentShader);
        glDeleteShader(vertexShader);
        return false;
    }

    programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);

    PreLink();

    glLinkProgram(programID);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (!CheckProgramLinkStatus(programID)) {
        return false;
    }

    PostLink();
    return true;
}

void Shader::Bind() {
    // If the program hasn't been created yet, attempt to compile and link the shader
    if (!isCompiled) {
        if (!Compile()) {
            std::cerr << "Error: Failed to compile and link shaders during Bind." << std::endl;
            return;
        }
        isCompiled = true;  // Mark the shader as successfully compiled and linked
    }

    // Bind the shader program
    glUseProgram(programID);
}

void Shader::Unbind() {
    glUseProgram(0);
}

void Shader::SetUniform(const std::string& name, int value) {
    glUniform1i(glGetUniformLocation(this->programID, name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, float value) {
    glUniform1f(glGetUniformLocation(this->programID, name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, const glm::vec3& value) {
    glUniform3fv(glGetUniformLocation(this->programID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& name, const glm::vec4& value) {
    glUniform4fv(glGetUniformLocation(this->programID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& name, const glm::mat4& value) {
    // stands for 4x4 matrix float vector
    glUniformMatrix4fv(
        glGetUniformLocation(this->programID, name.c_str()),
        1,
        GL_FALSE,
        glm::value_ptr(value)
    );
}

bool Shader::CheckShaderCompileStatus(GLuint shaderID) {
    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint maxLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> errorLog(maxLength);
        glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);
        std::cerr << "Shader Compilation Error: " << std::string(errorLog.begin(), errorLog.end()) << std::endl;
        return false;
    }
    return true;
}

bool Shader::CheckProgramLinkStatus(GLuint programID) {
    GLint success;
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success) {
        GLint maxLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<char> errorLog(maxLength);
        glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]);
        std::cerr << "Shader Linking Error: " << std::string(errorLog.begin(), errorLog.end()) << std::endl;
        return false;
    }
    return true;
}

std::string Shader::GetErrorLog() const {
    if (programID == 0) {
        return "No program has been created.";
    }

    GLint logLength = 0;
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        std::vector<char> errorLog(logLength);
        glGetProgramInfoLog(programID, logLength, nullptr, errorLog.data());
        return std::string(errorLog.begin(), errorLog.end());
    }

    return "No errors.";
}

