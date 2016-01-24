#pragma once

#include "Common.h"

namespace CKT
{
	namespace GAME
	{
		class CCollisionObj;

		class CMoveableObject
		{
		protected:
			CCollisionObj* m_CollisionObj = nullptr;

		public:
			DllExport CMoveableObject();
			DllExport virtual ~CMoveableObject();

			DllExport void SetCollisionObj(CCollisionObj* colObj);
			DllExport CCollisionObj* GetCollisionObj();

			DllExport virtual int Update(float time) = 0;
		};

	}

}
