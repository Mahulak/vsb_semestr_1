Program, který umí komprimovat a dekomprimovat TGA obrázky metodou JBK (jé-bé-ké), neboli Jednoduchou Blokovou Kompresí.

1.  Komprese funguje tak, že rozdělí obrázek na bloky se zadaným rozměrem a v každém bloku bude hledat posloupnosti podobných pixelů. Ty poté nahradí dvojicí obsahující první pixel v posloupnosti a počet pixelů v posloupnosti. Jedná se o formu tzv. RLE (run-length encoding) komprese.

2.  Při dekompresi se provadi inverze předchozí komprese. Načítá z disku JBK soubor a přečte si z něj, jaké měl původní obrázek rozměry a velikost bloku. Poté si vytvoří prázdný TGA obrázek s odpovídajícími rozměry.

Komprese:
    Bash:
    ./jbk compress --input <vstup.tga> --output <vystup.jbk> --block-size <cislo> --max-diff <cislo>

    --input: Cesta ke vstupnímu souboru
    --output: Cesta k výstupnímu souboru.
    --block-size: Velikost čtvercového bloku
    --max-diff: Maximální povolený rozdíl barev.

Dekomprese:
    Bash:
    ./jbk decompress --input <vstup.jbk> --output <vystup.tga>

    --input: Cesta ke vstupnímu souboru
    --output: Cesta k výstupnímu souboru.

Kompilace:
    přeložení přímo pomocí kompilátoru GCC následujícím příkazem:
    
    Bash:

    gcc -Wall -Wextra -g -fsanitize=address -o jbk main.c tga.c

    -Wall -Wextra: Zapne výpis všech varování (užitečné pro kontrolu chyb).
    -g: Přidá ladící informace
    -fsanitize=address: Zapne kontrolu práce s pamětí
    -o jbk: Název výstupního souboru.
    main.c tga.c: Seznam všech zdrojových souborů projektu.



