#ifndef SINGLETON_H
#define SINGLETON_H

namespace MeteorEngine
{
	template<typename T>
	class Singleton
	{
	public:
		static T* GetInstance() 
		{

			static T* instance = new T();
			return instance; 
		}
	};
}
#endif // !SINGLETON_H
