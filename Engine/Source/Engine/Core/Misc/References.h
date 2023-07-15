#ifndef REFERENCES_H
#define REFERENCES_H
#include <Engine/Core/Config.h>
#include <memory>

template<typename T>
class GEOMETRIC_API TRefCountSlot
{
public:
	TRefCountSlot() : Count(0) { }
	virtual ~TRefCountSlot() { }
	U32 Ref() const
	{
		return U32(++Count);
	}
	U32 UnRef()
	{
		U32 Refs = U32(--Count);
		if (!Refs)
			delete this;
		return Refs;
	}

	U32 GetRefCount() const
	{
		return Count;
	}
private:
	mutable int Count;
};
template<typename RefType>
class TRefCount
{
public:
	FORCEINLINE TRefCount()
		: Object(NULL)
	{
	}
	TRefCount(RefType* RefObject, bool IsAddRef = true)
		: Object(RefObject)
	{
		if (Object && IsAddRef)
			Object->AddRef();
	}

	TRefCount(const TRefCount& RefObject)
	{
		Object = RefObject.Object;
		if (Object)
			Object->AddRef();
	}
	TRefCount(TRefCount&& RefObject)
	{
		Object = RefObject.Object;
		RefObject.Object = NULL;
	}
	~TRefCount()
	{
		if (Object)
			Object->UnRef();
	}
	RefType* operator->()
	{
		return Object;
	}
	operator RefType* () const
	{
		return Object;
	}
	TRefCount& operator = (const RefType* Ref)
	{
		RefType* OldRef = Object;
		Object = Ref;

		if (Object) Object->Ref();
		if (OldRef) OldRef->UnRef();

		return *this;
	}
	TRefCount& operator = (const TRefCount& Ref)
	{
		return *this = Ref.Object;
	}
	bool operator == (const TRefCount& Ref)
	{
		return Object == Ref.Object;
	}
	RefType* GetRef() const
	{
		return Object;
	}
	RefType** GetInitRef()
	{
		*this = NULL;
		return &Object;
	}
	void Release()
	{
		*this = NULL;
	}
	U32 GetRefCount() const
	{
		if (Object)
		{
			Object->Ref();
			return Object->UnRef();
		}
		else
			return 0;
	}
	void Swap(TRefCount& Ref)
	{
		RefType* OldRef = Object;
		Object = Ref.Object;
		Ref.Object = OldRef;
	}
private:
	RefType* Object;
};
template<typename T>
class TRef
{
public:
		


	T* Data = NULL;

};

template<typename T>
using TScopePtr = std::unique_ptr<T>;

template<typename T, typename ... Args>
constexpr TScopePtr<T> MakeScope(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using TSharedPtr = std::shared_ptr<T>;

template<typename T, typename ... Args>
constexpr TSharedPtr<T> MakeShared(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}
#endif // !REFERENCES_H
