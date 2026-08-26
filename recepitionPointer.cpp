#include "main.h"
#include "renderer.h"
#include "drawModel.h"
#include "recepitionPointer.h"
#include "receptionDesk.h"
#include "scene.h"
#include "manager.h"
#include "weaponStoreDesk.h"
#include "generalStoreDesk.h"
#include "villageInfoDesk.h"
#include "instructor.h"
#include "villagePlayerAction.h"

void RecepitionPointer::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "shader\\vertexLightingPS.cso");

	AddComponet<DrawModel>()->Init("asset\\model\\receptionPoint.obj");
	Scene* scene = Manager::GetScene();

	m_Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);

	m_ShadowFlg = true;


	GameObject::Init();
}

void RecepitionPointer::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void RecepitionPointer::Update()
{
	Scene* scene = Manager::GetScene();
	RECEPTIONDESK* reception = scene->GetGameObject< RECEPTIONDESK>();
	WeaponStoreDesk* weaponsotre = scene->GetGameObject< WeaponStoreDesk>();
	GeneralStoreDesk* generalsotre = scene->GetGameObject<GeneralStoreDesk>();
	VillageInfoDesk* villageinfo = scene->GetGameObject<VillageInfoDesk>();
	Instructor* instructor = scene->GetGameObject<Instructor>();
	VillagePlayerAction* vplayer = scene->GetGameObject<VillagePlayerAction>();



	if (vplayer->GetReceptionFlg())
		m_Position = D3DXVECTOR3(reception->GetPosition().x, reception->GetPosition().y + 2.0f, reception->GetPosition().z);

	if (vplayer->GetWeaponDeskFlg())
		m_Position = D3DXVECTOR3(weaponsotre->GetPosition().x, weaponsotre->GetPosition().y + 2.0f, weaponsotre->GetPosition().z);

	if (vplayer->GetGeneralDeskFlg())
		m_Position = D3DXVECTOR3(generalsotre->GetPosition().x, generalsotre->GetPosition().y + 2.0f, generalsotre->GetPosition().z);

	if (vplayer->GetVillageInfoPointFlg())
		m_Position = D3DXVECTOR3(villageinfo->GetPosition().x, villageinfo->GetPosition().y  + 2.1f, villageinfo->GetPosition().z);

	if(vplayer->GetInstructorFlg())
		m_Position = D3DXVECTOR3(instructor->GetPosition().x, instructor->GetPosition().y + 2.3f, instructor->GetPosition().z);



	GameObject::Update();
}

void RecepitionPointer::Draw()
{
	Scene* scene = Manager::GetScene();
	VillagePlayerAction* vplayer = scene->GetGameObject< VillagePlayerAction>();
	
	if (vplayer->GetReceptionFlg() || vplayer->GetWeaponDeskFlg() || 
		vplayer->GetGeneralDeskFlg() || vplayer->GetVillageInfoPointFlg() ||
		vplayer->GetInstructorFlg())
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
		world = scale * rot * trans;
		Renderer::SetWorldMatrix(&world);

		GameObject::Draw();
	}
}