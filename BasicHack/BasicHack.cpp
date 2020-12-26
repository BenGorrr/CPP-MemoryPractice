#include "Bypass.h"
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct cheats {
	bool health = false;
	int healthValue = 1337;
	bool ammo = false;
	int ammoValue = 99;
	bool speed = false;
	int speedDef = 1;
	int speedValue = 2;
} cheat;

struct address {
	DWORD localEntity = 0x50F4F4;
	int pBase = 0;
	DWORD health = 0xF8;
	DWORD rifleLoadedAmmos = 0x150;
	//dualPistolEnabled = 0x10C;
	DWORD pistolLoadedAmmos = 0x13C;
	DWORD grenades = 0x158;
	DWORD speed = 0x80; //default = 1
	DWORD doublePistolLoadedAmmos = 0x15C;
	/*
	Mouse Pos X ---> 0x40 (Float)
	Mouse Pos Y ---> 0x44 (Float)
	Position X Offset ---> 0x4 (Float)
	Position Z Offset ---> 0x8 (Float)
	Position Y Offset ---> 0xC (Float)
	*/
} addr;

struct status {
	int health;
	int rifleLoadedAmmos;
} stats;

void displayStats(Bypass *bypass) {
	bypass->Read(addr.pBase + addr.health, &stats.health, sizeof(int));
	if (cheat.health) cout << "Health (ON) : " << dec << stats.health << endl;
	else cout << "Health (OFF) : " << dec << stats.health << endl;
	
	bypass->Read(addr.pBase + addr.rifleLoadedAmmos, &stats.rifleLoadedAmmos, sizeof(int));
	if (cheat.ammo) cout << "Ammo (ON): " << dec << stats.rifleLoadedAmmos << endl;
	else cout << "Ammo (OFF): " << dec << stats.rifleLoadedAmmos << endl;
}

int main()
{
	Bypass *bypass = new Bypass;
	//int pId;
	//cout << "Process ID: ";
	//cin >> dec >> pId;
	if (bypass->Attach("AssaultCube")) {
		cout << "Process Found." << endl;
	}
	else {
		cout << "Process not Found." << endl;
		return 1;
	}

	if (bypass->Read(addr.localEntity, &addr.pBase, sizeof(DWORD))) {
		cout << "pBase = " << hex << addr.pBase << endl;
	}
	cout << "Cheat Loaded!" << endl;
	Sleep(1000);
	do
	{
		displayStats(bypass);
		if (GetAsyncKeyState(VK_INSERT) & 0x0001) { // Toggle Health
			cheat.health = !cheat.health;
		}
		else if (GetAsyncKeyState(VK_HOME) & 0x0001) { //Toggle Ammo
			cheat.ammo = !cheat.ammo;
		}
		else if (GetAsyncKeyState(VK_DELETE) & 0x0001) { //Toggle Speed
			cheat.speed = !cheat.speed;
			if (!cheat.speed) bypass->Write(addr.pBase + addr.speed, &cheat.speedDef, sizeof(int));
		}

		if (cheat.health) {
			bypass->Write(addr.pBase + addr.health, &cheat.healthValue, sizeof(int));
		}
		if (cheat.ammo) {
			bypass->Write(addr.pBase + addr.pistolLoadedAmmos, &cheat.ammoValue, sizeof(int));
			bypass->Write(addr.pBase + addr.rifleLoadedAmmos, &cheat.ammoValue, sizeof(int));
			bypass->Write(addr.pBase + addr.grenades, &cheat.ammoValue, sizeof(int));
			bypass->Write(addr.pBase + addr.doublePistolLoadedAmmos, &cheat.ammoValue, sizeof(int));
		}
		if (cheat.speed) {
			bypass->Write(addr.pBase + addr.speed, &cheat.speedValue, sizeof(int));
		}

		Sleep(30);
		system("cls");
	} while ( !(GetAsyncKeyState(VK_END) & 0x0001) );
	cout << "Cheat Unloaded!" << endl;
	delete bypass;
}
