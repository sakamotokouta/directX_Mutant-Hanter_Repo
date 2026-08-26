#include "main.h"
#include "renderer.h"
#include "drawModel.h"
#include "generalStoreBoardObj.h"
#include "collitionBox.h"
#include "manager.h"

void GeneralStoreBoardObj::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\DepthShadowMappingPS.cso");

	AddComponet<DrawModel>()->Init("asset\\model\\generalsotreboard.obj");

	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_ShadowFlg = true;

	m_Scene = Manager::GetScene();

	GameObject::Init();
}

void GeneralStoreBoardObj::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();


	GameObject::Uninit();
}

void GeneralStoreBoardObj::Update()
{
	GameObject::Update();
}

void GeneralStoreBoardObj::Draw()
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