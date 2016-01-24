#pragma once

#include "MenuItem.h"
#include <Color.h>

namespace CKT
{
	namespace GUI
	{
		class CSeperator : public CMenuItem
		{
		protected:
			eOriantation m_Oriantation = VER;
			CColor m_Foreground;

		public:
			DllExport CSeperator();
			DllExport CSeperator(PRENDERER ren, float s, CColor colFront, CColor colBack);
			DllExport ~CSeperator();

		public:
		 	DllExport int Init(PRENDERER ren, float x, float y, float w, float h, CColor foreGround, CColor backGround);

		public:
			//DllExport int Update(SDL_Event* e) override;
			DllExport int Render() override;
		};

	}

}
