#pragma once
#pragma once

#include "gameObject.h"

class Tree : public GameObject
{
private:

	static ID3D11Buffer* m_VertexBuffer;
	static ID3D11ShaderResourceView* m_Texture;


	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	int m_Count{};

public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};