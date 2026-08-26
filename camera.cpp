#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"camera.h"
#include"player.h"
#include"scene.h"
#include"input.h"
#include "enemy.h"
#include "villageUi.h"
#include "weaponStoreDesk.h"
#include "generalStoreDesk.h"
#include "receptionDesk.h"
#include "questGateObj.h"
#include "instructor.h"
#include "village.h"
#include "tutorial.h"

void Camera::Init()
{

	m_Position = D3DXVECTOR3(0.0f, 5.0f, -20.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation.y = 3.2f;
}
void Camera::Update()
{

	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	Enemy* enemy = scene->GetGameObject<Enemy>();
	VillageUi* vui = scene->GetGameObject<VillageUi>();
	WeaponStoreDesk* weaponsotre = scene->GetGameObject<WeaponStoreDesk>();
	GeneralStoreDesk* generalsotre = scene->GetGameObject<GeneralStoreDesk>();
	RECEPTIONDESK* questdesk = scene->GetGameObject<RECEPTIONDESK>();
	Instructor* instructor = scene->GetGameObject<Instructor>();
	QuestGateObj* questgate = scene->GetGameObject<QuestGateObj>();

	m_ShakeOffset = sinf(m_ShakeTime * 1.5f) * m_ShakeAmplitude;
	m_ShakeTime++;
	m_ShakeAmplitude *= 0.9f;


	if (!GetPozFlg())
		m_Rotation.y += -GetCursorX() / 600;

	m_Rotation.x = -5.1f;



	////////ゲームシーンでのカメラ処理//////////////
	if (enemy != NULL && enemy->GetEnemyState() == ENEMY_STATE_DIE)
	{
		m_Target = enemy->GetPosition();
		m_Position = m_Target - GetForward() * 5.0f + GetTop() * 2.0f;

		m_Rotation.y += 0.01f;
		if (m_Rotation.y >= m_OldRot.y + 3.0f)
		{
			m_Rotation.y = m_OldRot.y + 3.0f;
		}

	}
	else {

		m_OldRot = m_Rotation;
		m_Target = player->GetPosition();
		m_Position = m_Target - GetForward() * 5.0f + GetTop() * 2.0f;

		if (m_Rotation.y >= 6.412 || m_Rotation.y <= -6.422)
			m_Rotation.y = 0.0f;

	}

	/////////村シーンでのカメラ処理//////////////////
	if (Village::GetVillageFlg())
	{
		if (vui->GetWeaponSotreInfoFlg())
		{
			m_Rotation.y = 4.7f;

			m_Target = weaponsotre->GetPosition();
			m_Position = m_Target - GetForward() * 5.0f + GetTop() * 2.0f;

		}

		if (vui->GetGeneralSotreInfoFlg())
		{
			m_Target = generalsotre->GetPosition();
			m_Position = m_Target - GetForward() * 5.0f + GetTop() * 2.0f;
		}

		if (vui->GetQuestBoardInfoFlg())
		{
			m_Target = questdesk->GetPosition();
			m_Position = m_Target - GetForward() * 5.0f + GetTop() * 2.0f;
		}

		if (vui->GetTutorialInfoFlg())
		{
			m_Rotation.y = 3.2f;
			m_Target = instructor->GetPosition();
			m_Position = m_Target - GetForward() * 5.0f + GetTop() * 2.0f;
		}


		if (vui->GetQuestGateInfoFlg())
		{
			m_Rotation.y = 3.2f;
			m_Target = questgate->GetPosition();
			m_Position = m_Target - GetForward() * 12.0f + GetTop() * 2.0f;
		}

	}


}

void Camera::Draw()
{
	//ビューマトリクス設定
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 position = m_Position + D3DXVECTOR3(m_ShakeOffset, m_ShakeOffset, 0.0f);
	D3DXVECTOR3 target = m_Target + D3DXVECTOR3(m_ShakeOffset, m_ShakeOffset, 0.0f);

	D3DXMatrixLookAtLH(&m_ViewMatrix, &position, &target, &up);
	//m_target 注視点

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクションマトリックス設定
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f/*視野*/, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);

	Renderer::SetCameraPosition(m_Position);
}

bool Camera::CheckView(D3DXVECTOR3 Position)
{
	D3DXMATRIX vp, invvp;
	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);


	D3DXVECTOR3 v, v1, v2, n;

	v = Position - m_Position;

	//左面判定
	{
		v1 = wpos[0] - m_Position;
		v2 = wpos[2] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < 0.0f)
			return false;
	}

	//右面判定
	{
		v1 = wpos[3] - m_Position;
		v2 = wpos[1] - m_Position;
		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < 0.0f)
			return false;
	}

	return true;
}

