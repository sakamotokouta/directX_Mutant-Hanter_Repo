#pragma once

#include "gameObject.h"

class TreeObj : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	static class Model* m_Model;

public:

	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};