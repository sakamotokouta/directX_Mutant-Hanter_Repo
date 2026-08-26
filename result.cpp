#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "title.h"
#include "result.h"
#include "resultLogo.h"
#include "input.h"
#include "fade.h"
#include "village.h"

ResultLogo* resurt;

void Result::Init()
{
	// polygon
	m_Fade = AddGameObject<Fade>(2);
	resurt = AddGameObject<ResultLogo>(2);
}

void Result::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN))
	{
		m_Fade->FadeOut();
	}
	if (m_Fade->GetFadeFinish())
	{
		Manager::SetScene<Village>();
	}
}

void Result::Draw()
{
	resurt->Draw();
	m_Fade->Draw();
}
