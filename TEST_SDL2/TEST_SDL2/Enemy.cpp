#include "Enemy.h"

#include "Graphics.h"
#include "Collision.h"

int CKT::GAME::CEnemy::ID_COUNTER = 0;

CKT::GAME::CEnemy::CEnemy()
{
	ID_COUNTER++;
	m_ID = ID_COUNTER;
}


CKT::GAME::CEnemy::~CEnemy()
{
	for each (GfxObject* exp in m_Explosions)
	{
		delete exp;
	}
	m_Explosions.clear();
}

bool CKT::GAME::CEnemy::IsObstacle(CEnemy* other)
{
	if (this == other)
		return false;

	if (!other->Visibility())
		return false;

	if (other->Y() > m_PosY && other->X() >= m_PosX && other->X() + other->Width() <= m_PosX + m_Width)
		return true;

	return false;
}

void CKT::GAME::CEnemy::Shot()
{
}


int CKT::GAME::CEnemy::Update(float time)
{
	// switch enemy sprite
	switch (m_Life)
	{
	case 3:
		m_rClip.x = 0;
		break;

	case 2:
		m_rClip.x = m_AnimWidth;
		break;

	case 1:
		m_rClip.x = m_AnimWidth * 2;
		break;		
	}

	// check if explosion nesseccary and create it
	if (m_OldLife != m_Life)
	{
		GfxObject* exp = new GfxObject();

		switch (m_Life)
		{
		case 2:
			exp->Init(m_pRenderer, CKT::getResourcePath() + "IMG\\EXPLOSION\\exp_S4x4.png", m_PosX - 5, m_PosY - 0, 4, 4, 0.5f);
			break;

		case 1:
			exp->Init(m_pRenderer, CKT::getResourcePath() + "IMG\\EXPLOSION\\exp_S4x4.png", m_PosX + 26, m_PosY + 8, 4, 4, 0.5f);
			break;

		case 0:
			exp->Init(m_pRenderer, CKT::getResourcePath() + "IMG\\EXPLOSION\\exp_S4x4.png", m_PosX - 5, m_PosY - 8, 4, 4);
			break;
		}
		m_Explosions.insert(exp);
	}

	m_OldLife = m_Life;

	// update explosions and delete it, mark enemy as not activ if its life is 0
	for each (GfxObject* exp in m_Explosions)
	{
		if (exp->PlayAnimation(0, 15, 50, 1) == 0)
		{
			m_Explosions.erase(exp);

			if (m_Life <= 0)
			{
				m_IsActive = false;
			}

			break;
		}
	}

	// randomly shot at the player
	if (m_Explosions.size() == 0 && m_ShotLineFree)
	{
		//std::cout << "fire free: " << m_ID << std::endl;
	}

	// update collsion obj
	if (m_CollisionObj)
		m_CollisionObj->Update(time);

	return 0;
}

int CKT::GAME::CEnemy::Render()
{
	GfxObject::Render();

	for each (GfxObject* exp in m_Explosions)
	{
		exp->Render();
	}

	if (m_CollisionObj && DEBUG_ON)
		m_CollisionObj->Render();

	return 0;
}