﻿#include "stdafx.h"
#include "mem.h"
#include "offsets.h"
#include "vars.h"

void reAttach()
{

	//Attach to hl2.exe
	processID = getProcessIdFromWindowName("HALF-LIFE 2");
	
	CloseHandle(handle);
	handle = getHandleFromProcessID(processID);
	std::cout << "Re-attached!" << std::endl;
}

int main()
{
	//Splash
	std::cout << "HL2 Bhop Hack" << std::endl;
	std::cout << "Made by _palonE" << std::endl;

	//Attach to hl.exe
	processID = getProcessIdFromWindowName("HALF-LIFE 2");

	handle = getHandleFromProcessID(processID);
	std::cout << std::endl << "Attached!" << std::endl;

	std::cout << "Press INS / EINFG to re-attach if needed." << std::endl << std::endl;

	clientDll = getModule("client.dll", processID);
	engineDLL = getModule("engine.dll", processID);

	std::cout << "enigneDll: " << engineDLL << std::endl;
	std::cout << "clientDll: " << clientDll << std::endl << std::endl;

	while (handle)
	{
		while (GetAsyncKeyState(VK_SPACE))
		{
			//read flags
			iFlags = readMem<int>(engineDLL, oFlags1);
			iFlags = readMem<int>(iFlags, oFlags2);
			iFlags = readMem<int>(iFlags, oFlags3);
			//BHOP

			//if onGround
			if (iFlags != 65666)
			{
				writeMem<int>(clientDll, oForceJump, 5);
			}
			else
			{
				writeMem<int>(clientDll, oForceJump, 4);
			}
			Sleep(1);
		}

		//reattach feature
		if (GetAsyncKeyState(VK_INSERT))
		{
			reAttach();

			while (GetAsyncKeyState(VK_INSERT))
			{
				Sleep(10);
			}
		}

		Sleep(1); //If you comment this you get a Space Heater for free!
	}

	return 0;
}
