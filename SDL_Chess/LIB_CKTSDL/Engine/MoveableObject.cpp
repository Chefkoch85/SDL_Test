#include "Include\MoveableObject.h"
#include "Include\CollisionRect.h"

using namespace CKT::GAME;

CMoveableObject::CMoveableObject()
{
}


CMoveableObject::~CMoveableObject()
{
	if (m_CollisionObj)
		delete m_CollisionObj;
}


void CMoveableObject::SetCollisionObj(CCollisionObj* colObj)
{
	m_CollisionObj = colObj;
}

CCollisionObj * CKT::GAME::CMoveableObject::GetCollisionObj()
{
		return m_CollisionObj;
}
