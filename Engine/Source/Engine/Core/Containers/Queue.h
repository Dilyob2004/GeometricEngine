#include <Engine/Core/Config.h>
#include <Engine/Core/Misc/AssertionMacros.h>

template<typename T>
class TQueue
{
public:
	TQueue()
	{
		Count = 0;
		Trail = Head = new Node();
	}
	~TQueue()
	{
		while (Trail != nullptr)
		{
			Node* Data = Trail;
			Trail = Trail->NextData;
			delete Data;
		}
	}
	void Push(const T& Element)
	{
		Node* NewNode = new Node(Element);
		if (NewNode != nullptr)
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

		if (Data != nullptr)
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
		Check(Trail->NextData != nullptr);
		return Trail->NextData->Data;
	}
	T Bottom()
	{
		Check(Head->Data != nullptr);
		return Head->Data;
	}
	T& Peek()
	{
		Check(Trail->NextData != nullptr);
		return Trail->NextData->Data;
	}
	bool Peek(T& OutItem)
	{
		if (Trail->NextData != nullptr)
		{
			OutItem = Trail->NextData->Data;
			return true;
		}
		return false;
	}
	bool IsEmpty() const
	{
		return (Trail->NextData == nullptr);
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
			: NextData(nullptr)
			, Data()
		{
		}
		Node(const T& Element) 
			: NextData(nullptr)
			, Data(Element)
		{
		}
	};
	MS_ALIGN(16) Node*volatile Head;
	Node* Trail;

	U32 Count;
};
