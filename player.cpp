#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "drawModel.h"
#include "input.h"
#include "scene.h"
#include "player.h"
#include "bullet.h"
#include "cylinder.h"
#include "box.h"
#include "audio.h"
#include "score.h"
#include "animationModel.h"
#include "meshField.h"
#include "camera.h"
#include "enemy.h"
#include "ui01.h"
#include "result.h"
#include "fade.h"
#include "explosion.h"
#include "weapon.h"
#include "enemyRemoteAttack.h"
#include "itemDataLoad.h"
#include "enemyJumpAttack.h"
#include "specialAttack01.h"
#include "specialAttack02.h"
#include "specialAttack03.h"
#include "village.h"
#include "collitionBox.h"
#include "villagePlayerAction.h"
#include "tutorial.h"
#include "villageUi.h"
#include "game.h"
#include "healEffect.h"

bool Player::m_PlayerEndFlg{};

void Player::Init()
{
	m_Scene = Manager::GetScene();

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\DepthShadowMappingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\DepthShadowMappingPS.cso");


	//アニメーションとモデルのロード
	{
		m_Model = new AnimationModel;
		m_Model->Load("asset\\model\\Ganfaul M Aure.fbx");
		m_Model->LoadAnimation("asset\\model\\Running (1).fbx", "Run");
		m_Model->LoadAnimation("asset\\model\\Breathing Idle.fbx", "Idle");
		m_Model->LoadAnimation("asset\\model\\One Hand Sword Combo (2).fbx", "Attack1");
		m_Model->LoadAnimation("asset\\model\\One Hand Sword Combo (3).fbx", "Attack2");
		m_Model->LoadAnimation("asset\\model\\Sword And Shield Slash (2).fbx", "Attack3");
		m_Model->LoadAnimation("asset\\model\\Great Sword Impact.fbx", "Damege");
		m_Model->LoadAnimation("asset\\model\\Stand To Roll.fbx", "Avoid");
		m_Model->LoadAnimation("asset\\model\\Terrified.fbx", "Scared");
		m_Model->LoadAnimation("asset\\model\\Sheath A Great Sword 1 (1).fbx", "SowrdMount");
		m_Model->LoadAnimation("asset\\model\\Draw A Great Sword 2.fbx", "SowrdSetUp");
		m_Model->LoadAnimation("asset\\model\\Great Sword Casting (2).fbx", "SpecialAttack");
		m_Model->LoadAnimation("asset\\model\\Great Sword Casting (5).fbx", "SpecialAttack2");
		m_Model->LoadAnimation("asset\\model\\/Two Handed Sword Death (1).fbx", "PlayerEnd");
		m_Model->LoadAnimation("asset\\model\\/Two Handed Sword Death (4).fbx", "PlayerEnd2");
		m_Model->LoadAnimation("asset\\model\\/Standing 2H Magic Area Attack 02.fbx", "heal");
	}



	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);
	m_Fade = m_Scene->AddGameObject<Fade>(2);
	m_Weapon = m_Scene->AddGameObject<Weapon>(2);

	//SELoad
	{
		m_DamageSE_1 = AddComponet<Audio>();
		m_DamageSE_1->Load("asset\\audio\\プレイヤーダメージ1.wav");
		m_DamageSE_1->Volume(0.4f);
		m_DamageSE_2 = AddComponet<Audio>();
		m_DamageSE_2->Load("asset\\audio\\プレイヤーダメージ2.wav");
		m_DamageSE_2->Volume(0.4f);

		m_HealSE = AddComponet<Audio>();
		m_HealSE->Load("asset\\audio\\体力回復.wav");
		m_HealSE->Volume(0.4f);

		m_AVoiceSE_1 = AddComponet<Audio>();
		m_AVoiceSE_1->Load("asset\\audio\\プレイヤー攻撃掛け声1.wav");
		m_AVoiceSE_1->Volume(0.4f);
		m_AVoiceSE_2 = AddComponet<Audio>();
		m_AVoiceSE_2->Load("asset\\audio\\プレイヤー攻撃掛け声2.wav");
		m_AVoiceSE_2->Volume(0.4f);
		m_AVoiceSE_3 = AddComponet<Audio>();
		m_AVoiceSE_3->Load("asset\\audio\\プレイヤー攻撃掛け声3.wav");
		m_AVoiceSE_3->Volume(0.4f);

		m_AttackSE_1 = AddComponet<Audio>();
		m_AttackSE_1->Load("asset\\audio\\剣で斬る.wav");
		m_AttackSE_1->Volume(0.4f);
		m_AttackSE_2 = AddComponet<Audio>();
		m_AttackSE_2->Load("asset\\audio\\剣で斬る.wav");
		m_AttackSE_2->Volume(0.4f);
		m_AttackSE_3 = AddComponet<Audio>();
		m_AttackSE_3->Load("asset\\audio\\剣で斬る.wav");
		m_AttackSE_3->Volume(0.4f);

		m_SAVoiceSE = AddComponet<Audio>();
		m_SAVoiceSE->Load("asset\\audio\\プレイヤー重攻撃掛け声.wav");
		m_SAVoiceSE->Volume(0.4f);

		m_SALandingSE = AddComponet<Audio>();
		m_SALandingSE->Load("asset\\audio\\プレイヤー重攻撃前.wav");
		m_SALandingSE->Volume(1.0f);

		m_SAttackSE_1 = AddComponet<Audio>();
		m_SAttackSE_1->Load("asset\\audio\\プレイヤー重攻撃1.wav");
		m_SAttackSE_1->Volume(0.6f);
		m_SAttackSE_2 = AddComponet<Audio>();
		m_SAttackSE_2->Load("asset\\audio\\プレイヤー重攻撃2.wav");
		m_SAttackSE_2->Volume(0.6f);

		m_BGM2 = AddComponet<Audio>();
		m_BGM2->Load("asset\\audio\\土の上を走る.wav");
		m_BGM3 = AddComponet<Audio>();
		m_BGM3->Load("asset\\audio\\剣を抜く.wav");
		m_BGM4 = AddComponet<Audio>();
		m_BGM4->Load("asset\\audio\\剣を鞘にしまう.wav");
	}


	m_Hp = HP_MAX;

	m_ShadowFlg = true;


	m_PlayerEndFlg = false;

	//アイテムデーターベースのデータロード
	ItemDataLoad::DataLoad();
	m_ItemCo = ItemDataLoad::GetItemBaseIndex(0)->GetItemCount();

	//collition
	m_Collision = m_Scene->AddGameObject<CollisionBox>(1);
	m_Collision->SetScale(D3DXVECTOR3(80.0f, 80.0f, 80.0f));


	GameObject::Init();

}

void Player::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Collision->SetDestroy();

	m_Model->Unload();
	delete m_Model;

	GameObject::Uninit();
}

void Player::Update()
{
	D3DXVECTOR3 oldPosition = m_Position;
	Camera* camera = m_Scene->GetGameObject<Camera>();
	Enemy* enemey = m_Scene->GetGameObject<Enemy>();
	Ui01* hpred = m_Scene->GetGameObject<Ui01>();
	Ui01* hpgreen = m_Scene->GetGameObject<Ui01>();
	EnemyRemoteAttack* remoteAttack = m_Scene->GetGameObject<EnemyRemoteAttack>();
	EnemyJumpAttack* enemyJumpAttack = m_Scene->GetGameObject<EnemyJumpAttack>();

	//敵の当たり判定（enemyがnullの時はゲームが終了する)
	if (enemey == NULL && !Village::GetTutorialFlg() && Game::GetGameFlg())
		m_Fade->FadeOut();

	if (m_Fade->GetFadeFinish())
	{
		Manager::SetScene<Result>();
		Game::SetGameFlg(false);
	}

	//遠隔攻撃の当たり判定flg
	if (remoteAttack != NULL)
		m_RemoteDamage = remoteAttack->GetAttackFlg();


	//////////ゲームシーンまたはチュートリアルシーンでの処理////////////////
	if (Game::GetGameFlg() || Tutorial::GetTutorialFlg())
	{
		if (hpred->GetHPRed() < HPREDMAX)
		{
			hpgreen->SetHPGreenplus(0.1f);
			if (hpred->GetHPRed() <= hpgreen->GetHPGreenScale())
			{
				hpgreen->SetHPGreenScale(hpred->GetHPRed());
			}
		}
	}

	if (m_Hp <= 0)
	{
		if(m_PlayerEndCo <= 74)
			m_PlayerState = PLAYER_STATE_END;
		else 
			m_PlayerState = PLAYER_STATE_END2;

		m_GameoverCo++;

		if(m_GameoverCo >= 400)
			m_Fade->FadeOut();
	
		if (m_Fade->GetFadeFinish())
		{
			Manager::SetScene<Result>();
		}
	}


	//重力
	m_Velocity.y -= 0.015f;
	m_Velocity.x -= 0.05f;
	m_Velocity.z -= 0.05f;

	if (m_Velocity.x <= 0)
		m_Velocity.x = 0.0f;

	if (m_Velocity.z <= 0)
		m_Velocity.z = 0.0f;


	//移動
	m_Position += m_Velocity;

	//メッシュフィールドとの衝突判定
	float groundHeight = 0.0f;
	MeshField* meshfield = m_Scene->GetGameObject<MeshField>();
	groundHeight = meshfield->GetHight(m_Position);

	//接地
	if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
	{
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;


		m_IsGround = true;
	}
	else
	{
		m_IsGround = false;
	}

	//////////////////村でのプレイヤーの処理//////////////////
	if (Village::GetVillageFlg())
	{
		VillagePlayerAction* villageAction = m_Scene->GetGameObject<VillagePlayerAction>();
		villageAction->VillageActions();
	}


	//敵との当たり判定
	if (enemey != NULL)
	{

		//OBB
		if (m_Collision->SetOBB(this, enemey, 1.0f) && m_PlayerState != PLAYER_STATE_DAMAGE && enemey != NULL)
		{
			m_Position.x = m_OldPosition.x;
			m_Position.z = m_OldPosition.z;
		}

		//AABB
		//D3DXVECTOR3 position = enemey->GetPosition();
		//D3DXVECTOR3 scale = enemey->GetScale() * 90;

		//if (position.x - scale.x - 0.5f < m_Position.x &&
		//	m_Position.x < position.x + scale.x + 0.5f &&
		//	position.z - scale.z - 0.5f < m_Position.z &&
		//	m_Position.z < position.z + scale.z + 0.5f)
		//{
		//	if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)
		//	{
		//		if (m_PlayerState != PLAYER_STATE_DAMAGE)
		//		{
		//			m_Position.x = m_OldPosition.x;
		//			m_Position.z = m_OldPosition.z;
		//		}
		//	}
		//}
	}

	//敵の特殊攻撃との当たり判定
	if (enemyJumpAttack != NULL && enemey != NULL)
	{
		//AABB
		/*D3DXVECTOR3 position = enemyJumpAttack->GetPosition();
		D3DXVECTOR3 scale = enemyJumpAttack->GetScale() * 4;

		if (position.x - scale.x - 0.5f < m_Position.x &&
			m_Position.x < position.x + scale.x + 0.5f &&
			position.z - scale.z - 0.5f < m_Position.z &&
			m_Position.z < position.z + scale.z + 0.5f)
		{
			if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)
			{
				m_Damage = true;
			}
		}*/

		//OBB
		if (m_Collision->SetOBB(this, enemyJumpAttack, 2.0f) && enemey->GetEnemyState() == ENEMY_STATE_JUMPATTACK)
		{
			m_Damage = true;
		}
	}



	//フィールドの上限と下限
	if (m_Position.x >= 100.0f)
		m_Position.x = 100.0f;

	if (m_Position.x <= -49.0f)
		m_Position.x = -49.0f;


	if (m_Position.z >= 49.0f)
		m_Position.z = 49.0f;

	if (m_Position.z <= -45.0f)
		m_Position.z = -45.0f;


	//ステートマシーン　
	switch (m_PlayerState)
	{
	case PLAYER_STATE_GROUND:
		UpdateGround();
		break;
	case PLAYER_STATE_ATTACK1:
		UpdateAttack1();
		break;
	case PLAYER_STATE_ATTACK2:
		UpdateAttack2();
		break;
	case PLAYER_STATE_ATTACK3:
		UpdateAttack3();
		break;
	case PLAYER_STATE_DAMAGE:
		UpdateDamege();
		break;
	case PLAYER_STATE_AVOIDANCE:
		UpdateAvoidace();
		break;
	case PLAYER_STATE_SCARED:
		UpdateScared();
		break;
	case PLAYER_STATE_MOUNT:
		UpdateMountMode();
		break;
	case PLAYER_STATE_SETUP:
		UpdateSetUpMode();
		break;
	case PLAYER_STATE_SPECIALATTACK:
		UpdateSpecialAttack();
		break;
	case PLAYER_STATE_END:
		UpdatePlayerEnd();
		break;
	case PLAYER_STATE_END2:
		UpdatePlayerEnd2();
		break;
	case PLAYER_STATE_HEAL:
		UpdateHeal();
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


	//collision
	m_Collision->SetPearent(m_WorldMatrix);
	SetCollider(m_Collision->GetMatrix());

	GameObject::Update();
}

void Player::Draw()
{


	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_WorldMatrix = scale * rot * trans;
	Renderer::SetWorldMatrix(&m_WorldMatrix);



	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendRate);
	m_Time+=0.6f;  //0.4f

	m_BlendRate += 0.03f;

	if (m_BlendRate > 1.0f)
		m_BlendRate = 1.0f;

	m_Model->Draw();


	GameObject::Draw();
}


void Player::UpdateGround()
{

	m_OldPosition = m_Position;

	Camera* camera = m_Scene->GetGameObject<Camera>();
	Enemy* enemy = m_Scene->GetGameObject<Enemy>();
	D3DXVECTOR3 cameraFoward;

	Ui01* ui = m_Scene->GetGameObject<Ui01>();
	Ui01* hpred = m_Scene->GetGameObject<Ui01>();
	Ui01* hpgreen = m_Scene->GetGameObject<Ui01>();
	VillagePlayerAction* vplayer = m_Scene->GetGameObject<VillagePlayerAction>();
	
	m_MoveFlg = false;

	//同時に押したときでも速度が変わらないようにする処理
	if (Input::GetKeyPress('W') || Input::GetKeyPress('D') &&
		Input::GetKeyPress('S') || Input::GetKeyPress('D') &&
		Input::GetKeyPress('W') || Input::GetKeyPress('A') &&
		Input::GetKeyPress('S') || Input::GetKeyPress('A'))
	{
		m_Forward = 0.071f;
	}
	else
	{
		m_Forward = 0.1f;
	}

	//村人と話しているときは動けないようにするflgの処理
	if (vplayer != NULL)
		m_VillageStopFlg = vplayer->GetSVillgeStopFlg();
	else
		m_VillageStopFlg = false;

	if (!m_VillageStopFlg)
	{
		// サードパーソンビュー
		if (Input::GetKeyPress('A'))
		{

			if (m_NextAnimationName != "Run")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Run";
				m_BlendRate = 0.0f;

			}

			cameraFoward = camera->GetRight();
			cameraFoward.y = 0.0f;
			D3DXVec3Normalize(&cameraFoward, &cameraFoward);

			m_Position -= cameraFoward * m_Forward;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(cameraFoward.x, -cameraFoward.z);

			D3DXQuaternionRotationAxis(&quat, &axis, -angle);
			//m_Quaternion = quat;
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);


			if (Input::GetKeyPress(VK_SHIFT) && (Game::GetGameFlg() || Tutorial::GetTutorialFlg()))
			{

				ui->SetSutaminahiku(2.0f);
				if (ui->GetSutaminaScale() <= 0)
					ui->SetSutamina(0.0f);
				else
					m_Position -= cameraFoward * m_Forward;

				m_SutaminaFlg = true;

			}
			else
				m_SutaminaFlg = false;


			if (Input::GetKeyPress(VK_CONTROL))
			{
				m_LeftAvoid = true;
				m_PlayerState = PLAYER_STATE_AVOIDANCE;

			}
			else
			{
				m_LeftAvoid = false;
			}

			m_MoveFlg = true;

		}
		else
		{
			if (!m_RunBgm1)
			{
				m_BGM2->Stop();
				m_RunBgm1 = true;

			}

		}

		if (Input::GetKeyTrigger('A'))
		{
			m_RunBgm1 = false;
			m_BGM2->Play(true);
			m_BGM2->Volume(0.1f);

		}




		if (Input::GetKeyPress('D'))
		{

			if (m_NextAnimationName != "Run")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Run";
				m_BlendRate = 0.0f;
			}

			cameraFoward = camera->GetRight();
			cameraFoward.y = 0.0f;
			D3DXVec3Normalize(&cameraFoward, &cameraFoward);

			m_Position += cameraFoward * m_Forward;


			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(cameraFoward.x, cameraFoward.z);

			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			//m_Quaternion = quat;
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);

			if (Input::GetKeyPress(VK_SHIFT) && (Game::GetGameFlg() || Tutorial::GetTutorialFlg()))
			{

				ui->SetSutaminahiku(2.0f);
				if (ui->GetSutaminaScale() <= 0)
					ui->SetSutamina(0.0f);
				else
					m_Position += cameraFoward * m_Forward;

				m_SutaminaFlg = true;

			}
			else
				m_SutaminaFlg = false;


			if (Input::GetKeyPress(VK_CONTROL))
			{
				m_RightAvoid = true;
				m_PlayerState = PLAYER_STATE_AVOIDANCE;

			}
			else
			{
				m_RightAvoid = false;
			}

			m_MoveFlg = true;
		}
		else
		{
			if (!m_RunBgm2)
			{
				m_BGM2->Stop();
				m_RunBgm2 = true;

			}

		}

		if (Input::GetKeyTrigger('D'))
		{
			m_RunBgm2 = false;
			m_BGM2->Play(true);
			m_BGM2->Volume(0.1f);

		}


		if (Input::GetKeyPress('W'))
		{
			if (m_NextAnimationName != "Run")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Run";
				m_BlendRate = 0.0f;
			}

			cameraFoward = camera->GetForward();
			cameraFoward.y = 0.0f;
			D3DXVec3Normalize(&cameraFoward, &cameraFoward);


			m_Position += cameraFoward * m_Forward;




			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(cameraFoward.x, cameraFoward.z);
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			//m_Quaternion = quat;
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);



			if (Input::GetKeyPress(VK_SHIFT) && (Game::GetGameFlg() || Tutorial::GetTutorialFlg()))
			{

				ui->SetSutaminahiku(1.0f);
				if (ui->GetSutaminaScale() <= 0)
					ui->SetSutamina(0.0f);
				else
					m_Position += cameraFoward * m_Forward;

				m_SutaminaFlg = true;

			}
			else
				m_SutaminaFlg = false;




			if (Input::GetKeyPress(VK_CONTROL))
			{
				m_FrontAvoid = true;
				m_PlayerState = PLAYER_STATE_AVOIDANCE;

			}
			else
			{
				m_FrontAvoid = false;
			}

			m_MoveFlg = true;
		}
		else
		{
			if (!m_RunBgm3)
			{
				m_BGM2->Stop();
				m_RunBgm3 = true;

			}
			m_SutaminaFlg = false;

		}

		if (Input::GetKeyTrigger('W'))
		{
			m_RunBgm3 = false;
			m_BGM2->Play(true);
			m_BGM2->Volume(0.1f);

		}

		if (Input::GetKeyPress('S'))
		{
			if (m_NextAnimationName != "Run")
			{
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "Run";
				m_BlendRate = 0.0f;
			}

			cameraFoward = camera->GetForward();
			cameraFoward.y = 0.0f;
			D3DXVec3Normalize(&cameraFoward, &cameraFoward);

			m_Position -= cameraFoward * m_Forward;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(cameraFoward.x, -cameraFoward.z);
			D3DXQuaternionRotationAxis(&quat, &axis, -angle);
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);

			if (Input::GetKeyPress(VK_SHIFT) && (Game::GetGameFlg() || Tutorial::GetTutorialFlg()))
			{

				ui->SetSutaminahiku(1.0f);
				if (ui->GetSutaminaScale() <= 0)
					ui->SetSutamina(0.0f);
				else
					m_Position -= cameraFoward * m_Forward;

				m_SutaminaFlg = true;

			}
			else
				m_SutaminaFlg = false;


			if (Input::GetKeyPress(VK_CONTROL))
			{
				m_BackAvoid = true;
				m_PlayerState = PLAYER_STATE_AVOIDANCE;

			}
			else
			{
				m_BackAvoid = false;
			}

			m_MoveFlg = true;
		}
		else
		{
			if (!m_RunBgm4)
			{
				m_BGM2->Stop();
				m_RunBgm4 = true;

			}

		}

		if (Input::GetKeyTrigger('S'))
		{
			m_RunBgm4 = false;
			m_BGM2->Play(true);
			m_BGM2->Volume(0.1f);

		}

	}


	if(m_AttackCoFlg == true)
	m_AattackCo++;


	if (m_AattackCo >= 10)
	{
		m_AattackCo = 0;
		m_AttackCoFlg = false;
	}

	//攻撃
	if (Input::GetKeyTrigger(VK_LBUTTON) && m_Attack01Co == 0 && m_Attackstate2_1 == false && m_Attackstate3_1 == false && m_SetUpFlg02)
	{
		m_Attackstate1 = true;
	}

	if (Input::GetKeyTrigger(VK_LBUTTON) && m_AttackCoFlg02 == 0 && m_Attackstate2_1 == true && m_SetUpFlg02)
	{
		m_Attackstate2_2 = true;
	}

	if (Input::GetKeyTrigger(VK_LBUTTON) && m_AttackCoFlg03 == 0 && m_Attackstate3_1 == true && m_SetUpFlg02)
	{
		m_Attackstate3_2 = true;

	}

	

	if (m_Attackstate1 == true)
	{
		m_PlayerState = PLAYER_STATE_ATTACK1;
	}

	if (m_Attackstate2_2 == true)
	{
		m_PlayerState = PLAYER_STATE_ATTACK2;
	}

	if (m_Attackstate3_2 == true)
	{
		m_PlayerState = PLAYER_STATE_ATTACK3;

	}

	//敵の咆哮時の怯み
	if (m_ScaredStart == true)
		m_PlayerState = PLAYER_STATE_SCARED;



	//特殊攻撃
	if (Input::GetKeyTrigger(VK_RBUTTON) && m_SetUpFlg02 && ui->GetSpescalAttackScale() >= 160.0f)
		m_SpecialAttackFlg = true;
	

	if(m_SpecialAttackFlg)
		m_PlayerState = PLAYER_STATE_SPECIALATTACK;

	

	/*if ((Input::GetKeyPress('S') || Input::GetKeyPress('W') || Input::GetKeyPress('A') || Input::GetKeyPress('D')) && 
		Input::GetKeyPress(VK_CONTROL))
	{
		m_BackAvoid = true;
		m_PlayerState = PLAYER_STATE_AVOIDANCE;
	}else 
		m_BackAvoid = false;*/


	if (!m_SutaminaFlg && (Game::GetGameFlg() || Tutorial::GetTutorialFlg()))
	{
		ui->SetSutaminaplus(1.0f);
		if (ui->GetSutaminaScale() >= SUTAMINAMAX)
			ui->SetSutamina(SUTAMINAMAX);

	}

	

	//村シーンでは剣を扱えないようにする処理
	if (!Village::GetVillageFlg())
	{
		//剣をとりだすアニメーション
		if (Input::GetKeyTrigger('Q') && !m_SetUpFlg02)
			m_SetUpFlg = true;

		if (m_SetUpFlg)
			m_PlayerState = PLAYER_STATE_SETUP;

		//剣をしまうアニメーション
		if (Input::GetKeyTrigger('E') && m_SetUpFlg02)
			m_MountFlg = true;

		if (m_MountFlg)
			m_PlayerState = PLAYER_STATE_MOUNT;
	}



	//体力処理
	if ((m_Damage == true || m_RemoteDamage == true) && 
		(Game::GetGameFlg() || Tutorial::GetTutorialFlg()))
	{
		if (!m_PlayerEndFlg)
		{
			m_Hp -= 8.0f;
			float red = 8.0f;
			hpgreen->SetHPGreenhiku(15.0f);
			hpred->SetHPRedhiku(red);
			red *= red;

			m_PlayerState = PLAYER_STATE_DAMAGE;
		}
	}

	//回復
	if (Input::GetKeyTrigger('F') && m_ItemCo > 0 && 
		(Game::GetGameFlg() || Tutorial::GetTutorialFlg()))
	{
		m_HealAnmFlg = true;
		m_PlayerState = PLAYER_STATE_HEAL;

		if (m_Hp < HP_MAX)
		{
			m_Hp += 20.0f;//2.0
			float red = 20.0f;//2.0
			hpgreen->SetHPGreenhiku(40.0f); //4.0
			hpgreen->SetHPGreenScale(hpred->GetHPRed()); //4.0
			hpred->SetHPRedplsu(red);

		}

		m_ItemCo -= 1;
		if (m_ItemCo < 0)
			m_ItemCo = 0;

		ItemDataLoad::GetItemBaseIndex(0)->SetItemCount(m_ItemCo);
	}
	
	m_Attack01Flg = false;

	if (!m_MoveFlg)
	{
		if (m_NextAnimationName != "Idle")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Idle";
			m_BlendRate = 0.0f;
		}
	}

}

void Player::UpdateAttack1(void)
{
	if (m_Attack01Co == 0)
	{
		m_AVoiceSE_1->Play();
	}

	if (m_NextAnimationName != "Attack1")
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Attack1";
		m_BlendRate = 1.0f;
		m_AttackCoFlg01 = true;
	}

	if (m_AttackCoFlg01 == true)
	{
		m_Attack01Co++;
		m_AttackSE_1->Play(false);
		
	}


	//敵との衝突判定の時だけヒットストップする処理
	if (m_Weapon->GetEnemyDamege())
	{
		if (m_Attack01Co >= 30 && m_Attack01Co <= 40)
		{
			auto camera = m_Scene->GetGameObject<Camera>();
			camera->Shake(0.02f);
			m_AnimationName = "None";

		}
		else
			m_AnimationName = "Attack1";
	}

	//エフェクト付けるためのflg
	if (m_Attack01Co == 40)
		m_AttackHit1 = true;
	else
		m_AttackHit1 = false;


	
	if (m_Attack01Co >= 50)
	{
		m_Attack01Flg = true;

		m_Attack01Co = 0;
		m_AttackFlg = false;
		m_AttackCoFlg01 = false;
		m_Attackstate1 = false;
		m_Attackstate2_1 = true;
		m_PlayerState = PLAYER_STATE_GROUND;
	}
}

void Player::UpdateAttack2(void)
{
	if (m_Count <= 30)
	{
		if (m_Attack02Co == 0)
		{
			m_AVoiceSE_2->Play();
		}

		if (m_NextAnimationName != "Attack2")
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Attack2";
			m_BlendRate = 1.0f;
			m_AttackCoFlg02 = true;

		}
	}

	if (m_AttackCoFlg02 == true)
	{
		m_Attack02Co++;
		m_AttackSE_2->Play(false);
	}


	//敵との衝突判定の時だけヒットストップする処理
	if (m_Weapon->GetEnemyDamege())
	{
		if (m_Attack02Co >= 10 && m_Attack02Co <= 20)
		{
			auto camera = m_Scene->GetGameObject<Camera>();
			camera->Shake(0.02f);
			m_AnimationName = "None";
		}
		else
			m_AnimationName = "Attack2";
	}
	
	//エフェクト付けるためのflg
	if (m_Attack02Co == 20)
		m_AttackHit2 = true;
	else
		m_AttackHit2 = false;



	if (m_Attack02Co >= 30)
	{
		m_Attack01Flg = true;

		m_Attack02Co = 0;
		m_AttackFlg = false;
		m_AttackCoFlg02 = false;
		//m_Damage = true;
		m_Attackstate1 = false;
		m_Attackstate2_1 = false;
		m_Attackstate2_2 = false;
		m_Attackstate3_1 = true;
		m_PlayerState = PLAYER_STATE_GROUND;

	}
}

void Player::UpdateAttack3(void)
{
	if (m_Count <= 70)
	{
		if (m_Attack03Co == 0)
		{
			m_AVoiceSE_3->Play();
		}

		if (m_NextAnimationName != "Attack3")
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Attack3";
			m_BlendRate = 1.0f;
			m_AttackCoFlg03 = true;
		}
	}

	if (m_AttackCoFlg03 == true)
	{
		m_Attack03Co++;
		m_AttackSE_3->Play(false);
	}


	//敵との衝突判定の時だけヒットストップする処理
	if (m_Weapon->GetEnemyDamege())
	{
		if (m_Attack03Co >= 40 && m_Attack03Co <= 50)
		{
			auto camera = m_Scene->GetGameObject<Camera>();
			camera->Shake(0.02f);
			m_AnimationName = "None";

		}
		else
			m_AnimationName = "Attack3";
	}

	//エフェクト付けるためのflg
	if (m_Attack03Co == 50)
		m_AttackHit3 = true;
	else
		m_AttackHit3 = false;


	if (m_Attack03Co >= 70)
	{
		m_Attack01Flg = true;
		m_Attack03Co = 0;
		m_AttackFlg = false;
		m_AttackCoFlg03 = false;
		m_Attackstate1 = false;
		m_Attackstate3_2 = false;
		m_Attackstate2_2 = false;
		m_Attackstate3_1 = false;
		m_PlayerState = PLAYER_STATE_GROUND;
	}
}

void Player::UpdateHeal(void)
{
	if (m_HealAnmFlg)
	{
		if (m_NextAnimationName != "heal")
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "heal";
			m_BlendRate = 1.0f;
			m_HealFlg = true;
		}

		if (m_HealFlg)
		{
			m_HealCo++;

			if (m_HealCo == 80)
			{

				HealEffect* heal = m_Scene->AddGameObject<HealEffect>(1);
				heal->SetPosition(D3DXVECTOR3(m_Position.x, m_Position.y - 1.0f, m_Position.z));
				heal->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
				heal->SetColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
				m_HealSE->Play();
			}

			if (m_HealCo >= 100)
			{
				m_HealCo = 0;
				m_PlayerState = PLAYER_STATE_GROUND;
				m_HealAnmFlg = false;
				m_HealFlg = false;
			}
		}

	}

}

void Player::UpdateDamege(void)
{
	EnemyRemoteAttack* remoteAttack = m_Scene->GetGameObject<EnemyRemoteAttack>();
	
	if (remoteAttack != NULL)
		remoteAttack->SetDestoryFlg(true);


	if (m_NextAnimationName != "Damege")
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Damege";
		m_BlendRate = 1.0f;

		m_DamegeCoFlg = true;
	}

	if (m_DamegeCoFlg == true)
	{

		m_DamegeCo++;

		m_Position -= GetForwardQ() * 0.1f;


		if (m_DamegeCo >= 40)
		{
			m_PlayerState = PLAYER_STATE_GROUND;

			int random = (int)rand();
			//ランダムで2パターンのSE再生
			if(random % 2 == 0)
				m_DamageSE_1->Play();
			else if (random % 2 == 1)
				m_DamageSE_2->Play();


			m_Damage = false;
			m_Enemyattack01 = false;
			m_DamegeCo = 0;
			m_DamegeCoFlg = false;


		}
	}
}

void Player::UpdateAvoidace(void)
{
	Camera* camera = m_Scene->GetGameObject<Camera>();

	if (m_NextAnimationName != "Avoid")
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "Avoid";
		m_BlendRate = 1.0f;
		m_AvoidFlg = true;
	}

	if (m_AvoidFlg == true)
	{
		m_AvoidCo++;
		if (m_FrontAvoid == true)
		{
			D3DXVECTOR3 cameraFoward = camera->GetForward();
			cameraFoward.y = 0.0f;
			D3DXVec3Normalize(&cameraFoward, &cameraFoward);

			m_Position += cameraFoward * 0.1f;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(cameraFoward.x, cameraFoward.z);
			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			//m_Quaternion = quat;
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);
		}

		else if (m_BackAvoid == true)
		{
			D3DXVECTOR3 cameraFoward = camera->GetForward();
			cameraFoward.y = 0.0f;
			D3DXVec3Normalize(&cameraFoward, &cameraFoward);

			m_Position -= cameraFoward * 0.1f;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(cameraFoward.x, -cameraFoward.z);
			D3DXQuaternionRotationAxis(&quat, &axis, -angle);
			//m_Quaternion = quat;
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);
		}

		else if (m_LeftAvoid == true)
		{
			D3DXVECTOR3 cameraFoward = camera->GetRight();
			cameraFoward.y = 0.0f;
			D3DXVec3Normalize(&cameraFoward, &cameraFoward);

			m_Position -= cameraFoward * 0.1f;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(cameraFoward.x, -cameraFoward.z);

			D3DXQuaternionRotationAxis(&quat, &axis, -angle);
			//m_Quaternion = quat;
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);
		}

		else if (m_RightAvoid == true)
		{
			D3DXVECTOR3 cameraFoward = camera->GetRight();
			cameraFoward.y = 0.0f;
			D3DXVec3Normalize(&cameraFoward, &cameraFoward);

			m_Position += cameraFoward * 0.1f;

			D3DXQUATERNION quat;
			D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			float angle = atan2f(cameraFoward.x, cameraFoward.z);

			D3DXQuaternionRotationAxis(&quat, &axis, angle);
			//m_Quaternion = quat;
			D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.3f);

		}

		if (m_AvoidCo >= 120)
		{
			m_FrontAvoid = false;
			m_BackAvoid = false;
			m_RightAvoid = false;
			m_LeftAvoid = false;
			m_AvoidCo = 0;
			m_AvoidFlg = false;
			m_PlayerState = PLAYER_STATE_GROUND;
		}
	}
}

void Player::UpdateScared(void)
{
	if (m_ScaredStart == true)
	{
		if (m_NextAnimationName != "Scared")
		{
			m_Time = 0.0f;
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Scared";
			m_BlendRate = 1.0f;
			m_ScaredFlg = true;
		}

		if (m_ScaredFlg == true)
		{
			m_ScaredCo++;
			Scene* scene = Manager::GetScene();

			auto camera = scene->GetGameObject<Camera>();
			camera->Shake(0.08f); //0.05

			if (m_ScaredCo >= 100)
			{
				m_ScaredCo = 0;
			}
		}
	}
	else {
		m_ScaredFlg = false;
		m_PlayerState = PLAYER_STATE_GROUND;

	}
}

void Player::UpdateMountMode()
{
	if (m_NextAnimationName != "SowrdMount")
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "SowrdMount";
		m_BlendRate = 0.0f;
		m_MountFlg01 = true;
		m_BGM4->Play(false);
		m_BGM4->Volume(0.1f);
	}

	if (m_MountFlg01)
	{
		m_MountCo++;

		if (m_MountCo >= 50)
		{
			m_MountCo = 0;
			m_SetUpFlg02 = false;
			m_MountFlg01 = false;
			m_MountFlg = false;
			m_PlayerState = PLAYER_STATE_GROUND;
		}
	}

}
void Player::UpdateSetUpMode()
{
	if (m_NextAnimationName != "SowrdSetUp")
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "SowrdSetUp";
		m_BlendRate = 0.0f;
		m_SetUpFlg01 = true;
		m_BGM3->Play(false);
		m_BGM3->Volume(0.1f);
	}

	if (m_SetUpFlg01)
	{
		m_SetUpCo++;
		if (m_SetUpCo >= 10)
		{
			m_SetUpCo = 0;
			m_SetUpFlg01 = false;
			m_SetUpFlg02 = true;
			m_SetUpFlg = false;
			m_PlayerState = PLAYER_STATE_GROUND;
		}
	}

}


//プレイヤーの特殊攻撃
void Player::UpdateSpecialAttack(void)
{
	SpecialAttack01* attack01;
	SpecialAttack02* attack02;
	SpecialAttack03* attack03;
	Ui01* ui = m_Scene->GetGameObject< Ui01>();

	if (m_SpecialAttackCo == 0)
	{
		m_SAVoiceSE->Play();
	}
	
	if (m_NextAnimationName != "SpecialAttack")
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "SpecialAttack";
		m_BlendRate = 0.0f;
		m_SpecialAttackCoFlg = true;
	}

	if (m_SpecialAttackCoFlg)
	{
		m_SpecialAttackCo++;

		ui->SetSpescalAttackScaleMin(0.5f);

		if(ui->GetSpescalAttackScale() <= 0)
			ui->SetSpescalAttackScale(0.0f);

		//剣が地面についたとき
		if (m_SpecialAttackCo == 100)
		{
			m_SALandingSE->Play();
		}

		//特殊攻撃オブジェクトを順番に生成していく
		if (m_SpecialAttackCo == 150)
		{
			attack01 = m_Scene->AddGameObject< SpecialAttack01>(1);
			m_SAttackSE_1->Play();
			m_SAttackSE_1->Volume(0.6f);
		}

		if (m_SpecialAttackCo == 170)
		{
			attack02 = m_Scene->AddGameObject< SpecialAttack02>(1);
			m_SAttackSE_2->Play();
		}

		if (m_SpecialAttackCo == 190)
		{
			attack03 = m_Scene->AddGameObject< SpecialAttack03>(1);
			m_SAttackSE_1->Play();
		}

		attack01 = m_Scene->GetGameObject< SpecialAttack01>();
		attack02 = m_Scene->GetGameObject< SpecialAttack02>();
		attack03 = m_Scene->GetGameObject< SpecialAttack03>();

		if (m_SpecialAttackCo > 190)
		{
			if (m_NextAnimationName != "SpecialAttack2")
			{
				m_Time = 0.0f;
				m_AnimationName = m_NextAnimationName;
				m_NextAnimationName = "SpecialAttack2";
				m_BlendRate = 0.0f;
			}		
		}

		if (m_SpecialAttackCo > 350)
		{
			attack01->SetDestroy();
			attack02->SetDestroy();
			attack03->SetDestroy();

			m_SpecialAttackCo = 0;
			m_SpecialAttackFlg = false;
			m_PlayerState = PLAYER_STATE_GROUND;
		}

	}

}


void Player::UpdatePlayerEnd(void)
{
	if (m_NextAnimationName != "PlayerEnd")
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "PlayerEnd";
		m_BlendRate = 0.0f;
		m_PlayerEndFlg = true;
	}

	if (m_PlayerEndFlg)
	{
		m_PlayerEndCo++;
	}
}

void Player::UpdatePlayerEnd2(void)
{
	if (m_NextAnimationName != "PlayerEnd2")
	{
		m_Time = 0.0f;
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = "PlayerEnd2";
		m_BlendRate = 0.0f;
	}

}

