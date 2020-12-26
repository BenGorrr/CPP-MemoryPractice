//#include <stdio.h>
//#include <stdlib.h>
//#include <Windows.h>
//#pragma warning (disable: 4996)
//
//int main()
//{
//	int pId;
//	int* memoryToWrite;
//
//	//Prompt user for Id of the process.
//	printf("Enter Process ID: ");
//	scanf("%d", &pId);
//
//	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId); //Get process handle
//	if (hProcess == NULL) { //If unsuccessfull, print error then exit.
//		printf("Open process failed. Last Error: %u\n", GetLastError());
//		system("pause");
//		return 1;
//	}
//	//Prompt user for the address of the process to write to.
//	printf("Enter Memory Address to write to: 0x");
//	scanf("%p", &memoryToWrite);
//	int type = -1;
//	do {
//		printf("What are we writing?\n1.Number\n2.Text\n");
//		type = _getch();
//		//printf("%d", type);
//		if (type != 49 && type != 50 && type != 51) {
//			printf("Invalid Input.\n");
//		}
//		else break;
//	} while (TRUE);
//	
//	if (type == 49) { //Writing Integer
//		int intToWrite = 0;
//		printf("New value: ");
//		scanf("%d", &intToWrite);
//		//write the process based from the input.
//		BOOL wpmReturn = WriteProcessMemory(hProcess, (LPVOID)memoryToWrite, &intToWrite, sizeof(int), NULL);
//		if (wpmReturn == FALSE) { //if write is not successfull, print error then exit.
//			printf("memoryToWrite: %p\nintToWrite: %d\n", (LPVOID)memoryToWrite, intToWrite);
//			printf("Write process failed. Last Error: %u\n", GetLastError());
//			system("pause");
//			return 1;
//		}
//		printf("Overwrite success.\n");
//	}
//	else if (type == 50) { //Writing Chars
//		char charToWrite[128];
//		printf("charToWrite = %s", charToWrite);
//		printf("New value: ");
//		rewind(stdin);
//		scanf("%[^\n]s", &charToWrite);
//		//write the process based from the input.
//		BOOL wpmReturn = WriteProcessMemory(hProcess, (LPVOID)memoryToWrite, &charToWrite, sizeof(char)*128, NULL);
//		if (wpmReturn == FALSE) { //if write is not successfull, print error then exit.
//			printf("write process failed. Last Error: %u\n", GetLastError());
//			system("pause");
//			return 1;
//		}
//		printf("Overwrite success.\n");
//	}/*
//	else if (type == 51) { //Reading Pointer
//		int* intPtr;
//		//read the process based from the input.
//		BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memoryToRead, &intPtr, 4, NULL);
//		if (rpmReturn == FALSE) { //if read is not successfull, print error then exit.
//			printf("Read process failed. Last Error: %u\n", GetLastError());
//			system("pause");
//			return 1;
//		}
//		printf("intPtr = %p\n", intPtr);
//
//		int intRead = 0;
//		//Read the value where the pointer is pointing
//		rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)intPtr, &intRead, sizeof(int), NULL);
//		if (rpmReturn == FALSE) { //if read is not successfull, print error then exit.
//			printf("Read process failed. Last Error: %u\n", GetLastError());
//			system("pause");
//			return 1;
//		}
//		printf("intRead = %d\n", intRead);
//	}*/
//
//	if (CloseHandle(hProcess) == 0) //CloseHandle return zero if failed.
//	{
//		printf("Close Handle failed.\n");
//	}
//	printf("Close Handle Success.\n");
//	system("pause");
//}