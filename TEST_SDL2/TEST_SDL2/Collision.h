#pragma once

#include "GfxObject.h"
#include "MoveableObject.h"

namespace CKT
{
	namespace GAME
	{
		class CCollisionRect;
		class CCollisionCircle;

		class CCollisionObj : public GFX::GfxObject
		{
		protected:

			GfxObject& m_ParentObj;

			float m_OffsetX = 0.0f;
			float m_OffsetY = 0.0f;

			float m_CorrX = 0.0f;
			float m_CorrY = 0.0f;

		public:
			CCollisionObj(GfxObject& parent);
			~CCollisionObj();

			virtual int Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s = 1.0f);

			virtual int Update(float time) = 0;

			virtual bool IsColliding(CCollisionRect* other) = 0;
			virtual bool IsColliding(CCollisionCircle* other) = 0;
		};

	}

}
