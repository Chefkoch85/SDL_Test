#pragma once

#include "GUIBase.h"

#include "FontManager.h"

namespace CKT
{
	namespace GUI
	{
		class CLabel : public CGUIBase
		{
		private:
			std::string m_Message = "";

		public:
			CLabel();
			~CLabel();

			void TextColor(SDL_Color col);

		public:
			int CLabel::Init(PRENDERER ren, const std::string& msg, float x, float y, SDL_Color col, GFX::FONT_ID id);
			int CLabel::Init(PRENDERER ren, const std::string& msg, float x, float y, GFX::FONT_ID id);
			int Init(PRENDERER ren, std::string file, float x, float y, float s = 1.0f) override;
		};

	}

}