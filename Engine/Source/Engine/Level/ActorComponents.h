#ifndef ACTORCOMPONENTS_H
#define ACTORCOMPONENTS_H
#include <Engine/Math/MathUtils.h>
#include <Engine/Math/Quaternion.h>
#include <Engine/Math/Vector2.h>
#include <Engine/Core/Misc/String.h>
#include <Engine/RendererCore/Sprite.h>
#include <Engine/Renderer/Camera.h>

struct Transform2DComponent
{
	Transform2DComponent() = default;
	Vector2f Position{0, 0};
	F32 Rotation{ 0};
	Vector2f Scale {1, 1};
};
struct SpriteRendererComponent
{
	SpriteRendererComponent() = default;
	FSprite* Sprite = NULL;
	Vector4f Color{1, 1, 1, 1};
	bool Flip = false;
};
struct IDComponent
{
	IDComponent() = default;
	U64 Value = 0;
};
struct NameComponent
{
	NameComponent() = default;
	String Name = "EmptyActor";
};
struct CameraComponent
{
	CameraComponent() = default;
	FLevelCamera Camera;
};
#endif // !ACTORCOMPONENTS_H
