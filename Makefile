####--------------------------------####
#--# Author:   by uriid1            #--#
#--# License:  GNU GPLv3            #--#
#--# Telegram: @main_moderator      #--#
#--# E-mail:   appdurov@gmail.com   #--#
####--------------------------------####

# Del old
install:
	gcc game.c -o AppleWar -Wno-unused -lncurses
	echo ===============
	./AppleWar

clean:
	rm AppleWar

.PHONY: install clear
