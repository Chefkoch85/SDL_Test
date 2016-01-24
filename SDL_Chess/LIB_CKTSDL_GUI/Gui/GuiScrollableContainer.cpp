#include "GuiScrollableContainer.h"

#include "ScrollbarHor.h"
#include "ScrollbarVer.h"

#include <conio.h>

using namespace CKT::GUI;

void CKT::GUI::CGuiScrollableContainer::onValueCallback(void * pThis, CKT::GUI::CScrollbar & sender, GUI::CGuiEventArgs & args)
{
	CGuiScrollableContainer* self = static_cast<CGuiScrollableContainer*>(pThis);
	self->onValue(sender, args);
}

void CKT::GUI::CGuiScrollableContainer::onValue(GUI::CScrollbar & sender, GUI::CGuiEventArgs & args)
{
	//std::cout << "SCB-VALUE-CHANGED() : " + sender.Name() << " : VAL: " << sender.GetValue() << std::endl;

	if (sender.ID() == m_scbBottom->ID())
	{
		m_CurentClip.x = (int)m_PosX + (sender.GetValue() * m_ScrollFactor);
	}
	else if (sender.ID() == m_scbRight->ID())
	{
		m_CurentClip.y = (int)m_PosY + (sender.GetValue() * m_ScrollFactor);
	}

}

CGuiScrollableContainer::CGuiScrollableContainer()
{
}


CGuiScrollableContainer::~CGuiScrollableContainer()
{
	if (m_scbRight)
		delete m_scbRight;

	if (m_scbBottom)
		delete m_scbBottom;
}

void CKT::GUI::CGuiScrollableContainer::ScrollbarUse(EScrollbarUse use, eOriantation witch)
{
	if (!m_ScrollbarsInitOK)
		return;

	switch (witch)
	{
	case CKT::GUI::HOR:
		m_UseScbRight = use;
		if (use == NEVER)
			m_scbRight->Visibility() = false;
		else if (use == ALLWAYS)
			m_scbRight->Visibility() = true;
		break;

	case CKT::GUI::VER:
		m_UseScbBottom = use;
		if (use == NEVER)
			m_scbBottom->Visibility() = false;
		else if (use == ALLWAYS)
			m_scbBottom->Visibility() = true;
		break;
		break;
	}
}

int CKT::GUI::CGuiScrollableContainer::InitScrollbars(PRENDERER ren, std::string fileHor, std::string fileVer, float w, float h, int xTiles, int yTiles)
{
	m_scbRight = new CScrollbarHor();
	m_scbBottom = new CScrollbarVer();

	m_scbRight->Init(m_pRenderer, fileHor, 0, 0, xTiles, yTiles, w, 0);
	m_scbBottom->Init(m_pRenderer, fileVer, 0, 0, xTiles, yTiles, 0, h);

	m_scbRight->Name() = "SCB_RIGHT";
	m_scbBottom->Name() = "SCB_BOTTOM";

	m_scbRight->Visibility() = false;
	m_scbBottom->Visibility() = false;

	m_scbRight->SnapToTicks() = true;
	m_scbBottom->SnapToTicks() = true;

	m_scbRight->SetScrollFactor(4);
	m_scbBottom->SetScrollFactor(4);

	m_scbRight->SetValueEvent(onValueCallback, this);
	m_scbBottom->SetValueEvent(onValueCallback, this);

	m_ScrollbarsInitOK = true;
	return 0;
}

void CKT::GUI::CGuiScrollableContainer::CalculatePositions()
{
	bool needScbHor = false;
	bool needScbVer = false;

	for each (CGUIBase* item in m_Content)
	{
		// extend container size if needed
		if (item->X() < m_ContainerBounds.x)
		{
			m_ContainerBounds.x = (int)item->X();
			needScbVer = true;
		}

		if (item->X() + item->Width() > m_ContainerBounds.w)
		{
			m_ContainerBounds.w = (int)item->X() + (int)item->Width();
			needScbVer = true;
		}

		if (item->Y() < m_ContainerBounds.y)
		{
			m_ContainerBounds.y = (int)item->Y();
			needScbHor = true;
		}

		if (item->Y() + item->Height() > m_ContainerBounds.h)
		{
			m_ContainerBounds.h = (int)item->Y() + (int)item->Height();
			needScbHor = true;
		}
		
		if (m_ScrollbarsInitOK)
		{
			if (needScbHor && item->X() + item->Width() + m_scbRight->GetW() > m_ContainerBounds.w)
			{
				needScbVer = true;
			}
			if (needScbVer && item->Y() + item->Height() + m_scbBottom->GetH() > m_ContainerBounds.h)
			{
				needScbHor = true;
			}
		}

		// correct the pos to be relative to the container
		CKT::GUI::AncorPoint ancor = item->AncorPoint();

		if (ancor == CKT::GUI::Center)
		{
			item->X() = ((m_Width - item->Width()) / 2 + item->X()) + m_PosX;
			item->Y() = ((m_Height - item->Height()) / 2 + item->Y()) + m_PosY;
			continue;
		}

		if (ancor & Top)
		{
			item->Y() = item->Y() + m_PosY;
		}
		if (ancor & Left)
		{
			item->X() = item->X() + m_PosX;
		}

		if (ancor & CenterX)
		{
			item->X() = ((m_Width - item->Width()) / 2 + item->X()) + m_PosX;
		}
		else if (ancor & Right)
		{
			item->X() = (m_Width - item->X() - item->Width()) + m_PosX;
		}

		if (ancor & CenterY)
		{
			item->Y() = ((m_Height - item->Height()) / 2 + item->Y()) + m_PosY;
		}
		else if (ancor & Bottom)
		{
			item->Y() = (m_Height - item->Y() - item->Height()) + m_PosY;
		}
	}

	if (!m_ScrollbarsInitOK)
		return;

	bool isExtraSizeSet = false;
	if (needScbVer)
	{
		m_scbBottom->Visibility() = true;

		m_scbBottom->Max() = (m_ContainerBounds.w - (int)m_Width) + (needScbHor ? (int)m_scbRight->GetW() : 0) / m_ScrollFactor;

		if (needScbHor && m_Width >= m_Height)
			m_scbBottom->SetBounds(m_PosX, m_PosY + m_Height - m_scbBottom->GetH(), m_Width - m_scbRight->GetW());
		else
			m_scbBottom->SetBounds(m_PosX, m_PosY + m_Height - m_scbBottom->GetH(), m_Width);
	}
	if (needScbHor)
	{
		m_scbRight->Visibility() = true;

		m_scbRight->Max() = (m_ContainerBounds.h - (int)m_Height) + (needScbVer ? (int)m_scbBottom->GetH() : 0) / m_ScrollFactor;

		if (needScbVer && m_Height > m_Width)
			m_scbRight->SetBounds(m_PosX + m_Width - m_scbRight->GetW(), m_PosY, m_Height - m_scbBottom->GetH());
		else
			m_scbRight->SetBounds(m_PosX + m_Width - m_scbRight->GetW(), m_PosY, m_Height);
	}
}

void CKT::GUI::CGuiScrollableContainer::Init(PRENDERER ren, SDL_Color col, float x, float y, float w, float h)
{
	CGuiContainer::Init(ren, col, x, y, w, h);

	m_ContainerBounds.x = 0;
	m_ContainerBounds.y = 0;
	m_ContainerBounds.w = (int)w;
	m_ContainerBounds.h = (int)h;
	m_CurentClip.x = m_OldClip.x = (int)x;
	m_CurentClip.y = m_OldClip.y = (int)y;
	m_CurentClip.w = m_OldClip.w = (int)w;
	m_CurentClip.h = m_OldClip.h = (int)h;
}

void CKT::GUI::CGuiScrollableContainer::Update(SDL_Event * e)
{
	if (!m_IsVisible)
		return;

	m_ElementsToDraw.clear();
	m_ElementsToUpdate.clear();

	for each (CGUIBase* item in m_Content)
	{
		item->X() = item->X() - ((m_CurentClip.x - m_OldClip.x));
		item->Y() = item->Y() - ((m_CurentClip.y - m_OldClip.y));

		if (item->X() + item->GetDesignWidth() >= m_PosX && item->X() <= m_PosX + m_Width &&
			item->Y() + item->GetDesignHeight() >= m_PosY && item->Y() <= m_PosY + m_Height)
		{
			m_ElementsToDraw.insert(item);
		}
	}

	m_OldClip = m_CurentClip;

	for each (CFocusableObj* item in m_UpdateContent)
	{
		if ((item->X() + item->GetDesignWidth() >= m_PosX && item->X() <= m_PosX + m_Width &&
			item->Y() + item->GetDesignHeight() >= m_PosY && item->Y() <= m_PosY + m_Height) || item->IsNonVisual())
			m_ElementsToUpdate.insert(item);
	}

	for each (CFocusableObj* item in m_ElementsToUpdate)
	{
		item->Update(e);
	}

	if (!m_ScrollbarsInitOK)
		return;

	if (m_scbBottom->Visibility())
		m_scbBottom->Update(e);
	if (m_scbRight->Visibility())
		m_scbRight->Update(e);
}

int CKT::GUI::CGuiScrollableContainer::Render()
{
	if (!m_IsVisible)
		return 0;

	CGUIBase::Render();
	SDL_RenderSetClipRect(m_pRenderer, &m_rClip);

	for each (CGUIBase* item in m_ElementsToDraw)
	{
		item->Render();
	}

	if (!m_ScrollbarsInitOK)
		return 0;

	if (m_scbBottom->Visibility())
		m_scbBottom->Render();
	if (m_scbRight->Visibility())
		m_scbRight->Render();

	SDL_RenderSetClipRect(m_pRenderer, nullptr);

	return 0;
}
