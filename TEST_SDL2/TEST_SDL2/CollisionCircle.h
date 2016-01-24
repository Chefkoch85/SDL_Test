#pragma once

#include "Collision.h"

namespace CKT
{
	namespace GAME
	{

		class CCollisionCircle : public CCollisionObj
		{
		private:
			float m_CenterX = 0;
			float m_CenterY = 0;
			float m_Radius = 0;

			bool m_RadiusSet = false;

		public:
			CCollisionCircle(GfxObject& parent, float radius);
			~CCollisionCircle();

			float GetCenterX() { return m_CenterX; }
			float GetCenterY() { return m_CenterY; }
			float GetRadius() { return m_Radius; }

			virtual int Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s = 1.0f);

			// Geerbt über CCollisionObj
			virtual int Update(float time) override;

			virtual bool IsColliding(CCollisionRect * other) override;
			virtual bool IsColliding(CCollisionCircle * other) override;
		};

	}

}
