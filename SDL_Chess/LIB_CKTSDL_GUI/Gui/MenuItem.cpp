#include "MenuItem.h"
#include <Color.h>

using namespace CKT::GUI;

CMenuItem::CMenuItem()
{
}


CMenuItem::~CMenuItem()
{
	if (m_Header)
		delete m_Header;
}

int CKT::GUI::CMenuItem::Init(PRENDERER ren, const std::string & msg, float x, float y, SDL_Color colText, SDL_Color colBack, GFX::FONT_ID id)
{
	m_Header = new CLabel();
	m_Header->Init(ren, msg, x + DIFF_TEXT, y, colText, id);

	m_PosX = x;
	m_PosY = y;

	m_DesignX = m_PosX;
	m_DesignY = m_PosY;

	m_Width = m_Header->Width() + DIFF_TEXT * 2;
	m_Height = m_Header->Height() + DIFF_TEXT;

	m_DesignWidth = m_Width;
	m_DesignHeight = m_Height;

	m_rClip = { (int)m_PosX, (int)m_PosY, (int)m_Width, (int)m_Height };

	m_BackgroundColor = colBack;
	m_OriginalColor = colBack;

	m_pRenderer = ren;

	m_EventArgs = new CBtnEventArgs(m_ID);

	return 0;
}

int CKT::GUI::CMenuItem::Init(PRENDERER ren, const std::string & msg, float x, float y, SDL_Color colBack, GFX::FONT_ID id)
{
	Init(ren, msg, x, y, { 0,0,0,255 }, colBack, id);

	return 0;
}

void CKT::GUI::CMenuItem::Add(CMenuItem * item, bool arrow)
{
	m_Content.push_back(item);

	if (m_Content.size() == 1)
	{
		std::string temp = m_Header->Text() + (arrow ? " >" : "");
		float x = m_Header->X();
		float y = m_Header->Y();
		SDL_Color cf = m_Header->TextColor();
		GFX::FONT_ID id = m_Header->FontID();
		delete m_Header;

		Init(m_pRenderer, temp, m_PosX, m_PosY, cf, m_OriginalColor, id);

		m_IsLeafItem = false;
	}

	float maxW = 0;
	for (int i = 0; i < (int)m_Content.size(); i++)
	{
		if (maxW < m_Content[i]->Width())
		{
			maxW = m_Content[i]->Width();
		}
	}

	for (int i = 0; i < (int)m_Content.size(); i++)
	{
		m_Content[i]->Width() = maxW;
	}
}

void CKT::GUI::CMenuItem::Add(CGUIBase * sep)
{
	m_Seperator.push_back(sep);
}

bool CKT::GUI::CMenuItem::IsInUse(CMenuItem * item)
{
	bool used = item->IsSelected();

	if (!used)
	{
		for each (auto item in item->Content())
		{
			used = item->IsSelected();

			if (used)
				break;

			used = IsInUse(item);

			if (used)
				break;
		}
	}

	return used;
}

void CKT::GUI::CMenuItem::SetX(float x)
{
	m_PosX = x;

	if (!m_IsSeperator)
		m_Header->X() = m_PosX + DIFF_TEXT;
}

void CKT::GUI::CMenuItem::SetY(float y)
{
	m_PosY = y;

	if (!m_IsSeperator)
		m_Header->Y() = m_PosY;
}

int CKT::GUI::CMenuItem::Update(SDL_Event * e)
{
	if (!m_IsEnabled)
		return 0;
	
	// Selection
	if (e && e->type == SDL_MOUSEMOTION)
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

	if (!m_IsSeperator)
	{
		if (!m_WasSelected && m_IsSelected && m_OnGotFocus)
			m_OnGotFocus(m_ObjForCallback, *this, *m_EventArgs);
		else if (m_WasSelected && !m_IsSelected && m_OnLostFocus)
			m_OnLostFocus(m_ObjForCallback, *this, *m_EventArgs);

		m_GotFocus = m_IsSelected && !m_WasSelected;
		m_LostFocus = !m_IsSelected && m_WasSelected;

		m_WasSelected = m_IsSelected;

		if (m_IsSelected)
		{
			m_BackgroundColor = CColor(m_OriginalColor).Complement().ToSDLColor();
		}
		else
		{
			m_BackgroundColor = m_OriginalColor;
		}

		// clicked
		if (m_IsSelected)
		{
			if (e->type == SDL_MOUSEBUTTONDOWN && e->button.button == SDL_BUTTON_LEFT)
				m_IsPressed = true;
			else if (e->type == SDL_MOUSEBUTTONUP && e->button.button == SDL_BUTTON_LEFT)
				m_IsPressed = false;


			if (!m_IsTopItem && !m_IsLeafItem)
				m_IsOpen = true;
		}
		else
		{
			m_IsPressed = false;
		}

		//std::cout << m_IsPressed << std::endl;
		if (m_IsSelected)
		{
			m_IsDown = m_IsPressed && !m_WasPressed;
			m_IsUp = !m_IsPressed && m_WasPressed;
		}

		m_WasPressed = m_IsPressed;

		// fire events
		if (m_IsDown || m_IsUp)
		{
			if (m_OnClick && m_EventArgs)
			{
				if (m_IsDown)
					((CBtnEventArgs*)m_EventArgs)->ClickState() = CBtnEventArgs::Down;
				else if (m_IsUp)
					((CBtnEventArgs*)m_EventArgs)->ClickState() = CBtnEventArgs::Up;

				m_EventArgs->Name() = m_GuiName;
				m_OnClick(m_ObjForCallback, *this, *((CBtnEventArgs*)m_EventArgs));
			}
		}
	}

	m_IsInUse = IsInUse(this);

	if (m_IsOpen && !m_IsInUse && !m_Timer.IsStarted())
	{
		m_Timer.Start(100);
		//std::cout << "Timer started: " << Name() << std::endl;
	}

	if (m_IsInUse)
	{
		m_Timer.Stop();
		//std::cout << "Timer stopped: " << Name() << std::endl;
	}
	
	if ((!m_IsInUse && m_Timer.IsFinish()) || (m_IsLeafItem && m_IsUp))
	{
		m_IsOpen = false;
		//std::cout << "Timer finished: " << Name() << std::endl;
	}

	UpdateChilds(e);

	return 0;
}

int CKT::GUI::CMenuItem::UpdateChilds(SDL_Event * e)
{
	// other included menu items
	if (m_IsOpen)
	{
		CMenuItem* lastItem = nullptr;
		int i = 0;
		for each (auto item in m_Content)
		{
			if (m_IsTopItem)
				item->SetX(m_PosX);
			else
				item->SetX(m_PosX + m_Width);

			if (lastItem)
			{
				if (m_IsTopItem)
					item->SetY(lastItem->Y() + lastItem->Height());
				else
					item->SetY(lastItem->Y() + lastItem->Height());
			}
			else
			{
				if (m_IsTopItem)
					item->SetY(m_PosY + (i + 1) * m_Height);
				else
					item->SetY(m_PosY + i * m_Height);
			}

			item->Update(e);

			lastItem = item;

			i++;
		}
	}

	return 0;
}

int CKT::GUI::CMenuItem::Render()
{
	CGUIBase::Render();

	m_Header->Render();

	if (m_IsOpen)
	{
		for each (auto item in m_Content)
		{
			item->Render();
		}
	}

	return 0;
}
