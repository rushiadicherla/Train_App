all: train_app

train_app: user.o train.o booking.o main.o
        gcc user.o train.o booking.o  main.o -o train_app

main.o: main.c
        gcc -c main.c

user.o: user.c
        gcc -c user.c

train.o: train.c
        gcc -c train.c

booking.o: booking.c
        gcc -c booking.c
