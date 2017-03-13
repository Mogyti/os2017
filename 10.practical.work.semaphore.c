#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

typedef struct {
	char type; // 0=fried chicken, 1=French fries
	int amount; // pieces or weight
	char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;
sem_t sem; //declare the semaphore

void produce(item *i) {
	while ((first + 1) % BUFFER_SIZE == last) {
	// do nothing -- no free buffer item
	}
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
}

item *consume() {
	item *i = (item*)malloc(sizeof(item));
	while (first == last) {
	// do nothing -- nothing to consume
	}
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	return i;
}

void *firstlast(){
	printf("\tFirst: %d, last: %d\n", first, last);
}



void *produce_items(){
	item plate1;
	plate1.type = '1';
	plate1.amount = 311;
	plate1.unit = '0';

	item plate2;
	plate2.type = '0';
	plate2.amount = 82;
	plate2.unit = '1';

	item plate3;
	plate3.type = '1';
	plate3.amount = 96;
	plate3.unit = '1';

	printf("First item:\n Type: %c, Amount: %d, Unit: %c\n", plate1.type, plate1.amount, plate1.unit);
	produce(&plate1);
	firstlast();
	printf("Second item:\n Type: %c, Amount: %d, Unit: %c\n", plate2.type, plate2.amount, plate2.unit);
	produce(&plate2);
	firstlast();
	printf("Third Item:\n Type: %c, Amount: %d, Unit: %c\n", plate3.type, plate3.amount, plate3.unit);
	produce(&plate3);
	firstlast();
	printf("\n\n");
}

void *consume_items(){
	item *consumed;
	consumed = consume();
	sleep(2);
	printf("Consuming....\n");
	sleep(5);
	printf("Consumed 1st item:\n Type: %c, Amount: %d, Unit: %c\n", consumed->type, consumed->amount, consumed->unit);
	firstlast();
	sleep(1);
	consumed = consume();
	printf("Consumed 2nd item:\n Type: %c, Amount: %d, Unit: %c\n", consumed->type, consumed->amount, consumed->unit);
	firstlast();
}

int main(){
	pthread_t produce_id, consume_id;
	sem_init(&sem, 0, BUFFER_SIZE); //Semaphore initialization, 0 indicate the semaphore is shared between threads
	printf("\n\nBefore consuming:...\n Procesing....\n  ");
	firstlast();
	pthread_create(&produce_id, NULL, produce_items, NULL);
	pthread_create(&consume_id, NULL, consume_items, NULL);
	pthread_join(consume_id, NULL);
	sem_destroy(&sem);    //Destroy semaphore
	return 0;
}