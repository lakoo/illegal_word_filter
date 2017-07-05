#include "word_finder.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

Word::Word(unsigned int start, unsigned int end)
: start(min(start, end))
, end(max(start, end)) {
}

CharNode::CharNode(wchar_t c)
: _c(c)
, _isEndNode(false)
, _next() {
}

CharNode::~CharNode() {
    _next.clear();
}

shared_ptr<CharNode> CharNode::nextNode(wchar_t c) const {
    if (isLeaf()) {
        return shared_ptr<CharNode>(nullptr);
    }

    auto it = _next.find(c);
    return it != _next.end() ? it->second : shared_ptr<CharNode>(nullptr);
}

bool CharNode::contains(wchar_t c) const {
    if (isLeaf()) {
        return false;
    }

    return _next.find(c) != _next.end();
}

bool CharNode::isLeaf() const {
    return _next.empty();
}

shared_ptr<CharNode> CharNode::add(wchar_t c) {
    auto it = _next.find(c);
    if (it != _next.end()) {
        return it->second;
    }

    auto newNode = make_shared<CharNode>(c);
    _next.insert(pair<wchar_t, shared_ptr<CharNode>>(c, newNode));
    return newNode;
}

WordFinder::WordFinder()
: _root(make_shared<CharNode>(L'\0')) {
}

WordFinder::WordFinder(const list<wstring> &strlist)
: WordFinder() {
    for(const wstring &str : strlist) {
        add(str);
    }
}

void WordFinder::add(const wstring &str) {
    wstring addStr = StringUtils::replace(str, L" ", L"");
    addStr = StringUtils::trim(addStr);
    addStr = StringUtils::toLowerCase(addStr);

    auto tmpNode = _root;

    for(auto c : addStr){
        tmpNode = tmpNode->add(c);
    }

    if ( tmpNode != _root){
        tmpNode->markEndNode();
    }
}

list<Word> & WordFinder::find(list<Word> &list, const wstring &str) const {
    wstring word = StringUtils::toLowerCase(str);
    unsigned int size = word.length();
    for(unsigned int i = 0U ; i < size ; ++i) {
        wchar_t charStart = word.at(i);
        if ( L' ' == charStart ) {
            continue;
        }

        auto nextNode = _root;
        unsigned int end = numeric_limits<unsigned int>::max();

        for(unsigned int j = i ; j < size ; ++j) {
            wchar_t c = word.at(j);
            if (c == L' ') {
                continue;
            }
            nextNode = nextNode->nextNode(c);
            if (!nextNode) {
                break;
            }

            if (nextNode->isEndNode()) {
                end = j;
            }
        }

        if (numeric_limits<unsigned int>::max() != end) {
            list.emplace_back(i, end);
        }
    }
    return list;
}

wstring StringUtils::replace(wstring str, const wstring &from, const wstring &to) {
    wstring::size_type begin = 0UL;
    while((begin = str.find(from, begin)) != wstring::npos) {
        str.replace(begin, from.length(), to);
        begin += to.length();
    }
    return str;
}

wstring StringUtils::trim(const wstring &str) {
    const wstring blank = L"\r\n\t ";
    size_t begin = str.find_first_not_of(blank);
    size_t end = str.find_last_not_of(blank);
    if (wstring::npos != begin || wstring::npos != end) {
        return str.substr(begin, end - begin + 1);
    }else{
        return L"";
    }
}

wstring StringUtils::toLowerCase(wstring str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

const wchar_t * StringUtils::charsToWstring(const char* str) {
    string currentLocale = setlocale(LC_ALL, "C.UTF-8");

    size_t size = mbstowcs(nullptr, str, 0UL) + 1UL;
    wchar_t *wstr = new wchar_t[size];
    wmemset(wstr, 0, size);
    mbstowcs(wstr, str, size);

    setlocale(LC_ALL, currentLocale.c_str());
    return wstr;
}

void StringUtils::free_charsToWstring(const wchar_t *str) {
    if (nullptr != str) {
        delete [] str;
    }
}

const char * StringUtils::wstringToChars(const wstring &wstr) {
    string currentLocale = setlocale(LC_ALL, "C.UTF-8");

    const wchar_t *wchars = wstr.c_str();
    size_t size = wcstombs(nullptr, wchars, 0UL) + 1UL;
    char *str = new char[size];
    memset(str, 0, size);
    wcstombs(str, wchars, size);

    setlocale(LC_ALL, currentLocale.c_str());
    return str;
}

void StringUtils::free_stringToChars(const char *str) {
    if (nullptr != str) {
        delete [] str;
    }
}

WordPurifierChekcer::WordPurifierChekcer()
: _finder() {
}

WordPurifierChekcer::WordPurifierChekcer(const list<wstring> &strlist)
: _finder(strlist) {
}

void WordPurifierChekcer::add(const wstring &str) {
    _finder.add(str);
}

wstring & WordPurifierChekcer::filter(wstring &str, wchar_t mask) const {
    list<Word> list;
    for(const Word &word : _finder.find(list, str)) {
        str.replace(word.start, word.count(), word.count(), mask);
    }
    return str;
}

bool WordPurifierChekcer::check(const wstring &str) const {
    list<Word> list;
    return _finder.find(list, str).size() > 0UL;
}
