#pragma once

#include "GfxObject.h"
#include "MoveableObject.h"

namespace CKT
{
	namespace GAME
	{
		class CCollisionRect;
		class CCollisionCircle;

		class CCollisionObj : public GFX::CGfxObject
		{
		protected:

			CGfxObject& m_ParentObj;

			float m_OffsetX = 0.0f;
			float m_OffsetY = 0.0f;

			float m_CorrX = 0.0f;
			float m_CorrY = 0.0f;

			void* m_Tag = nullptr;

		public:
			DllExport CCollisionObj(CGfxObject& parent);
			DllExport virtual ~CCollisionObj();

			DllExport virtual int Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s = 1.0f);

			DllExport virtual int Update(float time) = 0;

			DllExport float& OffsetX() { return m_OffsetX; }
			DllExport float& OffsetY() { return m_OffsetY; }

			DllExport void SetTag(void* tag) { m_Tag = tag; }
			DllExport void* GetTag() { return m_Tag; }

			DllExport void ResetObjCorr() { m_CorrX = 0.0f; m_CorrY = 0.0f; }

			DllExport virtual bool IsColliding(CCollisionRect* other) = 0;
			DllExport virtual bool IsColliding(CCollisionCircle* other) = 0;
		};

	}

}
