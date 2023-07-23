# To compile, type: 'make'
# To delete executables, type: 'make clean'


CPP = gcc
FLAGS = -Wall -Werror

EXEC = my-cat my-sed my-uniq

default:
	gcc -o my-cat my-cat.c
	gcc -o my-sed my-sed.c 
	gcc -o my-uniq my-uniq.c


clean:
	rm -f ${EXEC}
	rm -f *.o

${EXEC}:${OBJS}
	${CPP} ${FLAGS} -o ${EXEC} ${OBJS}

.c.o:
	${CPP} ${FLAGS} -c $<

