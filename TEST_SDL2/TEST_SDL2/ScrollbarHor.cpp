#include "ScrollbarHor.h"


using namespace CKT::GUI;

CScrollbarHor::CScrollbarHor()
{
}


CScrollbarHor::~CScrollbarHor()
{
}

void CKT::GUI::CScrollbarHor::SetValue(int val)
{
	if (val < m_Min)
		m_Value = m_Min;
	else if (val > m_Max)
		m_Value = m_Max;
	else
		m_Value = val;

	m_btnTrack->Y() = (m_PixelRange / m_ValueRange) * m_Value + m_PosY + m_btnPrev->Height();
}

void CKT::GUI::CScrollbarHor::SetBounds(float x, float y, float h, float w)
{
	m_PosX = x;
	m_PosY = y;

	m_Width = w <= 0 ? m_Width : w;
	m_Height = h;

	m_btnPrev->SetPos(m_PosX, m_PosY);
	m_btnNext->SetPos(m_PosX, m_PosY + m_Height - m_btnNext->Height());
	m_btnTrack->X() = m_PosX;
}

int CKT::GUI::CScrollbarHor::Update(SDL_Event * e)
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
	else if (m_btnPrev->IsUp() || m_btnNext->IsUp())
		m_ScrollDelayTimer.Reset();

	// do the movement of the track
	if (m_btnPrev->IsPressed())
	{
		if (m_SnapToTicks)
		{
			if (m_btnPrev->IsDown())
				m_btnTrack->Y() -= m_PixelRange / m_ValueRange;
			else if (m_ScrollDelayTimer.IsFinish())
				m_btnTrack->Y() -= 0.05f * m_ScrollFactor;
		}
		else
			m_btnTrack->Y() -= 0.05f * m_ScrollFactor;
	}
	else if(m_btnNext->IsPressed())
	{
		if (m_SnapToTicks)
		{
			if (m_btnNext->IsDown())
				m_btnTrack->Y() += m_PixelRange / m_ValueRange;
			else if (m_ScrollDelayTimer.IsFinish())
				m_btnTrack->Y() += 0.05f * m_ScrollFactor;
		}
		else
			m_btnTrack->Y() += 0.05f * m_ScrollFactor;
	}
	else if (m_btnTrack->IsPressed())
	{
		if (e->type == SDL_MOUSEMOTION)
		{
			m_btnTrack->Y() = e->motion.y - m_btnTrack->Height() / 2;
		}
	}
	else if (this->IsSelected())
	{
		if (e->type == SDL_MOUSEWHEEL)
		{
			if (m_SnapToTicks)
			{
				m_btnTrack->Y() -= m_PixelRange / m_ValueRange * e->wheel.y;
			}
			else
				m_btnTrack->Y() -= e->wheel.y * m_ScrollFactor;
		}
		else if (e->type == SDL_KEYDOWN)
		{
			if (e->key.keysym.sym == SDLK_UP)
				m_btnTrack->Y() -= m_PixelRange / m_ValueRange;
			else if(e->key.keysym.sym == SDLK_DOWN)
				m_btnTrack->Y() += m_PixelRange / m_ValueRange;
		}
	}

	if (m_btnTrack->Y() < m_btnPrev->Y() + m_btnPrev->Height())
		m_btnTrack->Y() = m_btnPrev->Y() + m_btnPrev->Height();
	else if (m_btnTrack->Y() + m_btnTrack->Height() > m_btnNext->Y())
		m_btnTrack->Y() = m_btnNext->Y() - m_btnTrack->Height();

	if (!m_CalcDataOk)
	{
		m_PixelRange = m_Height - m_btnPrev->Height() - m_btnNext->Height() - m_btnTrack->Height();
		m_ValueRange = (float)(m_Max - m_Min);
		m_PixelStart = m_PosY + m_btnPrev->Height();
		m_CalcDataOk = true;
	}

	m_Value = (int)(((m_btnTrack->Y() - m_PixelStart) * m_ValueRange) / m_PixelRange);
	
	if (m_OnValueChanged && m_Value != m_OldValue)
	{
		m_EventArgs->Name() = m_GuiName;
		m_OnValueChanged(m_ObjForCallback, *this, *m_EventArgs);
	}

	m_OldValue = m_Value;

	//std::cout << "SCB-VAL: " << m_Value << std::endl;

	return 0;
}

int CKT::GUI::CScrollbarHor::Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float w, float h)
{
	GUI::CGUIBase::Init(ren, file, x, y, xTiles, yTiles);

	if (w < 0)
		w = m_Width;
	else
		m_Width = w;

	if (h < m_Height * 4)
	{
		m_Height = m_Height * 4;
		h = m_Height;
	}
	else
		m_Height = h;

	m_btnPrev = new CBtn();
	m_btnPrev->Init(ren, file, x, y, xTiles, yTiles);
	m_btnPrev->Width() = w;
	m_btnPrev->Height() = w;

	m_btnNext = new CBtn();
	m_btnNext->Init(ren, file, x, y + h - w, xTiles, yTiles);
	m_btnNext->Width() = w;
	m_btnNext->Height() = w;

	m_btnTrack = new CBtn();
	m_btnTrack->Init(ren, file, x, y + w, xTiles, yTiles);
	m_btnTrack->Width() = w;
	m_btnTrack->Height() = w;

	SetClippingPoints(0, 0, 0, 1);
	SetBtnClippingPoints({ { 2,0 },{ 2,1 },{ 2,2 } }, { { 3,0 },{ 3,1 },{ 3,2 } }, { { 1,0 },{ 1,1 },{ 1,2 } });

	Update(&SDL_Event());

	m_EventArgs = new CGuiEventArgs(m_ID);

	return 0;
}
