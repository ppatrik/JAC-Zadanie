# Zadanie 2

Vytvorte modul a používateľské rozhranie, ktoré mestu pomôže „vydolovať“ z údajov, ktoré majú, nejaké zaujímavé informácie. Výstupy z turniketov sú vo forme mesačných správ, t.j. všetky údaje sú viazané na konkrétny kalendárny mesiac

Naše náznamy uložené v súbore vyzerajú nasledovne:
```
den v mesiaci   hodina:minúta  trvanie  meno a priezvisko.
```

**Príklady:**
```
3 8:30 120 Peter Plavec 
4 15:59 50 Martina Moravcová  
```

Vytvorte štruktúru **Navsteva**, ktorá bude uchovávať nasledujúce údaje:
- deň v mesiaci, kedy návštevník do plavárne vstúpil (deň návštevy), 
- hodina a minúta (čas) dňa, kedy návštevník vstúpil na plaváreň (prešiel turniketom), 
- trvanie vstupu v minútach, t.j. čas aký návštevník počas tejto návštevy strávil na plavárni, 
- meno a priezvisko návštevníka (kvôli jednoduchosti predpokladáme, že ľudia majú rôzne mená – pri skutočnej aplikácii by sme namiesto mena použili napríklad číslo karty). 

Ďalej vytvorte zoznam **ZoznamNavstev**, ktorá reprezentuje zoznam všetkých návštev plavárne v danom kalendárnom mesiaci. 

### Modul nech obsahuje funkcionalitu:
- Načítanie dát zo súboru
- Vytváranie nových návštev
- Pridávanie návštev do zoznamu návštev
- Vypísanie návštevy na obrazovku vo vhodnom tvare
- Vypísanie celého zoznamu na obrazovku v prijateľnom tvare
- Uloženie všetkých návštev zo zoznamu do súboru v takom tvare, ktorý môže byť opäť našim vstupným súborom
- Vypočítanie priemernej dĺžky jednej návštevy plavárne
- Nájdenie najdlhšie trvajúcej návštevy  plavárne
- Vytvorenie nového zoznamu všetkých návštev zadaného návštevníka
- Vypočítanie celkového času, ktorý strávil zadaný návštevník na plavárni
- Nájdenie dňa v týždni, počas ktorého sme zaznamenali najväčší počet návštev
- Vypočítanie celkových príjmov plavárne, ak určíme cenu za každú začatú hodinu

### Ďalšie požiadavky:
- Modul nech je dodaný v podobe samostatného C súboru vrátane hlavičkového súboru obsahujúceho požadované funkcie
- Vhodným spôsobom demonštrujte korektnú funkcionalitu vašej knižnice — odporúča sa vytvoriť jednoduché používateľské rozhranie, kde oddemonštrujete funkcionalitu.

#### Odporúčania:
- odporúča sa použiť spojový zoznam spojových zoznamov
- stačí využiť dátovú štruktúru pre zásobník z cvičení, ktorá je spojovým zoznamom.
