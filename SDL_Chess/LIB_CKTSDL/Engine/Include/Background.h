#pragma once

#include "Common.h"
#include "GfxObject.h"

namespace CKT
{
	namespace GAME
	{
		class CBackground : public GFX::CGfxObject
		{
		private:

			int m_TilesX;
			int m_TilesY;

		public:
			DllExport CBackground();
			DllExport ~CBackground();

			DllExport virtual int Init(PRENDERER ren, std::string file, int scrWidth, int scrHeight, float s = 1.0f);

			DllExport virtual int Render() override;

		};

	}

}
