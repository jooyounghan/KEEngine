#include "GraphicsSystemPch.h"
#include "CommandQueue.h"

using namespace Microsoft::WRL;

namespace ke
{
	CommandQueue::~CommandQueue()
	{
		shutdown();
	}

	void CommandQueue::initialize(
		ID3D12Device* device
		, ECommandType type
		, D3D12_COMMAND_QUEUE_PRIORITY priority/* = D3D12_COMMAND_QUEUE_PRIORITY::D3D12_COMMAND_QUEUE_PRIORITY_NORMAL*/
		, D3D12_COMMAND_QUEUE_FLAGS flag/* = D3D12_COMMAND_QUEUE_FLAGS::D3D12_COMMAND_QUEUE_FLAG_NONE*/
	)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		_type = type;

		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type = toD3D12CommandListType(type);
		desc.Priority = priority;
		desc.Flags = flag;
		desc.NodeMask = 0;

		KE_ASSERT(!FAILED(device->CreateCommandQueue(&desc, IID_PPV_ARGS(&_commandQueue))),
			"Failed to create command queue.");

		KE_ASSERT(!FAILED(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence))),
			"Failed to create fence.");

		_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		KE_ASSERT(_fenceEvent != nullptr, "Failed to create fence event.");

		_nextFenceValue = 1;
	}

	void CommandQueue::shutdown()
	{
		if (_commandQueue)
		{
			waitForIdle();
		}

		if (_fenceEvent)
		{
			CloseHandle(_fenceEvent);
			_fenceEvent = nullptr;
		}

		_fence.Reset();
		_commandQueue.Reset();
	}

	CommandFence CommandQueue::executeCommandList(ID3D12CommandList* commandList, const std::string& debugHint)
	{
		return executeCommandLists(&commandList, 1, debugHint);
	}

	CommandFence CommandQueue::executeCommandLists(ID3D12CommandList* const* commandLists, uint32 count, const std::string& debugHint)
	{
		_commandQueue->ExecuteCommandLists(count, commandLists);
		return signal(debugHint);
	}

	CommandFence CommandQueue::signal(const std::string& debugHint)
	{
		const uint64 fenceValue = _nextFenceValue++;
		KE_ASSERT(!FAILED(_commandQueue->Signal(_fence.Get(), fenceValue)),
			"Failed to signal fence.");

		CommandFence ret;
		ret.value = fenceValue;

#ifdef KE_DEV
		ret.commandDebugHint = debugHint;
#endif

		return ret;
	}

	CommandFence CommandQueue::getCompletedCommandFence() const
	{
		CommandFence commandFence;
		commandFence.value = _fence->GetCompletedValue();
		return commandFence;
	}

	bool CommandQueue::isComplete(CommandFence fenceValue)
	{
		if (fenceValue.value <= _lastCompletedFenceValue)
		{
			return true;
		}

		_lastCompletedFenceValue = std::max(_lastCompletedFenceValue, _fence->GetCompletedValue());
		return fenceValue.value <= _lastCompletedFenceValue;
	}

	void CommandQueue::wait(CommandFence fenceValue, DWORD timeOutMilliSecond/* = INFINITE*/)
	{
		if (isComplete(fenceValue))
		{
			return;
		}

		KE_ASSERT(!FAILED(_fence->SetEventOnCompletion(fenceValue.value, _fenceEvent)),
			"Failed to set fence event.");

		WaitForSingleObject(_fenceEvent, timeOutMilliSecond);
		_lastCompletedFenceValue = fenceValue.value;
	}

	void CommandQueue::waitForIdle()
	{
		const CommandFence fenceValue = signal("WaitForIdle");
		wait(fenceValue);
	}
}
