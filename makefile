CXX=g++
LIBS=-pthread
RM = rm -f
SERVER_EXE = server
CLIENT_EXE = client
SERVER_SRCS = main.cpp AVLTree.cpp AVLTree.h
SERVER_OBJS = $(SERVER_SRCS:.cpp=.o)
CLIENT_SRCS  = client.cpp
CLIENT_OBJS = $(CLIENT_SRCS:.cpp=.o)

all : server client

server :main.o
	$(CXX) main.o -o server $(LIBS)

client:client.o
	$(CXX) client.o -o client

main.o:AVLTree.cpp AVLTree.h main.cpp
	$(CXX) -c main.cpp

client.o:client.cpp
	$(CXX) -c client.cpp

clean:
	$(RM) $(SERVER_EXE) $(SEVER_OBJS)
	$(RM) $(CLIENT_EXE) $(CLIENT_OBJS)
.PHONY: clean

