#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "loadingLogo.h"
#include "input.h"
#include "fade.h"
#include "loading.h"
#include "village.h"
#include "tutorial.h"
#include "villageUi.h"

#include <thread>


void Loading::Init()
{

	m_Fade = AddGameObject<Fade>(2);

	AddGameObject<LoadingLogo>(2);


	std::thread th1(&Game::Load);
	th1.detach();

	std::thread th2(&Tutorial::Load);
	th2.detach();

	std::thread th3(&Village::Load);
	th3.detach();

}

void Loading::Update()
{
	Scene::Update();

	if (Game::GetLoadFinish())
		m_Fade->FadeOut();

	if (m_Fade->GetFadeFinish() && VillageUi::GetGameSceneFlg())
		Manager::SetScene<Game>();


	if (Tutorial::GetLoardFinish())
		m_Fade->FadeOut();

	if (m_Fade->GetFadeFinish() && Village::GetTutorialFlg())
		Manager::SetScene<Tutorial>();

	if(Village::GetLoadFinish())
		m_Fade->FadeOut();

	if (m_Fade->GetFadeFinish() && !Village::GetTutorialFlg() && !VillageUi::GetGameSceneFlg())
		Manager::SetScene<Village>();

}

