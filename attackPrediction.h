#pragma once
#pragma once

#include "gameObject.h"

class AttackPrediction : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	class Model* m_Model{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetWeaponPos(D3DXVECTOR3 pos) { m_Position = pos; }
};