#pragma once

namespace ke
{
	enum class ECommandType : uint8
	{
		None = 0,
		Direct,
		Compute,
		Copy,
		Count
	};

	struct CommandFence
	{
		uint64 value = 0;
#ifdef KE_DEV
		std::string commandDebugHint;
#endif
		bool operator<=(const CommandFence& other)
		{
			return value <= other.value;
		}
	};

	inline D3D12_COMMAND_LIST_TYPE toD3D12CommandListType(ECommandType type)
	{
		switch (type)
		{
		case ECommandType::Direct:	return D3D12_COMMAND_LIST_TYPE_DIRECT;
		case ECommandType::Compute:	return D3D12_COMMAND_LIST_TYPE_COMPUTE;
		case ECommandType::Copy:	return D3D12_COMMAND_LIST_TYPE_COPY;
		default:					KE_ASSERT(false, "Invalid command type."); return D3D12_COMMAND_LIST_TYPE_DIRECT;
		}
	}

	class CommandQueue
	{
	public:
		CommandQueue() = default;
		~CommandQueue();
		NONCOPYABLE(CommandQueue);

	public:
		void initialize(
			ID3D12Device* device
			, ECommandType type
			, D3D12_COMMAND_QUEUE_PRIORITY priority = D3D12_COMMAND_QUEUE_PRIORITY::D3D12_COMMAND_QUEUE_PRIORITY_NORMAL
			, D3D12_COMMAND_QUEUE_FLAGS flag = D3D12_COMMAND_QUEUE_FLAGS::D3D12_COMMAND_QUEUE_FLAG_NONE
		);
		void shutdown();

	public:
		CommandFence executeCommandList(ID3D12CommandList* commandList, const std::string& debugHint = "");
		CommandFence executeCommandLists(ID3D12CommandList* const* commandLists, uint32 count, const std::string& debugHint = "");

	private:
		CommandFence signal(const std::string& debugHint = "");

	public:
		CommandFence getCompletedCommandFence() const;
		bool isComplete(CommandFence fenceValue);
		void wait(CommandFence fenceValue, DWORD timeOutMilliSecond = INFINITE);
		void waitForIdle();

	public:
		inline ID3D12CommandQueue* getQueue() const { return _commandQueue.Get(); }
		inline ECommandType getType() const { return _type; }

	private:
		Microsoft::WRL::ComPtr<ID3D12CommandQueue>	_commandQueue;
		Microsoft::WRL::ComPtr<ID3D12Fence>			_fence;
		HANDLE										_fenceEvent = nullptr;
		uint64										_nextFenceValue = 1;
		uint64										_lastCompletedFenceValue = 0;
		ECommandType								_type = ECommandType::None;
	};
}
