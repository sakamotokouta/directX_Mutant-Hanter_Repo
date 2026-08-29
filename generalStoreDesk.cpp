#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "generalStoreDesk.h"

void GeneralStoreDesk::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "DepthShadowMappingPS.cso");

	m_Model = new AnimationModel;
	m_Model->Load("asset\\model\\Heraklios By A. Dizon.fbx");
	m_Model->LoadAnimation("asset\\model\\Unarmed Idle 01.fbx", "Idle01");

	m_AnimationName = "Idle01";
	m_NextAnimationName = "Idle01";

	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	m_Position = D3DXVECTOR3(-5.0f, 0.0f, 2.0f);

	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_ShadowFlg = true;

	GameObject::Init();
}

void GeneralStoreDesk::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Model->Unload();
	delete m_Model;


	GameObject::Uninit();
}

void GeneralStoreDesk::Update()
{

	GameObject::Update();
}

void GeneralStoreDesk::Draw()
{
	Scene* scene = Manager::GetScene();


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
	m_Time += 0.3f;

	m_BlendRate += 0.03f;

	if (m_BlendRate > 1.0f)
		m_BlendRate = 1.0f;


	m_Model->Draw();

	GameObject::Draw();
}

