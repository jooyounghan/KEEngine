#pragma once
#include "GPUResource.h"

namespace ke
{
	class CopyCommandContext;

	// ============================================================================
	// StructuredBuffer - Buffer of structured elements with SRV support
	//
	// Internally maintains an UPLOAD-heap staging buffer. Call upload() to write
	// CPU data into the staging buffer, then commitUpload() to copy it to the
	// DEFAULT-heap resource that is exposed externally via the SRV.
	//
	// If a DescriptorHeap is provided, an SRV is created for bindless access.
	// ============================================================================
	class StructuredBuffer : public GPUResource
	{
	public:
		StructuredBuffer() = default;
		~StructuredBuffer() override;
		NONCOPYABLE(StructuredBuffer);

	public:
		void initialize(
			ID3D12Device* device,
			uint32 elementCount,
			uint32 elementSize,
			DescriptorHeap* srvHeap = nullptr);
		void shutdown();

	public:
		void upload(const void* data, uint32 size);
		void commitUpload(CopyCommandContext& copyCtx);

	public:
		inline uint32 getElementCount() const { return _elementCount; }
		inline uint32 getElementSize() const { return _elementSize; }
		inline uint32 getBufferSize() const { return _elementCount * _elementSize; }

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> _stagingResource;
		uint32 _elementCount = 0;
		uint32 _elementSize = 0;
	};
}
