#include "main.h"
#include "manager.h"
#include <thread>
#include "input.h"

const char* CLASS_NAME = "AppClass";
const char* WINDOW_NAME = "DX11ゲーム";
POINT LastCursolPos;
POINT CursolPos;
bool g_Porz{};
float g_Flame = 60;


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


HWND g_Window;

HWND GetWindow()
{
	return g_Window;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{


	WNDCLASSEX wcex;
	{
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = 0;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = nullptr;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = nullptr;
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm = nullptr;

		RegisterClassEx(&wcex);


		RECT rc = { 0, 0, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

		g_Window = CreateWindowEx(0, CLASS_NAME, WINDOW_NAME, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);
	}



	Manager::Init();
	GetCursorPos(&LastCursolPos);

	ShowWindow(g_Window, nCmdShow);
	UpdateWindow(g_Window);




	DWORD dwExecLastTime;
	DWORD dwCurrentTime;
	timeBeginPeriod(1);
	dwExecLastTime = timeGetTime();
	dwCurrentTime = 0;



	MSG msg;
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / g_Flame))
			{
				dwExecLastTime = dwCurrentTime;


				GetCursorPos(&CursolPos);

				if (!g_Porz) {
					SetCursorPos(LastCursolPos.x, LastCursolPos.y);
					ShowCursor(false);
				}
				else
				{
					ShowCursor(true);
				}

				if (Input::GetKeyTrigger('O'))
				{
					g_Porz = !g_Porz;
				}

				//SetCursorPos(LastCursolPos.x, LastCursolPos.y);

				Manager::Update();
				Manager::Draw();
			}
		}
	}

	timeEndPeriod(1);

	UnregisterClass(CLASS_NAME, wcex.hInstance);

	Manager::Uninit();

	return (int)msg.wParam;
}


//ImGUIのウィンドウ処理をプロシージャに追加
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	//ImGUIのウィンドウ処理をプロシージャに追加
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

float GetCursorX(void)
{
	return CursolPos.x - LastCursolPos.x;
}
float GetCursorY(void)
{
	return CursolPos.y - LastCursolPos.y;
}

bool GetPozFlg(void) {
	return g_Porz;
}
int GetFlam(void) {
	return g_Flame;
}
void SetFlam(float flame){
	g_Flame = flame;
}
