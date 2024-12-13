#include <Windows.h>
#include <string>
#include <D3D11.h>
#include <vector>
#include <dxgi1_6.h>

#pragma comment(lib, "D3D11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#pragma comment(lib, "DXGI.lib")
#pragma once

class Window
{
public:
	HWND hwnd;
	HINSTANCE hinstance;
	std::string name;
	int width;
	int height;
	bool keys[256];
	int mousex;
	int mousey;
	bool mouseButtons[3];

	void create(int window_width, int window_height, std::string window_name);
	void processMessages();
	void updateMouse(int x, int y){
		mousex = x;
		mousey = y;
	}

	// Checks if a specific key is currently pressed
	bool keyPressed(int key)
	{
		return keys[key];
	}
	// Returns the mouse x coordinate
	int getMouseX()
	{
		return mousex;
	}

	// Returns the mouse y coordinate
	int getMouseY()
	{
		return mousey;
	}

	void lockMouseToScreenCenter(HWND hwnd, float sensitivity) {
		POINT center;
		RECT rect;
		GetClientRect(hwnd, &rect);
		center.x = (rect.right - rect.left) / 2;
		center.y = (rect.bottom - rect.top) / 2;

		static POINT lastCursorPos = { center.x, center.y };

		POINT currentPos;
		GetCursorPos(&currentPos);
		ScreenToClient(hwnd, &currentPos);

		float deltaX = static_cast<float>(center.x - currentPos.x);
		float deltaY = static_cast<float>(currentPos.y - center.y);

		//camera.processMouseInput(deltaX, deltaY, sensitivity);

		ClientToScreen(hwnd, &center);
		SetCursorPos(center.x, center.y);

		lastCursorPos = currentPos;
	}
};