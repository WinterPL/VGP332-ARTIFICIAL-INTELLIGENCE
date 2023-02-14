#pragma once

#include "Common.h"
#include "RCore.h"

namespace REng
{
extern void Start(const char* windowTitle);
extern void Start(const char* windowTitle, int width, int height);
extern void Run(bool (*gameLoop)(), void (*uiDebugUpdate)());
extern void Run(bool (*gameLoop)());
extern void Stop();
extern std::string ResourcesFullPath(const std::string& imageName);
}
