#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

int main() {
	int pId;
	uintptr_t memoryToRead = 0x0;

	//Prompt user for Id of the process.
	cout << "Enter Process ID: ";
	cin >> dec >> pId;

	HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, pId);
	if (hProcess == NULL) { //If unsuccessfull, print error then exit.
		cout << "Open process failed. Last Error: " << dec << GetLastError() << endl;
		return 1;
	}

	cout << "Enter Memory Address to read to: 0x";
	cin >> hex >> memoryToRead;
	int type = -1;
	do {
		cout << "What are we reading?\n1.Number\n2.CharArr\n3.String\n4.Int Pointer\n5.exit\n";
		cin >> type;
		if (type == 5) {
			CloseHandle(hProcess);
			return 0;
		}
		else if (type == 1) {
			int intRead = 0;
			BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memoryToRead, (LPVOID)&intRead, sizeof(int), NULL);
			if (rpmReturn == false) {
				CloseHandle(hProcess);
				cout << "Read process failed. Last Error: "<< dec << GetLastError() << endl;
				return 1;
			}
			else {
				cout << "intRead = " << intRead << endl;
				break;
			}
		}
		else if (type == 2) {
			char charRead[128];
			BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memoryToRead, (LPVOID)& charRead, 128, NULL);
			if (rpmReturn == false) {
				CloseHandle(hProcess);
				cout << "Read process failed. Last Error: " << dec << GetLastError() << endl;
				return 1;
			}
			else {
				cout << "charRead = " << charRead << endl;
				break;
			}
		}
		else if (type == 3) {
			char stringBuffer[15];
			BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memoryToRead, (LPVOID)& stringBuffer, sizeof(stringBuffer), NULL);
			if (rpmReturn == false) {
				CloseHandle(hProcess);
				cout << "Read process failed. Last Error: " << dec << GetLastError() << endl;
				return 1;
			}
			else {
				cout << "stringRead = " << stringBuffer << endl;
				cout << "Last Error :" << GetLastError() << endl;
				break;
			}
		}
		else if (type == 4) {
			int* intptrRead;
			BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memoryToRead, (LPVOID)&intptrRead, sizeof(intptrRead), NULL);
			if (rpmReturn == false) {
				CloseHandle(hProcess);
				cout << "Read process failed. Last Error: " << dec << GetLastError() << endl;
				return 1;
			}
			else {
				cout << "IntPtr = 0x" << hex << uppercase << intptrRead << endl;
				break;
			}
		}
	} while (true);
	CloseHandle(hProcess);
}