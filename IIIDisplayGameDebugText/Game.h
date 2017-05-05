#pragma once

extern int AddressByVersion(unsigned int _1_0, unsigned int _1_1, unsigned int _Steam);

typedef char                            Int8;
typedef unsigned char                   UInt8;
typedef signed char                     SInt8;
typedef short                           Int16;
typedef unsigned short                  UInt16;
typedef signed short                    SInt16;
typedef int                             Int;
typedef int                             Int32;
typedef unsigned int                    UInt32;
typedef signed int                      SInt32;
typedef float                           Float;
typedef Int8 Bool;
typedef Int8 Bool8;
typedef Int16 Bool16;
typedef Int32 Bool32;
typedef Int8 Char;
typedef UInt16 WChar;

class CRGBA
{
public:
	UInt8 r;
	UInt8 g;
	UInt8 b;
	UInt8 a;
	
	CRGBA(UInt8 nRed, UInt8 nGreen, UInt8 nBlue, UInt8 nAlpha) : r(nRed), g(nGreen), b(nBlue), a(nAlpha)
	{
		;
	}
};

class CVector
{
public:
	Float x;
	Float y;
	Float z;
	
	CVector()
	{
		;
	}
	
	CVector(Float fX, Float fY, Float fZ) : x(fX), y(fY), z(fZ)
	{
		;
	}
	
	inline CVector const& operator = (CVector const &refRight)
	{
		x = refRight.x;
		y = refRight.y;
		z = refRight.z;
		return *this;
	} 
};

class CRect
{
public:
	Float left;
	Float bottom;
	Float right;
	Float top;
	
	CRect()
	{
		left = 1000000.0f;
		top = 1000000.0f;
		right = -1000000.0f;
		bottom = -1000000.0f;
	}
	
	CRect(Float fLeft, Float fTop, Float fRight, Float fBottom) : left(fLeft), top(fTop), right(fRight), bottom(fBottom)
	{
		;
	}
	
};

enum eFontStyle : UInt16
{
	FONT_BANK = 0,
	FONT_PAGER,
	FONT_HEADING
};

class CFont
{
public:
	static void SetScale(Float w, Float h);
	static void SetColor(CRGBA color);
	static void SetJustifyOff();
	static void SetCentreOff();
	static void SetWrapx(Float value);
	static void SetBackgroundOff();
	static void SetBackGroundOnlyTextOff();
	static void SetRightJustifyOff();
	static void SetPropOff();
	static void SetPropOn();
	static void SetFontStyle(eFontStyle style);
	static void PrintString(Float x, Float y, WChar *text);
};

extern void AsciiToUnicode(Char const* ascii, WChar* uni);

class CTimer
{
public:
	static Float& ms_fTimeStepNonClipped;
};

class CCamera
{
public:
	char _unk[75];
	Bool m_bDebugCamPCOn;
};
extern CCamera& TheCamera;


typedef SInt16 tField;

class CControllerState
{
public:
	tField LEFTSTICKX;
	tField LEFTSTICKY;
	tField RIGHTSTICKX;
	tField RIGHTSTICKY;
	tField LEFTSHOULDER1;
	tField LEFTSHOULDER2;
	tField RIGHTSHOULDER1;
	tField RIGHTSHOULDER2;
	tField DPADUP;
	tField DPADDOWN;
	tField DPADLEFT;
	tField DPADRIGHT;
	tField START;
	tField SELECT;
	tField SQUARE;
	tField TRIANGLE;
	tField CROSS;
	tField CIRCLE;
	tField LEFTSHOCK;
	tField RIGHTSHOCK;
	tField field_28; //Guide ?
};

class CPad
{
public:
	CControllerState NewState;
	CControllerState OldState;
	CControllerState PCTempKeyState;
	CControllerState PCTempJoyState;
	CControllerState PCTempMouseState;
	Int16 ReadyState;
	Int16 Mode;
	Int16 field_D6;
	Int8 field_D8;
	Int8 field_D9[5];
	Int8 field_DE;
	Int8 field_DF;
	Bool field_E0;
	Int8 field_E1[15];
	Int32 field_F0;
	Int32 field_F4;
	Int32 field_F8;
	
	static CPad *GetPad(Int32 num);
};

struct tZonePrint
{
	Char name[12];
	CRect rect;
};

struct RsGlobalType
{
	const Char *appName;
	Int32 maximumWidth;
	Int32 maximumHeight;
	Int32 w;
	Int32 h;
	Int32 maxFPS;
	Bool32 quit;
	void *ps;
	int keyboard;
	int mouse;
	int pad;
};

extern tZonePrint *ZonePrint;
extern Char *version_name;
extern RsGlobalType &RsGlobal;
extern CVector FindPlayerCoors();