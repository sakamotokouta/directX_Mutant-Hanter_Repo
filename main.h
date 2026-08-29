#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define NOMINMAX
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <functional>



#pragma warning(push)
#pragma warning(disable:4005)

#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>

#pragma warning(pop)



#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")



//ImGUI
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"



#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)



HWND GetWindow();

float GetCursorX(void);
float GetCursorY(void);

bool GetPozFlg(void);

int GetFlam(void);

void SetFlam(float flame);
