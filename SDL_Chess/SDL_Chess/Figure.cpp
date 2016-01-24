#include "Figure.h"

using namespace CKT::GAME;

CFigure::CFigure(eWhere player, eFigures type)
{
	m_Player = player;
	m_Type = type;
}


CFigure::~CFigure()
{
}

void CKT::GAME::CFigure::SetBoardData(float tileSize, float x, float y)
{
	m_TileSize = tileSize;
	m_BoardX = x;
	m_BoardY = y;
}

void CKT::GAME::CFigure::SetField(int fx, int fy)
{
	m_FirstMove = false;
	m_PosX = m_BoardX + fx * m_TileSize;
	m_PosY = m_BoardY + fy * m_TileSize;
}

SDL_Point CKT::GAME::CFigure::GetField()
{
	SDL_Point p = { 0 };

	p.x = (int)((m_PosX - m_BoardX) / m_TileSize);
	p.y = (int)((m_PosY - m_BoardY) / m_TileSize);

	return p;
}

int CKT::GAME::CFigure::Update(float time)
{
	return 0;
}
