include				$(shell git rev-parse --show-toplevel)/build/setup.mk


# ***************************** CONFIGURATION ******************************** #

NAME			:=	libft.a
MSG_PROGRESS	:=	"📦"
COLOR_MAKE		=	$(STY_WHI)


#	Files

include				build/sourcelist.mk
SRC_DIR			:=	source
SRC				:=	$(addprefix $(SRC_DIR)/,$(SRC))
# SRC				:=	$(shell find $(SRC_DIR) -type f -name "*.c")


include				$(MAKEFILES_DIR)/config.mk
include				$(MAKEFILES_DIR)/build.mk
include				$(MAKEFILES_DIR)/doc.mk
include				$(MAKEFILES_DIR)/help.mk
