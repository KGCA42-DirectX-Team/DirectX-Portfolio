#include "CTextureMgr.h"

bool CTexture::LoadTextureFile(ID3D11Device* pDevice, std::wstring FileName)
{
    auto ImageObj = std::make_unique<DirectX::ScratchImage>();
    DirectX::TexMetadata mData;
    HRESULT hr = DirectX::GetMetadataFromDDSFile(FileName.c_str(), DirectX::DDS_FLAGS_NONE, mData);
    if (SUCCEEDED(hr))
    {
        hr = DirectX::LoadFromDDSFile(FileName.c_str(), DirectX::DDS_FLAGS_NONE, &mData, *ImageObj);
        if (SUCCEEDED(hr))
        {
            hr = DirectX::CreateShaderResourceView(pDevice, ImageObj->GetImages(),
                ImageObj->GetImageCount(),
                mData,&m_pTextureSRV);
            if (SUCCEEDED(hr))
            {
                return true;
            }
        }
    }
    hr = DirectX::GetMetadataFromWICFile(FileName.c_str(), DirectX::WIC_FLAGS_NONE, mData);
    if (SUCCEEDED(hr))
    {
        hr = DirectX::LoadFromWICFile(FileName.c_str(), DirectX::WIC_FLAGS_NONE, &mData, *ImageObj);
        if (SUCCEEDED(hr))
        {
            hr = DirectX::CreateShaderResourceView(pDevice, ImageObj->GetImages(),
                ImageObj->GetImageCount(),
                mData, &m_pTextureSRV);
            if (SUCCEEDED(hr))
            {
                return true;
            }
        }
    }

    hr = DirectX::GetMetadataFromTGAFile(FileName.c_str(), DirectX::TGA_FLAGS_NONE, mData);
    if (SUCCEEDED(hr))
    {
        hr = DirectX::LoadFromTGAFile(FileName.c_str(), DirectX::TGA_FLAGS_NONE, &mData, *ImageObj);
        if (SUCCEEDED(hr))
        {
            hr = DirectX::CreateShaderResourceView(pDevice, ImageObj->GetImages(),
                ImageObj->GetImageCount(),
                mData, &m_pTextureSRV);
            if (SUCCEEDED(hr))
            {
                return true;
            }
        }
    }



    return false;
}

bool CTexture::Release()
{
    if (m_pTextureSRV)m_pTextureSRV->Release();
    m_pTextureSRV = nullptr;
    return true;
}

bool CTextureMgr::Set(ID3D11Device* pDevice, ID3D11DeviceContext* pImmediateContext)
{
    m_pDevice = pDevice;
    m_pImmediateContext = pImmediateContext;
    return true;
}

const CTexture* CTextureMgr::Load(std::wstring FileName)
{
    std::size_t found = FileName.find_last_of(L"/");
    std::wstring path = FileName.substr(0,found+1);
    std::wstring Key = FileName.substr(found + 1);
    const CTexture* data = GetPtr(Key);

    if (data != nullptr)
    {
        return data;

    }
    CTexture* NewData = new CTexture;
    if (NewData->LoadTextureFile(m_pDevice.Get(), FileName))
    {
       
        m_List.insert(std::make_pair (Key,NewData));
        return NewData;
    }
    delete NewData;

    return nullptr;
}

const CTexture* CTextureMgr::GetPtr(std::wstring FileName)
{
    auto iter = m_List.find(FileName);
    if (m_List.end() == iter)
    {
        return nullptr;
    }

    return iter->second;
}

bool CTextureMgr::Get(std::wstring FileName, CTexture& texture)
{
    auto iter = m_List.find(FileName);
    if (m_List.end() == iter)
    {
        return false;
    }
    texture = *(iter->second);

    return true;
}

bool CTextureMgr::Release()
{
    for (auto& data : m_List)
    {
        data.second->Release();
        delete data.second;

    }
    m_List.clear();
    return true;
}

CTextureMgr::CTextureMgr()
{

}

CTextureMgr::~CTextureMgr()
{
    Release();
    
    
}