
#ifndef WORD_PURIFIER_H_
#define WORD_PURIFIER_H_

#ifdef __cplusplus
extern "C" {
#endif
void * word_purifier_init(void);
void word_purifier_destroy(void *handle);
void word_purifier_add(void *handle, const char *str);
const char * word_purifier_filter(void *handle, const char *str, const char *mask);
void word_purifier_free_str(const char *str);
char word_purifier_check(void *handle, const char *str);
#ifdef __cplusplus
}
#endif

#endif /* WORD_PURIFIER_H_ */
