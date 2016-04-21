/// Engine.h
// This header defines the CEngine class

/*
The CEngine class allows you to grab and set important info from the engine.dll module, using
the CProcess class already defined in Process.h;
Just call a function from here to get what you want from the engine.
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

class CEngine
{
public:

	// Returns a pointer to the engine as DWORD
	DWORD EnginePointer()
	{
		return Process.Read<DWORD>(Process.GetEngineBase() + Offsets::m_dwEnginePointer);
	}

	// Returns engine view angles as Vector3
	Vector3 ViewAngles()
	{
		return Process.Read<Vector3>(EnginePointer() + Offsets::m_dwViewAngles);
	}

	// Returns the current value of SigOnState as int
	int StateSig()
	{
		return Process.Read<int>(EnginePointer() + 0x100);
	}

	// Returns true if the user is connected and playing
	bool IsPlaying()
	{
		return Process.Read<int>(EnginePointer() + 0x100) == SigOnState::FULL_CONNECTED;
	}

	// Sets the engine view angles using VirtualProtect
	// Returns true if successful
	bool SetViewAngles(Vector3 NewAngles)
	{
		return Process.WriteProtected<Vector3>(EnginePointer() + Offsets::m_dwViewAngles, NewAngles);
	}

	// Force a full update. Returns true if successful
	bool ForceFullUpdate()
	{
		return Process.Write<int>(EnginePointer() + 0x16C, -1);
	}
	
	// Translates 3D coords into 2D coords
	// Retruns true if successful
	bool WorldToScreen(Vector3 ThreeDCoordinates, Vector2 &TwoDCoordinates)
	{
		RECT rc;
		HWND hWnd = FindWindow(L"Valve001", NULL);
		GetWindowRect(hWnd, &rc);

		WorldToScreenMatrix_t WorldToScreenMatrix;
		WorldToScreenMatrix = Process.Read<WorldToScreenMatrix_t>(Process.GetClientBase() + Offsets::m_dwViewMatrix);
		float w = 0.0f;

		TwoDCoordinates.x = WorldToScreenMatrix.flMatrix[0][0] * ThreeDCoordinates.x + WorldToScreenMatrix.flMatrix[0][1] * ThreeDCoordinates.y + WorldToScreenMatrix.flMatrix[0][2] * ThreeDCoordinates.z + WorldToScreenMatrix.flMatrix[0][3];
		TwoDCoordinates.y = WorldToScreenMatrix.flMatrix[1][0] * ThreeDCoordinates.x + WorldToScreenMatrix.flMatrix[1][1] * ThreeDCoordinates.y + WorldToScreenMatrix.flMatrix[1][2] * ThreeDCoordinates.z + WorldToScreenMatrix.flMatrix[1][3];
		w = WorldToScreenMatrix.flMatrix[3][0] * ThreeDCoordinates.x + WorldToScreenMatrix.flMatrix[3][1] * ThreeDCoordinates.y + WorldToScreenMatrix.flMatrix[3][2] * ThreeDCoordinates.z + WorldToScreenMatrix.flMatrix[3][3];

		if (w < 0.01f)
			return false;

		float invw = 1.0f / w;
		TwoDCoordinates.x *= invw;
		TwoDCoordinates.y *= invw;

		int width = (int)(rc.right - rc.left);
		int height = (int)(rc.bottom - rc.top);

		float x = width / 2;
		float y = height / 2;

		x += 0.5 * TwoDCoordinates.x * width + 0.5;
		y -= 0.5 * TwoDCoordinates.y * height + 0.5;

		TwoDCoordinates.x = x + rc.left;
		TwoDCoordinates.y = y + rc.top;

		return true;
	}

};

}

DoubleSDK::CEngine Engine;