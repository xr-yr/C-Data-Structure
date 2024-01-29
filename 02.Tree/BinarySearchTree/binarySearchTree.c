#include "binarySearchTree.h"

BSTree *createBSTree() {
	BSTree *tree = (BSTree *) malloc(sizeof(BSTree));
	if (tree == NULL) {
		perror("tree malloc");
		return NULL;
	}
	// 初始化
	tree->root = NULL;
	tree->cnt = 0;

	return tree;
}

void visitBSTNode(BSTNode *node) {
	if (node) {
		printf("%d\t", node->data);
	}
}

BSTNode *createBSTNode(Element_t e) {
	BSTNode *node = (BSTNode *) malloc(sizeof(BSTNode));
	if (node == NULL) {
		perror("tree node malloc");
		return NULL;
	}
	// 初始化
	node->data = e;
	node->left = NULL;
	node->right = NULL;

	return node;
}

// 释放树节点
static void releaseBSTNode(BSTree *tree, BSTNode *root) {
	if (root) {
		// 释放左 右节点
		releaseBSTNode(tree, root->left);
		releaseBSTNode(tree, root->right);
		free(root);
		--tree->cnt;
	}
}

// 递归，后序遍历释放每一个节点
void releaseBSTree(BSTree *tree) {
	if (tree) {
		releaseBSTNode(tree, tree->root);
		printf("tree node cnt: %d\n", tree->cnt);
		free(tree);
	}
}

// 中序遍历递归
static void inOrder(BSTNode *node) {
	if (node) {
		inOrder(node->left);
		visitBSTNode(node);
		inOrder(node->right);
	}
}

void inOrderBSTree(BSTree *tree) {
	if (tree) {
		inOrder(tree->root);
	}
}

// 层次遍历
void levelOrderBSTree(BSTree *tree) {
	// 申请一个队列
	BSTNode **queue = (BSTNode **) malloc(sizeof(BSTNode) * tree->cnt);
	if (queue == NULL) {
		perror("level queue malloc");
		return;
	}
	// 清零
	memset(queue, 0, sizeof(BSTNode) * tree->cnt);
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
		visitBSTNode(queue[front]);
		// 出队
		front = (front + 1) % tree->cnt;
	}
}

/* 计算树的高度，利用递归算法
 * 任何节点都有左子树和右子树，利用递的思想，把每个节点的高度返回给上一个节点
 * 归的初始条件，就是当前节点node已经空了，那么将0返回上层，到上层归的时候在这个基础上+1
 * */
int heightBSTree(BSTNode *node) {
	if (node == NULL) {
		return 0;
	}
	int left_height = heightBSTree(node->left);
	int right_height = heightBSTree(node->right);
	return left_height > right_height ? left_height + 1 : right_height + 1;
}

/* 使用非递归方式，再树中插入元素e
 * 插入节点必须知道上一个节点root，然后确定在root的左边还是右边操作，这样定义一个指针pre指向上一个位置
 * 定义一个遍历指针cur，当指向了NULL，那么就触发了插入条件
 * */
void insertBSTNodeNoRecur(BSTree *tree, Element_t e) {
	BSTNode *pre = NULL;
	BSTNode *cur = tree->root;                // 当前节点，根据二分搜索树的规矩，走到空就是待插入位置
	while (cur) {
		pre = cur;                            // cur向下走之前，用pre指向前一个节点，一旦满足条件，从这个节点进行插入
		if (e < cur->data) {
			cur = cur->left;
		} else if (e > cur->data) {
			cur = cur->right;
		} else {                              // 插入的元素已经在树上了，就不用插入了
			return;
		}
	}
	// 找到待插入位置后，创建节点
	BSTNode *node = createBSTNode(e);
	if (node == NULL) {
		return;
	}
	if (cur == NULL) {                        // 找到了空位置，再次判断是左边插入还是右边插入
		if (pre && e < pre->data) {
			pre->left = node;
		} else if (pre && e > pre->data) {
			pre->right = node;
		} else {                              // 若pre空，则树中没有节点，root为空
			tree->root = node;
		}
		++tree->cnt;
	}
}

/* 使用递归方式在二分搜索树的正确节点插入e元素
 * 递的过程，就是不断判断node节点的值和e的大小，然后把node的左子树还是右子树作为下一个问题的初始值
 * 当遇到node为空的时候，就可以归回来了，申请一个新节点返回到上一个问题中node的左还是右节点来接收这个归上来的答案
 * 再往上归的过程中，不断把node节点的处理问题往回返回即可
 * */
static BSTNode *insertBSTNodeRecur(BSTree *tree, BSTNode *node, Element_t e) {
	if (node == NULL) {
		++tree->cnt;
		return createBSTNode(e);
	}
	if (e < node->data) {
		node->left = insertBSTNodeRecur(tree, node->left, e);
	} else if (e > node->data) {
		node->right = insertBSTNodeRecur(tree, node->right, e);
	}
	return node;
}

void insertBSTreeRecur(BSTree *tree, Element_t e) {
	tree->root = insertBSTNodeRecur(tree, tree->root, e);
}

/* 按照左小右大规则，决定next的走向，进行查找
 * 返回查找节点
 * */
BSTNode *searchBSTree(BSTree *tree, Element_t e) {
	BSTNode *node = tree->root;
	while (node) {
		if (e < node->data) {
			node = node->left;
		} else if (e > node->data) {
			node = node->right;
		} else {
			return node;
		}
	}
	return NULL;
}

/* 递归方式删除值为e的节点
 * 递的过程是找到和e相等的节点，在做完删除动作后，按之前路径归回来
 * */
// 右孩子的最小值
static BSTNode *deRecurMiniNode(BSTNode *node) {
	while (node && node->left) {
		node = node->left;
	}
	return node;
}

// 左孩子的最大值
static BSTNode *deRecurMaxiNode(BSTNode *node) {
	while (node && node->right) {
		node = node->right;
	}
	return node;
}

static BSTNode *deleteBSTNode(BSTree *tree, BSTNode *node, Element_t e) {
	if (node == NULL) {
		return node;
	}
	if (e < node->data) {
		node->left = deleteBSTNode(tree, node->left, e);
	} else if (e > node->data) {
		node->right = deleteBSTNode(tree, node->right, e);
	} else {
		// 找到待删除节点
		BSTNode *tmp;
		if (node->left == NULL) {			// 右孩子节点为空
			tmp = node->right;
			free(node);
			--tree->cnt;
			return tmp;
		} else if (node->right == NULL) {	// 左孩子节点为空
			tmp = node->left;
			free(node);
			--tree->cnt;
			return tmp;
		} else {							// 两个孩子节点都存在
			/* 右孩子的最小值 */
			// tmp = deRecurMiniNode(node->right);
			// node->data = tmp->data;
			// node->right = deleteBSTNode(tree, node->right, tmp->data);

			/* 左孩子的最大值 */
			tmp = deRecurMaxiNode(node->left);
			node->data = tmp->data;
			node->left = deleteBSTNode(tree, node->left, tmp->data);
		}
	}
	return node;
}

void deleteBSTNodeRecur(BSTree *tree, Element_t e) {
	if (tree) {
		tree->root = deleteBSTNode(tree, tree->root, e);
	}
}

/* 非递归方式删除元素
 * 1. 找到这个待删除的元素节点node，由于要处理关系，还是要有一个pre节点指向上一个位置
 * 2. 判断node的孩子节点的情况
 * 		度为1或度为0，直接替换
 * 3. 如果node有2个孩子节点
 * 		找到这个节点的前驱（左孩子的最大值）或后继节点（右孩子的最小值）
 * 		删除后继节点
 * */
// 采用非递归方式，从node节点中找后继节点，然后做删除的更新操作
static void deleteMiniNode(BSTNode *node) {
	BSTNode *mini = node->right;        // 假设最小值的节点
	BSTNode *pre = node;
	while (mini && mini->left) {        // mini的左边为空，那么mini就是最小值了
		pre = mini;
		mini = mini->left;
	}
	// 如果前置节点的值等于删除节点的值，那么说明没有向左进行寻找最小值
	if (pre->data == node->data) {
		pre->right = mini->right;
	} else {                            // 更新的就是左边的关系
		pre->left = mini->right;
	}
	node->data = mini->data;            // 将最小值即后继节点值更新到node里
	free(mini);
}

// 左孩子的最大值
static void deleteMaxiNode(BSTNode *node) {
	BSTNode *maxi = node->left;
	BSTNode *pre = node;
	while (maxi && maxi->right) {
		pre = maxi;
		maxi = maxi->right;
	}
	if (pre->data == node->data) {
		pre->left = maxi->left;
	} else {
		pre->right = maxi->left;
	}
	node->data = maxi->data;
	free(maxi);
}

void deleteBSTNodeNoRecur(BSTree *tree, Element_t e) {
	BSTNode *node = tree->root;
	BSTNode *pre = NULL;
	// 采用前置节点和当前节点的策略，找到元素e所在的节点，用node标记该节点，用pre标记前置节点
	while (node) {
		if (e < node->data) {
			pre = node;
			node = node->left;
		} else if (e > node->data) {
			pre = node;
			node = node->right;
		} else {
			break;
		}
	}
	BSTNode *tmp = NULL;
	// 删除的节点不是根节点
	if (node && pre) {
		if (node->left == NULL) {                // 度为0或1
			tmp = node->right;
		} else if (node->right == NULL) {        // 度为0或1
			tmp = node->left;
		} else {                                // 度为2，有两个孩子节点
			deleteMaxiNode(node);
			--tree->cnt;
			return;
		}
		// 只有一个孩子节点时，判断左更新还是右更新
		if (node->data < pre->data) {            // node的孩子节点值比pre节点值小
			pre->left = tmp;
		} else {                                // node的孩子节点值比pre节点值大
			pre->right = tmp;
		}
		free(node);
		--tree->cnt;
		return;
	}
	// 删除的节点是根节点
	if (node && pre == NULL) {
		if (node->left == NULL) {                // 度为0或1
			tmp = node->right;
		} else if (node->right == NULL) {        // 度为0或1
			tmp = node->left;
		} else {                                // 度为2，有两个孩子节点
			deleteMaxiNode(node);
			--tree->cnt;
			return;
		}
		tree->root = tmp;
		free(node);
		--tree->cnt;
	}
}