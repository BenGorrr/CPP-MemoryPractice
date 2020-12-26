#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

class Bypass {
public:
	Bypass();
	~Bypass();
	BOOL Attach(DWORD pId);
	BOOL Attach(LPCSTR lpWindowName);
	BOOL Read(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead = NULL);
	BOOL Write(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten = NULL);
private:
	HANDLE m_hProcess = NULL;
};

