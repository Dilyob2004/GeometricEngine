#include <Engine/RHI/DirectX/DX12DynamicRHI.h>
#include <Engine/Core/Generic/ScopeLock.h>
#include <Engine/Core/Containers/Array.h>
#include <Engine/Core/Misc/Log.h>
namespace GeometricEngine
{

	/**static bool SafeTestD3D12Device(IDXGIAdapter* Adapter)
	{
		if (SUCCEEDED(D3D12CreateDevice(Adapter, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device), NULL)))
			return true;
		return false;
	}
	class DX12Fence
	{
	public:
		inline ID3D12Fence* GetFence() const { return DXFence; }
		DX12Fence(ID3D12Device* Device) :
			DXDevice(Device),
			DXFence(NULL),
			CurrentFence(1),
			LastCompletedFence(0),
			SignalFence(0),
			FenceCompletedEvent(INVALID_HANDLE_VALUE)
		{
		}
		bool CreateFence(U64 InitialValue)
		{
			FenceCompletedEvent = CreateEvent(NULL, false, false, NULL);
			if (FenceCompletedEvent == INVALID_HANDLE_VALUE)
				return false;
			if (FAILED(DXDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&DXFence))))
			{
				LOG("Error: [DX12RHI] Failed to create gpu fence!");
				return false;
			}
			LastCompletedFence = (U64)DXFence->GetCompletedValue();
			CurrentFence = SignalFence = LastCompletedFence + 1;


			return true;
		}
		U64 Signal(ID3D12CommandQueue* Queue)
		{
			ScopeLock Locker(&Section);
			Queue->Signal(DXFence, CurrentFence);

			SignalFence = CurrentFence;
			CurrentFence++;
			return SignalFence;
		}
		bool IsCompletedFence(U64 Value)
		{

			if (Value <= LastCompletedFence)
				return true;

			LastCompletedFence = (U64)DXFence->GetCompletedValue();


			return Value <= LastCompletedFence;
		}
		void WaitForGPU(ID3D12CommandQueue * Queue, U64 FenceValue)
		{
			if (!Queue)
				exit(-1);
			if (FAILED(Queue->Wait(DXFence, FenceValue)))
			{
				exit(-1);
			}
		}
		void WaitForFence(U64 Value)
		{
			if (IsCompletedFence(Value))
				return;


			DXFence->SetEventOnCompletion(Value, FenceCompletedEvent);


			WaitForSingleObject(FenceCompletedEvent, INFINITE);


			LastCompletedFence = Value;
		}
		void Release()
		{
			CloseHandle(FenceCompletedEvent);
			FenceCompletedEvent = NULL;

			DXFence->Release();
			DXFence = NULL;
		}
		FORCEINLINE U64 GetLastCompletedFence() const { return LastCompletedFence; }
		FORCEINLINE U64 GetSignalFence() const { return CurrentFence; }
		FORCEINLINE U64 GetCurrentFence() const { return SignalFence; }
	private:
		ID3D12Fence* DXFence;
		ID3D12Device* DXDevice;


		HANDLE FenceCompletedEvent;
		CriticalSection Section;
		U64 CurrentFence;
		U64	SignalFence;
		U64 LastCompletedFence;

	};
	class DX12CommandAllocator
	{
	public:
		DX12CommandAllocator(ID3D12Device* Device, const D3D12_COMMAND_LIST_TYPE& Type)
			: DXDevice(Device)
			, DXCommandType(Type)
		{

		}
		~DX12CommandAllocator()
		{
			Release();
		}
		ID3D12CommandAllocator* Request(U64 FenceValue)
		{
			ScopeLock Loker(&Section);
			ID3D12CommandAllocator* CmdAllocator = NULL;
			if (!FrameList.IsEmpty())
			{
				FrameData FirstFrameData = FrameList[0];
				if (FirstFrameData.FenceValue <= FenceValue)
				{
					CmdAllocator = FirstFrameData.DXCommandAllocator;
					FrameList.RemoveAtKeepOrder(0);
				}
			}

			if (!CmdAllocator)
			{
				DXDevice->CreateCommandAllocator(DXCommandType, IID_PPV_ARGS(&CmdAllocator));

				Allocators.Push(CmdAllocator);
			}

			return CmdAllocator;
		}
		void Release()
		{
			for (int i = 0; i < Allocators.GetCount(); i++)
			{
				Allocators[i]->Release();
				Allocators[i] = NULL;
			}
			Allocators.Clear();
		}
		void Discard(U64 FenceValue, ID3D12CommandAllocator* CommandAllocator)
		{
			ScopeLock Loker(&Section);
			FrameList.Push({ FenceValue, CommandAllocator });
		}
	private:
		struct FrameData
		{
			U64 FenceValue;
			ID3D12CommandAllocator* DXCommandAllocator;
		};

		TVector<FrameData> FrameList;
		TVector<ID3D12CommandAllocator*> Allocators;
		CriticalSection Section;
		ID3D12Device* DXDevice;
		D3D12_COMMAND_LIST_TYPE DXCommandType;
	};
	class DX12CommandQueue
	{
	public:
		DX12CommandQueue(ID3D12Device* Device, const D3D12_COMMAND_LIST_TYPE& Type)
			: DXDevice(Device)
			, DXCommandType(Type)
			, DXCommandQueue(NULL)
		{
			Fence = new DX12Fence(Device);
			CommandAllocator = new DX12CommandAllocator(Device, Type);
		}
		~DX12CommandQueue()
		{

		}
		bool CreateQueue()
		{
			D3D12_COMMAND_QUEUE_DESC CommandQueueDesc;
			SMemory::Zero(&CommandQueueDesc, sizeof(CommandQueueDesc));
			CommandQueueDesc.Type = DXCommandType;
			CommandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
			CommandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
			CommandQueueDesc.NodeMask = 0;
			if (FAILED(DXDevice->CreateCommandQueue(&CommandQueueDesc, IID_PPV_ARGS(&DXCommandQueue))))
			{
				LOG("Error: [DX12RHI] Failed to create a command queue!\n");
				return false;
			}
			if (!Fence->CreateFence(0))
				return false;
			return true;
		}
		void WaitForFence(U64 Value)
		{
			Fence->WaitForFence(Value);
		}
		void WaitForGPU()
		{
			U64 Value = Fence->Signal(DXCommandQueue);
			Fence->WaitForFence(Value);
		}
		U64 Excute(ID3D12CommandList* CmdList)
		{
			static_cast<ID3D12GraphicsCommandList*>(CmdList)->Close();

			DXCommandQueue->ExecuteCommandLists(1, &CmdList);

			return Fence->Signal(DXCommandQueue);
		}
		ID3D12CommandAllocator* RequestAllocator()
		{
			const U64 Value = Fence->GetLastCompletedFence();
			return CommandAllocator->Request(Value);
		}

		void Discard(U64 FenceValue, ID3D12CommandAllocator* DXCmdAllocator)
		{
			CommandAllocator->Discard(FenceValue, DXCmdAllocator);
		}
		FORCEINLINE ID3D12CommandQueue* GetDXCommandQueue() const { return DXCommandQueue; }
	private:

		DX12Fence* Fence;
		DX12CommandAllocator* CommandAllocator;
		D3D12_COMMAND_LIST_TYPE DXCommandType;
		ID3D12Device* DXDevice;
		ID3D12CommandQueue* DXCommandQueue;
	};
	class DX12CommandList
	{
	public:
		DX12CommandList(ID3D12Device* Device, const D3D12_COMMAND_LIST_TYPE& Type)
			: DXDevice(Device)
			, DXCommandList(NULL)
			, DXCommandType(Type)
			, DXCurrentAllocator(NULL)

		{
			CommandQueue = new DX12CommandQueue(Device, Type);
			FrameDataFence[0] = FrameDataFence[1] = 0;
		}
		bool Init()
		{
			if (!CommandQueue->CreateQueue())
			{
				return false;
			}
			DXCurrentAllocator = CommandQueue->RequestAllocator();
			if (FAILED(DXDevice->CreateCommandList(0, DXCommandType, DXCurrentAllocator, NULL, IID_PPV_ARGS(&DXCommandList))))
			{
				LOG("Error: [DX12RHI] Failed to create a command list!\n");
				return false;
			}

			return true;

		}

		U64 Excute(bool Wait)
		{
			U64 FenceValue = CommandQueue->Excute(DXCommandList);

			CommandQueue->Discard(FenceValue, DXCurrentAllocator);
			DXCurrentAllocator = NULL;
			if (Wait)
				CommandQueue->WaitForFence(FenceValue);


			return FenceValue;
		}
		void Begin()
		{
			if (DXCurrentAllocator == NULL)
			{
				DXCurrentAllocator = CommandQueue->RequestAllocator();
				DXCommandList->Reset(DXCurrentAllocator, NULL);
			}
		}
		void End()
		{
			FrameDataFence[1] = FrameDataFence[0];
			FrameDataFence[0] = Excute(false);
		}
		DX12CommandQueue* GetCommandQueue() { return CommandQueue; }
	private:
		U64 FrameDataFence[2];
		DX12CommandQueue* CommandQueue;
		D3D12_COMMAND_LIST_TYPE DXCommandType;

		ID3D12Device* DXDevice;
		ID3D12CommandAllocator* DXCurrentAllocator;
		ID3D12GraphicsCommandList* DXCommandList;
	};

	/**DynamicRHI* DynamicRHI::CreateDynamicRHI()
	{
#ifdef GEOMETRIC_DEBUG
		ID3D12Debug* DebugLayer;
		D3D12GetDebugInterface(IID_PPV_ARGS(&DebugLayer));
		if (DebugLayer)
		{
			DebugLayer->EnableDebugLayer();
			LOG("Info: [D3D12RHI] Debug Layer Enabled!\n");
		}
#endif 
		IDXGIFactory4* Factory;
		if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&Factory))))
		{
			LOG("Error: [D3D12RHI] Failed to create DXGI adpter!");
			exit(-1);
		}




		IDXGIAdapter* InAdapter, * SelectedAdapter = NULL;
		for (U32 i = 0; Factory->EnumAdapters(i, &InAdapter) != DXGI_ERROR_NOT_FOUND; i++)
		{
			if (InAdapter && SafeTestD3D12Device(InAdapter))
			{
				DXGI_ADAPTER_DESC Description;
				if (SUCCEEDED(InAdapter->GetDesc(&Description))) {
					SelectedAdapter = InAdapter;
				}
			}
		}
		return new DX12DynamicRHI(Factory, SelectedAdapter);
	}
	DX12DynamicRHI::DX12DynamicRHI()
		: DXDevice(NULL)
		, DXGIFactory(NULL)
		, DXGIAdapter(NULL)
		, DXGISwapChain(NULL)
	{

	}
	DX12DynamicRHI::DX12DynamicRHI(IDXGIFactory4 * Factory, IDXGIAdapter * InAdapter)
		: DXDevice(NULL)
		, DXGIFactory(Factory)
		, DXGIAdapter(InAdapter)
		, DXGISwapChain(NULL)
	{

	}
	DX12DynamicRHI::~DX12DynamicRHI()
	{
		DXDevice->Release();
		DXGIFactory->Release();
		DXGIAdapter->Release();
	}
	bool  DX12DynamicRHI::Initialize()
	{
		return InitDevice();
	}
	DX12CommandList* CommandList;
	bool DX12DynamicRHI::InitDevice()
	{
		if (SUCCEEDED(D3D12CreateDevice(DXGIAdapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&DXDevice))))
			return true;


		CommandList = new DX12CommandList(DXDevice, D3D12_COMMAND_LIST_TYPE_DIRECT);
		if (!CommandList->Init())
			return false;
		return true;
	}
	RHIViewport* DX12DynamicRHI::RHICreateViewport(void* HandleWindow, U32 Width, U32 Height, bool IsFullScreen)
	{

		DXGI_SWAP_CHAIN_DESC1 SwapChainDescriptor;
		SMemory::Zero(&SwapChainDescriptor, sizeof(SwapChainDescriptor));
		SwapChainDescriptor.Width = Width;
		SwapChainDescriptor.Height = Height;
		SwapChainDescriptor.Stereo = 0;
		SwapChainDescriptor.Scaling = DXGI_SCALING_STRETCH;
		SwapChainDescriptor.Format = DXGI_FORMAT_R10G10B10A2_UNORM;
		SwapChainDescriptor.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		SwapChainDescriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapChainDescriptor.BufferCount = 3;
		SwapChainDescriptor.SampleDesc.Count = 2;
		SwapChainDescriptor.SampleDesc.Quality = 0;
		SwapChainDescriptor.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		SwapChainDescriptor.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		DXGI_SWAP_CHAIN_FULLSCREEN_DESC FullscreenDescriptor;
		FullscreenDescriptor.RefreshRate.Denominator = 1;
		FullscreenDescriptor.RefreshRate.Numerator = 60;
		FullscreenDescriptor.Windowed = 1;
		FullscreenDescriptor.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		FullscreenDescriptor.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		/////////////////////////////////////////////////////////////////////////////////////////
		IDXGISwapChain1* SwapChain;
		if (FAILED(DXGIFactory->CreateSwapChainForHwnd(CommandList->GetCommandQueue()->GetDXCommandQueue(), (HWND)HandleWindow, &SwapChainDescriptor, &FullscreenDescriptor, NULL, &SwapChain)))
		{
			LOG("Error: [DX12RHI] Failed to Create a SwapChain!");
			exit(-1);
		}
		DXGISwapChain = static_cast<IDXGISwapChain3*>(SwapChain);
		return new RHIViewport();
	}
	void DX12DynamicRHI::RHIBegin()
	{
		CommandList->Begin();
	}
	void DX12DynamicRHI::RHIEnd()
	{

		CommandList->End();
		DXGISwapChain->Present(1, 0);
	}*/
}