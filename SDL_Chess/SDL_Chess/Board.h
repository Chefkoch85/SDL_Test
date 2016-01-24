#pragma once

#include <Entity.h>
#include <CollisionRect.h>
#include <vector>
#include "Figure.h"

#include <iostream>

namespace CKT
{
	namespace GAME
	{
		class CBoard : public CEntity
		{
		public:
			struct SFieldData
			{
				eFigures FigureType;
				eWhere Player;
				int curFigureIndex;
				CFigure* curFigure;
			};

			typedef std::vector<SDL_Point> POINT_LIST;

		private:
			const float TileSize = 61.0f;

			int m_BoardW = 0, m_BoardH = 0;
			std::vector<CCollisionObj*> m_Colliders;

			eWhere m_PlayerUp = NO_PLAYER;
			eWhere m_CurPlayer = NO_PLAYER;

			bool m_MouseClickLeft = false;
			bool m_MouseClickRight = false;
			float m_MouseX = 0.0f, m_MouseY = 0.0f;

			bool m_Selected = false;
			int m_SelField = -1;
			int m_OldSelField = -1;
			float m_SelX = 0.0f, m_SelY = 0.0f;

			GFX::CGfxObject m_SelFrame;
			GFX::CGfxObject m_MoveFrame;
			GFX::CGfxObject m_TargetFrame;
			CFigure* m_CurSelected = nullptr;

			std::vector<SFieldData> m_Field;

			std::vector<CFigure*> m_Figures;
			CFigure* m_KingBlack = nullptr;
			CFigure* m_KingWhite = nullptr;
			std::vector<CFigure*> m_BlackKingThreat;
			std::vector<CFigure*> m_WhiteKingThreat;

			POINT_LIST m_MoveableSpots;

			int m_RemovedXBlack = 0;
			int m_RemovedXWhite = 0;
			int m_CountBlackRemoved = 0;
			int m_CountWhiteRemoved = 0;

			bool m_BlackKingNoMove = false;
			bool m_WhiteKingNoMove = false;

		private:
			void CalculateMovement(CFigure& fig);
			bool CheckMovement(CFigure& fig, int fx, int fy);

			void CalculatePawn(CFigure& fig, POINT_LIST& pointList);
			void CalculateTower(CFigure& fig, POINT_LIST& pointList);
			void CalculateHorse(CFigure& fig, POINT_LIST& pointList);
			void CalculateBishop(CFigure& fig, POINT_LIST& pointList);
			void CalculateQueen(CFigure& fig, POINT_LIST& pointList);
			void CalculateKing(CFigure& fig, POINT_LIST& pointList);

			bool CheckKing(CFigure& king);

		public:
			CBoard();
			~CBoard();

			friend std::ostream& operator<< (std::ostream &out, CKT::GAME::eFigures &fig);
			friend std::ostream& operator<< (std::ostream &out, CKT::GAME::eWhere &where);

		public:
			int Init(PRENDERER ren, std::string file, float x, float y, int boardW, int boardH, eWhere isUp);
			int InitFigure(std::string file, int x, int y, eFigures what, eWhere side);

			void LeftMouseDown(float x, float y);
			void RightMouseDown();

			void DumpField();

			eWhere& PlayerUp() { return m_PlayerUp; }

			eWhere IsVictory();

			/**
			*to clear the Board! If you start a new round then call this to reset the borad
			*and then init the figures again. If you wish to change the Player up then set
			*PlayerUp() befor you call Clear() to change the players
			*/
			void Clear();

		public:
			// Geerbt über CEntity
			virtual int Update(float time) override;
			virtual int Render() override;
		};

		std::ostream& operator<< (std::ostream &out, eFigures &fig);
	}

}
