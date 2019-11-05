#pragma once
#include <assert.h>
#include <windows.h>
#include <string>
#include <functional>
#include "utils/timer.hpp"
#include "core/image.hpp"

class App
{
public:
	App();
	App(int width, int height);
	~App();
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	static App* GetApp();
	bool Initialize();
	void Run(std::function<void(Image*)>);
	void SingleFrame(std::function<void(Image*)>);
	LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	Timer m_timer;
	bool m_appPaused;
	static App* m_app;
	HWND m_hMainWnd = nullptr;
	HDC m_memoryDC;
	std::wstring m_mainWndCaption = L"Soft Render Engine";
	double m_clientWidth = 800;
	double m_clientHeight = 600;
	Image* m_surface;

	bool InitMainWindow();
	HDC CreateSurface();
	void Render();

	typedef enum {BUTTON_L, BUTTON_R, BUTTON_MID} button_t;
	void OnKeyDown(WPARAM key);
	void OnKeyUp(WPARAM key);
	void OnMouseDown(button_t button, int x, int y);
	void OnMouseUp(button_t button, int x, int y);
	void OnMouseScroll(float scroll);
	void OnMouseMove(WPARAM btnState, int x, int y);

};
