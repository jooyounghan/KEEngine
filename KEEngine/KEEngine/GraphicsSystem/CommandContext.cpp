#include "GraphicsSystemPch.h"
#include "CommandContext.h"

using namespace Microsoft::WRL;

namespace ke
{
	void CommandContext::initialize(ID3D12Device* device, ECommandType type)
	{
		if (device == nullptr)
		{
			KE_ASSERT(device != nullptr, "Device must not be null.");
			return;
		}
		_type = type;
		const D3D12_COMMAND_LIST_TYPE d3dType = toD3D12CommandListType(type);

		KE_ASSERT(!FAILED(device->CreateCommandAllocator(d3dType, IID_PPV_ARGS(&_commandAllocator))),
			"Failed to create command allocator.");

		ComPtr<ID3D12GraphicsCommandList> baseCmdList;
		KE_ASSERT(!FAILED(device->CreateCommandList(0, d3dType, _commandAllocator.Get(), nullptr, IID_PPV_ARGS(&baseCmdList))),
			"Failed to create command list.");

		KE_ASSERT(!FAILED(baseCmdList.As(&_commandList)),
			"Failed to query ID3D12GraphicsCommandList4. Ensure your GPU and driver support DXR.");

		// Command list is created in the recording state; close it so that reset() can be called.
		_commandList->Close();
	}

	void CommandContext::reset()
	{
		KE_ASSERT(_commandAllocator, "Command allocator is not initialized.");
		KE_ASSERT(_commandList, "Command list is not initialized.");

		KE_ASSERT(!FAILED(_commandAllocator->Reset()),
			"Failed to reset command allocator.");
		KE_ASSERT(!FAILED(_commandList->Reset(_commandAllocator.Get(), nullptr)),
			"Failed to reset command list.");

		_pendingBarrierCount = 0;
	}

	CommandFence CommandContext::finish(CommandQueue& queue, bool waitForCompletion)
	{
		flushBarriers();

		KE_ASSERT(!FAILED(_commandList->Close()),
			"Failed to close command list.");

		ID3D12CommandList* lists[] = { _commandList.Get() };
		const CommandFence fenceValue = queue.executeCommandLists(lists, 1);

		if (waitForCompletion)
		{
			queue.wait(fenceValue);
		}

		return fenceValue;
	}

	void CommandContext::transitionBarrier(
		ID3D12Resource* resource,
		D3D12_RESOURCE_STATES before,
		D3D12_RESOURCE_STATES after,
		uint32 subresource)
	{
		if (_pendingBarrierCount >= MAX_PENDING_BARRIERS)
		{
			flushBarriers();
		}

		D3D12_RESOURCE_BARRIER& barrier = _pendingBarriers[_pendingBarrierCount++];
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.Transition.pResource = resource;
		barrier.Transition.StateBefore = before;
		barrier.Transition.StateAfter = after;
		barrier.Transition.Subresource = subresource;
	}

	void CommandContext::uavBarrier(ID3D12Resource* resource)
	{
		if (_pendingBarrierCount >= MAX_PENDING_BARRIERS)
		{
			flushBarriers();
		}

		D3D12_RESOURCE_BARRIER& barrier = _pendingBarriers[_pendingBarrierCount++];
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_UAV;
		barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
		barrier.UAV.pResource = resource;
	}

	void CommandContext::flushBarriers()
	{
		if (_pendingBarrierCount > 0)
		{
			_commandList->ResourceBarrier(_pendingBarrierCount, _pendingBarriers);
			_pendingBarrierCount = 0;
		}
	}

	void CommandContext::setDescriptorHeaps(uint32 count, ID3D12DescriptorHeap* const* heaps)
	{
		_commandList->SetDescriptorHeaps(count, heaps);
	}

	// ============================================================================
	// GraphicsCommandContext
	// ============================================================================

	GraphicsCommandContext::GraphicsCommandContext()
	{
		_type = ECommandType::Direct;
	}

	void GraphicsCommandContext::setRenderTargets(
		uint32 numRTVs,
		const D3D12_CPU_DESCRIPTOR_HANDLE* rtvHandles,
		const D3D12_CPU_DESCRIPTOR_HANDLE* dsvHandle)
	{
		_commandList->OMSetRenderTargets(numRTVs, rtvHandles, FALSE, dsvHandle);
	}

	void GraphicsCommandContext::clearRenderTarget(D3D12_CPU_DESCRIPTOR_HANDLE rtv, const float color[4])
	{
		_commandList->ClearRenderTargetView(rtv, color, 0, nullptr);
	}

	void GraphicsCommandContext::clearDepthStencil(D3D12_CPU_DESCRIPTOR_HANDLE dsv, float depth, uint8 stencil)
	{
		_commandList->ClearDepthStencilView(
			dsv,
			D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL,
			depth, stencil, 0, nullptr);
	}

	void GraphicsCommandContext::setViewport(
		float x, float y, float width, float height,
		float minDepth, float maxDepth)
	{
		D3D12_VIEWPORT vp = { x, y, width, height, minDepth, maxDepth };
		_commandList->RSSetViewports(1, &vp);
	}

	void GraphicsCommandContext::setScissorRect(int32 left, int32 top, int32 right, int32 bottom)
	{
		D3D12_RECT rect = { static_cast<LONG>(left), static_cast<LONG>(top), static_cast<LONG>(right), static_cast<LONG>(bottom) };
		_commandList->RSSetScissorRects(1, &rect);
	}

	void GraphicsCommandContext::setViewportAndScissor(uint32 x, uint32 y, uint32 width, uint32 height)
	{
		setViewport(
			static_cast<float>(x), static_cast<float>(y),
			static_cast<float>(width), static_cast<float>(height));
		setScissorRect(
			static_cast<int32>(x), static_cast<int32>(y),
			static_cast<int32>(x + width), static_cast<int32>(y + height));
	}

	void GraphicsCommandContext::setPipelineState(ID3D12PipelineState* pso)
	{
		_commandList->SetPipelineState(pso);
	}

	void GraphicsCommandContext::setGraphicsRootSignature(ID3D12RootSignature* rootSig)
	{
		_commandList->SetGraphicsRootSignature(rootSig);
	}

	void GraphicsCommandContext::setGraphicsRootDescriptorTable(uint32 rootParamIndex, D3D12_GPU_DESCRIPTOR_HANDLE handle)
	{
		_commandList->SetGraphicsRootDescriptorTable(rootParamIndex, handle);
	}

	void GraphicsCommandContext::setGraphicsRoot32BitConstants(
		uint32 rootParamIndex, uint32 numValues,
		const void* data, uint32 destOffset)
	{
		_commandList->SetGraphicsRoot32BitConstants(rootParamIndex, numValues, data, destOffset);
	}

	void GraphicsCommandContext::setGraphicsRootConstantBufferView(uint32 rootParamIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
	{
		_commandList->SetGraphicsRootConstantBufferView(rootParamIndex, bufferLocation);
	}

	void GraphicsCommandContext::setGraphicsRootShaderResourceView(uint32 rootParamIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
	{
		_commandList->SetGraphicsRootShaderResourceView(rootParamIndex, bufferLocation);
	}

	void GraphicsCommandContext::setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology)
	{
		_commandList->IASetPrimitiveTopology(topology);
	}

	void GraphicsCommandContext::setVertexBuffers(uint32 startSlot, uint32 count, const D3D12_VERTEX_BUFFER_VIEW* views)
	{
		_commandList->IASetVertexBuffers(startSlot, count, views);
	}

	void GraphicsCommandContext::setIndexBuffer(const D3D12_INDEX_BUFFER_VIEW* view)
	{
		_commandList->IASetIndexBuffer(view);
	}

	void GraphicsCommandContext::draw(
		uint32 vertexCount, uint32 instanceCount,
		uint32 startVertex, uint32 startInstance)
	{
		flushBarriers();
		_commandList->DrawInstanced(vertexCount, instanceCount, startVertex, startInstance);
	}

	void GraphicsCommandContext::drawIndexed(
		uint32 indexCount, uint32 instanceCount,
		uint32 startIndex, int32 baseVertex,
		uint32 startInstance)
	{
		flushBarriers();
		_commandList->DrawIndexedInstanced(indexCount, instanceCount, startIndex, baseVertex, startInstance);
	}

	void GraphicsCommandContext::drawIndirect(
		ID3D12CommandSignature* commandSig,
		ID3D12Resource* argBuffer,
		uint64 argBufferOffset,
		uint32 maxCommandCount,
		ID3D12Resource* countBuffer,
		uint64 countBufferOffset)
	{
		flushBarriers();
		_commandList->ExecuteIndirect(commandSig, maxCommandCount, argBuffer, argBufferOffset, countBuffer, countBufferOffset);
	}

	void GraphicsCommandContext::buildRaytracingAccelerationStructure(
		const D3D12_BUILD_RAYTRACING_ACCELERATION_STRUCTURE_DESC* desc,
		uint32 numPostbuildInfoDescs,
		const D3D12_RAYTRACING_ACCELERATION_STRUCTURE_POSTBUILD_INFO_DESC* postbuildInfoDescs)
	{
		flushBarriers();
		_commandList->BuildRaytracingAccelerationStructure(desc, numPostbuildInfoDescs, postbuildInfoDescs);
	}

	void GraphicsCommandContext::dispatchRays(const D3D12_DISPATCH_RAYS_DESC* desc)
	{
		flushBarriers();
		_commandList->DispatchRays(desc);
	}

	// ============================================================================
	// ComputeCommandContext
	// ============================================================================

	ComputeCommandContext::ComputeCommandContext()
	{
		_type = ECommandType::Compute;
	}

	void ComputeCommandContext::setPipelineState(ID3D12PipelineState* pso)
	{
		_commandList->SetPipelineState(pso);
	}

	void ComputeCommandContext::setComputeRootSignature(ID3D12RootSignature* rootSig)
	{
		_commandList->SetComputeRootSignature(rootSig);
	}

	void ComputeCommandContext::setComputeRootDescriptorTable(uint32 rootParamIndex, D3D12_GPU_DESCRIPTOR_HANDLE handle)
	{
		_commandList->SetComputeRootDescriptorTable(rootParamIndex, handle);
	}

	void ComputeCommandContext::setComputeRoot32BitConstants(
		uint32 rootParamIndex, uint32 numValues,
		const void* data, uint32 destOffset)
	{
		_commandList->SetComputeRoot32BitConstants(rootParamIndex, numValues, data, destOffset);
	}

	void ComputeCommandContext::setComputeRootConstantBufferView(uint32 rootParamIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
	{
		_commandList->SetComputeRootConstantBufferView(rootParamIndex, bufferLocation);
	}

	void ComputeCommandContext::setComputeRootShaderResourceView(uint32 rootParamIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
	{
		_commandList->SetComputeRootShaderResourceView(rootParamIndex, bufferLocation);
	}

	void ComputeCommandContext::setComputeRootUnorderedAccessView(uint32 rootParamIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
	{
		_commandList->SetComputeRootUnorderedAccessView(rootParamIndex, bufferLocation);
	}

	void ComputeCommandContext::dispatch(uint32 threadGroupCountX, uint32 threadGroupCountY, uint32 threadGroupCountZ)
	{
		flushBarriers();
		_commandList->Dispatch(threadGroupCountX, threadGroupCountY, threadGroupCountZ);
	}

	void ComputeCommandContext::dispatchIndirect(
		ID3D12CommandSignature* commandSig,
		ID3D12Resource* argBuffer,
		uint64 argBufferOffset,
		uint32 maxCommandCount,
		ID3D12Resource* countBuffer,
		uint64 countBufferOffset)
	{
		flushBarriers();
		_commandList->ExecuteIndirect(commandSig, maxCommandCount, argBuffer, argBufferOffset, countBuffer, countBufferOffset);
	}

	// ============================================================================
	// CopyCommandContext
	// ============================================================================

	CopyCommandContext::CopyCommandContext()
	{
		_type = ECommandType::Copy;
	}

	void CopyCommandContext::copyBufferRegion(
		ID3D12Resource* dst, uint64 dstOffset,
		ID3D12Resource* src, uint64 srcOffset,
		uint64 numBytes)
	{
		flushBarriers();
		_commandList->CopyBufferRegion(dst, dstOffset, src, srcOffset, numBytes);
	}

	void CopyCommandContext::copyTextureRegion(
		const D3D12_TEXTURE_COPY_LOCATION* dst,
		uint32 dstX, uint32 dstY, uint32 dstZ,
		const D3D12_TEXTURE_COPY_LOCATION* src,
		const D3D12_BOX* srcBox)
	{
		flushBarriers();
		_commandList->CopyTextureRegion(dst, dstX, dstY, dstZ, src, srcBox);
	}

	void CopyCommandContext::copyResource(ID3D12Resource* dst, ID3D12Resource* src)
	{
		flushBarriers();
		_commandList->CopyResource(dst, src);
	}
}
