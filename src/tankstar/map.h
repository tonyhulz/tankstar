#include <map>
#include <list>
using namespace std;

class iEvent
{
	// �¼����࣬�����ڽ���֮��ͨѶ
public:
	int m_nType; // �¼�����
	int m_nLen; // �¼����ȣ�����������ʹ�õ��������
};
class iListen;
class iConnect
{
	// ���ӻ��࣬���ڷ����¼��ͽ����¼�
public:
	iListen * m_pListen; // ����ָ��
	virtual list<iEvent *> GetEvts() = 0; // ��ȡ�¼��б�����������¼��ĸ���
	virtual int SendEvt(iEvent * pEvent) = 0; // �����¼�
};

class iListen
{
	// ���������������ڽ����µ�����
public:
	virtual list<iConnect *> GetAccepts() = 0; // ��ȡ�������б�
};

class iNetworkMgr
{
	// ������������ͻ��˺ͷ�������ͬһ�����ȿ��Է������ӣ�����Դ�������������
public:
	virtual iConnect * ConnectTo(int nIp, int nPort) = 0; // ���ӵ�������
	virtual void Close(iConnect * pConnect) = 0; // �ر�һ������
	virtual iListen * Create(int nIp, int nPort) = 0; // ����һ������������
	virtual bool Release(iListen * pListen) = 0; // �ر�һ������������
};

enum EventId
{
	eAccept = 1,
};

class iNode
{
public:
	// �ڵ㣬���̿�ܵĻ���
	virtual iConnect * ConnectTo(int nIp, int nPort) = 0; // ���ӵ�������
	virtual void Close(iConnect * pConnect) = 0; // �ر�һ������
	virtual iListen * Create(int nIp, int nPort) = 0; // ����һ������������
	virtual bool Release(iListen * pListen) = 0; // �ر�һ������������
	virtual void OnEvt(iConnect * pConn, int nType, iEvent * pEvt) = 0; // �����¼��� ����¼������������ӣ����ӶϿ�������Ϣ
	void Process(int nTime)
	{
		// �������м����б�, ��ȡ�µ�����
		for (map<int, iListen*>::iterator listenIt = m_mapListen.begin(); listenIt != m_mapListen.end(); listenIt ++)
		{
			list<iConnect *> listAccepts = listenIt->second->GetAccepts();
			// ����ÿ������������µ����ӣ�֪ͨ�������¼������������б�
			for (list<iConnect *>::iterator connectIt = listAccepts.begin(); connectIt != listAccepts.end(); connectIt ++) 
			{
				m_mapConnect[(int)(*connectIt)] = *connectIt;
				OnEvt((*connectIt), eAccept, NULL);
			}
		}
		// �����������ӣ�ȡ�����������е���Ϣ���������Щ��Ϣ
		for (map<int, iConnect*>::iterator itConn = m_mapConnect.begin(); itConn != m_mapConnect.end(); itConn ++ )
		{
			list<iEvent *> listEvts = itConn->second->GetEvts();
			for (list<iEvent *>::iterator itEvt = listEvts.begin(); itEvt != listEvts.end(); itEvt ++)
			{
				OnEvt(itConn->second, (*itEvt)->m_nType, *itEvt);
			}
		}
	}
	map<int, iListen*> m_mapListen; // �����б�
	map<int, iConnect*> m_mapConnect; // �����б�
	iNetworkMgr * m_pNetworkMgr;
};

class iPorcessNode
{
public:
	// ����ڵ㣬 ��ʾһ�����̣�����֮��ͨ��������ͨѶ
	int Init() // �ڵ��ʼ��������һ���������������¼����������������̷����¼�
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
	// ��ͼ�еĸ��ӣ��������Լ������ԣ����Է������֣�һ���Ǿ�̬���ԣ����������ӹ��ã�����ֵ���ɱ��ı䣬���⻹���Լ����е����ԣ����Ա��ı�
public:
	int	m_static_info;	
	map<int, int> m_attribute;
};

class CMap : 
	public CGrid // ��ͼҲ��һ�ָ��ӣ�Ҳ�������Լ�������
{
	// ��ͼ�ǿ��Լ����ģ����ͼ����С��ͼ�������ͼϣ����
public:
	CMap ** m_subMap;
	int		m_nWidth;
	int		m_nHight;
				CMap(int nWidth, int nHight);
	virtual		~CMap();
	CGrid *		GetGrid(int x, int y);
	CMap *		GetSubMap(int x, int y);
	void DisPatchMsg(int x, int y, iEvent * pEvt) // �ַ�һ����Ϣ
	{

	}
private:
	CMap *		pGetSubMap(int mx, int my); // ͨ����ͼ�±�ȡ��ͼ
};

class MapDispatch
{
public:
	CMap * m_pMap;
	void DisPatchMsg(iEvent * pEvt)
	{
		//CGrid * pGrid = m_pMap->GetGrid();// �����ȡ�Ŀ�����һ�����ӣ�Ҳ�����ǿգ�����ǿվ���Ҫת����ȥ
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

