#include "Include\Timer.h"


using namespace CKT;

void CKT::CTimer::Start()
{
	m_IsStarted = true;
	m_IsStopped = false;
	m_IsPaused = false;

	m_PausedTicks = 0;
	m_StartTicks = SDL_GetTicks();
}

void CKT::CTimer::Stop()
{
	m_IsStarted = false;
	m_IsStopped = true;
	m_IsPaused = false;

	m_StartTicks = 0;
	m_PausedTicks = 0;
}

void CKT::CTimer::Pause()
{
	if (m_IsStarted && !m_IsPaused)
	{
		//Pause the timer
		m_IsPaused = true;

		//Calculate the paused ticks
		m_PausedTicks = SDL_GetTicks() - m_StartTicks;
		m_StartTicks = 0;
	}
}

void CKT::CTimer::Resume()
{
	if (m_IsStarted && m_IsPaused)
	{
		//Unpause the timer
		m_IsPaused = false;

		//Reset the starting ticks
		m_StartTicks = SDL_GetTicks() - m_PausedTicks;

		//Reset the paused ticks
		m_PausedTicks = 0;
	}
}

Uint32 CKT::CTimer::GetTicks()
{
	Uint32 curTicks = 0;

	if (m_IsStarted)
	{
		//If the timer is paused
		if (m_IsPaused)
		{
			//Return the number of ticks when the timer was paused
			curTicks = m_PausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			curTicks = SDL_GetTicks() - m_StartTicks;
		}
	}

	return curTicks;
}

CTimer::CTimer()
{
}


CTimer::~CTimer()
{
}
