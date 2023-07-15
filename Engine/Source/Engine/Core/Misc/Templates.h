#ifndef TEMPLATES_H
#define TEMPLATES_H
template<bool Predicate, typename Result = void>
struct TEnableIf;

template<typename Result>
struct TEnableIf<true, Result>
{
	typedef Result Type;
};

template<typename Result>
struct TEnableIf<false, Result>
{
};


template<typename T> struct TRemoveReference { typedef T Type; };
template<typename T> struct TRemoveReference<T&> { typedef T Type; };
template<typename T> struct TRemoveReference<T&&> { typedef T Type; };




#endif // !TEMPLATES_H
