#include "st.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static unsigned long st_hash(const char *str) {
    // djb2 hash
    unsigned long hash = 5381UL;
    int c;
    while ((c = (unsigned char)(*str++)) != 0) {
        hash = ((hash << 5) + hash) + (unsigned long)c; // hash * 33 + c
    }
    return hash;
}

static char *st_strdup(const char *s) {
    size_t n = strlen(s) + 1u;
    char *p = (char *)malloc(n);
    if (!p) return NULL;
    memcpy(p, s, n);
    return p;
}

SymbolTable *st_create(int capacity) {
    if (capacity <= 0) capacity = 101; // default prime-ish
    SymbolTable *st = (SymbolTable *)calloc(1, sizeof(SymbolTable));
    if (!st) return NULL;
    st->capacity = capacity;
    st->buckets = (STEntry **)calloc((size_t)capacity, sizeof(STEntry *));
    if (!st->buckets) {
        free(st);
        return NULL;
    }
    st->size = 0;
    return st;
}

void st_destroy(SymbolTable *st) {
    if (!st) return;
    for (int i = 0; i < st->capacity; ++i) {
        STEntry *e = st->buckets[i];
        while (e) {
            STEntry *next = e->next;
            free(e->key);
            free(e);
            e = next;
        }
    }
    free(st->buckets);
    free(st);
}

STEntry *st_lookup(SymbolTable *st, const char *key) {
    if (!st || !key) return NULL;
    unsigned long h = st_hash(key) % (unsigned long)st->capacity;
    STEntry *e = st->buckets[h];
    while (e) {
        if (strcmp(e->key, key) == 0) return e;
        e = e->next;
    }
    return NULL;
}

STEntry *st_insert(SymbolTable *st, const char *key) {
    if (!st || !key) return NULL;
    unsigned long h = st_hash(key) % (unsigned long)st->capacity;
    STEntry *e = st->buckets[h];
    int chainIndex = 0;
    while (e) {
        if (strcmp(e->key, key) == 0) return e;
        e = e->next;
        chainIndex++;
    }
    STEntry *ne = (STEntry *)calloc(1, sizeof(STEntry));
    if (!ne) return NULL;
    ne->key = st_strdup(key);
    ne->bucketIndex = (int)h;
    ne->chainIndex = chainIndex;
    ne->next = st->buckets[h];
    st->buckets[h] = ne;
    st->size++;
    return ne;
}

bool st_write_to_file(SymbolTable *st, const char *filepath) {
    if (!st || !filepath) return false;
    FILE *f = fopen(filepath, "w");
    if (!f) return false;
    fprintf(f, "# Symbol Table (hash table)\n");
    fprintf(f, "# size=%d capacity=%d\n", st->size, st->capacity);
    for (int i = 0; i < st->capacity; ++i) {
        STEntry *e = st->buckets[i];
        while (e) {
            fprintf(f, "%s -> (%d,%d)\n", e->key, e->bucketIndex, e->chainIndex);
            e = e->next;
        }
    }
    fclose(f);
    return true;
}


