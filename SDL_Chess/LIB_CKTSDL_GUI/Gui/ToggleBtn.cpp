#include "ToggleBtn.h"


using namespace CKT::GUI;

CToggleBtn::CToggleBtn()
{

}


CToggleBtn::~CToggleBtn()
{
}

void CKT::GUI::CToggleBtn::SetBtnClippingPoints(SDL_Point notSel, SDL_Point sel, SDL_Point pressNotSel, SDL_Point pressSel)
{
	m_FocusClipPoints[0] = notSel;
	m_FocusClipPoints[1] = sel;
	m_PressedClippingPoint[0] = pressNotSel;
	m_PressedClippingPoint[1] = pressSel;
}

int CKT::GUI::CToggleBtn::Update(SDL_Event * e)
{
	if (!m_IsVisible || !m_IsEnabled)
		return 0;

	CFocusableObj::Update(e);
	
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		if (e->button.button == SDL_BUTTON_LEFT)
		{
			if(m_IsSelected)
			{
				m_IsPressed = !m_IsPressed;
			}
		}
	}

	if (m_IsSelected)
	{
		m_IsDown = m_IsPressed && !m_IsPressedOld;
		m_IsUp = !m_IsPressed && m_IsPressedOld;
	}

	if (m_IsDown || m_IsUp)
	{
		if (m_OnClick)
		{
			if (m_EventArgs)
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
	}

	m_IsPressedOld = m_IsPressed;

	if (m_IsPressed && m_IsSelected)
	{
		if (m_PressedClippingPoint[1].x < 0 || m_PressedClippingPoint[1].y < 0)
		{
			m_rClip.x = m_AnimWidth * 1 + m_OffsetClipX;
			m_rClip.y = m_AnimHeight * 1 + m_OffsetClipY;
		}
		else
		{
			m_rClip.x = m_AnimWidth * m_PressedClippingPoint[1].x + m_OffsetClipX;
			m_rClip.y = m_AnimHeight * m_PressedClippingPoint[1].y + m_OffsetClipY;
		}
	}
	else if (m_IsPressed)
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
