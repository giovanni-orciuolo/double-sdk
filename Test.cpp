/// Test.cpp
// Example of using for the DoubleSDK

/*
DOUBLE SDK | A FREE CSGO SDK MADE BY DOUBLE V FOR UNKNOWNCHEATS.ME
CREDITS AND SHOUTOUTS:
Double V
WasserEsser
TeamGamerFood
Serge
*/

#include "DoubleSDK.h"
using namespace DoubleSDK;
using namespace std;

/// LITTLE AND SIMPLE BHOP MADE WITH DOUBLE SDK
int main()
{
	bool Enabled = false;
	int Result = InitSDK(); // Initialize the SDK and store the result in a variable
	SetConsoleTitleA("L33T BHOP MADE WITH DOUBLE SDK"); // Set the console title

	switch (Result) // Check for the result of initialization
	{
	case SDKEX_CSGO_NOT_FOUND:
		ThrowError("CS:GO not found!");
	break;
	case SDKEX_CLIENTSCAN_DUMP_FAILED:
		ThrowError("Failed to dump client.dll!");
	break;
	case SDKEX_ENGINESCAN_DUMP_FAILED:
		ThrowError("Failed to dump engine.dll!");
	break;
	}

	if (Result != 0) return 1; // Close the cheat if any of these exceptions occurred

	// If we are here this means that we initialized all stuff correctly, and we can print out some welcome screen
	printf(">-- DOUBLE SDK BHOP --<\n");
	printf("Press F1 to toggle bunny hop\n");
	printf("Press F2 to close the cheat\n");

	// Since it's only a bhop, I do not need threads
	while (true)
	{
		// Check for input
		if (GetAsyncKeyState(VK_F1))
		{
			Enabled = !Enabled;
			(Enabled) ? printf("BunnyHop enabled!\n") : printf("BunnyHop disabled\n");
			Sleep(250);
		}
		if (GetAsyncKeyState(VK_F2)) return 0;

		// Bunny Hop loop

		if (!Enabled) continue; // Check if the bhop is enabled

		if (GetAsyncKeyState(VK_SPACE) & 0x8000) // Check if the user is pressing the spacebar
		{
			if (Me.OnGround()) // Check if the local player is on ground
			{
				// Perform bhop
				Client.ForceJump();
				Sleep(20);
				Client.StopJump();
			}
		}

	}

	// Perform clean up here
	ClientScanner.Clear(); // Clear the dumped client.dll
	EngineScanner.Clear(); // Clear the dumped engine.dll
	Process.Clear(); // Close the handle to CS:GO
	return 0;
}