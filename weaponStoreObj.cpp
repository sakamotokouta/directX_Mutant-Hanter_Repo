#include "main.h"
#include "renderer.h"
#include "drawModel.h"
#include "weaponStoreObj.h"
#include "model.h"
#include "collitionBox.h"
#include "manager.h"

void WeaponStoreObj::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\DepthShadowMappingPS.cso");

	AddComponet<DrawModel>()->Init("asset\\model\\weaponstore01.obj");


	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_ShadowFlg = true;
	m_Scene = Manager::GetScene();


	//collition
	m_Collision = m_Scene->AddGameObject<CollisionBox>(1);
	m_Collision->SetScale(D3DXVECTOR3(1.5f, 3.0f, 1.5f));


	GameObject::Init();
}

void WeaponStoreObj::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Collision->SetDestroy();

	GameObject::Uninit();
}

void WeaponStoreObj::Update()
{

	GameObject::Update();
}

void WeaponStoreObj::Draw()
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

	//collision
	m_Collision->SetPearent(m_WorldMatrix);
	SetCollider(m_Collision->GetMatrix());

	GameObject::Draw();
}