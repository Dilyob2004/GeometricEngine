#ifndef EDITOR_H
#define EDITOR_H
#include <Engine/Core/Layer.h>
#include <Engine/Render/FrameBuffer.h>
#include <Engine/Render/Camera.h>
#include <Engine/Render/Texture.h>
#include <Editor/Entity.h>
#include <Editor/SceneHierarchy.h>
#include <Editor/ContentBrowser.h>
#include <Engine/System/Clock.h>
#include <Editor/Console.h>
#include <memory>
namespace MeteorEngine
{
    class METEOR_API Editor : public Layer
    {
    public:
        Editor();
        ~Editor();
        virtual void OnAttach();
        virtual void OnDetach();
        virtual void OnTick();
        virtual void OnEvent(Event &);


		static void SetViewPort(bool);
		static void SetSceneHierarchy(bool);
		static void SetProperties(bool);
		static void SetContentBrowser(bool);
		static void SetConsole(bool);
    private:
		Camera					m_cameraController;
        Vector2u							m_viewPortSize = {1200, 720};
        Clock								m_clock;

		std::shared_ptr <Scene>				m_scene;
		std::shared_ptr <Console>			m_console;
		std::shared_ptr <SceneHierarchy>	m_hierarchy;
		std::shared_ptr <ContentBrowser>	m_contentBrowser;
		std::shared_ptr<FrameBuffer>		m_frameBuffer;
    };
}
#endif // EDITOR_H
