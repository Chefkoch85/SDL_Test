#include "Shoot.h"

using namespace CKT::GAME;

void CKT::GAME::CShoot::Setup(int begin, int end, int speed)
{
	m_AnimFirst = begin;
	m_AnimLast = end;
	m_AnimSpeed = speed;
}

CShoot::CShoot()
{ 
	m_IsActive = true;
}


CShoot::~CShoot()
{

}

int CKT::GAME::CShoot::Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s)
{
	GfxObject::Init(ren, file, x, y, xTiles, yTiles, s);
	
	return 0;
}

int CKT::GAME::CShoot::Update(float time)
{
	PlayAnimation(m_AnimFirst, m_AnimLast, m_AnimSpeed);
	m_PosY += m_VelY * time;

	if(m_CollisionObj)
		m_CollisionObj->Update(time);
	
	if (m_PosY < m_Bounds.y)
	{
		m_IsActive = false;
	}

	return 0;
}

int CKT::GAME::CShoot::Render()
{
	GfxObject::Render();

	if(m_CollisionObj && DEBUG_ON)
		m_CollisionObj->Render();

	return 0;
}
