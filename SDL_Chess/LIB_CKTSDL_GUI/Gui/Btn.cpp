#include "Btn.h"

using namespace CKT::GUI;

CBtn::CBtn()
{
	m_PressedClippingPoint[0].x = -1;
	m_PressedClippingPoint[0].y = -1;
	m_PressedClippingPoint[1].x = -1;
	m_PressedClippingPoint[1].y = -1;
}


CBtn::~CBtn()
{
	if (m_Content)
		delete m_Content;
}

void CKT::GUI::CBtn::SetClickFocusEvents(Click cFunc, GotFocus gFunc, LostFocus lFunc, void * objForCallback)
{
	m_OnClick = cFunc;
	m_OnGotFocus = gFunc;
	m_OnLostFocus = lFunc;
	m_ObjForCallback = objForCallback;
}

void CKT::GUI::CBtn::SetBtnClippingPoints(SDL_Point notSel, SDL_Point sel, SDL_Point pressed)
{
	m_FocusClipPoints[0] = notSel;
	m_FocusClipPoints[1] = sel;
	m_PressedClippingPoint[0] = pressed;
}

void CKT::GUI::CBtn::SetScale(float s)
{
	CGfxObject::SetScale(s);

	if (m_Content)
		m_Content->SetScale(s);
}

CLabel & CKT::GUI::CBtn::Content()
{
	if (!m_Content)
		m_Content = new CLabel();

	return *m_Content;
}

int CKT::GUI::CBtn::Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s)
{
	CFocusableObj::Init(ren, file, x, y, xTiles, yTiles, s);

	Update(&SDL_Event());

	m_EventArgs = new CBtnEventArgs(m_ID);

	return 0;
}

int CKT::GUI::CBtn::Update(SDL_Event* e)
{
	if (!m_IsVisible || !m_IsEnabled)
		return 0;

	//m_IsPressed = false;

	CFocusableObj::Update(e);

	if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION)
	{
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			if (m_IsSelected)
			{
				m_IsPressed = true;
			}
		}
	}
	else if (e->type == SDL_MOUSEBUTTONUP)
	{
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			m_IsPressed = false;
		}
	}

	if (m_IsSelected)
	{
		m_IsDown = m_IsPressed && !m_IsPressedOld;
		m_IsUp = !m_IsPressed && m_IsPressedOld;
	}

	if ((m_IsPressed && m_ClickEventOnPress) || m_IsDown || m_IsUp)
	{
		if (m_OnClick && m_EventArgs)
		{
			if (m_IsDown)
				((CBtnEventArgs*)m_EventArgs)->ClickState() = CBtnEventArgs::Down;
			else if (m_IsPressed)
				((CBtnEventArgs*)m_EventArgs)->ClickState() = CBtnEventArgs::Press;
			else if (m_IsUp)
				((CBtnEventArgs*)m_EventArgs)->ClickState() = CBtnEventArgs::Up;

			m_EventArgs->Name() = m_GuiName;
			m_OnClick(m_ObjForCallback, *this, *((CBtnEventArgs*)m_EventArgs));
		}
	}

	m_IsPressedOld = m_IsPressed;

	if (m_IsPressed)
	{
		if (m_PressedClippingPoint[0].x < 0 || m_PressedClippingPoint[0].y < 0)
		{
			m_rClip.x = m_AnimWidth * 0 + m_OffsetClipX;
			m_rClip.y = m_AnimHeight * 1 + m_OffsetClipY;
		}
		else
		{
			m_rClip.x = m_AnimWidth * m_PressedClippingPoint[0].x + m_OffsetClipX;
			m_rClip.y = m_AnimHeight * m_PressedClippingPoint[0].y + m_OffsetClipY;
		}
	}
	
	return 0;
}

int CKT::GUI::CBtn::Render()
{
	CGfxObject::Render();

	if (m_Content)
	{
		m_Content->X() = (m_Width - m_Content->Width()) / 2 + m_PosX;
		m_Content->Y() = (m_Height - m_Content->Height()) / 2 + m_PosY;
		m_Content->Render();
	}

	return 0;
}
