#include "Collision.h"


using namespace CKT::GAME;

CCollisionObj::CCollisionObj(GfxObject& parent)
	:
	m_ParentObj(parent)
{
}


CCollisionObj::~CCollisionObj()
{
}

int CKT::GAME::CCollisionObj::Init(PRENDERER ren, std::string file, float x, float y, float w, float h, float s)
{
	GfxObject::Init(ren, file, x, y, w, h, s);

	m_CorrX = (m_ParentObj.Width() - w) / 2;
	m_CorrY = (m_ParentObj.Height() - h) / 2;

	m_OffsetX = m_PosX;
	m_OffsetY = m_PosY;

	m_PosX = m_PosX + m_ParentObj.X() + m_CorrX;
	m_PosY = m_PosY + m_ParentObj.Y() + m_CorrY;
	
	return 0;
}
