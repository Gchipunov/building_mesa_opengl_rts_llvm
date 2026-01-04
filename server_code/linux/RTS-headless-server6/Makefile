CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread

SERVER_SRC = rts_udp_game_server6.cpp
SERVER_OBJ = $(SERVER_SRC:.cpp=.o)
SERVER_EXEC = rts_server6

all: $(SERVER_EXEC)

$(SERVER_EXEC): $(SERVER_OBJ)
        $(CXX) $(CXXFLAGS) -o $@ $(SERVER_OBJ)

clean:
        rm -f $(SERVER_EXEC) $(SERVER_OBJ)
