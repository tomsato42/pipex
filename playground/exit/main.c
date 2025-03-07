#include <stdio.h>
#include <stdlib.h>

typedef struct s_test
{
	char	*str;
}			t_test;

typedef struct s_memory_manager {
    void    **pointers;   // 確保したメモリへのポインタの配列
    int     count;        // 現在管理しているポインタの数
    int     capacity;     // 配列の最大容量
} t_memory_manager;

// 初期化関数
t_memory_manager *init_memory_manager(int initial_capacity) {
    t_memory_manager *mm = malloc(sizeof(t_memory_manager));
    if (!mm)
        return NULL;
    
    mm->pointers = malloc(sizeof(void *) * initial_capacity);
    if (!mm->pointers) {
        free(mm);
        return NULL;
    }
    
    mm->count = 0;
    mm->capacity = initial_capacity;
    return mm;
}

// メモリ追加関数
int track_memory(t_memory_manager *mm, void *ptr) {
    if (mm->count >= mm->capacity) {
        // 必要に応じて拡張
        int new_capacity = mm->capacity * 2;
        void **new_pointers = realloc(mm->pointers, sizeof(void *) * new_capacity);
        if (!new_pointers)
            return 0;
        mm->pointers = new_pointers;
        mm->capacity = new_capacity;
    }
    
    mm->pointers[mm->count++] = ptr;
    return 1;
}

// 一括解放関数
void cleanup_all(t_memory_manager *mm) {
    for (int i = 0; i < mm->count; i++) {
        free(mm->pointers[i]);
    }
    free(mm->pointers);
    free(mm);
}

// エラー終了用関数
void exit_with_cleanup(t_memory_manager *mm, int status, const char *message) {
    if (message)
        fprintf(stderr, "Error: %s\n", message);
    cleanup_all(mm);
    exit(status);
}

int	main(void)
{
	char	*test_str;
	t_test	test_struct;
    t_memory_manager *mm = init_memory_manager(10);
    if (!mm) {
        fprintf(stderr, "Failed to initialize memory manager.\n");
        return 1;
    }

	printf("This is a program demonstrating the use of exit function.\n");
	// Some condition to exit the progra
	test_str = (char *)malloc(sizeof(char) * 5);
    if (!track_memory(mm, test_str)) {
        exit_with_cleanup(mm, 1, "Failed to track memory.");
    }
	test_struct.str = test_str;
	if (1)
	{
		printf("Exiting the program with status code 0.\n");
		cleanup_all(mm);
		exit(0); // Exit the program with status code 0 (success)
	}
	// This code will not be executed
	printf("This line will not be printed.\n");
	return (0);
}
