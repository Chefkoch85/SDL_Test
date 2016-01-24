#include "Progressbar.h"


using namespace CKT::GUI;

CProgressbar::CProgressbar()
{
}


CProgressbar::~CProgressbar()
{
}

int CKT::GUI::CProgressbar::Init(PRENDERER ren, float x, float y, float w, float h)
{
	m_pRenderer = ren;

	m_PosX = x;
	m_PosY = y;
	m_Width = w;
	m_Height = h;

	return 0;
}

int CKT::GUI::CProgressbar::Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s)
{
	CGUIBase::Init(ren, file, x, y, w, h, s);

	return 0;
}

int CKT::GUI::CProgressbar::Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s)
{
	CGUIBase::Init(ren, file, x, y, xTiles, yTiles, s);

	return 0;
}
