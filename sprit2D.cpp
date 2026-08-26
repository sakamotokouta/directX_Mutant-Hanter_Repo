#include "main.h"
#include "renderer.h"
#include "sprite.h"
#include "sprit2D.h"

VERTEX_3D vertex[4];

void Sprit2D::Init(const char* spritname)
{

	//VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;   // 変更
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;   // 変更

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		spritname,
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	//AddComponet<Sprite>()->Init(50.0f, 50.0f, 200.0f, 200.0f, "asset/texture/score.png");

	//座標
	m_Position = (D3DXVECTOR3(-100.0f, -120.0f, 0.0f));

	//サイズ
	m_Width = 800.0f;
	m_Height = 400.0f;

	GameObject::Init();
}

void Sprit2D::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void Sprit2D::Update()
{
}

void Sprit2D::Draw(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rotation,float clere)
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX world,rot;
	Renderer::SetWorldViewProjection2D();

	// 仮想関数なので強制的に呼び出す(基底クラスのメゾット呼び出し)
	//GameObject::Draw();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, clere);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// 画像の回転角度（ラジアン）を設定
	float angle = rotation.x;

	// 画像の中心座標
	float centerX = size.x;
	float centerY = size.y*2.01;

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	int count = m_Count;

	// 頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex01 = (VERTEX_3D*)msr.pData;


	for (int i = 0; i < 3; i++)
	{
		vertex01[0].Position = D3DXVECTOR3(pos.x, pos.y, 0.0f);
		vertex01[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex01[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, clere);
		vertex01[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex01[1].Position = D3DXVECTOR3(pos.x + size.x, pos.y, 0.0f);
		vertex01[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex01[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, clere);
		vertex01[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		vertex01[2].Position = D3DXVECTOR3(pos.x, pos.y + size.y, 0.0f);
		vertex01[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex01[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, clere);
		vertex01[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		vertex01[3].Position = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);
		vertex01[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex01[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, clere);
		vertex01[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点座標を回転
		for (int j = 0; j < 4; ++j)
		{
			float x = vertex01[j].Position.x - centerX;
			float y = vertex01[j].Position.y - centerY;

			vertex01[j].Position.x = x * cos(angle) - y * sin(angle) + centerX;
			vertex01[j].Position.y = x * sin(angle) + y * cos(angle) + centerY;
		}


	
		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

		// ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}


}