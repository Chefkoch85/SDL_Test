#include "Board.h"
#include <set>

#include <Point2D.h>

using namespace CKT::GAME;

#define OUT std::cout
#define NL std::endl

void CKT::GAME::CBoard::CalculateMovement(CFigure & fig)
{
	m_MoveableSpots.clear();
	int curX = fig.GetField().x;
	int curY = fig.GetField().y;

	bool oneEnemy = false;

	switch (fig.GetFiguresType())
	{
	case PAWN:
		CalculatePawn(fig, m_MoveableSpots);
		break;

	case TOWER:
		CalculateTower(fig, m_MoveableSpots);
		break;

	case HORSE:
		CalculateHorse(fig, m_MoveableSpots);
		break;

	case BISHOP:
		CalculateBishop(fig, m_MoveableSpots);
		break;

	case QUEEN:
		CalculateQueen(fig, m_MoveableSpots);
		break;

	case KING:
		CalculateKing(fig, m_MoveableSpots);
		break;
	}
}

bool CKT::GAME::CBoard::CheckMovement(CFigure& fig, int fx, int fy)
{
	bool moveOK = false;
	int nx = 0, ny = 0;

	for each (auto p in m_MoveableSpots)
	{
		if (p.x == fx && p.y == fy)
		{
			moveOK = true;
			break;
		}
	}

	return moveOK;
}

void CKT::GAME::CBoard::CalculatePawn(CFigure & fig, POINT_LIST & pointList)
{
	int curX = fig.GetField().x;
	int curY = fig.GetField().y;
	bool oneEnemy = false;

	int Side = 1;
	if (fig.GetPlayer() != m_PlayerUp)
		Side = -1;

	if (curY + Side < 0 || curY + Side >= m_BoardH)
		return;

	if (m_Field[curX + (curY + Side) * m_BoardW].FigureType != NONE &&
		fig.GetPlayer() == m_Field[curX + (curY + Side) * m_BoardW].curFigure->GetPlayer())
		return;

	// check enemy left
	if (curX - 1 >= 0 &&
		m_Field[(curX - 1) + (curY + (Side)) * m_BoardW].FigureType != NONE &&
		fig.GetPlayer() != m_Field[(curX - 1) + (curY + (Side)) * m_BoardW].curFigure->GetPlayer())
		pointList.push_back({ curX - 1, curY + Side });

	// check enemy right
	if (curX + 1 < m_BoardW &&
		m_Field[(curX + 1) + (curY + (Side)) * m_BoardW].FigureType != NONE &&
		fig.GetPlayer() != m_Field[(curX + 1) + (curY + (Side)) * m_BoardW].curFigure->GetPlayer())
		pointList.push_back({ curX + 1, curY + Side });

	// check enemy foward then no move possible
	if (m_Field[curX + (curY + (Side)) * m_BoardW].FigureType != NONE &&
		fig.GetPlayer() != m_Field[curX + (curY + (Side)) * m_BoardW].curFigure->GetPlayer())
		return;

	pointList.push_back({ curX, curY + Side });

	if (fig.GetFirstMove() && !oneEnemy)
	{
		if (m_Field[curX + (curY + (Side + Side)) * m_BoardW].FigureType != NONE &&
			fig.GetPlayer() == m_Field[curX + (curY + (Side + Side)) * m_BoardW].curFigure->GetPlayer())
			return;

		pointList.push_back({ curX, curY + (Side + Side) });
	}

}

void CKT::GAME::CBoard::CalculateTower(CFigure & fig, POINT_LIST& pointList)
{
	int curX = fig.GetField().x;
	int curY = fig.GetField().y;
	bool oneEnemy = false;
	// up
	for (int y = curY - 1; y >= 0; y--)
	{
		if (m_Field[curX + y * m_BoardW].FigureType != NONE &&
			m_Field[curX + y * m_BoardW].curFigure->GetPlayer() == fig.GetPlayer())
			break;

		if (m_Field[curX + y * m_BoardW].FigureType != NONE &&
			m_Field[curX + y * m_BoardW].curFigure->GetPlayer() != fig.GetPlayer())
		{
			if (oneEnemy)
				break;

			oneEnemy = true;
		}

		pointList.push_back({ curX, y });

		if (oneEnemy)
			break;
	}
	// down
	oneEnemy = false;
	for (int y = curY + 1; y < m_BoardW; y++)
	{
		if (m_Field[curX + y * m_BoardW].FigureType != NONE &&
			m_Field[curX + y * m_BoardW].curFigure->GetPlayer() == fig.GetPlayer())
			break;

		if (m_Field[curX + y * m_BoardW].FigureType != NONE &&
			m_Field[curX + y * m_BoardW].curFigure->GetPlayer() != fig.GetPlayer())
		{
			if (oneEnemy)
				break;

			oneEnemy = true;
		}

		pointList.push_back({ curX, y });

		if (oneEnemy)
			break;
	}
	// left
	oneEnemy = false;
	for (int x = curX - 1; x >= 0; x--)
	{
		if (m_Field[x + curY * m_BoardW].FigureType != NONE &&
			m_Field[x + curY * m_BoardW].curFigure->GetPlayer() == fig.GetPlayer())
			break;

		if (m_Field[x + curY * m_BoardW].FigureType != NONE &&
			m_Field[x + curY * m_BoardW].curFigure->GetPlayer() != fig.GetPlayer())
		{
			if (oneEnemy)
				break;

			oneEnemy = true;
		}

		pointList.push_back({ x, curY });

		if (oneEnemy)
			break;
	}
	// right
	oneEnemy = false;
	for (int x = curX + 1; x < m_BoardW; x++)
	{
		if (m_Field[x + curY * m_BoardW].FigureType != NONE &&
			m_Field[x + curY * m_BoardW].curFigure->GetPlayer() == fig.GetPlayer())
			break;

		if (m_Field[x + curY * m_BoardW].FigureType != NONE &&
			m_Field[x + curY * m_BoardW].curFigure->GetPlayer() != fig.GetPlayer())
		{
			if (oneEnemy)
				break;

			oneEnemy = true;
		}

		pointList.push_back({ x, curY });

		if (oneEnemy)
			break;
	}

}

void CKT::GAME::CBoard::CalculateHorse(CFigure & fig, POINT_LIST & pointList)
{
	int curX = fig.GetField().x;
	int curY = fig.GetField().y;
	bool oneEnemy = false;
	// right
	if (curX + 2 < m_BoardW && curY -1 >= 0 &&
		(m_Field[(curX + 2) + (curY - 1) * m_BoardW].FigureType == NONE ||
		fig.GetPlayer() != m_Field[(curX + 2) + (curY - 1) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX + 2, curY - 1 });

	if (curX + 2 < m_BoardW && curY + 1 < m_BoardH &&
		(m_Field[(curX + 2) + (curY + 1) * m_BoardW].FigureType == NONE ||
		fig.GetPlayer() != m_Field[(curX + 2) + (curY + 1) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX + 2, curY + 1 });
	// left
	if (curX - 2 >= 0 && curY - 1 >= 0 &&
		(m_Field[(curX - 2) + (curY - 1) * m_BoardW].FigureType == NONE ||
		fig.GetPlayer() != m_Field[(curX - 2) + (curY - 1) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX - 2, curY - 1 });

	if (curX - 2 >= 0 && curY + 1 < m_BoardH &&
		(m_Field[(curX - 2) + (curY + 1) * m_BoardW].FigureType == NONE ||
		fig.GetPlayer() != m_Field[(curX - 2) + (curY + 1) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX - 2, curY + 1 });
	// up
	if (curX - 1 >= 0 && curY - 2 >= 0 &&
		(m_Field[(curX - 1) + (curY - 2) * m_BoardW].FigureType == NONE ||
		fig.GetPlayer() != m_Field[(curX - 1) + (curY - 2) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX - 1, curY - 2 });

	if (curX + 1 < m_BoardW && curY - 2 >= 0 &&
		(m_Field[(curX + 1) + (curY - 2) * m_BoardW].FigureType == NONE ||
		fig.GetPlayer() != m_Field[(curX + 1) + (curY - 2) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX + 1, curY - 2 });
	// down
	if (curX - 1 >= 0 && curY + 2 < m_BoardH &&
		(m_Field[(curX - 1) + (curY + 2) * m_BoardW].FigureType == NONE ||
		fig.GetPlayer() != m_Field[(curX - 1) + (curY + 2) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX - 1, curY + 2 });

	if (curX + 1 < m_BoardW && curY + 2 < m_BoardH &&
		(m_Field[(curX + 1) + (curY + 2) * m_BoardW].FigureType == NONE ||
		fig.GetPlayer() != m_Field[(curX + 1) + (curY + 2) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX + 1, curY + 2 });
}

void CKT::GAME::CBoard::CalculateBishop(CFigure & fig, POINT_LIST & pointList)
{
	int curX = fig.GetField().x;
	int curY = fig.GetField().y;
	bool oneEnemyTL = false;
	bool oneEnemyTR = false;
	bool oneEnemyBL = false;
	bool oneEnemyBR = false;

	// Top Left
	for (int y = curY - 1; y >= 0; y--)
	{
		for (int x = curX - 1; x >= 0; x--)
		{
			if (x + curY == y + curX)
			{
				if (m_Field[x + y * m_BoardW].FigureType != NONE &&
					fig.GetPlayer() == m_Field[x + y * m_BoardW].curFigure->GetPlayer())
				{
					oneEnemyTL = true;
					break;
				}

				if (m_Field[x + y * m_BoardW].FigureType != NONE &&
					fig.GetPlayer() != m_Field[x + y * m_BoardW].curFigure->GetPlayer())
					oneEnemyTL = true;

				pointList.push_back({ x, y });
				break;
			}
		}

		if (oneEnemyTL)
			break;
	}
	// Top Right
	for (int y = curY - 1; y >= 0; y--)
	{
		for (int x = curX + 1; x < m_BoardW; x++)
		{
			if (x - curY == curX - y)
			{
				if (m_Field[x + y * m_BoardW].FigureType != NONE &&
					fig.GetPlayer() == m_Field[x + y * m_BoardW].curFigure->GetPlayer())
				{
					oneEnemyTR = true;
					break;
				}

				if (m_Field[x + y * m_BoardW].FigureType != NONE &&
					fig.GetPlayer() != m_Field[x + y * m_BoardW].curFigure->GetPlayer())
					oneEnemyTR = true;

				pointList.push_back({ x, y });
				break;
			}
		}

		if (oneEnemyTR)
			break;
	}
	// Bottom Left
	for (int y = curY + 1; y < m_BoardH; y++)
	{
		for (int x = curX - 1; x >= 0; x--)
		{
			if (x - curY == curX - y)
			{
				if (m_Field[x + y * m_BoardW].FigureType != NONE &&
					fig.GetPlayer() == m_Field[x + y * m_BoardW].curFigure->GetPlayer())
				{
					oneEnemyBL = true;
					break;
				}

				if (m_Field[x + y * m_BoardW].FigureType != NONE &&
					fig.GetPlayer() != m_Field[x + y * m_BoardW].curFigure->GetPlayer())
					oneEnemyBL = true;

				pointList.push_back({ x, y });
				break;
			}
		}

		if (oneEnemyBL)
			break;
	}	
	// Bottom Right
	for (int y = curY + 1; y < m_BoardH; y++)
	{
		for (int x = curX + 1; x < m_BoardW; x++)
		{
			if (x + curY == y + curX)
			{
				if (m_Field[x + y * m_BoardW].FigureType != NONE &&
					fig.GetPlayer() == m_Field[x + y * m_BoardW].curFigure->GetPlayer())
				{
					oneEnemyBR = true;
					break;
				}

				if (m_Field[x + y * m_BoardW].FigureType != NONE &&
					fig.GetPlayer() != m_Field[x + y * m_BoardW].curFigure->GetPlayer())
					oneEnemyBR = true;

				pointList.push_back({ x, y });
				break;
			}
		}

		if (oneEnemyBR)
			break;
	}
	
}

void CKT::GAME::CBoard::CalculateQueen(CFigure & fig, POINT_LIST & pointList)
{
	int curX = fig.GetField().x;
	int curY = fig.GetField().y;
	bool oneEnemy = false;

	// row /col
	CalculateTower(fig, pointList);
	// diagonal
	CalculateBishop(fig, pointList);
}

void CKT::GAME::CBoard::CalculateKing(CFigure & fig, POINT_LIST & pointList)
{
	int curX = fig.GetField().x;
	int curY = fig.GetField().y;
	bool oneEnemy = false;

	// right
	if (curX + 1 < m_BoardW && curY - 1 >= 0 &&
		(m_Field[(curX + 1)+(curY - 1) * m_BoardW].FigureType == NONE ||
		fig.GetPlayer() != m_Field[(curX + 1) + (curY - 1) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX + 1, curY - 1 });

	if (curX + 1 < m_BoardW &&
		(m_Field[(curX + 1) + (curY) * m_BoardW].FigureType == NONE ||
			fig.GetPlayer() != m_Field[(curX + 1) + (curY) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX + 1, curY });

	if (curX + 1 < m_BoardW && curY + 1 < m_BoardH &&
		(m_Field[(curX + 1) + (curY + 1) * m_BoardW].FigureType == NONE ||
			fig.GetPlayer() != m_Field[(curX + 1) + (curY + 1) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX + 1, curY + 1 });
	// left
	if (curX - 1 >= 0 && curY - 1 >= 0 &&
		(m_Field[(curX - 1) + (curY - 1) * m_BoardW].FigureType == NONE ||
			fig.GetPlayer() != m_Field[(curX - 1) + (curY - 1) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX - 1, curY - 1 });

	if (curX - 1 >= 0 &&
		(m_Field[(curX - 1) + (curY) * m_BoardW].FigureType == NONE ||
			fig.GetPlayer() != m_Field[(curX - 1) + (curY) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX - 1, curY });

	if (curX - 1 >= 0 && curY + 1 < m_BoardH &&
		(m_Field[(curX - 1) + (curY + 1) * m_BoardW].FigureType == NONE ||
			fig.GetPlayer() != m_Field[(curX - 1) + (curY + 1) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX - 1, curY + 1 });
	// up
	if (curY - 1 >= 0 &&
		(m_Field[(curX) + (curY - 1) * m_BoardW].FigureType == NONE ||
		fig.GetPlayer() != m_Field[(curX) + (curY - 1) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX, curY - 1 });
	// down
	if (curY + 1 < m_BoardH &&
		(m_Field[(curX)+(curY + 1) * m_BoardW].FigureType == NONE ||
			fig.GetPlayer() != m_Field[(curX) + (curY + 1) * m_BoardW].curFigure->GetPlayer()))
		pointList.push_back({ curX, curY + 1 });
}

bool CKT::GAME::CBoard::CheckKing(CFigure & king)
{
	if (king.GetPlayer() == BLACK)
		m_BlackKingThreat.clear();
	if (king.GetPlayer() == WHITE)
		m_WhiteKingThreat.clear();

	int curX = king.GetField().x;
	int curY = king.GetField().y;
	bool oneEnemy = false;

	bool BlackKingTarget = false;
	bool WhiteKingTarget = false;

	std::vector<SDL_Point> possibleKingMoves;
	POINT_LIST figMovement;

	std::set<CPoint2D*> remainingKingMoves;

	if (!king.IsAlive())
	{
		if (king.GetPlayer() == BLACK)
		{
			m_BlackKingNoMove = true;
		}
		else if (king.GetPlayer() == WHITE)
		{
			m_WhiteKingNoMove = true;
		}
	}

	if (m_BlackKingNoMove || m_WhiteKingNoMove)
		return true;

	CalculateKing(king, possibleKingMoves);

	for each(auto fig in m_Figures)
	{
		if (fig->IsAlive() && fig->GetPlayer() != king.GetPlayer())
		{
			CalculateMovement(*fig);

			for each (auto pFig in m_MoveableSpots)
			{
				if (pFig.x == curX && pFig.y == curY)
				{
					if (king.GetPlayer() == BLACK)
					{
						BlackKingTarget = true;
						m_BlackKingThreat.push_back(fig);
					}
					else if (king.GetPlayer() == WHITE)
					{
						WhiteKingTarget = true;
						m_WhiteKingThreat.push_back(fig);
					}
				}
			}
		}
	}

	return m_BlackKingNoMove || m_WhiteKingNoMove;
}

CBoard::CBoard()
{
}


CBoard::~CBoard()
{
	for each (CCollisionRect* cr in m_Colliders)
	{
		if (cr)
			delete cr;
	}

	m_Colliders.clear();

	for each (auto fig in m_Figures)
	{
		if (fig)
			delete fig;
	}

	m_Figures.clear();
}

int CKT::GAME::CBoard::Init(PRENDERER ren, std::string file, float x, float y, int boardW, int boardH, eWhere isUp)
{
	CEntity::Init(ren, file, x, y);

	m_BoardW = boardW;
	m_BoardH = boardH;

	m_PlayerUp = isUp;

	Clear();

	m_SelFrame.Init(m_pRenderer, getResourcePath() + "IMG\\Rect_Sel.png", 0, 0, TileSize, TileSize);
	m_SelFrame.Visibility() = false; 
	m_MoveFrame.Init(m_pRenderer, getResourcePath() + "IMG\\Rect_Tar.png", 0, 0, TileSize, TileSize);
	m_MoveFrame.Visibility() = false;
	m_TargetFrame.Init(m_pRenderer, getResourcePath() + "IMG\\Rect_Err.png", 0, 0, TileSize, TileSize);
	m_TargetFrame.Visibility() = false;

	for (int y = 0; y < m_BoardH; y++)
	{
		for (int x = 0; x < m_BoardW; x++)
		{
			CCollisionRect* cr = new CCollisionRect(*this);
			cr->Init(m_pRenderer, CKT::getResourcePath() + "IMG\\Rect_96.png", x * TileSize, y * TileSize, TileSize, TileSize);
			cr->ResetObjCorr();
			int* id = new int;
			*id = x + y * m_BoardW;
			cr->SetTag(id);
			m_Colliders.push_back(cr);
		}
	}

	for (int i = 0; i < m_BoardW * m_BoardH; i++)
	{
		SFieldData data;
		data.FigureType = NONE;
		data.curFigureIndex = -1;
		data.Player = NO_PLAYER;
		data.curFigure = nullptr;
		m_Field.push_back(data);
	}

	return 0;
}

int CKT::GAME::CBoard::InitFigure(std::string file, int x, int y, eFigures what, eWhere side)
{
	CFigure* fig = new CFigure(side, what);
	fig->Init(m_pRenderer, file, m_PosX + x * TileSize, m_PosY + y * TileSize, TileSize, TileSize);
	fig->SetBoardData(TileSize, m_PosX, m_PosY);

	if (what == KING && m_KingBlack == nullptr)
		m_KingBlack = fig;
	else if (what == KING && m_KingWhite == nullptr)
		m_KingWhite = fig;

	m_Field[x + y * m_BoardW].FigureType = what;
	m_Field[x + y * m_BoardW].Player = side;
	m_Field[x + y * m_BoardW].curFigureIndex = (int)m_Figures.size();
	m_Field[x + y * m_BoardW].curFigure = fig;
	m_Figures.push_back(fig);

	return 0;
}

void CKT::GAME::CBoard::LeftMouseDown(float x, float y)
{
	m_MouseClickLeft = true;
	m_MouseX = x;
	m_MouseY = y;

	//std::cout << m_MouseX << " : " << m_MouseY << std::endl;
}

void CKT::GAME::CBoard::RightMouseDown()
{
	m_MouseClickRight = true;
}

void CKT::GAME::CBoard::DumpField()
{
	std::string line = std::string(6*8+9, '-');

	std::cout << " |";
	for (int i = 0; i < m_BoardW; i++)
	{
		std::cout.width(6);
		std::cout << (i + 1) << " ";
	}


	char c[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	std::cout << std::endl;
	std::cout << line;
	std::cout << std::endl;
	std::cout << c[0] << "|";

	for (int i = 0; i < m_BoardW * m_BoardH; i++)
	{
		std::cout.width(3);
		std::cout << m_Field[i].Player << ":";
		std::cout.width(2);
		std::cout << m_Field[i].FigureType <<  " ";

		if (i > 0 && i < m_BoardW * m_BoardH - 1 && (i + 1) % 8 == 0)
		{
			std::cout << std::endl;
			std::cout << " |";
			std::cout << std::endl;
			std::cout << " |";
			std::cout << std::endl;
			std::cout << c[i / 8 + 1] << "|";
		}
	}

	std::cout << std::endl;
}

eWhere CKT::GAME::CBoard::IsVictory()
{
	if (m_CountBlackRemoved >= 16)
		return WHITE;

	else if (m_CountWhiteRemoved >= 16)
		return BLACK;

	else if (m_BlackKingNoMove)
		return WHITE;

	else if (m_WhiteKingNoMove)
		return BLACK;

	return NO_PLAYER;
}

void CKT::GAME::CBoard::Clear()
{
	m_Field.clear();

	for (int i = 0; i < m_BoardW * m_BoardH; i++)
	{
		SFieldData data;
		data.FigureType = NONE;
		data.curFigureIndex = -1;
		data.Player = NO_PLAYER;
		data.curFigure = nullptr;
		m_Field.push_back(data);
	}

	for each (auto fig in m_Figures)
	{
		if (fig)
			delete fig;
	}

	m_Figures.clear();

	m_BlackKingNoMove = false;
	m_WhiteKingNoMove = false;

	m_KingBlack = nullptr;
	m_KingWhite = nullptr;

	m_CurPlayer = m_PlayerUp;
}


int CKT::GAME::CBoard::Update(float time)
{
	if (m_Figures.size() <= 0)
		return 1;

	if (m_PlayerUp == BLACK)
	{
		m_RemovedXBlack = (int)(m_PosX - m_Figures[0]->Width() - 15);
		m_RemovedXWhite = (int)(m_PosX + m_Width + 15);
	}
	else
	{
		m_RemovedXBlack = (int)(m_PosX + m_Width + 15);
		m_RemovedXWhite = (int)(m_PosX - m_Figures[0]->Width() - 15);
	}

	for each (auto cr in m_Colliders)
	{
		cr->Update(time);

		if (m_MouseClickLeft)
		{
			if (m_MouseX >= cr->X() && m_MouseX < cr->X() + cr->Width() &&
				m_MouseY >= cr->Y() && m_MouseY < cr->Y() + cr->Height())
			{
				m_SelField = *(int*)(cr->GetTag());

				if (m_Field[m_SelField].FigureType != NONE && m_Field[m_SelField].Player == m_CurPlayer || 
					m_Selected)
				{
					m_SelX = cr->X();
					m_SelY = cr->Y();

					if (m_Selected && 
						(m_Field[m_SelField].FigureType == NONE || 
						m_CurSelected->GetPlayer() != m_Field[m_SelField].Player))
					{
						m_Selected = false;

						int id = m_Field[m_OldSelField].curFigureIndex;
						int newX = (int)((m_SelX - m_PosX) / TileSize);
						int newY = (int)((m_SelY - m_PosY) / TileSize);

						//std::cout << m_Figures[id]->GetField().x << " : " << m_Figures[id]->GetField().y << std::endl;
						//std::cout <<newX << " : " << newY << std::endl;
						
						if (CheckMovement(*m_Figures[id], newX, newY))
						{
							int oldID = m_Field[m_SelField].curFigureIndex;
							bool attack = false;
							int removedX = 0, removedY = 0;
							if (m_Field[m_SelField].FigureType != NONE && m_CurSelected->GetPlayer() != m_Field[m_SelField].Player)
							{
								if (m_Field[m_SelField].Player == WHITE)
								{
									removedX = m_RemovedXWhite;
									if (m_PlayerUp == WHITE)
									{
										if (m_CountWhiteRemoved > 7)
											removedX -= (int)m_Figures[0]->Width();

										removedY = (int)(m_PosY + m_Figures[0]->Height() * (m_CountWhiteRemoved % 8));
									}
									else
									{
										if (m_CountWhiteRemoved > 7)
											removedX += (int)m_Figures[0]->Width();

										removedY = (int)((m_PosY + m_Height - m_Figures[0]->Height()) - m_Figures[0]->Height() * (m_CountWhiteRemoved % 8));
									}
									
									m_CountWhiteRemoved++;
								}
								else if (m_Field[m_SelField].Player == BLACK)
								{
									removedX = m_RemovedXBlack; 
									if (m_PlayerUp == BLACK)
									{
										if (m_CountBlackRemoved > 7)
											removedX -= (int)m_Figures[0]->Width();

										removedY = (int)(m_PosY + m_Figures[0]->Height() * (m_CountBlackRemoved % 8));
									}
									else
									{
										if (m_CountBlackRemoved > 7)
											removedX += (int)m_Figures[0]->Width();

										removedY = (int)((m_PosY + m_Height - m_Figures[0]->Height()) - m_Figures[0]->Height() * (m_CountBlackRemoved % 8));
									}

									m_CountBlackRemoved++;
								}

								m_Figures[oldID]->SetPos((float)removedX, (float)removedY);
								m_Figures[oldID]->IsAlive() = false;

								attack = true;
							}

							//int temp = m_Field[m_SelField].FigureType;
							m_Field[m_SelField].FigureType = m_Field[m_OldSelField].FigureType;
							m_Field[m_OldSelField].FigureType = NONE;

							m_Field[m_SelField].curFigureIndex = id;
							m_Field[m_OldSelField].curFigureIndex = -1;

							m_Field[m_SelField].curFigure = m_Field[m_OldSelField].curFigure;
							m_Field[m_OldSelField].curFigure = nullptr;

							//temp = m_Field[m_SelField].Player;
							m_Field[m_SelField].Player = m_Field[m_OldSelField].Player;
							m_Field[m_OldSelField].Player = NO_PLAYER;

							m_Figures[id]->SetField(newX, newY);

							m_WhiteKingNoMove = CheckKing(*m_KingWhite);
							m_BlackKingNoMove = CheckKing(*m_KingBlack);

							m_CurPlayer = m_CurPlayer == BLACK ? WHITE : BLACK;
						}

						m_SelField = -1;
						m_CurSelected = nullptr;
					}

					if (m_SelField >= 0 && m_Field[m_SelField].FigureType != NONE)
					{
						m_Selected = true;
						m_CurSelected = m_Figures[m_Field[m_SelField].curFigureIndex];

						if (m_Selected && m_CurSelected != nullptr)
							CalculateMovement(*m_CurSelected);
					}

				}
				else
					m_SelField = -1;
			}
		}

		if (m_MouseClickRight)
		{
			m_Selected = false;
			m_SelField = -1;
			m_CurSelected = nullptr;
		}
	}

	m_OldSelField = m_SelField;

	for each (auto fig in m_Figures)
	{
		fig->Update(time);
	}

	if (m_SelField >= 0)
	{
		m_SelFrame.Visibility() = true;
		m_SelFrame.SetPos(m_SelX, m_SelY);
	}

	if (m_CurSelected == nullptr)
		m_MoveableSpots.clear();

	m_MouseClickLeft = false;
	m_MouseClickRight = false;
	return 0;
}

int CKT::GAME::CBoard::Render()
{
	GFX::CGfxObject::Render();

	for each (auto cr in m_Colliders)
	{
		//cr->Render();
	}
	
	for each (auto fig in m_Figures)
	{
		fig->Render();
	}

	for each (auto p in m_MoveableSpots)
	{
		if (p.x >= 0 && p.x < m_BoardW && p.y >= 0 && p.y < m_BoardH)
		{
			if (m_Field[p.x + p.y * m_BoardW].FigureType != NONE && 
				m_CurSelected->GetPlayer() != m_Field[p.x + p.y * m_BoardW].curFigure->GetPlayer())
			{
				m_TargetFrame.Visibility() = true;
				m_TargetFrame.SetPos(m_PosX + p.x * TileSize, m_PosY + p.y * TileSize);
				m_TargetFrame.Render();
			}
			else
			{
				m_MoveFrame.Visibility() = true;
				m_MoveFrame.SetPos(m_PosX + p.x * TileSize, m_PosY + p.y * TileSize);
				m_MoveFrame.Render();
			}
		}
	}

	if (m_BlackKingThreat.size() > 0)
	{
		for each (auto t in m_BlackKingThreat)
		{
			m_TargetFrame.Visibility() = true;
			m_TargetFrame.SetPos(m_PosX + t->GetField().x * TileSize, m_PosY + t->GetField().y * TileSize);
			m_TargetFrame.Render();
		}
	}
	if (m_WhiteKingThreat.size() > 0)
	{
		for each (auto t in m_WhiteKingThreat)
		{
			m_TargetFrame.Visibility() = true;
			m_TargetFrame.SetPos(m_PosX + t->GetField().x * TileSize, m_PosY + t->GetField().y * TileSize);
			m_TargetFrame.Render();
		}
	}

	if (m_SelField >= 0)
		m_SelFrame.Render();

	//m_MoveableSpots.clear();

	return 0;
}

std::ostream & CKT::GAME::operator<<(std::ostream & out, CKT::GAME::eFigures & fig)
{
	// Since operator<< is a friend of the Point class, we can access
	// Point's members directly.
	std::string temp = "";
	switch (fig)
	{
	case NONE:		temp = "N";			break;
	case PAWN:		temp = "PA";		break;
	case TOWER:		temp = "TO";		break;
	case HORSE:		temp = "HO";		break;
	case BISHOP:	temp = "BI";		break;
	case QUEEN:		temp = "QU";		break;
	case KING:		temp = "KI";		break;
	}

	out << temp;
	return out;
}

std::ostream & CKT::GAME::operator<<(std::ostream & out, CKT::GAME::eWhere & where)
{
	std::string temp = "";
	switch (where)
	{
	case NONE:		temp = "N";			break;
	case BLACK:		temp = "BL";		break;
	case WHITE:		temp = "WH";		break;
	}

	out << temp;
	return out;
}
