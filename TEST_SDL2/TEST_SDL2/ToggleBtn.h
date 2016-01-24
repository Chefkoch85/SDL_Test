#pragma once

#include "Btn.h"

namespace CKT
{
	namespace GUI
	{
		class CToggleBtn : public CBtn
		{

		public:
			CToggleBtn();
			~CToggleBtn();

			void SetBtnClippingPoints(SDL_Point notSel, SDL_Point sel, SDL_Point pressNotSel, SDL_Point pressSel);

			virtual int Update(SDL_Event* e) override;

		};

	}

}