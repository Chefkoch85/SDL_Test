#include "GuiEventArgs.h"


using namespace CKT::GUI;

//CGuiEventArgs::CGuiEventArgs()
//{
//}

CKT::GUI::CGuiEventArgs::CGuiEventArgs(GUI_ID id)
{
	m_ID = id;
}

CGuiEventArgs::~CGuiEventArgs()
{
}
