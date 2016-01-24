#include "Include\Clock.h"


using namespace CKT::GUI;

CClock::CClock()
{
}


CClock::~CClock()
{
}

int CKT::GUI::CClock::Init(PRENDERER ren, std::string fileBack, std::string filePointer, float x, float y, float s)
{
	GFX::CGfxObject::Init(ren, fileBack, x, y, s);

	m_Pointer = new GFX::CGfxObject();
	m_Pointer->Init(ren, filePointer, x, y, s);
	m_Pointer->UseRotate() = true;

	m_Pointer2 = new GFX::CGfxObject();
	m_Pointer2->Init(ren, filePointer, x, y, s);
	m_Pointer2->UseRotate() = true;

	return 0;
}

int CKT::GUI::CClock::Update(float time)
{
	float xPointer = (m_Width - m_Pointer->Width()) / 2 + m_PosX;
	float yPointer = m_PosY + 10;
	m_Pointer->SetPos(xPointer, yPointer);
	m_Pointer->Center() = { (int)(m_Pointer->Width() / 2), (int)m_Pointer->Height() - 10 };

	xPointer = (m_Width - m_Pointer2->Width()) / 2 + m_PosX;
	yPointer = m_PosY + 10;
	m_Pointer2->SetPos(xPointer, yPointer);
	m_Pointer2->Center() = { (int)(m_Pointer2->Width() / 2 - 0.5f), (int)m_Pointer2->Height() - 10 };

	m_SumTime += time;
	
	if (m_SumTime >= m_RefreshTime)
	{
		m_SumTime = 0.0f;
		//m_Angle += 360.0 / 60 / 100;	// "360 / 60" = degrees per second; degrees per second / 100 = degrees per 10ms
		m_Pointer->Angle() += 360.0 / 60 * (m_RefreshTime);

		if (m_Pointer->Angle() >= 360.0)
		{
			m_Pointer->Angle() = 0.0;
			m_Angle += 360 / 60;

			if (m_Angle >= 360.0)
				m_Angle = 0.0;

			m_Pointer2->Angle() = m_Angle;
		}
		

	}

	//std::cout << "Clock Angle: " << m_Angle << std::endl;

	return 0;
}

int CKT::GUI::CClock::Render()
{
	GFX::CGfxObject::Render();

	m_Pointer->Render();
	m_Pointer2->Render();

	return 0;
}
