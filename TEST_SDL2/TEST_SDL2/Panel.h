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
			void AddContainer(CGuiContainer* item);
			void RemoveContainer(CGuiContainer* item);

		public:
			CPanel();
			~CPanel();

			void Update(SDL_Event* e) override;
		};

	}

}
