#pragma once
#include"CDefine.h"
#include"CoreInterface.h"
class CTexture
{

	ID3D11ShaderResourceView* m_pTextureSRV = nullptr;
	
public:
	std::wstring   m_csName;
	std::wstring   m_csPath;
	bool Apply(ID3D11DeviceContext* pImmediateContext, int iSlot) const
	{

		CoreInterface::g_pImmediateContext->PSSetShaderResources(iSlot, 1, &m_pTextureSRV);
		return true;
	}
	bool LoadTextureFile(ID3D11Device* pDevice, std::wstring FileName);
	
	bool Release();


};




class CTextureMgr
{
public:
	ComPtr<ID3D11Device> m_pDevice ;
	ComPtr<ID3D11DeviceContext> m_pImmediateContext ;
	std::map < std::wstring, CTexture*> m_List;

public:

	bool Set(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext);
	const CTexture* Load(std::wstring FileName);
	const CTexture* GetPtr(std::wstring FileName);
	bool Get(std::wstring FileName,CTexture& texture);
	bool Release();
	static CTextureMgr& GetInstance()
	{
		static CTextureMgr Texture;
		return Texture;

	}

private:
	CTextureMgr();
public:

	virtual ~CTextureMgr();


};

