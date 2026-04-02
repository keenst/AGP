#pragma once

namespace CommonUtilities
{


enum class KeyCode : int
{
	MouseLeft = 0x01,
	MouseRight = 0x02,
	Cancel = 0x03,
	MouseMiddle = 0x04,

	MouseX1 = 0x05,
	MouseX2 = 0x06,

	Backspace = 0x08,
	Tab = 0x09,

	Clear = 0x0C,
	Enter = 0x0D,

	Shift = 0x10,
	Control = 0x11,
	Alt = 0x12,
	Pause = 0x13,
	CapsLock = 0x14,

	KANA = 0x15,
	HANGUL = 0x15,
	JUNJA = 0x17,
	FINAL = 0x18,
	HANJA = 0x19,
	KANJI = 0x19,

	Escape = 0x1B,

	CONVERT = 0x1C,
	NONCONVERT = 0x1D,
	ACCEPT = 0x1E,
	MODECHANGE = 0x1F,

	Space = 0x20,
	PageUp = 0x21, //page up
	PageDown = 0x22, //page down
	End = 0x23,
	Home = 0x24,
	Left = 0x25,
	Up = 0x26,
	Right = 0x27,
	Down = 0x28,
	Select = 0x29,
	Print = 0x2A,
	Execute = 0x2B,
	PrintScreen = 0x2C,
	Insert = 0x2D,
	Delete = 0x2E,
	Help = 0x2F,

	Alpha0 = 0x30, 	//0 key
	Alpha1 = 0x31, 	//1 key
	Alpha2 = 0x32, 	//2 key
	Alpha3 = 0x33, 	//3 key
	Alpha4 = 0x34, 	//4 key
	Alpha5 = 0x35, 	//5 key
	Alpha6 = 0x36, 	//6 key
	Alpha7 = 0x37, 	//7 key
	Alpha8 = 0x38, 	//8 key
	Alpha9 = 0x39, 	//9 key

	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,
	//
	LeftWin = 0x5B,
	RightWin = 0x5C,
	App = 0x5D,

	Sleep = 0x5F,

	Numpad0 = 0x60,
	Numpad1 = 0x61,
	Numpad2 = 0x62,
	Numpad3 = 0x63,
	Numpad4 = 0x64,
	Numpad5 = 0x65,
	Numpad6 = 0x66,
	Numpad7 = 0x67,
	Numpad8 = 0x68,
	Numpad9 = 0x69,
	Multiply = 0x6A,
	Add = 0x6B,
	Separator = 0x6C,
	Subtract = 0x6D,
	Decimal = 0x6E,
	Divide = 0x6F,
	F1 = 0x70,
	F2 = 0x71,
	F3 = 0x72,
	F4 = 0x73,
	F5 = 0x74,
	F6 = 0x75,
	F7 = 0x76,
	F8 = 0x77,
	F9 = 0x78,
	F10 = 0x79,
	F11 = 0x7A,
	F12 = 0x7B,
	F13 = 0x7C,
	F14 = 0x7D,
	F15 = 0x7E,
	F16 = 0x7F,
	F17 = 0x80,
	F18 = 0x81,
	F19 = 0x82,
	F20 = 0x83,
	F21 = 0x84,
	F22 = 0x85,
	F23 = 0x86,
	F24 = 0x87,

	NumLock = 0x90,
	ScrollLock = 0x91,

	OEM_NEC_EQUAL = 0x92,		// '=' key on numpad

	OEM_FJ_JISHO = 0x92,	// 'Dictionary' key
	OEM_FJ_MASSHOU = 0x93,   // 'Unregister word' key
	OEM_FJ_TOUROKU = 0x94,   // 'Register word' key
	OEM_FJ_LOYA = 0x95,		// 'Left OYAYUBI' key
	OEM_FJ_ROYA = 0x96,		// 'Right OYAYUBI' key

	LeftShift = 0xA0,
	RightShift = 0xA1,
	LeftControl = 0xA2,
	RightControl = 0xA3,
	LeftAlt = 0xA4,
	RightAlt = 0xA5,

	BrowserBack = 0xA6,
	BrowserForward = 0xA7,
	BrowserRefresh = 0xA8,
	BrowserStop = 0xA9,
	BrowserSearch = 0xAA,
	BrowserFavorites = 0xAB,
	BrowserHome = 0xAC,

	VolumeMute = 0xAD,
	VolumeDown = 0xAE,
	VolumeUp = 0xAF,
	MediaNextTrack = 0xB0,
	MediaPreviousTrack = 0xB1,
	MediaStop = 0xB2,
	MediaPlayPause = 0xB3,
	LaunchMail = 0xB4,
	LaunchMedia = 0xB5,
	LaunchApp1 = 0xB6,
	LaunchApp2 = 0xB7,

	OEM_1 = 0xBA,   // ';:' for US
	OEM_PLUS = 0xBB,   // '+' any country
	OEM_COMMA = 0xBC,   // ',' any country
	OEM_MINUS = 0xBD,   // '-' any country
	OEM_PERIOD = 0xBE,   // '.' any country
	OEM_2 = 0xBF,   // '/?' for US
	OEM_3 = 0xC0,   // '`~' for US

	Gamepad_A = 0xC3, // reserved
	Gamepad_B = 0xC4, // reserved
	Gamepad_X = 0xC5, // reserved
	Gamepad_Y = 0xC6, // reserved
	Gamepad_RightShoulder = 0xC7, // reserved
	Gamepad_LeftShoulder = 0xC8, // reserved
	Gamepad_LeftTrigger = 0xC9, // reserved
	Gamepad_RightTrigger = 0xCA, // reserved
	Gamepad_DpadUp = 0xCB, // reserved
	Gamepad_DpadDown = 0xCC, // reserved
	Gamepad_DpadLeft = 0xCD, // reserved
	Gamepad_DpadRight = 0xCE, // reserved
	Gamepad_Menu = 0xCF, // reserved
	Gamepad_View = 0xD0, // reserved
	Gamepad_LeftThumbstickButton = 0xD1, // reserved
	Gamepad_RightThumbstickButton = 0xD2, // reserved
	Gamepad_LeftThumbstickUp = 0xD3, // reserved
	Gamepad_LeftThumbstickDown = 0xD4, // reserved
	Gamepad_LeftThumbstickRight = 0xD5, // reserved
	Gamepad_LeftThumbstickLeft = 0xD6, // reserved
	Gamepad_RightThumbstickUp = 0xD7, // reserved
	Gamepad_RightThumbstickDown = 0xD8, // reserved
	Gamepad_RightThumbstickRight = 0xD9, // reserved
	Gamepad_RightThumbstickLeft = 0xDA, // reserved

	OEM_4 = 0xDB,  //  '[{' for US
	OEM_5 = 0xDC,  //  '\|' for US
	OEM_6 = 0xDD,  //  ']}' for US
	OEM_7 = 0xDE,  //  ''"' for US
	OEM_8 = 0xDF,

	OEM_AX = 0xE1,  //  'AX' key on Japanese AX kbd
	OEM_102 = 0xE2,  //  "<>" or "\|" on RT 102-key kbd.
	ICO_HELP = 0xE3,  //  Help key on ICO
	ICO_00 = 0xE4,  //  00 key on ICO

	PROCESSKEY = 0xE5,

	ICO_CLEAR = 0xE6,

	PACKET = 0xE7,

	OEM_RESET = 0xE9,
	OEM_JUMP = 0xEA,
	OEM_PA1 = 0xEB,
	OEM_PA2 = 0xEC,
	OEM_PA3 = 0xED,
	OEM_WSCTRL = 0xEE,
	OEM_CUSEL = 0xEF,
	OEM_ATTN = 0xF0,
	OEM_FINISH = 0xF1,
	OEM_COPY = 0xF2,
	OEM_AUTO = 0xF3,
	OEM_ENLW = 0xF4,
	OEM_BACKTAB = 0xF5,

	ATTN = 0xF6,
	CRSEL = 0xF7,
	EXSEL = 0xF8,
	EREOF = 0xF9,
	PLAY = 0xFA,
	ZOOM = 0xFB,
	NONAME = 0xFC,
	PA1 = 0xFD,
	OEM_CLEAR = 0xFE
};

}