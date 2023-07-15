#pragma once


#include <Engine/Core/Misc/String.h>

enum class EAssetType
{
	Texture
};
class FAssetData
{
public:
	FAssetData() {}
	FAssetData(	String InPackageName,
				String InAssetName,
				String InAssetPath) 
	{
		PackageName = InPackageName;
		AssetName = InAssetName;
		AssetPath = InAssetPath;
	}

	String PackageName;
	String AssetName;
	String AssetPath;
};



class FAssetRegistry
{
public:

};