#pragma once

#include "Btn.h"
#include "GuiContainer.h"
#include "Util.h"

#include <set>

namespace CKT
{
	namespace GUI
	{
		class CGroupBoxBtn : public CFocusableObj
		{
		public:
			typedef std::set<CBtn*> GROUPBOX_SET;

		protected:
			GROUPBOX_SET m_Group;

			float m_Scale = 1.0f;
			CBtn* m_OldSelected = nullptr;
			float m_OldPos = 0, m_SavedOldPos = 0;
			float m_OldSize = 0, m_NewSize = 0;
			bool m_Reset = false;
			eOriantation m_Oriantation = eOriantation::HOR;

		protected:
			void RecalculatePositions(CBtn* sel);

		public:
			CGroupBoxBtn();
			~CGroupBoxBtn();

			void AddBtn(CBtn* item);

		public:
			float& Scale() { return m_Scale; }
			eOriantation& Oriantation() { return m_Oriantation; }

			virtual int Update(SDL_Event* e) override;
		};

	}

}

