#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define HASHMAP_SIZE 64
#define HASHMAP_SIZE_LIST 1

struct aiv_set_item
{
    const char *key;
    size_t key_len;
};

struct aiv_set
{
    struct aiv_set_item hashmap[HASHMAP_SIZE][HASHMAP_SIZE_LIST];
};

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

void aiv_set_insert(struct aiv_set *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len == 0)
        {
            set->hashmap[index][i].key = key;
            set->hashmap[index][i].key_len = key_len;
            printf("added %s at index %llu slot %llu\n", key, index, i);
            return;
        }
        else if (set->hashmap[index][i].key_len == key_len && memcmp(set->hashmap[index][i].key, key, key_len) == 0)
        {
            printf("Duplicate key %s found at index %llu slot %llu\n", key, index, i);
            return;
        }
    }

    printf("COLLISION! for %s (index %llu)\n", key, index);
}

void aiv_set_search(struct aiv_set *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len > 0)
        {
            if (set->hashmap[index][i].key_len == key_len && memcmp(set->hashmap[index][i].key, key, key_len) == 0)
            {
                printf("FOUND %s at index %llu slot %llu\n", key, index, i);
                return;
            }
        }
    }

    printf("Key %s not found in the set\n", key);
}

void aiv_set_remove(struct aiv_set *set, const char *key)
{
    const size_t key_len = strlen(key);

    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % HASHMAP_SIZE;

    printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

    for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
    {
        if (set->hashmap[index][i].key_len > 0)
        {
            if (set->hashmap[index][i].key_len == key_len && memcmp(set->hashmap[index][i].key, key, key_len) == 0)
            {
                printf("REMOVING %s from index %llu slot %llu\n", key, index, i);
                set->hashmap[index][i].key_len = 0;
                set->hashmap[index][i].key = NULL;
                return;
            }
        }
    }

    printf("Key %s not found in the set, nothing to remove\n", key);
}

int main(int argc, char **argv)
{
    struct aiv_set myset;
    memset(&myset, 0, sizeof(struct aiv_set));

    aiv_set_insert(&myset, "Hello");
    aiv_set_insert(&myset, "Hello2");
    aiv_set_insert(&myset, "Test");
    aiv_set_insert(&myset, "Foobar");
    aiv_set_insert(&myset, "XYZ");
    aiv_set_insert(&myset, "AAAAAA");
    aiv_set_insert(&myset, "AAAAAa");

    aiv_set_search(&myset, "XYZ");

    aiv_set_remove(&myset, "XYZ");

    aiv_set_search(&myset, "XYZ");

    return 0;
}