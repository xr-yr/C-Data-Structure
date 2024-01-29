#include "avlTree.h"

int main() {
	AVLTree *tree = createAVLTree();
	if (tree == NULL) {
		return -1;
	}

	Element_t arr[] = {74, 52, 27, 63, 26, 93, 40, 78, 4, 21};

	for (int i = 0; i < 10; ++i) {
		insertAVLTree(tree, arr[i]);
	}
	printf("AVLTree cnt: %d\n", tree->cnt);

	printf("in   :\t");
	inOrderAVLTree(tree);
	printf("\n");

	printf("level:\t");
	levelOrderAVLTree(tree);
	printf("\n");

	printf("----------delete----------\n");

	deleteAVLTree(tree, 27);

	printf("in   :\t");
	inOrderAVLTree(tree);
	printf("\n");

	printf("level:\t");
	levelOrderAVLTree(tree);
	printf("\n");

	releaseAVLTree(tree);

	return 0;
}