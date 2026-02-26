#pragma once
#include "TypeCommon.h"

namespace ke
{
	enum class EBlend : uint8
	{
		Zero			= 1,
		One				= 2,
		SrcColor		= 3,
		InvSrcColor		= 4,
		SrcAlpha		= 5,
		InvSrcAlpha		= 6,
		DestAlpha		= 7,
		InvDestAlpha	= 8,
		DestColor		= 9,
		InvDestColor	= 10,
		SrcAlphaSat		= 11,
		BlendFactor		= 14,
		InvBlendFactor	= 15,
		Src1Color		= 16,
		InvSrc1Color	= 17,
		Src1Alpha		= 18,
		InvSrc1Alpha	= 19,
		AlphaFactor		= 20,
		InvAlphaFactor	= 21,
	};

	enum class EBlendOp : uint8
	{
		Add				= 1,
		Subtract		= 2,
		RevSubtract		= 3,
		Min				= 4,
		Max				= 5,
	};

	enum class EDepthWriteMask : uint8
	{
		Zero	= 0,
		All		= 1,
	};

	enum class EComparisonFunc : uint8
	{
		Never			= 1,
		Less			= 2,
		Equal			= 3,
		LessEqual		= 4,
		Greater			= 5,
		NotEqual		= 6,
		GreaterEqual	= 7,
		Always			= 8,
	};

	enum class EFillMode : uint8
	{
		Wireframe	= 2,
		Solid		= 3,
	};

	enum class ECullMode : uint8
	{
		None	= 1,
		Front	= 2,
		Back	= 3,
	};

	enum class EConservativeRasterizationMode : uint8
	{
		Off	= 0,
		On	= 1,
	};

	enum class EStencilOp : uint8
	{
		Keep		= 1,
		Zero		= 2,
		Replace		= 3,
		IncrSat		= 4,
		DecrSat		= 5,
		Invert		= 6,
		Incr		= 7,
		Decr		= 8,
	};

	enum class EDxgiFormat : uint8
	{
		Unknown						= 0,
		R32G32B32A32_Typeless		= 1,
		R32G32B32A32_Float			= 2,
		R32G32B32A32_Uint			= 3,
		R32G32B32A32_Sint			= 4,
		R32G32B32_Typeless			= 5,
		R32G32B32_Float				= 6,
		R32G32B32_Uint				= 7,
		R32G32B32_Sint				= 8,
		R16G16B16A16_Typeless		= 9,
		R16G16B16A16_Float			= 10,
		R16G16B16A16_Unorm			= 11,
		R16G16B16A16_Uint			= 12,
		R16G16B16A16_Snorm			= 13,
		R16G16B16A16_Sint			= 14,
		R32G32_Typeless				= 15,
		R32G32_Float				= 16,
		R32G32_Uint					= 17,
		R32G32_Sint					= 18,
		R10G10B10A2_Typeless		= 23,
		R10G10B10A2_Unorm			= 24,
		R10G10B10A2_Uint			= 25,
		R11G11B10_Float				= 26,
		R8G8B8A8_Typeless			= 27,
		R8G8B8A8_Unorm				= 28,
		R8G8B8A8_Unorm_Srgb			= 29,
		R8G8B8A8_Uint				= 30,
		R8G8B8A8_Snorm				= 31,
		R8G8B8A8_Sint				= 32,
		R16G16_Typeless				= 33,
		R16G16_Float				= 34,
		R16G16_Unorm				= 35,
		R16G16_Uint					= 36,
		R16G16_Snorm				= 37,
		R16G16_Sint					= 38,
		R32_Typeless				= 39,
		D32_Float					= 40,
		R32_Float					= 41,
		R32_Uint					= 42,
		R32_Sint					= 43,
		D24_Unorm_S8_Uint			= 45,
		R8G8_Typeless				= 48,
		R8G8_Unorm					= 49,
		R8G8_Uint					= 50,
		R8G8_Snorm					= 51,
		R8G8_Sint					= 52,
		R16_Typeless				= 53,
		R16_Float					= 54,
		D16_Unorm					= 55,
		R16_Unorm					= 56,
		R16_Uint					= 57,
		R16_Snorm					= 58,
		R16_Sint					= 59,
		R8_Typeless					= 60,
		R8_Unorm					= 61,
		R8_Uint						= 62,
		R8_Snorm					= 63,
		R8_Sint						= 64,
		A8_Unorm					= 65,
		B8G8R8A8_Unorm				= 87,
		B8G8R8X8_Unorm				= 88,
		B8G8R8A8_Typeless			= 90,
		B8G8R8A8_Unorm_Srgb			= 91,
	};

	enum class EInputClassification : uint8
	{
		PerVertexData	= 0,
		PerInstanceData	= 1,
	};

	enum class EPrimitiveTopologyType : uint8
	{
		Undefined	= 0,
		Point		= 1,
		Line		= 2,
		Triangle	= 3,
		Patch		= 4,
	};
}
