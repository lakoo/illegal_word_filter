#ifndef WORLD_FINDER_H_
#define WORLD_FINDER_H_

#include <cstring>
#include <list>
#include <map>
#include <memory>
#include <string>

class CharNode;

typedef std::map<wchar_t, std::shared_ptr<CharNode>> CHAR_MAP;

struct Word
{
    unsigned int start;
    unsigned int end;
    Word(unsigned int start, unsigned int end);
    ~Word() = default;
    Word(const Word &) = delete;
    Word &operator=(const Word &) = delete;

    inline size_t count() const { return end - start + 1UL;}
};

class CharNode
{
    public:
        explicit CharNode(wchar_t c);
        ~CharNode();
        CharNode(const CharNode &) = delete;
        CharNode & operator=(const CharNode &) = delete;

        inline wchar_t c() const { return _c; }
        inline bool isEndNode() const { return _isEndNode; }
        inline void markEndNode() { _isEndNode = true; }

        std::shared_ptr<CharNode> nextNode(wchar_t c) const;
        bool contains(wchar_t c) const;
        bool isLeaf() const;
        std::shared_ptr<CharNode> add(wchar_t c);

    private:
        wchar_t _c;
        bool _isEndNode;
        CHAR_MAP _next;
};

class WordFinder {
    public:
        WordFinder();
        explicit WordFinder(const std::list<std::wstring> &strlist);
        ~WordFinder() = default;
        WordFinder(const WordFinder &) = delete;
        WordFinder & operator=(const WordFinder &) = delete;

        void add(const std::wstring &str);
        std::list<Word> & find(std::list<Word> &list, const std::wstring &str) const;

    private:
        std::shared_ptr<CharNode> _root;
};

namespace StringUtils {
    std::wstring trim(const std::wstring &str);
    std::wstring replace(std::wstring str, const std::wstring &from, const std::wstring &to);
    std::wstring toLowerCase(std::wstring str);

    const wchar_t * charsToWstring(const char *str);
    void free_charsToWstring(const wchar_t *str);

    const char * wstringToChars(const std::wstring &wstr);
    void free_stringToChars(const char *str);
};

class WordPurifierChekcer {
    public:
        WordPurifierChekcer();
        explicit WordPurifierChekcer(const std::list<std::wstring> &strlist);
        ~WordPurifierChekcer() = default;
        WordPurifierChekcer(const WordPurifierChekcer &) = delete;
        WordPurifierChekcer & operator=(const WordPurifierChekcer &) = delete;
        void add(const std::wstring &str);
        std::wstring & filter(std::wstring &str, wchar_t mask) const;
        bool check(const std::wstring &str) const;
    private:
        WordFinder _finder;
};

#endif /* WORLD_FINDER_H_ */
