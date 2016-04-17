/// Entity.h
// This header defines the CEntity class

/*
The CEntity class allows you to read stuff from a generic entity currently in the
game's entity list.
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

class CEntity
{
private:
	int Index;
public:

	inline CEntity* operator[] (int i)
	{
		Index = i;
		return this;
	}

	// Returns the entity base as DWORD
	DWORD Base()
	{
		return Process.Read<DWORD>(Process.GetClientBase() + Offsets::m_dwEntityList + (Index * 0x10));
	}

	// Returns the entity bone base as DWORD
	DWORD BoneBase()
	{
		return Process.Read<DWORD>(Base() + Offsets::m_dwBoneMatrix);
	}

	// Searches for PlayerResources index through the entity list and returns it
	// Warning: REALLY HEAVY! WILL PERFORM 4 RPMS FOR EACH LOOP
	int SearchPlayerResources()
	{
		for (int i=0; i<1000; i++)
		{
			Index = i;
			if (ClassID() == ClassIDs::CCSPlayerResource) return Index;
		}
	}

	// Returns the entity health as int
	int Health()
	{
		return Process.Read<int>(Base() + Offsets::m_iHealth);
	}

	// Returns the entity team as int
	int Team()
	{
		return Process.Read<int>(Base() + Offsets::m_iTeam);
	}

	// Returns the ClassID of the entity as int
	int ClassID()
	{
		return Process.Read<int>(Process.Read<int>(Process.Read<int>(Process.Read<int>(Base() + 0x8) + 2*0x4) + 0x1) + 20);
	}

	// Returns the entity postion as Vector3
	Vector3 Position()
	{
		return Process.Read<Vector3>(Base() + Offsets::m_vecOrigin);
	}

	// Returns the entity bone position (by a given bone id) as Vector3
	Vector3 BonePos(int BoneID)
	{
		Vector3 BonePos;
		BonePos.x = Process.Read<float>(BoneBase() + 0x30 * BoneID + 0x0C);
		BonePos.y = Process.Read<float>(BoneBase() + 0x30 * BoneID + 0x1C);
		BonePos.z = Process.Read<float>(BoneBase() + 0x30 * BoneID + 0x2C);
		return BonePos;
	}

	// Returns the entity vec velocity as Vector3
	Vector3 VecVelocity()
	{
		return Process.Read<Vector3>(Base() + Offsets::m_vecVelocity);
	}

	// Returns the entity flash duration as float
	float FlashDuration()
	{
		return Process.Read<float>(Base() + Offsets::m_flFlashDuration);
	}

	// Returns true if the entity is spotted on radar
	bool Spotted()
	{
		return Process.Read<bool>(Base() + Offsets::m_bSpotted);
	}

	// Returns the entity distance from the local player as float
	float DistanceFromMe()
	{
		return Math.VecDist(Me.Position(), Position());
	}

	// Returns the glow index of the entity as int
	int GlowIndex()
	{
		return Process.Read<int>(Base() + Offsets::m_iGlowIndex);
	}

	// Returns the life state of the entity as int
	int LifeState()
	{
		return Process.Read<int>(Base() + Offsets::m_lifeState);
	}

	// Returns flags of the entity as BYTE
	BYTE Flags()
	{
		return Process.Read<BYTE>(Base() + Offsets::m_fFlags);
	}

	// Returns true if the entity is on ground
	bool OnGround()
	{
		return Flags() & FL_ONGROUND;
	}

	// Returns true if the entity is dead
	bool Dead()
	{
		return LifeState() == LifeState::LIFE_DEAD;
	}

	// Returns true if the entity is enemy
	bool Enemy()
	{
		return Team() != Me.Team();
	}

	// Returns true if the entity is dormant (not networked on your side)
	bool Dormant()
	{
		return Process.Read<bool>(Base() + Offsets::m_bDormant);
	}

	// Returns true if the entity is valid (performs several checks all in one func)
	bool isValid()
	{
		if (!Base())
			return false;

		if (!BoneBase())
			return false;

		if (Team() == Teams::NONE)
			return false;

		if (!Enemy())
			return false;

		if (Dead())
			return false;

		if (Dormant())
			return false;

		if (Position().IsZero())
			return false;

		if (Health() <= 0)
			return false;

		return true;
	}

	// Force spotted status of the entity
	bool SetSpotted(bool spotted)
	{
		return Process.Write<int>(Base() + Offsets::m_bSpotted, (int)spotted);
	}

};

}

DoubleSDK::CEntity EntityList;