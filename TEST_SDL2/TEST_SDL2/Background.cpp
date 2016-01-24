#include "Background.h"

#include "Graphics.h"

CKT::GAME::CBackground::CBackground()
{
}


CKT::GAME::CBackground::~CBackground()
{
}

int CKT::GAME::CBackground::Init(PRENDERER ren, std::string file, int scrWidth, int scrHeight, float s)
{
	GFX::GfxObject::Init(ren, file, 0, 0, s);

	m_TilesX = scrWidth / (int)m_Width;
	m_TilesY = scrHeight / (int)m_Height;

	return 0;
}

int CKT::GAME::CBackground::Render()
{
	// Draw the background
	for (int i = 0; i < m_TilesX * m_TilesY; i++)
	{
		int x = i % m_TilesX;
		int y = i / m_TilesX;
		CKT::GFX::renderTexture(m_Texture, m_pRenderer, x * (int)m_Width, y * (int)m_Height);
	}

	return 0;
}
