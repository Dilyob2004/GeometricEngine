#ifndef VIEWPORTCLIENT_H
#define VIEWPORTCLIENT_H
#include <Engine/RHI/DynamicRHI.h>
namespace GeometricEngine
{
	class GEOMETRIC_API ViewportClient
	{
	public:

		ViewportClient();
		~ViewportClient();
		void Initialize();
		void BeginFrame();
		void EndFrame();
		void Resize(U32 SizeWidth, U32 SizeHeight);

		RHIViewport* GetMainViewport() const
		{
			return MainViewport;
		}
	private:

		RHIViewport* MainViewport;
	};
	extern ViewportClient* GClient;
}

#endif