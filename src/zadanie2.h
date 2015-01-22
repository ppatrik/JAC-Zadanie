struct Navsteva;
struct ZoznamNavstev;

/* Načítanie dát zo súboru */
struct ZoznamNavstev *loadFromFile(char *filename); /* done */

/* Vytváranie nových návštev */
struct Navsteva *createVisit(int day, int hour, int minute, int timeSpent, char name[]); /* done */

/* Pridávanie návštev do zoznamu návštev */
void addVisit(struct ZoznamNavstev *list, struct Navsteva *visit); /* done */

/* Vypísanie návštevy na obrazovku vo vhodnom tvare */
void printVisit(struct Navsteva *visit); /* done */

/* Vypísanie celého zoznamu na obrazovku v prijateľnom tvare */
void listVisits(struct ZoznamNavstev *list); /* done */

/* Uloženie všetkých návštev zo zoznamu do súboru v takom tvare, ktorý môže byť opäť našim vstupným súborom */
void saveToFile(struct ZoznamNavstev *list, char *filename); /* done */

/* Vypočítanie priemernej dĺžky jednej návštevy plavárne */
float getAverageSpentOfOneVisit(struct ZoznamNavstev *list); /* done */

/* Nájdenie najdlhšie trvajúcej návštevy  plavárne */
struct Navsteva *getLongestVisit(struct ZoznamNavstev *list); /* done */

/* Vytvorenie nového zoznamu všetkých návštev zadaného návštevníka */
struct ZoznamNavstev *getListOfName(struct ZoznamNavstev *list, char *name); /* done */

/* Vypočítanie celkového času, ktorý strávil zadaný návštevník na plavárni */
int getTotalSpentTimeOfName(struct ZoznamNavstev *list, char *name); /* done */

/* Nájdenie dňa v týždni, počas ktorého sme zaznamenali najväčší počet návštev */
int getBestDay(struct ZoznamNavstev *list); /* done */

/* Vypočítanie celkových príjmov plavárne, ak určíme cenu za každú začatú hodinu */
float getTotalIncome(struct ZoznamNavstev *list, float price); /* done */
