#include "BtnEventArgs.h"

using namespace CKT::GUI;


CBtnEventArgs::CBtnEventArgs(GUI_ID id) 
	:
	CGuiEventArgs(id)
{

}

CKT::GUI::CBtnEventArgs::CBtnEventArgs(GUI_ID id, eClickState state)
	:
	CGuiEventArgs(id)
{
	m_ClickState = state;
}

CBtnEventArgs::~CBtnEventArgs()
{
}
