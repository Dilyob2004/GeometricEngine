#ifndef APPLICATION_H
#define APPLICATION_H
#include <Engine/Core/Config.h>
#include <Engine/Core/Window.h>
#include <Engine/Core/LayerStack.h>
#include <Engine/Render/Renderer.h>
#include <Engine/Core/Core.h>
#include <memory>
namespace MeteorEngine
{
	class METEOR_API Application
	{
	public:
		static Application& GetInstance() { return *m_ThisInstance; }
		Application();
		virtual ~Application();

		u32 GetX() const { return m_Window->GetPosition().x; }
		u32 GetY() const { return m_Window->GetPosition().y; }
		u32 GetWidth() const { return m_Window->GetSize().x; }
		u32 GetHeight() const { return m_Window->GetSize().y; }

		static void Close();
		bool ShouldExit();
		void Run();
		void OnEvent(Event& );
		Window& GetWindow() { return *m_Window; }
		void PushLayer(Layer*);
		void PushOverlay(Layer*);
	private:
		std::shared_ptr<RenderContext>	m_Context;
		std::shared_ptr<Window>		m_Window;
	private:
        static Application *            m_ThisInstance;
		LayerStack						m_LayerStack;
    };
}

#endif // APPLICATION_H
