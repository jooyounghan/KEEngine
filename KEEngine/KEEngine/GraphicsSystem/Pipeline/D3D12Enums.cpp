#include "GraphicsSystemPch.h"
#include "D3D12Enums.h"
#include "EnumUtil.h"

namespace ke
{
	DEFINE_ENUM_DESCRIPTOR(EBlend,
		Zero, One,
		SrcColor, InvSrcColor,
		SrcAlpha, InvSrcAlpha,
		DestAlpha, InvDestAlpha,
		DestColor, InvDestColor,
		SrcAlphaSat,
		BlendFactor, InvBlendFactor,
		Src1Color, InvSrc1Color,
		Src1Alpha, InvSrc1Alpha,
		AlphaFactor, InvAlphaFactor
	);

	DEFINE_ENUM_DESCRIPTOR(EBlendOp,
		Add, Subtract, RevSubtract, Min, Max
	);

	DEFINE_ENUM_DESCRIPTOR(EDepthWriteMask,
		Zero, All
	);

	DEFINE_ENUM_DESCRIPTOR(EComparisonFunc,
		Never, Less, Equal, LessEqual, Greater, NotEqual, GreaterEqual, Always
	);

	DEFINE_ENUM_DESCRIPTOR(EFillMode,
		Wireframe, Solid
	);

	DEFINE_ENUM_DESCRIPTOR(ECullMode,
		None, Front, Back
	);

	DEFINE_ENUM_DESCRIPTOR(EConservativeRasterizationMode,
		Off, On
	);

	DEFINE_ENUM_DESCRIPTOR(EStencilOp,
		Keep, Zero, Replace, IncrSat, DecrSat, Invert, Incr, Decr
	);

	DEFINE_ENUM_DESCRIPTOR(EDxgiFormat,
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

	DEFINE_ENUM_DESCRIPTOR(EInputClassification,
		PerVertexData, PerInstanceData
	);

	DEFINE_ENUM_DESCRIPTOR(EPrimitiveTopologyType,
		Undefined, Point, Line, Triangle, Patch
	);
}
