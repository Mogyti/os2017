#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 10


typedef struct {
	char type; // 0=fried chicken, 1=French fries
	int amount; // pieces or weight
	char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

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

int main(){
	//produce 2 new items
	item a;
	a.type = '1';
	a.amount = 3;
	a.unit = '0';

	item b;
	b.type = '0';
	b.amount = 8;
	b.unit = '1';

	printf("First Item:\n Type: %c, Amount: %d, Unit: %c\n", a.type, a.amount, a.unit);
	produce(&a);
	printf("\tFirst: %d, last: %d\n", first, last);
	printf("Second Item:\n Type: %c, Amount: %d, Unit: %c\n", b.type, b.amount, b.unit);
	produce(&b);
	printf("\tFirst: %d, last: %d\n\n", first, last);

	//consume
	item* consumed = consume();
	printf("Item consumed:\n Type: %c, Amount: %d, Unit: %c\n", consumed->type, consumed->amount, consumed->unit);

	return 0;
}