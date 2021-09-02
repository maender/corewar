# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/26 14:38:11 by edjubert          #+#    #+#              #
#    Updated: 2019/08/11 17:25:16 by edjubert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=		libft.a

#==============================================================================#
#------------------------------------------------------------------------------#
#                               DIRECTORIES                                    #

SRC_DIR			:=		./srcs
INC_DIR			:=		./includes
OBJ_DIR			:=		./obj

#==============================================================================#
#------------------------------------------------------------------------------#
#                                  FILES                                       #

SRC				:=		ft_atoi.c				\
						ft_abs.c				\
						ft_atol.c				\
						ft_bindec.c				\
						ft_bzero.c				\
						ft_dabs.c				\
						ft_dtob.c				\
						ft_dneg.c				\
						ft_get_next_line.c		\
						ft_intlen.c				\
						ft_intlen_unsigned.c	\
						ft_isalnum.c			\
						ft_isalpha.c			\
						ft_isascii.c			\
						ft_isdigit.c			\
						ft_isprint.c			\
						ft_isword.c				\
						ft_itoa.c				\
						ft_itoa_base.c			\
						ft_itoa_long.c			\
						ft_lstadd.c				\
						ft_lstdel.c				\
						ft_lstdelone.c			\
						ft_lstiter.c			\
						ft_lstmap.c				\
						ft_lstnew.c				\
						ft_lstqueue.c			\
						ft_lstsize.c			\
						ft_match.c				\
						ft_matcha.c				\
						ft_memalloc.c			\
						ft_memccpy.c			\
						ft_memchr.c				\
						ft_memcmp.c				\
						ft_memcpy.c				\
						ft_memdel.c				\
						ft_memmove.c			\
						ft_memset.c				\
						ft_nmatch.c				\
						ft_pow.c				\
						ft_putchar_fd.c			\
						ft_putchar.c			\
						ft_putendl_fd.c			\
						ft_putendl.c			\
						ft_putnbr_fd.c			\
						ft_putnbr.c				\
						ft_putstr_fd.c			\
						ft_putstr.c				\
						ft_strcat.c				\
						ft_strchr.c				\
						ft_strclr.c				\
						ft_strcmp.c				\
						ft_strcpy.c				\
						ft_strdel.c 			\
						ft_strdup.c				\
						ft_strldup.c			\
						ft_strequ.c				\
						ft_striter.c			\
						ft_striteri.c			\
						ft_strjoin_free.c		\
						ft_strjoin.c			\
						ft_strlcat.c			\
						ft_strlen_free.c		\
						ft_strlen_pro.c			\
						ft_strlen.c				\
						ft_strmap.c				\
						ft_strmapi.c			\
						ft_strncat.c			\
						ft_strncmp.c			\
						ft_strncpy.c			\
						ft_strnequ.c			\
						ft_strnew.c				\
						ft_strnstr.c			\
						ft_strrchr.c			\
						ft_strrev.c				\
						ft_strsplit.c			\
						ft_strstr.c				\
						ft_strsub_free.c		\
						ft_strsub.c				\
						ft_strtrim.c			\
						ft_tolower.c			\
						ft_toupper.c			\
						ft_utoa_long.c			\
						ft_utoa_base.c			\
						ft_wlen.c				\
						ft_sqrt.c				\
						ft_lstsize.c			\
						ft_tabdel.c				\
						ft_swap.c				\
						ft_color.c				\
						ft_match.c				\
						ft_nmatch.c				\
						ft_matcha.c				\
						ft_check.c				\
						ft_init.c				\
						ft_choose.c				\
						ft_field_tools.c		\
						ft_list_tools.c			\
						ft_parse.c				\
						ft_printf.c				\
						ft_swap.c				\
						handle_binary.c			\
						handle_digit.c			\
						handle_base.c			\
						handle_float_long.c		\
						handle_float.c			\
						handle_long.c			\
						handle_string.c			\
						handle_padding.c		\
						handle_unsigned.c		\
						handle_unsigned_long.c	\
						handle_char.c			\
						handle_title.c			\
						handle_title_a_o.c		\
						handle_title_o_z.c		\
						handle_unicode.c		\
						ft_count_needles.c		\
						ft_strirep.c			\
						ft_atoul.c

OBJ				:=		$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
NB				:=		$(words $(SRC))
INDEX			:=		0

#==============================================================================#
#------------------------------------------------------------------------------#
#                            COMPILER & FLAGS                                  #

CC				:=			gcc
CFLAGS			:=			-Wall -Wextra -Werror

#==============================================================================#
#------------------------------------------------------------------------------#
#                                 RULES                                        #

all:					$(NAME)

$(NAME):				$(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf '\033[32m[ 100%% ] %-15s\033[92m%-30s\033[32m%s\n\033[0m' "Compilation of " $(NAME) " is done ---"



$(OBJ_DIR)/%.o:			$(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval TO_DO=$(shell echo "$@"))
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@printf "                                                     \r"
	@printf "\033[33m[ %3d%% ] %s\t%s\r\033[0m" $(PERCENT) $(NAME) $@
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))


clean:
	@rm -rf $(OBJ_DIR)
	@printf '\033[91m[ KILL ] %-15s\033[31m%-30s\033[91m%s\n\033[0m' "CLEAN  of " $(NAME) " is done ---"


fclean: 				clean
	@rm -rf $(NAME)
	@printf '\033[91m[ KILL ] %-15s\033[31m%-30s\033[91m%s\n\033[0m' "FCLEAN of " $(NAME) " is done ---"


re:						fclean all


.PHONY: all clean fclean re build cbuild
