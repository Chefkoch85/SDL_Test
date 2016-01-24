#pragma once

#include "GfxObject.h"
#include "MoveableObject.h"

namespace CKT
{
	namespace GAME
	{
		class CEntity : public GFX::CGfxObject, public CMoveableObject
		{
		public:
			DllExport CEntity();
			DllExport virtual ~CEntity();
		};

	}

}
