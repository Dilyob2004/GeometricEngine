#include <Engine/RHI/DirectX/DX11DynamicRHI.h>
#include <Engine/Core/Misc/Log.h>
namespace GeometricEngine
{
	static bool SafeTestD3D11CreateDevice(IDXGIAdapter* Adapter, D3D_FEATURE_LEVEL MaxFeatureLevel, D3D_FEATURE_LEVEL* OutFeatureLevel)
	{
		ID3D11Device* D3DDevice = NULL;
		ID3D11DeviceContext* D3DDeviceContext = NULL;
		U32 DeviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;
		#ifdef GEOMETRIC_DEBUG
				DeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
		#endif // GEOMETRIC_DEBUG

		D3D_FEATURE_LEVEL RequestedFeatureLevels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };

		I32 FirstAllowedFeatureLevel = 0;
		I32 NumAllowedFeatureLevels = ARRAY_COUNT(RequestedFeatureLevels);
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
			&D3DDeviceContext)))
		{
			D3DDevice->Release();
			D3DDeviceContext->Release();
			return true;
		}
		return false;
	}
	DX11DynamicRHI::DX11DynamicRHI()
		:
		  Viewport(NULL)
		, DXDevice(NULL)
		, DXDeviceContext(NULL)
		, DXGIFactory(NULL)
	{

	}
	DX11DynamicRHI::DX11DynamicRHI(IDXGIFactory1* Factory, DX11Adapter Adapter)
		: Viewport(NULL)
		, DXDevice(NULL)
		, DXDeviceContext(NULL)
		, DXGIFactory(Factory)
		, DXAdapterIndex(Adapter.Index)
	{

	}
	bool  DX11DynamicRHI::Initialize()
	{
		return InitDevice();
	}
	DX11DynamicRHI::~DX11DynamicRHI()
	{
		DXDeviceContext->Release();
		DXDevice->Release();
		DXGIFactory->Release();
	}
	DynamicRHI* DynamicRHI::CreateDynamicRHI()
	{
		IDXGIFactory1* DXGIFactory;
		if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&DXGIFactory))))
		{
			LOG("Error: [DX11RHI] Failed to create DXGI adapter!");
			return NULL;
		}

		DX11Adapter ChoosenAdapter;
		D3D_FEATURE_LEVEL ActualLevel;
		IDXGIAdapter* EnumAdapter;
		for (U32 i = 0; DXGIFactory->EnumAdapters(i, &EnumAdapter) != DXGI_ERROR_NOT_FOUND; i++)
		{
			if (EnumAdapter && SafeTestD3D11CreateDevice(EnumAdapter, D3D_FEATURE_LEVEL_11_1, &ActualLevel))
			{
				DXGI_ADAPTER_DESC Description;
				if (SUCCEEDED(EnumAdapter->GetDesc(&Description)))
				{
					ChoosenAdapter.Index = i;
					ChoosenAdapter.Description = Description;
					ChoosenAdapter.MaxSupportFeatureLevel = ActualLevel;
				}
			}
		}


		return new DX11DynamicRHI(DXGIFactory, ChoosenAdapter);
	}
	bool DX11DynamicRHI::InitDevice()
	{
		U32 Flags							= D3D11_CREATE_DEVICE_BGRA_SUPPORT;


		D3D_FEATURE_LEVEL MaxFeatureLevel	= D3D_FEATURE_LEVEL_11_1;



		D3D_FEATURE_LEVEL ActualLevel		= (D3D_FEATURE_LEVEL)0;

		IDXGIAdapter* EnumAdapter;
		#ifdef GEOMETRIC_DEBUG
			Flags |= D3D11_CREATE_DEVICE_DEBUG;
		#endif // GEOMETRIC_DEBUG

		if (FAILED(DXGIFactory->EnumAdapters(DXAdapterIndex, &EnumAdapter)))
		{
			LOG("Error: [DX11RHI] Failed to enum adapters!\n");
			return false;
		}
		if (FAILED(D3D11CreateDevice(EnumAdapter,
									D3D_DRIVER_TYPE_UNKNOWN,
									NULL, 
									Flags,
									&MaxFeatureLevel,
									1, 
									D3D11_SDK_VERSION, 
									&DXDevice, 
									&ActualLevel, 
									&DXDeviceContext)))
		{
			LOG("Error: [DX11RHI] D3D11CreateDevice!");
			return false;
		}
		return true;
	}
}