#include <Engine/Core/Application.h>
#ifdef METEOR_DEBUG

	int main(int argc, char* argv[])
	{
		return MeteorEngine::Main({ argc, argv });
	}

#else

	int WINAPI WinMain(_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ PSTR    lpCmdLine,
		_In_ int       nCmdShow)
	{
		return MeteorEngine::Main({ lpCmdLine });
	}
#endif