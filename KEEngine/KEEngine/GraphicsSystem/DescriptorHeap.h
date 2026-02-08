#pragma once

namespace ke
{
	// ============================================================================
	// DescriptorHandle - Lightweight handle to a descriptor in a heap
	// ============================================================================
	struct DescriptorHandle
	{
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = {};
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = {};
		uint32 heapIndex = INVALID_INDEX(uint32);

		inline bool isValid() const { return heapIndex != INVALID_INDEX(uint32); }
		inline bool isShaderVisible() const { return gpuHandle.ptr != 0; }
	};

	// ============================================================================
	// DescriptorHeap - Manages a ID3D12DescriptorHeap with free-list allocation
	//
	// Supports both shader-visible heaps (for bindless CBV/SRV/UAV) and
	// non-shader-visible heaps (for RTV/DSV).
	// ============================================================================
	class DescriptorHeap
	{
	public:
		DescriptorHeap() = default;
		~DescriptorHeap();

		DELETE_COPYABLE(DescriptorHeap);
		DEFAULT_MOVEABLE(DescriptorHeap);

	public:
		void initialize(
			ID3D12Device* device,
			D3D12_DESCRIPTOR_HEAP_TYPE type,
			uint32 capacity,
			bool shaderVisible = false);
		void shutdown();

	public:
		DescriptorHandle allocate();
		void release(const DescriptorHandle& handle);

	public:
		inline ID3D12DescriptorHeap* getHeap() const { return _heap.Get(); }
		inline D3D12_DESCRIPTOR_HEAP_TYPE getType() const { return _type; }
		inline uint32 getDescriptorSize() const { return _descriptorSize; }
		inline uint32 getCapacity() const { return _capacity; }
		inline uint32 getActiveCount() const { return _activeCount; }
		inline bool isShaderVisible() const { return _shaderVisible; }

	private:
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	_heap;
		D3D12_DESCRIPTOR_HEAP_TYPE	_type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		uint32						_descriptorSize = 0;
		uint32						_capacity = 0;
		uint32						_activeCount = 0;
		bool						_shaderVisible = false;

		std::vector<uint32>			_freeIndices;
	};
}
