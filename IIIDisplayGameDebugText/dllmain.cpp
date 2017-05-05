#include <windows.h>
#include <stdio.h>
#include "Game.h"
#include "CPatch.h"

//#define PAD_NUMBER 1 //default
#define PAD_NUMBER 0

Float FramesPerSecond = 30.0f;

Float FramesPerSecondCounter;
Int32 FrameSamples;

void DisplayGameDebugText()
{
	static Bool bDisplayPosn = false;
    static Bool bDisplayRate = false;

	Char str[200];
	WChar ustr[200];
	WChar uversion_name[200];
	
	AsciiToUnicode(version_name, uversion_name);

	CFont::SetPropOn();
	CFont::SetBackgroundOff();
	CFont::SetFontStyle(FONT_BANK);
	CFont::SetScale(((RsGlobal.h * 0.0020833334f) / 1.0f) * 0.5f, ((RsGlobal.h * 0.0020833334f) / 1.0f) * 0.5f);
	CFont::SetCentreOff();
	CFont::SetRightJustifyOff();
	CFont::SetWrapx(RsGlobal.w);
	CFont::SetJustifyOff();
	CFont::SetBackGroundOnlyTextOff();
	CFont::SetColor(CRGBA(255, 108, 0, 255));
	CFont::PrintString(10.0f, 10.0f, uversion_name);

	++FrameSamples;
	FramesPerSecondCounter = 1000.0f / (CTimer::ms_fTimeStepNonClipped * 0.02f * 1000.0f) + FramesPerSecondCounter;
	FramesPerSecond = FramesPerSecondCounter / FrameSamples;
	
	if ( FrameSamples > 30 )
	{
		FramesPerSecondCounter = 0.0f;
		FrameSamples = 0;
	}
  
	if ( !TheCamera.m_bDebugCamPCOn && CPad::GetPad(PAD_NUMBER)->NewState.SQUARE && CPad::GetPad(PAD_NUMBER)->NewState.TRIANGLE )
	{
		if ( CPad::GetPad(PAD_NUMBER)->NewState.LEFTSHOULDER2 && CPad::GetPad(PAD_NUMBER)->OldState.LEFTSHOULDER2 )
			bDisplayPosn = !bDisplayPosn;
	}

	if ( CPad::GetPad(PAD_NUMBER)->NewState.SQUARE && CPad::GetPad(PAD_NUMBER)->NewState.TRIANGLE )
	{
		if ( CPad::GetPad(PAD_NUMBER)->NewState.RIGHTSHOULDER2 && !CPad::GetPad(PAD_NUMBER)->OldState.RIGHTSHOULDER2 )
			bDisplayRate = !bDisplayRate;
	}
	
	if ( bDisplayPosn || bDisplayRate )
	{
		CVector pos = FindPlayerCoors();
		Int32 ZoneId = 9;
		
		for ( Int32 i = 0; i < 9; i++ )
		{
			if ( pos.x > ZonePrint[i].rect.left
				&& pos.x < ZonePrint[i].rect.right
				&& pos.y > ZonePrint[i].rect.bottom
				&& pos.y < ZonePrint[i].rect.top )
			{
				ZoneId = i;
			}
		}

		if ( bDisplayRate )
		{
			/*
				correct float to int conversion hack
			*/
			Int32 fps = 0;
			_asm
			{
				fld FramesPerSecond
				fistp fps
			}
			sprintf(str, "X:%5.1f, Y:%5.1f, Z:%5.1f, F-%d, %s", pos.x, pos.y, pos.z, fps, ZonePrint[ZoneId].name);
			
			// Original line
			// sprintf(str, "X:%5.1f, Y:%5.1f, Z:%5.1f, F-%d, %s", pos.x, pos.y, pos.z, (SInt32)FramesPerSecond, ZonePrint[ZoneId].name);
		}
		else
			sprintf(str, "X:%5.1f, Y:%5.1f, Z:%5.1f, %s", pos.x, pos.y, pos.z, ZonePrint[ZoneId].name);
		
		AsciiToUnicode(str, ustr);
		
		CFont::SetPropOff();
		CFont::SetBackgroundOff();
		CFont::SetScale(0.7f, 1.5f);
		CFont::SetCentreOff();
		CFont::SetRightJustifyOff();
		CFont::SetJustifyOff();
		CFont::SetBackGroundOnlyTextOff();
		CFont::SetWrapx(640.0f);
		CFont::SetFontStyle(FONT_HEADING);
		
		CFont::SetColor(CRGBA(0, 0, 0, 255));
		CFont::PrintString(42.0f, 42.0f, ustr);
		
		CFont::SetColor(CRGBA(255, 108, 0, 255));
		CFont::PrintString(40.0f, 40.0f, ustr);
	}
}

void (__cdecl *_Render)();
void Render()
{
	DisplayGameDebugText();
	_Render();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
	if(reason == DLL_PROCESS_ATTACH)
	{
		_Render = (void (__cdecl *)())CPatch::MakeCallAddr(AddressByVersion(0x48E470, 0x48E530, 0x48E4C0), AddressByVersion(0x509030, 0x509110, 0x5090A0));
		CPatch::RedirectCall(AddressByVersion(0x48E470, 0x48E530, 0x48E4C0), Render);
	}
	return TRUE;
}