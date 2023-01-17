#ifndef DX11SWAPCHAIN_H
#define DX11SWAPCHAIN_H

#include <Engine/Core/Config.h>
#include <Engine/RHI/RHIResources.h>
#include <Engine/RHI/DynamicRHI.h>
#include <d3d11.h>
namespace MeteorEngine
{
	class DX11DynamicRHI;
	class METEOR_API DX11Viewport : public RHIViewport
	{
	public:
		DX11Viewport();
		DX11Viewport(const DX11DynamicRHI*, HWND, u32, u32, bool);
		~DX11Viewport();
		void Resize(const DX11DynamicRHI*, u32, u32, bool);
		void Present(bool);
	private:
		HWND HandleWindow;
		u32 Width, Height;

		bool EnabledVSync, EnabledFullScreen;
	};
}
#endif // !DXSWAPCHAIN_H
