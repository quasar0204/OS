#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"
#include "hash.h"
#include "bitmap.h"

struct hash_item {
	struct hash_elem elem;
	int data;
};

struct LIST {
	struct list List;
	char name[30];
	char type[10];
};
struct HASH {
	struct hash Hash;
	char name[30];
};

struct BITMAP {
	struct bitmap* Bitmap;
	char name[30];
};

//list
int listIdx;
struct LIST* lists[30];

void create_list(char* name) {
	struct LIST *new_list = (struct LIST*)malloc(sizeof(struct LIST));
	list_init(&(new_list->List));
	strcpy(new_list->type, "list");
	strcpy(new_list->name, name);
	lists[listIdx++] = new_list;
}

void dumpdata_list(struct LIST* list) {
	for (struct list_elem* cur = list_begin(&(list->List));
		cur != list_tail(&(list->List)); cur = list_next(cur)) {
		printf("%d", list_entry(cur, struct list_item, elem)->data);
		if (cur->next == list_tail(&(list->List))) printf("\n");
		else printf(" ");
	}
}

void list_pb(char* str, int num) {
	struct list_item *tmp = (struct list_item*)malloc(sizeof(struct list_item));
	tmp->data = num;
	for (int i = 0; i < listIdx; i++) {
		if (strcmp(lists[i]->name, str) == 0) {
			list_push_back(&(lists[i]->List), &(tmp->elem));
			return;
		}
	}
}

void list_pf(char* str, int num) {
	struct list_item *tmp = (struct list_item*)malloc(sizeof(struct list_item));
	tmp->data = num;
	for (int i = 0; i < listIdx; i++) {
		if (strcmp(lists[i]->name, str) == 0) {
			list_push_front(&(lists[i]->List), &(tmp->elem));
			return;
		}
	}
}

void list_insert_(char* str, int idx, int num) {
	struct list_item *tmp = (struct list_item*)malloc(sizeof(struct list_item));
	tmp->data = num;
	for (int i = 0; i < listIdx; i++) {
		if (strcmp(lists[i]->name, str) == 0) {
			struct list_elem* before = list_begin(&(lists[i]->List));
			for (; idx--; before = list_next(before));
			list_insert(before, &(tmp->elem));
			return;
		}
	}
}

bool cmp(const struct list_elem *a, const struct list_elem *b, void *aux) {
	int x = list_entry(a, struct list_item, elem)->data;
	int y = list_entry(b, struct list_item, elem)->data;
	
	return x < y;
}

void list_insert_order(char* str, int num) {
	struct list_item *tmp = (struct list_item*)malloc(sizeof(struct list_item));
	tmp->data = num;
	for (int i = 0; i < listIdx; i++) {
		if (strcmp(lists[i]->name, str) == 0) {
//			struct list_elem* before = list_begin(&(lists[i]->List));
			list_insert_ordered(&(lists[i]->List), &(tmp->elem), cmp, NULL);
			return;
		}
	}
}

int get_element_idx(char* str) {
	for (int i = 0; i < listIdx; i++) {
		if (lists[i] != NULL && strcmp(lists[i]->name, str) == 0) {
			return i;
		}
	}
	return -1;
}

//hash
int hashIdx;
struct HASH* hashs[30];

bool hash_less(const struct hash_elem *a, const struct hash_elem *b, void *aux) {
	struct hash_item *A, *B;
	A = hash_entry(a, struct hash_item, elem);
	B = hash_entry(b, struct hash_item, elem);
	return A->data < B->data;
}

unsigned hash_func(const struct hash_elem *e, void*aux) {
	return hash_int(hash_entry(e, struct hash_item, elem)->data);
}

void create_hash(char* name) {
	struct HASH *new_hash = (struct HASH*)malloc(sizeof(struct HASH));
	hash_init(&(new_hash->Hash), hash_func, hash_less, NULL);
	//strcpy(new_hash->type, "hash");
	strcpy(new_hash->name, name);
	hashs[hashIdx++] = new_hash;
}

void dumpdata_hash(struct HASH* hash) {
	if (hash_empty(&(hash->Hash))) return;
	struct hash_iterator cur;
	hash_first(&cur, &(hash->Hash));
	for (; hash_next(&cur) != NULL;) {
		printf("%d ", hash_entry(cur.elem, struct hash_item, elem)->data);
	}
	printf("\n");
}

void hash_square(struct hash_elem* h, void *aux) {
	int sq;
	sq = hash_entry(h, struct hash_item, elem)->data;
	hash_entry(h, struct hash_item, elem)->data = sq * sq;
}

void hash_triple(struct hash_elem* h, void *aux) {
	int t;
	t = hash_entry(h, struct hash_item, elem)->data;
	hash_entry(h, struct hash_item, elem)->data = t*t*t;
}

int get_element_idx_hash(char* str) {
	for (int i = 0; i < hashIdx; i++) {
		if (hashs[i] != NULL && strcmp(hashs[i]->name, str) == 0) {
			return i;
		}
	}
	return -1;
}

//bitmap
int bitmapIdx;
struct BITMAP* bitmaps[30];

void create_bm(char* name, int num) {
	struct BITMAP* tmp = (struct BITMAP*)malloc(sizeof(struct BITMAP));
	tmp->Bitmap = bitmap_create(num);
	strcpy(tmp->name, name);
	bitmaps[bitmapIdx++] = tmp;
}

int get_element_idx_bitmap(char* str) {
	for (int i = 0; i < bitmapIdx; i++) {
		if (bitmaps[i] != NULL && strcmp(bitmaps[i]->name, str) == 0) {
			return i;
		}
	}
	return -1;
}

void dumpdata_bitmap(struct BITMAP* bitmap) {
	int size = bitmap_size(bitmap->Bitmap);
	if (size == 0) return;

	for (int i = 0; i < size; i++) {
		if (bitmap_test(bitmap->Bitmap, i)) printf("1");
		else printf("0");
	}
	printf("\n");
}

//total
void create(char* str1, char* str2, int num1) {
	if (strcmp(str1, "list") == 0) return create_list(str2);
	else if (strcmp(str1, "hashtable") == 0) return create_hash(str2);
	else if (strcmp(str1, "bitmap") == 0) return create_bm(str2, num1);
}

void dumpdata(char* str) {
	int idx = get_element_idx(str);
	if (idx != -1) {
		struct LIST* target = lists[idx];

		dumpdata_list(target);
		return;
	}
	idx = get_element_idx_hash(str);
	if (idx != -1) {
		struct HASH* target = hashs[idx];

		dumpdata_hash(target);
		return;
	}
	idx = get_element_idx_bitmap(str);
	if (idx != -1) {
		struct BITMAP* target = bitmaps[idx];

		dumpdata_bitmap(target);
		return;
	}
}

void _delete(char* str) {
	int idx = get_element_idx(str);
	if (idx != -1) {

		for (int i = idx; i < listIdx; i++) {
			lists[i] = lists[i + 1];
		}

		listIdx--;
	}
	idx = get_element_idx_hash(str);
	if (idx != -1) {

		for (int i = idx; i < hashIdx; i++) {
			hashs[i] = hashs[i + 1];
		}

		hashIdx--;
	}
	idx = get_element_idx_bitmap(str);
	if (idx != -1) {

		for (int i = idx; i < bitmapIdx; i++) {
			bitmaps[i] = bitmaps[i + 1];
		}

		bitmapIdx--;
	}
}