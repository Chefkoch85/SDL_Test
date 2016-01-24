#include "ProgressbarH.h"

using namespace CKT::GUI;


CProgressbarH::CProgressbarH()
{
	m_Orientation = FromBottom;
}


CProgressbarH::~CProgressbarH()
{
}


int CKT::GUI::CProgressbarH::Render()
{
	if (m_Texture)
	{
		SDL_Rect rBack = { (int)m_PosX, (int)m_PosY, (int)m_Width, (int)m_Height };
		SDL_SetRenderDrawColor(m_pRenderer, m_ColBack.r, m_ColBack.g, m_ColBack.b, m_ColBack.a);
		SDL_RenderFillRect(m_pRenderer, &rBack);
	}
	else
	{
		SDL_Rect rBack = { (int)m_PosX, (int)m_PosY, (int)m_Width, (int)m_Height };
		SDL_SetRenderDrawColor(m_pRenderer, m_ColBack.r, m_ColBack.g, m_ColBack.b, m_ColBack.a);
		SDL_RenderFillRect(m_pRenderer, &rBack);

		float PixelRange = m_Height - m_DiffBackFront * 2;
		float ValueRange = (float)m_Max - m_Min;

		float DrawHeight = (((m_Value - m_Min) * PixelRange) / ValueRange);

		SDL_Rect rFront = { 0 };
		if (m_Orientation == FromBottom)
			rFront = { (int)m_PosX + m_DiffBackFront, (int)m_PosY + (int)m_Height - m_DiffBackFront, (int)m_Width - m_DiffBackFront * 2, -(int)DrawHeight };
		else if (m_Orientation == FromCenter)
			rFront = { (int)m_PosX + m_DiffBackFront, (int)(m_PosY + m_Height / 2) - (int)DrawHeight / 2, (int)m_Width - m_DiffBackFront * 2, (int)DrawHeight };
		else
			rFront = { (int)m_PosX + m_DiffBackFront, (int)m_PosY + m_DiffBackFront, (int)m_Width - m_DiffBackFront * 2, (int)DrawHeight };

		SDL_SetRenderDrawColor(m_pRenderer, m_ColFront.r, m_ColFront.g, m_ColFront.b, m_ColFront.a);
		SDL_RenderFillRect(m_pRenderer, &rFront);
	}

	return 0;
}

