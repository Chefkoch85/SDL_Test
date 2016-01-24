#pragma once

#include "Scrollbar.h"

namespace CKT
{
	namespace GUI
	{
		class CScrollbarHor : public CScrollbar
		{
		public:
			CScrollbarHor();
			~CScrollbarHor();

		public:
			void SetValue(int val);

			void SetBounds(float x, float y, float h, float w = 0) override;

		public:
			int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float w, float h);
			virtual int Update(SDL_Event* e);

		};

	}

}
