#include "rbTree.h"

RBTree *createRBTree() {
	RBTree *tree = (RBTree *) malloc(sizeof(RBTree));
	if (tree == NULL) {
		perror("tree malloc");
		return NULL;
	}
	// 清零
	memset(tree, 0, sizeof(RBTree));
	tree->root = NULL;
	tree->cnt = 0;

	return tree;
}

// 后序遍历释放节点
static void releaseRBTNode(RBTree *tree, RBTNode *root) {
	if (root) {
		releaseRBTNode(tree, root->left);
		releaseRBTNode(tree, root->right);
		free(root);
		--tree->cnt;
	}
}

void releaseRBTree(RBTree *tree) {
	if (tree) {
		releaseRBTNode(tree, tree->root);
		printf("tree cnt: %d\n", tree->cnt);
		free(tree);
	}
}

// 前序递归
void visitRBTree(RBTNode *node, Element_t key, int dir) {
	if (node) {
		if (dir == 0) {
			printf("%2d[B] is root\n", node->key);
		} else {
			printf("%2d[%c] is %2d's %s\n", node->key,
				   (node->color == RED) ? 'R' : 'B', key,
				   (dir == 1) ? "right child" : "left child");
		}
		visitRBTree(node->left, node->key, -1);
		visitRBTree(node->right, node->key, 1);
	}
}

/* 红黑树插入删除 */

/* 将x进行左旋，将左、右、父节点进行更新
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           / \
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 * */
static void leftRotate(RBTree *tree, RBTNode *x) {
	RBTNode *y = x->right;
	x->right = y->left;
	if (y->left) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent) {
		if (x->parent->left == x) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
	} else {
		tree->root = y;
	}
	y->left = x;
	x->parent = y;
}

/* 将y进行左旋，将左、右、父节点进行更新
 *           py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(右旋)-->            /  \
 *        x   ry                           lx   y
 *       / \                                   / \
 *      lx  rx                                rx  ry
 * */
static void rightRotate(RBTree *tree, RBTNode *y) {
	RBTNode *x = y->left;
	y->left = x->right;
	if (x->right) {
		x->right->parent = y;
	}
	x->parent = y->parent;
	if (y->parent) {
		if (y->parent->left == y) {
			y->parent->left = x;
		} else {
			y->parent->right = x;
		}
	} else {
		tree->root = x;
	}
	// x->left = y;		// BUG
	x->right = y;
	y->parent = x;
}

// 创建一个红黑树的节点，默认创建的节点是红色，父、子节点为null
static RBTNode *createRBTNode(RBTree *tree, Element_t key) {
	RBTNode *node = (RBTNode *) malloc(sizeof(RBTNode));
	if (node == NULL) {
		perror("tree node malloc");
		return NULL;
	}
	node->color = RED;
	node->key = key;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	++tree->cnt;

	return node;
}

/* 1.插入节点，如果父节点是黑色，那么不用调整
 * 2.如果父节点是红色，就有两个连续的红，进行调整
 *  2.1 叔节点是红色:
 *      重新调整颜色（g->红，p->黑，u->黑）grand做为新节点重新判断
 *  2.2 叔节点是黑色:
 *      2.2.1 cur左孩子，par是左孩子
 *          g右旋 g->红，p->黑
 *      2.2.2 cur右孩子，par是右孩子
 *          g左旋 g->红，p->黑
 *      2.2.3 cur右孩子，par是左孩子
 *          p左旋，cur和par交换，然后重复2.2.1
 *      2.2.4 cur左孩子，par是右孩子
 *          p右旋，cur和par交换，然后重复2.2.2
 * */
static void insertFixUp(RBTree *tree, RBTNode *node) {
	RBTNode *parent = node->parent;
	RBTNode *grandParent;
	RBTNode *uncle;
	RBTNode *tmp;
	// 若父节点存在且是红色，违反了红红
	while (parent && parent->color == RED) {
		// 找到祖父节点，根据祖父节点和父节点关系，确定uncle节点，祖父节点一定存在，因为父节点是红色
		grandParent = parent->parent;
		// 找到叔节点
		if (grandParent->left == parent) {
			uncle = grandParent->right;
		} else {
			uncle = grandParent->left;
		}
		if (uncle && uncle->color == RED) {        // uncle存在并且是红色，如果不存在，相当于是黑色
			parent->color = BLACK;
			uncle->color = BLACK;
			grandParent->color = RED;
			// 判断祖父节点变成红色后是否存在红红
			node = grandParent;
			parent = node->parent;
			continue;
		}
		// 若没有叔节点或叔节点为黑色，则需要旋转
		if (grandParent->left == parent) {
			printf("grand %d\n", grandParent->key);
			printf("parent %d\n", parent->key);
			if (parent->right == node) {        // 当前孩子为右孩子 LR
				leftRotate(tree, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			rightRotate(tree, grandParent);    // LL
			// 旋转后，父节点与祖父节点改变颜色
			grandParent->color = RED;
			parent->color = BLACK;
		} else {
			printf("grand %d\n", grandParent->key);
			printf("parent %d\n", parent->key);
			if (parent->left == node) {            // RL
				rightRotate(tree, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			leftRotate(tree, grandParent);    // RR
			// 旋转后，父节点与祖父节点改变颜色
			grandParent->color = RED;
			parent->color = BLACK;
		}
	}
	tree->root->color = BLACK;
}

void insertRBTree(RBTree *tree, Element_t key) {
	// 创建一个红色节点
	RBTNode *node = createRBTNode(tree, key);
	if (node == NULL) {
		return;
	}
	// 根据二 叉搜索树的规则找到待插入的节点
	RBTNode *cur = tree->root;
	RBTNode *pre = NULL;
	while (cur) {
		pre = cur;
		if (key < cur->key) {
			cur = cur->left;
		} else if (key > cur->key) {
			cur = cur->right;
		} else {                    // 该节点已经存在
			printf("Key: %d have exist!\n", key);
			return;
		}
	}
	// 在对应位置上插入，若是根节点，则更新tree
	node->parent = pre;            // 找到空位置，新节点的父节点指向pre
	if (pre) {                    // 若为根节点，pre将为NULL
		if (key < pre->key) {        // 判断新节点在父节点的左边还是右边
			pre->left = node;
		} else {
			pre->right = node;
		}
	} else {
		tree->root = node;
	}
	// 修正红黑树,如果节点是黑色，则不用调整
	insertFixUp(tree, node);
}

RBTNode *SearchRBTNode(RBTree *tree, Element_t key) {
	RBTNode *move = tree->root;
	while (move) {
		if (key < move->key) {
			move = move->left;
		} else if (key > move->key) {
			move = move->right;
		} else {
			return move;
		}
	}
	// 没有找到该节点
	return NULL;
}

// 调整红黑树节点		???
static void deleteFixup(RBTree *tree, RBTNode *child, RBTNode *parent) {
	RBTNode *brother;
	while (tree->root != child && (!child || child->color == BLACK)) {
		if (parent->left == child) {                            // child 是父节点左孩子
			brother = parent->right;                            // brother 是 child 的兄弟节点
			if (brother->color == RED) {
				// case1，child 的兄弟是红色
				brother->color = BLACK;                         // (1) 将 child 的兄弟节点设置为黑色
				parent->color = RED;                            // (2) 将 child 的父节点设为红色
				leftRotate(tree, parent);                    // (3) 对 child 父节点进行左旋
				brother = parent->right;                        // (4) 左旋后，重新设置 child 的兄弟节点
			}
			// 兄弟节点都是黑色的了
			if ((!brother->left || brother->left->color == BLACK) &&
				(!brother->right || brother->right->color == BLACK)) {
				// case2，child 的兄弟是黑色，child 的兄弟的两个孩子都是黑色
				brother->color = RED;                // (1) 将 child 的兄弟节点设为红色
				child = parent;                      // (2) 设置 child 的父节点为新的 child 节点
				parent = child->parent;
			} else {
				if (!brother->right || brother->right->color == BLACK) {
					// case3，child 的兄弟节点是黑色，child 的兄弟节点的左孩子是红色，右孩子是黑色的
					brother->left->color = BLACK;     // (1) 将 child 兄弟节点的左孩子设为黑色
					brother->color = RED;             // (2) 将 child 兄弟节点设为红色
					rightRotate(tree, brother);    // (3) 对 child 的兄弟节点进行右旋
					brother = parent->right;          // (4) 右旋后，重新设置 child 的兄弟节点
				}
				// case4， child 的兄弟是黑色，child 的兄弟节点的右孩子是红色
				brother->color = parent->color;       // (1) 将 child 父节点颜色赋值给 child 的兄弟节点
				parent->color = BLACK;                // (2) 将 child 父节点设为黑色
				brother->right->color = BLACK;        // (3) 将 child 兄弟节点的右子节点设为黑色
				leftRotate(tree, parent);          // (4) 对 child 的父节点进行左旋
				child = tree->root;                   // (5) 设置 child 为根节点
				break;
			}
		} else {
			brother = parent->left;
			if (brother->color == RED) {
				// case1, child 的兄弟 brother 是红色
				brother->color = BLACK;
				parent->color = RED;
				rightRotate(tree, parent);
				brother = parent->left;
			}
			if ((!brother->left || brother->left->color == BLACK) &&
				(!brother->right || brother->right->color == BLACK)) {
				// case2, child 的兄弟w是黑色，且w的两个孩子也都是黑色的
				brother->color = RED;
				child = parent;
				parent = child->parent;
			} else {
				if ((!brother->left || brother->left->color == BLACK)) {
					// case3, child 的兄弟 brother 是黑色的，并且 brother 的左孩子是红色，右孩子为黑色
					brother->right->color = BLACK;
					brother->color = RED;
					leftRotate(tree, brother);
					brother = parent->left;
				}
				// case4, child 的兄弟 brother 是黑色的，并且 brother 的右孩子是红色的，左孩子任意
				brother->color = parent->color;
				parent->color = BLACK;
				brother->left->color = BLACK;
				rightRotate(tree, parent);
				child = tree->root;
				break;
			}
		}
	}
	// 根节点
	if (child) {
		child->color = BLACK;
	}
}

// 从红黑树中删除一个节点
static void deleteRBTNode(RBTree *tree, RBTNode *node) {
	RBTNode *deNode;        // 删除节点地址
	RBTNode *child;         // 替换节点
	RBTNode *parent;        // 替换节点为null后，无法找到父节点
	if (node->left == NULL || node->right == NULL) {    // 有一个孩子或者没有孩子
		deNode = node;
	} else {                                            // 有两个孩子
		// 找右孩子的最大值
		deNode = node->right;
		while (deNode->left) {
			deNode = deNode->left;
		}
	}
	// 真正删除的节点找到了，开始寻找替换节点
	if (deNode->left) {
		child = deNode->left;
	} else {
		child = deNode->right;
	}
	parent = deNode->parent;
	// 开始更新替换节点和原父节点的关系
	if (child) {
		child->parent = deNode->parent;
	}
	if (deNode->parent == NULL) {
		tree->root = child;
	} else if (deNode->parent->left == deNode) {
		deNode->parent->left = child;
	} else {
		deNode->parent->right = child;
	}
	// 更新有左 右孩子的根节点为后继节点的值，其他不变
	if (deNode != node) {
		node->key = deNode->key;
	}
	// 如果删除的节点是黑色的，那么需要调整
	if (deNode->color == BLACK) {
		deleteFixup(tree, child, parent);
	}
	// 调整完，或者删除节点是红色，直接释放
	free(deNode);
	--tree->cnt;
}

void deleteRBTree(RBTree *tree, Element_t key) {
	RBTNode *node = SearchRBTNode(tree, key);
	if (node) {
		deleteRBTNode(tree, node);
	} else {
		printf("No find node: %d\n", key);
	}
}

void levelOrderRBTree(RBTree *tree) {
	// 申请一个队列
	RBTNode **queue = (RBTNode **) malloc(sizeof(RBTNode) * tree->cnt);
	if (queue == NULL) {
		perror("level queue malloc");
		return;
	}
	// 清零
	memset(queue, 0, sizeof(RBTNode) * tree->cnt);
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
		visitRBTNode(queue[front]);
		// 出队
		front = (front + 1) % tree->cnt;
	}
	free(queue);
}

void visitRBTNode(RBTNode *node) {
	if (node) {
		printf("%d\t", node->key);
	}
}