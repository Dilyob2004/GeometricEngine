#pragma once

#include <Engine/RHI/DynamicRHI.h>

class GEOMETRIC_API ContentBrowserEditor
{
public:
	ContentBrowserEditor();
	~ContentBrowserEditor();


	void OnTick();
	void OnPaint();

private:
	RHITexture2D* DirectoryTexture;
	RHITexture2D* FileTexture;
};

