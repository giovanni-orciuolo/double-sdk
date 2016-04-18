/// DoubleSDK.h
// This header includes everything from DoubleSDK

/*
DOUBLE SDK | A FREE CSGO SDK MADE BY DOUBLE V FOR UNKNOWNCHEATS.ME
CREDITS AND SHOUTOUTS:
Double V
WasserEsser
TeamGamerFood
Serge
*/

#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <iostream>
#include <stdint.h>
#include <sys/stat.h>

#include "Process.h"
#include "PatternScan.h"
#include "Enums.h"
#include "Math.h"
#include "Utils.h"
#include "Offsets.h"
#include "Client.h"
#include "Engine.h"
#include "LocalPlayer.h"
#include "Entity.h"

/// TODO: Add DoubleSDK's headers

#define SDKEX_CSGO_NOT_FOUND 1
#define SDKEX_CLIENTSCAN_DUMP_FAILED 2
#define SDKEX_ENGINESCAN_DUMP_FAILED 3

/// TODO: Add more error codes as you wish

// Use this function to initialize the SDK components
int InitSDK()
{
	try
	{
		if (!Process.Init()) throw SDKEX_CSGO_NOT_FOUND;
		ClientScanner.Init(Process.GetProcHandle(), Process.GetClient());
		EngineScanner.Init(Process.GetProcHandle(), Process.GetEngine());
		if (!ClientScanner.Dump()) throw SDKEX_CLIENTSCAN_DUMP_FAILED;
		if (!EngineScanner.Dump()) throw SDKEX_ENGINESCAN_DUMP_FAILED;
		Offsets::GetOffsets();
		Offsets::ForceNetvars();
		return 0;
	}
	catch (int Ex)
	{
		return Ex;
	}
}
