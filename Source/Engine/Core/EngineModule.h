#ifndef ENGINEMODULE_H
#define ENGINEMODULE_H
#include <Engine/Core/Config.h>
#include <Engine/Core/Containers/Array.h>
#include <Engine/Core/Misc/Log.h>
namespace GeometricEngine
{
	class EngineModule
	{
	public:
		virtual ~EngineModule() = default;
		static TVector<EngineModule*>& GetModule()
		{
			static TVector<EngineModule*> Result;
			return Result;
		}
		CHAR* GetModuleName() const
		{
			return ModuleName;
		}
		static bool OnInitialize()
		{
			for (auto i : GetModule())
				if (!i->Initialize())
				{
					LOG("Failed to initialized InputModule!\n");
					return false;
				}
				else 
				{
					LOG(i->GetModuleName());
					LOG(" has initialized!\n");
				}

			return true;
		}
		static void OnTick()
		{
			for (auto i : GetModule())
				i->Tick();
		}
		static void OnLateTick()
		{
			for (auto i : GetModule())
				i->LateTick();
		}
		static void OnDeInitialize()
		{
			for (auto i : GetModule())
				i->DeInitialize();



			LOG("InputModule Has UnInitizlized!\n");
		}
	protected:

		EngineModule(const CHAR* Name)
			: ModuleName((CHAR*)Name)
		{
			auto& StackModule = GetModule();
			StackModule.Push(this);
		}
	public:
		virtual bool Initialize() { return false; }
		virtual void Tick() {};
		virtual void LateTick() {};
		virtual void Draw() {};
		virtual void DeInitialize() {};


		TVector<EngineModule*> Module;
		CHAR* ModuleName;
	};
}

#endif // !ENGINEMODULE_H
