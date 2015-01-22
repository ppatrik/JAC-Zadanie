#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zadanie2.h"

#define true 1
#define false 0

struct Navsteva {
	int day;
	int hour;
	int minute;
	int timeSpent;
	char name[100];
};

struct ZoznamNavstev {
	struct Navsteva *current;
	struct ZoznamNavstev *_next;
};

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL)
    	return -1;

    if (stream == NULL)
    	return -1;

    if (n == NULL)
    	return -1;

    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF)
    	return -1;

    if (bufptr == NULL) {
    	bufptr = malloc(128);
    	if (bufptr == NULL)
    		return -1;

    	size = 128;
    }

    p = bufptr;
    while(c != EOF) {
    	if ((int)(size - 1) < (int)(p - bufptr)) {
    		size = size + 128;
    		bufptr = realloc(bufptr, size);
    		if (bufptr == NULL)
    			return -1;

    	}
    	*p++ = c;
    	if (c == '\n') {
    		break;
    	}
    	c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

struct Navsteva *createVisit(int day, int hour, int minute, int timeSpent, char *name)
{
	struct Navsteva *item = NULL;
	item = malloc(sizeof(struct Navsteva));

	if(item == NULL) {
		perror("Not allocated memory!");
		return NULL;
	}

	item->day = day;
	item->hour = hour;
	item->minute = minute;
	item->timeSpent = timeSpent;
	strcpy( item->name, name );

	return item;
}

void addVisit(struct ZoznamNavstev *list, struct Navsteva *visit)
{
    struct ZoznamNavstev *newVisit;

    if(list->current == NULL) {
        list->current = visit;
        return;
    }

    newVisit = malloc(sizeof(struct ZoznamNavstev));
    newVisit->current = visit;
    while (list->_next != NULL) {
        list = list->_next;
    }
    list->_next = newVisit;
}

void listVisitsRow(struct Navsteva *visit)
{
    printf("|  %02d | %02d:%02d | %07d | %s\n",
        visit->day,
        visit->hour,
        visit->minute,
        visit->timeSpent,
        visit->name
    );
}

void printLine(int lastLine)
{
    printf("----------------------------------------------------\n");
    if(lastLine==1) {
        printf("\n\n");
    }
}

void listVisits(struct ZoznamNavstev *list)
{
    int total = 0;

    printLine(false);
    printf("| DEN | CAS   | TRVANIE | MENO                     |\n");
    printLine(false);
    do {
        if(list->current == NULL && list->_next==NULL)
            break;

        if(list->current != NULL) {
            listVisitsRow(list->current);
            total++;
        }

        list = list->_next;
    } while(list != NULL);
    printf("Total: %d\n", total);
    printLine(true);
}

void printVisit(struct Navsteva *visit)
{
    printLine(false);
    printf("Deň v mesiaci: %d\n", visit->day);
    printf("Čas: %02d:%02d\n", visit->hour, visit->minute);
    printf("Trvanie: %d\n", visit->timeSpent);
    printf("Meno: %s\n", visit->name);
    printLine(true);
}

struct ZoznamNavstev *loadFromFile(char *filename)
{
    FILE *fr;
    struct ZoznamNavstev *list;
    struct Navsteva *visit;
    char *line = NULL;
    size_t len;

    list = malloc(sizeof(struct ZoznamNavstev));
    list->current = NULL;
    list->_next = NULL;

    printLine(false);
    printf("Otvaram subor na citanie...\n");
    fr = fopen(filename, "r");

    printf("Zacinam citat zo suboru...\n");

    while ((int)(getline(&line, &len, fr)) != -1) {
        visit = malloc(sizeof(struct Navsteva));
        sscanf(line, "%d %d:%d %d %s\n", &visit->day, &visit->hour, &visit->minute, &visit->timeSpent, visit->name);
        addVisit(list, visit);
    }

    printf("Citanie ukoncene zatvaram subor...\n");

    fclose(fr);
    printf("Hotovo\n");
    printLine(true);

    return list;
}

void saveToFile(struct ZoznamNavstev *list, char *filename)
{
    FILE *fw;
    int total;

    printLine(false);
    printf("Otvaram subor na zapisovanie...\n");
    fw = fopen(filename, "w");

    printf("Zacinam zapisovat do suboru...\n");
    total = 0;
    do {
        if(list->current == NULL && list->_next==NULL)
            break;

        if(list->current != NULL) {
            fprintf(fw, "%d %d:%d %d %s\n",
                list->current->day,
                list->current->hour,
                list->current->minute,
                list->current->timeSpent,
                list->current->name
            );

            printf("Zapisujem %d...\n", ++total);
        }

        list = list->_next;

    } while(list != NULL);
    printf("Zápis ukončený zatvátam súbor...\n");

    fclose(fw);
    printf("Hotovo\n");
    printLine(true);
}

float getAverageSpentOfOneVisit(struct ZoznamNavstev *list)
{
    float sum = 0;
    int total = 0;

    do {
        if(list->current == NULL && list->_next==NULL)
            break;
        if(list->current != NULL) {
            sum += list->current->timeSpent;
            total++;
        }
        list = list->_next;
    } while(list != NULL);

    if(total==0)
        return 0;
    return sum / total;
}

struct Navsteva *getLongestVisit(struct ZoznamNavstev *list)
{
    struct Navsteva *longestVisit = NULL;
    do {
        if(list->current == NULL && list->_next==NULL)
            break;
        if(list->current != NULL) {
            if(longestVisit==NULL || list->current->timeSpent > longestVisit->timeSpent) {
                longestVisit = list->current;
            }
        }
        list = list->_next;
    } while(list != NULL);
    return longestVisit;
}

struct ZoznamNavstev *getListOfName(struct ZoznamNavstev *list, char *name)
{
    struct ZoznamNavstev *nameList;
    nameList = malloc(sizeof(struct ZoznamNavstev));

    do {
        if(list->current == NULL && list->_next==NULL)
            break;
        if(list->current != NULL) {
            if(strcmp( list->current->name, name ) == 0) {
                addVisit(nameList, list->current);
            }
        }
        list = list->_next;
    } while(list != NULL);

    return nameList;
}

int getTotalSpentTimeOfName(struct ZoznamNavstev *list, char *name)
{
    int total = 0;
    list = getListOfName(list, name);

    do {
        if(list->current == NULL && list->_next==NULL)
            break;
        if(list->current != NULL) {
            total += list->current->timeSpent;
        }
        list = list->_next;
    } while(list != NULL);

    return total;
}

int getBestDay(struct ZoznamNavstev *list)
{
    int countByDay[31];
    int bestDay = 0;
    int i;

    for(i=0; i < 31; i++) {
        countByDay[i] = 0;
    }

    do {
        if(list->current == NULL && list->_next==NULL)
            break;
        if(list->current != NULL) {
            countByDay[list->current->day - 1]++;
            if(countByDay[bestDay] < countByDay[list->current->day - 1]) {
                bestDay = list->current->day - 1;
            }
        }
        list = list->_next;
    } while(list != NULL);

    return bestDay + 1;
}

float getTotalIncome(struct ZoznamNavstev *list, float price)
{
    int total = 0;

    do {
        if(list->current == NULL && list->_next==NULL)
            break;
        if(list->current != NULL) {
            total += (int) list->current->timeSpent / 60.;
        }
        list = list->_next;
    } while(list != NULL);

    return total * price;
}

int main(void)
{
    struct ZoznamNavstev *list = NULL;
    struct Navsteva *visit1;
    struct Navsteva *visit2;
    struct Navsteva *visit3;
    if(false) {
        /* from file*/
        list = loadFromFile("output.txt");
    } else {
        list = malloc(sizeof(struct ZoznamNavstev));
        list->current = NULL;
        list->_next = NULL;
        visit1 = createVisit(1, 5, 0, 400, "Jozko Mrkvička");
        addVisit(list, visit1);
        visit2 = createVisit(2, 7, 10, 1000, "Jozko Mrkvička");
        addVisit(list, visit2);
        visit3 = createVisit(4, 9, 11, 45, "Jozko Blby");
        addVisit(list, visit3);
    }

	listVisits(list);

	/*printVisit(visit2);*/

	/*saveToFile(list, "output.txt");*/

	printLine(false);
	printf("Priemerná dĺžka návštevy je: %.2f \n", getAverageSpentOfOneVisit(list));
	printLine(true);

	printLine(false);
	printf("Najdlhšia návšteva je:\n");
	printVisit(getLongestVisit(list));

	printLine(false);
	printf("Navstevy klienta 'Jozko Blby' sú:\n");
	listVisits(getListOfName(list, "Jozko Blby"));

	printLine(false);
	printf("Celkovy čas klienta 'Jozko Mrkvička' je: %d\n", getTotalSpentTimeOfName(list, "Jozko Mrkvička"));
	printLine(true);

	printLine(false);
	printf("Celkovy zarobok pri cene 0.50 €: %.2f€\n", getTotalIncome(list, 0.5));
	printLine(true);

	printLine(false);
	printf("Najlepsim dnom bol %d. den v mesiaci\n", getBestDay(list));
	printLine(true);

	return 0;
}
