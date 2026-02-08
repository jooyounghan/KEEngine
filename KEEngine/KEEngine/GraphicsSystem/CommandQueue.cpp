#include "GraphicsSystemPch.h"
#include "CommandQueue.h"

using namespace Microsoft::WRL;

namespace ke
{
	CommandQueue::~CommandQueue()
	{
		shutdown();
	}

	void CommandQueue::initialize(ID3D12Device* device, ECommandType type)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		_type = type;

		D3D12_COMMAND_QUEUE_DESC desc = {};
		desc.Type = toD3D12CommandListType(type);
		desc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
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

	uint64 CommandQueue::executeCommandList(ID3D12CommandList* commandList)
	{
		return executeCommandLists(&commandList, 1);
	}

	uint64 CommandQueue::executeCommandLists(ID3D12CommandList* const* commandLists, uint32 count)
	{
		_commandQueue->ExecuteCommandLists(count, commandLists);
		return signal();
	}

	uint64 CommandQueue::signal()
	{
		const uint64 fenceValue = _nextFenceValue++;
		KE_ASSERT(!FAILED(_commandQueue->Signal(_fence.Get(), fenceValue)),
			"Failed to signal fence.");
		return fenceValue;
	}

	bool CommandQueue::isFenceComplete(uint64 fenceValue) const
	{
		return _fence->GetCompletedValue() >= fenceValue;
	}

	void CommandQueue::waitForFenceValue(uint64 fenceValue)
	{
		if (isFenceComplete(fenceValue))
		{
			return;
		}

		KE_ASSERT(!FAILED(_fence->SetEventOnCompletion(fenceValue, _fenceEvent)),
			"Failed to set fence event.");

		WaitForSingleObject(_fenceEvent, INFINITE);
	}

	void CommandQueue::waitForIdle()
	{
		const uint64 fenceValue = signal();
		waitForFenceValue(fenceValue);
	}

	uint64 CommandQueue::getLastCompletedFenceValue() const
	{
		return _fence->GetCompletedValue();
	}
}
