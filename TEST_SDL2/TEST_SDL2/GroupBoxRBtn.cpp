#include "GroupBoxRBtn.h"

using namespace CKT::GUI;

CGroupBoxRBtn::CGroupBoxRBtn()
{
	m_NonVisual = true;
}


CGroupBoxRBtn::~CGroupBoxRBtn()
{
}

void CKT::GUI::CGroupBoxRBtn::AddRadioBtn(CRadioBtn * btn)
{
	m_Group.insert(btn);
}

int CKT::GUI::CGroupBoxRBtn::Update(SDL_Event * e)
{
	for each (CRadioBtn* item in m_Group)
	{
		if (item->IsDown())
		{
			for each (CRadioBtn* btn in m_Group)
			{
				if (btn != item)
					btn->IsPressed() = false;
			}

			return 0;
		}
	}

	return 0;
}
