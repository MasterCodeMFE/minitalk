# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manufern <manufern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/12 11:32:43 by manufern          #+#    #+#              #
#    Updated: 2024/07/12 16:50:36 by manufern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAMECLIENT = client
NAMESERVER = server
GCC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCSCLIENT = src/client.c \
             src/ft_printf.c \
             src/ft_printf_aux.c

SRCSSERVER = src/server.c \
             src/ft_printf.c \
             src/ft_printf_aux.c

OBJDIR := src/obj
OBJSCLIENT := $(SRCSCLIENT:src/%.c=$(OBJDIR)/%.o)
OBJSERVER := $(SRCSSERVER:src/%.c=$(OBJDIR)/%.o)
RM = rm -rf

all: $(NAMECLIENT) $(NAMESERVER)

$(NAMECLIENT): $(OBJSCLIENT)
	@echo "Building $(NAMECLIENT)"
	@$(GCC) $(CFLAGS) -o $(NAMECLIENT) $(OBJSCLIENT)

$(NAMESERVER): $(OBJSERVER)
	@echo "Building $(NAMESERVER)"
	@$(GCC) $(CFLAGS) -o $(NAMESERVER) $(OBJSERVER)

$(OBJDIR)/%.o: src/%.c
	@echo "Compiling $< to $@"
	@mkdir -p $(OBJDIR)
	@$(GCC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	@$(RM) $(OBJDIR)

fclean: clean
	@echo "Performing full clean..."
	@$(RM) $(NAMECLIENT) $(NAMESERVER)

re: fclean all