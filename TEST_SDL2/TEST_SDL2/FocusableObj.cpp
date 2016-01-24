#include "FocusableObj.h"


using namespace CKT::GUI;

CFocusableObj::CFocusableObj()
{
	m_FocusClipPoints[0] = { -1,-1 };
	m_FocusClipPoints[1] = { -1,-1 };
}


CFocusableObj::~CFocusableObj()
{
	if (m_EventArgs)
		delete m_EventArgs;
}

void CKT::GUI::CFocusableObj::SetClippingPoints(int x1, int y1, int x2, int y2)
{
	m_FocusClipPoints[0].x = x1;
	m_FocusClipPoints[0].y = y1;
	m_FocusClipPoints[1].x = x2;
	m_FocusClipPoints[1].y = y2;
}

void CKT::GUI::CFocusableObj::SetFocusChanged(GotFocus gotFunc, LostFocus lostFunc, void * objForCallback)
{
	m_OnGotFocus = gotFunc;
	m_OnLostFocus = lostFunc;
	m_ObjForCallback = objForCallback;
}

int CKT::GUI::CFocusableObj::Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s)
{
	GfxObject::Init(ren, file, x, y, xTiles, yTiles, s);

	m_EventArgs = new CGuiEventArgs(m_ID);

	return 0;
}

int CKT::GUI::CFocusableObj::Update(SDL_Event * e)
{
	if (!m_IsEnabled)
		return 0;

	if (e->type == SDL_MOUSEMOTION)
	{
		if (e->button.x >= m_PosX && e->button.x < m_PosX + m_Width &&
			e->button.y >= m_PosY && e->button.y < m_PosY + m_Height &&
			!(e->button.button == SDL_BUTTON_LEFT))
		{
			m_IsSelected = true;
		}
		else if (e->button.x < m_PosX || e->button.x >= m_PosX + m_Width ||
			e->button.y < m_PosY || e->button.y >= m_PosY + m_Height)
		{
			m_IsSelected = false;
		}
	}
	
	if (!m_WasSelected && m_IsSelected && m_OnGotFocus)
		m_OnGotFocus(m_ObjForCallback, *this, *m_EventArgs);
	else if (m_WasSelected && !m_IsSelected && m_OnLostFocus)
		m_OnLostFocus(m_ObjForCallback, *this, *m_EventArgs);

	m_WasSelected = m_IsSelected;

	if (m_IsSelected)
	{
		if (m_FocusClipPoints[1].x < 0 || m_FocusClipPoints[1].y < 0)
		{
			m_rClip.x = m_AnimWidth * 1 + m_OffsetClipX;
			m_rClip.y = m_AnimHeight * 0 + m_OffsetClipY;
		}
		else
		{
			m_rClip.x = m_AnimWidth * m_FocusClipPoints[1].x + m_OffsetClipX;
			m_rClip.y = m_AnimHeight * m_FocusClipPoints[1].y + m_OffsetClipY;
		}
	}
	else
	{
		if (m_FocusClipPoints[0].x < 0 || m_FocusClipPoints[0].y < 0)
		{
			m_rClip.x = m_AnimWidth * 0 + m_OffsetClipX;
			m_rClip.y = m_AnimHeight * 0 + m_OffsetClipY;
		}
		else
		{
			m_rClip.x = m_AnimWidth * m_FocusClipPoints[0].x + m_OffsetClipX;
			m_rClip.y = m_AnimHeight * m_FocusClipPoints[0].y + m_OffsetClipY;
		}
	}

	return 0;
}
