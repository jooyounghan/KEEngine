#pragma once

namespace ke
{
	struct DescriptorHandle
	{
		D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = {};
		D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = {};
		uint32_t heapIndex = UINT32_MAX;

		bool isValid() const { return heapIndex != UINT32_MAX; }
	};

	class DescriptorHeap
	{
	public:
		DescriptorHeap() = default;
		~DescriptorHeap() = default;

	public:
		void init(
			ID3D12Device* device,
			D3D12_DESCRIPTOR_HEAP_TYPE type,
			uint32_t numDescriptors,
			bool shaderVisible);

		DescriptorHandle allocate();
		void release(const DescriptorHandle& handle);

	public:
		inline ID3D12DescriptorHeap* getHeap() const { return _heap.Get(); }
		inline uint32_t getDescriptorSize() const { return _descriptorSize; }
		inline uint32_t getNumDescriptors() const { return _numDescriptors; }
		inline uint32_t getNumFreeDescriptors() const { return static_cast<uint32_t>(_freeIndices.size()); }

	private:
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>	_heap;
		D3D12_CPU_DESCRIPTOR_HANDLE						_cpuStart = {};
		D3D12_GPU_DESCRIPTOR_HANDLE						_gpuStart = {};
		uint32_t										_descriptorSize = 0;
		uint32_t										_numDescriptors = 0;
		std::vector<uint32_t>							_freeIndices;
	};
}
