#pragma once

#include "Common.h"

namespace CKT
{
	class CTimer
	{
	protected:
		bool m_IsStarted = false;
		bool m_IsStopped = true;
		bool m_IsPaused = false;

		Uint32 m_StartTicks = 0;
		Uint32 m_PausedTicks = 0;

	public:
		DllExport void Start();
		DllExport void Stop();
		DllExport void Pause();
		DllExport void Resume();

		DllExport bool IsStarted() { return m_IsStarted; }
		DllExport bool IsStopped() { return m_IsStopped; }
		DllExport bool IsPaused() { return m_IsPaused; }

		DllExport Uint32 GetTicks();

	public:
		DllExport CTimer();
		DllExport ~CTimer();
	};

}
