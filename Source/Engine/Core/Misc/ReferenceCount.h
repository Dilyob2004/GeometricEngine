#ifndef REFERENCECOUNT_H
#define REFERENCECOUNT_H
#include <Engine/Core/Config.h>
namespace GeometricEngine
{


	template<typename T>
	class RefCount
	{
	public:
		FORCEINLINE RefCount()
			: Object(NULL)
		{
		}
		RefCount(T* RefObject, bool IsAddRef = true)
			: Object(RefObject)
		{
			if (Object && IsAddRef)
				Object->AddRef();
		}

		RefCount(const RefCount& RefObject)
		{
			Object = RefObject.Object;
			if (Object)
				Object->AddRef();
		}
		RefCount(RefCount&& RefObject)
		{
			Object = RefObject.Object;
			RefObject.Object = NULL;
		}
		~RefCount()
		{
			if (Object)
				Object->Release();
		}
	private:
		T* Object;
	};
}
#endif // !REFERENCECOUNT_H
