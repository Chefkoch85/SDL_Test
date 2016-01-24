#pragma once

#include "Scrollbar.h"

namespace CKT
{
	namespace GUI
	{
		class CScrollbarHor : public CScrollbar
		{
		public:
			DllExport CScrollbarHor();
			DllExport ~CScrollbarHor();

		public:
			DllExport void SetValue(int val);

			DllExport void SetBounds(float x, float y, float h, float w = 0) override;

		public:
			DllExport int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float w, float h);
			DllExport virtual int Update(SDL_Event* e);

		};

	}

}
