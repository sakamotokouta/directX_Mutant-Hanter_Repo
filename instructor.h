#pragma once
#pragma once

#include "gameObject.h"
#include <string>
#include "animationModel.h"



class Instructor : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;
	ID3D11ShaderResourceView* m_DisolveTexture = nullptr;

	class AnimationModel* m_Model{};

	std::string m_AnimationName;

	std::string m_NextAnimationName;

	float m_BlendRate{};

	float m_Time;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

