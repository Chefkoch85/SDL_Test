#include "Include\GfxObject.h"

#include "Include\Graphics.h"


void CKT::GFX::CGfxObject::_SetScale(float sx, float sy)
{
	if (sx > 0)
		m_ScaleX = sx;

	if (sy > 0)
		m_ScaleY = sy;

	float oldWidth = m_Width;
	float oldHeight = m_Height;

	m_Width = m_AnimWidth * m_ScaleX;
	m_Height = m_AnimHeight * m_ScaleY;

	m_DesignWidth = m_Width;
	m_DesignHeight = m_Height;

	m_PosX += ((oldWidth - m_Width) / 2);
	m_PosY += ((oldHeight - m_Height) / 2);
}

void CKT::GFX::CGfxObject::SetScale(float s)
{
	_SetScale(s, s);
}

void CKT::GFX::CGfxObject::SetScale(float sx, float sy)
{
	_SetScale(sx, sy);
}

void CKT::GFX::CGfxObject::SetScaleX(float sx)
{
	_SetScale(sx, m_ScaleY);
}

void CKT::GFX::CGfxObject::SetScaleY(float sy)
{
	_SetScale(m_ScaleX, sy);
}

CKT::GFX::CGfxObject::CGfxObject()
{

}


CKT::GFX::CGfxObject::~CGfxObject()
{
	//SDL_DestroyTexture(m_Texture); // the texture can be shared with other modells so it can't be destroied here!
	CKT::GFX::CTextureManager::Instance()->releaseTexture(m_Texture);
}

int CKT::GFX::CGfxObject::Init(PRENDERER ren, PTEXTURE tex, float x, float y, float s)
{
	m_Texture = tex;

	// size
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_TexWidth, &m_TexHeight);

	// Clipping rect for one frame
	m_rClip = { 0,0,m_TexWidth, m_TexHeight };

	// resize the player modell
	m_ScaleX = s;
	m_ScaleY = s;
	m_Width = m_TexWidth * s;
	m_Height = m_TexHeight * s;

	m_DesignWidth = m_Width;
	m_DesignHeight = m_Height;

	m_AnimWidth = (int)m_Width;
	m_AnimHeight = (int)m_Height;

	// set start point (center of screen)
	m_PosX = x;
	m_PosY = y;

	m_DesignX = x;
	m_DesignY = y;

	m_pRenderer = ren;

	m_lastTime = SDL_GetTicks();

	return 0;
}

int CKT::GFX::CGfxObject::Init(PRENDERER ren, std::string file, float x, float y, float s)
{
	// texture
	//m_Texture = CKT::GFX::loadTexture(file, ren);
	m_Texture = CKT::GFX::CTextureManager::Instance()->loadTexture(file, ren);

	// size
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_TexWidth, &m_TexHeight);

	// Clipping rect for one frame
	m_rClip = { 0,0,m_TexWidth, m_TexHeight };

	// resize the player modell
	m_ScaleX = s;
	m_ScaleY = s;
	m_Width = m_TexWidth * s;
	m_Height = m_TexHeight * s;
	
	m_DesignWidth = m_Width;
	m_DesignHeight = m_Height;

	m_AnimWidth = (int)m_Width;
	m_AnimHeight = (int)m_Height;

	// set start point (center of screen)
	m_PosX = x;
	m_PosY = y;

	m_DesignX = x;
	m_DesignY = y;

	m_pRenderer = ren;

	m_lastTime = SDL_GetTicks();

	return 0;
}

int CKT::GFX::CGfxObject::Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s)
{
	Init(ren, file, x, y, s);

	m_Width = w;
	m_Height = h;

	m_DesignWidth = m_Width;
	m_DesignHeight = m_Height;

	return 0;
}

int CKT::GFX::CGfxObject::Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s)
{
	Init(ren, file, x, y, s);
	m_Width /= xTiles;
	m_Height /= yTiles;

	m_DesignWidth = m_Width;
	m_DesignHeight = m_Height;

	m_AnimWidth = m_TexWidth / xTiles;
	m_AnimHeight = m_TexHeight / yTiles;

	m_rClip = { 0, 0, m_AnimWidth, m_AnimHeight };

	return 0;
}

int CKT::GFX::CGfxObject::Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, SDL_Rect clip, float s)
{
	Init(ren, file, x, y, xTiles, yTiles, s);
	m_rClip = clip;

	return 0;
}

int CKT::GFX::CGfxObject::Render()
{
	if (!m_IsVisible)
		return 0;

	SDL_Rect rDst = { (int)m_PosX, (int)m_PosY, (int)(m_Width + 0.5f), (int)(m_Height + 0.5f) };

	if (m_AlphaMod < 255)
	{
		SDL_SetTextureBlendMode(m_Texture, m_BlendMode);
		SDL_SetTextureAlphaMod(m_Texture, m_AlphaMod);
	}

	if (m_UseRotate)
	{
		if (m_rClip.w == 0 && m_rClip.h == 0)
			CKT::GFX::renderTexture(m_Texture, m_pRenderer, rDst, m_Angle, &m_RotationCenter, m_Flipping);
		else
			CKT::GFX::renderTexture(m_Texture, m_pRenderer, rDst, m_Angle, &m_RotationCenter, m_Flipping, &m_rClip);
	}
	else
	{
		if (m_rClip.w == 0 && m_rClip.h == 0)
			CKT::GFX::renderTexture(m_Texture, m_pRenderer, rDst);
		else
			CKT::GFX::renderTexture(m_Texture, m_pRenderer, rDst, &m_rClip);
	}

	return 0;
}

void CKT::GFX::CGfxObject::ResetAnimation()
{
	m_AnimStep = 0;
	m_AnimStepX = 0;
	m_AnimStepY = 0;
	m_AnimTimesToPlay = -1;
}

int CKT::GFX::CGfxObject::PlayAnimation(int beginn, int end, int speed, bool loop)
{
	int ret = 1;
	Uint32 time = SDL_GetTicks();

	if (time > m_lastTime + speed)
	{
		if (loop && m_AnimStep >= end)
		{
			m_AnimStep = beginn;
			m_AnimStepX = beginn;
			m_AnimStepY = 0;
			ret = 0;
			m_AnimActiv = false;
		}
		else if (!loop && m_AnimStep >= end)
		{
			ret = 0;
			m_AnimActiv = false;
		}
		else
		{
			m_AnimActiv = true;
			m_AnimStep++;
			m_AnimStepX++;
		}

		float t = m_AnimStepX * (float)m_rClip.w;

		while (t >= m_TexWidth)
		{
			t -= m_TexWidth;
			m_AnimStepY++;
			m_AnimStepX = 0;
		}

		m_lastTime = time;
	}

	m_rClip.x = m_AnimStepX * m_rClip.w;
	m_rClip.y = m_AnimStepY * m_rClip.h;

	//printf("PlayReturn: %i\n", ret);

	return ret;

}

int CKT::GFX::CGfxObject::PlayAnimation(int beginn, int end, int speed, int timesPlay)
{
	int ret = 0;

	if (m_AnimTimesToPlay < 0)
	{
		m_AnimTimesToPlay = timesPlay;
	}

	if (m_AnimTimesToPlay > 0)
	{
		ret = PlayAnimation(beginn, end, speed, false);
		if (ret == 0)
			m_AnimTimesToPlay--;
	}

	return ret;
}
