#include "Label.h"

using namespace CKT::GUI;

CLabel::CLabel()
{

}


CLabel::~CLabel()
{
}

void CKT::GUI::CLabel::TextColor(SDL_Color col)
{
	SDL_SetTextureColorMod(m_Texture, col.r, col.g, col.b);
}

int CLabel::Init(CKT::PRENDERER ren, const std::string& msg, float x, float y, SDL_Color col, CKT::GFX::FONT_ID id)
{
	CKT::PTEXTURE t = GFX::CFontManager::Instance()->TextToTexture(msg, col, ren, id);
	GfxObject::Init(ren, t, x, y, 1.0f);
	m_Message = msg;
	return 0;
}

int CKT::GUI::CLabel::Init(PRENDERER ren, const std::string & msg, float x, float y, GFX::FONT_ID id)
{
	Init(ren, msg, x, y, { 255,255,255,255 }, id);
	return 0;
}

int CKT::GUI::CLabel::Init(PRENDERER ren, std::string file, float x, float y, float s)
{
	GfxObject::Init(ren, file, x, y, s);
	return 0;
}
