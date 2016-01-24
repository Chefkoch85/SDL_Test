#pragma once

#include <set>

#include "GuiContainer.h"

namespace CKT
{
	namespace GUI
	{
		class CLabel;

		class CPanel : public CGuiContainer
		{
		public:
			typedef std::set<CGuiContainer*> GUI_CONTAINER_SET;
			typedef std::set<CGuiContainer*>::iterator GUI_CONTAINER_IT;

		protected:
			GUI_CONTAINER_SET m_Containers;

			int m_SelectedID = -1;
			CBtn* m_OldSelecedItem = nullptr;

		public:
			DllExport void AddContainer(CGuiContainer* item);
			DllExport void RemoveContainer(CGuiContainer* item);

		public:
			DllExport CPanel();
			DllExport ~CPanel();

			DllExport void Update(SDL_Event* e) override;
		};

	}

}
