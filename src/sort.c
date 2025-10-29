/* ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤
 ¤ sort.c                                                                         ¤
 ¤ ~~~~~~~~~~~~~~~~~~~~                                                           ¤
 ¤ Indeholder funktioner til sortering af brugerens input (fra main.c).           ¤
 ¤ ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ */

#include <stdio.h>
#include <ctype.h>
#include "sort.h"

/* Kører listen med brugerens input i gennem indtil flere ombytninger ikke er mulige/nødvendige. */
void boblesortering(char liste[], size_t laengde, bool (*par_er_i_orden)(char a, char b)) {
    if (!liste || !par_er_i_orden || laengde < 2) return;
    bool byttet;
    do {
        byttet = false;
        for (size_t i = 1; i < laengde; ++i) {
            if (!par_er_i_orden(liste[i - 1], liste[i])) {
                ombytning(&liste[i - 1], &liste[i]);
                byttet = true;
            }
        }
    } while (byttet);
}

/* Kaldes af boblesortering() og håndterer selve ombytningen. */
void ombytning(char *venstre, char *hoejre) {
    if (!venstre || !hoejre) return;
    char tmp = *venstre;
    *venstre = *hoejre;
    *hoejre = tmp;
}

/* Tjekker om to bogstaver er i rækkefølge. Hvis nej, ombyttes de af boblesortering(). */
bool bogstaver_i_orden(char a, char b) {
    unsigned char ua = (unsigned char)a, ub = (unsigned char)b;
    return (char)tolower(ua) <= (char)tolower(ub);          // Konvertering af alle bogstaver til lowercase,
}                                                           // så store ikke kommer før små (lavere ASCII-værdi).

/* Som for bogstaver_i_orden men for tal. */
bool tal_stigende(char a, char b) {
    return a <= b;
}
