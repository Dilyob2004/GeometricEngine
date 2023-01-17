#ifndef DX11DYNAMICRHI_H
#define DX11DYNAMICRHI_H
#include <Engine/RHI/DynamicRHI.h>
#include <Engine/RHI/DirectX/DX11/DX11Viewport.h>
#include <d3d11.h>
namespace MeteorEngine
{
	class METEOR_API DX11DynamicRHI: public DynamicRHI
	{
	public:
		friend class DX11Viewport;
		DX11DynamicRHI();
		DX11DynamicRHI(IDXGIFactory*, IDXGIAdapter*);
		~DX11DynamicRHI();
		virtual void Init() override;

		virtual RHIViewport*		RHICreateViewport(void*, u32, u32, bool) override;
		virtual RHIPixelShader*		RHICreatePixelShader(const std::vector<u32>& )override;
		virtual RHIVertexShader*	RHICreateVertexShader(const std::vector<u32>&) override;		
		virtual RHIVertexLayout*	RHICreateVertexLayout(const RHIVertexShader*, const VertexLayoutGroup&) override;
		virtual RHIVertexBuffer*	RHICreateVertexBuffer(void*, u32) override;
		virtual RHIIndexBuffer*		RHICreateIndexBuffer(void*, u32) override;

		virtual void				RHIBindPixelShader(const RHIPixelShader*) override;
		virtual void				RHIBindVertexShader(const RHIVertexShader*) override;
		virtual void				RHIBindVertexLayout(const RHIVertexLayout*) override;

		virtual void				RHIDrawVertices(u32, u32) override;
		virtual void				RHIBindVertexBuffer(const RHIVertexBuffer*, u32, u32) override;
		virtual void				RHIBindIndexBuffer(const RHIIndexBuffer*) override{}

		virtual void				RHISetViewport(f32, f32, f32, f32, f32, f32) override;
		virtual void				RHIResizeViewport(u32, u32, bool)override;
		virtual void				RHIBegin()override;
		virtual void				RHIEnd()override;


		void InitDevice();
		IDXGIFactory* GetDXGIFactory() const { return DXGIFactory; }
		ID3D11Device* GetDXDevice() const { return DXDevice; }
		ID3D11DeviceContext* GetDXDeviceContext() const { return DXDeviceContext; }
	private:
		DX11Viewport*			DXViewport;
		ID3D11Device*			DXDevice;
		ID3D11DeviceContext*	DXDeviceContext;
		IDXGIFactory*			DXGIFactory;
		IDXGIAdapter*			DXGIAdapter;
	};
}

#endif // !DX11DynamicRHI_H
