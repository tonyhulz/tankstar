#include <map>
using namespace std;

class iEvent
{
public:
	int m_nId;
	int m_nLen;
};

class iConnect
{
public:
	int m_nId;
	virtual iEvent * GetMsg(int nCount) = 0;
	virtual int Sendevt(iEvent * pEvent) = 0;
};

class iNetworkServer
{
public:
	virtual iConnect * GetAccept() = 0;
};

class iNetworkMgr
{
public:
	virtual iConnect * ConnectTo(int nIp, int nPort);
	virtual void Close(iConnect * pConnect);
	virtual iNetworkServer * Create(int nIp, int nPort) = 0;
	virtual bool Release(iNetworkServer * pServer) = 0;

};

class iPorcessNode
{
	int Init()
	{

	}
	int ProcessMsg(int nTime)
	{

	}
	iNetworkMgr * m_pNetworkMgr;
};

class iMapEvent
{
public:
	int m_x;
	int m_y;
};

class iDispatch
{
public:
};

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
	void DisPatchMsg(int x, int y, iEvent * pEvt) // 分发一个消息
	{

	}
private:
	CMap *		pGetSubMap(int mx, int my); // 通过地图下标取地图
};

class MapDispatch
{
public:
	CMap * m_pMap;
	void DisPatchMsg(iEvent * pEvt)
	{
		//CGrid * pGrid = m_pMap->GetGrid();// 这里获取的可能是一个格子，也可能是空，如果是空就需要转发出去
	}
	
};

class CEventMgr
{
public:
	void SendEvent(CMap * pMap, int nX,int nY, iEvent * pEvt)
	{

	};
	void ProcessEvent(CMap * pMap, int nX,int nY, iEvent * pEvt)
	{
		//SendEent(map, x,y,iEvent * pEvt)
	};

};

