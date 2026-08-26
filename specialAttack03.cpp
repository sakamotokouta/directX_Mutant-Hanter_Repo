#include "main.h"
#include "renderer.h"
#include "drawModel.h"
#include "specialAttack03.h"
#include "player.h"
#include "manager.h"
#include "enemy.h"
#include "explosion.h"
#include "collitionBox.h"


void SpecialAttack03::Init()
{
	m_Scene = Manager::GetScene();

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\DepthShadowMappingPS.cso");

	AddComponet<DrawModel>()->Init("asset\\model\\special_attack.obj");

	m_Position = D3DXVECTOR3(-2.0f, 50.0f, 530.0f);

	m_Scale = D3DXVECTOR3(100.0f, 100.0f, 100.0f);

	m_Rotation = D3DXVECTOR3(0.0f, 1.6f, 0.0f);

	m_ShadowFlg = true;

	//collition
	m_Collision = m_Scene->AddGameObject<CollisionBox>(1);
	m_Collision->SetScale(D3DXVECTOR3(1.0f, 1.0f, 2.0f));


	GameObject::Init();
}

void SpecialAttack03::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Collision->SetDestroy();


	GameObject::Uninit();
}

void SpecialAttack03::Update()
{
	Enemy* enemy = m_Scene->GetGameObject<Enemy>();


	////posの変換
	//m_CollitionPos.x = m_CollitionMatrix._41; // 行列の右下の要素がX軸方向の移動成分
	//m_CollitionPos.y = m_CollitionMatrix._42; // 行列の右下の要素がY軸方向の移動成分
	//m_CollitionPos.z = m_CollitionMatrix._43; // 行列の右下の要素がZ軸方向の移動成分

	if (enemy != NULL)
	{

		if (m_Collision->SetOBB(this, enemy, 1.0f))
		{
			m_EnemyDamege = true;
			Explosion* effect = m_Scene->AddGameObject<Explosion>(1);
			effect->SetPosition(enemy->GetPosition());
			effect->SetColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
			enemy->SetEnmeyMuinusHp(0.05f);

		}
		else {
			m_EnemyDamege = false;
		}

		////敵との当たり判定
		//D3DXVECTOR3 position = enemy->GetPosition();
		//D3DXVECTOR3 scale1 = enemy->GetScale() * 388;

		//if (position.x - scale1.x - 0.5f < m_Position.x &&
		//	m_Position.x < position.x + scale1.x + 0.5f &&
		//	position.z - scale1.z - 0.5f < m_Position.z &&
		//	m_Position.z < position.z + scale1.z + 0.5f)
		//{
		//	if (m_Position.y < position.y + scale1.y * 2.0f - 0.5f)
		//	{
		//		m_EnemyDamege = true;
		//		Explosion* effect = scene->AddGameObject<Explosion>(1);
		//		effect->SetPosition(enemy->GetPosition());
		//		effect->SetColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
		//	}

		//}
		//else {
		//	m_EnemyDamege = false;
		//}


	}


	GameObject::Update();
}

void SpecialAttack03::Draw()
{

	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	D3DXMATRIX world, scale, rot, trans, htrans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_CollitionMatrix = scale * rot * trans * player->GetMatrix();
	Renderer::SetWorldMatrix(&m_CollitionMatrix);

	//collision
	m_Collision->SetPearent(m_CollitionMatrix);
	SetCollider(m_Collision->GetMatrix());


	GameObject::Draw();
}