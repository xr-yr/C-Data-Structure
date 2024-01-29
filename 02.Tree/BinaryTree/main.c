#include "binaryTree.h"

BinaryTree *initTree()
{
	//创建节点
	TreeNode *nodeA = createTreeNode('A');
	TreeNode *nodeB = createTreeNode('B');
	TreeNode *nodeC = createTreeNode('C');
	TreeNode *nodeD = createTreeNode('D');
	TreeNode *nodeE = createTreeNode('E');
	TreeNode *nodeF = createTreeNode('F');
	TreeNode *nodeG = createTreeNode('G');
	TreeNode *nodeH = createTreeNode('H');
	TreeNode *nodeK = createTreeNode('K');
	//创建二叉树
	BinaryTree *tree = createBinaryTree(nodeA);
	insertBinaryTree(tree, nodeA, nodeB, nodeE);
	insertBinaryTree(tree, nodeB, NULL, nodeC);
	insertBinaryTree(tree, nodeC, nodeD, NULL);
	insertBinaryTree(tree, nodeE, NULL, nodeF);
	insertBinaryTree(tree, nodeF, nodeG, NULL);
	insertBinaryTree(tree, nodeG, nodeH, nodeK);

	return tree;
}

int main()
{
	BinaryTree *tree = initTree();
	printf("tree count :%d\n", tree->count);

	printf("递归先序：");
	preOrderBinaryTree(tree);
	printf("\n");

	printf("递归中序：");
	inOrderBinaryTree(tree);
	printf("\n");

	printf("递归后序：");
	postOrderBinaryTree(tree);
	printf("\n");

	printf("层次遍历：");
	levelOrderBinaryTree(tree);
	printf("\n");

	releaseBinaryTree(tree);

	return 0;
}