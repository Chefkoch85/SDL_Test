#pragma once

#include "GuiEventArgs.h"

namespace CKT
{
	namespace GUI
	{
		
		class CBtnEventArgs : public CGuiEventArgs
		{
		public:
			enum eClickState
			{
				None = 0x00,
				Down = 0x01,
				Press = 0x02,
				Up = 0x04,
			};

		protected:
			eClickState m_ClickState = None;

		public:
			DllExport CBtnEventArgs(GUI_ID id);
			DllExport CBtnEventArgs(GUI_ID id, eClickState state);
			DllExport ~CBtnEventArgs();

			DllExport eClickState& ClickState() { return m_ClickState; }
		};

	}
}
