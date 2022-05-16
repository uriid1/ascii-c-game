####--------------------------------####
#--# Author:   by uriid1            #--#
#--# License:  GNU GPLv3            #--#
#--# Telegram: @main_moderator      #--#
#--# E-mail:   appdurov@gmail.com   #--#
####--------------------------------####

# Del old
if [ -f AppleWar ]; then
	rm AppleWar
fi

# Build new
gcc game.c -o AppleWar -Wno-unused -lncurses

# Run
./AppleWar
