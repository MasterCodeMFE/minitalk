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

# Variables
NAMECLIENT = client
NAMESERVER = server
NAMECLIENT_BONUS = client_bonus
NAMESERVER_BONUS = server_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCSCLIENT = src/client.c \
             src/ft_printf.c \
             src/ft_printf_aux.c

SRCSSERVER = src/server.c \
             src/ft_printf.c \
             src/ft_printf_aux.c

SRCSCLIENT_BONUS = src/client_bonus.c \
                   src/ft_printf_bonus.c \
                   src/ft_printf_aux_bonus.c

SRCSSERVER_BONUS = src/server_bonus.c \
                   src/ft_printf_bonus.c \
                   src/ft_printf_aux_bonus.c

OBJDIR := src/obj
OBJSCLIENT := $(SRCSCLIENT:src/%.c=$(OBJDIR)/%.o)
OBJSERVER := $(SRCSSERVER:src/%.c=$(OBJDIR)/%.o)
OBJSCLIENT_BONUS := $(SRCSCLIENT_BONUS:src/%.c=$(OBJDIR)/%.o)
OBJSERVER_BONUS := $(SRCSSERVER_BONUS:src/%.c=$(OBJDIR)/%.o)

RM = rm -rf
MARKER = .compiled

# Targets
all: $(NAMECLIENT) $(NAMESERVER) $(MARKER)

$(NAMECLIENT): $(OBJSCLIENT)
	@$(CC) $(CFLAGS) -o $(NAMECLIENT) $(OBJSCLIENT)

$(NAMESERVER): $(OBJSERVER)
	$(CC) $(CFLAGS) -o $(NAMESERVER) $(OBJSERVER)

$(MARKER): $(NAMECLIENT) $(NAMESERVER)
	@touch $(MARKER)

bonus: $(MARKER) $(NAMECLIENT_BONUS) $(NAMESERVER_BONUS)

$(NAMECLIENT_BONUS): $(OBJSCLIENT_BONUS)
	$(CC) $(CFLAGS) -o $(NAMECLIENT_BONUS) $(OBJSCLIENT_BONUS)

$(NAMESERVER_BONUS): $(OBJSERVER_BONUS)
	$(CC) $(CFLAGS) -o $(NAMESERVER_BONUS) $(OBJSERVER_BONUS)

$(OBJDIR)/%.o: src/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJDIR) $(MARKER)

fclean: clean
	$(RM) $(NAMECLIENT) $(NAMESERVER) $(NAMECLIENT_BONUS) $(NAMESERVER_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
