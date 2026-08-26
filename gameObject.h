#pragma once

#include <list>
#include "component.h"
#include "renderer.h"


class GameObject
{
protected:
	bool m_Destroy = false;

	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	bool m_ShadowFlg{};

	D3DXMATRIX m_WorldMatrix;

	D3DXQUATERNION m_Quaternion = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);

	std::list<Component*> m_Component;

	//collition
	D3DXVECTOR3 m_MatrixPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_MatrixScale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_MatrixForward = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_MatrixRight = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_MatrixUp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


public:

	bool GetShadowFlg(void) { return m_ShadowFlg; }


	void SetDestroy()
	{
		m_Destroy = true;
	}

	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	void SetPosition(D3DXVECTOR3 pos) { m_Position = pos; }
	void SetRotation(D3DXVECTOR3 rot) { m_Rotation = rot; }
	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; }

	D3DXVECTOR3 GetPosition() { return m_Position; }
	D3DXVECTOR3 GetRotation() { return m_Rotation; }
	D3DXVECTOR3 GetScale() { return m_Scale; }

	// 前方向ベクトル取得
	D3DXVECTOR3 GetForward()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	// 右方向ベクトル取得
	D3DXVECTOR3 GetRight()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._11;
		forward.y = rot._12;
		forward.z = rot._13;

		return forward;
	}

	// 上方向ベクトル取得
	D3DXVECTOR3 GetTop()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		D3DXVECTOR3 forward;
		forward.x = rot._21;
		forward.y = rot._22;
		forward.z = rot._23;

		return forward;
	}


	// 前方向ベクトル取得
	D3DXVECTOR3 GetForwardQ()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);

		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	// 右方向ベクトル取得
	D3DXVECTOR3 GetRightQ()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);

		D3DXVECTOR3 forward;
		forward.x = rot._11;
		forward.y = rot._12;
		forward.z = rot._13;

		return forward;
	}

	// 上方向ベクトル取得
	D3DXVECTOR3 GetTopQ()
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);

		D3DXVECTOR3 forward;
		forward.x = rot._21;
		forward.y = rot._22;
		forward.z = rot._23;

		return forward;
	}

	D3DXMATRIX CalcLookAtMatrixAxisFix(
		D3DXMATRIX* rot,
		D3DXVECTOR3* pPos,
		D3DXVECTOR3* pLook,
		D3DXVECTOR3* pUp
	) {

		D3DXVECTOR3 X, Y, Z, D;
		D = *pLook - *pPos;
		D *= -1;
		D3DXVec3Normalize(&D, &D);
		D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, pUp), &D);
		D3DXVec3Normalize(&X, &X);
		D3DXVec3Normalize(&Z, D3DXVec3Cross(&Z, &X, &Y));

		rot->_11 = X.x; rot->_12 = X.y; rot->_13 = X.z; rot->_14 = 0;
		rot->_21 = Y.x; rot->_22 = Y.y; rot->_23 = Y.z; rot->_24 = 0;
		rot->_31 = Z.x; rot->_32 = Z.y; rot->_33 = Z.z; rot->_34 = 0;
		rot->_41 = 0.0f; rot->_42 = 0.0f; rot->_43 = 0.0f; rot->_44 = 1.0f;

		return *rot;
	}


	virtual void Init() {}

	virtual void Uninit()
	{
		for (Component* component : m_Component)
		{
			component->Uninit();
			delete component;
		}

		// リスト構造の削除
		m_Component.clear();
	}

	virtual void Update()
	{
		for (Component* component : m_Component)
		{
			component->Update();
		}
	}

	virtual void Draw()
	{
		if (m_ShadowFlg)
		{
			// テクスチャ設定
			ID3D11ShaderResourceView* depthShadowTexture = Renderer::GetDepthShadowTexture();
			Renderer::GetDeviceContext()->PSSetShaderResources(1, 1, &depthShadowTexture);
		}


		for (Component* component : m_Component)
		{
			component->Draw();
		}
	}

	// テンプレート関数
	template <typename T>
	T* AddComponet()
	{
		Component* componet = new T();
		m_Component.push_back(componet);
		componet->Init();

		return (T*)componet;
	}



	//collition
	D3DXVECTOR3 MatrixPosition(D3DXMATRIX matrix)
	{
		D3DXVECTOR3 pos;
		pos.x = matrix._41;
		pos.y = matrix._42;
		pos.z = matrix._43;
		return pos;
	}
	D3DXVECTOR3 MatrixScale(D3DXMATRIX matrix)
	{
		D3DXVECTOR3 scale;
		scale.x = matrix._11;
		scale.y = matrix._22;
		scale.z = matrix._33;
		return scale;
	}
	D3DXVECTOR3 MatrixForward(D3DXMATRIX matrix)
	{
		D3DXVECTOR3 forward;
		forward.x = matrix._31;
		forward.y = matrix._32;
		forward.z = matrix._33;
		return forward;
	}
	D3DXVECTOR3 MatrixRight(D3DXMATRIX matrix)
	{
		D3DXVECTOR3 right;
		right.x = matrix._11;
		right.y = matrix._12;
		right.z = matrix._13;
		return right;
	}
	D3DXVECTOR3 MatrixUp(D3DXMATRIX matrix)
	{
		D3DXVECTOR3 up;
		up.x = matrix._21;
		up.y = matrix._22;
		up.z = matrix._23;
		return up;
	}
	void SetCollider(D3DXMATRIX matrix)
	{
		m_MatrixPosition = MatrixPosition(matrix);
		m_MatrixScale = MatrixScale(matrix);
		m_MatrixForward = MatrixForward(matrix);
		m_MatrixRight = MatrixRight(matrix);
		m_MatrixUp = MatrixUp(matrix);
	}


	D3DXVECTOR3 GetMatrixPosition() { return m_MatrixPosition; }
	D3DXVECTOR3 GetMatrixScale() { return m_MatrixScale; }
	D3DXVECTOR3 GetMatrixForward() { return m_MatrixForward; }
	D3DXVECTOR3 GetMatrixRight() { return m_MatrixRight; }
	D3DXVECTOR3 GetMatrixUp() { return m_MatrixUp; }
	D3DXMATRIX GetMatrix() { return m_WorldMatrix; }

};