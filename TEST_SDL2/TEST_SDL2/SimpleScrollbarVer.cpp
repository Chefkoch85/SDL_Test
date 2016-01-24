#include "SimpleScrollbarVer.h"

using namespace CKT::GUI;

CSimpleScrollbarVer::CSimpleScrollbarVer()
{
}


CSimpleScrollbarVer::~CSimpleScrollbarVer()
{
}

int CKT::GUI::CSimpleScrollbarVer::Init(PRENDERER ren, int x, int y, int w, int h)
{
	m_pRenderer = ren;

	m_PosX = x;
	m_PosY = y;
	m_Width = w;
	m_Height = h;

	m_btnPrev.w = m_Height;
	m_btnPrev.h = m_Height;

	m_btnNext.w = m_Height;
	m_btnNext.h = m_Height;

	m_btnTrack.w = m_Height;
	m_btnTrack.h = m_Height;

	return 0;
}

int CKT::GUI::CSimpleScrollbarVer::Update(SDL_Event * e)
{
	m_btnPrev.x = m_PosX;
	m_btnPrev.y = m_PosY;

	m_btnNext.x = m_Width - m_btnNext.h + m_PosX;
	m_btnNext.y = m_PosY;

	m_btnTrack.x = m_PosX + m_btnPrev.w + 20;
	m_btnTrack.y = m_PosY;

	return 0;
}

int CKT::GUI::CSimpleScrollbarVer::Render()
{
	// background
	SDL_Rect rDst = { m_PosX, m_PosY, m_Width, m_Height };
	SDL_SetRenderDrawColor(m_pRenderer, m_ColBack.r, m_ColBack.g, m_ColBack.b, m_ColBack.a);
	SDL_RenderFillRect(m_pRenderer, &rDst);

	// background button
	// button prev
	rDst = { m_btnPrev.x, m_btnPrev.y, m_btnPrev.w, m_btnPrev.h };
	SDL_SetRenderDrawColor(m_pRenderer, m_ColBtnBack.r, m_ColBtnBack.g, m_ColBtnBack.b, m_ColBtnBack.a);
	SDL_RenderFillRect(m_pRenderer, &rDst);

	// button next
	rDst = { m_btnNext.x, m_btnNext.y, m_btnNext.w, m_btnNext.h };
	SDL_SetRenderDrawColor(m_pRenderer, m_ColBtnBack.r, m_ColBtnBack.g, m_ColBtnBack.b, m_ColBtnBack.a);
	SDL_RenderFillRect(m_pRenderer, &rDst);

	// button track
	rDst = { m_btnTrack.x, m_btnTrack.y, m_btnTrack.w, m_btnTrack.h };
	SDL_SetRenderDrawColor(m_pRenderer, m_ColBtnBack.r, m_ColBtnBack.g, m_ColBtnBack.b, m_ColBtnBack.a);
	SDL_RenderFillRect(m_pRenderer, &rDst);


	// forground button
	// button prev
	rDst = { m_btnPrev.x, m_btnPrev.y, m_btnPrev.w, m_btnPrev.h };
	SDL_Point pPrev1[] = 
	{ 
			{m_btnPrev.x + m_btnPrev.w - 2, m_btnPrev.y + 2}, 
			{m_btnPrev.x + 2,m_btnPrev.y + m_btnPrev.h / 2 - 1}, 
			{m_btnPrev.x + m_btnPrev.w - 2,m_btnPrev.y + m_btnPrev.h - 3} 
	};
	SDL_SetRenderDrawColor(m_pRenderer, m_ColBtnFront.r, m_ColBtnFront.g, m_ColBtnFront.b, m_ColBtnFront.a);
	SDL_RenderDrawLines(m_pRenderer, pPrev1, 3);
	SDL_Point pPrev2[] =
	{
		{ m_btnPrev.x + m_btnPrev.w - 2, m_btnPrev.y + 5 },
		{ m_btnPrev.x + 7,m_btnPrev.y + m_btnPrev.h / 2 - 1 },
		{ m_btnPrev.x + m_btnPrev.w - 2,m_btnPrev.y + m_btnPrev.h - 6 }
	};
	SDL_SetRenderDrawColor(m_pRenderer, m_ColBtnFront.r, m_ColBtnFront.g, m_ColBtnFront.b, m_ColBtnFront.a);
	SDL_RenderDrawLines(m_pRenderer, pPrev2, 3);

	// button next
	rDst = { m_btnPrev.x, m_btnPrev.y, m_btnPrev.w, m_btnPrev.h };
	SDL_Point pNext1[] =
	{
		{ m_btnNext.x + 2,m_btnNext.y + 2 },
		{ m_btnNext.x + m_btnNext.w - 2, m_btnNext.y + m_btnNext.h / 2 - 1 },
		{ m_btnNext.x + 2,m_btnNext.y + m_btnNext.h - 3 }
	};
	SDL_SetRenderDrawColor(m_pRenderer, m_ColBtnFront.r, m_ColBtnFront.g, m_ColBtnFront.b, m_ColBtnFront.a);
	SDL_RenderDrawLines(m_pRenderer, pNext1, 3);
	SDL_Point pNext2[] =
	{
		{ m_btnNext.x + 2,m_btnNext.y + 5 },
		{ m_btnNext.x + m_btnNext.w - 7, m_btnNext.y + m_btnNext.h / 2 - 1 },
		{ m_btnNext.x + 2,m_btnNext.y + m_btnNext.h - 6 }
	};
	SDL_SetRenderDrawColor(m_pRenderer, m_ColBtnFront.r, m_ColBtnFront.g, m_ColBtnFront.b, m_ColBtnFront.a);
	SDL_RenderDrawLines(m_pRenderer, pNext2, 3);

	// button track
	rDst = { m_btnTrack.x + 2, m_btnTrack.y + 2, m_btnTrack.w - 4, m_btnTrack.h - 4 };
	SDL_SetRenderDrawColor(m_pRenderer, m_ColBtnFront.r, m_ColBtnFront.g, m_ColBtnFront.b, m_ColBtnFront.a);
	SDL_RenderDrawRect(m_pRenderer, &rDst);
	rDst = { m_btnTrack.x + 5, m_btnTrack.y + 5, m_btnTrack.w - 10, m_btnTrack.h - 10 };
	SDL_SetRenderDrawColor(m_pRenderer, m_ColBtnFront.r, m_ColBtnFront.g, m_ColBtnFront.b, m_ColBtnFront.a);
	SDL_RenderDrawRect(m_pRenderer, &rDst);


	return 0;
}
