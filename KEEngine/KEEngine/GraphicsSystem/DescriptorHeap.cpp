#include "GraphicsSystemPch.h"
#include "DescriptorHeap.h"

namespace ke
{
	void DescriptorHeap::init(
		ID3D12Device* device,
		D3D12_DESCRIPTOR_HEAP_TYPE type,
		uint32_t numDescriptors,
		bool shaderVisible)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(numDescriptors > 0, "numDescriptors must be greater than 0.");

		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.NumDescriptors = numDescriptors;
		desc.Type = type;
		desc.Flags = shaderVisible
			? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE
			: D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

		KE_ASSERT(!FAILED(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&_heap))),
			"Failed to create descriptor heap.");

		_descriptorSize = device->GetDescriptorHandleIncrementSize(type);
		_numDescriptors = numDescriptors;
		_cpuStart = _heap->GetCPUDescriptorHandleForHeapStart();

		if (shaderVisible)
		{
			_gpuStart = _heap->GetGPUDescriptorHandleForHeapStart();
		}

		_freeIndices.resize(numDescriptors);
		for (uint32_t i = 0; i < numDescriptors; ++i)
		{
			_freeIndices[i] = (numDescriptors - 1) - i;
		}
	}

	DescriptorHandle DescriptorHeap::allocate()
	{
		KE_ASSERT(!_freeIndices.empty(), "No free descriptors available in the heap.");

		const uint32_t index = _freeIndices.back();
		_freeIndices.pop_back();

		DescriptorHandle handle;
		handle.heapIndex = index;
		handle.cpuHandle.ptr = _cpuStart.ptr + static_cast<SIZE_T>(index) * _descriptorSize;
		handle.gpuHandle.ptr = _gpuStart.ptr + static_cast<UINT64>(index) * _descriptorSize;
		return handle;
	}

	void DescriptorHeap::release(const DescriptorHandle& handle)
	{
		KE_ASSERT(handle.isValid(), "Cannot release an invalid descriptor handle.");
		KE_ASSERT(handle.heapIndex < _numDescriptors, "Descriptor handle index out of range.");
		_freeIndices.push_back(handle.heapIndex);
	}
}
