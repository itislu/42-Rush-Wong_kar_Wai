include				$(shell git rev-parse --show-toplevel)/build/setup.mk


# ***************************** CONFIGURATION ******************************** #

NAME			:=	2048
MSG_PROGRESS	:=	"🟨"
MSG_USAGE		?=	"Usage: ./$(NAME)"
COLOR_MAKE		=	$(STY_GRE)


#	Dependencies

LIBS_LOCAL		=	$(LIB_ROOT_DIR)/libft/libft.a
LIBS_EXTERN		:=	ncurses


#	Files

SRC_DIR			:=	source
# SRC				:=	$(addprefix $(SRC_DIR)/, \
# 					main.c \
# )
SRC				:=	$(shell find $(SRC_DIR) -type f -name "*.c")


include				$(MAKEFILES_DIR)/config.mk
include				$(MAKEFILES_DIR)/build.mk
include				$(MAKEFILES_DIR)/doc.mk
include				$(MAKEFILES_DIR)/help.mk
