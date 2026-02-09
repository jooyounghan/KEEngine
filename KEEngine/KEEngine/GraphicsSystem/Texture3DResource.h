#pragma once
#include "GPUResource.h"

namespace ke
{
	class CopyCommandContext;

	// ============================================================================
	// Texture3DResource - 3D (volume) texture with SRV support and staging upload
	//
	// Creates a DEFAULT-heap 3D texture with an optional SRV descriptor.
	// Internally maintains an UPLOAD-heap staging buffer for CPU data upload.
	// Call upload() to write voxel data to the staging buffer, then
	// commitUpload() to copy it to the DEFAULT-heap texture.
	// ============================================================================
	class Texture3DResource : public GPUResource
	{
	public:
		Texture3DResource() = default;
		~Texture3DResource() override;
		NONCOPYABLE(Texture3DResource);

	public:
		void initialize(
			ID3D12Device* device,
			uint32 width,
			uint32 height,
			uint16 depth,
			DXGI_FORMAT format,
			DescriptorHeap* srvHeap = nullptr,
			uint16 mipLevels = 1);
		void shutdown();

	public:
		void upload(const void* data, uint32 size);
		void commitUpload(CopyCommandContext& copyCtx);

	public:
		inline uint32 getWidth() const { return _width; }
		inline uint32 getHeight() const { return _height; }
		inline uint16 getDepth() const { return _depth; }
		inline DXGI_FORMAT getFormat() const { return _format; }
		inline uint16 getMipLevels() const { return _mipLevels; }

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> _stagingResource;
		uint32		_width = 0;
		uint32		_height = 0;
		uint16		_depth = 0;
		DXGI_FORMAT	_format = DXGI_FORMAT_UNKNOWN;
		uint16		_mipLevels = 1;
		uint32		_rowPitch = 0;
		uint32		_slicePitch = 0;
	};
}
