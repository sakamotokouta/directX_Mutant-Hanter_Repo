#pragma once

#include "model.h"
#include "gameObject.h"
#include <string>
#include "animationModel.h"

class TitlePlayer : public GameObject
{
private:

	class AnimationModel* m_Model{};
	class Scene* m_Scene{};
	class Audio* m_BGM{};
	class Fade* m_Fade{};

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	D3DXMATRIX m_Matrix{};

	D3DXVECTOR3 m_Velocity{};

	float m_BlendRate{};
	float m_Time;

	std::string m_AnimationName;
	std::string m_NextAnimationName;

	bool m_IsGround = false;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};