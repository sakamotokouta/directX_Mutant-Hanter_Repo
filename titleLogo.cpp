#include "main.h"
#include "renderer.h"
#include "titleLogo.h"
#include "sprite.h"
#include "sprit2D.h"



void TitleLogo::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	AddComponet<Sprite>()->Init(0.0f, 300.0f, 800.0f, 500.0f, "asset/texture/titlelogo01.png");

	m_Sprite1 = new Sprit2D;
	char textuer[100] = "asset/texture/pushenterkeywaku02.png";
	m_Sprite1->Init(textuer);
	m_Sprite2 = new Sprit2D;
	char textuer1[100] = "asset/texture/pushenterkey.png";
	m_Sprite2->Init(textuer1);


	m_Sprite1Pos = D3DXVECTOR3(613.0f, 293.0f, 0.0f);
	m_Sprite1Scale = D3DXVECTOR3(800.0f, 400.0f, 0.0f);
	m_Sprite2Pos = D3DXVECTOR3(520.0f, 196.0f, 0.0f);
	m_Sprite2Scale = D3DXVECTOR3(1000.0f, 600.0f, 0.0f);

	GameObject::Init();
}

void TitleLogo::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_Sprite1->Uninit();

	GameObject::Uninit();
}

void TitleLogo::Update()
{

	GameObject::Update();
}

void TitleLogo::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();


	m_Sprite1->Draw(m_Sprite1Pos,m_Sprite1Scale,D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_clear);
	m_Sprite2->Draw(m_Sprite2Pos, m_Sprite2Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f);


	if (m_clear <= 0.2f)
	{
		m_PulsFlg = true;
		m_Minus = false;
	}

	if (m_clear >= 0.7f)
	{
		m_Minus = true;
		m_PulsFlg = false;
	}

	if (m_PulsFlg)
		m_clear += 0.01f;

	if (m_Minus)
		m_clear -= 0.01f;

	// 仮想関数なので強制的に呼び出す(基底クラスのメゾット呼び出し)
	GameObject::Draw();
}