#include "binaryTree.h"

BinaryTree *createBinaryTree(TreeNode *root) {
	BinaryTree *tree = (BinaryTree *) malloc(sizeof(BinaryTree));
	if (tree == NULL) {
		printf("tree malloc failed!\n");
		return NULL;
	}
	if (root) {
		tree->root = root;
		tree->count = 1;
	} else {
		tree->root = NULL;
		tree->count = 0;
	}

	return tree;
}

//释放二 叉树，通过后序遍历的方式，将节点逐个释放
static void releasePostOder(BinaryTree *tree, TreeNode *node) {
	if (node == NULL) {
		return;
	}
	releasePostOder(tree, node->left);
	releasePostOder(tree, node->right);
	--tree->count;
	free(node);
}

void releaseBinaryTree(BinaryTree *tree) {
	if (tree) {
		releasePostOder(tree, tree->root);
		printf("tree count :%d\n", tree->count);
		free(tree);
	}
}

//初始化二叉树根节点，若树有根节点，那么释放之前的树，重新指向新节点
void initBinaryTreeRoot(BinaryTree *tree, TreeNode *root) {
	if (tree->root) {
		releasePostOder(tree, tree->root);
		tree->root = root;
	} else {
		tree->root = root;
	}
	if (root) {
		tree->count = 1;
	}
}

//创建新节点，初始化左右指针为NULL
TreeNode *createTreeNode(char e) {
	TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
	if (node == NULL) {
		printf("tree node malloc failed!\n");
		return NULL;
	}
	// 初始化
	node->data = NULL;
	node->show = e;
	node->left = NULL;
	node->right = NULL;

	return node;
}

//树的节点访问
void visitTreeNode(TreeNode *node) {
	if (node) {
		printf("%c ", node->show);
	}
}

//向父节点插入左 右节点
void insertBinaryTree(BinaryTree *tree, TreeNode *parent, TreeNode *left, TreeNode *right) {
	if (tree && parent) {
		parent->left = left;
		parent->right = right;
		if (left) {
			++tree->count;
		}
		if (right) {
			++tree->count;
		}
	}
}

//递归先序遍历
static void preOrder(TreeNode *node) {
	if (node == NULL) {
		return;
	}
	visitTreeNode(node);
	preOrder(node->left);
	preOrder(node->right);
}

void preOrderBinaryTree(BinaryTree *tree) {
	if (tree == NULL) {
		return;
	}
	preOrder(tree->root);
}

//递归中序遍历
static void inOrder(TreeNode *node) {
	if (node == NULL) {
		return;
	}
	inOrder(node->left);
	visitTreeNode(node);
	inOrder(node->right);
}

void inOrderBinaryTree(BinaryTree *tree) {
	if (tree == NULL) {
		return;
	}
	inOrder(tree->root);
}

//递归后序遍历
static void postOrder(TreeNode *node) {
	if (node == NULL) {
		return;
	}
	postOrder(node->left);
	postOrder(node->right);
	visitTreeNode(node);
}

void postOrderBinaryTree(BinaryTree *tree) {
	if (tree == NULL) {
		return;
	}
	postOrder(tree->root);
}

//层次遍历，将根节点入队
//只要队列不为空，就取出队列元素，将这个元素的左 右地址分别入队
void levelOrderBinaryTree(BinaryTree *tree) {
	if (tree == NULL) {
		return;
	}
// 队列空间大小
#define N 5
	// 定义一个队列
	// int n = tree->count;
	TreeNode *queue[N] = {0};        // 队列空间
	int front = 0;                   // 头指针
	int rear = 0;                    // 尾指针
	if (tree->root) {
		queue[rear] = tree->root;
		rear = (rear + 1) % N;
		while (front != rear) {
			// 看左右子节点是否为空
			if (queue[front]->left) {
				queue[rear] = queue[front]->left;
				rear = (rear + 1) % N;
			}
			if (queue[front]->right) {
				queue[rear] = queue[front]->right;
				rear = (rear + 1) % N;
			}
			// 判断满队
			if ((rear + 1) % N == front) {
				printf("queue full!\n");
				return;
			}
			visitTreeNode(queue[front]);
			front = (front + 1) % N;
		}
	} else {
		printf("tree empty!\n");
	}
}