#include "main.h"
#include "renderer.h"
#include "enemy.h"
#include "animationModel.h"
#include "player.h"
#include "scene.h"
#include "manager.h"
#include "camera.h"
#include "input.h"
#include "fade.h"
#include "manager.h"
#include "result.h"
#include "ui01.h"
#include "attackPrediction.h"
#include "enemyRemoteAttack.h"
#include "weapon.h"
#include "meshField.h"
#include "audio.h"
#include "component.h"
#include "enemyJumpAttack.h"
#include "specialAttack01.h"
#include "specialAttack02.h"
#include "specialAttack03.h"
#include "explosion.h"
#include "village.h"
#include "bullet.h"
#include "collitionBox.h"

#include <string>
#include <random>


float Enemy::m_EnemyHp{};


bool g_Flg001 = false;

float flam = 60;


void Enemy::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "pixelLightingRimVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "pixelLightingRimPS.cso");

	m_Scene = Manager::GetScene();

	m_Fade = m_Scene->AddGameObject<Fade>(2);


	m_EnemyModel[0] = "asset\\model\\Skeletonzombie T Avelange.fbx";
	m_EnemyModel[1] = "asset\\model\\Maw J Laygo.fbx";
	m_EnemyModel[2] = "asset\\model\\Warrok W Kurniawan.fbx";


	m_Model = new AnimationModel;
	m_Model->Load(m_EnemyModel[m_EnemyModelCo]);
	m_Model->LoadAnimation("asset\\model\\Mutant Idle.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\Mutant Swiping (1).fbx", "Attack");
	m_Model->LoadAnimation("asset\\model\\Magic Heal.fbx", "LongDistanceAttack");
	m_Model->LoadAnimation("asset\\model\\Mutant Run (1).fbx", "Run");
	m_Model->LoadAnimation("asset\\model\\Two Handed Sword Death.fbx", "Die");
	m_Model->LoadAnimation("asset\\model\\Mutant Roaring.fbx", "Roaring");
	m_Model->LoadAnimation("asset\\model\\Mutant Jumping.fbx", "Jump");



	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	m_Scale = D3DXVECTOR3(0.02f, 0.02f, 0.02f);


	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	m_Player = m_Scene->GetGameObject<Player>();



	std::srand(time(NULL));

	m_EnemyActionRondomNum = rand() % 3 + 1;
	m_Rot1 = rand() % 2 + 1;
	m_Rot2 = rand() % 5 + 1;


	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/dissolve.png",
		NULL,
		NULL,
		&m_DisolveTexture,
		NULL);
	assert(m_DisolveTexture);


	m_ShadowFlg = true;


	m_GameClar = false;


	m_JABarkSE = AddComponet<Audio>();
	m_JABarkSE->Load("asset\\audio\\BeforetheEnemysHeavyAttack.wav");
	m_JALandingSE = AddComponet<Audio>();
	m_JALandingSE->Load("asset\\audio\\EnemyHeavyAttack.wav");
	m_RAttackSE = AddComponet<Audio>();
	m_RAttackSE->Load("asset\\audio\\EnemyRangedAttacks.wav");

	m_DamageBarkSE = AddComponet<Audio>();
	m_DamageBarkSE->Load("asset\\audio\\CryofGoblin2.wav");
	m_DamageBarkSE->Volume(0.2f);

	m_BarkSE = AddComponet<Audio>();
	m_BarkSE->Load("asset\\audio\\CryofGoblin2.wav");
	m_BarkSE->Volume(0.3f);

	if (Village::GetTutorialFlg())
		m_EnemyHp = 30.0f;

	//collition
	m_Collision = m_Scene->AddGameObject<CollisionBox>(1);
	m_Collision->SetScale(D3DXVECTOR3(80.0f, 80.0f, 80.0f));


	GameObject::Init();
}

void Enemy::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Collision->SetDestroy();

	m_Model->Unload();
	delete m_Model;

	m_DisolveTexture->Release();

	GameObject::Uninit();
}

void Enemy::Update()
{
	Weapon* weapon = m_Scene->GetGameObject<Weapon>();
	SpecialAttack01* attack01 = m_Scene->GetGameObject<SpecialAttack01>();
	SpecialAttack02* attack02 = m_Scene->GetGameObject<SpecialAttack02>();
	SpecialAttack03* attack03 = m_Scene->GetGameObject<SpecialAttack03>();
	Bullet* bullet = m_Scene->GetGameObject<Bullet>();

	m_Direction01 = GetPlayerDirection01();
	m_Direction02 = GetPlayerDirection02();
	m_Length = GetPlayerLenth();

	//敵のHPが0になったときの処理
	//敵のジャンプ攻撃オブジェが消えたときのflgがtrueになったら倒れるステートに行く
	if (m_JampAttackOBjFlg)
	{
		m_Damage = true;
		m_JampAttackOBjFlg = false;
		m_EnemyState = ENEMY_STATE_DIE;
	}

	//敵が索敵状態の時のプレイヤーが攻撃した場合の処理
	if (weapon->GetEnemyDamege() && m_EnemyFirstAttackCo < 1 && m_EnemyState == ENEMY_STATE_SACH && 
		(m_Player->GetPlayerAttackHit1() || m_Player->GetPlayerAttackHit2() || m_Player->GetPlayerAttackHit3()))
	{
		m_PlayerDetectFlg = true;
		m_EnemyFirstAttackCo += 1;
	}

	float fieldOfView = D3DXToRadian(120.0f); // 視野角

	//enemyの疑似視野の処理
	m_Siya = IsInFieldOfView(m_Position, m_Direction02, fieldOfView, m_ViewDistance);

	//敵がプレイヤーを見つけたとき動き
	if (m_Siya || m_PlayerDetectFlg)
	{
		m_Attackflg = true;
		m_RoringStart = true;

		if (m_FoundFlg == false)
			m_EnemyState = ENEMY_STATE_ROARING;

		if (m_FoundFlg == true)
			m_EnemyState = ENEMY_STATE_SACH;
	}

	if (m_GameClar == true)
	{
		m_Fade->FadeOut();
	}

	if (m_Fade->GetFadeFinish())
	{

		Manager::SetScene<Result>();
	}

	if (m_EnemyHp <= 20 && m_EnemyHp >= 0)
	{
		m_EnemyState = ENEMY_STATE_JUMPATTACK;
	}
	

	//重力
	m_Velocity.y -= 0.015f;

	//移動
	m_Position += m_Velocity;



	//敵のHPで色が変化する処理
	if (m_EnemyHp > 50.0f)
		m_RimColor = D3DXCOLOR(0.0f, 0.5f, 0.5f, 1.0f);
	else if (m_EnemyHp <= 50.0f && m_EnemyHp > 40.0f)
		m_RimColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	else if (m_EnemyHp <= 40.0f && m_EnemyHp > 30.0f)
		m_RimColor = D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f);
	else if (m_EnemyHp <= 30.0f && m_EnemyHp > 20.0f)
		m_RimColor = D3DXCOLOR(0.6f, 0.3f, 0.0f, 1.0f);
	else if (m_EnemyHp <= 20.0f && m_EnemyHp >= 0.0f)
		m_RimColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	else if (m_EnemyHp <= 0.0f)
		m_RimColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);


	//メッシュフィールドとの衝突判定
	float groundHeight = 0.0f;
	MeshField* meshfield = m_Scene->GetGameObject<MeshField>();
	groundHeight = meshfield->GetHight(m_Position);

	//接地
	if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
	{
		m_Velocity.y = 0.0f;
		m_Position.y = groundHeight;
	}



	//ステートマシーン　
	switch (m_EnemyState)
	{
	case ENEMY_STATE_SACH:
		UpdateEnemySach();
		break;
	case ENEMY_STATE_ROARING:
		UpdateEnemyRoaring();
		break;
	case ENEMY_STATE_FOUND:
		UpdateEnemyFound();
		break;
	case ENEMY_STATE_DIE:
		UpdateEnemyDie();
		break;
	case ENEMY_STATE_REMOTEATTACK:
		UpdateEnemyRemoteAttack();
		break;
	case ENEMY_STATE_JUMPATTACK:
		UpdateEnemyJumpAttack();
		break;
	case ENEMY_STATE_ATTACK:
		UpdateEnemyAttack();
		break;
	case ENEMY_STATE_CHASE:
		UpdateEnemyChase();
		break;

	default:
		break;
	}

	AnimationModel* anim = m_Model;
	BONE* bone = anim->GetBoneName("mixamorig:Hips");
	D3DXMATRIX pearent = anim->ConvertMatrix(bone->WorldMatrix);

	//collision
	m_Collision->SetPearent(m_WorldMatrix);
	m_Collision->SetBoneEnable(true);
	m_Collision->SetBoneMatrix(anim->ConvertMatrix(bone->WorldMatrix));
	SetCollider(m_Collision->GetMatrix());


	GameObject::Update();
}

void Enemy::Draw()
{


	//視錘台カリング
	{
		Scene* scene = Manager::GetScene();
		Camera* camera = scene->GetGameObject<Camera>();

		if (!camera->CheckView(m_Position))
			return;
	}
	D3DXVECTOR3 p_pos = m_Player->GetPosition();
	D3DXVECTOR3 top = GetTop();


	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y + D3DX_PI, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);

	m_WorldMatrix = scale * rot * trans;
	Renderer::SetWorldMatrix(&m_WorldMatrix);





	//ディゾルブの処理
	Renderer::GetDeviceContext()->PSSetShaderResources(2, 1, &m_DisolveTexture);
	PARAMETER param;
	ZeroMemory(&param, sizeof(param));
	param.dissolveThreshold = m_Threshold;
	param.disolveRange = 0.1f;
	Renderer::SetParameter(param);


	//リムライトの処理 
	ENEMYPARAM eparam;
	eparam.rimColor = m_RimColor;
	Renderer::SetEnemy(eparam);


	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendRate);
	m_Time += 0.3f;

	m_BlendRate += 0.03f;

	if (m_BlendRate > 1.0f)
		m_BlendRate = 1.0f;

	m_Model->Draw();


	GameObject::Draw();
}

void Enemy::UpdateEnemyRoaring(void)
{

	if (m_RoringStart == true)
	{
		if (m_NextAnimationName != "Roaring")
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Roaring";
			m_BlendRate = 0.0f;
			m_Roarigflg = true;
			m_Player->SetScaredFlg(true);

		}

		if (m_Roarigflg)
			m_Rotation.y = atan2(m_Direction01.x, m_Direction01.z);


		if (m_Roarigflg == true)
		{
			if (m_RoarigCo == 0)
			{
				m_BarkSE->Play(true);
			}

			m_RoarigCo++;

			if (m_RoarigCo >= 400)
			{
				m_BarkSE->Stop();

				m_ViewDistance = 0.0f;
				m_PlayerDetectFlg = false;
				m_RoringStart = false;
				m_Roarigflg = false;
				m_EnemyState = ENEMY_STATE_FOUND;
				m_FoundFlg = true;
			}

			if (m_RoarigCo >= 300)
			{
				m_Player->SetScaredFlg(false);
			}
		}
	}
}



void Enemy::UpdateEnemySach(void)
{
	m_ViewDistance = 5.0f;
	//敵がプレイヤーを探しているときの動き
	if (m_Animflg == false && m_FoundFlg == false)
	{
		//行動の乱数
		if (m_MoveCo > 100)
		{
			std::srand(time(NULL));
			m_EnemyActionRondomNum = rand() % 3 + 1;
			if (m_EnemyActionRondomNum == 3)
			{
				m_Rot1 = rand() % 2 + 1;
				m_Rot2 = rand() % 5 + 1;
			}
			m_MoveCo = 0;
		}
		//移動しているパターン
		if (m_EnemyActionRondomNum == 1)
		{
			if (m_NextAnimationName != "Run")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Run";
				m_BlendRate = 0.0f;
			}
			m_Position -= GetForward() * 0.1f;

			if (m_Position.x >= 100.0f)
				m_Position.x = 100.0f;

			if (m_Position.x <= -49.0f)
				m_Position.x = -49.0f;


			if (m_Position.z >= 49.0f)
				m_Position.z = 49.0f;

			if (m_Position.z <= -45.0f)
				m_Position.z = -45.0f;

			if (m_MoveCo > 100)
			{
				m_MoveCo = 0;
			}
		}
		//止まっているパターン
		if (m_EnemyActionRondomNum == 2)
		{
			if (m_NextAnimationName != "Idle")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Idle";
				m_BlendRate = 0.0f;
			}
			if (m_MoveCo > 100)
			{
				m_MoveCo = 0;
			}
		}
		//回転しているパターン
		if (m_EnemyActionRondomNum == 3)
		{
			if (m_NextAnimationName != "Idle")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Idle";
				m_BlendRate = 0.0f;
				m_TurnFlg = true;
			}

			m_Rotation.y += 0.1f;
			if (m_Rotation.y > m_Rot2)
			{
				m_Rotation.y = m_Rot2;
			}

			if (m_MoveCo > 100)
			{
				m_MoveCo = 0;
				m_TurnFlg = false;
			}
		}
		m_MoveCo++;
	}

}

void Enemy::UpdateEnemyFound(void)
{
	m_RoringStart = false;
	m_EnemyDistance = 10.0f;


	//プレイヤーを見つけたとき
	if (m_FoundFlg == true)
	{

		//敵の行動numを0にする
		m_EnemyActionRondomNum = 0;

		//攻撃flgをtrueにして攻撃モーションに入る
		m_Animflg = true;
		m_EnemyState = ENEMY_STATE_ATTACK;
	}
}

void Enemy::UpdateEnemyAttack(void)
{
	//攻撃開始するときの距離
	if (ATTACK_RANGE > m_Length)
	{
		if (m_NextAnimationName != "Attack" && m_Attackflg == true)
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Attack";
			m_BlendRate = 0.0f;
			m_ActionFlg = true;
		}

		if (m_ActionFlg == true)
		{
			m_ActionCount++;
			m_EnemyHitOnlyCo++;
		}

		//269
		if (m_EnemyHitOnlyCo == 269)
		{
			m_EnemyHitOnlyCo = 0;
		}

		//enemyが攻撃しているときだけplayerに当たり判定を行うときの処理
		if (m_EnemyHitOnlyCo >= 100 && m_EnemyHitOnlyCo <= 180)
		{
			m_EnemyHitFlg = true;
		}
		else
		{
			m_EnemyHitFlg = false;

		}


		//一定時間たったらプレイヤーの方向を向く処理
		if (m_ActionCount >= 300)
		{
			m_ActionCount = 0;
			m_Rotation.y = atan2(m_Direction01.x, m_Direction01.z);
		}
	}

	//プレイヤーと一定距離離れ場合の処理
	if (ATTACK_RANGE + MIDDLE_RANGE < m_Length)
	{
		m_EnemyHitOnlyCo = 0;
		m_EnemyState = ENEMY_STATE_CHASE;
	}

}

void Enemy::UpdateEnemyChase(void)
{

	if (CHASE_RANGE < m_Length)
	{

		m_ActionFlg = false;
		m_Attackflg = false;
		m_Position += m_Direction02 * 0.01f;

		if (m_ActionFlg == false)
		{
			m_Rotation.y = atan2(m_Direction01.x, m_Direction01.z);
		}

		if (m_NextAnimationName != "Run" && m_Attackflg == false)
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Run";
			m_BlendRate = 0.0f;

		}

		//少し追いかけたら遠隔攻撃に切り替える
		if (m_RunCo > 100)
		{
			m_EnemyState = ENEMY_STATE_REMOTEATTACK;
			m_RunCo = 0;
			m_FoundFlg = false;
			m_Animflg = false;
		}
		m_RunCo++;
	}
	else
	{
		m_RunCo = 0;
		m_Attackflg = true;
		m_EnemyState = ENEMY_STATE_ATTACK;
	}

}



void Enemy::UpdateEnemyDie(void)
{
	if (m_NextAnimationName != "Die" && m_Damegeflg == false)
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Die";
		m_BlendRate = 0.0f;
		m_Damegeflg = true;
	}



	if (m_Damegeflg == true)
	{

		m_DamegeCo++;

		if (m_DamegeCo >= 230)
			m_NextAnimationName = "";

		if (m_DamegeCo >= 800)
		{
			m_Threshold += 0.005f;

			if (m_Threshold > 1.1f)
			{
				SetDestroy();
				m_Threshold = 0.0f;

				if (m_DamegeCo >= 600)
				{
					m_GameClar = true;
				}
			}
		}
	}
}


void Enemy::UpdateEnemyRemoteAttack(void)
{
	//アニメーション再生
	if (m_NextAnimationName != "LongDistanceAttack")
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "LongDistanceAttack";
		m_BlendRate = 0.0f;
	}

	//遠距離攻撃予想落下地点
	AttackPrediction* attackp;
	//遠距離攻撃の落下物
	EnemyRemoteAttack* eattack;

	//遠距離攻撃カウント
	attacPCo++;

	//遠距離攻撃カウントが1の時一回だけ予想落下地点モデルを表示する
	if (attacPCo == 1)
		attackp = m_Scene->AddGameObject<AttackPrediction>(1);

	//予想落下地点モデルの情報を呼び出す
	attackp = m_Scene->GetGameObject<AttackPrediction>();

	//敵が落下予想地点モデルの方向を向くようにするための処理
	D3DXVECTOR3 direction1 = m_Position - attackp->GetPosition();
	direction1.y = 0.0f;
	D3DXVec3Normalize(&direction1, &direction1);
	m_Rotation.y = atan2(direction1.x, direction1.z);

	//遠距離攻撃カウントが100になると予想地点モデルの座標が固定される
	if (attacPCo <= 100)
		attackp->SetPosition(m_Player->GetPosition());

	//遠距離攻撃カウントが150の時一回だけ落下物モデルを投下する
	if (attacPCo == 150)
	{
		EnemyRemoteAttack* eattack = m_Scene->AddGameObject<EnemyRemoteAttack>(1);
		eattack->SetPosition(D3DXVECTOR3(attackp->GetPosition().x, 5.0f, attackp->GetPosition().z));
		m_RAttackSE->Play();
		m_RAttackSE->Volume(0.2f);
	}

	//落下物モデルの情報を呼び出す
	eattack = m_Scene->GetGameObject<EnemyRemoteAttack>();

	//遠距離攻撃カウントが160以上になると落下物モデルと予想地点モデルを消し、カウント0にする
	if (attacPCo > 160)
	{
		attackp->SetDestroy();
		eattack->SetDestroy();
		attacPCo = 0;
	}

	//敵とプレイヤーの位置が一定より近づくと近距離攻撃のステートに移るようにする処理
	if (ATTACK_RANGE > m_Length)
	{
		attackp->SetDestroy();

		if(eattack != NULL)
			eattack->SetDestroy();

		m_EnemyState = ENEMY_STATE_ATTACK;
		m_FoundFlg = true;
		m_Attackflg = true;
		attacPCo = 0;
	}


}


void Enemy::UpdateEnemyJumpAttack(void)
{

	AttackPrediction* attackp;
	EnemyJumpAttack* jumpattack;
	float attackY = -1.0f;


	if (m_NextAnimationName != "Jump")
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Jump";
		m_BlendRate = 0.0f;
		m_EnemyJumpFlg = true;
	}

	if (m_EnemyJumpFlg)
	{
		m_EnemyJumpCo++;

		if (m_EnemyJumpCo == 1)
		{
			attackp = m_Scene->AddGameObject<AttackPrediction>(1);
			m_JABarkSE->Play();
			m_JABarkSE->Volume(0.2f);
		}

		attackp = m_Scene->GetGameObject<AttackPrediction>();
		jumpattack = m_Scene->GetGameObject<EnemyJumpAttack>();

		D3DXVECTOR3 direction2 = attackp->GetPosition() - m_Position;

		if (m_EnemyJumpCo >= 80)
			m_Position += direction2 * 0.01f;





		D3DXVECTOR3 direction1 = m_Position - attackp->GetPosition();
		direction1.y = 0.0f;
		D3DXVec3Normalize(&direction1, &direction1);




		m_Rotation.y = atan2(direction1.x, direction1.z);



		if (m_EnemyJumpCo <= 100)
			attackp->SetPosition(m_Player->GetPosition());


		if (m_EnemyJumpCo == 200)
		{
			m_Position = attackp->GetPosition();
			jumpattack = m_Scene->AddGameObject<EnemyJumpAttack>(1);
			jumpattack->SetPosition(D3DXVECTOR3(attackp->GetPosition().x, -0.1f, attackp->GetPosition().z));
			m_JALandingSE->Play();
			m_JALandingSE->Volume(0.6f);
		}

		if (m_EnemyJumpCo >= 200)
			m_Position -= direction2 * 0.01f;


		if (m_EnemyJumpCo >= 320)
		{
			m_EnemyJumpCo = 0;
			attackp->SetDestroy();
			jumpattack->SetDestroy();

		}

		//enemyのHPが0になったらジャンプ攻撃のオブジェクトを消してflgをオンにする
		if (m_EnemyHp <= 0 && !m_JampAttackOBjFlg)
		{

			attackp->SetDestroy();

			if(jumpattack != NULL)
				jumpattack->SetDestroy();

			m_JampAttackOBjFlg = true;
		}


	}


}

bool Enemy::IsInFieldOfView(const D3DXVECTOR3& origin, D3DXVECTOR3& direction, float fieldOfViewRadians, float viewDistancee)
{
	// 視野範囲内かどうかの判定
	D3DXVECTOR3 normalizedDirection;
	D3DXVec3Normalize(&normalizedDirection, &direction);
	D3DXVECTOR3 houkou = -GetForward();
	float dotProduct = D3DXVec3Dot(&houkou, &normalizedDirection);
	float angle = acos(dotProduct);
	bool isInFieldOfView = angle <= fieldOfViewRadians / 2.0f;

	// 視野距離内かどうかの判定
	D3DXVECTOR3 dice = origin - m_Player->GetPosition();
	float distance = D3DXVec3Length(&dice);
	bool isInViewDistance = distance <= viewDistancee;

	return isInFieldOfView && isInViewDistance;
}

D3DXVECTOR3 Enemy::GetPlayerDirection01(void) {

	D3DXVECTOR3 direction = m_Position - m_Player->GetPosition();
	direction.y = 0.0f;
	D3DXVec3Normalize(&direction, &direction);

	return direction;
}

float Enemy::GetPlayerLenth(void) {

	D3DXVECTOR3 direction = m_Player->GetPosition() - m_Position;
	float length = D3DXVec3Length(&direction);
	return length;
}

D3DXVECTOR3 Enemy::GetPlayerDirection02(void) {

	D3DXVECTOR3 direction = m_Player->GetPosition() - m_Position;

	return direction;
}
