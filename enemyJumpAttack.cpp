#include "main.h"
#include "renderer.h"
#include "drawModel.h"
#include "enemyJumpAttack.h"
#include "collitionBox.h"
#include "scene.h"
#include "manager.h"

void EnemyJumpAttack::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\DepthShadowMappingPS.cso");

	AddComponet<DrawModel>()->Init("asset\\model\\enemy_effect.obj");

	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_Scale = D3DXVECTOR3(0.7f, 0.7f, 0.7f);
	m_ShadowFlg = true;

	m_Scene = Manager::GetScene();

	//collition
	m_Collision = m_Scene->AddGameObject<CollisionBox>(1);
	m_Collision->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));


	GameObject::Init();
}

void EnemyJumpAttack::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//m_Collision->Unload();

	GameObject::Uninit();
}

void EnemyJumpAttack::Update()
{
	//collision
	m_Collision->SetPearent(m_WorldMatrix);
	SetCollider(m_Collision->GetMatrix());

	GameObject::Update();
}

void EnemyJumpAttack::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_WorldMatrix = scale * rot * trans;
	Renderer::SetWorldMatrix(&m_WorldMatrix);

	GameObject::Draw();
}