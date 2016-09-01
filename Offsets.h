/// Offsets.h
// This header defines the COffsets class

/*
The COffsets class, using PatternScanning, allows you to get useful offsets dynamically.
These offsets are used in other classes like CLocalPlayer or CEntity, but you can use them as you wish.
Credits to serge for most patterns used.
Credits to WasserEsser for pattern to m_dwSensitivity
*/

/*
DOUBLE SDK | A FREE CSGO SDK MADE BY DOUBLE V FOR UNKNOWNCHEATS.ME
CREDITS AND SHOUTOUTS:
Double V
WasserEsser
TeamGamerFood
Serge
*/

#pragma once
#include "DoubleSDK.h"

// Namespace for the offsets, contains offsets and useful methods to grab them dynamically
namespace Offsets
{

	DWORD
		m_dwLocalPlayer,
		m_dwEntityList,
		m_dwEnginePointer,
		m_dwForceAttack,
		m_dwForceJump,
		m_dwViewAngles,
		m_iCrosshairID,
		m_dwGlowObject,
		m_dwSensitivity,
		m_bDormant,
		m_iTeam,
		m_iHealth,
		m_bIsDefusing,
		m_iItemDefinitionIndex,
		m_hActiveWeapon,
		m_dwBoneMatrix,
		m_vecOrigin,
		m_vecViewOffset,
		m_vecPunch,
		m_fFlags,
		m_flFlashDuration,
		m_bSpotted,
		m_vecVelocity,
		m_iGlowIndex,
		m_lifeState,
		m_iShotsFired,
		m_dwViewMatrix,
		m_iTeamNum;

	// Get m_dwLocalPlayer
	void UpdateLocalPlayer()
	{
		DWORD lpStart = ClientScanner.FindPatternArr(Process.GetClientBase(), Process.GetClientSize(), "xxx????xx????xxxxx?", 19, 0x8D, 0x34, 0x85, 0x0, 0x0, 0x0, 0x0, 0x89, 0x15, 0x0, 0x0, 0x0, 0x0, 0x8B, 0x41, 0x8, 0x8B, 0x48, 0x0);
		DWORD lpP1 = Process.Read<DWORD>(lpStart + 3);
		BYTE lpP2 = Process.Read<BYTE>(lpStart + 18);
		m_dwLocalPlayer = (lpP1 + lpP2) - Process.GetClientBase();

	}

	// Get m_dwEntityList
	void UpdateEntityList()
	{
		DWORD elStart = ClientScanner.FindPatternArr(Process.GetClientBase(), Process.GetClientSize(), "x????xx?xxx", 11, 0x5, 0x0, 0x0, 0x0, 0x0, 0xC1, 0xE9, 0x0, 0x39, 0x48, 0x4);
		DWORD elP1 = Process.Read<DWORD>(elStart + 1);
		BYTE elP2 = Process.Read<BYTE>(elStart + 7);
		m_dwEntityList = (elP1 + elP2) - Process.GetClientBase();
	}

	// Get m_dwEnginePointer
	void UpdateEnginePointer()
	{
		DWORD epStart = EngineScanner.FindPatternArr(Process.GetEngineBase(), Process.GetEngineSize(), "xxxxxxxx????xxxxxxxxxx????xxxx????xxx", 37, 0xF3, 0x0F, 0x5C, 0xC1, 0xF3, 0x0F, 0x10, 0x15, 0x0, 0x0, 0x0, 0x0, 0x0F, 0x2F, 0xD0, 0x76, 0x04, 0xF3, 0x0F, 0x58, 0xC1, 0xA1, 0x0, 0x0, 0x0, 0x0, 0xF3, 0x0F, 0x11, 0x80, 0x0, 0x0, 0x0, 0x0, 0xD9, 0x46, 0x04);
		m_dwEnginePointer = Process.Read<DWORD>(epStart + 22) - Process.GetEngineBase();
	}

	// Get m_dwForceAttack
	void UpdateForceAttack()
	{
		DWORD aStart = ClientScanner.FindPatternArr(Process.GetClientBase(), Process.GetClientSize(), "xx????xx????xxxxxxxxxxx", 23, 0x89, 0x15, 0x0, 0x0, 0x0, 0x0, 0x8B, 0x15, 0x0, 0x0, 0x0, 0x0, 0xF6, 0xC2, 0x3, 0x74, 0x3, 0x83, 0xCE, 0x4, 0xA8, 0x4, 0xBF);
		DWORD aOff = Process.Read<DWORD>(aStart + 2);
		m_dwForceAttack = aOff - Process.GetClientBase();
	}

	// Get m_dwForceJump
	void UpdateForceJump()
	{
		DWORD jStart = ClientScanner.FindPatternArr(Process.GetClientBase(), Process.GetClientSize(), "xx????xx????xxxxxxxxxxx", 23, 0x89, 0x15, 0x0, 0x0, 0x0, 0x0, 0x8B, 0x15, 0x0, 0x0, 0x0, 0x0, 0xF6, 0xC2, 0x3, 0x74, 0x3, 0x83, 0xCE, 0x8, 0xA8, 0x8, 0xBF);
		DWORD jOff = Process.Read<DWORD>(jStart + 2);
		m_dwForceJump = jOff - Process.GetClientBase();
	}

	// Get m_dwViewAngles
	void UpdateViewAngles()
	{
		DWORD vaStart = EngineScanner.FindPatternArr(Process.GetEngineBase(), Process.GetEngineSize(), "xxxxxxxx????xxxxxxxxxx????xxxx????xxx", 37, 0xF3, 0x0F, 0x5C, 0xC1, 0xF3, 0x0F, 0x10, 0x15, 0x0, 0x0, 0x0, 0x0, 0x0F, 0x2F, 0xD0, 0x76, 0x04, 0xF3, 0x0F, 0x58, 0xC1, 0xA1, 0x0, 0x0, 0x0, 0x0, 0xF3, 0x0F, 0x11, 0x80, 0x0, 0x0, 0x0, 0x0, 0xD9, 0x46, 0x04);
		m_dwViewAngles = Process.Read<DWORD>(vaStart + 30);
	}

	// Get m_iCrosshairID
	void UpdateCrosshairID()
	{
		m_iCrosshairID = 0xAA54;
	}

	// Get m_dwGlowObject
	void UpdateGlowObject()
	{
		DWORD gpStart = ClientScanner.FindPatternArr(Process.GetClientBase(), Process.GetClientSize(), "x????xxxx????xx", 15, 0xE8, 0x0, 0x0, 0x0, 0x0, 0x83, 0xC4, 0x04, 0xB8, 0x0, 0x0, 0x0, 0x0, 0xC3, 0xCC);
		m_dwGlowObject = Process.Read<DWORD>(gpStart + 9) - Process.GetClientBase();
	}

	void UpdateSensitivity()
	{
		DWORD starts = ClientScanner.FindPatternArr(Process.GetClientBase(), Process.GetClientSize(), "xxxxxxxxxxx", 11, 0x6A, 0x01, 0x51, 0xC7, 0x04, 0x24, 0x17, 0xb7, 0xd1, 0x38, 0xb9);
		starts = Process.Read<DWORD>(starts + 11);
		m_dwSensitivity = starts - Process.GetClientBase();
	}

	// Get m_dwViewMatrix
	void UpdateViewMatrix()
	{
		m_dwViewMatrix = 0xE16AC598;
	}

	// Method to call all dynamic getters for offsets
	void GetOffsets()
	{
		UpdateLocalPlayer();
		UpdateEntityList();
		UpdateEnginePointer();
		UpdateForceAttack();
		UpdateForceJump();
		UpdateViewAngles();
		UpdateCrosshairID();
		UpdateGlowObject();
		UpdateSensitivity(); // This one is hardcoded! (not anymore)
		UpdateViewMatrix();
	}

	// Hardcode netvars
	// TODO: Implement a netvar manager maybe? :P
	void ForceNetvars()
	{
		m_bDormant = 0xE9;
		m_iTeam = 0xF0;
		m_iHealth = 0xFC;
		m_bIsDefusing = 0x3894;
		m_iItemDefinitionIndex = 0x2F88;
		m_hActiveWeapon = 0x2EE8;
		m_dwBoneMatrix = 0x2698;
		m_vecOrigin = 0x134;
		m_vecViewOffset = 0x104;
		m_vecPunch = 0x3018;
		m_fFlags = 0x100;
		m_flFlashDuration = 0xA2F8;
		m_bSpotted = 0x939;
		m_vecVelocity = 0x110;
		m_iGlowIndex = 0xA310;
		m_lifeState = 0x25B;
		m_iShotsFired = 0xA2B0;
		m_iTeamNum = 0xF0;
	}

}