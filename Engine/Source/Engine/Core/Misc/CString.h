#ifndef CSTRING_H
#define CSTRING_H
#include <Engine/Core/Config.h>

enum class ESearchCase
{
	Sensitive,
	InSensitive,
};
class GEOMETRIC_API CString
{
public:
	static bool IsDigit(Char);
	static bool IsLower(Char);
	static bool IsUpper(Char);
	static Char ToLower(Char);
	static Char ToUpper(Char);
		
	static I32		Length(const Char*);
	static I32		Length(const CharAnsi*);
	static Char*	Copy(Char*, const Char*);
	static CharAnsi*	Copy(CharAnsi*, const CharAnsi*);

	static F32 Atof(const CharAnsi*);
	static I32 Atoi(const CharAnsi*);
	static I128 Atoll(const CharAnsi*);



	static I32 Compare(const CharAnsi*, const CharAnsi*);
	static I32 Compare(const CharAnsi*, const CharAnsi*, I32);
	static I32 CompareCaseInSensitive(const CharAnsi*, const CharAnsi*);
	static I32 CompareCaseInSensitive(const CharAnsi*, const CharAnsi*, I32);


	static I32 Compare(const Char*, const Char*);
	static I32 Compare(const Char*, const Char*, I32);
	static I32 CompareCaseInSensitive(const Char*, const Char*);
	static I32 CompareCaseInSensitive(const Char*, const Char*, I32);


	static const CharAnsi* Find(const CharAnsi*, const CharAnsi*);
	static const Char* Find(const Char*, const Char*);



	static const CharAnsi* FindCaseInSensitive(const CharAnsi*, const CharAnsi*);
	static const Char* FindCaseInSensitive(const Char*, const Char*);


	static void ConvertAnsiToWide(const CharAnsi*, Char*, I32 Len);
	static void ConvertWideToAnsi(const Char*, CharAnsi*, I32 Len);
};
#endif // !CSTRING_H
