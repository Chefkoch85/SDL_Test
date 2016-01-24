#pragma once

#include "Common.h"
#include "GfxObject.h"
#include "MoveableObject.h"
#include "Collision.h"

namespace CKT
{
	namespace GAME
	{

		class CCollisionRect : public CCollisionObj
		{
		public:
			CCollisionRect(GfxObject& parent);
			~CCollisionRect();

			virtual int Update(float time) override;
			
			virtual bool IsColliding(CCollisionRect* other) override;
			virtual bool IsColliding(CCollisionCircle* other) override;

		};

	}

}
