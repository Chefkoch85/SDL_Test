#include "CollisionCircle.h"

#include "CollisionRect.h"

using namespace CKT::GAME;

CCollisionCircle::CCollisionCircle(GfxObject& parent, float radius = 0)
	:
	CCollisionObj(parent)
{
	m_Radius = radius;
	if (m_Radius > 0.0f)
		m_RadiusSet = true;
}


CCollisionCircle::~CCollisionCircle()
{
}

int CKT::GAME::CCollisionCircle::Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s)
{
	CCollisionObj::Init(ren, file, x, y, w, h, s);
	
	m_CenterX = m_Width / 2 + m_PosX;
	m_CenterY = m_Height / 2 + m_PosY;

	return 0;
}

int CKT::GAME::CCollisionCircle::Update(float time)
{
	m_PosX = (m_ParentObj.X() + m_CorrX) + m_OffsetX;
	m_PosY = (m_ParentObj.Y() + m_CorrY) + m_OffsetY;
	m_Width = (float)m_Width;
	m_Height = (float)m_Height;

	m_CenterX = m_Width / 2 + m_PosX;
	m_CenterY = m_Height / 2 + m_PosY;

	if (m_RadiusSet)
		m_Radius = ((m_Width / 2) + (m_Height / 2)) / 2;

	return 0;
}

bool CKT::GAME::CCollisionCircle::IsColliding(CCollisionRect * other)
{
	if (!other)
		return false;

	float centerX = other->Width() / 2 + other->X();
	float centerY = other->Height() / 2 + other->Y();
	float Distance = sqrtf(pow(m_CenterX - centerX, 2) + pow(m_CenterY - centerY, 2));

	float radius = ((other->Width() / 2) + (other->Height() / 2)) / 2;

	if (Distance >= m_Radius + radius)
		return false;

	return true;
}

bool CKT::GAME::CCollisionCircle::IsColliding(CCollisionCircle * other)
{
	if (!other)
		return false;

	float Distance = sqrtf(pow(m_CenterX - other->GetCenterX(), 2) + pow(m_CenterY - other->GetCenterY(), 2));
	
	if (Distance >= m_Radius + other->GetRadius())
		return false;

	return true;
}
