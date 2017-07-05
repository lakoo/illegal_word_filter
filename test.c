#include "word_purifier.h"
#include <stdio.h>

int main(void){
    void * handle = word_purifier_init();
    word_purifier_add(handle, "hello");
    word_purifier_add(handle, "a");
    word_purifier_add(handle, "ab");
    word_purifier_add(handle, "");
    printf("result: %s\n", word_purifier_filter(handle, "hello world", ""));
    printf("result: %s\n", word_purifier_filter(handle, "abca", "x"));
    word_purifier_destroy(handle);
}
