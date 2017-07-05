#include "word_purifier.h"

#include "word_finder.h"
#include <iostream>

using namespace std;

void * word_purifier_init() {
    return new WordPurifierChekcer();
}

void word_purifier_destroy(void *handle) {
    if (nullptr == handle){
        return;
    }
    delete reinterpret_cast<WordPurifierChekcer *>(handle);
}

void word_purifier_add(void *handle, const char* str){
    if (nullptr == handle) {
        return;
    }
    WordPurifierChekcer *checker = reinterpret_cast<WordPurifierChekcer *>(handle);
    const wchar_t *wstr = StringUtils::charsToWstring(str);
    checker->add(wstr);
    StringUtils::free_charsToWstring(wstr);
}

const char * word_purifier_filter(void *handle, const char *str, const char *mask){
    if (nullptr == handle){
        return nullptr;
    }

    const wchar_t *maskPtr = StringUtils::charsToWstring(mask);
    wchar_t maskChar = wcslen(maskPtr) ? maskPtr[0] : L'*';
    StringUtils::free_charsToWstring(maskPtr);

    WordPurifierChekcer *checker = reinterpret_cast<WordPurifierChekcer *>(handle);
    const wchar_t *wstrPtr = StringUtils::charsToWstring(str);
    wstring wstr(wstrPtr);
    wstring result = checker->filter(wstr, maskChar);

    return StringUtils::wstringToChars(result);
}

void word_purifier_free_str(const char *str){
    StringUtils::free_stringToChars(str);
}

char word_purifier_check(void *handle, const char *str){
    if (nullptr == handle){
        return 0;
    }
    WordPurifierChekcer *checker = reinterpret_cast<WordPurifierChekcer *>(handle);
    const wchar_t *wstr = StringUtils::charsToWstring(str);
    bool result = checker->check(wstr);
    StringUtils::free_charsToWstring(wstr);
    return result ? 1 : 0;
}
