#include"pch.h"
#include<iostream>
#include<Windows.h>
#include<cstdio>
#include<time.h>

HHOOK _hook;
KBDLLHOOKSTRUCT kbdStructure;

int HideUnhide(int key_stroke);

int atemp = 0;
int btemp = 0;
int ctemp = 0;
int visible = 1;

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	if(nCode >= 0) {
		if (wParam == WM_KEYDOWN) {
			kbdStructure = *((KBDLLHOOKSTRUCT*)lParam);
			HideUnhide(kbdStructure.vkCode);
		}
	}

	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook() {
	if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0))) {
		MessageBox(NULL, L"Failed ot install hook!", L"Error", MB_ICONERROR);
	}
}

void ReleaseHook() {
	UnhookWindowsHookEx(_hook);
}

int HideUnhide(int keystroke) {
	std::cout << keystroke << std::endl;
	atemp = btemp;
	btemp = ctemp;
	ctemp = keystroke;
	if ((atemp == 162) && (btemp == 160) && (ctemp == 49)) {
		visible = (visible + 1) % 2;
		ShowWindow(FindWindowA("ConsoleWindowClass", NULL), visible);
	}
	return 0;
}

int main() {
	SetHook();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {

	}
	return 0;
}