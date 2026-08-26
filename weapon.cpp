#include "main.h"
#include "renderer.h"
#include "drawModel.h"
#include "weapon.h"
#include "player.h"
#include "manager.h"
#include "scene.h"
#include "animationModel.h"
#include "input.h" 
#include "enemy.h"
#include "weaponDataLoad.h"
#include "explosion.h"
#include "ui01.h"
#include "collitionBox.h"
#include "model.h"
#include "trail.h"

ID3D11Buffer* SwordTopVertex::m_VertexBuffer{};
int Weapon::m_WeaponCount{};


void Weapon::Init()
{
	m_Scene = Manager::GetScene();

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\DepthShadowMappingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\DepthShadowMappingPS.cso");

	m_WeaponCount = WeaponDataLoad::GetWeaponNumber();

	//武器情報読み込み
	WeaponDataLoad::DataLoad();


	//m_Weapondataにデータを読み込む
	for (int i = 0; i < WEAPON_NUM; i++)
	{
		m_Weapondata[i] = WeaponDataLoad::GetWeaponDataBaseIndex(i);
	}



	//武器データ読み込み
	//m_WeaponData = new WeaponDataLoad;
	//m_WeaponData->DataLoad();
	m_WeaponName = m_Weapondata[m_WeaponCount]->GetWeaponModelName();

	m_Model = new Model;
	m_Model->Load(m_WeaponName);

	m_SwordTopVertex = m_Scene->AddGameObject<SwordTopVertex>(1);

	m_Trail = m_Scene->AddGameObject<Trail>(1);

	m_WeaponChangeFlg = false;

	//collition
	m_Collision = m_Scene->AddGameObject<CollisionBox>(1);
	m_Collision->SetScale(D3DXVECTOR3(1.0f, 3.0f, 1.0f));

	m_Collision->SetPosition(D3DXVECTOR3(-1.0f, 4.0f, 0.0f));


	GameObject::Init();
}

void Weapon::Uninit()
{

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//m_Collision->SetDestroy();

	m_Model->Unload();
	delete m_Model;

	//m_Trail->Destroy();

	GameObject::Uninit();
}

void Weapon::Update()
{
	Player* player = m_Scene->GetGameObject<Player>();
	Enemy* enemy = m_Scene->GetGameObject<Enemy>();
	Ui01* ui = m_Scene->GetGameObject<Ui01>();


	//プレイヤーのモデルを取得
	AnimationModel* anim = player->GetAnim();
	//上で取得したモデルのボーンを取得する
	//腰のボーン取得
	BONE* Hips = anim->GetBoneName("mixamorig:Hips");
	//右手のボーン取得
	BONE* RightHand = anim->GetBoneName("mixamorig:RightHand");


	if (enemy != NULL)
	{

		//OBB
		if (m_Collision->SetOBB(this, enemy, 3.0f))
		{
			//プレイヤーが攻撃モーションの時に攻撃が通じるようにする処理
			if (player->GetPlayerState() == PLAYER_STATE_ATTACK1 ||
				player->GetPlayerState() == PLAYER_STATE_ATTACK2 ||
				player->GetPlayerState() == PLAYER_STATE_ATTACK3)
			{
				m_EnemyDamege = true;
			}
			else
			{
				m_EnemyDamege = false;
			}
			//エフェクトを付ける際に特定のフレーム数の時だけエフェクトを付けたい
			if (player->GetPlayerAttackHit1() ||
				player->GetPlayerAttackHit2() ||
				player->GetPlayerAttackHit3())
			{

				enemy->SetEnmeyMuinusHp(0.8f);

				if (m_EffectFlg == false)
				{
					Explosion* effect = m_Scene->AddGameObject<Explosion>(1);
					effect->SetPosition(enemy->GetPosition());
					effect->SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
					effect->SetColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
					m_EffectFlg = true;
				}


				ui->SetSpescalAttackScalePulsu(30.0f);

			}
			else
			{
				m_EffectFlg = false;
			}

		}
		else
		{
			m_EnemyDamege = false;
			m_EffectFlg = false;
		}

		//AABB
		////敵との当たり判定
		//D3DXVECTOR3 position = enemy->GetPosition();
		//D3DXVECTOR3 scale1 = enemy->GetScale() * 100;

		//if (position.x - scale1.x - 0.5f < m_CollitionPos.x &&
		//	m_CollitionPos.x < position.x + scale1.x + 0.5f &&
		//	position.z - scale1.z - 0.5f < m_CollitionPos.z &&
		//	m_CollitionPos.z < position.z + scale1.z + 0.5f)
		//{
		//	if (m_CollitionPos.y < position.y + scale1.y * 2.0f - 0.5f)
		//	{
		//		if (player->GetPlayerState() == PLAYER_STATE_ATTACK1 ||
		//			player->GetPlayerState() == PLAYER_STATE_ATTACK2 ||
		//			player->GetPlayerState() == PLAYER_STATE_ATTACK3 ||
		//			!player->GetPlayerState() == PLAYER_STATE_SCARED)
		//		{
		//			m_EnemyDamege = true;
		//			Explosion* effect = scene->AddGameObject<Explosion>(1);
		//			effect->SetPosition(enemy->GetPosition());
		//			effect->SetColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f));
		//			ui->SetSpescalAttackScalePulsu(5.0f);

		//		}
		//	}

		//}
		//else {
		//	m_EnemyDamege = false;
		//}


	}

	m_AttackCo++;

	if (player->GetSetUpFlg())
	{
		//剣を取り出しているときの位置、スケール、回転
		m_Position = WeaponDataLoad::GetWeaponDataBaseIndex(WeaponDataLoad::GetWeaponNumber())->GetWeaponSetUpPosition();
		m_Scale = WeaponDataLoad::GetWeaponDataBaseIndex(WeaponDataLoad::GetWeaponNumber())->GetWeaponSetUpScale();
		m_Rotation = WeaponDataLoad::GetWeaponDataBaseIndex(WeaponDataLoad::GetWeaponNumber())->GetWeaponSetUpRotation();

		//プレイヤーのモデルの右手のボーンのマトリックスを取得している
		m_Parent = anim->ConvertMatrix(RightHand->WorldMatrix);
	}
	else
	{
		//剣をしまっているときの位置、スケール、回転
		m_Position = WeaponDataLoad::GetWeaponDataBaseIndex(WeaponDataLoad::GetWeaponNumber())->GetWeaponMountPosition();
		m_Scale = WeaponDataLoad::GetWeaponDataBaseIndex(WeaponDataLoad::GetWeaponNumber())->GetWeaponMountScale();
		m_Rotation = WeaponDataLoad::GetWeaponDataBaseIndex(WeaponDataLoad::GetWeaponNumber())->GetWeaponMountRotation();

		//プレイヤーのモデルの腰のボーンのマトリックスを取得している
		m_Parent = anim->ConvertMatrix(Hips->WorldMatrix);
	}


	//剣を降っているときだけにトレイルがつくようにする処理
	if (player->GetPlayerState() == PLAYER_STATE_ATTACK1 ||
		player->GetPlayerState() == PLAYER_STATE_ATTACK2 ||
		player->GetPlayerState() == PLAYER_STATE_ATTACK3)
	{
		m_TrailFlg = true;
	}
	else
		m_TrailFlg = false;

	//下の頂点の取得
	m_BottomVertex = MatrixPosition(m_WorldMatrix);


	m_Trail->SetTrail(m_SwordTopVertex->GetTopVertexPostion(), GetBottomVertexPostion(), m_TrailFlg);


	GameObject::Update();
}

void Weapon::Draw()
{
	Player* player = m_Scene->GetGameObject<Player>();

	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	D3DXMATRIX scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);

	//剣のマトリックスに取得したプレイヤーのモデルのボーンと
	//プレイヤーのマトリックスを掛けることにより剣に追従する
	m_WorldMatrix = scale * rot * trans * m_Parent * player->GetMatrix();

	Renderer::SetWorldMatrix(&m_WorldMatrix);

	//collision
	m_Collision->SetPearent(m_WorldMatrix);
	SetCollider(m_Collision->GetMatrix());


	m_Model->Draw();

	GameObject::Draw();
}

void SwordTopVertex::Init()
{
	m_Scene = Manager::GetScene();
	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	WeaponDataLoad::DataLoad();
	m_Position = WeaponDataLoad::GetWeaponDataBaseIndex(WeaponDataLoad::GetWeaponNumber())->GetTrailPositon();
}
void SwordTopVertex::Load()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);	//左奥
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(1.0f, 0.0f, 1.0f);	//右奥
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(1.0f, 0.0f, -1.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファ設定
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void SwordTopVertex::Unload()
{
	m_VertexBuffer->Release();
	WeaponDataLoad::DataUnLoad();
}

void SwordTopVertex::Uninit()
{
}

void SwordTopVertex::Update()
{

	Weapon* weapon = m_Scene->GetGameObject<Weapon>();


	m_Parent = weapon->GetMatrix();
	m_TopVertex = MatrixPosition(m_WorldMatrix);
}

void SwordTopVertex::Draw()
{
	//マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_WorldMatrix = scale * rot * trans * m_Parent;
	Renderer::SetWorldMatrix(&m_WorldMatrix);



	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
}


void Weapon::SetWeapon(int co) {
	m_WeaponCount = co;
	m_Model->Load(m_Weapondata[m_WeaponCount]->GetWeaponModelName());
	m_WeaponChangeFlg = true;
	WeaponDataLoad::SetWeaponNumber(m_WeaponCount);
}
