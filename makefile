
CXX=g++
LIBS=-pthread
RM = rm -f
SERVER_EXE = server
CLIENT_EXE = client
SERVER_SRCS = server.cpp 
SERVER_OBJS = $(SERVER_SRCS:.cpp=.o)
CLIENT_SRCS  = client.cpp
CLIENT_OBJS = $(CLIENT_SRCS:.cpp=.o)

all : server client

server :server.o
	$(CXX) server.o -o server $(LIBS)

client:client.o
	$(CXX) client.o -o client

server.o:server.cpp
	$(CXX) -c server.cpp

client.o:client.cpp
	$(CXX) -c client.cpp

clean:
	$(RM) $(SERVER_EXE) $(SEVER_OBJS)
	$(RM) $(CLIENT_EXE) $(CLIENT_OBJS)
.PHONY: clean

