#ifndef DX11SWAPCHAIN_H
#define DX11SWAPCHAIN_H

#include <Engine/Core/Config.h>
#include <Engine/RHI/RHIResources.h>
#include <Engine/RHI/DynamicRHI.h>
namespace GeometricEngine
{
	class DX11DynamicRHI;
	class DX11Viewport : public RHIViewport
	{
	public:
		DX11Viewport();
		DX11Viewport(const DX11DynamicRHI*, HWND, U32, U32, bool);
		~DX11Viewport();
		void Resize(const DX11DynamicRHI*, U32, U32, bool);
		void Present(bool);

		U32 GetWidth() const { return Width; }
		U32 GetHeight() const { return Height; }
	private:
		HWND HandleWindow;
		U32 Width = 0, Height = 0;

		bool EnabledVSync, EnabledFullScreen;
	};
}
#endif // !DXSWAPCHAIN_H
