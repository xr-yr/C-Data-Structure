#include "avlTree.h"

AVLTree *createAVLTree() {
	AVLTree *tree = (AVLTree *) malloc(sizeof(AVLTree));
	if (tree == NULL) {
		perror("tree malloc");
		return NULL;
	}
	tree->root = NULL;
	tree->cnt = 0;

	return tree;
}

// 后序遍历释放节点
static void releaseAVLNode(AVLTree *tree, AVLNode *root) {
	if (root) {
		releaseAVLNode(tree, root->left);
		releaseAVLNode(tree, root->right);
		free(root);
		--tree->cnt;
	}
}

void releaseAVLTree(AVLTree *tree) {
	if (tree) {
		releaseAVLNode(tree, tree->root);
		printf("AVLTree cnt: %d\n", tree->cnt);
		free(tree);
	}
}

void visitAVLNode(AVLNode *node) {
	if (node) {
		printf("%d\t", node->data);
	}
}

// 中序遍历递归
static void inOrder(AVLNode *node) {
	if (node) {
		inOrder(node->left);
		visitAVLNode(node);
		inOrder(node->right);
	}
}

void inOrderAVLTree(AVLTree *tree) {
	if (tree) {
		inOrder(tree->root);
	}
}

void levelOrderAVLTree(AVLTree *tree) {
	// 申请一个队列
	AVLNode **queue = (AVLNode **) malloc(sizeof(AVLNode) * tree->cnt);
	if (queue == NULL) {
		perror("level queue malloc");
		return;
	}
	// 清零
	memset(queue, 0, sizeof(AVLNode) * tree->cnt);
	int front = 0;
	int rear = 0;
	// 若第一个节点存在，入队
	if (tree->root) {
		queue[rear] = tree->root;
		rear = (rear + 1) % tree->cnt;
	} else {
		printf("tree empty!\n");
	}
	while (front != rear) {
		// 判断队列是否已满
		if ((rear + 1) % tree->cnt == front) {
			printf("queue full!\n");
			return;
		}
		// 若左子节点存在，入队
		if (queue[front]->left) {
			queue[rear] = queue[front]->left;
			rear = (rear + 1) % tree->cnt;
		}
		// 若右子节点存在，入队
		if (queue[front]->right) {
			queue[rear] = queue[front]->right;
			rear = (rear + 1) % tree->cnt;
		}
		visitAVLNode(queue[front]);
		// 出队
		front = (front + 1) % tree->cnt;
	}
	free(queue);
}

// 遍历计算节点高度
int heightAVLNode(AVLNode *node) {
	if (node == NULL) {
		return 0;
	}
	int left_height = heightAVLNode(node->left);
	int right_height = heightAVLNode(node->right);

	return ((left_height > right_height) ? left_height : right_height) + 1;
}

AVLNode *findMaxiNode(AVLNode *node) {
	while (node && node->right) {
		node = node->right;
	}
	return node;
}

AVLNode *findMiniNode(AVLNode *node) {
	while (node && node->left) {
		node = node->left;
	}
	return node;
}

/* 平衡二 叉树通用接口 */
static int maxNum(int a, int b) {
	return a > b ? a : b;
}

static int nodeHeight(AVLNode *node) {
	if (node == NULL) {
		return 0;
	}
	return node->height;
}

static int getBalance(AVLNode *node) {
	return (nodeHeight(node->left) - nodeHeight(node->right));
}

static AVLNode *createAVLTNode(Element_t e) {
	AVLNode *node = (AVLNode *) malloc(sizeof(AVLNode));
	if (node == NULL) {
		perror("tree node malloc");
		return NULL;
	}
	node->data = e;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;

	return node;
}

/* 左旋操作
 *     px
 *     |
 *     x
 *   /  \
 * lx    y
 *      / \
 *     ly ry
 * */
static AVLNode *leftRotate(AVLNode *x) {
	AVLNode *y = x->right;
	x->right = y->left;
	y->left = x;
	// 更新x y 节点的的高度，顺序不能改变，因为x 变成了y 的子节点，若先更新y ，则高度会错误，偏大
	x->height = 1 + maxNum(nodeHeight(x->left), nodeHeight(x->right));
	y->height = 1 + maxNum(nodeHeight(y->left), nodeHeight(y->right));
	return y;
}

/* 右旋操作
 *       py
 *       |
 *       y
 *     /  \
 *    x   ry
 *   / \
 * lx  rx
 * */
static AVLNode *rightRotate(AVLNode *y) {
	AVLNode *x = y->left;
	y->left = x->right;
	x->right = y;
	// 更新x y 节点的的高度，顺序不能改变，因为y 变成了x 的子节点，若先更新x ，则高度会错误，偏大
	y->height = 1 + maxNum(nodeHeight(y->left), nodeHeight(y->right));
	x->height = 1 + maxNum(nodeHeight(x->left), nodeHeight(x->right));
	return x;
}

// 递归插入节点
static AVLNode *insertAVLTNode(AVLTree *tree, AVLNode *node, Element_t e) {
	if (node == NULL) {
		++tree->cnt;
		return createAVLTNode(e);
	}
	if (e < node->data) {
		node->left = insertAVLTNode(tree, node->left, e);
	} else if (e > node->data) {
		node->right = insertAVLTNode(tree, node->right, e);
	} else {
		return node;
	}
	// 更新节点高度
	node->height = 1 + maxNum(nodeHeight(node->left), nodeHeight(node->right));
	// 计算当前节点平衡因子
	int balance = getBalance(node);
	if (balance > 1) {                    // 左边的高度大了
		// 根据失衡的子节点判断是LL还是LR
		if (e > node->left->data) {       // LR
			node->left = leftRotate(node->left);
		}
		return rightRotate(node);      // LL
	} else if (balance < -1) {			  // 右边的高度大了
		// 根据失衡的子节点判断是RL还是RR
		if (e < node->right->data) {      // RL
			node->right = rightRotate(node->right);
		}
		return leftRotate(node);       // RR
	}
	return node;            			  // 不需要调整，直接返回这个节点（归）
}

void insertAVLTree(AVLTree *tree, Element_t e) {
	if (tree) {
		tree->root = insertAVLTNode(tree, tree->root, e);
	}
}

// 递归删除节点，并调节平衡因子
static AVLNode *deleteAVLTNode(AVLTree *tree, AVLNode *node, Element_t e) {
	AVLNode *tmp;
	// 找到待删除节点
	if (node == NULL) {
		return NULL;
	}
	if (e < node->data) {
		node->left = deleteAVLTNode(tree, node->left, e);
	} else if (e > node->data) {
		node->right = deleteAVLTNode(tree, node->right, e);
	} else {							  // 找到删待除节点
		// if (node->left == NULL || node->right == NULL) {
		// 	tmp = node->right ? node->right : node->left;
		// 	if (tmp == NULL) {
		// 		free(node);
		// 		--tree->cnt;
		// 		return NULL;
		// 	} else {
		// 		node->data = tmp->data;
		// 		node->left = tmp->left;
		// 		node->right = tmp->right;
		// 		--tree->cnt;
		// 		free(tmp);
		// 	}
		// } else {
		// 	// 找左子树的最大值
		// 	tmp = findMaxiNode(node->left);
		// 	node->data = tmp->data;
		// 	node->left = deleteAVLTNode(tree, node->left, tmp->data);
		// }

		if (node->left == NULL) {
			tmp = node->right;
			free(node);
			--tree->cnt;
			return tmp;
		} else if (node->right == NULL) {
			tmp = node->left;
			free(node);
			--tree->cnt;
			return tmp;
		} else {
			// 找右边子树的最小值
			tmp = findMiniNode(node->right);
			node->data = tmp->data;
			node->right = deleteAVLTNode(tree, node->right, tmp->data);
		}
	}
	// 2. 更新平衡因子，在判断LL LR等状态时，因为是删除节点，不能通过值进行判断，可以通过平衡因子的正负号决定
	node->height = 1 + maxNum(nodeHeight(node->left), nodeHeight(node->right));
	int balance = getBalance(node);
	if (balance > 1) {								// 左多
		if (getBalance(node->left) < 0) {		// 右有值	LR
			node->left = leftRotate(node->left);
		}
		return rightRotate(node);				// LL
	} else if (balance < -1) {						// 右多
		if (getBalance(node->right) > 0) {	// 左有值	RL
			node->right = rightRotate(node->right);
		}
		return leftRotate(node);
	}
	return node;
}

void deleteAVLTree(AVLTree *tree, Element_t e) {
	if (tree) {
		tree->root = deleteAVLTNode(tree, tree->root, e);
	}
}