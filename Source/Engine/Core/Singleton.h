#ifndef SINGLETON_H
#define SINGLETON_H

namespace MeteorEngine
{
	template<typename T>
	class Singleton
	{
	public:
		Singleton() = default;
		static T* GetInstance()
		{
			static T* instance;
			return instance;
		}
	};
}
#endif // !SINGLETON_H
