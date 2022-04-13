
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
				SDLEngine.cpp\
				OpenGLEngine.cpp\
				glad.cpp\
				ShaderClass.cpp\

SRCPATH = src/scripts
HDRPATH = src/headers
OBJPATH = obj
SDLPATH = SDL/SDL2/Headers

CC = g++ -std=c++11

FLAGS = -I $(HDRPATH)

SDL_FLAGS = -F ./SDL -O3 

SDL_FRAMEWORK = -framework SDL2 -lglfw -framework Cocoa -framework OpenGL -lm


OBJ = $(addprefix $(OBJPATH)/,$(SOURCE:.cpp=.o))

INC = -I $(HDRPATH) -I $(SDLPATH)

all: load $(NAME)

load:
	@echo $(CYAN) "     LOADING"

$(NAME): $(OBJ)
	@echo $(END)
	@$(CC) $(FLAGS) $(SDL_FLAGS) $(SDL_FRAMEWORK) -o $(NAME) $^
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

sdl2:
	cp -r libraries/SDL/SDL2.framework ~/Library/Frameworks/

.PHONY: all lib clean fclean re