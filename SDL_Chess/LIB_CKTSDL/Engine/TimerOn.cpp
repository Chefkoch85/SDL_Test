#include "Include\TimerOn.h"

using namespace CKT;

void CKT::CTimerOn::Start(int ticks)
{
	if (ticks >= 0)
		m_TicksToFinish = ticks;
	
	CTimer::Start();
}

void CKT::CTimerOn::Reset()
{
	CTimer::Stop();
	m_IsFinishedOnce = false;
}

bool CKT::CTimerOn::IsFinish()
{
	if (CTimer::GetTicks() >= m_TicksToFinish)
	{
		CTimer::Pause();
		return true;
	}

	return false;
}

bool CKT::CTimerOn::IsFinishOnce()
{
	if (!m_IsFinishedOnce && CTimer::GetTicks() >= m_TicksToFinish)
	{
		m_IsFinishedOnce = true;
		CTimer::Pause();
		return true;
	}

	return false;
}

CTimerOn::CTimerOn()
{
}


CTimerOn::~CTimerOn()
{
}
