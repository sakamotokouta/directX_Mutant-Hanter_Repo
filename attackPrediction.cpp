#include "main.h"
#include "renderer.h"
#include "drawModel.h"
#include "player.h"
#include "manager.h"
#include "scene.h"
#include "animationModel.h"
#include "input.h" 
#include "attackPrediction.h"

void AttackPrediction::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	m_Model = new Model;
	m_Model->Load("asset\\model\\point.obj");
	m_Scale = D3DXVECTOR3(1.5f, 1.5f, 1.5f);


	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	GameObject::Init();
}

void AttackPrediction::Uninit()
{

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Model->Unload();
	delete m_Model;

	GameObject::Uninit();
}

void AttackPrediction::Update()
{

	GameObject::Update();
}

void AttackPrediction::Draw()
{

	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
	
	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans, htrans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);

	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();

	GameObject::Draw();
}