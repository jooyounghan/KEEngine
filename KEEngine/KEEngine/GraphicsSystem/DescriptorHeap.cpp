#include "GraphicsSystemPch.h"
#include "DescriptorHeap.h"

namespace ke
{
	DescriptorHeap::~DescriptorHeap()
	{
		shutdown();
	}

	void DescriptorHeap::initialize(
		ID3D12Device* device,
		D3D12_DESCRIPTOR_HEAP_TYPE type,
		uint32 capacity,
		bool shaderVisible)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		KE_ASSERT(capacity > 0, "Descriptor heap capacity must be greater than zero.");

		_type = type;
		_capacity = capacity;
		_shaderVisible = shaderVisible;
		_descriptorSize = device->GetDescriptorHandleIncrementSize(type);

		D3D12_DESCRIPTOR_HEAP_DESC desc = {};
		desc.Type = type;
		desc.NumDescriptors = capacity;
		desc.Flags = shaderVisible
			? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE
			: D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		desc.NodeMask = 0;

		KE_ASSERT(!FAILED(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&_heap))),
			"Failed to create descriptor heap.");

		_freeIndices.reserve(capacity);
		for (uint32 i = capacity; i > 0; --i)
		{
			_freeIndices.push_back(i - 1);
		}

		_activeCount = 0;
	}

	void DescriptorHeap::shutdown()
	{
		_heap.Reset();
		_freeIndices.clear();
		_activeCount = 0;
		_capacity = 0;
	}

	DescriptorHandle DescriptorHeap::allocate()
	{
		KE_ASSERT(!_freeIndices.empty(), "Descriptor heap is full. Cannot allocate.");

		const uint32 index = _freeIndices.back();
		_freeIndices.pop_back();
		++_activeCount;

		DescriptorHandle handle;
		handle.heapIndex = index;
		handle.cpuHandle = _heap->GetCPUDescriptorHandleForHeapStart();
		handle.cpuHandle.ptr += static_cast<SIZE_T>(index) * _descriptorSize;

		if (_shaderVisible)
		{
			handle.gpuHandle = _heap->GetGPUDescriptorHandleForHeapStart();
			handle.gpuHandle.ptr += static_cast<UINT64>(index) * _descriptorSize;
		}

		return handle;
	}

	void DescriptorHeap::release(const DescriptorHandle& handle)
	{
		KE_ASSERT(handle.isValid(), "Cannot release an invalid descriptor handle.");
		KE_ASSERT(handle.heapIndex < _capacity, "Descriptor handle index out of range.");

		_freeIndices.push_back(handle.heapIndex);
		--_activeCount;
	}
}
