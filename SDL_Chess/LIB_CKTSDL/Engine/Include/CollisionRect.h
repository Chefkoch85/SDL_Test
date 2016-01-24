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
			DllExport CCollisionRect(CGfxObject& parent);
			DllExport ~CCollisionRect();

			DllExport virtual int Update(float time) override;
			
			DllExport virtual bool IsColliding(CCollisionRect* other) override;
			DllExport virtual bool IsColliding(CCollisionCircle* other) override;

		};

	}

}
