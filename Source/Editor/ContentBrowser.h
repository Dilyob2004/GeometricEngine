#ifndef CONTENTBROWSER_H
#define CONTENTBROWSER_H
#include <Engine/Render/Texture.h>
namespace MeteorEngine
{
	class METEOR_API ContentBrowser
	{
	public:
		ContentBrowser();
		~ContentBrowser();


		void OnUpdate();

		static void SetActive(bool);
	private:

		std::string m_currentPath;
		Texture2D* m_DirectoryIcon;
		Texture2D* m_FileIcon;

	};
}
#endif // ! 
