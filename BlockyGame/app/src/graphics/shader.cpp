#include "graphics/shader.h"
#include "glad/glad.h"
#include <sstream>
#include <fstream>
#include "logger.h"

namespace Blocky {
	void Shader::Create(const char* vPath, const char* fPath)
	{
		vertexPath = vPath; fragmentPath = fPath; id = 0;

		// Gets the characters from the verte shader file
		std::string vCode = ReadShader(vPath);
		// Gets the characters from the fragment shder file
		std::string fCode = ReadShader(fPath);
		// Creates the shader and stores the handle
		id = CreateShader(vCode, fCode);
	}

	Shader::~Shader()
	{
		glDeleteProgram(id);
	}

	uint32_t Shader::GetUniformLocation(const char* name)
	{
		// Checks to see if the name is in the map
		// if it is then that is a cache hit and it returns at the position
		if (uniformLocationCache.find(name) != uniformLocationCache.end())
			return uniformLocationCache[name];

		// if it is not in the map get the location
		int location = glGetUniformLocation(id, name);

		if (location == -1) {
			Logger::output(FATAL, "Failed to find uniform %s", name);
		}
		else {
			// cache the location in the map
			uniformLocationCache[name] = location;
		}
		return location;
	}

	std::string Shader::ReadShader(const char* path)
	{
		// creates a stream to read the file
		std::fstream stream(path);

		std::string line;
		std::stringstream data;
		// loops through the file line by line
		while (getline(stream, line)) {
			// push the line and a new line char to the data buffer
			data << line << '\n';
		}
		return data.str();
	}

	uint32_t Shader::CreateShader(std::string& vertexShader, std::string& fragmentShader)
	{
		// Creates a program which is a small amount of memory on the cpu which can be ran
		uint32_t program = glCreateProgram();
		// Compiles the vertex shader
		uint32_t vs = CompileShader(vertexShader.c_str(), GL_VERTEX_SHADER);
		// Compiles the fragment shader
		uint32_t fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

		// attachs the shaders to the program giving it instructions on what to excute
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		// links the program puting into useable form on the gpu
		glLinkProgram(program);
		// Makes sure there were no error in the program
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	uint32_t Shader::CompileShader(const std::string& source, uint32_t type)
	{
		// Creates a shader handle
		uint32_t id = glCreateShader(type);
		const char* src = source.c_str();
		// sets the source code of the shader and tells openGL to prepare it on our shader id
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		// Gets the result of compileing the shader
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		// if there was an error
		if (result == GL_FALSE) {
			// Gets the length if error message and allocates that much memory for c style string
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)malloc(length * sizeof(char));

			// Gets the error from openGL
			glGetShaderInfoLog(id, length, &length, message);
			Logger::output(FATAL, "Failed to compile shader %s source %s", message, source.c_str());
			return 0;
		}

		return id;
	}

	void Shader::Bind()
	{
		glUseProgram(id);
	}

	void Shader::UnBind()
	{
		glUseProgram(0);
	}

	/// <summary>
	/// All the functions bellow handle sending data to the gpu in differant forms
	/// these methods need to know the location so perform a cache check
	/// they then send this infomation in the set form
	/// </summary>

	void Shader::SetUniform1f(const char* name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetUniform1i(const char* name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform3f(const char* name, float f0, float f1, float f2)
	{
		glUniform3f(GetUniformLocation(name), f0, f1, f2);
	}

	void Shader::SetUniform4f(const char* name, float f0, float f1, float f2, float f3)
	{
		glUniform4f(GetUniformLocation(name), f0, f1, f2, f3);
	}

	void Shader::SetMatrix4(const char* name, Matrix4x4 mat)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, mat.v);
	}
}