#include "Include\Collision.h"


using namespace CKT::GAME;

CCollisionObj::CCollisionObj(CGfxObject& parent)
	:
	m_ParentObj(parent)
{
}


CCollisionObj::~CCollisionObj()
{
	if (m_Tag)
		delete m_Tag;
}

int CKT::GAME::CCollisionObj::Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s)
{
	CGfxObject::Init(ren, file, x, y, w, h, s);

	m_CorrX = (m_ParentObj.Width() - w) / 2;
	m_CorrY = (m_ParentObj.Height() - h) / 2;

	m_OffsetX = m_PosX;
	m_OffsetY = m_PosY;

	m_PosX = m_PosX + m_ParentObj.X() + m_CorrX;
	m_PosY = m_PosY + m_ParentObj.Y() + m_CorrY;
	
	return 0;
}