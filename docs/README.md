# Week07_BubbleSort
Programmet skal kunne tjekke om brugerens input er bogstaver eller tal,
hvorefter det skal sortere dette i stigende alfabetisk eller numerisk rækkefølge.
Brugeren spørges om type (bogstaver eller tal) og data, der skal sorteres,
hvorefter det sorteres.

# main.c
Håndterer input fra brugeren og udskrift af data til terminalen.
Tjekker for bogstaver/tal (andre tegn ignoreres/fjernes) og 
lægger dem i et array til brug for de tilhørende funktioner.
Kalder funktionerne i sort.c/.h til sortering af brugerens data.

# sort.c/.h
Sorterer alle bogstaver/tal gemt i arrayet.
For bogstaver gælder det at case (upper/lower) ignoreres under sorteringen.

# Filer
- main.c
- sort.c
- sort.h
- README.md
- BubbleSort_flow.svg
- tasks.json
- launch.json
- compile_flags.txt
- .gitignore