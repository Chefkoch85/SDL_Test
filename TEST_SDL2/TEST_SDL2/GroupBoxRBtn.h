#pragma once

#include "RadioBtn.h"
#include <set>

namespace CKT
{
	namespace GUI
	{
		class CGroupBoxRBtn : public CFocusableObj
		{
		public:
			typedef std::set<CRadioBtn*> GROUPBOX_SET;

		protected:
			GROUPBOX_SET m_Group;

		public:
			CGroupBoxRBtn();
			~CGroupBoxRBtn();

		public:
			void AddRadioBtn(CRadioBtn* btn);

			virtual int Update(SDL_Event* e) override;


		};

	}

}