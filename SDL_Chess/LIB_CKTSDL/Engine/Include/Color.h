#pragma once

#include "Common.h"

namespace CKT
{
	class CColor
	{
	public:
//#define COLTRANS	CColor(0,0,0,0)
//#define COLBLACK	CColor(0,0,0,255)
//#define COLRED		CColor(255,0,0,255)
//#define COLGREEN	CColor(0,255,0,255)
//#define COLBLUE		CColor(0,0,255,255)
//#define COLWHITE	CColor(255,255,255,255);

	private:
		Uint8 m_Red = 0;
		Uint8 m_Green = 0;
		Uint8 m_Blue = 0;
		Uint8 m_Alpha = 255;

		void CheckColor();

	public:
		DllExport CColor();
		/*
		*c = color as UINT32
		*1. byte: red; 2. byte: green; 3. byte: blue; 4. byte: alpha
		*/
		DllExport CColor(Uint32 c);
		DllExport CColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
		DllExport CColor(SDL_Color c);
		DllExport ~CColor();

	public:
		DllExport Uint8& R() { return m_Red; }
		DllExport Uint8& G() { return m_Green; }
		DllExport Uint8& B() { return m_Blue; }
		DllExport Uint8& A() { return m_Alpha; }

	public:
		DllExport SDL_Color ToSDLColor();
		DllExport Uint32 ToWordColor();

	public:
		DllExport CColor Complement();

	public:
		DllExport CColor operator+(CColor& rv);
		DllExport CColor operator-(CColor& rv);

		DllExport CColor& operator+=(CColor& rv);
		DllExport CColor& operator-=(CColor& rv);
	};

}
