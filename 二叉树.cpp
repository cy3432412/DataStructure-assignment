#include <stdio.h>
#include <stdlib.h>


// add an annotation to test
typedef struct  node{
	char data;	//数据域
	struct node *lchild ,  *rchild;  //左右孩子指针
}BinTNode, *BinTree;   //树中结点类型

void CreateBiTree(BinTree &bt);    //建立二叉树存储结构
void OutputBiTree(BinTree bt);     //输出二叉树的形态
void PreOrderTraverse(BinTree bt);   //求二叉树的先序遍历
void InOrderTraverse(BinTree bt);     //求二叉树的中序遍历
void PostOrderTraverse(BinTree bt);    //求二叉树的后序遍历
void LevelOrderTraverse(BinTree bt);    //求二叉树的层次遍历
void Path(BinTree bt);    //求给定结点的路径

void main()
{
	BinTree bt;
	while(1)
	{
		int choice;
		printf("请选择功能：\n");
		printf("1.建立二叉树存储结构\t2.输出二叉树的形态\n");
		printf("3.求二叉树的先序遍历\t4.求二叉树的中序遍历\n");
		printf("5.求二叉树的后序遍历\t6.求二叉树的层次遍历\n");
		printf("7.求给定结点的路径\t0.退出系统\n");
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
			printf("输入数字错误\n");
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
	if(bt != NULL)      //当前根节点存在时,输出节点数据和左、右孩子数据
	{
		for(int i = 0;i<space;++i)    //打出空格
		{
			printf(" ");
		}
		printf("%c\n", bt->data);
		if(bt->lchild)    //如果左孩子存在
		{
			for(int j = 0;j<space-1;++j)    //比上一行少打出一个空格
				printf(" ");
			printf("/ ");     //输出/作为左分支
		}
		if(bt->rchild)    //右孩子存在，输出\作为右分支
		{
			printf("\\");
		}
		printf("\n");    //换行，输出左右孩子数据
		if(bt->lchild)    //先判断左右孩子是否存在
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
