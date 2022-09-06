#ifndef  SCRIPTLAYER_H
#define SCRIPTLAYER_H
#include <Editor/Entity.h>

namespace MeteorEngine
{
	class ScriptLayer
	{
	public:
		/**virtual void OnEnable() = 0;
		virtual void OnAwake() = 0;
		virtual void OnStart() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnFixedUpdate() = 0;
		virtual void OnLateUpdate() = 0;
		virtual void OnDisable() = 0;*/


	private:
		Entity m_entity;
		friend class Scene;
	};
}
#endif // ! SCRIPTLAYER_H
