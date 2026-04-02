#pragma once
#include <string>
#include "RendererCommons.h"

struct ShaderInfo
{

	std::string vertexShaderEntry = "Main";
	std::string vertexShaderPath;
	std::string fragmentShaderEntry = "Main";
	std::string fragmentShaderPath;
	std::string computeShaderSource;
	ShaderLanguage shaderLanguage = ShaderLanguage::SPIRV;
};