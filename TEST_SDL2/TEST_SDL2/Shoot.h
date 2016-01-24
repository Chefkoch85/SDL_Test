#pragma once

#include "Common.h"
#include "GfxObject.h"
#include "MoveableObject.h"
#include "Graphics.h"

#include "CollisionRect.h"

namespace CKT
{
	namespace GAME
	{

		class CShoot : public GFX::GfxObject, public CMoveableObject
		{
		private:

			float m_VelX = 0.0f;
			float m_VelY = 0.0f;

			SDL_Rect m_Bounds = { 0 };

			int m_AnimSpeed = 0;
			int m_AnimFirst = 0;
			int m_AnimLast = 0;

			bool m_IsActive = false;
			
		public:

			bool IsActive() { return m_IsActive; }

			float& VelX() { return m_VelX; }
			float& VelY() { return m_VelY; }

			SDL_Rect& Bounds() { return m_Bounds; }

			void Setup(int begin, int end, int speed);
			int& AnimSpeed() { return m_AnimSpeed; }
			
		public:
			CShoot();
			~CShoot();

			int Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s = 1.0f) override;

			int Update(float time) override;
			int Render() override;
		};

	}

}
