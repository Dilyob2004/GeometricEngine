#include <Engine/Core/Config.h>

namespace GeometricEngine
{
	template<typename T>
	class GEOMETRIC_API TQueue
	{
	public:
		TQueue()
		{
			Count = 0;
			Trail = Head = new Node();
		}
		~TQueue()
		{
			while (Trail != NULL)
			{
				Node* Data = Trail;
				Trail = Trail->NextData;
				delete Data;
			}
		}
		void Push(const T& Element)
		{
			Node* NewNode = new Node(Element);
			if (NewNode != NULL)
			{
				Node* OldHead = Head;
				Head = NewNode;
				OldHead->NextData = NewNode;
				Count++;
			}
		}
		void Pop()
		{
			Node* Data = Trail->NextData;

			if (Data != NULL)
			{
				Node* OldTrail = Trail;
				Trail = Data;
				Trail->Data = T();
				delete OldTrail;
				Count--;
			}
		}
		void Clear()
		{
			while (!IsEmpty())
				Pop();
		}
		T Front()
		{
			_ASSERT(Trail->NextData != NULL);
			return Trail->NextData->Data;
		}
		T Bottom()
		{
			_ASSERT(Head->Data != NULL);
			return Head->Data;
		}
		T& Peek()
		{
			_ASSERT(Trail->NextData != NULL);
			return Trail->NextData->Data;
		}
		bool IsEmpty() const
		{
			return (Trail->NextData == NULL);
		}
		I32 Size() const
		{
			return Count;
		}
	private:
		struct Node
		{
			Node* volatile NextData;
			T Data;
			Node() 
				: NextData(NULL)
				, Data()
			{
			}
			Node(const T& Element) 
				: NextData(NULL)
				, Data(Element)
			{
			}
		};
		Node* Head;
		Node* Trail;

		U32 Count;
	};
}