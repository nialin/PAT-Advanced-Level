#include <stdio.h>
#include <stdlib.h>

#define ROOT_ID	1


struct tnode {
	int *children, child_cnt;
};


int main()
{
	struct tnode tree[100] = {{0}};
	int i, j, cnt, index, branch_cnt, queue[100], front, rear, last, non_leaf_cnt;

	scanf("%d%d", &cnt, &branch_cnt);

	for(i = 0; i < branch_cnt; ++i) {
		scanf("%d", &index);
		scanf("%d", &tree[index].child_cnt);

		tree[index].children = malloc(tree[index].child_cnt * sizeof(int));

		for(j = 0; j < tree[index].child_cnt; ++j)
			scanf("%d", &tree[index].children[j]);
	}

	for(front = rear = 0, queue[rear++] = last = ROOT_ID, non_leaf_cnt = 0; front != rear; ) {
		i = queue[front++];

		if(tree[i].child_cnt)
			for(j = 0; j < tree[i].child_cnt; ++j)
				queue[rear++] = tree[i].children[j];
		else
			++non_leaf_cnt;

		if(i == last) {
			printf("%s%d", ROOT_ID == last ? "" : " ", non_leaf_cnt);

			non_leaf_cnt = 0;
			last = queue[rear - 1];
		}
	}

	printf("\n");

	return 0;
}
