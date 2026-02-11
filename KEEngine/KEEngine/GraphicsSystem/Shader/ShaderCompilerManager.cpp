#include "GraphicsSystemPch.h"
#include "ShaderCompilerManager.h"
#include "Pipeline/VertexShader.h"
#include "Pipeline/PixelShader.h"
#include "Pipeline/GeometryShader.h"
#include "Pipeline/DomainShader.h"
#include "Pipeline/HullShader.h"
#include "Pipeline/ComputeShader.h"

namespace ke
{
	ShaderCompilerManager::ShaderCompilerManager()
	{
	}

	ShaderCompilerManager::~ShaderCompilerManager()
	{
	}

	bool ShaderCompilerManager::initialize()
	{
		HRESULT hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&_dxcUtils));
		if (FAILED(hr))
		{
			return false;
		}

		hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&_dxcCompiler));
		if (FAILED(hr))
		{
			return false;
		}

		hr = _dxcUtils->CreateDefaultIncludeHandler(&_includeHandler);
		if (FAILED(hr))
		{
			return false;
		}

		return true;
	}

	bool ShaderCompilerManager::compileShader(
		const IBuffer* shaderSource,
		VertexShader* outShader)
	{
		if (!shaderSource || !outShader)
			return false;

		const std::string entryPoint = outShader->_entryPoint.toString();
		const std::string targetProfile = outShader->_targetProfile.toString();

		// Convert to wide strings
		std::wstring wEntryPoint(entryPoint.begin(), entryPoint.end());
		std::wstring wTargetProfile(targetProfile.begin(), targetProfile.end());

		void* bytecode = nullptr;
		size_t bytecodeSize = 0;

		if (!compileShaderInternal(shaderSource, wEntryPoint.c_str(), wTargetProfile.c_str(), &bytecode, &bytecodeSize))
		{
			return false;
		}

		outShader->_compiledBytecode.resize(bytecodeSize);
		memcpy(outShader->_compiledBytecode.data(), bytecode, bytecodeSize);

		return true;
	}

	bool ShaderCompilerManager::compileShader(
		const IBuffer* shaderSource,
		PixelShader* outShader)
	{
		if (!shaderSource || !outShader)
			return false;

		const std::string entryPoint = outShader->_entryPoint.toString();
		const std::string targetProfile = outShader->_targetProfile.toString();

		std::wstring wEntryPoint(entryPoint.begin(), entryPoint.end());
		std::wstring wTargetProfile(targetProfile.begin(), targetProfile.end());

		void* bytecode = nullptr;
		size_t bytecodeSize = 0;

		if (!compileShaderInternal(shaderSource, wEntryPoint.c_str(), wTargetProfile.c_str(), &bytecode, &bytecodeSize))
		{
			return false;
		}

		outShader->_compiledBytecode.resize(bytecodeSize);
		memcpy(outShader->_compiledBytecode.data(), bytecode, bytecodeSize);

		return true;
	}

	bool ShaderCompilerManager::compileShader(
		const IBuffer* shaderSource,
		GeometryShader* outShader)
	{
		if (!shaderSource || !outShader)
			return false;

		const std::string entryPoint = outShader->_entryPoint.toString();
		const std::string targetProfile = outShader->_targetProfile.toString();

		std::wstring wEntryPoint(entryPoint.begin(), entryPoint.end());
		std::wstring wTargetProfile(targetProfile.begin(), targetProfile.end());

		void* bytecode = nullptr;
		size_t bytecodeSize = 0;

		if (!compileShaderInternal(shaderSource, wEntryPoint.c_str(), wTargetProfile.c_str(), &bytecode, &bytecodeSize))
		{
			return false;
		}

		outShader->_compiledBytecode.resize(bytecodeSize);
		memcpy(outShader->_compiledBytecode.data(), bytecode, bytecodeSize);

		return true;
	}

	bool ShaderCompilerManager::compileShader(
		const IBuffer* shaderSource,
		DomainShader* outShader)
	{
		if (!shaderSource || !outShader)
			return false;

		const std::string entryPoint = outShader->_entryPoint.toString();
		const std::string targetProfile = outShader->_targetProfile.toString();

		std::wstring wEntryPoint(entryPoint.begin(), entryPoint.end());
		std::wstring wTargetProfile(targetProfile.begin(), targetProfile.end());

		void* bytecode = nullptr;
		size_t bytecodeSize = 0;

		if (!compileShaderInternal(shaderSource, wEntryPoint.c_str(), wTargetProfile.c_str(), &bytecode, &bytecodeSize))
		{
			return false;
		}

		outShader->_compiledBytecode.resize(bytecodeSize);
		memcpy(outShader->_compiledBytecode.data(), bytecode, bytecodeSize);

		return true;
	}

	bool ShaderCompilerManager::compileShader(
		const IBuffer* shaderSource,
		HullShader* outShader)
	{
		if (!shaderSource || !outShader)
			return false;

		const std::string entryPoint = outShader->_entryPoint.toString();
		const std::string targetProfile = outShader->_targetProfile.toString();

		std::wstring wEntryPoint(entryPoint.begin(), entryPoint.end());
		std::wstring wTargetProfile(targetProfile.begin(), targetProfile.end());

		void* bytecode = nullptr;
		size_t bytecodeSize = 0;

		if (!compileShaderInternal(shaderSource, wEntryPoint.c_str(), wTargetProfile.c_str(), &bytecode, &bytecodeSize))
		{
			return false;
		}

		outShader->_compiledBytecode.resize(bytecodeSize);
		memcpy(outShader->_compiledBytecode.data(), bytecode, bytecodeSize);

		return true;
	}

	bool ShaderCompilerManager::compileShader(
		const IBuffer* shaderSource,
		ComputeShader* outShader)
	{
		if (!shaderSource || !outShader)
			return false;

		const std::string entryPoint = outShader->_entryPoint.toString();
		const std::string targetProfile = outShader->_targetProfile.toString();

		std::wstring wEntryPoint(entryPoint.begin(), entryPoint.end());
		std::wstring wTargetProfile(targetProfile.begin(), targetProfile.end());

		void* bytecode = nullptr;
		size_t bytecodeSize = 0;

		if (!compileShaderInternal(shaderSource, wEntryPoint.c_str(), wTargetProfile.c_str(), &bytecode, &bytecodeSize))
		{
			return false;
		}

		outShader->_compiledBytecode.resize(bytecodeSize);
		memcpy(outShader->_compiledBytecode.data(), bytecode, bytecodeSize);

		return true;
	}

	bool ShaderCompilerManager::compileShaderInternal(
		const IBuffer* shaderSource,
		const wchar_t* entryPoint,
		const wchar_t* targetProfile,
		void** outBytecode,
		size_t* outBytecodeSize)
	{
		if (!shaderSource || !entryPoint || !targetProfile || !outBytecode || !outBytecodeSize)
			return false;

		// Create source buffer
		DxcBuffer sourceBuffer = {};
		sourceBuffer.Ptr = shaderSource->getConstBuffer();
		sourceBuffer.Size = shaderSource->getCursorPos();
		sourceBuffer.Encoding = DXC_CP_ACP;

		// Compile arguments
		std::vector<LPCWSTR> arguments = {
			L"-E", entryPoint,
			L"-T", targetProfile,
			L"-Zi",           // Debug info
			L"-Od",           // Disable optimizations (for debug)
			L"-Qembed_debug", // Embed debug info
		};

		// Compile the shader
		Microsoft::WRL::ComPtr<IDxcResult> result;
		HRESULT hr = _dxcCompiler->Compile(
			&sourceBuffer,
			arguments.data(),
			static_cast<UINT32>(arguments.size()),
			_includeHandler.Get(),
			IID_PPV_ARGS(&result)
		);

		if (FAILED(hr))
		{
			return false;
		}

		// Check compilation status
		HRESULT compileStatus;
		result->GetStatus(&compileStatus);

		if (FAILED(compileStatus))
		{
			// Get error messages
			Microsoft::WRL::ComPtr<IDxcBlobUtf8> errors;
			result->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&errors), nullptr);
			if (errors && errors->GetStringLength() > 0)
			{
				// Could output error messages here
				// For now, just return false
			}
			return false;
		}

		// Get compiled shader bytecode
		Microsoft::WRL::ComPtr<IDxcBlob> shaderBlob;
		result->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);

		if (!shaderBlob)
		{
			return false;
		}

		*outBytecode = shaderBlob->GetBufferPointer();
		*outBytecodeSize = shaderBlob->GetBufferSize();

		return true;
	}
}
