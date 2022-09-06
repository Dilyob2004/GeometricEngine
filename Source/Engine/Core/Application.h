#ifndef APPLICATION_H
#define APPLICATION_H
#include <Engine/Core/Config.h>
#include <Engine/Core/Window.h>
#include <Engine/Core/LayerStack.h>
#include <Engine/Render/OpenGL/OpenGLContext.h>
#include <Engine/Render/OpenGL/OpenGLShader.h>
#include <Engine/Core/Core.h>
#include <memory>
namespace MeteorEngine
{
	class METEOR_API Application
	{
	public:
		static Application& GetInstance() { return *m_instance; }
		Application();
		virtual ~Application();

		u32 GetWidth() const;
		u32 GetHeight() const;


		void Run();
		void OnEvent(Event& );
		Window& GetWindow() { return *m_window; }
		OpenGLContext& GetContext() { return *m_context; }

		void PushLayer(Layer*);
		void PushOverlay(Layer*);
	private:
		std::shared_ptr<OpenGLContext>  m_context;
		std::shared_ptr<Window>         m_window;
	private:
		Event                           m_event {};
        LayerStack                      m_layerStack;
        static Application *            m_instance;
    };
}

#endif // APPLICATION_H
