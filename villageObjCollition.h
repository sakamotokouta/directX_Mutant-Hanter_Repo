#pragma once
#pragma once

#include "gameObject.h"

class VillageObjCollition : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	D3DXVECTOR3 m_pos{};
	D3DXVECTOR3 m_scale{};

	class SpriteField* tile{};
	class Scene* m_Scene{};

public:

	void ObjCollition(void);
};