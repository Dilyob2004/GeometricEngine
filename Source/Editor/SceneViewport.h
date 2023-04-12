#ifndef SCENEVIEWPORT_H
#define SCENEVIEWPORT_H

#include <Engine/RHI/DynamicRHI.h>
#include <Engine/Core/Misc/References.h>
#include <Engine/Renderer/Camera.h>
#include <Engine/Math/Vector2.h>

namespace GeometricEngine
{
	class GEOMETRIC_API SceneViewport
	{
	public:
		SceneViewport();
		~SceneViewport();


		void OnDrawSceneViewport();
		void OnDrawRenderer();


	private:

		void InitRenderTarget();

		RHITexture2D* RenderTarget;
		RHITexture2D* DepthTarget;
		Vector2f SceneViewSize{1280, 720};
		Camera SceneCamera;

		TSharedPtr<RHIBlendState> BlendState;
		TSharedPtr<RHIRasterizerState> RasterizerState;
		TSharedPtr<RHIDepthStencilState> DepthStencilState;

	};
}
#endif // !SCENEVIEWPORT_H
