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
			DllExport CCollisionCircle(CGfxObject& parent, float radius);
			DllExport ~CCollisionCircle();

			DllExport float GetCenterX() { return m_CenterX; }
			DllExport float GetCenterY() { return m_CenterY; }
			DllExport float GetRadius() { return m_Radius; }

			DllExport virtual int Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s = 1.0f);

			// Geerbt über CCollisionObj
			DllExport virtual int Update(float time) override;

			DllExport virtual bool IsColliding(CCollisionRect * other) override;
			DllExport virtual bool IsColliding(CCollisionCircle * other) override;
		};

	}

}
