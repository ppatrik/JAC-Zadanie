#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zadanie2.h"

#define MAX 100

struct Navsteva {
	int day;
	int hour;
	int minute;
	int timeSpent;
	char name[MAX];
};

struct ZoznamNavstev {
	struct Navsteva *current;
	struct ZoznamNavstev *_next;
};

int main(void) {
	return 0;
}
