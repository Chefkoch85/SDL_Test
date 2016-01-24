#pragma once

#include "Btn.h"

namespace CKT
{
	namespace GUI
	{
		class CRadioBtn : public CBtn
		{
		public:
			CRadioBtn();
			~CRadioBtn();
			
			int Update(SDL_Event* e) override;
		};

	}

}