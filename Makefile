all:
	@g++ -std=c++11 -fPIC $(CFLAGS) $(LDFLAGS) -shared -o libillegalword.so word_finder.cpp illegal_word.cpp
