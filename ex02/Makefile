NAME = PmergeMe

SRCS = main.cpp srcs/PmergeMe.cpp
OBJS = $(SRCS:.cpp=.o)

CPP = g++ -Wall -Werror -Wextra -std=c++98 -Iincl

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CPP) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re