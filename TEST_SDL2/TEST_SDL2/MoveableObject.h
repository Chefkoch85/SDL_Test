#pragma once

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
			CMoveableObject();
			virtual ~CMoveableObject();

			void SetCollisionObj(CCollisionObj* colObj);
			CCollisionObj* GetCollisionObj();

			virtual int Update(float time) = 0;
		};

	}

}
