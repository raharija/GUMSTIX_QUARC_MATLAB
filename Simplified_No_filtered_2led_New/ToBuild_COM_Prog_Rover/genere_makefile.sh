echo "CC=$compilation_cmd
CFLAGS=$compilation_options
EXEC= COM_"$model_name"_RT
SRC= \$(wildcard *.c)
OBJ= \$(SRC:.c=.o)

all: \$(EXEC)

\$(EXEC): \$(OBJ)
	\$(CC) -o \$@ \$^ \$(CFLAGS)

%.o: %.c
	\$(CC) -o \$@ -c \$< \$(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf \$(EXEC)"> makefile
