
# ===== Colors =====
END:="\033[0;0m"
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
CYAN:="\033[1;36m"
PURPLE:="\033[1;35m"
WHITE:="\033[1;37m"
#===================

NAME = MySecretProject

CFLAGS =

SOURCE = main.cpp\
				OpenGLEngine.cpp\
				glad.cpp\
				Shader.cpp\
				VertexArray.cpp\
				VertexBuffer.cpp\
				ElementBuffer.cpp\
				stb.cpp\
				Texture.cpp\
				Camera.cpp\

SRCPATH = src/scripts
HDRPATH = src/headers
OBJPATH = obj
SDLPATH = SDL/SDL2/Headers

CC = clang++ -std=C++11 -Wall -Werror -g -O2 

FLAGS = -I $(HDRPATH)

LIBRARY_FLAGS = -lglfw -framework Cocoa -framework OpenGL -lm 


OBJ = $(addprefix $(OBJPATH)/,$(SOURCE:.cpp=.o))

INC = -I $(HDRPATH) -I $(SDLPATH)

all: load $(NAME)

load:
	@echo $(CYAN) "     LOADING"

$(NAME): $(OBJ)
	@echo $(END)
	@$(CC) $(FLAGS) $(LIBRARY_FLAGS) -o $(NAME) $^
	@echo $(GREEN)"   $(NAME) installed"$(END)

$(OBJPATH)/%.o: $(SRCPATH)/%.cpp $(SRCPATH)/%.cpp
	@echo ".\cpp"
	@mkdir $(OBJPATH) 2> /dev/null || true
	@clang $(FLAGS) $(SDL_FLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJPATH)

fclean: clean
	@rm -rf $(NAME)
	@echo '\033[0;31m'"$(NAME) uninstalled"'\033[0m'

re: fclean all

.PHONY: all lib clean fclean re