gcc -c ./src/game/CharLogicHandler.c -lm -Wall -Werror -o ./src/game/CharLogicHandler.o

gcc -c ./src/game/FileHandler.c -lm -Wall -Werror -o ./src/game/FileHandler.o

gcc -c ./src/game/GameLogic.c -lm -Wall -Werror -o ./src/game/GameLogic.o

gcc -c ./src/game/IntLogicHandler.c -lm -Wall -Werror -o ./src/game/IntLogicHandler.o

gcc -c ./src/game/Random.c -lm -Wall -Werror -o ./src/game/Random.o

gcc -c ./src/terminal/GameSession.c -lm -Wall -Werror -o ./src/terminal/GameSession.o

gcc -c ./src/terminal/PrintHandler.c -lm -Wall -Werror -o ./src/terminal/PrintHandler.o

gcc -c ./src/terminal/PromptHandler.c -lm -Wall -Werror -o ./src/terminal/PromptHandler.o

gcc -c ./src/terminal/StyleHandler.c -lm -Wall -Werror -o ./src/terminal/StyleHandler.o

gcc -c ./src/terminal/WindowSize.c -lm -Wall -Werror -o ./src/terminal/WindowSize.o

gcc -c ./src/util/Utils.c -lm -Wall -Werror -o ./src/util/Utils.o

gcc -c ./main.c -lm -Wall -Werror -o ./main.o

gcc ./src/game/CharLogicHandler.o ./src/game/FileHandler.o ./src/game/GameLogic.o ./src/game/IntLogicHandler.o ./src/game/Random.o ./src/terminal/GameSession.o ./src/terminal/PrintHandler.o ./src/terminal/PromptHandler.o ./src/terminal/StyleHandler.o ./src/terminal/WindowSize.o ./src/util/Utils.o ./main.o -lm -Wall -Werror -o TheGameOfLife
