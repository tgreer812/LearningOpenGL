#include "Shader.h"
#include "Utils.h"

Shader::~Shader() {
    if (programID != 0) {
        GL_CALL(glDeleteProgram(programID));
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

    GLuint vertexShader;
    GL_CALL(vertexShader = glCreateShader(GL_VERTEX_SHADER));
    const char* vertexSourceCStr = vertexSourceCode.c_str();
    GL_CALL(glShaderSource(vertexShader, 1, &vertexSourceCStr, nullptr));
    GL_CALL(glCompileShader(vertexShader));
    if (!CheckShaderCompileStatus(vertexShader)) {
        GL_CALL(glDeleteShader(vertexShader));
        return false;
    }

    GLuint fragmentShader;
    GL_CALL(fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
    const char* fragmentSourceCStr = fragmentSourceCode.c_str();
    GL_CALL(glShaderSource(fragmentShader, 1, &fragmentSourceCStr, nullptr));
    GL_CALL(glCompileShader(fragmentShader));
    if (!CheckShaderCompileStatus(fragmentShader)) {
        GL_CALL(glDeleteShader(fragmentShader));
        GL_CALL(glDeleteShader(vertexShader));
        return false;
    }

    GL_CALL(programID = glCreateProgram());
    GL_CALL(glAttachShader(programID, vertexShader));
    GL_CALL(glAttachShader(programID, fragmentShader));

    PreLink();

    GL_CALL(glLinkProgram(programID));
    GL_CALL(glDeleteShader(vertexShader));
    GL_CALL(glDeleteShader(fragmentShader));

    if (!CheckProgramLinkStatus(programID)) {
        return false;
    }

    PostLink();
    return true;
}

void Shader::Bind() {
    if (!isCompiled) {
        if (!Compile()) {
            std::cerr << "Error: Failed to compile and link shaders during Bind." << std::endl;
            return;
        }
        isCompiled = true;
    }

    GL_CALL(glUseProgram(programID));
}

void Shader::Unbind() {
    GL_CALL(glUseProgram(0));
}

void Shader::SetBool(const std::string& name, bool value) {
    GL_CALL(glUniform1i(glGetUniformLocation(this->programID, name.c_str()), value));
}

void Shader::SetInt(const std::string& name, int value) {
    GL_CALL(glUniform1i(glGetUniformLocation(this->programID, name.c_str()), value));
}

void Shader::SetFloat(const std::string& name, float value) {
    GL_CALL(glUniform1f(glGetUniformLocation(this->programID, name.c_str()), value));
}

void Shader::SetFloat3(const std::string& name, const glm::vec3& value) {
    GL_CALL(glUniform3fv(glGetUniformLocation(this->programID, name.c_str()), 1, glm::value_ptr(value)));
}

void Shader::SetFloat4(const std::string& name, const glm::vec4& value) {
    GL_CALL(glUniform4fv(glGetUniformLocation(this->programID, name.c_str()), 1, glm::value_ptr(value)));
}

void Shader::SetMat3(const std::string& name, const glm::mat3& value) {
    GL_CALL(glUniformMatrix3fv(
        glGetUniformLocation(this->programID, name.c_str()),
        1,
        GL_FALSE,
        glm::value_ptr(value)
    ));
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value) {
    GL_CALL(glUniformMatrix4fv(
        glGetUniformLocation(this->programID, name.c_str()),
        1,
        GL_FALSE,
        glm::value_ptr(value)
    ));
}

bool Shader::CheckShaderCompileStatus(GLuint shaderID) {
    GLint success;
    GL_CALL(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success));
    if (!success) {
        GLint maxLength = 0;
        GL_CALL(glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength));
        std::vector<char> errorLog(maxLength);
        GL_CALL(glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]));
        std::cerr << "Shader Compilation Error: " << std::string(errorLog.begin(), errorLog.end()) << std::endl;
        return false;
    }
    return true;
}

bool Shader::CheckProgramLinkStatus(GLuint programID) {
    GLint success;
    GL_CALL(glGetProgramiv(programID, GL_LINK_STATUS, &success));
    if (!success) {
        GLint maxLength = 0;
        GL_CALL(glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength));
        std::vector<char> errorLog(maxLength);
        GL_CALL(glGetProgramInfoLog(programID, maxLength, &maxLength, &errorLog[0]));
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
    GL_CALL(glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength));

    if (logLength > 0) {
        std::vector<char> errorLog(logLength);
        GL_CALL(glGetProgramInfoLog(programID, logLength, nullptr, errorLog.data()));
        return std::string(errorLog.begin(), errorLog.end());
    }

    return "No errors.";
}