#include "main.h"
#include "renderer.h"
#include "drawModel.h"
#include "player.h"
#include "manager.h"
#include "scene.h"
#include "animationModel.h"
#include "input.h" 
#include "enemy.h"
#include "weaponDataLoad.h"
#include "explosion.h"
#include "enemyWeapon.h"
#include "enemy.h"
#include "collitionBox.h"
#include "audio.h"


void EnemyWeapon::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\DepthShadowMappingPS.cso");

	m_Scene = Manager::GetScene();

	m_Model = new Model;
	m_Model->Load("asset\\model\\box.obj");

	m_AttackSE = AddComponet<Audio>();
	m_AttackSE->Load("asset\\audio\\EnemyCloseRangeAttack.wav");
	m_AttackSE->Volume(0.6f);


	m_Scale = D3DXVECTOR3(15.0f, 40.0f, 15.0f);

	m_Position = D3DXVECTOR3(0.0f, -30.0f, 0.0f);


	m_ShadowFlg = true;

	flg = false;


	//collition
	m_CollisionBox = m_Scene->AddGameObject<CollisionBox>(1);
	m_CollisionBox->SetScale(D3DXVECTOR3(1.0f, 3.0f, 1.0f));



	GameObject::Init();
}

void EnemyWeapon::Uninit()
{

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Model->Unload();
	delete m_Model;

	m_CollisionBox->SetDestroy();


	GameObject::Uninit();
}

void EnemyWeapon::Update()
{
	Player* player = m_Scene->GetGameObject<Player>();
	Enemy* enemy = m_Scene->GetGameObject<Enemy>();




	////posの変換
	//m_CollitionPos.x = m_CollitionMatrix._41; // 行列の右下の要素がX軸方向の移動成分
	//m_CollitionPos.y = m_CollitionMatrix._42; // 行列の右下の要素がY軸方向の移動成分
	//m_CollitionPos.z = m_CollitionMatrix._43; // 行列の右下の要素がZ軸方向の移動成分


	if (enemy != NULL)
	{
		AnimationModel* anim = enemy->GetAnim();
		BONE* bone1 = anim->GetBoneName("mixamorig:RightHand");
		m_Parent = anim->ConvertMatrix(bone1->WorldMatrix);

		//OBB
		if (m_CollisionBox->SetOBB(this, player, 1.0f) && enemy->GetEnemyHitFlg())
		{
				player->SetDamegeFlg(true);

				m_AttackSE->Play();

				enemy->SetEnemyHitFlg(false);

		}else
			player->SetDamegeFlg(false);



		////プレイヤーとの当たり判定
		//D3DXVECTOR3 position = player->GetPosition();
		//D3DXVECTOR3 scale1 = player->GetScale() * 200;

		//if (position.x - scale1.x - 0.5f < m_CollitionPos.x &&
		//	m_CollitionPos.x < position.x + scale1.x + 0.5f &&
		//	position.z - scale1.z - 0.5f < m_CollitionPos.z &&
		//	m_CollitionPos.z < position.z + scale1.z + 0.5f)
		//{
		//	if (m_CollitionPos.y < position.y + scale1.y * 2.0f - 0.5f)
		//	{
		//		if (enemy->GetEnemyHitFlg())
		//			player->SetDamegeFlg(true);
		//		else
		//			player->SetDamegeFlg(false);
		//	}

		//}
		//else {
		//	player->SetDamegeFlg(false);
		//}

	}


	GameObject::Update();
}

void EnemyWeapon::Draw()
{

	Scene* scene = Manager::GetScene();
	Enemy* enemy = scene->GetGameObject<Enemy>();

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	D3DXMATRIX world, scale, rot, trans, htrans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);

	if(enemy != NULL)
		m_WorldMatrix = scale * rot * trans * m_Parent * enemy->GetMatrix();


	Renderer::SetWorldMatrix(&m_WorldMatrix);

	//collision
	m_CollisionBox->SetPearent(m_WorldMatrix);
	SetCollider(m_CollisionBox->GetMatrix());



	//m_Model->Draw();


	GameObject::Draw();
}
