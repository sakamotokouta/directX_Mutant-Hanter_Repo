#include "main.h"
#include "renderer.h"
#include "model.h"
#include "treeObj.h"
#include "model.h"

Model* TreeObj::m_Model{};

void TreeObj::Load()
{
	m_Model = new Model;

	m_Model->Load("asset\\model\\tree04.obj");

}
void TreeObj::Unload()
{
	m_Model->Unload();
	delete m_Model;

}


void TreeObj::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\DepthShadowMappingPS.cso");
	

	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_ShadowFlg = true;

	GameObject::Init();
}

void TreeObj::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();


	GameObject::Uninit();
}

void TreeObj::Update()
{

	GameObject::Update();
}

void TreeObj::Draw()
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

	m_Model->Draw();

	GameObject::Draw();
}