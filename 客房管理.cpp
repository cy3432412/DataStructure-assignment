#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//定义客房链表结点结构
typedef struct HNode
	{
		char	roomN[7];	//客房名称
		float   Price;		//标准价格
		float   PriceL;	//入住价格(默认值=标准价格*80%)
		int	   Beds;		//床位数Beds
		char	   State[5];	//入住状态(值域："空闲"、"入住"、"预订"，默认值为"空闲")
		struct HNode  *next;	//指针域
	}Hotel, *HLink;

void Build(HLink &H);    //创建客房信息链表函数
void Exp(HLink H);      //输出全部客房信息
int Find(HLink &H, char *roomN);   //查找客房名称，若找到返回客房在链表中的位置，若没找到返回0
void updateH(HLink &H, int beds, char *state);   //将床位数为bed的客房状态改为state
void Add(HLink &H);  //将该链表中未入住的客房入住价格均加价20%
HLink FirstH(HLink &H);    //找到入住价格最高的客房，返回该节点指针，返回前将该节点删除
void MoveK1(HLink &H, int k);   //将单链表中倒数第k个结点移到第一个结点位置
void ReverseN2(HLink &H);    //将单链表的正中间位置结点之后的全部结点倒置
void SortPriceL(HLink &H);     //按照客房（入住价格，客房名称）升序排序
void upBed(HLink &H, int beds);  //创建一个【床位数为beds的新结点】，使链表的形态为：【头结点】->【床位数>beds的结点】->【床位数为beds的新结点】->【床位数<=beds的结点】

void main()
{
	HLink H;
	int choice;
	Build(H);
	while (1)
	{
		printf("请选择使用的功能：\n");
		printf("1.输出全部客房信息\t\t\t\t2.查找客房名称\n");
		printf("3.更改指定床位数的客房的入住状态\t\t4.未入住的客房加价20%%\n");
		printf("5.找到价格最高的客房\t\t\t\t6.倒数第k间房移动到第一间的位置\n");
		printf("7.正中间客房之后的房间全部倒置\t\t\t8.按照客房（入住价格，客房名称）升序排序\n");
		printf("9.创建新客房\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			Exp(H);
			break;
		case 2:
		{
			printf("请输入要查找的客房名称:");
			char name[7];
			scanf("%s", name);
			int pos = Find(H, name);
			printf("客房名称为%s的房间在第%d个位置：", name, pos);
			break;
		}
		case 3:
			printf("请输入要更改的客房的房间数：");
			int bed;
			scanf("%d", &bed);
			printf("请输入要更改的状态\n");
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
			printf("请输入要移动的客房位置：");
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
			printf("请输入新客房房间数：");
			int beds;
			scanf("%d", &beds);
			upBed(H, beds);
			break;
		default:
			printf("输入不合法\n");
		}
		printf("\n\n\n");
	}
}

void Build(HLink &H)
{
	FILE* input = fopen("D:\\数据文件.txt", "r");
	H = (HLink)malloc(sizeof(Hotel));
	H->next = NULL;
	HLink rear = H;
	while(!feof(input))
	{
		HLink p = (HLink)malloc(sizeof(Hotel));
		char roomn[7];
		fscanf(input, "%s%f%d", roomn, &p->Price, &p->Beds);
		strcpy(p->roomN, roomn);
		strcpy(p->State, "空闲");
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
	printf("\n客房信息如下：\n");
	printf("----------------------------------------------------\n");
	printf("房间名 标准价格 入住价格 床位数 入住状态\n");
	while(p)
	{
		printf("%s %8.1f %8.1f %6d %8s\n",p->roomN,p->Price,p->PriceL,p->Beds,p->State);
		p = p->next;
	}
}

int Find(HLink &H, char *roomN)
{
	HLink p = H->next;   //指针p指向首节点
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
		if(strcmp(p->State, "空闲") == 0)
		{
			p->PriceL *= 1.2f;
		}
		p = p->next;
	}
}

HLink FirstH(HLink &H)
{
	HLink p = H->next;
	HLink pre = H;    //指向要删除节点的前一个节点
	HLink max_price = p;  //价格最高的节点
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
	printf("被删除的客房信息为：\n");
	printf("房间名 标准价格 入住价格 床位数 入住状态\n");
	printf("%s%8.1f%8.1f%6d%8s\n", q->roomN, q->Price, q->PriceL, q->Beds, q->State);
	free(q);
	return max_price;
}

void MoveK1(HLink &H, int k)
{
	HLink p = H->next, q = H->next, pre = H;
	if (k <= 0)
	{
		printf("输入位置不合法！\n");
		return;
	}
	for (int i = 0; i < k; ++i)    //先让q走k步
	{
		if (q->next == NULL)
		{
			printf("输入位置超过链表长度！\n");
			return;
		}
		q = q->next;
	}
	while (q)   //q走到最后一个时再走一步，此时p指向倒数第k个节点
	{
		q = q->next;
		p = p->next;
		pre = pre->next;
	}
	pre->next = p->next;
	p->next = H->next;    //将p指向的节点移动到第一个位置
	H->next = p;
}

void ReverseN2(HLink &H)
{
	HLink p = H, q = H;
	while (q)   //q走到表尾，p走到第n/2个节点
	{
		if (q->next == NULL)   //当q走到表尾时，p不走，退出循环
		{
			break;
		}
		q = q->next->next;
		p = p->next;
	}
	q = p->next;    //q指向n/2+1个节点
	p->next = NULL;  //断链
	HLink s = q->next;   //s暂时存储q的下一个节点
	while (q)
	{
		//依次把第二条链的首节点插入到p之后
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
	q->next = NULL;   //断链
	HLink s = p->next;    
	while (p)
	{
		while (q && q->PriceL < p->PriceL)    //从头开始遍历前半个（已经排好序的）链表，直到找到入住价格>=要插入的节点的，或遍历到最后一个
		{
			pre = pre->next;
			q = q->next;
		}
		if (q == NULL)   //如果在前半个链表中没有找到符合条件的节点，带插入节点插入到最后位置
		{
			pre->next = p;
			p->next = NULL;
		}
		else if (q->PriceL == p->PriceL)   //找到价格相同的节点，用相同方法按名称排序
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
		else    //找到价格比带插入价格大的节点，插入到这个节电前面
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
	printf("请输入客房标准价格:");    //输入新房间的信息
	scanf("%f", &newRoom->Price);
	printf("请输入客房名称：");
	scanf("%s", newRoom->roomN);
	newRoom->PriceL = newRoom->Price*0.8f;
	strcpy(newRoom->State, "空闲");
	HLink s = H->next;     //s存储链表的首节点
	newRoom->next = H->next;    //newRoom插入到头节点后面
	H->next = newRoom;
	newRoom->next = NULL;     //断链
	HLink front = H, rear = newRoom, s2 = s->next;   //front指向newRoom的前一个节点，rear指向尾结点
	while (s)    //插入
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
