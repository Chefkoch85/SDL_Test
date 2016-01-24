#include "RadioBtn.h"


using namespace CKT::GUI;

CRadioBtn::CRadioBtn()
{
}


CRadioBtn::~CRadioBtn()
{
}

int CKT::GUI::CRadioBtn::Update(SDL_Event * e)
{
	if (!m_IsVisible || !m_IsEnabled)
		return 0;

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

	m_IsDown = m_IsPressed && !m_IsPressedOld;
	m_IsUp = !m_IsPressed && m_IsPressedOld;

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
