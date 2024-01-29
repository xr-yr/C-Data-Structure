#include "binarySearchTree.h"

int main() {
	BSTree *tree = createBSTree();
	if (tree == NULL) {
		return -1;
	}

	Element_t data[] = {74, 52, 27, 63, 26, 93, 40, 78, 4, 21};
	for (int i = 0; i < 10; ++i) {
		insertBSTreeRecur(tree, data[i]);
	}
	printf("tree node cnt: %d\n", tree->cnt);

	printf("in   :\t");
	inOrderBSTree(tree);
	printf("\n");

	printf("level:\t");
	levelOrderBSTree(tree);
	printf("\n");

	// 计算树高度
	printf("tree height: %d\n", heightBSTree(tree->root));

	// 查找
	visitBSTNode(searchBSTree(tree, 21));
	printf("\n");

	printf("----------delete----------\n");

	// 删除节点
	deleteBSTNodeNoRecur(tree, 27);
	printf("in   :\t");
	inOrderBSTree(tree);
	printf("\n");

	printf("level:\t");
	levelOrderBSTree(tree);
	printf("\n");

	releaseBSTree(tree);

	return 0;
}