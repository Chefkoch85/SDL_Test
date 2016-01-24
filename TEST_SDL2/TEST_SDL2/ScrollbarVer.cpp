#include "ScrollbarVer.h"


using namespace CKT::GUI;

CScrollbarVer::CScrollbarVer()
{
}


CScrollbarVer::~CScrollbarVer()
{
}

void CKT::GUI::CScrollbarVer::SetValue(int val)
{
	if (val < m_Min)
		m_Value = m_Min;
	else if (val > m_Max)
		m_Value = m_Max;
	else
		m_Value = val;

	m_btnTrack->X() = (m_PixelRange / m_ValueRange) * m_Value + m_PosX + m_btnPrev->Width();
}

void CKT::GUI::CScrollbarVer::SetBounds(float x, float y, float w, float h)
{
	m_PosX = x;
	m_PosY = y;

	m_Width = w;
	m_Height = h <= 0 ? m_Height : h;

	m_btnPrev->SetPos(m_PosX, m_PosY);
	m_btnNext->SetPos(m_PosX + m_Width - m_btnNext->Width(), m_PosY);
	m_btnTrack->Y() = m_PosY;
}

int CKT::GUI::CScrollbarVer::Update(SDL_Event * e)
{
	if (!m_IsVisible || !m_IsEnabled)
		return 0;

	CFocusableObj::Update(e);
	
	// update the parts of the scrollbar
	m_btnPrev->Update(e);
	m_btnNext->Update(e);
	m_btnTrack->Update(e);
	
	if (m_btnPrev->IsDown() || m_btnNext->IsDown())
		m_ScrollDelayTimer.Start(m_ScrollDelay);
	else if(m_btnPrev->IsUp() || m_btnNext->IsUp())
		m_ScrollDelayTimer.Reset();

	// do the movement of the track
	if (m_btnPrev->IsPressed())
	{
		if (m_SnapToTicks)
		{
			if (m_btnPrev->IsDown())
				m_btnTrack->X() -= m_PixelRange / m_ValueRange;
			else if (m_ScrollDelayTimer.IsFinish())
				m_btnTrack->X() -= 0.05f * m_ScrollFactor;
		}
		else
			m_btnTrack->X() -= 0.05f * m_ScrollFactor;
	}
	else if (m_btnNext->IsPressed())
	{
		if (m_SnapToTicks)
		{
			if (m_btnNext->IsDown())
				m_btnTrack->X() += m_PixelRange / m_ValueRange;
			else if(m_ScrollDelayTimer.IsFinish())
				m_btnTrack->X() += 0.05f * m_ScrollFactor;
		}
		else
			m_btnTrack->X() += 0.05f * m_ScrollFactor;
	}
	else if (m_btnTrack->IsPressed())
	{
		if (e->type == SDL_MOUSEMOTION)
		{
			m_btnTrack->X() = e->motion.x - m_btnTrack->Width() / 2;
		}
	}
	else if (this->IsSelected())
	{
		if (e->type == SDL_MOUSEWHEEL)
		{
			if (m_SnapToTicks)
			{
				m_btnTrack->X() -= m_PixelRange / m_ValueRange * e->wheel.y;
			}
			else
				m_btnTrack->X() -= e->wheel.y * m_ScrollFactor;
		}
		else if (e->type == SDL_KEYDOWN)
		{
			if (e->key.keysym.sym == SDLK_LEFT)
				m_btnTrack->X() -= m_PixelRange / m_ValueRange;
			else if (e->key.keysym.sym == SDLK_RIGHT)
				m_btnTrack->X() += m_PixelRange / m_ValueRange;
		}
	}

	if (m_btnTrack->X() < m_btnPrev->X() + m_btnPrev->Width())
		m_btnTrack->X() = m_btnPrev->X() + m_btnPrev->Width();
	else if (m_btnTrack->X() + m_btnTrack->Width() > m_btnNext->X())
		m_btnTrack->X() = m_btnNext->X() - m_btnTrack->Width();

	if (!m_CalcDataOk)
	{
		m_PixelRange = m_Width - m_btnPrev->Width() - m_btnNext->Width() - m_btnTrack->Width();
		m_ValueRange = (float)(m_Max - m_Min);
		m_PixelStart = m_PosX + m_btnPrev->Width();
		m_CalcDataOk = true;
	}

	m_Value = (int)(((m_btnTrack->X() - m_PixelStart) * m_ValueRange) / m_PixelRange);

	if (m_OnValueChanged && m_Value != m_OldValue)
	{
		m_EventArgs->Name() = m_GuiName;
		m_OnValueChanged(m_ObjForCallback, *this, *m_EventArgs);
	}

	m_OldValue = m_Value;

	//std::cout << "SCB-VAL: " << m_Value << std::endl;

	return 0;
}

int CKT::GUI::CScrollbarVer::Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float w, float h)
{
	GUI::CGUIBase::Init(ren, file, x, y, xTiles, yTiles);

	if (h < 0)
		h = m_Height;
	else
		m_Height = h;

	if (w < m_Width * 4)
	{
		m_Width = m_Width * 4;
		w = m_Width;
	}
	else
		m_Width = w;

	m_btnPrev = new CBtn();
	m_btnPrev->Init(ren, file, x, y, xTiles, yTiles);
	m_btnPrev->Width() = h;
	m_btnPrev->Height() = h;

	m_btnNext = new CBtn();
	m_btnNext->Init(ren, file, x + w - h, y, xTiles, yTiles);
	m_btnNext->Width() = h;
	m_btnNext->Height() = h;

	m_btnTrack = new CBtn();
	m_btnTrack->Init(ren, file, x + h, y, xTiles, yTiles);
	m_btnTrack->Width() = h;
	m_btnTrack->Height() = h;

	SetClippingPoints(0, 0, 0, 1);
	SetBtnClippingPoints({ { 2,0 },{ 2,1 },{ 2,2 } }, { { 3,0 },{ 3,1 },{ 3,2 } }, { { 1,0 },{ 1,1 },{ 1,2 } });

	Update(&SDL_Event());

	m_EventArgs = new CGuiEventArgs(m_ID);

	return 0;
}