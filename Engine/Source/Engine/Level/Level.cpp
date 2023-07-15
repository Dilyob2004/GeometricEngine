#include "Level.h"
#include "Actor.h"
#include "ActorComponents.h"
#include <Engine/Renderer/Renderer2D.h>
#include <Engine/Core/Misc/Log.h>
#include <Engine/Core/Generic/File.h>
#include <Engine/Core/Generic/Path.h>
#include <Engine/JsonCore/JsonCore.h>




FSprite* DummySprite;


bool IsPlaying = false;

FLevel::FLevel()
	: Name("")
	, MainCamera(EditorCamera())
{
}
FLevel::FLevel(const String& InName)
	: Name(InName)
	, MainCamera(EditorCamera())
{
	DummySprite = new FSprite(SPath::GetEngineContentDir() + "/Textures/Engine/Sprites/Square.png");
	
	MakeSquadActor();
	MakeCameraActor();
}
FLevel::~FLevel()
{

}
Actor FLevel::MakeActor(const String& Name)
{
	auto Registry = HandleRegistry.create();
	Actor NewActor(Registry, this);
	NewActor.AddComponent<IDComponent>().Value = (U32)Registry;
	NewActor.AddComponent<NameComponent>().Name = Name;
	NewActor.AddComponent<Transform2DComponent>();
	return NewActor;
}
Actor FLevel::MakeCameraActor()
{
	auto Registry = HandleRegistry.create();
	Actor NewActor(Registry, this);
	NewActor.AddComponent<IDComponent>().Value = (U32)Registry;
	NewActor.AddComponent<NameComponent>().Name = "Camera";
	NewActor.AddComponent<Transform2DComponent>();
	NewActor.AddComponent<CameraComponent>();
	return NewActor;
}
Actor  FLevel::MakeSquadActor()
{
	auto Registry = HandleRegistry.create();
	Actor NewActor(Registry, this);
	NewActor.AddComponent<IDComponent>().Value = (U32)Registry;
	NewActor.AddComponent<NameComponent>().Name = "Square";
	NewActor.AddComponent<Transform2DComponent>();
	NewActor.AddComponent<SpriteRendererComponent>().Sprite = DummySprite;
	return NewActor;
}
void FLevel::RemoveActor(Actor ActiveActor)
{
	HandleRegistry.destroy(ActiveActor);
}

void FLevel::OnTick()
{
	MainCamera.OnTick(0.5f);
}
void FLevel::OnResize(const Vector2f& Size)
{
	MainCamera.OnResize(Size);
	auto View = HandleRegistry.view<CameraComponent>();
	for (auto [AActor, CameraValue] : View.each())
	{
		CameraValue.Camera.OnResize(Size);
	}
}
void FLevel::OnDrawActors()
{
	
	Camera* CurrentCamera = nullptr;



	if(IsPlaying)
	{
		auto View = HandleRegistry.view<CameraComponent, Transform2DComponent>();
		for (auto [AActor, CameraValue, Transform] : View.each())
		{
			CurrentCamera = &CameraValue.Camera;
		}
	}
	else
		CurrentCamera = &MainCamera;
			 
	if (CurrentCamera) 
	{
		Renderer2D::BeginFrame(*CurrentCamera);

		auto View = HandleRegistry.view<Transform2DComponent, SpriteRendererComponent>();

		for (auto [AActor, Transform, SpriteRender] : View.each())
		{
			Renderer2D::DrawSprite(SpriteRender.Sprite, SpriteRender.Color, Transform.Position, Transform.Rotation, Transform.Scale);
		}

		Renderer2D::EndFrame();
	}
			
	
}
void SerializeTransform(Writer<StringBuffer>& Writer, Transform2DComponent Component)
{
	Writer.Key("Transform");
		Writer.StartObject();
		Writer.Key("Position");
		Writer.String(*String::Format("%f %f", Component.Position.x, Component.Position.y));
		Writer.Key("Rotation");
		Writer.Double((double)Component.Rotation);
		Writer.Key("Scale");
		Writer.String(*String::Format("%f %f", Component.Scale.x, Component.Scale.y));
	Writer.EndObject();
}
void SerializeNameComponent(Writer<StringBuffer>& Writer, NameComponent Component)
{
	Writer.Key("Name");
	Writer.String(*Component.Name);
}
void SerializeSpriteRendererComponent(Writer<StringBuffer>& Writer, SpriteRendererComponent Component)
{
	Writer.Key("SpriteRenderer");
	Writer.StartObject();
	Writer.Key("Texture");
	Writer.String(*Component.Sprite->GetPath());

	Writer.Key("Color");
	Writer.String(*String::Format("%f %f %f %f", Component.Color.x, Component.Color.y, Component.Color.z, Component.Color.w));

	Writer.EndObject();
}
void SerializeActor(Writer<StringBuffer> &Writer, Actor AActor)
{

	Writer.StartObject();
	Writer.Key("Components");
	Writer.StartObject();
		SerializeNameComponent(Writer, AActor.GetComponent<NameComponent>());
		SerializeTransform(Writer, AActor.GetComponent<Transform2DComponent>());
		SerializeSpriteRendererComponent(Writer, AActor.GetComponent<SpriteRendererComponent>());
	Writer.EndObject();
	Writer.EndObject();

}
void FLevel::Serialize(const String& Path)
{
	StringBuffer  Buffer;
	Writer<StringBuffer> Writer(Buffer);
	Writer.StartObject();
		Writer.Key("Actors");
		Writer.StartArray();
			HandleRegistry.each([&](auto AActor)
			{
				Actor NewActor(AActor, this);
				SerializeActor(Writer, NewActor);
			});
		Writer.EndArray();
	Writer.EndObject();

	File* JsonFile = File::Create(Path, FileMode::CreateAlways, FileAccess::Write, FileShare::Read);
	U32 OutSize;
	JsonFile->Write(Buffer.GetString(), (U32)Buffer.GetSize(), &OutSize);
	JsonFile->Close();
	delete JsonFile;
	JsonFile = nullptr;
}
void FLevel::Deserialize(const String& Path)
{
	File* JsonFile = File::Create(Path, FileMode::OpenAlways, FileAccess::Read, FileShare::Read);
	String Buffer;
	U32 OutSize;
	Buffer.Resize(JsonFile->GetSize());
	JsonFile->Read(*Buffer, Buffer.Size(), &OutSize);
	JsonFile->Close();
	delete JsonFile;
	JsonFile = nullptr;
	
	Document JsonDocument;
	JsonDocument.Parse(*Buffer);


	for (auto i = JsonDocument["Actors"].Begin(); i != JsonDocument["Actors"].End(); i++)
	{
		Actor EmptyActor = MakeActor("Empty");
		for (Value::ConstMemberIterator Components = (*i).MemberBegin(); Components != (*i).MemberEnd(); ++Components)
		{
			for (Value::ConstMemberIterator Component = (*Components).value.MemberBegin(); Component != (*Components).value.MemberEnd(); ++Component)
			{
				if (CString::Compare(Component->name.GetString(), "Name") == 0)
				{
					EmptyActor.GetComponent<NameComponent>().Name = Component->value.GetString();
				}
				if (CString::Compare(Component->name.GetString(), "Transform") == 0)
				{
					TArray<String> Position = String(Component->value["Position"].GetString()).Split(' ');
					EmptyActor.GetComponent<Transform2DComponent>().Position = Vector2f(Position[0].ToFloat(), Position[1].ToFloat());


					EmptyActor.GetComponent<Transform2DComponent>().Rotation = (F32)Component->value["Rotation"].GetDouble();

					TArray<String> Scale = String(Component->value["Scale"].GetString()).Split(' ');
					EmptyActor.GetComponent<Transform2DComponent>().Scale = Vector2f(Scale[0].ToFloat(), Scale[1].ToFloat());
				}
				if (CString::Compare(Component->name.GetString(), "SpriteRenderer") == 0)
				{
					TArray<String> Color = String(Component->value["Color"].GetString()).Split(' ');
					EmptyActor.AddComponent<SpriteRendererComponent>();
					EmptyActor.GetComponent<SpriteRendererComponent>().Sprite = new FSprite(Component->value["Texture"].GetString());
					EmptyActor.GetComponent<SpriteRendererComponent>().Color = Vector4f(Color[0].ToFloat(), Color[1].ToFloat(), Color[2].ToFloat(), Color[3].ToFloat());
				}
			}

		}
	}
}
