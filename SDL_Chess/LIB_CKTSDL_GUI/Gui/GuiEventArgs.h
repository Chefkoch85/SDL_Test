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
			DllExport CGuiEventArgs(GUI_ID id);
			DllExport ~CGuiEventArgs();

		public:
			DllExport std::string& Name() { return m_Name; }
			DllExport GUI_ID ID() { return m_ID; }
		};

	}
}
