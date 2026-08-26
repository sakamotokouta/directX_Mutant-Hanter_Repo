#include"main.h"
#include"manager.h"
#include"renderer.h"
#include"player.h"
#include"scene.h"
#include"input.h"
#include "titleCamera.h"
#include "titlePlayer.h"

bool g_Porz3 = false;

void TitleCamera::Init()
{

	m_Position = D3DXVECTOR3(0.0f, 5.0f, -20.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rotation.y = 3.2f;

}
void TitleCamera::Update()
{

	Scene* scene = Manager::GetScene();
	TitlePlayer* player = scene->GetGameObject<TitlePlayer>();

	m_ShakeOffset = sinf(m_ShakeTime * 1.5f) * m_ShakeAmplitude;
	m_ShakeTime++;
	m_ShakeAmplitude *= 0.9f;


	//if (Input::GetKeyTrigger('J'))
	//	g_Porz3 = !g_Porz3;

	//if (g_Porz3)
	//	m_Rotation.y += -GetCursorX() / 600;

	////m_Rotation.x = -5.1f;
	
	m_Rotation.y = 8.9f;

	m_Rotation.x = -5.1f;

	m_Target = player->GetPosition();
	m_Position = m_Target - GetForward() * 3.0f + GetTop() * 2.0f;




}

void TitleCamera::Draw()
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
}

bool TitleCamera::CheckView(D3DXVECTOR3 Position)
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

