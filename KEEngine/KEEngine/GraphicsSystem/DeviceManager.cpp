#include "GraphicsSystemPch.h"
#include "DeviceManager.h"

using namespace Microsoft::WRL;

namespace ke
{
	void DeviceManager::initialize()
	{
#if defined(_DEBUG)
		ComPtr<ID3D12Debug> debugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();
		}
#endif

		KE_ASSERT(!FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&_factory))), "Failed to create DXGI Factory and D3D12 Device.");

        getMonitors();
        getAdapters(_factory.Get());

		size_t isDirectX12SupportedIndex = 0;
        for (; isDirectX12SupportedIndex < _adapterInfos.size(); ++isDirectX12SupportedIndex)
        {
            if (_adapterInfos[isDirectX12SupportedIndex].isDX12Supported)
            {
                break;
            }
        }
        if (isDirectX12SupportedIndex < _adapterInfos.size())
        {
            selectAdapter(isDirectX12SupportedIndex);
        }
        else
        {
            KE_ASSERT(false, "No compatible DirectX 12 adapter found.");
		}
	}

    void DeviceManager::selectAdapter(size_t index)
    {
        KE_ASSERT(index < _adapterInfos.size(), "Invalid adapter index");
		AdapterInfo& adapterInfo = _adapterInfos[index];
        if (adapterInfo.isDX12Supported)
        {
            _selectedAdapter = adapterInfo._adapter;
        }
        KE_ASSERT(!FAILED(D3D12CreateDevice(_selectedAdapter.Get(), D3D_FEATURE_LEVEL_12_2, IID_PPV_ARGS(&_device))), "Failed to create D3D12 Device.");
     }

    void DeviceManager::getAdapters(IDXGIFactory1* pFactory)
    {
        _adapterInfos.clear();
        Microsoft::WRL::ComPtr<IDXGIFactory6> factory6;
        bool isFactory6Supported = SUCCEEDED(pFactory->QueryInterface(IID_PPV_ARGS(&factory6)));

        for (UINT i = 0; ; ++i)
        {
            Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
            if (isFactory6Supported)
            {
                if (FAILED(factory6->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_UNSPECIFIED, IID_PPV_ARGS(&adapter)))) break;
            }
            else
            {
                if (FAILED(pFactory->EnumAdapters1(i, &adapter))) break;
            }

            DXGI_ADAPTER_DESC1 desc;
            adapter->GetDesc1(&desc);
            if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;

            AdapterInfo info = {};
            info._adapter = adapter;
            info._luid = desc.AdapterLuid;
            info._dedicatedVRAM = (float)desc.DedicatedVideoMemory / (1024.0f * 1024.0f * 1024.0f);
            info._sharedSystemRAM = (float)desc.SharedSystemMemory / (1024.0f * 1024.0f * 1024.0f);
            info._vendorId = desc.VendorId;
            info.isDX12Supported = SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_2, _uuidof(ID3D12Device), nullptr));

            _adapterInfos.push_back(info);

            KE_LOG_INFO("[Adapter] LUID: 0x%08x%08x | VRAM: %.2f GB | Shared: %.2f GB | DX12: %s",
                info._luid.HighPart, info._luid.LowPart, info._dedicatedVRAM, info._sharedSystemRAM, info.isDX12Supported ? "OK" : "No");

        }
    }

    void DeviceManager::getMonitors()
    {
        _monitorInfos.clear();

        UINT32 pathCount = 0;
        UINT32 modeCount = 0;

        if (GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &pathCount, &modeCount) != ERROR_SUCCESS)
        {
            return;
        }

        std::vector<DISPLAYCONFIG_PATH_INFO> paths(pathCount);
        std::vector<DISPLAYCONFIG_MODE_INFO> modes(modeCount);

        if (QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &pathCount, paths.data(), &modeCount, modes.data(), nullptr) != ERROR_SUCCESS)
        {
            return;
        }

        for (const auto& path : paths)
        {
            DISPLAYCONFIG_TARGET_DEVICE_NAME targetName = {};
            targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            targetName.header.size = sizeof(targetName);
            targetName.header.adapterId = path.targetInfo.adapterId;
            targetName.header.id = path.targetInfo.id;

            if (DisplayConfigGetDeviceInfo(&targetName.header) == ERROR_SUCCESS)
            {
                MonitorInfo info = {};
                info._monitorName = (targetName.monitorFriendlyDeviceName[0] != L'\0')
                    ? targetName.monitorFriendlyDeviceName
                    : L"Internal/Generic Monitor";

                info._adapterLuid = path.targetInfo.adapterId;
                bool isInternal = (path.targetInfo.outputTechnology == DISPLAYCONFIG_OUTPUT_TECHNOLOGY_INTERNAL);

                _monitorInfos.push_back(info);

                KE_LOG_INFO("[Monitor %zu] %ls %s | Attached to LUID: 0x%08x%08x",
                    _monitorInfos.size() - 1,
                    info._monitorName.c_str(),
                    isInternal ? "(Laptop Internal)" : "(External)",
                    info._adapterLuid.HighPart,
                    info._adapterLuid.LowPart);
            }
        }
    }
}
