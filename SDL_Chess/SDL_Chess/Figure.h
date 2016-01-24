#pragma once

#include <Entity.h>

namespace CKT
{
	namespace GAME
	{
		enum eFigures
		{
			NONE = 0x0000,
			PAWN = 0x0001,
			TOWER = 0x0002,
			HORSE = 0x0004,
			BISHOP = 0x0008,
			QUEEN = 0x0010,
			KING = 0x0020,
		};
		enum eWhere
		{
			NO_PLAYER,
			BLACK,
			WHITE,
		};

		class CFigure : public CEntity
		{
		private:
			float m_TileSize = 0;
			float m_BoardX = 0.0f;
			float m_BoardY = 0.0f;

			bool m_FirstMove = true;

			eFigures m_Type = NONE;
			eWhere m_Player = NO_PLAYER;

			bool m_IsAlive = true;

		public:
			CFigure(eWhere player, eFigures type);
			virtual ~CFigure();

			bool& IsAlive() { return m_IsAlive; }

			eWhere GetPlayer() { return m_Player; }
			eFigures GetFiguresType() { return m_Type; }
			bool GetFirstMove() { return m_FirstMove; }

			void SetBoardData(float tileSize, float x, float y);
			void SetField(int fx, int fy);
			SDL_Point GetField();

			// Geerbt über CEntity
			virtual int Update(float time) override;
		};

	}

}
