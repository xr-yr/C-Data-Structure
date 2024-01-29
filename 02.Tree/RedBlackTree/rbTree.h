#ifndef RBTREE_H
#define RBTREE_H

#include <common.h>

/* 1.每个结点要么是红的要么是黑的。
 * 2.根结点是黑的。
 * 3.每个叶结点（叶结点即指树尾端NIL指针或NULL结点）都是黑的。
 * 4.如果一个结点是红的，那么它的两个儿子都是黑的。
 * 5.对于任意结点而言，其到叶结点树尾端NIL指针的每条路径都包含相同数目的黑结点。
 * */

// 红黑树节点结构
typedef struct node {
	char color;
	Element_t key;
	struct node *parent;
	struct node *left;
	struct node *right;
}RBTNode;

// 红黑树结构
typedef struct {
	RBTNode *root;
	int cnt;
}RBTree;

// 红黑节点颜色枚举类型
enum RBColor {
	RED, BLACK
};

// 创建红黑树
RBTree *createRBTree();

// 释放
void releaseRBTree(RBTree *tree);

// 从红黑树中查找节点
RBTNode *searchRBNode(RBTree *tree, Element_t key);

// 查看
void visitRBTree(RBTNode *node, int key, int dir);

// 向红黑树插入值
void insertRBTree(RBTree *tree, Element_t key);

// 从红黑树中删除值
void deleteRBTree(RBTree *tree, Element_t key);

// 查找节点
RBTNode *SearchRBTNode(RBTree *tree, Element_t key);

// 层次遍历
void levelOrderRBTree(RBTree *tree);

void visitRBTNode(RBTNode *node);

#endif //RBTREE_H