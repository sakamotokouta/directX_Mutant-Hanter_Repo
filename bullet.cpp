#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "drawModel.h"
#include "scene.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "sky.h"
#include "player.h"
#include "score.h"
#include "collitionBox.h"
#include "otomo.h"

void Bullet::Init()
{
	m_Scene = Manager::GetScene();
	m_Otomo = m_Scene->GetGameObject<Otomo>();

	m_Velocity = D3DXVECTOR3(m_Otomo->GetForward().x * 2.3f, 0.0f, m_Otomo->GetForward().z * 2.3f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexLightingPS.cso");

	AddComponet<DrawModel>()->Init("asset\\model\\torus.obj");

	//collition
	m_Collision = m_Scene->AddGameObject<CollisionBox>(1);
	m_Collision->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));


	GameObject::Init();
}

void Bullet::Uninit()
{

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Collision->SetDestroy();

	GameObject::Uninit();
}

void Bullet::Update()
{
	Scene* scene = Manager::GetScene();
	Enemy* enemy = scene->GetGameObject<Enemy>();

	m_Position += m_Velocity;

	//フィールド外または敵に当たった時に弾が消えるようにする
	if (m_Position.z > 100.0f || m_Position.z<-100.0f
		|| m_Position.x > 100.0f || m_Position.x < -100.0f||
		m_EnemyDamegeFlg)
	{
		// 消す予約をする
		SetDestroy();
	}

	// enemyとの衝突判定
	if (enemy != NULL)
	{


		//OBB
		if (m_Collision->SetOBB(this, enemy, 1.0f))
		{
			enemy->SetEnmeyMuinusHp(0.01f);
			Explosion* effect = scene->AddGameObject<Explosion>(1);
			effect->SetPosition(enemy->GetPosition());
			effect->SetColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
			m_EnemyDamegeFlg = true;
		}
		else
		{
			m_EnemyDamegeFlg = false;
		}

		////AABB
		//D3DXVECTOR3 position = enemy->GetPosition();
		//D3DXVECTOR3 scale1 = enemy->GetScale() * 100;

		//if (position.x - scale1.x - 0.5f < m_Position.x &&
		//	m_Position.x < position.x + scale1.x + 0.5f &&
		//	position.z - scale1.z - 0.5f < m_Position.z &&
		//	m_Position.z < m_Position.z + 0.5f)
		//{
		//	if (m_Position.y < position.y + scale1.y * 2.0f - 0.5f)
		//	{
		//		m_EnemyDamegeFlg = true;
		//		enemy->SetEnmeyMuinusHp(0.01f);
		//		Explosion* effect = scene->AddGameObject<Explosion>(1);
		//		effect->SetPosition(enemy->GetPosition());
		//		effect->SetColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
		//	}
		//}
		//else {
		//	m_EnemyDamegeFlg = false;
		//}
	}


}

void Bullet::Draw()
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

