#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "drawModel.h"
#include "input.h"
#include "scene.h"
#include "bullet.h"
#include "cylinder.h"
#include "box.h"
#include "score.h"
#include "animationModel.h"
#include "meshField.h"
#include "ui01.h"
#include "result.h"
#include "fade.h"
#include "explosion.h"
#include "weapon.h"
#include "enemyRemoteAttack.h"
#include "villageUi.h"
#include "receptionDesk.h"
#include "weaponStoreDesk.h"
#include "generalStoreDesk.h"
#include "titlePlayer.h"
#include "titleCamera.h"


void TitlePlayer::Init()
{
	m_Scene = Manager::GetScene();

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\DepthShadowMappingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\DepthShadowMappingPS.cso");


	m_Model = new AnimationModel;
	m_Model->Load("asset\\model\\Ganfaul M Aure.fbx");
	m_Model->LoadAnimation("asset\\model\\Male Sitting Pose.fbx", "Idle");

	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	m_Fade = m_Scene->AddGameObject<Fade>(2);

	m_ShadowFlg = true;

	m_Rotation.y = 3.0f;

	GameObject::Init();

}

void TitlePlayer::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_Model->Unload();
	delete m_Model;

	GameObject::Uninit();
}

void TitlePlayer::Update()
{
	TitleCamera* camera = m_Scene->GetGameObject<TitleCamera>();
	VillageUi* vui = m_Scene->GetGameObject<VillageUi>();
	RECEPTIONDESK* reception = m_Scene->GetGameObject<RECEPTIONDESK>();
	WeaponStoreDesk* weaponsotre = m_Scene->GetGameObject<WeaponStoreDesk>();
	GeneralStoreDesk* generalsotre = m_Scene->GetGameObject<GeneralStoreDesk>();


	//重力
	m_Velocity.y -= 0.015f;

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
	GameObject::Update();
}

void TitlePlayer::Draw()
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
	//D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	m_Matrix = scale * rot * trans;
	Renderer::SetWorldMatrix(&m_Matrix);

	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendRate);
	m_Time += 0.6f;  //0.4f

	m_BlendRate += 0.05f;

	if (m_BlendRate > 1.0f)
		m_BlendRate = 1.0f;

	m_Model->Draw();


	GameObject::Draw();
}