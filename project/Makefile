# COLORS
GREEN	= \033[0;32m
RED 	= \033[0;31m
ORANGE	= \033[0;33m
CYAN	= \033[0;36m
RESET	= \033[0m
UP 		= \033[A
CUT 	= \033[K

# PROGRAM
NAME		= webserv

# FOLDERS & FILES
SRCS_DIR	= ./src/
SRCS_FILES	= main.cpp
SRCS_FILES	+= HttpException.cpp HttpParser.cpp
SRCS		:= ${patsubst %, ${SRCS_DIR}%, ${SRCS_FILES}}

O_DIR		= ./objs/
D_DIR		= ./debugs/

OBJS_FILES	:= ${SRCS_FILES:.cpp=.o}

OBJS		:= ${patsubst %, ${O_DIR}%, ${OBJS_FILES}}
DEBUGS		:= ${patsubst %, ${D_DIR}%, ${OBJS_FILES}}

# FLAGS
CC			= g++
CFLAGS		= -Wall -Wextra -Werror
# Add this for debug
#CFLAGS		+= -g3

CPP_FLAGS 	= -std=c++98 -pedantic

# COMMANDS
MKDIR		= mkdir -p
RM			= rm -f

all: ${NAME}

# Compile normal executable
${NAME}: ${O_DIR} ${OBJS}
	@${CC} ${CFLAGS} ${CPP_FLAGS} -o ${NAME} ${OBJS}
	@echo "[$(ORANGE)$(NAME)$(RESET)] Creation *.o files & compilation : $(GREEN)OK$(RESET)"
	@echo "[\033[1;32msuccess$(RESET)]: $(NAME) is ready"

# Create objects directory
${O_DIR}:
	@${MKDIR} ${O_DIR}

# Compile normals objects
${O_DIR}%.o: ${SRCS_DIR}%.cpp
	@echo "[$(CYAN)Compiling$(RESET)]: $<$(UP)$(CUT)"
	@${CC} ${CFLAGS} ${HEADS} -o $@ -c $<

#Compile a debug executable with -g and fsanitize
debug: ${D_DIR} ${DEBUGS}
	@${CC} ${CFLAGS} ${CPP_FLAGS} -fsanitize=address -o ${NAME} ${DEBUGS}
	@echo "[$(ORANGE)$(NAME)$(RESET)] Creation *.o files for debug : $(GREEN)OK$(RESET)"
	@echo "[\033[1;32msuccess$(RESET)]: Debug - $(NAME) is ready"

#Create debug directory
${D_DIR}:
	@${MKDIR} ${D_DIR}

#Compile debug objects
${D_DIR}%.o: ${SRCS_DIR}%.cpp
	@echo "[$(CYAN)Debug$(RESET)]: $<$(UP)$(CUT)"
	@${CC} ${CFLAGS} -g ${HEADS} -o $@ -c $<

clean:
	@${RM} ${OBJS} ${OBJSB} ${DEBUGS}
	@${RM} -r ${O_DIR}
	@${RM} -r ${D_DIR}
	@echo "[$(ORANGE)$(NAME)$(RESET)] clean *.o files : $(GREEN)OK$(RESET)"

fclean:	clean
	@${RM} ${NAME}
	@echo "[$(ORANGE)$(NAME)$(RESET)] fclean: $(GREEN)OK$(RESET)"
	@echo "[\033[1;32msuccess$(RESET)]: $(NAME) has been clean up"

valgrind: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

re: fclean all

.PHONY: all clean fclean re valgrind