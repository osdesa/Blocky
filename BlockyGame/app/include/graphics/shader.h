#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include "math/BMath.h"

namespace Blocky {
	class Shader
	{
	private:
		uint32_t id = 0;
		const char* vertexPath = "";
		const char* fragmentPath = "";

		std::unordered_map<const char*, int> uniformLocationCache;

		uint32_t GetUniformLocation(const char* name);
		uint32_t CompileShader(const std::string& source, uint32_t type);
		std::string ReadShader(const char* path);
		uint32_t CreateShader(std::string& vertexShader, std::string& fragmentShader);

	public:
		Shader() : id(0) {}
		~Shader();

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		Shader(Shader&& rhs) noexcept
		{
			std::swap(id, rhs.id);
		}

		Shader& operator=(Shader&& rhs) noexcept {
			std::swap(id, rhs.id);
			return *this;
		}

		void Create(const char* vPath, const char* fPath);

		void Bind();
		void UnBind();

		uint32_t GetId() { return id; }
		// Set uniforms
		// sends data to GPU
		void SetUniform1f(const char* name, float value);
		void SetUniform1i(const char* name, int value);
		void SetUniform3f(const char* name, float f0, float f1, float f2);
		void SetUniform4f(const char* name, float f0, float f1, float f2, float f3);
		void SetMatrix4(const char* name, Matrix4x4 mat);
	};
};