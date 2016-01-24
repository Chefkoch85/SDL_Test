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
			SDL_Color m_TextColor;
			GFX::FONT_ID m_FontID = -1;

		public:
			DllExport CLabel();
			DllExport ~CLabel();

			DllExport void TextColor(SDL_Color col);
			DllExport SDL_Color TextColor() { return m_TextColor; }

			DllExport GFX::FONT_ID FontID() { return m_FontID; }
			DllExport std::string Text() { return m_Message; }

		public:
			DllExport int CLabel::Init(PRENDERER ren, const std::string& msg, float x, float y, SDL_Color col, GFX::FONT_ID id);
			DllExport int CLabel::Init(PRENDERER ren, const std::string& msg, float x, float y, GFX::FONT_ID id);
			DllExport int Init(PRENDERER ren, std::string file, float x, float y, float s = 1.0f) override;
		};

	}

}