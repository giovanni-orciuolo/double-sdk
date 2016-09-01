/// Client.h
// This header defines the CClient class

/*
The CClient class allows you to grab and set important info from the client.dll module, using
the CProcess class already defined in Process.h;
Just call a function from here to get what you want from the client.
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

namespace DoubleSDK
{

class CClient
{
public:

	// Returns a pointer to glow objects as DWORD
	DWORD GlowPointer()
	{
		return Process.Read<DWORD>(Process.GetClientBase() + Offsets::m_dwGlowObject);
	}

	// Returns number of glow entities as DWORD
	DWORD GlowCount()
	{
		return Process.Read<DWORD>(Process.GetClientBase() + Offsets::m_dwGlowObject + 0x4);
	}

	// Returns current sensitivity as float
	float Sens()
	{
		return Process.Read<float>(Process.GetClientBase() + Offsets::m_dwSensitivity);
	}

	// Force current sensitivity
	// Returns true if successful
	bool ForceSens(float NewSens)
	{
		return Process.Write<float>(Process.GetClientBase() + Offsets::m_dwSensitivity, NewSens);
	}

	// Force the player to jump
	// Returns true if successful
	bool ForceJump()
	{
		return Process.Write<int>(Process.GetClientBase() + Offsets::m_dwForceJump, 5);
	}

	// Force the player to stop jumping
	// Returns true if successful
	bool StopJump()
	{
		return Process.Write<int>(Process.GetClientBase() + Offsets::m_dwForceJump, 4);
	}

	// Force the player to attack
	// Returns true if successful
	bool ForceAttack()
	{
		return Process.Write<int>(Process.GetClientBase() + Offsets::m_dwForceAttack, 5);
	}

	// Force the player to stop attacking
	// Returns true if successful
	bool StopAttack()
	{
		return Process.Write<int>(Process.GetClientBase() + Offsets::m_dwForceAttack, 4);
	}
	
	// Force m_dwForceAttack using an arbitrary value
	// Returns true if successful
	bool EditAttack(int Value)
	{
		return Process.Write<int>(Process.GetClientBase() + Offsets::m_dwForceAttack, Value);
	}
	
	// Force m_dwForceJump using an arbitrary value
	// Returns true if successful
	bool EditJump(int Value)
	{
		return Process.Write<int>(Process.GetClientBase() + Offsets::m_dwForceJump, Value);
	}

};

}

DoubleSDK::CClient Client;
