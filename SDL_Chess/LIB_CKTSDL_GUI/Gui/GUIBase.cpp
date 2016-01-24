#include "GUIBase.h"

#include "TextureManager.h"

using namespace CKT::GUI;

CKT::GUI::GUI_ID CKT::GUI::CGUIBase::ID_COUNTER = 0;

CGUIBase::CGUIBase()
{
	ID_COUNTER++;
	m_ID = ID_COUNTER;
}


CGUIBase::~CGUIBase()
{
}

void CKT::GUI::CGUIBase::SetContent(PTEXTURE tex, bool resize)
{
	CKT::GFX::CTextureManager::Instance()->releaseTexture(m_Texture);

	if (resize)
	{
		int w, h;
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
		m_Width = (float)w;
		m_Height = (float)h;

		m_rClip.w = w;
		m_rClip.h = h;
	}
	
	m_Texture = tex;
}

int CKT::GUI::CGUIBase::Render()
{
	if (!m_IsVisible)
		return 0;

	if ((m_BackgroundColor.r > 0 || m_BackgroundColor.g > 0 || m_BackgroundColor.b > 0) && m_BackgroundColor.a > 0 && m_pRenderer)
	{
		SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(m_pRenderer, m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, m_BackgroundColor.a);
		SDL_Rect rDst = { (int)m_PosX, (int)m_PosY, (int)m_Width, (int)m_Height };
		SDL_RenderFillRect(m_pRenderer, &rDst);
	}
	else if (m_Texture)
	{
		GFX::CGfxObject::Render();
	}

	return 0;
}
