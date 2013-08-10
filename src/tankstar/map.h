#include <map>
using namespace std;

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
private:
	CMap *		pGetSubMap(int mx, int my); // ͨ����ͼ�±�ȡ��ͼ
};
