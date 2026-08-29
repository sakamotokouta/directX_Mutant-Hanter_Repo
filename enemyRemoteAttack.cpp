#include "main.h"
#include "renderer.h"
#include "drawModel.h"
#include "player.h"
#include "manager.h"
#include "scene.h"
#include "animationModel.h"
#include "input.h" 
#include "enemyRemoteAttack.h"
#include "collitionBox.h"

void EnemyRemoteAttack::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexLightingPS.cso");

	AddComponet<DrawModel>()->Init("asset\\model\\cylinder.obj");

	m_Scale = D3DXVECTOR3(1.5f, 1.5f, 1.5f);

	m_Position = D3DXVECTOR3(1.0f, 0.0f, 1.0f);

	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Scene = Manager::GetScene();


	//collition
	m_Collision = m_Scene->AddGameObject<CollisionBox>(1);
	m_Collision->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));


	GameObject::Init();
}

void EnemyRemoteAttack::Uninit()
{

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Collision->SetDestroy();

	GameObject::Uninit();
}

void EnemyRemoteAttack::Update()
{

	Player* player = m_Scene->GetGameObject<Player>();

	m_Position.y -= 0.7f;

	//OBB
	if (m_Collision->SetOBB(this, player, 1.0f))
	{
		m_AttackFlg = true;
	}
	else
	{
		m_AttackFlg = false;
	}



	//AABB
	/*if (m_Position.x - m_Scale.x - 0.1f < player->GetPosition().x &&
		player->GetPosition().x < m_Position.x + m_Scale.x + 0.1f &&
		m_Position.z - m_Scale.z - 0.1f < player->GetPosition().z &&
		player->GetPosition().z < m_Position.z + m_Scale.z + 0.1f)
	{
		m_AttackFlg = true;
	}
	else
	{
		m_AttackFlg = false;
	}

	if (m_DestroyFlg == true)
	{
		SetDestroy();
	}*/

	
	GameObject::Update();
}

void EnemyRemoteAttack::Draw()
{


	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);

	m_WorldMatrix = scale * rot * trans;
	Renderer::SetWorldMatrix(&m_WorldMatrix);

	//collision
	m_Collision->SetPearent(m_WorldMatrix);
	SetCollider(m_Collision->GetMatrix());



	GameObject::Draw();
}