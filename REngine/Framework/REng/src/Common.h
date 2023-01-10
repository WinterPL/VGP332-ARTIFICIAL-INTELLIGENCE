#pragma once

#include <assert.h>
#include <imgui.h>
#include <iostream>
#include <math.h>
#include <raylib.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

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
