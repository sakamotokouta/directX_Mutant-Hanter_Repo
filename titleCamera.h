#pragma once

#include "gameObject.h"

class TitleCamera : public GameObject
{
private:
	D3DXVECTOR3 m_Target{};
	D3DXMATRIX m_ViewMatrix{};
	D3DXMATRIX m_ProjectionMatrix;


	float m_ShakeOffset{};
	int   m_ShakeTime{};
	float m_ShakeAmplitude{};

	bool m_Porzu{};

public:
	void Init();
	void Update();
	void Draw();

	// 前方向ベクトル取得
	D3DXVECTOR3 GetForward()
	{
		D3DXMATRIX rot;
		//D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
		D3DXMatrixInverse(&rot, nullptr, &m_ViewMatrix);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	// 横方向ベクトル取得
	D3DXVECTOR3 GetRight()
	{
		D3DXMATRIX rot;
		//D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
		D3DXMatrixInverse(&rot, nullptr, &m_ViewMatrix);

		D3DXVECTOR3 forward;
		forward.x = rot._11;
		forward.y = rot._12;
		forward.z = rot._13;

		return forward;
	}

	D3DXMATRIX GetViewMatrix()
	{
		return m_ViewMatrix;
	}
	bool CheckView(D3DXVECTOR3 Position);

	void Shake(float Amplitude)
	{
		m_ShakeAmplitude = Amplitude;
	}
};