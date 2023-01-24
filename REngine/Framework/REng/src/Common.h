#pragma once

#include <assert.h>
#include <imgui.h>
#include <iostream>
#include <functional>
#include <fstream>
#include <math.h>
#include <raylib.h>
#include <string>
#include <sstream>
#include <vector>

#include <rlgl.h>
#ifdef PLATFORM_DESKTOP
#include <GLFW/glfw3.h>
#endif

#ifndef NO_FONT_AWESOME
#include <FA6FreeSolidFontData.h>
#endif

#ifndef NO_FONT_AWESOME
#include <IconsFontAwesome6.h>
#define FONT_AWESOME_ICON_SIZE 11
#endif