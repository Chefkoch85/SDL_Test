#include "Include\Color.h"

using namespace CKT;

void CKT::CColor::CheckColor()
{
	if (m_Red < 0)
		m_Red = 0;
	else if (m_Red > 255)
		m_Red = 255;

	if (m_Green < 0)
		m_Green = 0;
	else if (m_Green > 255)
		m_Green = 255;

	if (m_Blue < 0)
		m_Blue = 0;
	else if (m_Blue > 255)
		m_Blue = 255;

	if (m_Alpha < 0)
		m_Alpha = 0;
	else if (m_Alpha > 255)
		m_Alpha = 255;
}

CColor::CColor()
{
}


CKT::CColor::CColor(Uint32 c)
{
	m_Red = ((c & 0xFF000000) >> 24);
	m_Green = ((c & 0x00FF0000) >> 16);
	m_Blue = ((c & 0x0000FF00) >> 8);
	m_Alpha = (c & 0x000000FF);

	CheckColor();
}

CKT::CColor::CColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	m_Red = r;
	m_Green = g;
	m_Blue = b;
	m_Alpha = a;

	CheckColor();
}

CKT::CColor::CColor(SDL_Color c)
{
	m_Red = c.r;
	m_Green = c.g;
	m_Blue = c.b;
	m_Alpha = c.a;

	CheckColor();
}

CColor::~CColor()
{
}

SDL_Color CKT::CColor::ToSDLColor()
{
	return { m_Red, m_Green, m_Blue, m_Alpha };
}

Uint32 CKT::CColor::ToWordColor()
{
	Uint32 c = (m_Red << 24);
	c |= (m_Green << 16);
	c |= (m_Blue << 8);
	c |= (m_Alpha);

	return c;
}

CColor CKT::CColor::Complement()
{
	return CColor(255 - m_Red, 255 - m_Green, 255 - m_Blue, m_Alpha);
}

CColor CKT::CColor::operator+(CColor& rv)
{
	Uint8 r = m_Red - rv.m_Red;
	Uint8 g = m_Green - rv.m_Green;
	Uint8 b = m_Blue - rv.m_Blue;
	
	return CColor(r, g, b, m_Alpha);
}


CColor CKT::CColor::operator-(CColor& rv)
{
	Uint8 r = m_Red - rv.m_Red;
	Uint8 g = m_Green - rv.m_Green;
	Uint8 b = m_Blue - rv.m_Blue;

	return CColor(r, g, b, m_Alpha);
}

CColor& CKT::CColor::operator+=(CColor& rv)
{
	m_Red += rv.m_Red;
	m_Green += rv.m_Green;
	m_Blue += rv.m_Blue;

	CheckColor();

	return *this;
}

CColor& CKT::CColor::operator-=(CColor& rv)
{
	m_Red -= rv.m_Red;
	m_Green -= rv.m_Green;
	m_Blue -= rv.m_Blue;

	CheckColor();

	return *this;
}