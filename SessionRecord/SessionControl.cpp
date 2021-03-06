#include"pch.h"
#include<iostream>
#include<Windows.h>
#include<cstdio>
#include<time.h>
#pragma warning(disable : 4996)

HHOOK _hook;
KBDLLHOOKSTRUCT kbdStructure;

int ShowKeyStroke(int key_stroke);

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0) {
		if (wParam == WM_KEYDOWN) {
			kbdStructure = *((KBDLLHOOKSTRUCT*)lParam);
			ShowKeyStroke(kbdStructure.vkCode);
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

int ShowKeyStroke(int keystroke) {
	std::cout << keystroke << std::endl;
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	std::cout << timePtr->tm_hour << " : " << timePtr->tm_min << " : " << timePtr->tm_sec << std::endl;
	return 0;
}

int main() {
	SetHook();

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
	}
	return 0;
}