#include "GraphicsSystemPch.h"
#include "CommandManager.h"

namespace ke
{
	CommandManager::~CommandManager()
	{
		shutdown();
	}

	void CommandManager::initialize(ID3D12Device* device)
	{
		KE_ASSERT(device != nullptr, "Device must not be null.");
		_device = device;

		_graphicsQueue.initialize(device, ECommandType::Direct);
		_computeQueue.initialize(device, ECommandType::Compute);
		_copyQueue.initialize(device, ECommandType::Copy);
	}

	void CommandManager::shutdown()
	{
		_graphicsQueue.shutdown();
		_computeQueue.shutdown();
		_copyQueue.shutdown();
		_device = nullptr;
	}

	GraphicsCommandContext CommandManager::allocateGraphicsContext()
	{
		GraphicsCommandContext context;
		context.initialize(_device, ECommandType::Direct);
		context.reset();
		return context;
	}

	ComputeCommandContext CommandManager::allocateComputeContext()
	{
		ComputeCommandContext context;
		context.initialize(_device, ECommandType::Compute);
		context.reset();
		return context;
	}

	CopyCommandContext CommandManager::allocateCopyContext()
	{
		CopyCommandContext context;
		context.initialize(_device, ECommandType::Copy);
		context.reset();
		return context;
	}

	uint64 CommandManager::executeGraphicsContext(GraphicsCommandContext& context, bool waitForCompletion)
	{
		return context.finish(_graphicsQueue, waitForCompletion);
	}

	uint64 CommandManager::executeComputeContext(ComputeCommandContext& context, bool waitForCompletion)
	{
		return context.finish(_computeQueue, waitForCompletion);
	}

	uint64 CommandManager::executeCopyContext(CopyCommandContext& context, bool waitForCompletion)
	{
		return context.finish(_copyQueue, waitForCompletion);
	}

	void CommandManager::waitForIdle()
	{
		_graphicsQueue.waitForIdle();
		_computeQueue.waitForIdle();
		_copyQueue.waitForIdle();
	}

	void CommandManager::waitForGraphicsQueue()
	{
		_graphicsQueue.waitForIdle();
	}

	void CommandManager::waitForComputeQueue()
	{
		_computeQueue.waitForIdle();
	}

	void CommandManager::waitForCopyQueue()
	{
		_copyQueue.waitForIdle();
	}
}
