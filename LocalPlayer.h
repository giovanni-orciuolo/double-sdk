/// LocalPlayer.h
// This header defines the CLocalPlayer class

/*
The CLocalPlayer class allows you to grab and set important info from the local player, using
the CProcess class already defined in Process.h;
Just call a function from here to get/set whatever you want.
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

	class CLocalPlayer
	{
	public:

		// Returns the local player base as DWORD
		DWORD Base()
		{
			return Offsets::m_dwLocalPlayer;
		}

		DWORD LocalBase()
		{
			return Process.Read<DWORD>(Process.GetClientBase() + Base());
		}
		// Returns the WeaponIndex in the EntityList as DWORD
		DWORD WeaponIndex()
		{
			return Process.Read<DWORD>(LocalBase() + Offsets::m_hActiveWeapon) & 0xFFF;
		}

		// Returns the WeaponEntity from the EntityList using WeaponIndex as DWORD
		DWORD WeaponEntity()
		{
			return Process.Read<DWORD>((Process.GetClientBase() + Offsets::m_dwEntityList + WeaponIndex() * 0x10) - 0x10);
		}

		// Returns health as int
		int Health()
		{
			return Process.Read<int>(Base() + Offsets::m_iHealth);
		}

		// Returns team number as int
		int Team()
		{
			return Process.Read<int>(LocalBase() + Offsets::m_iTeamNum);
		}

		// Returns crosshair id as int
		int CrosshairID()
		{
			return Process.Read<int>(Base() + Offsets::m_iCrosshairID) - 1;
		}

		// Returns ItemDefinitionIndex for the weapon currently held as int
		int Weapon()
		{
			return Process.Read<int>(WeaponEntity() + Offsets::m_iItemDefinitionIndex);
		}

		// Returns shots fired in a single spraydown as int
		int ShotsFired()
		{
			return Process.Read<int>(Base() + Offsets::m_iShotsFired);
		}

		// Returns current position as Vector3
		Vector3 Position()
		{
			return Process.Read<Vector3>((LocalBase()) + Offsets::m_vecOrigin);
		}

		// Returns current vec view as Vector3
		Vector3 VecView()
		{
			return Process.Read<Vector3>(Base() + Offsets::m_vecViewOffset);
		}

		// Returns view found through position + vecview as Vector3
		Vector3 ViewEye()
		{
			return Position() + VecView();
		}

		// Returns current vec velocity as Vector3
		Vector3 VecVelocity()
		{
			return Process.Read<Vector3>(Base() + Offsets::m_vecVelocity);
		}

		// Returns current punch vector (for recoil)
		Vector3 VecPunch()
		{
			return Process.Read<Vector3>(Base() + Offsets::m_vecPunch);
		}

		// Return flags as BYTE
		BYTE Flags()
		{
			return Process.Read<int>(LocalBase() + Offsets::m_fFlags);
		}

		// Return flash duration as float
		float FlashDuration()
		{
			return Process.Read<float>(Base() + Offsets::m_flFlashDuration);
		}

		// Return true if on ground
		bool OnGround()
		{
			return Flags() & FL_ONGROUND;
		}

		// Return true if jumping
		bool Jumping()
		{
			return Flags() & IN_JUMP;
		}

		// Return true if zooming
		bool Zooming()
		{
			return Flags() & IN_ZOOM;
		}

		// Return true if you are holding a knife
		bool hasKnife()
		{
			int idi = Weapon();
			return
				idi == WeaponIDI::WEAPON_KNIFE ||
				idi == WeaponIDI::WEAPON_KNIFE_BAYONET ||
				idi == WeaponIDI::WEAPON_KNIFE_BOWIE ||
				idi == WeaponIDI::WEAPON_KNIFE_BUTTERFLY ||
				idi == WeaponIDI::WEAPON_KNIFE_FALCHION ||
				idi == WeaponIDI::WEAPON_KNIFE_FLIP ||
				idi == WeaponIDI::WEAPON_KNIFE_GUT ||
				idi == WeaponIDI::WEAPON_KNIFE_KARAMBIT ||
				idi == WeaponIDI::WEAPON_KNIFE_M9_BAYONET ||
				idi == WeaponIDI::WEAPON_KNIFE_PUSH ||
				idi == WeaponIDI::WEAPON_KNIFE_T ||
				idi == WeaponIDI::WEAPON_KNIFE_TACTICAL;
		}

		// Returns true if you are holding the C4
		bool hasBomb()
		{
			return Weapon() == WeaponIDI::WEAPON_C4;
		}

		// Returns true if you are holding a grenade
		bool hasGrenade()
		{
			int idi = Weapon();
			return
				idi == WeaponIDI::WEAPON_FLASHBANG ||
				idi == WeaponIDI::WEAPON_HEGRENADE ||
				idi == WeaponIDI::WEAPON_SMOKEGRENADE ||
				idi == WeaponIDI::WEAPON_DECOY ||
				idi == WeaponIDI::WEAPON_MOLOTOV ||
				idi == WeaponIDI::WEAPON_INCGRENADE;
		}

		// Returns true if you are holding a Zeus (taser)
		bool hasZeus()
		{
			return Weapon() == WeaponIDI::WEAPON_TASER;
		}

		// Returns true if you are holding an invalid weapon (Knife, bomb, zeus or grenade of any type)
		bool hasInvalidWeapon()
		{
			return hasKnife() || hasBomb() || hasGrenade() || hasZeus();
		}

		// Returns true if you are holding a pistol
		bool hasPistol()
		{
			int idi = Weapon();
			return
				idi == WeaponIDI::WEAPON_DEAGLE ||			// DEAGLE
				idi == WeaponIDI::WEAPON_ELITE ||			// DUALIES
				idi == WeaponIDI::WEAPON_FIVESEVEN ||		// 5 7
				idi == WeaponIDI::WEAPON_GLOCK ||			// GLOCK
				idi == WeaponIDI::WEAPON_TEC9 ||			// TEC-9
				idi == WeaponIDI::WEAPON_HKP2000 ||			// P2000
				idi == WeaponIDI::WEAPON_P250 ||			// P250
				idi == WeaponIDI::WEAPON_USP_SILENCER ||	// USP-S
				idi == WeaponIDI::WEAPON_CZ75A ||			// CZ
				idi == WeaponIDI::WEAPON_REVOLVER;			// R8
		}

		// Returns true if you are holding a rifle
		bool hasRifle()
		{
			int idi = Weapon();
			return
				idi == WeaponIDI::WEAPON_AK47 ||
				idi == WeaponIDI::WEAPON_AUG ||
				idi == WeaponIDI::WEAPON_FAMAS ||
				idi == WeaponIDI::WEAPON_GALILAR ||
				idi == WeaponIDI::WEAPON_M4A4 ||
				idi == WeaponIDI::WEAPON_M4A1_SILENCER ||
				idi == WeaponIDI::WEAPON_SG556;
		}

		// Returns true if you are holding an SMG
		bool hasSMG()
		{
			int idi = Weapon();
			return
				idi == WeaponIDI::WEAPON_MAC10 ||
				idi == WeaponIDI::WEAPON_MP7 ||
				idi == WeaponIDI::WEAPON_MP9 ||
				idi == WeaponIDI::WEAPON_BIZON ||
				idi == WeaponIDI::WEAPON_P90 ||
				idi == WeaponIDI::WEAPON_UMP45;
		}

		// Returns true if you are holding a shotgun
		bool hasShotgun()
		{
			int idi = Weapon();
			return
				idi == WeaponIDI::WEAPON_MAG7 ||
				idi == WeaponIDI::WEAPON_NOVA ||
				idi == WeaponIDI::WEAPON_SAWEDOFF ||
				idi == WeaponIDI::WEAPON_XM1014;
		}

		// Returns true if you are holding heavy weapon
		bool hasHeavy()
		{
			int idi = Weapon();
			return
				idi == WeaponIDI::WEAPON_M249 ||
				idi == WeaponIDI::WEAPON_NEGEV;
		}

		// Returns true if you are holding a sniper
		bool hasSniper()
		{
			int idi = Weapon();
			return
				idi == WeaponIDI::WEAPON_AWP ||
				idi == WeaponIDI::WEAPON_SSG08;
		}

		// Returns true if you are holding an autonoob
		bool hasAutoNoob()
		{
			int idi = Weapon();
			return
				idi == WeaponIDI::WEAPON_G3SG1 ||
				idi == WeaponIDI::WEAPON_SCAR20;
		}

		// Force the flash duration (useful for No Flash feature)
		bool SetFlashDuration(float NewDuration)
		{
			return Process.Write<float>(Base() + Offsets::m_flFlashDuration, NewDuration);
		}

	};

}

DoubleSDK::CLocalPlayer Me;