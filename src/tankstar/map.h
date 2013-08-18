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

