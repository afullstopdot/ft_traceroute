# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarquez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/20 10:10:12 by amarquez          #+#    #+#              #
#    Updated: 2017/07/14 10:10:49 by amarquez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler

CC	= gcc
LINKER = gcc

# Flags

FLAGS = -Wall -Wextra -Werror

# Project Directory

CWD = .

# Genereic File Structure

INCDIR = $(CWD)/inc
SRCDIR = $(CWD)/src
OBJDIR = $(CWD)/obj

# Include Files

INC := $(wildcard $(INCDIR)/*.h)

# Interpreter src & obj

INTERPRETER_DIR = interpreter
INTERPRETER_SRC := $(wildcard $(SRCDIR)/$(INTERPRETER_DIR)/*.c)
INTERPRETER_OBJ := $(INTERPRETER_SRC:$(SRCDIR)/$(INTERPRETER_DIR)/%.c=$(OBJDIR)/$(INTERPRETER_DIR)/%.o)

# Error src & obj

ERROR_DIR = error
ERROR_SRC := $(wildcard $(SRCDIR)/$(ERROR_DIR)/*.c)
ERROR_OBJ := $(ERROR_SRC:$(SRCDIR)/$(ERROR_DIR)/%.c=$(OBJDIR)/$(ERROR_DIR)/%.o)

# Privileges src & obj

PRIV_DIR = privileges
PRIV_SRC := $(wildcard $(SRCDIR)/$(PRIV_DIR)/*.c)
PRIV_OBJ := $(PRIV_SRC:$(SRCDIR)/$(PRIV_DIR)/%.c=$(OBJDIR)/$(PRIV_DIR)/%.o)

# Privileges src & obj

SOCK_DIR = sockets
SOCK_SRC := $(wildcard $(SRCDIR)/$(SOCK_DIR)/*.c)
SOCK_OBJ := $(SOCK_SRC:$(SRCDIR)/$(SOCK_DIR)/%.c=$(OBJDIR)/$(SOCK_DIR)/%.o)

# ICMP src & obj

ICMP_DIR = icmp
ICMP_SRC := $(wildcard $(SRCDIR)/$(ICMP_DIR)/*.c)
ICMP_OBJ := $(ICMP_SRC:$(SRCDIR)/$(ICMP_DIR)/%.c=$(OBJDIR)/$(ICMP_DIR)/%.o)

# Signal src & obj

SIGN_DIR = signals
SIGN_SRC := $(wildcard $(SRCDIR)/$(SIGN_DIR)/*.c)
SIGN_OBJ := $(SIGN_SRC:$(SRCDIR)/$(SIGN_DIR)/%.c=$(OBJDIR)/$(SIGN_DIR)/%.o)

# Wrappers src & obj

WRAP_DIR = wrappers
WRAP_SRC := $(wildcard $(SRCDIR)/$(WRAP_DIR)/*.c)
WRAP_OBJ := $(WRAP_SRC:$(SRCDIR)/$(WRAP_DIR)/%.c=$(OBJDIR)/$(WRAP_DIR)/%.o)

# Main src & obj

MAIN_DIR = main
MAIN_SRC := $(wildcard $(SRCDIR)/$(MAIN_DIR)/*.c)
MAIN_OBJ := $(MAIN_SRC:$(SRCDIR)/$(MAIN_DIR)/%.c=$(OBJDIR)/$(MAIN_DIR)/%.o)

# Executabe name

EXE = ft_traceroute

# OS for linking libraries (linux and os x different)

OS := $(shell uname)

LIBFT = -L ./libft -lft
LIBFT_H = -I libft

ifneq ($(OS),Darwin)

  LINK = $(LIBFT)

endif

# Bin directory

BINDIR = .

##### NB: Check if directories exists before you try to use them

# rules begin:

all: $(OBJDIR) $(BINDIR)/$(EXE)

$(OBJDIR):
	@echo "\033[0;31m[PING]: \033[0m\033[0;36mCreating "$@" directory!\033[0m"
	@mkdir -p $@/$(INTERPRETER_DIR) $@/$(ERROR_DIR) $@/$(ICMP_DIR) $@/$(MAIN_DIR) $@/$(PRIV_DIR) $@/$(SOCK_DIR) $@/$(SIGN_DIR) $@/$(WRAP_DIR)
	@echo "\033[0;31m[PING]: \033[0m\033[0;32mComplete!\033[0m"


$(BINDIR)/$(EXE): $(INTERPRETER_OBJ) $(ERROR_OBJ) $(PRIV_OBJ) $(ICMP_OBJ) $(SOCK_OBJ) $(SIGN_OBJ) $(WRAP_OBJ) $(MAIN_OBJ)
	@echo "\033[0;31m[PING]: \033[0mLinking object files!"
	@$(LINKER) $(INTERPRETER_OBJ) $(ERROR_OBJ) $(PRIV_OBJ) $(ICMP_OBJ) $(SOCK_OBJ) $(SIGN_OBJ) $(WRAP_OBJ) $(MAIN_OBJ) $(FLAGS) -o $@ $(LIBFT) -I $(INCDIR) $(LIBFT_H)
	@echo "\033[0;31m[PING]: \033[0mLinking complete!"


$(INTERPRETER_OBJ): $(OBJDIR)/$(INTERPRETER_DIR)/%.o : $(SRCDIR)/$(INTERPRETER_DIR)/%.c
	@echo "\033[0;32m[interpreter]: \033[0mCompiling source file \033[0;36m"$<"\033[0m!"
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCDIR) $(LINK) $(LIBFT_H)
	@echo "\033[0;32m[interpreter]: \033[0mCompiled \033[0;32m"$<"\033[0m successfully!"
	

$(ERROR_OBJ): $(OBJDIR)/$(ERROR_DIR)/%.o : $(SRCDIR)/$(ERROR_DIR)/%.c
	@echo "\033[0;33m[error]: \033[0mCompiling source file \033[0;36m"$<"\033[0m!"
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCDIR) $(LINK) $(LIBFT_H)
	@echo "\033[0;33m[error]: \033[0mCompiled \033[0;36m"$<"\033[0m successfully!"


$(MAIN_OBJ): $(OBJDIR)/$(MAIN_DIR)/%.o : $(SRCDIR)/$(MAIN_DIR)/%.c
	@echo "\033[0;34m[main]: \033[0mCompiling source file \033[0;36m"$<"\033[0m!"
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCDIR) $(LINK) $(LIBFT_H)
	@echo "\033[0;34m[main]: \033[0mCompiled \033[0;36m"$<"\033[0m successfully!"


$(PRIV_OBJ): $(OBJDIR)/$(PRIV_DIR)/%.o : $(SRCDIR)/$(PRIV_DIR)/%.c
	@echo "\033[0;34m[priv]: \033[0mCompiling source file \033[0;36m"$<"\033[0m!"
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCDIR) $(LINK) $(LIBFT_H)
	@echo "\033[0;34m[priv]: \033[0mCompiled \033[0;36m"$<"\033[0m successfully!"


$(SOCK_OBJ): $(OBJDIR)/$(SOCK_DIR)/%.o : $(SRCDIR)/$(SOCK_DIR)/%.c
	@echo "\033[0;34m[sock]: \033[0mCompiling source file \033[0;36m"$<"\033[0m!"
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCDIR) $(LINK) $(LIBFT_H)
	@echo "\033[0;34m[sock]: \033[0mCompiled \033[0;36m"$<"\033[0m successfully!"


$(ICMP_OBJ): $(OBJDIR)/$(ICMP_DIR)/%.o : $(SRCDIR)/$(ICMP_DIR)/%.c
	@echo "\033[0;34m[icmp]: \033[0mCompiling source file \033[0;36m"$<"\033[0m!"
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCDIR) $(LINK) $(LIBFT_H)
	@echo "\033[0;34m[icmp]: \033[0mCompiled \033[0;36m"$<"\033[0m successfully!"


$(SIGN_OBJ): $(OBJDIR)/$(SIGN_DIR)/%.o : $(SRCDIR)/$(SIGN_DIR)/%.c
	@echo "\033[0;34m[signals]: \033[0mCompiling source file \033[0;36m"$<"\033[0m!"
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCDIR) $(LINK) $(LIBFT_H)
	@echo "\033[0;34m[signals]: \033[0mCompiled \033[0;36m"$<"\033[0m successfully!"


$(WRAP_OBJ): $(OBJDIR)/$(WRAP_DIR)/%.o : $(SRCDIR)/$(WRAP_DIR)/%.c
	@echo "\033[0;34m[signals]: \033[0mCompiling source file \033[0;36m"$<"\033[0m!"
	@$(CC) $(FLAGS) -c $< -o $@ -I $(INCDIR) $(LINK) $(LIBFT_H)
	@echo "\033[0;34m[signals]: \033[0mCompiled \033[0;36m"$<"\033[0m successfully!"


.PHONY: clean
clean:
	@echo "\033[0;36mRemoving object files\033[0m"
	@rm -f $(INTERPRETER_OBJ) $(ERROR_OBJ) $(PRIV_OBJ) $(ICMP_OBJ) $(SOCK_OBJ) $(SIGN_OBJ) $(MAIN_OBJ) $(WRAP_OBJ)
	@echo "\033[0;32mCleanup complete\033[0m"


.PHONY: fclean
fclean: clean
	@echo "\033[0;36mRemoving executable '$(BINDIR)/$(EXE)"
	@rm -f $(BINDIR)/$(EXE)
	@echo "\033[0;32mExecutable removed\033[0m"


.PHONY: re
re: fclean all