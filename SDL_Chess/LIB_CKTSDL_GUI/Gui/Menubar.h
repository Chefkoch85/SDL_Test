#pragma once

#include "GuiContainer.h"

#include <map>
#include <set>
#include <vector>

#include "MenuItem.h"

namespace CKT
{
	namespace GUI
	{
		enum eMenuPosition
		{
			TOP = 0x01,
			BOTTOM = 0x02,
			LEFT = 0x04,
			RIGHT = 0x08,
		};

		class CMenubar : public CFocusableObj
		{
		public:
			typedef std::vector<CMenuItem*> MENUITEM_LIST;

		protected:
			MENUITEM_LIST m_Content;

			eMenuPosition m_MenuPosition = TOP;

		public:
			DllExport CMenubar();
			DllExport ~CMenubar();

			DllExport int Init(PRENDERER ren, SDL_Color col, float x, float y, float w, float h);

		public:
			DllExport void Add(CMenuItem* item);
			
			DllExport eMenuPosition& MenuPosition() { return m_MenuPosition; }

		public:
			DllExport int Update(SDL_Event* e) override;
			DllExport int Render() override;
		};

	}
}