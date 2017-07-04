#include "illegal_word.h"
#include <stdio.h>

int main(void){
    void * handle = illegal_word_init();
    illegal_word_add(handle, "hello");
    printf("result: %s\n", illegal_word_filter(handle, "hello world"));
    illegal_word_destroy(handle);
}
