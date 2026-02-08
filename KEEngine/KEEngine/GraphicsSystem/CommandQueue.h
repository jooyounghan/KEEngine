#pragma once

namespace ke
{
	enum class ECommandType : uint8
	{
		Direct = 0,
		Compute,
		Copy,
		Count
	};

	class CommandQueue
	{
	public:
		CommandQueue() = default;
		~CommandQueue();

		DELETE_COPYABLE(CommandQueue);
		DEFAULT_MOVEABLE(CommandQueue);

	public:
		void initialize(ID3D12Device* device, ECommandType type);
		void shutdown();

	public:
		uint64 executeCommandList(ID3D12CommandList* commandList);
		uint64 executeCommandLists(ID3D12CommandList* const* commandLists, uint32 count);

	public:
		uint64 signal();
		bool isFenceComplete(uint64 fenceValue) const;
		void waitForFenceValue(uint64 fenceValue);
		void waitForIdle();

	public:
		inline ID3D12CommandQueue* getQueue() const { return _commandQueue.Get(); }
		inline uint64 getNextFenceValue() const { return _nextFenceValue; }
		uint64 getLastCompletedFenceValue() const;
		inline ECommandType getType() const { return _type; }

	private:
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>	_commandQueue;
		Microsoft::WRL::ComPtr<ID3D12Fence>			_fence;
		HANDLE		_fenceEvent = nullptr;
		uint64		_nextFenceValue = 1;
		ECommandType _type = ECommandType::Direct;
	};
}
