#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

uintptr_t getMemAddr() {
	uintptr_t memoryToWrite;
	cout << "Enter Memory Address to write to: 0x";
	cin >> hex >> memoryToWrite;
	return memoryToWrite;
}

int main() {
	int pId;
	uintptr_t memoryToWrite = 0x0;

	//Prompt user for Id of the process.
	cout << "Enter Process ID: ";
	cin >> dec >> pId;

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	if (hProcess == NULL) { //If unsuccessfull, print error then exit.
		cout << "Open process failed. Last Error: " << dec << GetLastError() << endl;
		return 1;
	}

	int type = -1;
	do {
		cout << "What are we writing?\n1.Number\n2.CharArr\n3.Manual\n4.exit\n";
		cin >> type;
		if (type == 4) {
			CloseHandle(hProcess);
			return 0;
		}
		else if (type == 1) {
			memoryToWrite = getMemAddr();
			int intWrite = 0;
			cout << "New value: ";
			cin >> dec >> intWrite;
			BOOL rpmReturn = WriteProcessMemory(hProcess, (LPVOID)memoryToWrite, (LPVOID)& intWrite, sizeof(int), NULL);
			if (rpmReturn == false) {
				CloseHandle(hProcess);
				cout << "Write process failed. Last Error: " << dec << GetLastError() << endl;
				return 1;
			}
			else {
				cout << "Overwrite Success." << endl;
				break;
			}
		}
		else if (type == 2) {
			memoryToWrite = getMemAddr();
			char charWrite[128];
			cout << "New value: ";
			cin >> charWrite;
			BOOL rpmReturn = WriteProcessMemory(hProcess, (LPVOID)memoryToWrite, (LPVOID)& charWrite, 128, NULL);
			if (rpmReturn == false) {
				CloseHandle(hProcess);
				cout << "Write process failed. Last Error: " << dec << GetLastError() << endl;
				return 1;
			}
			else {
				cout << "Overwrite Success." << endl;
				break;
			}
		}
		else if (type == 3) {
			while (true)
			{
				if (GetAsyncKeyState(VK_HOME) & 0x0001) {
					memoryToWrite = getMemAddr();
					int intWrite = 9999;
					BOOL rpmReturn = WriteProcessMemory(hProcess, (LPVOID)memoryToWrite, (LPVOID)& intWrite, sizeof(int), NULL);
					if (rpmReturn == false) {
						CloseHandle(hProcess);
						cout << "Write process failed. Last Error: " << dec << GetLastError() << endl;
						return 1;
					}
					else {
						cout << "Overwrite Success." << endl;
					}
				}
				else if (GetAsyncKeyState('S') & 0x0001){
					memoryToWrite = getMemAddr();
					char charWrite[] = "HOHOHOHOHOHHO!";
					BOOL rpmReturn = WriteProcessMemory(hProcess, (LPVOID)memoryToWrite, (LPVOID)& charWrite, sizeof(charWrite), NULL);
					if (rpmReturn == false) {
						CloseHandle(hProcess);
						cout << "Write process failed. Last Error: " << dec << GetLastError() << endl;
						return 1;
					}
					else {
						cout << "Overwrite Success." << endl;
					}
				}
				else if (GetAsyncKeyState(VK_END) & 0x0001) break;
			}
			break;
		}
	} while (true);
	CloseHandle(hProcess);
}