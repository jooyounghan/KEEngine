#pragma once
#include "CommandContext.h"

namespace ke
{
	class CommandManager
	{
	public:
		CommandManager() = default;
		~CommandManager();

		DELETE_COPYABLE(CommandManager);
		DEFAULT_MOVEABLE(CommandManager);

	public:
		void initialize(ID3D12Device* device);
		void shutdown();

	public:
		inline CommandQueue& getGraphicsQueue() { return _graphicsQueue; }
		inline CommandQueue& getComputeQueue() { return _computeQueue; }
		inline CommandQueue& getCopyQueue() { return _copyQueue; }

		inline const CommandQueue& getGraphicsQueue() const { return _graphicsQueue; }
		inline const CommandQueue& getComputeQueue() const { return _computeQueue; }
		inline const CommandQueue& getCopyQueue() const { return _copyQueue; }

	public:
		GraphicsCommandContext allocateGraphicsContext();
		ComputeCommandContext allocateComputeContext();
		CopyCommandContext allocateCopyContext();

	public:
		CommandFence executeGraphicsContext(GraphicsCommandContext& context, bool waitForCompletion = false);
		CommandFence executeComputeContext(ComputeCommandContext& context, bool waitForCompletion = false);
		CommandFence executeCopyContext(CopyCommandContext& context, bool waitForCompletion = false);

	public:
		void waitForIdle();
		void waitForGraphicsQueue();
		void waitForComputeQueue();
		void waitForCopyQueue();

	public:
		inline ID3D12Device* getDevice() const { return _device; }

	private:
		ID3D12Device*	_device = nullptr;
		CommandQueue	_graphicsQueue;
		CommandQueue	_computeQueue;
		CommandQueue	_copyQueue;
	};
}
