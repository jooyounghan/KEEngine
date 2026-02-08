#include "GraphicsSystemPch.h"
#include "BindlessDescriptorHeap.h"

namespace ke
{
	void BindlessDescriptorHeap::init(ID3D12Device* device, uint32_t maxDescriptors)
	{
		_heap.init(device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, maxDescriptors, true);
	}

	DescriptorHandle BindlessDescriptorHeap::allocate()
	{
		return _heap.allocate();
	}

	void BindlessDescriptorHeap::release(const DescriptorHandle& handle)
	{
		_heap.release(handle);
	}

	DescriptorHandle BindlessDescriptorHeap::copyDescriptor(
		ID3D12Device* device,
		const DescriptorHandle& srcHandle)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(srcHandle.isValid(), "Source descriptor handle must be valid.");

		DescriptorHandle dstHandle = _heap.allocate();

		device->CopyDescriptorsSimple(
			1,
			dstHandle.cpuHandle,
			srcHandle.cpuHandle,
			D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

		return dstHandle;
	}
}
