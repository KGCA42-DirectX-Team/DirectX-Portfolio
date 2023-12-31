#pragma once
#include"CMap.h"

class CHeightMap : public CMap
{
public:
	std::vector<float>		m_fHeightList;
public:
	bool CreateHeightMap(std::wstring HeightMapName);
	bool CreateMap(CMapDesc& MapDesc);
	float GetHeightVertex(UINT index);
	TVector4 GetColorVertex(UINT index);
	float GetHeightMap(int row, int col);
	bool CreateIndexBuffer(std::vector<DWORD> m_TreeIndexList);
	bool CheckSquare(int n);
	int ResizeMap(int n);
public:

};

