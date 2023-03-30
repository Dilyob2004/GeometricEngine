#include <Engine/RendererCore/ViewportClient.h>
#include <Engine/Core/Application.h>

namespace GeometricEngine
{

	ViewportClient::ViewportClient():
		MainViewport(NULL)
	{

	}
	ViewportClient::~ViewportClient()
	{

	}
	void ViewportClient::Initialize()
	{
		RHIViewportDefinition Definition;
		Definition.Width		= Application::GetMainWindow()->GetWidth();
		Definition.Height		= Application::GetMainWindow()->GetHeight();
		Definition.HandleWindow = Application::GetMainWindow()->GetHandle();
		MainViewport			= GDynamicRHI->RHICreateViewport(Definition);

	}
	void ViewportClient::Resize(U32 SizeWidth, U32 SizeHeight)
	{
		GDynamicRHI->RHIResizeViewport(MainViewport, SizeWidth, SizeHeight, RHIPixelFormat::R8G8BA8_UNORM, false);
	}
	void ViewportClient::BeginFrame()
	{
		GDynamicRHI->RHIBegin(MainViewport);

	}
	void ViewportClient::EndFrame()
	{
		GDynamicRHI->RHIEnd(MainViewport);
	}
}