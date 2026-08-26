#include "main.h"
#include "renderer.h"
#include "drawModel.h"
#include "animationModel.h"
#include "player.h"
#include "scene.h"
#include "manager.h"
#include "camera.h"
#include <random>
#include "input.h"
#include "fade.h"
#include "manager.h"
#include "result.h"
#include <string>
#include "ui01.h"
#include "otomo.h"
#include "bullet.h"
#include "enemy.h"


void Otomo::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "DepthShadowMappingPS.cso"); //pixelLightingRim


	m_Scene = Manager::GetScene();

	m_Fade = m_Scene->AddGameObject<Fade>(2);


	m_Model = new AnimationModel;
	m_Model->Load("asset\\model\\character (1).fbx");
	m_Model->LoadAnimation("asset\\model\\Happy Idle.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\Standing 1H Magic Attack 02 (1).fbx", "attack");
	m_Model->LoadAnimation("asset\\model\\Drunk Run Forward.fbx", "Run");


	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	m_Scale = D3DXVECTOR3(0.007f, 0.007f, 0.007f);


	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_Player = m_Scene->GetGameObject<Player>();

	m_EnemyHp = 50.0f;

	std::srand(time(NULL));

	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/dissolve.png",
		NULL,
		NULL,
		&m_DisolveTexture,
		NULL);
	assert(m_DisolveTexture);


	m_OtomoState = OTOMO_IDLE;

	m_ShadowFlg = true;

	GameObject::Init();
}

void Otomo::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Model->Unload();
	delete m_Model;

	m_DisolveTexture->Release();

	GameObject::Uninit();
}

void Otomo::Update()
{

	Player* player = m_Scene->GetGameObject<Player>();
	Enemy* enemy = m_Scene->GetGameObject<Enemy>();
	D3DXVECTOR3 m_Direction02 = m_Position - player->GetPosition();

	m_Direction02.y = 0.0f;
	D3DXVec3Normalize(&m_Direction02, &m_Direction02);

	m_Direction01 = player->GetPosition() - m_Position;
	m_Length01 = D3DXVec3Length(&m_Direction01);
	enemy->GetPosition();


	m_Rotation.y = atan2(m_Direction02.x, m_Direction02.z);

	bool flg = enemy->GetAttackFlg();


	if (m_Length01 > 2.0f)
		m_OtomoState = OTOMO_WALK;
	else
		m_OtomoState = OTOMO_IDLE;

	if (enemy != NULL)
	{
		if (enemy->GetEnemyState() == ENEMY_STATE_ATTACK || enemy->GetEnemyState() == ENEMY_STATE_REMOTEATTACK ||
			enemy->GetEnemyState() == ENEMY_STATE_JUMPATTACK)
			m_OtomoState = OTOMO_ATTACK;
	}

	if(enemy != NULL && enemy->GetEnemyState() == ENEMY_STATE_FOUND  && enemy->GetAttackFlg() == false)
		m_OtomoState = OTOMO_WALK;



	switch (m_OtomoState)
	{
	case OTOMO_IDLE:
		UpdateIdle();
		break;
	case OTOMO_WALK:
		UpdateWalk();
		break;
	case OTOMO_ATTACK:
		UpdateAttack();
		break;
	default:
		break;
	}





	GameObject::Update();
}

void Otomo::Draw()
{
	//視錘台カリング
	{
		Scene* scene = Manager::GetScene();
		Camera* camera = scene->GetGameObject<Camera>();

		if (!camera->CheckView(m_Position))
			return;
	}
	Scene* scene = Manager::GetScene();
	Player* playe = scene->GetGameObject<Player>();
	D3DXVECTOR3 p_pos = playe->GetPosition();
	D3DXVECTOR3 top = GetTop();


	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans, muki;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y + D3DX_PI, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);

	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);


	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendRate);
	m_Time += 0.8f;

	m_BlendRate += 0.03f;

	if (m_BlendRate > 1.0f)
		m_BlendRate = 1.0f;

	m_Model->Draw();

	GameObject::Draw();
}


void Otomo::UpdateIdle()
{
	if (m_NextAnimationName != "Idle")
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Idle";
		m_BlendRate = 0.0f;
	}
}

void Otomo::UpdateWalk()
{
	m_Position += m_Direction01 * 0.03f;

	if (m_NextAnimationName != "Run")
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Run";
		m_BlendRate = 0.0f;
	}
}


void Otomo::UpdateAttack()
{
	Enemy* enemy = m_Scene->GetGameObject<Enemy>();

	D3DXVECTOR3 direction = enemy->GetPosition() - m_Position;

	m_Direction02 = m_Position - enemy->GetPosition();
	m_Direction02.y = 0.0f;
	D3DXVec3Normalize(&m_Direction02, &m_Direction02);


	m_Rotation.y = atan2(m_Direction02.x, m_Direction02.z);


	if (m_NextAnimationName != "attack")
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "attack";
		m_BlendRate = 0.0f;
	}

	if (m_BulletCo == 60)
	{
		Bullet* o_bullet = m_Scene->AddGameObject<Bullet>(1);
		o_bullet->SetPosition(m_Position + D3DXVECTOR3(0.0f, 0.5f, 0.0f));
		o_bullet->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		o_bullet->SetScale(D3DXVECTOR3(0.8f, 0.8f, 0.8f));
		o_bullet->SetVelocity(direction);
		m_BulletCo = 0;
	}

	m_BulletCo++;

}



