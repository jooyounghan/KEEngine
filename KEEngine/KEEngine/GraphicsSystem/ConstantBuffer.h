#pragma once
#include "GPUResource.h"

namespace ke
{
	class CopyCommandContext;

	// ============================================================================
	// ConstantBuffer - Default-heap buffer for constant data (CBV) with staging
	//
	// Internally maintains an UPLOAD-heap staging buffer. Call upload() to write
	// CPU data into the staging buffer, then commitUpload() to copy it to the
	// DEFAULT-heap resource that is exposed externally.
	//
	// If a DescriptorHeap is provided during initialization, a CBV descriptor
	// is allocated for bindless access via getBindlessIndex().
	// ============================================================================
	class ConstantBuffer : public GPUResource
	{
	public:
		ConstantBuffer() = default;
		~ConstantBuffer() override;
		NONCOPYABLE(ConstantBuffer);

	public:
		void initialize(ID3D12Device* device, uint32 bufferSize, DescriptorHeap* cbvHeap = nullptr);
		void shutdown();

	public:
		void upload(const void* data, uint32 size);
		void commitUpload(CopyCommandContext& copyCtx);

	public:
		inline uint32 getBufferSize() const { return _bufferSize; }

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> _stagingResource;
		uint32 _bufferSize = 0;
	};
}
