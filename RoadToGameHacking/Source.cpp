#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

int main() {
	int varInt = 123456;
	string varString = "default String";
	char arrChar[128] = "Long char array right there ->";

	//pointers
	int* ptr2int = &varInt;
	int** ptr2ptr = &ptr2int;
	int*** ptr2ptr2 = &ptr2ptr;

	do
	{
		cout << "Process ID: " << GetCurrentProcessId() << endl << endl;

		cout << "varInt (0x" << &varInt << ") = " << varInt << endl;
		cout << "varString (0x" << &varString << ") = " << varString << endl;
		cout << "arrChar (0x" << &arrChar << ") = " << arrChar << endl << endl;

		cout << "ptr2int (0x" << &ptr2int << ") = 0x" << ptr2int << endl;
		cout << "ptr2ptr (0x" << &ptr2ptr << ") = 0x" << ptr2ptr << endl;
		cout << "ptr2ptr2 (0x" << &ptr2ptr2 << ") = 0x" << ptr2ptr2 << endl << endl;

		cout << "Press Enter to print again. (e to exit)";
		int a = getchar();
		if (a == 'e') break;
		else printf("\n\n---------------------------------------------------------------------------\n\n");
	} while (true);
}