#include "Panel.h"

#include "FocusableObj.h"
#include "Label.h"

using namespace CKT::GUI;

CPanel::CPanel()
{
}


CPanel::~CPanel()
{
	for each (CGUIBase* item in m_Content)
	{
		// TODO: for now deactivated because the test elements are created on the stack not on the heap
		//delete item;
	}

	m_Content.clear();
	m_UpdateContent.clear();
}

void CKT::GUI::CPanel::Update(SDL_Event * e)
{
	CGuiContainer::Update(e);

	for each (CGuiContainer* item in m_Containers)
	{
		item->Update(e);
	}
}

void CKT::GUI::CPanel::AddContainer(CGuiContainer * item)
{
	if (!item)
		return;

	m_Content.insert(item);
	m_Containers.insert(item);
}

void CKT::GUI::CPanel::RemoveContainer(CGuiContainer * item)
{
	GUI_CONTAINER_IT it = m_Containers.find(item);
	if (it != m_Containers.end())
	{
		m_Containers.erase(item);
		m_Content.erase((CGUIBase*)item);
	}
}


//
//void CKT::GUI::CPanel::Update(SDL_Event * e)
//{
//	if (!m_IsVisible)
//		return;
//
//	if (e->type == SDL_KEYDOWN && !m_KeyWasPressed)
//	{
//		m_KeyWasPressed = true;
//
//		/*if (e->key.keysym.sym == SDLK_UP || e->key.keysym.sym == SDLK_w)
//			m_SelectedID--;
//
//		if (e->key.keysym.sym == SDLK_DOWN || e->key.keysym.sym == SDLK_s)
//			m_SelectedID++;*/
//
//		if (m_SelectedItem && (e->key.keysym.sym == SDLK_RETURN || e->key.keysym.sym == SDLK_SPACE))
//			m_SelectedItem->IsPressed() = true;
//	}
//	else if (e->type == SDL_KEYUP)
//	{
//		m_KeyWasPressed = false;
//
//		if (m_SelectedItem && (e->key.keysym.sym == SDLK_RETURN || e->key.keysym.sym == SDLK_SPACE))
//			m_SelectedItem->IsPressed() = false;
//	}
//
//	for each (CPanel* item in m_Containers)
//	{
//		item->Update(e);
//	}
//
//	for each (CFocusableObj* item in m_UpdateContent)
//	{
//		// to check if the object can be converted to a needed base class
//		// and so the object is inherit from this base class
//		//if (dynamic_cast<CFocusableObj*>(item))
//		{
//			item->Update(e);
//
//			if (item->IsSelected())
//			{
//				m_SelectedItem = (CBtn*)item;
//			}
//		
//			/*if (m_SelectedID < 0)
//			{
//				m_SelectedID = item->ID();
//			}
//
//			if (item->ID() == m_SelectedID)
//			{
//				m_SelectedItem = (CBtn*)item;
//
//				if (m_SelectedItem != m_OldSelecedItem)
//				{
//					std::cout << "Seleced Item ID: " << m_SelectedItem->ID() << std::endl;
//
//					if (m_OldSelecedItem)
//						m_OldSelecedItem->IsSelected() = false;
//
//					m_SelectedItem->IsSelected() = true;
//				}
//			}*/
//		}
//	}
//
//	//std::cout << "Seleced Item (OLD): " << m_OldSelecedItem << std::endl;
//	//std::cout << "Seleced Item (NEW): " << m_SelectedItem << std::endl;
//
//	//std::cout << "Seleced ID: " << m_SelectedID << std::endl;
//
//	//m_OldSelecedItem = m_SelectedItem;
//}
