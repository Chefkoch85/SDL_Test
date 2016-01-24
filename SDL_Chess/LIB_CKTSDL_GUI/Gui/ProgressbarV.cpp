#include "ProgressbarV.h"

using namespace CKT::GUI;

CProgressbarV::CProgressbarV()
{
	m_Orientation = FromLeft;
}


CProgressbarV::~CProgressbarV()
{
}

int CKT::GUI::CProgressbarV::Render()
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

		float PixelRange = m_Width - m_DiffBackFront * 2;
		float ValueRange = (float)m_Max - m_Min;

		float DrawWidth = (((m_Value - m_Min) * PixelRange) / ValueRange);

		SDL_Rect rFront = { 0 };
		if (m_Orientation == FromRight)
			rFront = { (int)m_PosX + (int)m_Width - m_DiffBackFront, (int)m_PosY + m_DiffBackFront, -(int)DrawWidth, (int)m_Height - m_DiffBackFront * 2 };
		else if(m_Orientation == FromCenter)
			rFront = { (int)(m_PosX + m_Width / 2) - (int)DrawWidth / 2, (int)m_PosY + m_DiffBackFront, (int)DrawWidth, (int)m_Height - m_DiffBackFront * 2 };
		else
			rFront = { (int)m_PosX + m_DiffBackFront, (int)m_PosY + m_DiffBackFront, (int)DrawWidth, (int)m_Height - m_DiffBackFront * 2 };

		SDL_SetRenderDrawColor(m_pRenderer, m_ColFront.r, m_ColFront.g, m_ColFront.b, m_ColFront.a);
		SDL_RenderFillRect(m_pRenderer, &rFront);
	}

	return 0;
}
