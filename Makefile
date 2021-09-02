# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edjubert <edjubert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/04 18:02:25 by edjubert          #+#    #+#              #
#    Updated: 2019/08/11 16:50:14 by edjubert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COREWAR			:=		corewar
ASM				:=		asm

#==============================================================================#
#------------------------------------------------------------------------------#
#                                  DIRECTORIES                                 #

SRC_DIR_COREWAR	:=		./srcs/vm
SRC_DIR_ASM		:=		./srcs/asm
INC_DIR			:=		./includes
OBJ_DIR_COREWAR	:=		./obj
OBJ_DIR_ASM		:=		./obj
LIBFT_FOLDER	:=		./libft
LIBFT			:=		$(LIBFT_FOLDER)/libft.a
INC_LIB			:=		./libft/includes
INC_FILES		:=		./libft/includes/libft.h	\
						./includes/asm.h			\
						./includes/corewar.h		\
						./includes/op.h

#==============================================================================#
#------------------------------------------------------------------------------#
#                                   COREWAR                                    #

SRC_COREWAR		:=		oc.c						\
						op_aff_live_zjmp.c			\
						op_exec.c					\
						op_ocp.c					\
						op_fork_lfork.c				\
						op_ld_lld_sti.c				\
						op_ldi_lldi_st.c			\
						op_operations.c				\
						op_types.c					\
						vm_args.c					\
						vm_champs.c					\
						vm_colors.c					\
						vm_fight.c					\
						vm_init.c					\
						vm_main.c					\
						vm_ncurses.c				\
						vm_procs.c					\
						vm_run.c					\
						vm_utils.c					\
						vm_check.c					\
						vm_breakdown.c

OBJ_COREWAR		:=		$(addprefix $(OBJ_DIR_COREWAR)/,$(SRC_COREWAR:.c=.o))
NB_COREWAR		:=		$(words $(SRC_COREWAR))
INDEX_COREWAR	:=		0

#==============================================================================#
#------------------------------------------------------------------------------#
#                                     ASM                                      #

SRC_ASM			:=		asm.c						\
						asm_errors.c				\
						asm_errors_handle.c			\
						asm_free.c					\
						asm_input.c					\
						asm_labels.c				\
						asm_lex_wrap.c				\
						asm_lexer.c					\
						asm_options.c				\
						asm_output.c				\
						asm_output_tools.c			\
						asm_parsechecks.c			\
						asm_parser.c				\
						asm_parsetype.c				\
						asm_print.c					\
						asm_print_lst_tools.c		\
						asm_print_lst_tools_bis.c	\
						asm_skipper.c				\
						asm_token.c					\
						asm_tools.c					\
						asm_utils.c					\
						op.c

OBJ_ASM			:=		$(addprefix $(OBJ_DIR_ASM)/,$(SRC_ASM:.c=.o))
NB_ASM			:=		$(words $(SRC_ASM))
INDEX_ASM		:=		0

#==============================================================================#
#------------------------------------------------------------------------------#
#                               COMPILER & FLAGS                               #

GCC				:=		gcc
FLAGS			:=		-Wall						\
						-Wextra						\
						-Werror

#==============================================================================#
#------------------------------------------------------------------------------#
#                                     RULES                                    #

.PHONY:					all
all:					$(COREWAR) $(ASM)

.PHONY:					makelib
makelib :
	@ make -C $(LIBFT_FOLDER)

$(COREWAR):				makelib $(INC_FILES) $(OBJ_COREWAR)
	@ $(GCC) $(FLAGS) $(OBJ_COREWAR) -L$(LIBFT_FOLDER) -lft -lncurses -o $(COREWAR)
	@ printf '\033[32m[ 100%% ] %-15s\033[92m%-30s\033[32m%s\n\033[0m' \
		"Compilation of " $(COREWAR) " is done ---"

$(ASM):					makelib $(INC_FILES) $(OBJ_ASM)
	@ $(GCC) $(FLAGS) $(OBJ_ASM) -L$(LIBFT_FOLDER) -lft -o $(ASM)
	@ printf '\033[32m[ 100%% ] %-15s\033[92m%-30s\033[32m%s\n\033[0m' \
		"Compilation of " $(ASM) " is done ---"

$(OBJ_DIR_COREWAR)/%.o:	$(SRC_DIR_COREWAR)/%.c $(INC_FILES)
	@ mkdir -p $(OBJ_DIR_COREWAR)
	@ $(eval DONE = $(shell echo $$(($(INDEX_COREWAR) * 20 / $(NB_COREWAR)))))
	@ $(eval PERCENT = $(shell \
		echo $$(($(INDEX_COREWAR) * 100 / $(NB_COREWAR)))))
	@ $(eval TO_DO = $(shell echo "$@"))
	@ $(GCC) $(FLAGS) -I$(INC_LIB) -I$(INC_DIR) -c $< -o $@
	@ printf "                                                          \r"
	@ printf "\033[33m[ %3d%% ] %s\t%s\r\033[0m" $(PERCENT) $(COREWAR) $@
	@ $(eval INDEX = $(shell echo $$(($(INDEX_COREWAR) + 1))))

$(OBJ_DIR_ASM)/%.o:			$(SRC_DIR_ASM)/%.c $(INC_FILES)
	@ mkdir -p $(OBJ_DIR_ASM)
	@ $(eval DONE = $(shell echo $$(($(INDEX_ASM) * 20 / $(NB_ASM)))))
	@ $(eval PERCENT = $(shell echo $$(($(INDEX_ASM) * 100 / $(NB_ASM)))))
	@ $(eval TO_DO = $(shell echo "$@"))
	@ $(GCC) $(FLAGS) -I$(INC_LIB) -I$(INC_DIR) -c $< -o $@
	@ printf "                                                          \r"
	@ printf "\033[33m[ %3d%% ] %s\t%s\r\033[0m" $(PERCENT) $(ASM) $@
	@ $(eval INDEX = $(shell echo $$(($(INDEX_ASM) + 1))))

.PHONY:					clean
clean:
	@ /bin/rm -rf $(OBJ_DIR_COREWAR) $(OBJ_DIR_ASM)
	@ make -C $(LIBFT_FOLDER) clean --no-print-directory
	@ printf '\033[91m[ KILL ] %-15s\033[31m%-30s\033[91m%s\n\033[0m' \
		"CLEAN  of " $(COREWAR) " is done ---"
	@ printf '\033[91m[ KILL ] %-15s\033[31m%-30s\033[91m%s\n\033[0m' \
		"CLEAN  of " $(ASM) " is done ---"

.PHONY:					fclean
fclean:					clean
	@ /bin/rm -rf $(COREWAR) $(ASM)
	@ make -C $(LIBFT_FOLDER) fclean --no-print-directory
	@ printf '\033[91m[ KILL ] %-15s\033[31m%-30s\033[91m%s\n\033[0m' \
		"FCLEAN of " $(COREWAR) " is done ---"
	@ printf '\033[91m[ KILL ] %-15s\033[31m%-30s\033[91m%s\n\033[0m' \
		"FCLEAN of " $(ASM) " is done ---"

.PHONY:					re
re:						fclean all
