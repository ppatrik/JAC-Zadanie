#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "zadanie2.h"

#define true 1
#define false 0
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

	/* kontrola vstupu */
	if(day < 1 && day > 31)
        return NULL;
	if(hour < 0 && hour >= 24)
        return NULL;
	if(minute < 0 && minute >= 60)
        return NULL;
	if(timeSpent < 0 && timeSpent >= 86400)
        return NULL;
    if(name == NULL)
        return NULL;

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

    if(visit == NULL)
        return;
    if(list == NULL) {
        printf("List is not initialized!\n");
        return;
    }

    if(list->current == NULL) {
        list->current = visit;
        return;
    }

    newVisit = malloc(sizeof(struct ZoznamNavstev));
    newVisit->current = visit;
    newVisit->_next = NULL;

    while (list->_next != NULL) {
        list = list->_next;
    }
    list->_next = newVisit;
}

void listVisitsRow(struct Navsteva *visit)
{
    if(visit == NULL) {
        printf("Visit is not inicialized\n");
        return;
    }

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
    if(list == NULL) {
        printf("List is not inicialized\n");
        return;
    }

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
    if(visit == NULL) {
        printf("Visit is not inicialized\n");
        return;
    }

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

    if(filename == NULL || strcmp(filename, "") == 0) {
        printf("Wrong filename\n");
        return NULL;
    }

    list = malloc(sizeof(struct ZoznamNavstev));
    list->current = NULL;
    list->_next = NULL;

    printLine(false);
    printf("Otvaram subor na citanie...\n");
    fr = fopen(filename, "r");

    if(fr==NULL) {
        printf("Súbor nebol nájdený");
        return NULL;
    }

    printf("Zacinam citat zo suboru...\n");

    while ((int)(getline(&line, &len, fr)) != -1) {
        visit = malloc(sizeof(struct Navsteva));
        sscanf(line, "%d %d:%d %d %49[^\t.\n]%*c", &visit->day, &visit->hour, &visit->minute, &visit->timeSpent, visit->name);
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

    if(list == NULL) {
        printf("List is not inicialized\n");
        return;
    }
    if(filename == NULL || strcmp(filename, "") == 0) {
        printf("Wrong filename\n");
        return;
    }

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

    if(list == NULL) {
        printf("List is not inicialized\n");
        return 0;
    }

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

    if(list == NULL) {
        printf("List is not inicialized\n");
        return NULL;
    }

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

    if(list == NULL) {
        printf("List is not inicialized\n");
        return NULL;
    }
    if(name == NULL || strcmp(name, "") == 0) {
        printf("Wrong name\n");
        return NULL;
    }

    nameList = malloc(sizeof(struct ZoznamNavstev));
    nameList->current = NULL;
    nameList->_next = NULL;

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

    if(list == NULL) {
        printf("List is not inicialized\n");
        return -1;
    }
    if(name == NULL || strcmp(name, "") == 0) {
        printf("Wrong name\n");
        return -1;
    }

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

    if(list == NULL) {
        printf("List is not inicialized\n");
        return -1;
    }

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

    if(list == NULL) {
        printf("List is not inicialized\n");
        return 0;
    }

    do {
        if(list->current == NULL && list->_next==NULL)
            break;
        if(list->current != NULL) {
            total += (int) list->current->timeSpent / 60;
            if(list->current->timeSpent % 60 > 0)
                total++;
        }
        list = list->_next;
    } while(list != NULL);

    return total * price;
}

int main(void)
{
    struct ZoznamNavstev *list = NULL;
    struct ZoznamNavstev *helpList = NULL;
    struct Navsteva *visit;
    int endRequested = false;
    int n;
    float price;

    int inputInt;
    char inputString[MAX] = "";

    list = malloc(sizeof(struct ZoznamNavstev));
    list->current = NULL;
    list->_next = NULL;

    while (endRequested == false) {
        printf("- MENU ---------------------\n");
        printf(" [1] - Načítaj zo súboru\n");
        printf(" [2] - Ulož do súboru\n");
        printf(" [3] - Vytvor a pridaj návštevu\n");
        printf(" [4] - Výpis n-tej návštevy\n");
        printf(" [5] - Výpis všetkých návštev\n");
        printf(" [6] - Priemerný čas jednej návštevy\n");
        printf(" [7] - Najdlhšia návšteva\n");
        printf(" [8] - Vypíš zoznam návštev jedného návštevníka\n");
        printf(" [9] - Celkový čas návštev jedného návštevníka\n");
        printf("[10] - Deň s najväčším počtom návštev\n");
        printf("[11] - Celkový zárobok\n");
        printf(" [0] - Zatvoriť\n");

        printf("Zadajte akciu: ");
        scanf("%d", &inputInt);
        printf("\n");

        switch (inputInt) {
            case 1:
                printLine(false);
                printf("Zadajte názov súboru: ");
                scanf("%s", inputString);
                printf("\n");
                list = loadFromFile(inputString);
                if(list==NULL) {
                    endRequested = true;
                }
                break;
            case 2:
                printLine(false);
                printf("Zadajte názov súboru: ");
                scanf("%s", inputString);
                printf("\n");
                saveToFile(list, inputString);
                break;
            case 3 :
                visit = malloc(sizeof(struct Navsteva));

                printLine(false);
                printf("Pridanie novej návštevy\n");
                printf("Zadajte deň: ");
                scanf("%d", &visit->day);
                printf("Zadajte hodinu: ");
                scanf("%d", &visit->hour);
                printf("Zadajte minutu: ");
                scanf("%d", &visit->minute);
                printf("Zadajte celkovy cas: ");
                scanf("%d", &visit->timeSpent);
                printf("Zadajte meno: ");
                scanf(" %49[^\t.\n]%*c", visit->name);

                visit = createVisit(visit->day, visit->hour, visit->minute, visit->timeSpent, visit->name);
                printVisit(visit);
                addVisit(list, visit);


                break;
            case 4 :
                printf("Zadajte poradové číslo návštevy: ");
                scanf("%d", &inputInt);

                n = 0;
                visit = NULL;

                helpList = list;
                if(helpList==NULL) {
                    break;
                }
                do {
                    if(helpList->current == NULL && helpList->_next==NULL)
                        break;

                    if(helpList->current != NULL) {
                        n++;
                        if(n==inputInt) {
                            visit = helpList->current;
                            break;
                        }
                    }
                    helpList = helpList->_next;
                } while(helpList != NULL);

                printVisit(visit);

                break;
            case 5:
                listVisits(list);
                break;
            case 6:
                printLine(false);
                printf("Priemerná dĺžka návštevy je: %.2f \n", getAverageSpentOfOneVisit(list));
                printLine(true);
                break;
            case 7:
                printLine(false);
                printf("Najdlhšia návšteva je:\n");
                printVisit(getLongestVisit(list));
                break;
            case 8:
                printf("Zadajte meno: ");
                scanf(" %49[^\t.\n]%*c", inputString);

                listVisits(getListOfName(list, inputString));
                break;
            case 9:
                printf("Zadajte meno: ");
                scanf(" %49[^\t.\n]%*c", inputString);

                printLine(false);
                printf("Celkovy čas klienta '%s' je: %d\n", inputString, getTotalSpentTimeOfName(list, inputString));
                printLine(true);
                break;
            case 10:
                printLine(false);
                printf("Najlepsim dnom bol %d. den v mesiaci\n", getBestDay(list));
                printLine(true);
                break;
            case 11:
                printf("Zadajte cenu za hodinu: ");
                scanf("%f", &price);

                printLine(false);
                printf("Celkovy zarobok pri cene %.2f €: %.2f€\n", price, getTotalIncome(list, price));
                printLine(true);
                break;
            case 0:
                printf("\nDovidenia");
                endRequested = true;
                break;
            default:
                printf("\nWrong input\n");
        }
        printf("\n");
        if(endRequested==false) {
            printf("Press any key to continue\n");
            getchar();
            getchar();
        }
    }
    return 0;
}
