#include "Game.h"
#include <Windows.h>

static int nVersion            = -1;
static bool bAutoVersionCheck   = true;


enum eGame
{
    Unknown_Game    = 0,
    GTA_3_1_0,
    GTA_3_1_1,
    GTA_3_Steam,
};

static char *aGameVer [] = 
{
    "",
    "GTA_3_1_0",
    "GTA_3_1_1",
    "GTA_3_Steam"
};

static DWORD getModuleEntryPointAddress(HANDLE hModule) 
{
	IMAGE_DOS_HEADER * pDOSHeader = (IMAGE_DOS_HEADER *)hModule;
	IMAGE_NT_HEADERS * pNTHeaders = (IMAGE_NT_HEADERS*)((BYTE*)pDOSHeader + pDOSHeader->e_lfanew);
	return pNTHeaders->OptionalHeader.AddressOfEntryPoint + (DWORD)pDOSHeader;
}

static DWORD getGameVersion(HANDLE hModule = NULL) 
{
	enum
	{
		ENTRYPOINT_1_0                  = 0x5C1E70,
		ENTRYPOINT_1_1                  = 0x5C2130,
		ENTRYPOINT_1_1_BUKA_1C          = 0x985240,
		ENTRYPOINT_STEAM                = 0x9912ED,
		ENTRYPOINT_STEAM_CRACKED        = 0x5C6FD0,
	};

	if (!hModule) 
		hModule = GetModuleHandle(NULL);
	
	DWORD dwEntryPoint = getModuleEntryPointAddress(hModule);
	switch (dwEntryPoint) 
	{
		case ENTRYPOINT_1_0:
			return GTA_3_1_0;
		case ENTRYPOINT_1_1:
		case ENTRYPOINT_1_1_BUKA_1C:
			return GTA_3_1_1;
		case ENTRYPOINT_STEAM:
		case ENTRYPOINT_STEAM_CRACKED:
			return GTA_3_Steam;
	}
	return Unknown_Game;
}

static eGame GetGameVersion()
{
	nVersion = (eGame)getGameVersion();
	return (eGame)nVersion;
}

int AddressByVersion(unsigned int _1_0, unsigned int _1_1, unsigned int _Steam)
{
    if (bAutoVersionCheck && nVersion == -1)
    {
        GetGameVersion();
    }

    switch ( nVersion )
    {
        case GTA_3_1_0:
           return _1_0;
           break;
        case GTA_3_1_1:
           return _1_1;
           break;
        case GTA_3_Steam:
           return _Steam;
           break;
    }
}

tZonePrint *ZonePrint = (tZonePrint *)AddressByVersion(0x5F5274, 0x5F5164, 0x60215C);
Char *version_name = (Char *)AddressByVersion(0x70D990, 0x70D990, 0x71DAD0);
Float& CTimer::ms_fTimeStepNonClipped = *(Float *)AddressByVersion(0x8E2C4C, 0x8E2D00, 0x8F2E40);
CCamera& TheCamera = *(CCamera*)AddressByVersion(0x6FACF8, 0x6FACF8, 0x70AE38);
RsGlobalType &RsGlobal = *(RsGlobalType *)AddressByVersion(0x8F4360, 0x8F4414, 0x904554);

void CFont::SetScale(Float w, Float h)
{
	((void (__cdecl *)(Float, Float))AddressByVersion(0x501B80, 0x501C60, 0x501BF0))(w, h);
}

void CFont::SetColor(CRGBA color)
{
	((void (__cdecl *)(CRGBA *))AddressByVersion(0x501BD0, 0x501CB0, 0x501C40))(&color);
}

void CFont::SetJustifyOff()
{
	((void (__cdecl *)())AddressByVersion(0x501C80, 0x501D60, 0x501CF0))();
}

void CFont::SetCentreOff()
{
	((void (__cdecl *)())AddressByVersion(0x501CB0, 0x501D90, 0x501D20))();
}

void CFont::SetWrapx(Float value)
{
	((void (__cdecl *)(Float))AddressByVersion(0x501CC0, 0x501DA0, 0x501D30))(value);
}

void CFont::SetBackgroundOff()
{
	((void (__cdecl *)())AddressByVersion(0x501CF0, 0x501DD0, 0x501D60))();
}

void CFont::SetBackGroundOnlyTextOff()
{
	((void (__cdecl *)())AddressByVersion(0x501D40, 0x501E20, 0x501DB0))();
}

void CFont::SetRightJustifyOff()
{
	((void (__cdecl *)())AddressByVersion(0x501D70, 0x501E50, 0x501DE0))();
}

void CFont::SetPropOff()
{
	((void (__cdecl *)())AddressByVersion(0x501D90, 0x501E70, 0x501E00))();
}

void CFont::SetPropOn()
{
	((void (__cdecl *)())AddressByVersion(0x501DA0, 0x501E80, 0x501E10))();
}

void CFont::SetFontStyle(eFontStyle style)
{
	((void (__cdecl *)(eFontStyle))AddressByVersion(0x501DB0, 0x501E90, 0x501E20))(style);
}

void CFont::PrintString(Float x, Float y, WChar *text)
{
	((void (__cdecl *)(Float, Float, WChar *))AddressByVersion(0x500F50, 0x501030, 0x500FC0))(x, y, text);
}

void AsciiToUnicode(Char const* ascii, WChar* uni)
{
	((void (__cdecl *)(Char const*, WChar*))AddressByVersion(0x5009C0, 0x500AA0, 0x500A30))(ascii, uni);
}

CPad *CPad::GetPad(Int32 num)
{
	return ((CPad *(__cdecl*)(Int32))AddressByVersion(0x492F60, 0x493020, 0x492FB0))(num);
}

CVector FindPlayerCoors()
{
	return ((CVector (__cdecl *)())AddressByVersion(0x4A1030, 0x4A1120, 0x4A10B0))();
}