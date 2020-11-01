#include "main.h"


int main() {
	char str[100] = { 0 };
	char str1[30], str2[30], str3[30];
	int num1, num2, num3;
	size_t sz1, sz2, sz3;
	bool value;

	while (true) {
		str1[0] = str2[0] = str3[0] = '\0';
		num1 = num2 = num3 = 0;
		sz1 = sz2 = sz3 = 0;
		value = true;
		fgets(str, 100, stdin);

		sscanf(str, "%s ", str1);
		
		if (strcmp(str1, "quit") == 0) 
			break;
		
		else if (strcmp(str1, "create") == 0) {
			sscanf(str, "%*s %s %s %d", str2, str3, &num1);
			create(str2, str3, num1);
			
		}
		else if (strcmp(str1, "dumpdata") == 0) {
			sscanf(str, "%*s %s", str2);
			dumpdata(str2);
		}
		else if (strcmp(str1, "delete") == 0) {
			sscanf(str, "%*s %s", str2);
			_delete(str2);

		}

		// list
		else if (strcmp(str1, "list_push_back") == 0) {
			sscanf(str, "%*s %s %d", str2, &num1);
			list_pb(str2, num1);
		}
		else if (strcmp(str1, "list_push_front") == 0) {
			sscanf(str, "%*s %s %d", str2, &num1);
			list_pf(str2, num1);
		}
		else if (strcmp(str1, "list_pop_back") == 0) {
			sscanf(str, "%*s %s", str2);
			list_pop_back(&(lists[get_element_idx(str2)]->List));
		}
		else if (strcmp(str1, "list_pop_front") == 0) {
			sscanf(str, "%*s %s", str2);
			list_pop_front(&(lists[get_element_idx(str2)]->List));
		}
		else if (strcmp(str1, "list_back") == 0) {
			sscanf(str, "%*s %s", str2);
			printf("%d\n", list_entry(list_back(&(lists[get_element_idx(str2)]->List)), struct list_item, elem)->data);
		}
		else if (strcmp(str1, "list_front") == 0) {
			sscanf(str, "%*s %s", str2);
			printf("%d\n", list_entry(list_front(&(lists[get_element_idx(str2)]->List)), struct list_item, elem)->data);
		}
		else if (strcmp(str1, "list_insert") == 0) {
			sscanf(str, "%*s %s %d %d", str2, &num1, &num2);
			list_insert_(str2, num1, num2);
		}
		else if (strcmp(str1, "list_insert_ordered") == 0) {
			sscanf(str, "%*s %s %d", str2, &num1);
			list_insert_order(str2, num1);
		}
		else if (strcmp(str1, "list_empty") == 0) {
			sscanf(str, "%*s %s", str2);
			if (list_empty(&(lists[get_element_idx(str2)]->List))) printf("true\n");
			else printf("false\n");
		}
		else if (strcmp(str1, "list_size") == 0) {
			sscanf(str, "%*s %s", str2);
			printf("%zu\n", list_size(&(lists[get_element_idx(str2)]->List)));
		}
		else if (strcmp(str1, "list_max") == 0) {
			sscanf(str, "%*s %s", str2);
			printf("%d\n", list_entry(list_max(&(lists[get_element_idx(str2)]->List), cmp, NULL), struct list_item, elem)->data);
		}
		else if (strcmp(str1, "list_min") == 0) {
			sscanf(str, "%*s %s", str2);
			printf("%d\n", list_entry(list_min(&(lists[get_element_idx(str2)]->List), cmp, NULL), struct list_item, elem)->data);
		}
		else if (strcmp(str1, "list_remove") == 0) {
			sscanf(str, "%*s %s %d", str2, &num1);
			struct LIST *l = lists[get_element_idx(str2)];
			struct list_elem* cur = list_begin(&(l->List));
			for (; num1--; cur = list_next(cur));
			list_remove(cur);
		}
		else if (strcmp(str1, "list_reverse") == 0) {
			sscanf(str, "%*s %s", str2);
			list_reverse(&(lists[get_element_idx(str2)]->List));
		}
		else if (strcmp(str1, "list_shuffle") == 0) {
			sscanf(str, "%*s %s", str2);
			list_shuffle(&(lists[get_element_idx(str2)]->List));
		}
		else if (strcmp(str1, "list_sort") == 0) {
			sscanf(str, "%*s %s", str2);
			list_sort(&(lists[get_element_idx(str2)]->List),cmp,NULL);
		}
		else if (strcmp(str1, "list_splice") == 0) {
			sscanf(str, "%*s %s %d %s %d %d", str2, &num1, str3, &num2, &num3);
			struct LIST *l1 = lists[get_element_idx(str2)];
			struct LIST *l2 = lists[get_element_idx(str3)];
			struct list_elem* before = list_begin(&(l1->List));
			struct list_elem* from = list_begin(&(l2->List));
			struct list_elem* to = list_begin(&(l2->List));
			for (; num1--; before = list_next(before));
			for (; num2--; from = list_next(from));
			for (; num3--; to = list_next(to));
			list_splice(before, from, to);
		}
		else if (strcmp(str1, "list_swap") == 0) {
			sscanf(str, "%*s %s %d %d", str2, &num1, &num2);
			struct LIST *l1 = lists[get_element_idx(str2)];
			struct list_elem* a = list_begin(&(l1->List));
			struct list_elem* b = list_begin(&(l1->List));
			for (; num1--; a = list_next(a));
			for (; num2--; b = list_next(b));
			list_swap(a, b);
		}
		else if (strcmp(str1, "list_unique") == 0) {
			sscanf(str, "%*s %s %s", str2, str3);
			list_unique(&(lists[get_element_idx(str2)]->List), &(lists[get_element_idx(str3)]->List), cmp, NULL);
		}

		//hash
		/*
		else if (strcmp(str1, "hash_create") == 0) {
			sscanf(str, "%*s %s %s", str2, str3);
			create(str2, str3);
		}
		*/
		else if (strcmp(str1, "hash_insert") == 0) {
			sscanf(str, "%*s %s %d", str2, &num1);
			struct hash_item* tmp = (struct hash_item*)malloc(sizeof(struct hash_item));
			tmp->data = num1;
			hash_insert(&(hashs[get_element_idx_hash(str2)]->Hash), &(tmp->elem));
		}
		else if (strcmp(str1, "hash_apply") == 0) {
			sscanf(str, "%*s %s %s", str2, str3);
			if (strcmp(str3, "square") == 0)
				hash_apply(&(hashs[get_element_idx_hash(str2)]->Hash), hash_square);
			else if (strcmp(str3, "triple") == 0)
				hash_apply(&(hashs[get_element_idx_hash(str2)]->Hash), hash_triple);
		}
		else if (strcmp(str1, "hash_delete") == 0) {
			sscanf(str, "%*s %s %d", str2, &num1);
			struct hash_item* tmp = (struct hash_item*)malloc(sizeof(struct hash_item));
			tmp->data = num1;
			hash_delete(&(hashs[get_element_idx_hash(str2)]->Hash), &(tmp->elem));
		}
		else if (strcmp(str1, "hash_empty") == 0) {
			sscanf(str, "%*s %s", str2);
			if (hash_empty(&(hashs[get_element_idx_hash(str2)]->Hash))) printf("true\n");
			else printf("false\n");
		}
		else if (strcmp(str1, "hash_size") == 0) {
			sscanf(str, "%*s %s", str2);
			printf("%zu\n", hash_size(&(hashs[get_element_idx_hash(str2)]->Hash)));
		}
		else if (strcmp(str1, "hash_clear") == 0) {
			sscanf(str, "%*s %s", str2);
			hash_clear(&(hashs[get_element_idx_hash(str2)]->Hash), NULL);
		}
		else if (strcmp(str1, "hash_find") == 0) {
			sscanf(str, "%*s %s %d", str2, &num1);
			struct hash_item* tmp = (struct hash_item*)malloc(sizeof(struct hash_item));
			tmp->data = num1;
			if (hash_find(&(hashs[get_element_idx_hash(str2)]->Hash), &(tmp->elem))) {
				printf("%d\n", hash_entry(hash_find(&(hashs[get_element_idx_hash(str2)]->Hash), &(tmp->elem)),struct hash_item, elem)->data);
			}
		}
		else if (strcmp(str1, "hash_replace") == 0) {
			sscanf(str, "%*s %s %d", str2, &num1);
			struct hash_item* tmp = (struct hash_item*)malloc(sizeof(struct hash_item));
			tmp->data = num1;
			hash_replace(&(hashs[get_element_idx_hash(str2)]->Hash), &(tmp->elem));
		}
		
		//bitmap
		else if (strcmp(str1, "bitmap_mark") == 0) {
			sscanf(str, "%*s %s %d", str2, &num1);
			bitmap_mark(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, num1);
		}
		else if (strcmp(str1, "bitmap_any") == 0) {
			sscanf(str, "%*s %s %d %d", str2, &num1, &num2);
			if (bitmap_any(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, num1, num2)) printf("true\n");
			else printf("false\n");
			
		}
		else if (strcmp(str1, "bitmap_all") == 0) {
			sscanf(str, "%*s %s %d %d", str2, &num1, &num2);
			if (bitmap_all(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, num1, num2)) printf("true\n");
			else printf("false\n");
		}
		else if (strcmp(str1, "bitmap_contains") == 0) {
			sscanf(str, "%*s %s %d %d %s", str2, &num1, &num2, str3);
			if (strcmp(str3, "true") == 0) 
				value = true;
			else 
				value = false;
			if (bitmap_contains(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, num1, num2, value) == true) printf("true\n");
			else printf("false\n");
		}
		else if (strcmp(str1, "bitmap_count") == 0) {
			sscanf(str, "%*s %s %d %d %s", str2, &num1, &num2, str3);
			if (strcmp(str3, "true") == 0) value = true;
			else value = false;
			printf("%zu\n", bitmap_count(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, num1, num2, value));
		}
		else if (strcmp(str1, "bitmap_dump") == 0) {
			sscanf(str, "%*s %s", str2);
			bitmap_dump(bitmaps[get_element_idx_bitmap(str2)]->Bitmap);
		}
		else if (strcmp(str1, "bitmap_expand") == 0) {
			sscanf(str, "%*s %s %d", str2, &num1);
			int tmp = get_element_idx_bitmap(str2);
			bitmaps[tmp]->Bitmap = bitmap_expand(bitmaps[tmp]->Bitmap, num1);
		}
		else if (strcmp(str1, "bitmap_set_all") == 0) {
			sscanf(str, "%*s %s %s", str2, str3);
			if (strcmp(str3, "true") == 0) value = true;
			else value = false;
			bitmap_set_all(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, value);
		}
		else if (strcmp(str1, "bitmap_flip") == 0) {
			sscanf(str, "%*s %s %d", str2, &num1);
			bitmap_flip(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, num1);
		}
		else if (strcmp(str1, "bitmap_none") == 0) {
			sscanf(str, "%*s %s %d %d", str2, &num1, &num2);
			if (bitmap_none(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, num1, num2) == true) printf("true\n");
			else printf("false\n");
		}
		else if (strcmp(str1, "bitmap_reset") == 0) {
			sscanf(str, "%*s %s %d", str2, &num1);
			bitmap_reset(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, num1);
		}
		else if (strcmp(str1, "bitmap_scan") == 0) {
			sscanf(str, "%*s %s %d %d %s", str2, &num1, &num2, str3);
			if (strcmp(str3, "true") == 0) value = true;
			else value = false;
			printf("%zu\n", bitmap_scan(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, num1, num2, value));
		}
		else if (strcmp(str1, "bitmap_scan_and_flip") == 0) {
			sscanf(str, "%*s %s %d %d %s", str2, &num1, &num2, str3);
			if (strcmp(str3, "true") == 0) value = true;
			else value = false;
			printf("%zu\n", bitmap_scan_and_flip(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, num1, num2, value));
		}
		else if (strcmp(str1, "bitmap_set") == 0) {
			sscanf(str, "%*s %s %d %s", str2, &num1, str3);
			if (strcmp(str3, "true") == 0) value = true;
			else value = false;
			bitmap_set(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, num1, value);
		}
		else if (strcmp(str1, "bitmap_set_all") == 0) {
			sscanf(str, "%*s %s %s", str2, str3);
			if (strcmp(str3, "true") == 0) value = true;
			else value = false;
			bitmap_set_all(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, value);
		}
		else if (strcmp(str1, "bitmap_set_multiple") == 0) {
			sscanf(str, "%*s %s %d %d %s", str2, &num1, &num2, str3);
			if (strcmp(str3, "true") == 0) value = true;
			else value = false;
			bitmap_set_multiple(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, num1, num2, value);
		}
		else if (strcmp(str1, "bitmap_size") == 0) {
			sscanf(str, "%*s %s", str2);
			printf("%zu\n", bitmap_size(bitmaps[get_element_idx_bitmap(str2)]->Bitmap));
		}
		else if (strcmp(str1, "bitmap_test") == 0) {
			sscanf(str, "%*s %s %d", str2, &num1);
			if (bitmap_test(bitmaps[get_element_idx_bitmap(str2)]->Bitmap, num1)) printf("true\n");
			else printf("false\n");
		}

	}
	return 0;
}