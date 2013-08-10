#include <map>
using namespace std;

class CGrid
{
	// 地图中的格子，格子有自己的属性，属性分两部分，一个是静态属性，和其他格子公用，属性值不可被改变，此外还有自己特有的属性，可以被改变
public:
	int	m_static_info;	
	map<int, int> m_attribute;
};

class CMap : 
	public CGrid // 地图也是一种格子，也可以有自己的属性
{
	// 地图是可以级联的，大地图级联小地图，这个地图希望能
public:
	CMap ** m_subMap;
	int		m_nWidth;
	int		m_nHight;
				CMap(int nWidth, int nHight);
	virtual		~CMap();
	CGrid *		GetGrid(int x, int y);
	CMap *		GetSubMap(int x, int y);
private:
	CMap *		pGetSubMap(int mx, int my); // 通过地图下标取地图
};
