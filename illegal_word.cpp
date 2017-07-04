#include "illegal_word.h"

#include "word_finder.h"
#include <iostream>

using namespace std;

void * illegal_word_init() {
    return new IllegalWordChecker();
}

void illegal_word_destroy(void *handle) {
    if (nullptr == handle){
        return;
    }
    delete reinterpret_cast<IllegalWordChecker *>(handle);
}

void illegal_word_add(void *handle, const char* str){
    if (nullptr == handle) {
        return;
    }
    IllegalWordChecker *checker = reinterpret_cast<IllegalWordChecker *>(handle);
    const wchar_t *wstr = StringUtils::charsToWstring(str);
    checker->add(wstr);
    StringUtils::free_charsToWstring(wstr);
}

const char * illegal_word_filter(void *handle, const char *str){
    if (nullptr == handle){
        return nullptr;
    }

    IllegalWordChecker *checker = reinterpret_cast<IllegalWordChecker *>(handle);
    const wchar_t *wstrPtr = StringUtils::charsToWstring(str);
    wstring wstr(wstrPtr);
    wstring result = checker->filter(wstr);
    return StringUtils::wstringToChars(result);
}

void illegal_word_free_str(const char *str){
    StringUtils::free_stringToChars(str);
}

char illegal_word_check(void *handle, const char *str){
    if (nullptr == handle){
        return 0;
    }
    IllegalWordChecker *checker = reinterpret_cast<IllegalWordChecker *>(handle);
    const wchar_t *wstr = StringUtils::charsToWstring(str);
    bool result = checker->check(wstr);
    StringUtils::free_charsToWstring(wstr);
    return result ? 1 : 0;
}
