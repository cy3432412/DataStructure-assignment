#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//����ͷ�������ṹ
typedef struct HNode
	{
		char	roomN[7];	//�ͷ�����
		float   Price;		//��׼�۸�
		float   PriceL;	//��ס�۸�(Ĭ��ֵ=��׼�۸�*80%)
		int	   Beds;		//��λ��Beds
		char	   State[5];	//��ס״̬(ֵ��"����"��"��ס"��"Ԥ��"��Ĭ��ֵΪ"����")
		struct HNode  *next;	//ָ����
	}Hotel, *HLink;

void Build(HLink &H);    //�����ͷ���Ϣ������
void Exp(HLink H);      //���ȫ���ͷ���Ϣ
int Find(HLink &H, char *roomN);   //���ҿͷ����ƣ����ҵ����ؿͷ��������е�λ�ã���û�ҵ�����0
void updateH(HLink &H, int beds, char *state);   //����λ��Ϊbed�Ŀͷ�״̬��Ϊstate
void Add(HLink &H);  //����������δ��ס�Ŀͷ���ס�۸���Ӽ�20%
HLink FirstH(HLink &H);    //�ҵ���ס�۸���ߵĿͷ������ظýڵ�ָ�룬����ǰ���ýڵ�ɾ��
void MoveK1(HLink &H, int k);   //���������е�����k������Ƶ���һ�����λ��
void ReverseN2(HLink &H);    //������������м�λ�ý��֮���ȫ����㵹��
void SortPriceL(HLink &H);     //���տͷ�����ס�۸񣬿ͷ����ƣ���������
void upBed(HLink &H, int beds);  //����һ������λ��Ϊbeds���½�㡿��ʹ�������̬Ϊ����ͷ��㡿->����λ��>beds�Ľ�㡿->����λ��Ϊbeds���½�㡿->����λ��<=beds�Ľ�㡿

void main()
{
	HLink H;
	int choice;
	Build(H);
	while (1)
	{
		printf("��ѡ��ʹ�õĹ��ܣ�\n");
		printf("1.���ȫ���ͷ���Ϣ\t\t\t\t2.���ҿͷ�����\n");
		printf("3.����ָ����λ���Ŀͷ�����ס״̬\t\t4.δ��ס�Ŀͷ��Ӽ�20%%\n");
		printf("5.�ҵ��۸���ߵĿͷ�\t\t\t\t6.������k�䷿�ƶ�����һ���λ��\n");
		printf("7.���м�ͷ�֮��ķ���ȫ������\t\t\t8.���տͷ�����ס�۸񣬿ͷ����ƣ���������\n");
		printf("9.�����¿ͷ�\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			Exp(H);
			break;
		case 2:
		{
			printf("������Ҫ���ҵĿͷ�����:");
			char name[7];
			scanf("%s", name);
			int pos = Find(H, name);
			printf("�ͷ�����Ϊ%s�ķ����ڵ�%d��λ�ã�", name, pos);
			break;
		}
		case 3:
			printf("������Ҫ���ĵĿͷ��ķ�������");
			int bed;
			scanf("%d", &bed);
			printf("������Ҫ���ĵ�״̬\n");
			char state[5];
			scanf("%s", state);
			updateH(H, bed, state);
			break;
		case 4:
			Add(H);
			break;
		case 5:
		{
			HLink high = FirstH(H);
			break;
		}
		case 6:
			printf("������Ҫ�ƶ��Ŀͷ�λ�ã�");
			int k;
			scanf("%d", &k);
			MoveK1(H, k);
			break; 
		case 7:
			ReverseN2(H);
			break;
		case 8:
			SortPriceL(H);
			break;
		case 9:
			printf("�������¿ͷ���������");
			int beds;
			scanf("%d", &beds);
			upBed(H, beds);
			break;
		default:
			printf("���벻�Ϸ�\n");
		}
		printf("\n\n\n");
	}
}

void Build(HLink &H)
{
	FILE* input = fopen("D:\\�����ļ�.txt", "r");
	H = (HLink)malloc(sizeof(Hotel));
	H->next = NULL;
	HLink rear = H;
	while(!feof(input))
	{
		HLink p = (HLink)malloc(sizeof(Hotel));
		char roomn[7];
		fscanf(input, "%s%f%d", roomn, &p->Price, &p->Beds);
		strcpy(p->roomN, roomn);
		strcpy(p->State, "����");
		p->PriceL = p->Price * 0.8f;
		p->next = rear->next;
		rear->next = p;
		rear = p;
	}
	rear->next = NULL;
	fclose(input);
}

void Exp(HLink H)
{
	HLink p = H->next;
	printf("\n�ͷ���Ϣ���£�\n");
	printf("----------------------------------------------------\n");
	printf("������ ��׼�۸� ��ס�۸� ��λ�� ��ס״̬\n");
	while(p)
	{
		printf("%s %8.1f %8.1f %6d %8s\n",p->roomN,p->Price,p->PriceL,p->Beds,p->State);
		p = p->next;
	}
}

int Find(HLink &H, char *roomN)
{
	HLink p = H->next;   //ָ��pָ���׽ڵ�
	int pos = 1;
	while(p)
	{
		if(strcmp(p->roomN, roomN) == 0)
			return pos;
		p = p->next;
		++pos;
	}
	return 0;
}

void updateH(HLink &H, int beds, char *state)
{
	HLink p = H->next;
	while(p)
	{
		if(p->Beds == beds)
		{
			strcpy(p->State, state);
		}
		p = p->next;
	}
}

void Add(HLink &H)
{
	HLink p = H->next;
	while(p)
	{
		if(strcmp(p->State, "����") == 0)
		{
			p->PriceL *= 1.2f;
		}
		p = p->next;
	}
}

HLink FirstH(HLink &H)
{
	HLink p = H->next;
	HLink pre = H;    //ָ��Ҫɾ���ڵ��ǰһ���ڵ�
	HLink max_price = p;  //�۸���ߵĽڵ�
	while(p->next)
	{
		if(p->next->PriceL > max_price->PriceL)
		{	
			max_price = p->next;
			pre = p;
		}
		p = p->next;
	}
	pre->next = max_price->next;
	max_price->next = NULL;
	HLink q = max_price;
	printf("��ɾ���Ŀͷ���ϢΪ��\n");
	printf("������ ��׼�۸� ��ס�۸� ��λ�� ��ס״̬\n");
	printf("%s%8.1f%8.1f%6d%8s\n", q->roomN, q->Price, q->PriceL, q->Beds, q->State);
	free(q);
	return max_price;
}

void MoveK1(HLink &H, int k)
{
	HLink p = H->next, q = H->next, pre = H;
	if (k <= 0)
	{
		printf("����λ�ò��Ϸ���\n");
		return;
	}
	for (int i = 0; i < k; ++i)    //����q��k��
	{
		if (q->next == NULL)
		{
			printf("����λ�ó��������ȣ�\n");
			return;
		}
		q = q->next;
	}
	while (q)   //q�ߵ����һ��ʱ����һ������ʱpָ������k���ڵ�
	{
		q = q->next;
		p = p->next;
		pre = pre->next;
	}
	pre->next = p->next;
	p->next = H->next;    //��pָ��Ľڵ��ƶ�����һ��λ��
	H->next = p;
}

void ReverseN2(HLink &H)
{
	HLink p = H, q = H;
	while (q)   //q�ߵ���β��p�ߵ���n/2���ڵ�
	{
		if (q->next == NULL)   //��q�ߵ���βʱ��p���ߣ��˳�ѭ��
		{
			break;
		}
		q = q->next->next;
		p = p->next;
	}
	q = p->next;    //qָ��n/2+1���ڵ�
	p->next = NULL;  //����
	HLink s = q->next;   //s��ʱ�洢q����һ���ڵ�
	while (q)
	{
		//���ΰѵڶ��������׽ڵ���뵽p֮��
		q->next = p->next;
		p->next = q;
		q = s;
		if(s)
			s = s->next;
	}
}


void SortPriceL(HLink &H)
{
	HLink pre = H;
	HLink q = H->next;
	HLink p = H->next->next;
	q->next = NULL;   //����
	HLink s = p->next;    
	while (p)
	{
		while (q && q->PriceL < p->PriceL)    //��ͷ��ʼ����ǰ������Ѿ��ź���ģ�����ֱ���ҵ���ס�۸�>=Ҫ����Ľڵ�ģ�����������һ��
		{
			pre = pre->next;
			q = q->next;
		}
		if (q == NULL)   //�����ǰ���������û���ҵ����������Ľڵ㣬������ڵ���뵽���λ��
		{
			pre->next = p;
			p->next = NULL;
		}
		else if (q->PriceL == p->PriceL)   //�ҵ��۸���ͬ�Ľڵ㣬����ͬ��������������
		{
			HLink q2 = q;
			HLink pre2 = pre;
			while (q2 && strcmp(q2->roomN, p->roomN) <= 0 && q2->PriceL <= p->PriceL)
			{
				q2 = q2->next;
				pre2 = pre2->next;
			}
			p->next = q2;
			pre2->next = p;
		}
		else    //�ҵ��۸�ȴ�����۸��Ľڵ㣬���뵽����ڵ�ǰ��
		{
			p->next = q;
			pre->next = p;
		}
		p = s;
		if(s)
			s = s->next;
		q = H->next;
		pre = H;
	}
}

void upBed(HLink & H, int beds)
{
	HLink newRoom = (HLink)malloc(sizeof(Hotel));
	newRoom->Beds = beds;
	printf("������ͷ���׼�۸�:");    //�����·������Ϣ
	scanf("%f", &newRoom->Price);
	printf("������ͷ����ƣ�");
	scanf("%s", newRoom->roomN);
	newRoom->PriceL = newRoom->Price*0.8f;
	strcpy(newRoom->State, "����");
	HLink s = H->next;     //s�洢������׽ڵ�
	newRoom->next = H->next;    //newRoom���뵽ͷ�ڵ����
	H->next = newRoom;
	newRoom->next = NULL;     //����
	HLink front = H, rear = newRoom, s2 = s->next;   //frontָ��newRoom��ǰһ���ڵ㣬rearָ��β���
	while (s)    //����
	{
		if (s->Beds > newRoom->Beds)
		{
			s->next = newRoom;
			front->next = s;
			front = s;
			s = s2;
			if(s2)
				s2 = s2->next;
		}
		else
		{
			s->next = NULL;
			rear->next = s;
			rear = s;
			s = s2;
			if(s2)
				s2 = s2->next;
		}
	}
}
