#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <Engine/Render/CameraController2D.h>
#include <Engine/Math/MathUtils.h>
#include <Editor/ScriptLayer.h>


#include <functional>
namespace MeteorEngine
{

	struct Transform
	{
		Transform() = default;
		Transform(const Transform&) = default;
		Matrix4f GetTransform() const
		{
			Quaternion q(rotation);
			Matrix4f rotation = toMatrix4(q);
			return Translate(Matrix4f::Identity, position)* rotation* Scale(Matrix4f::Identity, scale);
		}
		Vector3f position{ 0, 0, 0 };
		Vector3f rotation{ 0, 0, 0 };
		Vector3f scale{ 1, 1, 1 };


		Matrix4f matrixTransform;
	};
	struct SpriteRenderer
	{
		SpriteRenderer() = default;
		SpriteRenderer(const SpriteRenderer&) = default;
		Vector4f color{ 1, 1, 1, 1 };
	};

	struct Tag
	{
		Tag() = default;
		Tag(const Tag&) = default;
		std::string tag = "";
	};
	struct NativeScript
	{
		ScriptLayer* Instance = NULL;

		std::function<void()> InstantiateFunction;
		std::function<void()> DestroyFunction;


		//std::function<void(ScriptLayer*)> EnableFunction;
		//std::function<void(ScriptLayer*)> AwakeFunction;
		//std::function<void(ScriptLayer*)> StartFunction;

		std::function<void(ScriptLayer*)> UpdateFunction;
		//std::function<void(ScriptLayer*)> FixedUpdateFunction;
		//std::function<void(ScriptLayer*)> LateUpdateFunction;

		//std::function<void(ScriptLayer*)> DisableFunction;

		template<typename T>
		void Bind()
		{
			InstantiateFunction = [&]() {Instance = new T(); };
			DestroyFunction = [&]() { delete (T*)Instance; Instance = NULL; };



			//EnableFunction = [](ScriptLayer * layer) { ((T*)layer)->OnEnable(); };
			//DisableFunction = [](ScriptLayer * layer) { ((T*)layer)->OnDisable(); };

			//AwakeFunction = [](ScriptLayer * layer) { ((T*)layer)->OnAwake(); };
			//StartFunction = [](ScriptLayer * layer) { ((T*)layer)->OnStart(); };

			UpdateFunction = [](ScriptLayer * layer) { ((T*)layer)->OnUpdate(); };
			//FixedUpdateFunction = [](ScriptLayer * layer) { ((T*)layer)->OnFixedUpdate(); };
			//LateUpdateFunction = [](ScriptLayer * layer) { ((T*)layer)->OnLateUpdate(); };
			

		}
	};
	struct SceneCamera
	{
	};
	/*
	void OnEnable()
	{
	}

	void OnStart()
	{

	}
	void OnUpdate()
	{
	}
	
	void OnFixedUpdate()
	{
	}
	void OnLateUpdate()
	{
	}

	void OnDisable()
	{
	}

	
	
	*/
}

#endif