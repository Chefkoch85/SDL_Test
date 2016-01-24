#pragma once

#include "Scrollbar.h"

namespace CKT
{
	namespace GUI
	{
		class CScrollbarVer : public CScrollbar
		{
		public:
			DllExport CScrollbarVer();
			DllExport ~CScrollbarVer();

		public:
			DllExport void SetValue(int val);

			DllExport void SetBounds(float x, float y, float w, float h = 0) override;

		public:
			DllExport int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float w, float h);
			DllExport virtual int Update(SDL_Event* e);

		};

	}

}