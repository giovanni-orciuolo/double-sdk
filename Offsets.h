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

// Just a namespace to store all the patterns (all the patterns are BYTE arrays!)
namespace Patterns
{
	BYTE pt_dwLocalPlayer	[] = { 0xA3, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x59, 0xC3, 0x6A };
	BYTE pt_dwEntityList	[] = { 0x05, 0x00, 0x00, 0x00, 0x00, 0xC1, 0xE9, 0x00, 0x39, 0x48, 0x04 };
	BYTE pt_dwEnginePointer	[] = { 0xF3, 0x0F, 0x5C, 0xC1, 0xF3, 0x0F, 0x10, 0x15, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x2F, 0xD0, 0x76, 0x04, 0xF3, 0x0F, 0x58, 0xC1, 0xA1, 0x00, 0x00, 0x00, 0x00, 0xF3, 0x0F, 0x11, 0x80, 0x00, 0x00, 0x00, 0x00, 0xD9, 0x46, 0x04 };
	BYTE pt_dwForceAttack	[] = { 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, 0xF6, 0xC2, 0x03, 0x74, 0x03, 0x83, 0xCE, 0x04, 0xA8, 0x04, 0xBF };
	BYTE pt_dwForceJump		[] = { 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, 0xF6, 0xC2, 0x03, 0x74, 0x03, 0x83, 0xCE, 0x08, 0xA8, 0x08, 0xBF };
	BYTE pt_iCrosshairID	[] = { 0x56, 0x57, 0x8B, 0xF9, 0xC7, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x81, 0xF9, 0x00, 0x00, 0x00, 0x00, 0x75, 0x07, 0xA1, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x07 };
	BYTE pt_dwViewMatrix    [] = { 0x53, 0x8B, 0xDC, 0x83, 0xEC, 0x08, 0x83, 0xE4, 0xF0, 0x83, 0xC4, 0x04, 0x55, 0x8B, 0x6B, 0x04, 0x89, 0x6C, 0x24, 0x04, 0x8B, 0xEC, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x81, 0xEC, 0x98, 0x03, 0x00, 0x00 };
	BYTE pt_dwGlowObject	[] = { 0xA1, 0x00, 0x00, 0x00, 0x00, 0xA8, 0x01, 0x75, 0x00, 0x0F, 0x57, 0xC0, 0xC7, 0x05 };
	BYTE pt_dwSensitivity   [] = { 0x75, 0x0A, 0xF3, 0x0F, 0x10, 0x05, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x0F, 0x8B, 0x01 }; //TODO: Find a good pattern for m_dwSensitivity, this one isn't working!
}

// Just a namespace to store all the masks (all the masks are const char*!)
namespace Masks
{
	const char* msk_dwLocalPlayer		= "x????xx????????x????xxx";
	const char* msk_dwEntityList		= "x????xx?xxx";
	const char* msk_dwEnginePointer		= "xxxxxxxx????xxxxxxxxxx????xxxx????xxx";
	const char* msk_dwForceAttack		= "xx????xx????xxxxxxxxxxx";
	const char* msk_dwForceJump			= "xx????xx????xxxxxxxxxxx";
	const char* msk_iCrosshairID		= "xxxxxx????????xx????xx????xxx????xx";
	const char* msk_dwViewMatrix		= "xxxxxxxxxxxxxxxxxxxxxxx????xxxxxx";
	const char* msk_dwGlowObject		= "x????xxx?xxxxx";
	const char* msk_dwSensitivity		= "xxxxxx????xxxx"; //TODO: Make a mask for m_dwSensitivity out of a working pattern
}

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
	m_dwViewMatrix;

	// Get m_dwLocalPlayer
	void UpdateLocalPlayer()
	{
		DWORD start = ClientScanner.FindPattern(Patterns::pt_dwLocalPlayer, Masks::msk_dwLocalPlayer, 0);
		DWORD p1 = Process.Read<DWORD>(start + 1);
		m_dwLocalPlayer = Process.Read<DWORD>(p1 + 16);
	}

	// Get m_dwEntityList
	void UpdateEntityList()
	{
		DWORD start = ClientScanner.FindPattern(Patterns::pt_dwEntityList, Masks::msk_dwEntityList, 0);
		DWORD p1 = Process.Read<DWORD>(start + 1);
		BYTE p2 = Process.Read<BYTE>(start + 7);
		m_dwEntityList = (p1 + p2) - Process.GetClientBase();
	}

	// Get m_dwEnginePointer
	void UpdateEnginePointer()
	{
		DWORD start = EngineScanner.FindPattern(Patterns::pt_dwEnginePointer, Masks::msk_dwEnginePointer, 0);
		m_dwEnginePointer = Process.Read<DWORD>(start + 22) - Process.GetEngineBase();
	}

	// Get m_dwForceAttack
	void UpdateForceAttack()
	{
		DWORD start = ClientScanner.FindPattern(Patterns::pt_dwForceAttack, Masks::msk_dwForceAttack, 0);
		m_dwForceAttack = Process.Read<DWORD>(start + 2);
	}

	// Get m_dwForceJump
	void UpdateForceJump()
	{
		DWORD start = ClientScanner.FindPattern(Patterns::pt_dwForceJump, Masks::msk_dwForceJump, 0);
		m_dwForceJump = Process.Read<DWORD>(start + 2);
	}

	// Get m_dwViewAngles
	void UpdateViewAngles()
	{
		DWORD start = EngineScanner.FindPattern(Patterns::pt_dwEnginePointer, Masks::msk_dwEnginePointer, 0);
		m_dwViewAngles = Process.Read<DWORD>(start + 30);
	}

	// Get m_iCrosshairID
	void UpdateCrosshairID()
	{
		DWORD start = ClientScanner.FindPattern(Patterns::pt_iCrosshairID, Masks::msk_iCrosshairID);
		m_iCrosshairID = Process.Read<DWORD>(start + 6);
	}

	// Get m_dwGlowObject
	void UpdateGlowObject()
	{
		DWORD start = ClientScanner.FindPattern(Patterns::pt_dwGlowObject, Masks::msk_dwGlowObject);
		m_dwGlowObject = Process.Read<DWORD>(start + 0x58) - Process.GetClientBase();
	}

	// Get m_dwSensitivity (HARDCODED)
	// TODO: Find a good pattern for m_dwSensitivity
	void UpdateSensitivity()
	{
		//DWORD start = ClientScanner.FindPattern(Patterns::pt_dwSensitivity, Masks::msk_dwSensitivity);
		//m_dwSensitivity = Process.Read<DWORD>(start + 5);
		m_dwSensitivity = 0x00A85CD4; // Hardcoded for now
	}

	// Get m_dwViewMatrix
	void UpdateViewMatrix()
	{
		DWORD start = ClientScanner.FindPattern(Patterns::pt_dwViewMatrix, Masks::msk_dwViewMatrix);
		start = Process.Read<DWORD>(start + 0x4EE);
		m_dwViewMatrix = (start + 0x80) - Process.GetClientBase();
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
		UpdateSensitivity(); // This one is hardcoded!
	}

	// Hardcode netvars
	// TODO: Implement a netvar manager maybe? :P
	void ForceNetvars()
	{
		m_bDormant = 0xE9;
		m_iTeam = 0xF0;
		m_iHealth = 0xFC;
		m_bIsDefusing = 0x3894;
		m_iItemDefinitionIndex = 0x2F80;
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
	}

}