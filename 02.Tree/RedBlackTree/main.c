#include "rbTree.h"

int main() {
	int data[] = {55, 40, 65, 60, 75, 57, 63, 56};

	RBTree *tree = createRBTree();
	if (tree == NULL) {
		return -1;
	}

	for (int i = 0; i < sizeof(data) / sizeof(data[0]); ++i) {
		insertRBTree(tree, data[i]);
	}
	printf("tree cnt: %d\n", tree->cnt);

	printf("level:\t");
	levelOrderRBTree(tree);
	printf("\n");

	if (tree->root) {
		visitRBTree(tree->root, tree->root->key, 0);
	}
	printf("----------delete----------\n");

	deleteRBTree(tree, 60);

	printf("level:\t");
	levelOrderRBTree(tree);
	printf("\n");

	if (tree->root) {
		visitRBTree(tree->root, tree->root->key, 0);
	}

	releaseRBTree(tree);

	return 0;
}