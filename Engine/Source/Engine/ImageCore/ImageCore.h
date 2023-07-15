#ifndef IMAGECORE_H
#define IMAGECORE_H

#include <Engine/Core/Misc/String.h>
#include <Engine/Core/Containers/Array.h>
class GEOMETRIC_API Image
{
public:
	Image();
	Image(const Image&);
	~Image();
	bool Load(const String&);
	U32 GetWidth() const { return Width; }
	U32 GetHeight() const { return Height; }
	U8* GetRawData() { return Data.Pointer(); }
	const U8* GetRawData() const { return Data.Pointer(); }
	const TArray<U8>& GetData() const { return Data; }
private:
	U32 Width, Height;
	TArray<U8> Data;
};

#endif // IMAGECORE_H
