#include "stdafx.h"
#include "Astar.h"

HRESULT Astar::init()
{
	//��ü��� �ʱ�ȭ
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			//���ο� ���� ��Ʈ��ġ ����
			totalNode[x][y] = new node(x, y); //�ε���
			totalNode[x][y]->rc = RectMake(5 + x * 20, 5 + y * 20, 20, 20);
		}
	}
	
	//ùŬ���� ¦���� �ǰ� �ϱ����� -1�� �ʱ�ȭ
	//�������� ¦���� �ǰ� �ϱ�����
	count = -1;
	//�� ã�ҳ�?
	isFind = false;


	

	return S_OK;
}

void Astar::release()
{

}

void Astar::update()
{
	//����, ���� ����
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//����, ���� ��尡 �̹� ���õǾ��ִٸ� �׳� ������
		if (startNode && endNode) return; //���� ������ ������Ʈ ����

		for (int y = 0; y < MAX_Y; y++)
		{
			for (int x = 0; x < MAX_X; x++)
			{
				//��Ʈ �浹ó��
				if (PtInRect(&totalNode[x][y]->rc, _ptMouse))
				{
					count++;
					if (count % 2 == 0) //ī��Ʈ�� -1���� 0�� �Ǳ⶧���� ó�� Ŭ���� 0 �׷��� ��������
					{
						totalNode[x][y]->nodeState = NODE_START;
						startNode = totalNode[x][y];
					}
					else
					{
						totalNode[x][y]->nodeState = NODE_END;
						endNode = totalNode[x][y];
					}

				}
			}
		}
	}

	//�� ���� ( ���� ���� ��� �������� �������� ���ϰ� ���� ) 
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON) && startNode && endNode)
	{

		for (int y = 0; y < MAX_Y; y++)
		{
			for (int x = 0; x < MAX_X; x++)
			{
				//��Ʈ �浹ó��
				if (PtInRect(&totalNode[x][y]->rc, _ptMouse))
				{
					//���۳��, ������� �������� ���ϰ� ����
					if (totalNode[x][y]->nodeState == NODE_START) continue;
					if (totalNode[x][y]->nodeState == NODE_END) continue;					
					totalNode[x][y]->nodeState = NODE_WALL;
				}
			}
		}
	}


	//��ã�� ����
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		this->pathFinding();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		//count = -1;
		this->init();
	}

}

void Astar::render()
{
	//��ü��� ����
	char str[128];
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			//���ο� ���� ��Ʈ��ġ ����
			Rectangle(getMemDC(), totalNode[x][y]->rc );

			//���۳�� �����ֱ�
			if (totalNode[x][y]->nodeState == NODE_START)
			{
				this->setNodeColor(startNode, RGB(255, 0, 0));
				TextOut(getMemDC(), startNode->rc.left + 100, startNode->rc.top + 10, "START", strlen("START"));					
			}
			//������ �����ֱ�
			if (totalNode[x][y]->nodeState == NODE_END)
			{
				this->setNodeColor(endNode, RGB(0, 0, 255));
				TextOut(getMemDC(), endNode->rc.left + 100, endNode->rc.top + 10, "END", strlen("END"));
			}
			//����� �����ֱ�
			if (totalNode[x][y]->nodeState == NODE_WALL)
			{
				this->setNodeColor(totalNode[x][y], RGB(0, 0, 0));
				TextOut(getMemDC(), totalNode[x][y]->rc.left + 100, totalNode[x][y]->rc.top + 10, "WALL", strlen("WALL"));
			}

			//��ü ����� �ε��� �����ֱ�
			sprintf(str, "%d, %d", totalNode[x][y]->idx, totalNode[x][y]->idy);
			TextOut(getMemDC(), totalNode[x][y]->rc.left + 10, totalNode[x][y]->rc.top + 10, str, strlen(str));
		}
	}

	if (isFind)
	{
		for (int i = 0; i < vFinalList.size(); i++)
		{
			setNodeColor(vFinalList[i], RGB(200, 200, 0));
			sprintf(str, "[%d, %d]      %d��° ���", vFinalList[i]->idx, vFinalList[i]->idy, i+1);
			TextOut(getMemDC(), vFinalList[i]->rc.left + 10, vFinalList[i]->rc.top + 30, str, strlen(str));
			sprintf(str, "F:%d, G:%d, H:%d", vFinalList[i]->F, vFinalList[i]->G, vFinalList[i]->H);
			TextOut(getMemDC(), vFinalList[i]->rc.left + 10, vFinalList[i]->rc.top + 50, str, strlen(str));
		}
	}
}

//��� ��ä��� (���������� ��ĥ��)
void Astar::setNodeColor(node * node, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	FillRect(getMemDC(), &node->rc, brush);
	DeleteObject(brush);
	FrameRect(getMemDC(), node->rc, RGB(0, 0, 0));
}
//*�߿�*//
//��ã�� �Լ�
void Astar::pathFinding()
{
	//���۳�� �� ���� ��尡 �ִ� ��쿡�� ��ã��
	if (!startNode || !endNode) return;	//����������

	//��ã�� ����
	//�˻��� �Ϸ��� ������ ���¸���Ʈ�� ��Ƶΰ� F�� H �� �������� ���� ã�Ƽ� �׳��� ������� �����ϰ� ���¸���Ʈ���� ������� �����ϰ� ������� Ŭ�����Ʈ�� ��Ƶд�

	//1. ���۳�尡 �־�� ����� �����ϴ� ���۳�带 ���¸���Ʈ�� ����ش�
	vOpenList.push_back(startNode);

	//2. ���¸���Ʈ�� ��� �ִ� ���͸� �˻��ؼ� �����忡 �����ҋ����� ���ѷ���
	while (vOpenList.size() > 0) //��ŸƮ�븣�� ������ �̰��� ����
	{
		curNode = vOpenList[0];

		//���¸���Ʈ �� ���� F�� �۰ų� F�� ���ٸ�  H�� ���� �� ����븣�� �ϰ� �����带 ���¸���Ʈ���� Ŭ���� ����Ʈ�� �ű��
		//�񱳸� �Ϸ��� �ϸ� �ּ� ���۳�忡�� �ֺ��� Ž���� ���� ��ã�Ⱑ ���۵Ǵ� 1���� ��������
		for (int i = 1; i < vOpenList.size(); i++)
		{
			if (vOpenList[i]->F <= curNode->F && vOpenList[i]->H < curNode->H)
			{
				curNode = vOpenList[i];
			}
		}

		//Ŭ�����Ʈ�� �־��ش�
		for (int i = 0; i < vOpenList.size(); i++)
		{
			if (curNode == vOpenList[i])
			{
				this->delOpenList(i);
				vCloseList.push_back(curNode);
			}
		}

		//������� ������ ���� ���� == �� ã�ҳ�?
		if (curNode == endNode)
		{
			node* _endNode = endNode;
			vector <node*> tempNode;
			while (_endNode != startNode)
			{
				tempNode.push_back(_endNode);
				_endNode = _endNode->parentNode;
			}

			//STL����Ʈ�� �̿��ϸ� reverse() ����ϰų�, push_front()�� ���
			//�츰 ���͸� �̿��ϴ� �Ųٷ� Ǫ�ù� ���ش�
			for (int i = tempNode.size() - 1; i > 0; i--)
			{
				vFinalList.push_back(tempNode[i]);
			}
			isFind = true;
			//�����ϰ� ����������
			return;
		}

		// �����¿� ( ������ ��� x) �ֺ� Ÿ�� ��� ���¸���Ʈ�� �־ �˻� �� ����
		this->addOpenList(curNode->idx, curNode->idy - 1); //��
		this->addOpenList(curNode->idx, curNode->idy + 1); //��
		this->addOpenList(curNode->idx - 1, curNode->idy); //��
		this->addOpenList(curNode->idx + 1, curNode->idy); //��
		
		//���� �밢���� �˻� ����
		this->addOpenList(curNode->idx- 1, curNode->idy - 1); //�»�
		this->addOpenList(curNode->idx- 1, curNode->idy + 1); //����
		this->addOpenList(curNode->idx + 1, curNode->idy - 1); //���
		this->addOpenList(curNode->idx + 1, curNode->idy + 1); //����
	}
}
//���¸���Ʈ�� �߰� �Լ�
void Astar::addOpenList(int idx, int idy)
{
	//����ó��
	//���¸���Ʈ�� ���� ��尡 ��ü��� �ε��� ������ ������ �߰����� ���ϰ� ó���Ѵ�(�ε��� ������ 0~ 4)
	if (idx < 0 || idx >MAX_X || idy < 0 || idy > MAX_Y) return;
	//��ֹ��� ���¸���Ʈ�� ���� �� ����
	if (totalNode[idx][idy]->nodeState == NODE_WALL) return;
	//Ŭ�����Ʈ�� �ִٸ� �̹� ������ ���̴� ������ �ȵȴ�
	for (int i = 0; i < vCloseList.size(); i++)
	{
		if (totalNode[idx][idy] == vCloseList[i]) return;
	}

	//������� �͝��� ������ ������ ���� ���¸���Ʈ�� �߰��ϱ�
	//���� ��� 4���� ��带 �̿������ �ϰ� ���� = 10, �밢�� 14���
	node* neightNode = totalNode[idx][idy];
	int moveCost = curNode->G + (curNode->idx - idx == 0 || curNode->idy - idy == 0) ? 10 : 14;  //�ε������� �ε��� ������ 0 �̸� �������� �̵��� �� + 10 // �ƴϸ� �밢�̵��̴� +14
	//���¸���Ʈ�ȿ� �̿���尡 ������ �ȵȴ�
	for (int i = 0; i < vOpenList.size(); i++)
	{
		if (vOpenList[i] == neightNode) return;
	}

	//�����¤����� ��������Ʈ���� ���� ��� G, H, ParentNode ������ ���¸���Ʈ�� �߰�
	neightNode->G = moveCost;
	neightNode->H = (abs(neightNode->idx - endNode->idx) + abs(neightNode->idy - endNode->idy) * 10); // adb�� ���밪 ���
	neightNode->F = neightNode->G + neightNode->H;
	neightNode->parentNode = curNode;
	vOpenList.push_back(neightNode);


}
//���¸���Ʈ ����
void Astar::delOpenList(int index)
{
	vOpenList.erase(vOpenList.begin() + index);
}
