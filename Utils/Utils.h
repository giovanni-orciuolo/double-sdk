/// Utils.h
// This header defines several non-namespaced methods and structs that can help you (maybe)

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

// Struct definition for a glow object
struct GlowObject_t
{
	DWORD pEntity;
	float r;
	float g;
	float b;
	float a;
	uint8_t unk1[16];
	bool RenderWhenOccluded;
	bool RenderWhenUnoccluded;
	bool FullBloom;
	uint8_t unk2[14];
};

// Struct definition for an RGBA color
// Kind of rough, can be improved ofc
struct RGBA
{
	float r, g, b, a;
};

// Struct definition for the WorldToScreenMatrix 4x4
typedef struct
{
	float flMatrix[4][4];
} WorldToScreenMatrix_t;

// Returns true if a file exists at a given path
// Credits: StackOverflow
bool FileExists(std::string Path)
{
	struct stat buffer;   
	return (stat (Path.c_str(), &buffer) == 0);
}

// Clearns screen without needing to call shit "system"
// Credits: StackOverflow
void ClearScreen()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hStdOut;
	DWORD count;
	DWORD cellCount;
	COORD homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if( hStdOut == INVALID_HANDLE_VALUE ) return;

	if( !GetConsoleScreenBufferInfo( hStdOut, &csbi ) ) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	if( !FillConsoleOutputCharacter( hStdOut, ( TCHAR ) ' ', cellCount, homeCoords, &count ) )
		return;

	if( !FillConsoleOutputAttribute( hStdOut, csbi.wAttributes, cellCount, homeCoords, &count ) )
		return;
	SetConsoleCursorPosition( hStdOut, homeCoords );
}

// Throws a log as a MessageBox
int ThrowLog(std::string Log, UINT uType = MB_ICONINFORMATION | MB_OK, ...)
{
	va_list v1;
	va_start(v1, Log);
	char buff[1024];
	vsprintf_s(buff, Log.c_str(), v1);
	return MessageBoxA(NULL, buff, "LOG", uType);
}

// Throws a error as a MessageBox
int ThrowError(std::string Error, UINT uType = MB_ICONSTOP | MB_OK, ...)
{
	va_list v1;
	va_start(v1, Error);
	char buff[1024];
	vsprintf_s(buff, Error.c_str(), v1);
	return MessageBoxA(NULL, buff, "ERROR", uType);
}

// Converts a const char* to LPCWSTR
static wchar_t* CharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}