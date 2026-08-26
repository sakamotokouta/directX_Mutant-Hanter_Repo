#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "drawModel.h"
#include "titleDome.h"
#include "titleCamera.h"

void TitleDome::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	m_Model = new Model;
	m_Model->Load("asset\\model\\skydoom002.obj");

	GameObject::Init();

}

void TitleDome::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Model->Unload();
	delete m_Model;

	GameObject::Uninit();

}

void TitleDome::Update()
{

	Scene* scene = Manager::GetScene();
	TitleCamera* camera = scene->GetGameObject<TitleCamera>();


	m_Position = camera->GetPosition();

	GameObject::Update();

}

void TitleDome::Draw()
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