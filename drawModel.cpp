#include "main.h"
#include "renderer.h"
#include "drawModel.h"

void DrawModel::Init(const char* model)
{
	m_Model = new Model();
	m_Model->Load(model);

	m_DrawFlg = true;
}

void DrawModel::Uninit()
{
	m_Model->Unload();
	delete m_Model;
}

void DrawModel::Update()
{
}

void DrawModel::Draw()
{
	if(m_DrawFlg)
		m_Model->Draw();
}
