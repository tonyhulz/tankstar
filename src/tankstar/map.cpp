#include "stdafx.h"
#include "map.h"
CMap::CMap(int nWidth, int nHight)
{
	m_nWidth = nWidth;
	m_nHight = nHight;
	m_subMap = new CMap *[nWidth, nHight];
}

CMap::~CMap()
{
	delete[] m_subMap;
}

CMap * CMap::GetSubMap(int x, int y)
{
	if (x == 0 || y == 0) // 坐标不能为0
		return NULL;

	int gx = x > 0 ? x - 1 : x + 1; // 通过坐标取得数组下标
	int gy = y > 0 ? y - 1 : y + 1; // 通过坐标取得数组下标

	if (abs(x) > m_nWidth || abs(y)> m_nHight)
	{
		int mx = gx / m_nWidth;	// 子图的下标
		int my = gy / m_nHight;	// 子图的下标
		return pGetSubMap(mx, my);
	}
	return NULL;
}

CMap * CMap::pGetSubMap(int mx, int my)
{
	return m_subMap[my * m_nWidth + mx];
}

CGrid * CMap::GetGrid(int x, int y)
{
	if (x == 0 || y == 0) // 坐标不能为0
		return NULL;

	int gx = x > 0 ? x - 1 : x + 1; // 通过坐标取得数组下标
	int gy = y > 0 ? y - 1 : y + 1; // 通过坐标取得数组下标

	if (abs(x) > m_nWidth || abs(y)> m_nHight)
	{
		int mx = gx / m_nWidth;	// 子图的下标
		int my = gy / m_nHight;	// 子图的下标
		return pGetSubMap(mx, my)->GetGrid(x - mx * m_nWidth, y - my * m_nHight); // 在子地图中去取格子
	}
	return (CGrid*)pGetSubMap(gx, gy);
}
