

#include <Engine/Core/Core.h>
#include <Engine/Core/Generic/Platform.h>
#include <Engine/Core/Containers/Array.h>
#include <Engine/Core/Types/String.h>
namespace GeometricEngine
{
	int GuardedMain(void* hInstance, const CHAR* cmdLine)
	{
		String str("1111");
		str = str.Replace("1", "0");
		//str = str.Replace("1", "2");
		std::cout << *str << "\n" << str.Size();
		//Platform::PreInit(hInstance);
	//	std::string s1 = "1234", s2 = "1334";

//		std::cout << CString::Compare(s1.data(), s2.data());
		/**TVector<int> Elements;
		Elements.Resize(2);
		Elements.Push(10);
		Elements.Push(20);
		for (auto i : Elements)
			std::cout << i << " ";
		std::cout << "\n";


		Elements.Resize(5);
		Elements.Push(30);
		for (auto i : Elements)
		{
			std::cout << i << " ";
		}*/
		return 0;
	}
}