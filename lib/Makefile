#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmoumini <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/12 13:41:19 by mmoumini          #+#    #+#              #
#    Updated: 2015/05/23 02:25:14 by mmoumini         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY = all, clean, fclean, re

JPEGNAME = libjpeg.a

LIBOGG = libogg.a

NAME = $(JPEGNAME) $(LIBOGG)

CFLAGS = -Wall -Wextra -Werror

C_LIB = (cd jpeg-9a; make; cd ../libogg-1.3.2; make)

CLEAN_LIB = (cd jpeg-9a; make clean; cd ../libogg-1.3.2; make clean)

MVLIB = (mv jpeg-9a/.libs/$(JPEGNAME) ./; mv libogg-1.3.2/src/.libs/$(LIBOGG) ./)

all: $(NAME)

$(NAME): 
		$(C_LIB)
		$(MVLIB)

clean:
		rm -rf $(OBJ)
		$(CLEAN_LIB)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean re fclean