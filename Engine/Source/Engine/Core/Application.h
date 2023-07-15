#ifndef APPLICATION_H
#define APPLICATION_H

#if defined DEBUG_EDITOR || RELEASE_EDITOR
#include <Editor/Editor.h>
typedef Editor Application;
#else
#include <Engine/Core/Engine.h>
typedef Engine Application;
#endif
#endif // APPLICATION_H
