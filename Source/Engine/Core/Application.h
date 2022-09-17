#ifndef APPLICATION_H
#define APPLICATION_H
#include <Engine/Core/Config.h>
#include <Engine/Core/Window.h>
#include <Engine/Core/LayerStack.h>
#include <Engine/Render/RenderContext.h>
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

		u32 GetX() const { return m_window->GetPosition().x; }
		u32 GetY() const { return m_window->GetPosition().y; }
		u32 GetWidth() const { return m_window->GetSize().x; }
		u32 GetHeight() const { return m_window->GetSize().y; }
		static void Exit();
		bool ShouldExit();
		void Run();
		void OnEvent(Event& );
		Window& GetWindow() { return *m_window; }
		RenderContext& GetContext() { return *m_context; }

		void PushLayer(Layer*);
		void PushOverlay(Layer*);
	private:
		std::shared_ptr<RenderContext>  m_context;
		std::shared_ptr<Window>         m_window;
	private:
        static Application *            m_instance;
    };
}

#endif // APPLICATION_H
