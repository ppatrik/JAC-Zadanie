struct Navsteva;
struct ZoznamNavstev;

/* Načítanie dát zo súboru */
struct ZoznamNavstev *loadFromFile(char *filename); /* done 1 */

/* Vytváranie nových návštev */
struct Navsteva *createVisit(int day, int hour, int minute, int timeSpent, char name[]); /* done 3 */

/* Pridávanie návštev do zoznamu návštev */
void addVisit(struct ZoznamNavstev *list, struct Navsteva *visit); /* done part of 3 */

/* Vypísanie návštevy na obrazovku vo vhodnom tvare */
void printVisit(struct Navsteva *visit); /* done 4 */

/* Vypísanie celého zoznamu na obrazovku v prijateľnom tvare */
void listVisits(struct ZoznamNavstev *list); /* done 5 */

/* Uloženie všetkých návštev zo zoznamu do súboru v takom tvare, ktorý môže byť opäť našim vstupným súborom */
void saveToFile(struct ZoznamNavstev *list, char *filename); /* done 2 */

/* Vypočítanie priemernej dĺžky jednej návštevy plavárne */
float getAverageSpentOfOneVisit(struct ZoznamNavstev *list); /* done 6 */

/* Nájdenie najdlhšie trvajúcej návštevy  plavárne */
struct Navsteva *getLongestVisit(struct ZoznamNavstev *list); /* done 7 */

/* Vytvorenie nového zoznamu všetkých návštev zadaného návštevníka */
struct ZoznamNavstev *getListOfName(struct ZoznamNavstev *list, char *name); /* done 8 */

/* Vypočítanie celkového času, ktorý strávil zadaný návštevník na plavárni */
int getTotalSpentTimeOfName(struct ZoznamNavstev *list, char *name); /* done 9 */

/* Nájdenie dňa v týždni, počas ktorého sme zaznamenali najväčší počet návštev */
int getBestDay(struct ZoznamNavstev *list); /* done 10 */

/* Vypočítanie celkových príjmov plavárne, ak určíme cenu za každú začatú hodinu */
float getTotalIncome(struct ZoznamNavstev *list, float price); /* done 11 */
