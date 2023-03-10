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

#define KEY_LENGTH 3

void main(void) {
    char* v = dynamic_string("gzfgd");
    char* k = dynamic_string("aaa");
	
	for(int a = 1; a <= 26; a++) {
		for(int b = 1; b <= 26; b++) {
			for(int c = 1; c <= 26; c++) {
				k[2] = ia(c);
				printf("%s : ", k);
				char* d = decrypt(v, strlen(v), k, KEY_LENGTH);
				printf("%s\n", d);   
			}
			k[1] = ia(b);
			printf("%s : ", k);
			char* d = decrypt(v, strlen(v), k, KEY_LENGTH);
			printf("%s\n", d);   
		}
		k[0] = ia(a);
		printf("%s : ", k);
		char* d = decrypt(v, strlen(v), k, KEY_LENGTH);
		printf("%s\n", d);   
	}

}
