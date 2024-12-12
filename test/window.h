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
};