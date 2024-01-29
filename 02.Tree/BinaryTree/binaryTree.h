#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "common.h"

//树的节点结构
typedef struct treeNode
{
	void *data;
	char show;
	struct treeNode *left;
	struct treeNode *right;
}TreeNode;

//二 叉树描述信息结构
typedef struct
{
	TreeNode *root;		//二 叉树的根节点
	int count;			//二 叉树的节点个数
}BinaryTree;

//创建二叉树
BinaryTree *createBinaryTree(TreeNode *root);

//释放二 叉树，通过后序遍历的方式，将节点逐个释放
void releaseBinaryTree(BinaryTree *tree);

//初始化二叉树根节点，若树有根节点，那么释放之前的树，重新指向新节点
void initBinaryTreeRoot(BinaryTree *tree, TreeNode *root);

//创建新节点，初始化左右指针为NULL
TreeNode *createTreeNode(char e);

//树的节点访问
void visitTreeNode(TreeNode *node);

//向父节点插入左 右节点
void insertBinaryTree(BinaryTree *tree, TreeNode *parent, TreeNode *left, TreeNode *right);

//递归先序遍历
void preOrderBinaryTree(BinaryTree *tree);

//递归中序遍历
void inOrderBinaryTree(BinaryTree *tree);

//递归后序遍历
void postOrderBinaryTree(BinaryTree *tree);

//层次遍历，将根节点入队
//只要队列不为空，就取出队列元素，将这个元素的左 右地址分别入队
void levelOrderBinaryTree(BinaryTree *tree);

#endif //BINARYTREE_H