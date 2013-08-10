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
	if (x == 0 || y == 0) // ���겻��Ϊ0
		return NULL;

	int gx = x > 0 ? x - 1 : x + 1; // ͨ������ȡ�������±�
	int gy = y > 0 ? y - 1 : y + 1; // ͨ������ȡ�������±�

	if (abs(x) > m_nWidth || abs(y)> m_nHight)
	{
		int mx = gx / m_nWidth;	// ��ͼ���±�
		int my = gy / m_nHight;	// ��ͼ���±�
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
	if (x == 0 || y == 0) // ���겻��Ϊ0
		return NULL;

	int gx = x > 0 ? x - 1 : x + 1; // ͨ������ȡ�������±�
	int gy = y > 0 ? y - 1 : y + 1; // ͨ������ȡ�������±�

	if (abs(x) > m_nWidth || abs(y)> m_nHight)
	{
		int mx = gx / m_nWidth;	// ��ͼ���±�
		int my = gy / m_nHight;	// ��ͼ���±�
		return pGetSubMap(mx, my)->GetGrid(x - mx * m_nWidth, y - my * m_nHight); // ���ӵ�ͼ��ȥȡ����
	}
	return (CGrid*)pGetSubMap(gx, gy);
}
