#pragma once
namespace ke
{
	struct MonitorInfo
	{
		std::wstring _monitorName;
		LUID         _adapterLuid;
	};

	struct AdapterInfo
	{
		Microsoft::WRL::ComPtr<IDXGIAdapter1> _adapter;
		float                                 _dedicatedVRAM;
		float                                 _sharedSystemRAM;
		UINT                                  _vendorId;
		LUID                                  _luid;
		bool                                  isDX12Supported;
	};

	class DeviceManager
	{
		SINGLETON_CLASS(DeviceManager);

	protected:
		Microsoft::WRL::ComPtr<ID3D12Device>    _device;
		Microsoft::WRL::ComPtr<IDXGIFactory4>   _factory;
		Microsoft::WRL::ComPtr<IDXGIAdapter1>   _selectedAdapter;

	protected:
		std::vector<MonitorInfo> _monitorInfos;
		std::vector<AdapterInfo> _adapterInfos;

	public:
		inline ID3D12Device* getDevice() const { return _device.Get(); }
		inline IDXGIFactory* getFactory() const { return _factory.Get(); }
		inline const std::vector<MonitorInfo>& getMonitorInfos() const { return _monitorInfos; }
		inline const std::vector<AdapterInfo>& getAdapterInfos() const { return _adapterInfos; }

	public:
		void initialize();
		void selectAdapter(size_t index);

	protected:
		void getAdapters(IDXGIFactory1* pFactory);
		void getMonitors();
	};
}

