#include "Seperator.h"

#include <Graphics.h>

using namespace CKT::GUI;

CSeperator::CSeperator()
{
	m_IsSeperator = true;
}

CKT::GUI::CSeperator::CSeperator(PRENDERER ren, float s, CColor colFront, CColor colBack)
{
	m_IsSeperator = true;
	Init(ren, 0, 0, s, s, colFront, colBack);
}


CSeperator::~CSeperator()
{
}

int CKT::GUI::CSeperator::Init(PRENDERER ren, float x, float y, float w, float h, CColor foreGround, CColor backGround)
{
	m_PosX = x;
	m_PosY = y;

	m_DesignX = m_PosX;
	m_DesignY = m_PosY;

	m_Width = w;
	m_Height = h;

	m_DesignWidth = m_Width;
	m_DesignHeight = m_Height;

	m_rClip = { (int)m_PosX, (int)m_PosY, (int)m_Width, (int)m_Height };

	m_BackgroundColor = backGround.ToSDLColor();
	m_Foreground = foreGround;

	m_pRenderer = ren;

	return 0;
}

int CKT::GUI::CSeperator::Render()
{
	CGUIBase::Render();

	float newSize = 0;
	float diffSize = 0;
	if(m_Oriantation == VER)
	{
		newSize = m_Width * 95 / 100;
		diffSize = (m_Width - newSize) / 2;
	}
	else
	{
		newSize = m_Height * 95 / 100;
		diffSize = (m_Height - newSize) / 2;
	}

	GFX::FillRect(m_pRenderer, m_PosX + diffSize, m_PosY, newSize, m_Height, m_Foreground.ToSDLColor());

	return 0;
}
