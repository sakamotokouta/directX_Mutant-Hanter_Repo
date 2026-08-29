#pragma once
#pragma once

#include "gameObject.h"

class LoadingLogo : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	class Sprit2D* m_OperationInfo{};

	D3DXVECTOR3 m_OperationInfoPos{};
	D3DXVECTOR3 m_OperationInfoScale{};



public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};