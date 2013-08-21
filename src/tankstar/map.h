#include <map>
#include <list>
using namespace std;

class iEvent
{
	// 事件基类，用于在进程之间通讯
public:
	int m_nType; // 事件类型
	int m_nLen; // 事件长度，用于网络层会使用到这个参数
};
class iListen;
class iConnect
{
	// 连接基类，用于发送事件和接收事件
public:
	iListen * m_pListen; // 监听指针
	virtual list<iEvent *> GetEvts() = 0; // 获取事件列表，输出参数是事件的个数
	virtual int SendEvt(iEvent * pEvent) = 0; // 发送事件
};

class iListen
{
	// 监听服务器，用于接收新的连接
public:
	virtual list<iConnect *> GetAccepts() = 0; // 获取新连接列表
};

class iNetworkMgr
{
	// 网络管理器，客户端和服务器用同一个，既可以发起连接，亦可以创建监听服务器
public:
	virtual iConnect * ConnectTo(int nIp, int nPort) = 0; // 连接到服务器
	virtual void Close(iConnect * pConnect) = 0; // 关闭一个连接
	virtual iListen * Create(int nIp, int nPort) = 0; // 创建一个监听服务器
	virtual bool Release(iListen * pListen) = 0; // 关闭一个监听服务器
};

enum EventId
{
	eAccept = 1,
};

class iNode
{
public:
	// 节点，进程框架的基类
	virtual iConnect * ConnectTo(int nIp, int nPort) = 0; // 连接到服务器
	virtual void Close(iConnect * pConnect) = 0; // 关闭一个连接
	virtual iListen * Create(int nIp, int nPort) = 0; // 创建一个监听服务器
	virtual bool Release(iListen * pListen) = 0; // 关闭一个监听服务器
	virtual void OnEvt(iConnect * pConn, int nType, iEvent * pEvt) = 0; // 处理事件， 这个事件可能是新连接，连接断开，新消息
	void Process(int nTime)
	{
		// 遍历所有监听列表, 获取新的连接
		for (map<int, iListen*>::iterator listenIt = m_mapListen.begin(); listenIt != m_mapListen.end(); listenIt ++)
		{
			list<iConnect *> listAccepts = listenIt->second->GetAccepts();
			// 遍历每个监听里面的新的连接，通知新连接事件，插入连接列表
			for (list<iConnect *>::iterator connectIt = listAccepts.begin(); connectIt != listAccepts.end(); connectIt ++) 
			{
				m_mapConnect[(int)(*connectIt)] = *connectIt;
				OnEvt((*connectIt), eAccept, NULL);
			}
		}
		// 遍历所有连接，取出所有连接中的消息，处理掉这些消息
		for (map<int, iConnect*>::iterator itConn = m_mapConnect.begin(); itConn != m_mapConnect.end(); itConn ++ )
		{
			list<iEvent *> listEvts = itConn->second->GetEvts();
			for (list<iEvent *>::iterator itEvt = listEvts.begin(); itEvt != listEvts.end(); itEvt ++)
			{
				OnEvt(itConn->second, (*itEvt)->m_nType, *itEvt);
			}
		}
	}
	map<int, iListen*> m_mapListen; // 监听列表
	map<int, iConnect*> m_mapConnect; // 连接列表
	iNetworkMgr * m_pNetworkMgr;
};

class iPorcessNode
{
public:
	// 处理节点， 表示一个进程，进程之间通过网络来通讯
	int Init() // 节点初始化，建立一个监听用来接收事件，可以项其他进程发送事件
	{

	}
	int ProcessMsg(int nTime)
	{

	}
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

