#include "shared.h"

int main(void)
{
    Compdb db = {0};
    
    // Test 1: Add entry with output
    Cmd cmd1 = {0};
    cmd_append(&cmd1, "cc", "-c", "-Wall", "-o", "test.o", "test.c");
    compdb_add(&db, &cmd1, "test.c", .output = "test.o");
    printf("Added entry 1: file=%s, output=%s, argc=%zu\n", 
           db.items[0].file, db.items[0].output, db.items[0].arguments.count);
    
    // Test 2: Add entry without output
    Cmd cmd2 = {0};
    cmd_append(&cmd2, "cc", "-c", "-I./include", "main.c");
    compdb_add(&db, &cmd2, "main.c");
    printf("Added entry 2: file=%s, output=%s, argc=%zu\n", 
           db.items[1].file, db.items[1].output ? db.items[1].output : "NULL", db.items[1].arguments.count);
    
    // Test 3: Save to file
    if (!compdb_save(&db, "test_compdb.json")) {
        printf("Failed to save compilation database\n");
        return 1;
    }
    printf("Saved compilation database to test_compdb.json\n");
    
    // Test 4: Free database
    compdb_free(&db);
    printf("Freed compilation database: count=%zu, capacity=%zu\n", db.count, db.capacity);
    
    return 0;
}
