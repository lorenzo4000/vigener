#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

char* resize_key(char* key, unsigned int len, unsigned int new_len) {
    if(new_len < len) {
        return NULL;
    }
    
    key = (char*)realloc(key, new_len);
    for(int i = 0; i < new_len; i++) {
        key[i] = key[i % len];
    }
    return key;
}

// 1 - 26 : (a-z / A-Z)
// -1 : out of range
int ai(char c) {
    if(c >= 97 && c <= 122) {
        return c - 96;
    }
    if(c >= 65 && c <= 90) {
        return c - 64;
    }
    return -1;
}

// A-Z : (1 - 26)
char ia(int i) {
    return i + 64;
}

char* encrypt(char* str, unsigned int len, char* key, int key_len) {
    key = resize_key(key, key_len, len);
    if(key == NULL) {
        return NULL;
    }

    for(int i=0; i < len; i++) {
        char a = ai(str[i]);
        char b = ai(key[i]);
        str[i] = ia((((a + b) - 1) % 26) + 1);
    }
    return str;
}

char* decrypt(char* str, unsigned int len, char* key, int key_len) {
    key = resize_key(key, key_len, len);
    if(key == NULL) {
        return NULL;
    }

    for(int i=0; i < len; i++) {
        char a = ai(str[i]);
        char b = ai(key[i]);
        str[i] = ia((((((a - b) - 1) % 26) + 26) % 26) + 1);
    }
    return str;
}

char* dynamic_string(const char* cstr) {
    unsigned int len = strlen(cstr);
    char* dyn = malloc(len);
    if(dyn == NULL) {
        return NULL;
    }

    dyn = strcpy(dyn, cstr);
    return dyn;
}

void main(void) {
    char* v = dynamic_string("ilcifrariodivernererutilizza");
    char* k = dynamic_string("esempiodichiavelunga");
    
    char* e = encrypt(v, strlen(v), k, strlen(k));
    printf("%s\n", e);
    
    char* d = decrypt(e, strlen(e), k, strlen(k));
    printf("%s\n\n\n", d);

    free(v);
    free(k);

    v = dynamic_string("gzfgd");
    k = dynamic_string("eysee");

    d = decrypt(v, strlen(v), k, strlen(k));
    printf("%s\n", d);   
}
