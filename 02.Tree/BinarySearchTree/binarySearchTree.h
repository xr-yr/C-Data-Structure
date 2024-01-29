#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "common.h"

// 定义树节点
typedef struct node {
	Element_t data;
	struct node *left;
	struct node *right;
}BSTNode;

// 定义树结构
typedef struct {
	BSTNode *root;		// 根节点
	int cnt;			// 节点数量
}BSTree;

// 创建树
BSTree *createBSTree();

// 创建新节点
BSTNode *createBSTNode(Element_t e);

// 释放	需要是否所有节点
void releaseBSTree(BSTree *tree);

// 查看节点信息
void visitBSTNode(BSTNode *node);

// 计算树的高度
int heightBSTree(BSTNode *node);

// 中序遍历查看
void inOrderBSTree(BSTree *tree);

// 层次遍历
void levelOrderBSTree(BSTree *tree);

// 插入节点，判断节点值大小插入左边还是右边
// 递归插入
void insertBSTreeRecur(BSTree *tree, Element_t e);

// 非递归插入节点
void insertBSTNodeNoRecur(BSTree *tree, Element_t e);

// 查找元素
BSTNode *searchBSTree(BSTree *tree, Element_t e);

// 删除节点
// 递归删除值为e的节点
void deleteBSTNodeRecur(BSTree *tree, Element_t e);

// 非递归删除值为e的节点
void deleteBSTNodeNoRecur(BSTree *tree, Element_t e);

#endif //BINARYSEARCHTREE_H