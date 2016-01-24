#include "Scrollbar.h"

using namespace CKT::GUI;

const int CKT::GUI::CScrollbar::STD_SCB_SIZE = -1;

CScrollbar::CScrollbar()
{
}


CScrollbar::~CScrollbar()
{
}

void CKT::GUI::CScrollbar::SetValueFocusEvents(ValueChanged vFunc, GotFocus gFunc, LostFocus lFunc, void * objForCallback)
{
	m_OnValueChanged = vFunc;
	m_OnGotFocus = gFunc;
	m_OnLostFocus = lFunc;
	m_ObjForCallback = objForCallback;
}

void CKT::GUI::CScrollbar::SetBtnClippingPoints(ScrollbarClip prev, ScrollbarClip next, ScrollbarClip track)
{
	m_btnPrev->SetBtnClippingPoints(prev.btnNotSel, prev.btnSel, prev.btnPress);
	m_btnNext->SetBtnClippingPoints(next.btnNotSel, next.btnSel, next.btnPress);
	m_btnTrack->SetBtnClippingPoints(track.btnNotSel, track.btnSel, track.btnPress);
}

int CScrollbar::Render()
{
	if (!m_IsVisible)
		return 0;

	GFX::GfxObject::Render();

	m_btnPrev->Render();
	m_btnNext->Render();
	m_btnTrack->Render();

	return 0;
}