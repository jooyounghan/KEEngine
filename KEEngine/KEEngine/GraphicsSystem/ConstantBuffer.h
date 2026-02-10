#pragma once
#include "GPUResource.h"

namespace ke
{
	// ============================================================================
	// ConstantBuffer - Upload-heap buffer for constant data (CBV)
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

	public:
		inline const DescriptorHandle& getDescriptorHandle() const { return _descriptorHandle; }
		inline uint32 getBindlessIndex() const { return _descriptorHandle.heapIndex; }
		inline uint32 getBufferSize() const { return _bufferSize; }

	private:
		DescriptorHeap*		_ownerHeap = nullptr;
		DescriptorHandle	_descriptorHandle;
		uint32				_bufferSize = 0;
	};
}
