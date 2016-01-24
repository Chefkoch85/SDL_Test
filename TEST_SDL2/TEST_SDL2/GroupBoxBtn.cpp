#include "GroupBoxBtn.h"


using namespace CKT::GUI;

void CKT::GUI::CGroupBoxBtn::RecalculatePositions(CBtn* sel)
{
	if (!sel || m_Reset)
	{
		if (m_Oriantation == eOriantation::HOR)
		{
			float diffSize = (m_NewSize - m_OldSelected->Height()) / 2;
			//std::cout << "Smaler: " << diffSize << std::endl;
			// reset to befor
			for each(CBtn* item in m_Group)
			{
				if (item == m_OldSelected)
					continue;

				if (item->Y() > m_OldPos)
				{
					item->Y() = item->Y() - diffSize;
				}
				else if (item->Y() < m_OldPos)
				{
					item->Y() = item->Y() + diffSize;
				}
			}
		}
		else
		{
			float diffSize = (m_NewSize - m_OldSelected->Width()) / 2;
			//std::cout << "Smaler: " << diffSize << std::endl;
			// reset to befor
			for each(CBtn* item in m_Group)
			{
				if (item == m_OldSelected)
					continue;

				if (item->X() > m_OldPos)
				{
					item->X() = item->X() - diffSize;
				}
				else if (item->X() < m_OldPos)
				{
					item->X() = item->X() + diffSize;
				}
			}
		}

		if (!m_Reset)
		{
			return;
		}
	}
	
	// if we have to reset the position because we move from one to another sel object
	// use the right oldY from the new Selected object to do the new moving
	if (m_Reset)
	{
		m_OldPos = m_SavedOldPos;
		m_Reset = false;
	}

	if (m_Oriantation == eOriantation::HOR)
	{
		float diffSize = (sel->Height() - m_OldSize) / 2;
		//std::cout << "Bigger: " << diffSize << std::endl;
		// move y
		for each(CBtn* item in m_Group)
		{
			if (item == sel)
				continue;

			if (item->Y() > m_OldPos)
			{
				item->Y() = item->Y() + diffSize;
			}
			else if (item->Y() < m_OldPos)
			{
				item->Y() = item->Y() - diffSize;
			}
		}
	}
	else
	{
		float diffSize = (sel->Width() - m_OldSize) / 2;
		std::cout << "Bigger: " << diffSize << std::endl;
		// move y
		for each(CBtn* item in m_Group)
		{
			if (item == sel)
				continue;

			if (item->X() > m_OldPos)
			{
				item->X() = item->X() + diffSize;
			}
			else if (item->X() < m_OldPos)
			{
				item->X() = item->X() - diffSize;
			}
		}
	}
}

CGroupBoxBtn::CGroupBoxBtn()
{
	m_NonVisual = true;
}


CGroupBoxBtn::~CGroupBoxBtn()
{
}

void CKT::GUI::CGroupBoxBtn::AddBtn(CBtn * item)
{
	m_Group.insert(item);
}

int CKT::GUI::CGroupBoxBtn::Update(SDL_Event * e)
{
	CBtn* sel = nullptr;
	for each(CBtn* item in m_Group)
	{
		//item->Update(e);

		if (item->IsSelected())
		{
			if (m_Oriantation == eOriantation::HOR)
			{
				m_OldPos = item->Y();
				m_OldSize = item->Height();
				item->SetScale(m_Scale);
				m_NewSize = item->Height();
			}
			else
			{
				m_OldPos = item->X();
				m_OldSize = item->Width();
				item->SetScale(m_Scale);
				m_NewSize = item->Width();
			}
			
			sel = item;
		}
		else
		{
			item->SetScale(1.0f);
		}
	}

	if (sel != m_OldSelected)
	{
		if (sel && m_OldSelected && sel != m_OldSelected)
		{
			// save the new OldY from the currnet selected object cooridnate for the moving after the resetting
			m_SavedOldPos = m_OldPos;
			// this is nesseccary for reseting the old sel object to right value
			if (m_Oriantation == eOriantation::HOR)
				m_OldPos = m_OldSelected->Y();
			else
				m_OldPos = m_OldSelected->X();

			m_Reset = true;
		}

		if (m_OldSelected || sel)
			RecalculatePositions(sel);
	}

	m_OldSelected = sel;

	return 0;
}
