#include "Menubar.h"

using namespace CKT::GUI;

CMenubar::CMenubar()
{
}


CMenubar::~CMenubar()
{
}

DllExport int CKT::GUI::CMenubar::Init(PRENDERER ren, SDL_Color col, float x, float y, float w, float h)
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

	m_BackgroundColor = col;

	m_pRenderer = ren;

	return 0;
}

DllExport void CKT::GUI::CMenubar::Add(CMenuItem * item)
{
	if (m_Content.size() > 0)
	{
		if (m_MenuPosition == TOP)
			item->SetX(m_Content.back()->X() + m_Content.back()->Width());
	}

	item->MenuPosition() = m_MenuPosition;
	m_Content.push_back(item);
}

DllExport int CKT::GUI::CMenubar::Update(SDL_Event * e)
{
	for each (auto item in m_Content)
	{
		item->Update(e);

		if (item->IsUp() && !item->IsOpen())
		{
			item->IsOpen() = true;
			item->UpdateChilds(e);
		}
		else if (item->IsUp() && item->IsOpen())
		{
			item->IsOpen() = false;
			item->UpdateChilds(e);
		}

		//std::cout << item->IsInUse() << std::endl;
	}

	return 0;
}

DllExport int CKT::GUI::CMenubar::Render()
{
	CGUIBase::Render();

	for each (auto item in m_Content)
	{
		item->Render();
	}

	return 0;
}
