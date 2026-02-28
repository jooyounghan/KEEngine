#include "GraphicsSystemPch.h"
#include "D3D12Enums.h"

namespace ke
{
	KE_DEFINE_REFLECT_ENUM(EBlend,
		Zero, One,
		SrcColor, InvSrcColor,
		SrcAlpha, InvSrcAlpha,
		DestAlpha, InvDestAlpha,
		DestColor, InvDestColor
	);

	KE_DEFINE_REFLECT_ENUM(EBlendOp,
		Add, Subtract, RevSubtract, Min, Max
	);

	KE_DEFINE_REFLECT_ENUM_FLAG(EBlendColorMask,
		Red, Green, Blue, Alpha
	);

	KE_DEFINE_REFLECT_ENUM(EDepthWriteMask,
		Zero, All
	);

	KE_DEFINE_REFLECT_ENUM(EComparisonFunc,
		Never, Less, Equal, LessEqual, Greater, NotEqual, GreaterEqual, Always
	);

	KE_DEFINE_REFLECT_ENUM(EFillMode,
		Wireframe, Solid
	);

	KE_DEFINE_REFLECT_ENUM(ECullMode,
		None, Front, Back
	);

	KE_DEFINE_REFLECT_ENUM(EConservativeRasterizationMode,
		Off, On
	);

	KE_DEFINE_REFLECT_ENUM(EStencilOp,
		Keep, Zero, Replace, IncrSat, DecrSat, Invert, Incr, Decr
	);

	KE_DEFINE_REFLECT_ENUM(EDXGIFormat,
		Unknown,
		R32G32B32A32_Typeless, R32G32B32A32_Float, R32G32B32A32_Uint, R32G32B32A32_Sint,
		R32G32B32_Typeless, R32G32B32_Float, R32G32B32_Uint, R32G32B32_Sint,
		R16G16B16A16_Typeless, R16G16B16A16_Float, R16G16B16A16_Unorm, R16G16B16A16_Uint, R16G16B16A16_Snorm, R16G16B16A16_Sint,
		R32G32_Typeless, R32G32_Float, R32G32_Uint, R32G32_Sint,
		R10G10B10A2_Typeless, R10G10B10A2_Unorm, R10G10B10A2_Uint, R11G11B10_Float,
		R8G8B8A8_Typeless, R8G8B8A8_Unorm, R8G8B8A8_Unorm_Srgb, R8G8B8A8_Uint, R8G8B8A8_Snorm, R8G8B8A8_Sint,
		R16G16_Typeless, R16G16_Float, R16G16_Unorm, R16G16_Uint, R16G16_Snorm, R16G16_Sint,
		R32_Typeless, D32_Float, R32_Float, R32_Uint, R32_Sint,
		D24_Unorm_S8_Uint,
		R8G8_Typeless, R8G8_Unorm, R8G8_Uint, R8G8_Snorm, R8G8_Sint,
		R16_Typeless, R16_Float, D16_Unorm, R16_Unorm, R16_Uint, R16_Snorm, R16_Sint,
		R8_Typeless, R8_Unorm, R8_Uint, R8_Snorm, R8_Sint, A8_Unorm,
		B8G8R8A8_Unorm, B8G8R8X8_Unorm, B8G8R8A8_Typeless, B8G8R8A8_Unorm_Srgb
	);

	KE_DEFINE_REFLECT_ENUM(EInputClassification,
		PerVertexData, PerInstanceData
	);

	KE_DEFINE_REFLECT_ENUM(EPrimitiveTopologyType,
		Undefined, Point, Line, Triangle, Patch
	);
}
