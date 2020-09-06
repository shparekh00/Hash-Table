#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_NAME 256
#define TABLE_SIZE 8
#define NUM_PEOPLE 12

/**
 * This code implements a hash table that stores 
 * person objects.
 * The hash table is made up of hash buckets at each
 * index. 
 * Each hash bucket keeps track of the set of person 
 * objects mapped to that index of the hash table.
 * 
 */

typedef struct {
    char name[MAX_NAME];
    int age;
} person_t;

typedef struct listnode {
    struct listnode* next;
    person_t* val;
} listnode_t; 

typedef struct hash_bucket {
    listnode_t* head;
    listnode_t* tail;
    int size;
} hash_bucket_t;


// declare hash table
hash_bucket_t hash_table[TABLE_SIZE];

/**
 * Returns hash corresponding to person's name
 */
unsigned int hash_function(char *name) {
    unsigned int hash = 0;
    for (int i = 0; i < strlen(name); i++) {
        hash += name[i];
        hash *= name[i]*3;
    }
    return hash % TABLE_SIZE;
}
/**
 * Initializes values in hash table to null
 */
void init_hash_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        //hash_table[i] = (hash_bucket_t*)malloc(sizeof(struct hash_bucket));
        hash_table[i].head = NULL;
        hash_table[i].tail = NULL;
        hash_table[i].size = 0;
    }
}

/**
 * Print each entry of hash table on separate row
 */
void print_hash_table() {
    printf("start\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table[i].head != NULL) {
            // print table index
            printf("%i\t", i);
            listnode_t* tmp = hash_table[i].head;
            // print each person in hash bucket on same row
            while (tmp) {
                printf("%s\t",tmp->val->name);
                tmp = tmp->next;
            }
            printf("\n");
        }
        else {
            // if no entry at the table index print dashed line
            printf("%i\t-------\n", i);
        }
    } 
    printf("end\n");
}

/**
 * Insert new values in hash table
 */
void hash_table_insert(person_t *p) {
    int index = hash_function(p->name);
    
    // create new listnode object to insert in hash table
    listnode_t* node = malloc(sizeof(struct listnode));
    node->val = p;
    node->next = NULL;

    if (hash_table[index].head == NULL) {
        // add first element to hash bucket
        hash_table[index].head = node;
    }
    else {
        if(hash_table[index].tail == NULL) {
            // add the second node of the hash bucket
            hash_table[index].head->next = node;
            hash_table[index].tail = node;
            
        } 
        else {
            // add new element to hash bucket
            hash_table[index].tail->next = node;
            // move tail to last element
            hash_table[index].tail = hash_table[index].tail->next;
        }
    }
    // increase size of the hash_bucket we inserted in
    hash_table[index].size += 1;
}

/**
 * Search for person object in the hash table
 */
person_t* hash_table_lookup(char* name) {
    int index = hash_function(name);
    if (hash_table[index].head == NULL) {
        printf("%s not found!", name);
        return NULL;
    }
    else {
        listnode_t* tmp = hash_table[index].head;
        while(tmp) {
            if(strcmp(tmp->val->name,name) == 0) {
                printf("Found %s!\nname: %s age: %i\n", name, name, tmp->val->age);
                return tmp->val;
            }
            tmp = tmp->next;
        }
        return NULL;
    }
}

int main() {
    // declare person objects
    person_t shivani = {.name="Shivani", .age = 20};
    person_t liz = {.name="Liz", .age = 20};
    person_t gem = {.name="Gem", .age = 20};
    person_t aranza = {.name="Aranza", .age = 21};
    person_t jessica = {.name="Jessica", .age = 21};
    person_t brady = {.name="Brady", .age = 20};
    person_t ritu = {.name="Ritu", .age = 26};
    person_t parth = {.name="Parth", .age = 20};
    person_t molly = {.name="Molly", .age = 25};
    person_t ginny = {.name="Ginny", .age = 15};
    person_t jesus = {.name="Jesus", .age = 25};
    person_t ose = {.name="Ose", .age = 24};

    person_t* people[NUM_PEOPLE] = {&shivani, &liz, &gem, &aranza, &jessica, &brady, &ritu, 
                        &parth, &molly, &ginny, &jesus, &ose};

    init_hash_table();

    // insert each person object into hash table
    for (int i = 0; i < NUM_PEOPLE; i++) {
        hash_table_insert(people[i]);
    }
    
    hash_table_lookup("Jen");
    hash_table_lookup("Jessica");

    print_hash_table();

    return 0;
}