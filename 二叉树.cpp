#include <stdio.h>
#include <stdlib.h>


// add an annotation to test
typedef struct  node{
	char data;	//������
	struct node *lchild ,  *rchild;  //���Һ���ָ��
}BinTNode, *BinTree;   //���н������

void CreateBiTree(BinTree &bt);    //�����������洢�ṹ
void OutputBiTree(BinTree bt);     //�������������̬
void PreOrderTraverse(BinTree bt);   //����������������
void InOrderTraverse(BinTree bt);     //����������������
void PostOrderTraverse(BinTree bt);    //��������ĺ������
void LevelOrderTraverse(BinTree bt);    //��������Ĳ�α���
void Path(BinTree bt);    //���������·��

void main()
{
	BinTree bt;
	while(1)
	{
		int choice;
		printf("��ѡ���ܣ�\n");
		printf("1.�����������洢�ṹ\t2.�������������̬\n");
		printf("3.����������������\t4.����������������\n");
		printf("5.��������ĺ������\t6.��������Ĳ�α���\n");
		printf("7.���������·��\t0.�˳�ϵͳ\n");
		scanf("%d", &choice);
		switch(choice)
		{
		case 1:
			getchar();
			CreateBiTree(bt);
			break;
		case 2:
			OutputBiTree(bt);
			break;
		case 3:
			PreOrderTraverse(bt);
			break;
		case 4:
			InOrderTraverse(bt);
			break;
		case 5:
			PostOrderTraverse(bt);
			break;
		case 6:
			LevelOrderTraverse(bt);
			break;
		case 7:
			Path(bt);
			break;
		case 0:
			return;
		default:
			printf("�������ִ���\n");
		}
	}
}

void CreateBiTree(BinTree &bt)
{
	char num;
	scanf("%c", &num);
	if(num == '#')
		bt = NULL;
	else
	{
		bt = (BinTree)malloc(sizeof(BinTNode));
		bt->data = num;
		CreateBiTree(bt->lchild);
		CreateBiTree(bt->rchild);
	}
}

void OutputBiTree(BinTree bt, int space)
{
	if(bt != NULL)      //��ǰ���ڵ����ʱ,����ڵ����ݺ����Һ�������
	{
		for(int i = 0;i<space;++i)    //����ո�
		{
			printf(" ");
		}
		printf("%c\n", bt->data);
		if(bt->lchild)    //������Ӵ���
		{
			for(int j = 0;j<space-1;++j)    //����һ���ٴ��һ���ո�
				printf(" ");
			printf("/ ");     //���/��Ϊ���֧
		}
		if(bt->rchild)    //�Һ��Ӵ��ڣ����\��Ϊ�ҷ�֧
		{
			printf("\\");
		}
		printf("\n");    //���У�������Һ�������
		if(bt->lchild)    //���ж����Һ����Ƿ����
		{
			for(int m = 0;m<space-2;++m)
				printf(" ");
			printf("%c   ", bt->lchild->data);
		}
		if(bt->rchild)
		{
			printf("%c", bt->rchild->data);
		}
	}
	printf("\n\n");
}

void PreOrderTraverse(BinTree bt)
{

}

void InOrderTraverse(BinTree bt)
{

}

void PostOrderTraverse(BinTree bt)
{

}

void LevelOrderTraverse(BinTree bt)
{

}

void Path(BinTree bt)
{

}
