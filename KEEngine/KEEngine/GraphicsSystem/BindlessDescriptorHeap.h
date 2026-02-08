#pragma once
#include "DescriptorHeap.h"

namespace ke
{
	class BindlessDescriptorHeap
	{
	public:
		BindlessDescriptorHeap() = default;
		~BindlessDescriptorHeap() = default;

	public:
		void init(ID3D12Device* device, uint32_t maxDescriptors);

		DescriptorHandle allocate();
		void release(const DescriptorHandle& handle);

	public:
		DescriptorHandle copyDescriptor(
			ID3D12Device* device,
			const DescriptorHandle& srcHandle);

	public:
		inline uint32_t getBindlessIndex(const DescriptorHandle& handle) const { return handle.heapIndex; }
		inline ID3D12DescriptorHeap* getHeap() const { return _heap.getHeap(); }
		inline uint32_t getNumFreeDescriptors() const { return _heap.getNumFreeDescriptors(); }

	private:
		DescriptorHeap _heap;
	};
}
