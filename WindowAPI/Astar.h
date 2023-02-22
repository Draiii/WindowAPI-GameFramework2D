#pragma once
#include "gameNode.h"

#define MAX_X 40
#define MAX_Y 40


//Ÿ�ϰ�
enum NODESTATE
{
	NODE_START,
	NODE_END,
	NODE_WALL,
	NODE_EMPTY
};

//��� Ŭ����
class node 
{
private:
	//���� GETTER, SETTER ���� ���� �ؾ������� �������� �ۺ��� ������
	//���̽�Ÿ���� �⿪�ؾ� �� 2����
	//1. ���(F, G, H)
	//2. �θ��� ������(��������� ������)
public:
	RECT rc;				//��Ʈ
	int idx, idy;			//�ε��� x, y
	int F, G, H;			//F = G + H //G = ���� to ���� // H = ���� to ����
	node* parentNode;		//�θ� ����ų ��� (�������)
	NODESTATE nodeState;	//����� ����(����, ����, ��, ����)

	 
	//��� ������
	node() {}
	//������ �����ε��� ���� �ʱ�ȭ
	node(int _idx, int _idy)
	{
		idx = _idx;
		idy = _idy;
		F = G = H = 0;
		nodeState = NODE_EMPTY;
		parentNode = NULL;
	}

	//��� �Ҹ���
	~node() {}
};




class Astar :	public gameNode
{
private:

	node* totalNode[MAX_X][MAX_Y];	//��ü ��� 25��
	node* startNode;				//���۳��	
	node* endNode;					//������
	node* curNode;					//������  - ��ó���� ���۳�� = ������
	
	vector <node*> vOpenList;		//���¸���Ʈ (Ž���� ��带 ��Ƶ� ����)
	vector <node*> vCloseList;		//Ŭ�����Ʈ (���¸���Ʈ�� �ִܰŸ�(�̹�Ž���Ϸ���) ��带 ������ Ŭ�����Ʈ ���Ϳ� ��´�)
	vector <node*> vFinalList;		//���̳θ���Ʈ (��ã�� �� Ŭ�����Ʈ�� ����ִ� ������ ������ ��ų �뵵)

	int count;						//����, ���� ����ѹ����� �����ϱ� ���� ����
	bool isFind;					//�� ã�ҳ�?

	

public:

	HRESULT init();
	void release();
	void update();
	void render();


	//��� ��ä��� (���������� ��ĥ��)
	void setNodeColor(node* node, COLORREF color);

	//*�߿�*//
	//��ã�� �Լ�
	void pathFinding();
	//���¸���Ʈ�� �߰� �Լ�
	void addOpenList(int idx, int idy);
	//���¸���Ʈ ����
	void delOpenList(int index);

	Astar() : startNode(NULL), endNode(NULL) {}
	~Astar() {}
};

