#include "main.h"
#include "renderer.h"
#include "sky.h"
#include "spritefield.h"

void Sky::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\DepthShadowMappingPS.cso");

	m_pos.x = -20.0;
	m_pos.y = 0.001f;
	m_pos.z = 20.0f;

	m_scale.x = 50.0f;
	m_scale.z = -50.0f;

	AddComponet<SpriteField>()->Init(m_pos.x, m_scale.x, m_pos.y, m_scale.y, m_pos.z, m_scale.z, 0.0f, 1.0f, 0.0f, "asset/texture/tiletextuer.jpeg");

	m_ShadowFlg = true;

	GameObject::Init();
}

void Sky::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void Sky::Update()
{

	GameObject::Update();
}

void Sky::Draw()
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
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	GameObject::Draw();
}