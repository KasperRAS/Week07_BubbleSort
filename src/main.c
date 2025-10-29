/* ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
 ¤ main.c                                                                         ¤
 ¤ ~~~~~~~~~~~~~~~~~~~~                                                           ¤
 ¤ Indeholder funktioner til at håndtere brugerens input, sende det til sort.c    ¤
 ¤ og udskrive resultatet af sorteringen til terminalen.                          ¤
 ¤ ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "sort.h"

#define MAKS_ELEMENTER 256

/* ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
 ¤ laes_linje                                                                               ¤
 ¤ ~~~~~~~~~~~~~~~~~~~~                                                                     ¤
 ¤ Læser én linje fra stdin ind i 'buffer' (inkl. evt. mellemrum).                          ¤
 ¤ ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ */
static size_t laes_linje(char *buffer, size_t kapacitet) {
    if (!fgets(buffer, (int)kapacitet, stdin)) return 0;
    size_t n = strlen(buffer);
    if (n && buffer[n-1] == '\n') buffer[--n] = '\0';       // Fjerner evt. \n for at undgå uønskede linjeskift.
    return n;
}

/* ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
 ¤ tjek_bogstaver                                                                           ¤
 ¤ ~~~~~~~~~~~~~~~~~~~~                                                                     ¤
 ¤ Lægger alle bogstaver (A–Z/a–z) fra 'linje' over i 'ud' og ignorerer øvrige tegn.        ¤
 ¤ Returnerer antal håndterede/gemte tegn (n).                                              ¤
 ¤ ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ */
static size_t tjek_bogstaver(const char *linje, char *ud) {
    size_t n = 0;
    for (const char *p = linje; *p && n < MAKS_ELEMENTER; ++p)
        if (isalpha((unsigned char)*p)) ud[n++] = *p;          // Tjekker for bogstaver
    return n;
}

/* ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
 ¤  tjek_tal                                                                                ¤
 ¤ ~~~~~~~~~~~~~~~~~~~~                                                                     ¤
 ¤ Læser heltal separeret af mellemrum fra 'linje' til 'ud' (lagres som signed char).       ¤
 ¤ Returnerer antal tal. Ikke-numeriske stykker ignoreres.                                  ¤
 ¤ ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ */
static size_t tjek_tal(const char *linje, char *ud) {
    size_t n = 0;
    const char *p = linje; char *slut = NULL;
    while (*p && n < MAKS_ELEMENTER) {
        long v = strtol(p, &slut, 10);
        if (slut == p) { ++p; continue; }               // Spring ikke-tal over.
        ud[n++] = (char)v;                              // Afkorter/trunkerer til signed char.
        p = slut;
    }
    return n;
}

/* ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
 ¤ udskriv_bogstaver                                                                        ¤
 ¤ ~~~~~~~~~~~~~~~~~~~~                                                                     ¤
 ¤ Skriver 'n' bogstaver som en kompakt streng efterfulgt af newline.                       ¤
 ¤ ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ */
static void udskriv_bogstaver(const char *a, size_t n) {
    for (size_t i = 0; i < n; ++i) putchar(a[i]);
    putchar('\n');
}

/* ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
 ¤ udskriv_tal                                                                              ¤
 ¤ ~~~~~~~~~~~~~~~~~~~~                                                                     ¤
 ¤ Skriver 'n' tal (castet til int => ikke ASCII-output) separeret af mellemrum.            ¤
 ¤ ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ */
static void udskriv_tal(const char *a, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        if (i) putchar(' ');
        printf("%d", (int)a[i]);
    }
    putchar('\n');
}

/* ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
 ¤ main                                                                                     ¤
 ¤ ~~~~~~~~~~~~~~~~~~~~                                                                     ¤
 ¤ Spørger brugeren om typen af data: (b)ogstaver eller (t)al.                              ¤
 ¤ Læser og analyserer brugerens input, som gemmes til et array, hvorefter det skrives til  ¤
 ¤ et array og sorterer med boblesortering + sammenligner.                                  ¤
 ¤ Før- og efter-resultat udskrives til terminalen med puts().                              ¤
 ¤ ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ */
int main(void) {
    char valg[16], linje[1024];         // Buffere til brugerens valg og input.
    char liste[MAKS_ELEMENTER];         // Liste med brugerens gemte input. 
    size_t antal = 0;

    puts("Vælg datatype: (b)ogstaver eller (t)al:");
    laes_linje(valg, sizeof valg);
    int mode = tolower((unsigned char)valg[0]);        // Konvertering til lowercase -> både b/t og B/T kan bruges.
                                                                    
    if (mode == 'b') {
        puts("Skriv bogstaver (mellemrum ignoreres):");
        laes_linje(linje, sizeof linje);
        antal = tjek_bogstaver(linje, liste);

        if (!antal) {                                  // Intet at sortere = Slut
            puts("Ingen bogstaver fundet."); 
            return 0; 
        }

        puts("Før:");
        udskriv_bogstaver(liste, antal);
        boblesortering(liste, antal, bogstaver_i_orden);
        puts("Efter:");
        udskriv_bogstaver(liste, antal);

    } else if (mode == 't') {
        puts("Skriv heltal separeret af mellemrum (fx: 4 -1 2 9):");
        laes_linje(linje, sizeof linje);
        antal = tjek_tal(linje, liste);

        if (!antal) { 
            puts("Ingen tal fundet."); 
            return 0; 
        }

        puts("Før:");
        udskriv_tal(liste, antal);
        boblesortering(liste, antal, tal_stigende);
        puts("Efter:");
        udskriv_tal(liste, antal);

    } else {
        puts("Ukendt valg. Brug 'b' eller 't'.");
    }
    return 0;
}
