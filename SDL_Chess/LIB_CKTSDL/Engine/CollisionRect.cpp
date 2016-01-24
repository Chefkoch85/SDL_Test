#include "Include\CollisionRect.h"

#include "Include\CollisionCircle.h"

#include <math.h>

using namespace CKT::GAME;

CKT::GAME::CCollisionRect::CCollisionRect(CGfxObject& parent)
	:
	CKT::GAME::CCollisionObj(parent)
{
}

CKT::GAME::CCollisionRect::~CCollisionRect()
{
}

int CKT::GAME::CCollisionRect::Update(float time)
{
	m_PosX = (m_ParentObj.X() + m_CorrX) + m_OffsetX;
	m_PosY = (m_ParentObj.Y() + m_CorrY) + m_OffsetY;
	m_Width = (float)m_Width;
	m_Height = (float)m_Height;
	return 0;
}

bool CKT::GAME::CCollisionRect::IsColliding(CCollisionRect * other)
{
	if (!other)
		return false;

	if (m_PosX + m_Width < other->X() || m_PosX > other->X() + other->Width() ||
		m_PosY + m_Height < other->Y() || m_PosY > other->Y() + other->Width())
	{
		return false;
	}

	return true;
}

bool CKT::GAME::CCollisionRect::IsColliding(CCollisionCircle * other)
{
	if (!other)
		return false;

	float centerX = m_Width / 2 + m_PosX;
	float centerY = m_Height / 2 + m_PosY;
	float Distance = sqrtf(pow(centerX - other->GetCenterX(), 2) + pow(centerY - other->GetCenterY(), 2));

	float radius = ((m_Width / 2) + (m_Height / 2)) / 2;

	if (Distance >= other->GetRadius() + radius)
		return false;

	return true;
}
