#include "main.h"
#include "renderer.h"
#include "loadingLogo.h"
#include "sprite.h"
#include "village.h"
#include "sprit2D.h"
#include "input.h"

void LoadingLogo::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	//ゲームでのロード画面
	m_OperationInfo = new Sprit2D;
	m_OperationInfo->Init("asset/texture/sousainfo.png");
	AddComponet<Sprite>()->Init(0.0f, 0.0f, 100, 100, "asset/texture/loading.png");


	m_OperationInfoPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_OperationInfoScale = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);



	GameObject::Init();
}

void LoadingLogo::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_OperationInfo->Uninit();


	GameObject::Uninit();
}

void LoadingLogo::Update()
{

	m_Position = D3DXVECTOR3(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 100.0f, 0.0f);
	m_Rotation.z += 0.1f;


	GameObject::Update();
}

void LoadingLogo::Draw()
{

	m_OperationInfo->Draw(m_OperationInfoPos, m_OperationInfoScale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);


	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans, offset;
	D3DXMatrixTranslation(&offset, -50.0f, -50.0f, 0.0f);
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = offset * scale * rot * trans;
	Renderer::SetWorldMatrix(&world);


	// 仮想関数なので強制的に呼び出す(基底クラスのメゾット呼び出し)
	GameObject::Draw();
}