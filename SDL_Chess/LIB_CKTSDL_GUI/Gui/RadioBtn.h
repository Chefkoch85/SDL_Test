#pragma once

#include "Btn.h"

namespace CKT
{
	namespace GUI
	{
		class CRadioBtn : public CBtn
		{
		public:
			DllExport CRadioBtn();
			DllExport ~CRadioBtn();
			
			DllExport int Update(SDL_Event* e) override;
		};

	}

}