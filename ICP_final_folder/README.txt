Autoři: Boris Burkalo (xkburka00), Jan Klusáček (xklusa14)

Aplikace pro zobrazení linek hromadné dopravy a sledování jejich pohybu

Překlad:
- make
Spuštění:
- make run
Zabalení do archivu zip:
- make pack
Vytvoření dokumentace:
- make doxygen
Smazání dokumentace:
- make clean-doxy
Smazání archivu:
- make clean-pack

-- všechny tyto make příkazy musí být provedeny z kořenové složky

Ovládání aplikace:
- Aplikace se ovládá pomocí tlačítek nacházejících se na pravé straně okna. Jejich popis najdete na hlavní stránce dokumentace (index.html - viz. dále).
- Pro vybrání vozdila nebo ulice se použije levé tlačítko myši, pro vybrání ulice na objížďku se použije pravé tlačítko myši.

Dokumentace:
- Pro vytvoření dokumentace zadejte v kořenovém adresáři příkaz 'make doxygen'. Dokumentace se vygeneruje ve složce /doc/html.
- Pro její přečtení otevřete soubor 'index.html' v libovolném prohlížeči.

Odevzdaná složka obsahuje:
- složku src se zdrojovými kódy
- složku doc, která v podsložce img obsahuje obrázky, které jsou obsažené v dokumentaci
- složku examples obsahující mapové podklady a jízdní řády
- Makefile sloužící pro překlad a spuštění programu, vygenerování dokumentace,...
- README.txt soubor
