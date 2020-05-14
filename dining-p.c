#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <signal.h>

static int sigTermRecieved = 0;//0 = false, 1 = true;
static int totalNumberOfEatThinkCycles = 0;
static int philosopherNumber = 0;
static int numberOfSeats = 0;

sem_t *chopstick[3];

void eat(int philosopherNumber) {
	printf("Philosopher %d is eating\n", philosopherNumber);
	usleep((rand() % 3000000) + 500000);//sleep for 0.5 - 3 sec
}

void think(int philosopherNumber) {
	printf("Philosopher %d is thinking\n", philosopherNumber);
	usleep((rand() % 3000000) + 500000);//sleep for 0.5 - 3 sec
}

void handler(int mySignal) {
	sigTermRecieved = 1;
	sem_destroy(chopstick[philosopherNumber]);
	sem_close(chopstick[philosopherNumber]);
}

sem_t mutex;

int main(int argc, char* argv[]) {
	printf("Pid: %d\n", getpid());

	numberOfSeats = atoi(argv[1]);

	philosopherNumber = atoi(argv[2]);

	sem_t chopstick[numberOfSeats];

	signal(SIGTERM, handler);

	do {
		sem_init(&chopstick[philosopherNumber], 0, 1);

		sem_wait(&chopstick[philosopherNumber]);

		eat(philosopherNumber);

		think(philosopherNumber);

		sem_post(&chopstick[philosopherNumber]);

		totalNumberOfEatThinkCycles++;

	} while(sigTermRecieved == 0);

	printf("philosopher %d completed %d cycles\n", philosopherNumber, totalNumberOfEatThinkCycles);
	return (0);
}
