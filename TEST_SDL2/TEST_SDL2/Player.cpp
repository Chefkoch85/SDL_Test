#include "Player.h"
#include "Collision.h"
#include "CollisionCircle.h"

void CKT::GAME::CPlayer::Fire()
{
	CShoot* ShootObj = new CShoot();
	ShootObj->Init(m_pRenderer, CKT::getResourcePath() + "IMG\\WEAPON\\Shoot_3.png", 0, 0, 3, 1);
	ShootObj->X() = m_PosX + ((m_Width - ShootObj->Width()) / 2);
	ShootObj->Y() = m_PosY;
	ShootObj->VelY() = -150.0f;
	ShootObj->Setup(0, 2, 50);
	ShootObj->Bounds().y = 50;

	CCollisionObj* CollisionObj = new CCollisionCircle(*ShootObj, ShootObj->Width() / 2);
	CollisionObj->Init(m_pRenderer, CKT::getResourcePath() + "IMG\\DEBUG\\circle_16.png", 0, 0, ShootObj->Width(), ShootObj->Height());
	ShootObj->SetCollisionObj(CollisionObj);

	m_Shoots.insert(ShootObj);

	//printf("Fired! Shoots: %i\n", m_Shoots.size());
}

CKT::GAME::CPlayer::CPlayer()
{
}


CKT::GAME::CPlayer::~CPlayer()
{
}


//int CKT::GAME::CPlayer::Init(PRENDERER ren, std::string file, float x, float y, int xTiles, int yTiles, float s)
//{
//	GFX::GfxObject::Init(ren, file, x, y, xTiles, yTiles, s);
//
//	return 0;
//}

void CKT::GAME::CPlayer::ResetPlayer()
{
	for each (CShoot* shot in m_Shoots)
	{
		delete shot;
	}

	m_Shoots.clear();

	m_PosX = 0.0f;
	m_PosY = 0.0f;
	m_VelX = 0.0f;
	m_VelY = 0.0f;

	m_HasShield = true;
}

void CKT::GAME::CPlayer::PlayerData(PlayerVars vars)
{
	m_Vars = vars;
}

int CKT::GAME::CPlayer::Update(float time)
{
	std::cout << "PLayer FTIS: " << time << std::endl;

	bool move = m_MoveLeft || m_MoveRight;
	static Uint32 lastTime = SDL_GetTicks();
	Uint32 curTime = SDL_GetTicks();
	static bool Fired = false;

	// firing
	if (m_Shoot)
	{
		if (!Fired && curTime > (lastTime + m_Vars.TIME_TO_SHOOT))
		{
			Fire();
			lastTime = curTime;
			Fired = true;
		}
	}
	else
	{
		Fired = false;
	}


	// update shoots
	for each (CShoot* item in m_Shoots)
	{
		item->Update(time);

		if (!item->IsActive())
		{
			m_Shoots.erase(item);
			delete item;
			break;
		}
	}


	// movement
	if (m_MoveLeft)
		m_VelX -= m_Vars.ACC_SPEED * time;
	else if (m_MoveRight)
		m_VelX += m_Vars.ACC_SPEED * time;
	

	// max speed
	if (m_VelX > m_Vars.MAX_SPEED)
		m_VelX = m_Vars.MAX_SPEED;

	if (m_VelX < -m_Vars.MAX_SPEED)
		m_VelX = -m_Vars.MAX_SPEED;


	int AnimStep = 2;
	// Player animation to the right
	if (m_VelX > m_Vars.ANIM_STEP_0 && m_VelX < m_Vars.ANIM_STEP_1)
	{
		AnimStep = 3;
	}
	else if (m_VelX > m_Vars.ANIM_STEP_0 && m_VelX <= m_Vars.ANIM_STEP_2)
	{
		AnimStep = 4;
	}
	// Player animation to the left
	else if (m_VelX < -m_Vars.ANIM_STEP_0 && m_VelX > -m_Vars.ANIM_STEP_1)
	{
		AnimStep = 1;
	}
	else if (m_VelX < -m_Vars.ANIM_STEP_0 && m_VelX >= -m_Vars.ANIM_STEP_2)
	{
		AnimStep = 0;
	}
	// Player animation center
	else
	{
		AnimStep = 2;
	}
	// set animation clipping rect
	m_rClip.x = AnimStep * m_rClip.w;


	// braking
	if (!move && m_VelX > 0)
	{
		m_VelX -= m_Vars.BRAKE_SPEED * time;
		if (m_VelX < 0)
			m_VelX = 0;
	}
	if (!move && m_VelX < 0)
	{
		m_VelX += m_Vars.BRAKE_SPEED * time;
		if (m_VelX > 0)
			m_VelX = 0;
	}


	// change player.x if the player is in the window
	if (m_PosX + m_VelX > 0 && (m_PosX + m_Width + m_VelX) < CKT::SCREEN.W)
		m_PosX += m_VelX;
	// else make the player bounce back from the wall
	else
		m_VelX = -m_VelX * m_Vars.BOUNCE_STRENGTH;

	if (m_CollisionObj)
		m_CollisionObj->Update(time);

	return 0;
}

int CKT::GAME::CPlayer::Render()
{
	for each (CShoot* item in m_Shoots)
	{
		item->Render();
	}
	
	GfxObject::Render();

	if (m_HasShield && m_CollisionObj || m_CollisionObj && DEBUG_ON)
		m_CollisionObj->Render();

	return 0;
}