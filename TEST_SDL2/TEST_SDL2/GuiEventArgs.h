#pragma once

#include "GUIBase.h"

namespace CKT
{
	namespace GUI
	{

		class CGuiEventArgs
		{
		protected:
			std::string m_Name = "";
			GUI_ID m_ID = 0;

		public:
			CGuiEventArgs(GUI_ID id);
			~CGuiEventArgs();

		public:
			std::string& Name() { return m_Name; }
			GUI_ID ID() { return m_ID; }
		};

	}
}
