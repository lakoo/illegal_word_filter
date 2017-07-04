
#ifndef ILLEGAL_WORD_H_
#define ILLEGAL_WORD_H_

#ifdef __cplusplus
extern "C" {
#endif
void * illegal_word_init(void);
void illegal_word_destroy(void *handle);
void illegal_word_add(void *handle, const char* str);
const char * illegal_word_filter(void *handle, const char *str);
void illegal_word_free_str(const char *str);
char illegal_word_check(void *handle, const char *str);
#ifdef __cplusplus
}
#endif

#endif /* ILLEGAL_WORD_H_ */
