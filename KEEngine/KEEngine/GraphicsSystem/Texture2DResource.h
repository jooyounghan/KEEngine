#pragma once
#include "GPUResource.h"

namespace ke
{
	// ============================================================================
	// Texture2DResource - 2D texture with SRV support and staging upload
	//
	// Creates a DEFAULT-heap 2D texture with an optional SRV descriptor.
	// Internally maintains an UPLOAD-heap staging buffer for CPU data upload.
	// Call upload() to write pixel data to the staging buffer, then
	// commitUpload() to copy it to the DEFAULT-heap texture.
	// ============================================================================
	class Texture2DResource : public GPUResource
	{
	public:
		Texture2DResource() = default;
		~Texture2DResource() override;
		NONCOPYABLE(Texture2DResource);

	public:
		void initialize(
			ID3D12Device* device,
			uint32 width,
			uint32 height,
			DXGI_FORMAT format,
			DescriptorHeap* srvHeap = nullptr,
			uint16 mipLevels = 1);
		void shutdown();

	public:
		void upload(const void* data, uint32 size);
		void commitUpload(ID3D12GraphicsCommandList* commandList);

	public:
		inline uint32 getWidth() const { return _width; }
		inline uint32 getHeight() const { return _height; }
		inline DXGI_FORMAT getFormat() const { return _format; }
		inline uint16 getMipLevels() const { return _mipLevels; }

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> _stagingResource;
		uint32		_width = 0;
		uint32		_height = 0;
		DXGI_FORMAT	_format = DXGI_FORMAT_UNKNOWN;
		uint16		_mipLevels = 1;
		uint32		_rowPitch = 0;
		uint64		_stagingSize = 0;
	};
}
