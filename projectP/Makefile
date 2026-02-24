CC = gcc #prekladac/kompilator se jmenuje gcc
CFLAGS = -Wall -Wextra -g -fsanitize=address #zapnuti zakladnich varovani
TARGET = jbk #promena target obsahuje jmeno vysledneho programu

$(TARGET): main.c tga.c #pravidlo pro vytvoreni ciloveho souboru
	$(CC) $(CFLAGS) -o $(TARGET) main.c tga.c
#prikaz se spesti v terminalu...zavola gcc, preda mu vlajky, vystup ulozi do jbk a main.c tga.c prelozi

clean: #smaze vytvoreny program/soubor
	rm -f $(TARGET)