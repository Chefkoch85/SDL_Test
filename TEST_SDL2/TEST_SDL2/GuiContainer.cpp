#include "GuiContainer.h"

#include "Label.h"
#include "Btn.h"

using namespace CKT::GUI;

void CKT::GUI::CGuiContainer::AddControl(CGUIBase * item)
{
	if (!item)
		return;

	m_Content.insert(item);
}

void CKT::GUI::CGuiContainer::AddControl(CFocusableObj * item)
{
	if (!item)
		return;

	m_Content.insert(item);
	m_UpdateContent.insert(item);
}

void CKT::GUI::CGuiContainer::AddControl(CLabel * item, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (!(item + i))
			continue;

		m_Content.insert((item + i));
	}
}

void CKT::GUI::CGuiContainer::RemoveControl(CGUIBase * item)
{
	GUI_DRAW_ELEM_IT it = m_Content.find(item);
	if (it != m_Content.end())
		m_Content.erase(item);
}

void CKT::GUI::CGuiContainer::RemoveControl(CFocusableObj * item)
{
	GUI_UPDATE_ELEM_IT it = m_UpdateContent.find(item);
	if (it != m_UpdateContent.end())
	{
		m_UpdateContent.erase(item);
		m_Content.erase((CGUIBase*)item);
	}
}

CGUIBase * CKT::GUI::CGuiContainer::GetControlByName(std::string name)
{
	for each (CGUIBase* item in m_Content)
	{
		if (item->Name().compare(name) == 0)
		{
			return item;
		}
	}

	return nullptr;
}

CGuiContainer::CGuiContainer()
{
}


CGuiContainer::~CGuiContainer()
{
	for each (CGUIBase* item in m_Content)
	{
		// TODO: for now deactivated because the test elements are created on the stack not on the heap
		//delete item;
	}

	m_Content.clear();
	m_UpdateContent.clear();
}

int CKT::GUI::CGuiContainer::Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s)
{
	GUI::CGUIBase::Init(ren, file, x, y, w, h, s);

	return 0;
}

int CKT::GUI::CGuiContainer::Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s)
{
	GUI::CGUIBase::Init(ren, file, x, y, xTiles, yTiles, s);

	return 0;
}

void CKT::GUI::CGuiContainer::Init(PRENDERER ren, SDL_Color col, float x, float y, float w, float h)
{
	m_PosX = x;
	m_PosY = y;

	m_DesignX = x;
	m_DesignY = y;

	m_Width = w;
	m_Height = h;

	m_DesignWidth = w;
	m_DesignHeight = h;

	m_rClip = { (int)m_PosX, (int)m_PosY, (int)m_Width, (int)m_Height };

	m_BackgroundColor = col;

	m_pRenderer = ren;
}

void CKT::GUI::CGuiContainer::CalculatePositions()
{
	for each (CGUIBase* item in m_Content)
	{
		CKT::GUI::AncorPoint ancor = item->AncorPoint();

		if (ancor == CKT::GUI::Center)
		{
			item->X() = ((m_Width - item->Width()) / 2 + item->GetDesignX()) + m_PosX;
			item->Y() = ((m_Height - item->Height()) / 2 + item->GetDesignY()) + m_PosY;
			continue;
		}

		if (ancor & Top)
		{
			item->Y() = item->GetDesignY() + m_PosY;
		}
		if (ancor & Left)
		{
			item->X() = item->GetDesignX() + m_PosX;
		}

		if (ancor & CenterX)
		{
			item->X() = ((m_Width - item->Width()) / 2/* + item->X()*/) + m_PosX;
		}
		else if (ancor & Right)
		{
			item->X() = (m_Width - item->GetDesignX() - item->Width()) + m_PosX;
		}

		if (ancor & CenterY)
		{
			item->Y() = ((m_Height - item->Height()) / 2/* + item->Y()*/) + m_PosY;
		}
		else if (ancor & Bottom)
		{
			item->Y() = (m_Height - item->Y() - item->Height()) + m_PosY;
		}

		if (item->X() < m_PosX)
			item->X() = (float)m_PosX;

		if (item->Y() < m_PosY)
			item->Y() = (float)m_PosY;

		if (item->Width() > m_Width)
			item->Width() = (float)m_Width;

		if (item->Height() > m_Height)
			item->Height() = (float)m_Height;
	}
}

void CKT::GUI::CGuiContainer::Update(SDL_Event * e)
{
	if (!m_IsVisible)
		return;

	if (e->type == SDL_KEYDOWN && !m_KeyWasPressed)
	{
		m_KeyWasPressed = true;

		if (m_SelectedItem && (e->key.keysym.sym == SDLK_RETURN || e->key.keysym.sym == SDLK_SPACE))
			m_SelectedItem->IsPressed() = true;
	}
	else if (e->type == SDL_KEYUP)
	{
		m_KeyWasPressed = false;

		if (m_SelectedItem && (e->key.keysym.sym == SDLK_RETURN || e->key.keysym.sym == SDLK_SPACE))
			m_SelectedItem->IsPressed() = false;
	}

	for each (CFocusableObj* item in m_UpdateContent)
	{
		item->Update(e);

		if (item->IsSelected())
		{
			m_SelectedItem = (CBtn*)item;
		}
	}
}

int CKT::GUI::CGuiContainer::Render()
{
	if (!m_IsVisible)
		return 0;

	CGUIBase::Render();

	for each (CGUIBase* item in m_Content)
	{
		item->Render();
	}

	return 0;
}
