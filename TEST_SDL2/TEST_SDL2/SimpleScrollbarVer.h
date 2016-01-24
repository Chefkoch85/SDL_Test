#pragma once

#include "ScrollbarVer.h"

namespace CKT
{
	namespace GUI
	{
		class CSimpleScrollbarVer : public CScrollbarVer
		{
		protected:
			struct SSimpleBtn
			{
				int x, y;
				int w, h;
				bool Selected, Pressed, Down, Up;
			};

			SSimpleBtn m_btnPrev, m_btnNext, m_btnTrack;

			SDL_Color m_ColBack = { 128,128,128,128 };
			SDL_Color m_ColBtnBack = { 200,200,200,200 };
			SDL_Color m_ColBtnFront = { 255,255,255,200 };

			SDL_Color m_ColBtnSel = { 255,155,0,255 };
			SDL_Color m_ColBtnPress = { 0,255,0,255 };
		public:
			CSimpleScrollbarVer();
			~CSimpleScrollbarVer();

		public:
			SDL_Color& ColorBack() { return m_ColBack; }
			SDL_Color& ColorBtnBack() { return m_ColBtnBack; }
			SDL_Color& ColorBtnFront() { return m_ColBtnFront; }

		public:
			virtual int Init(PRENDERER ren, int x, int y, int w, int h);
			virtual int Update(SDL_Event* e) override;
			virtual int Render() override;

		};

	}
}