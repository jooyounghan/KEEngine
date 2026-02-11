#pragma once
#include "IBuffer.h"

namespace ke
{
	class VertexShader;
	class PixelShader;
	class GeometryShader;
	class DomainShader;
	class HullShader;
	class ComputeShader;

	class ShaderCompilerManager
	{
	public:
		ShaderCompilerManager();
		~ShaderCompilerManager();

	private:
		Microsoft::WRL::ComPtr<IDxcUtils> _dxcUtils;
		Microsoft::WRL::ComPtr<IDxcCompiler3> _dxcCompiler;
		Microsoft::WRL::ComPtr<IDxcIncludeHandler> _includeHandler;

	public:
		bool initialize();

	public:
		bool compileShader(
			const IBuffer* shaderSource,
			VertexShader* outShader
		);

		bool compileShader(
			const IBuffer* shaderSource,
			PixelShader* outShader
		);

		bool compileShader(
			const IBuffer* shaderSource,
			GeometryShader* outShader
		);

		bool compileShader(
			const IBuffer* shaderSource,
			DomainShader* outShader
		);

		bool compileShader(
			const IBuffer* shaderSource,
			HullShader* outShader
		);

		bool compileShader(
			const IBuffer* shaderSource,
			ComputeShader* outShader
		);

	private:
		bool compileShaderInternal(
			const IBuffer* shaderSource,
			const wchar_t* entryPoint,
			const wchar_t* targetProfile,
			Microsoft::WRL::ComPtr<IDxcBlob>& outBlob
		);
	};
}
