#pragma once
#include "GPUResource.h"

namespace ke
{
	// ============================================================================
	// StructuredBuffer - Buffer of structured elements with SRV support
	//
	// When cpuWritable is true, the buffer is created on an upload heap and
	// supports map/unmap for CPU-side writes.
	// When cpuWritable is false, the buffer is created on a default heap
	// (GPU-only); use a CopyCommandContext to upload data.
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
			bool cpuWritable = false,
			DescriptorHeap* srvHeap = nullptr);
		void shutdown();

	public:
		void upload(const void* data, uint32 size);

	public:
		inline const DescriptorHandle& getSRVHandle() const { return _srvHandle; }
		inline uint32 getBindlessIndex() const { return _srvHandle.heapIndex; }
		inline uint32 getElementCount() const { return _elementCount; }
		inline uint32 getElementSize() const { return _elementSize; }
		inline uint32 getBufferSize() const { return _elementCount * _elementSize; }
		inline bool isCPUWritable() const { return _cpuWritable; }

	private:
		DescriptorHeap*		_ownerHeap = nullptr;
		DescriptorHandle	_srvHandle;
		uint32				_elementCount = 0;
		uint32				_elementSize = 0;
		bool				_cpuWritable = false;
	};
}
