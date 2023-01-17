#include <Engine/RHI/DirectX/DX11DynamicRHI.h>

namespace MeteorEngine
{
	static bool SafeTestD3D11CreateDevice(IDXGIAdapter* Adapter, D3D_FEATURE_LEVEL MaxFeatureLevel, D3D_FEATURE_LEVEL* OutFeatureLevel)
	{
		ID3D11Device* D3DDevice = NULL;
		ID3D11DeviceContext* D3DDeviceContext = NULL;
		u32 DeviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;

		// Use a debug device if specified on the command line.
		/**if (Debug())
		{
			DeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		}*/
		D3D_FEATURE_LEVEL RequestedFeatureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0 };

		i32 FirstAllowedFeatureLevel = 0;
		i32 NumAllowedFeatureLevels = ARRAY_COUNT(RequestedFeatureLevels);
		while (FirstAllowedFeatureLevel < NumAllowedFeatureLevels)
		{
			if (RequestedFeatureLevels[FirstAllowedFeatureLevel] == MaxFeatureLevel)
				break;
			FirstAllowedFeatureLevel++;
		}
		NumAllowedFeatureLevels -= FirstAllowedFeatureLevel;

		if (!NumAllowedFeatureLevels)
			return false;

		if (SUCCEEDED(D3D11CreateDevice(
			Adapter,
			D3D_DRIVER_TYPE_UNKNOWN,
			NULL,
			DeviceFlags,
			&RequestedFeatureLevels[FirstAllowedFeatureLevel],
			NumAllowedFeatureLevels,
			D3D11_SDK_VERSION,
			&D3DDevice,
			OutFeatureLevel,
			&D3DDeviceContext
		)))
		{
			D3DDevice->Release();
			D3DDeviceContext->Release();
			return true;
		}
		return false;
	}
	DX11DynamicRHI::DX11DynamicRHI()
		: DXDevice(NULL)
		, DXDeviceContext(NULL)
		, DXGIFactory(NULL)
		, DXGIAdapter(NULL)
	{

	}
	DX11DynamicRHI::DX11DynamicRHI(IDXGIFactory* Factory, IDXGIAdapter* InAdapter)
		: DXDevice(NULL)
		, DXDeviceContext(NULL)
		, DXGIFactory(Factory)
		, DXGIAdapter(InAdapter)
	{

	}
	void DX11DynamicRHI::Init()
	{
		InitDevice();
	}
	DX11DynamicRHI::~DX11DynamicRHI()
	{
		DXDevice->Release();
		DXDeviceContext->Release();
		DXGIFactory->Release();
		DXGIAdapter->Release();
	}
	DynamicRHI* DynamicRHI::CreateDynamicRHI()
	{
		D3D_FEATURE_LEVEL FeatureLevel = D3D_FEATURE_LEVEL_11_0;
		IDXGIFactory* Factory = NULL;
		if (CreateDXGIFactory(IID_PPV_ARGS(&Factory)) != S_OK)
		{
			LOG("Cannot create DXGI adapter");
			return NULL;
		}
		IDXGIAdapter* InAdapter;
		IDXGIAdapter* SelectedAdapter = NULL;
		for (u32 i = 0; Factory->EnumAdapters(i, &InAdapter) != DXGI_ERROR_NOT_FOUND; i++)
		{
			if (InAdapter)
			{
				DXGI_ADAPTER_DESC Description;
				if (SUCCEEDED(InAdapter->GetDesc(&Description)))
				{
					if(i == 0)
						SelectedAdapter = InAdapter;
				}
			}
		}
		return new DX11DynamicRHI(Factory, SelectedAdapter);
	}
	void DX11DynamicRHI::InitDevice()
	{
		D3D_DRIVER_TYPE DriverType			= D3D_DRIVER_TYPE_UNKNOWN;
		u32 Flags							= D3D11_CREATE_DEVICE_BGRA_SUPPORT;
		D3D_FEATURE_LEVEL MaxFeatureLevel	= D3D_FEATURE_LEVEL_11_1;
		D3D_FEATURE_LEVEL ActualLevel		= (D3D_FEATURE_LEVEL)0;
		if (FAILED(D3D11CreateDevice(
								DXGIAdapter,
								DriverType, 
								NULL, 
								Flags,
								&MaxFeatureLevel,
								1, 
								D3D11_SDK_VERSION, 
								&DXDevice, 
								&ActualLevel, 
								&DXDeviceContext
		)))
		{
			LOG("Error: D3D11CreateDevice!");
			return;
		}

	}
}