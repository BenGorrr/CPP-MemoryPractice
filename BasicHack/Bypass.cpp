#include "Bypass.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

Bypass::Bypass() {}

Bypass::~Bypass() {
	if (m_hProcess != NULL) {
		CloseHandle(m_hProcess);
		cout << "Handle Closed" << endl;
	}
}

BOOL Bypass::Attach(DWORD pId) {
	m_hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, false, pId);
	if (m_hProcess == NULL) return false; return true;
}

BOOL Bypass::Attach(LPCSTR lpWindowName) {
	HWND hwnd = FindWindowA(NULL, lpWindowName);
	DWORD pId;
	GetWindowThreadProcessId(hwnd, &pId);
	if (Attach(pId)) return true; return false;
}

BOOL Bypass::Read(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead) {
	if (ReadProcessMemory(m_hProcess, (LPCVOID)lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead)) return true; return false;
}

BOOL Bypass::Write(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten) {
	if (WriteProcessMemory(m_hProcess, (LPVOID)lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten)) return true; return false;
}