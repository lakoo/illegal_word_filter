CC = g++ -std=c++11 $(CFLAGS) $(LDFLAGS) -c

TARGET = libwordpurifier.a

SRC = word_finder.cpp \
      word_purifier.cpp

OBJ = $(SRC:.cpp=.o)

AR = ar 

all: $(TARGET)

$(TARGET):$(OBJ)
	@$(AR) -cr $(TARGET) $(OBJ)
	@rm -rf $(OBJ)

$(OBJ):
	$(CC) $(SRC)
