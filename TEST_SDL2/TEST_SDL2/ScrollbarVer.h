#pragma once

#include "Scrollbar.h"

namespace CKT
{
	namespace GUI
	{
		class CScrollbarVer : public CScrollbar
		{
		public:
			CScrollbarVer();
			~CScrollbarVer();

		public:
			void SetValue(int val);

			void SetBounds(float x, float y, float w, float h = 0) override;

		public:
			int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float w, float h);
			virtual int Update(SDL_Event* e);

		};

	}

}