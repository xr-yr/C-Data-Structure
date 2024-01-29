#ifndef AVLTREE_H
#define AVLTREE_H

#include "common.h"

/* 平衡二 叉搜索树，和二 叉搜索树的结构一致，
 * 为了满足插入和删除时计算平衡因子，加入节点的高度属性
 * 避免每次运算时，都计算一次各节点的高度
 * 采用递归方式进行插入删除
 * */

// 定义树节点
typedef struct node {
	Element_t data;
	struct node *left;
	struct node *right;
	int height;
}AVLNode;

// 定义树结构
typedef struct {
	AVLNode *root;		// 根节点
	int cnt;			// 节点数量
}AVLTree;

// 创建平衡二叉树
AVLTree *createAVLTree();

// 释放平衡二叉树
void releaseAVLTree(AVLTree *tree);

// 访问平衡二 叉树的节点
void visitAVLNode(AVLNode *node);

// 平衡二叉树中序遍历
void inOrderAVLTree(AVLTree *tree);

// 平衡二 叉树层次遍历
void levelOrderAVLTree(AVLTree *tree);

// 递归得到节点的高度
int heightAVLNode(AVLNode *node);

// 查找最大元素节点
AVLNode *findMaxiNode(AVLNode *node);

// 查找最小元素节点
AVLNode *findMiniNode(AVLNode *node);

// 插入元素到AVL树
void insertAVLTree(AVLTree *tree, Element_t e);

// 删除元素从AVL树
void deleteAVLTree(AVLTree *tree, Element_t e);

#endif //AVLTREE_H
