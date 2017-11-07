SHELL=/bin/bash #come prima riga indicare sempre la shell che si intende usare

all:		tutto.txt 

tutto.txt:	B1.txt B2.txt
			
			cat B1.txt > tutto.txt; cat B2.txt >> tutto.txt

B1.txt:		A1.txt
			cat A1.txt > B1.txt ; date >> B1.txt

B2.txt:		A2.txt
			cat A2.txt > B2.txt ; date >> B2.txt

A1.txt:			
			echo "ZZZZZ" > A1.txt

A2.txt:
			echo "YYYYY" > A2.txt

.PHONY: clean touch

clean:	
		rm A1.txt A2.txt
touch:
		if [[ -e B2.txt]]; then touch B1.txt; fi
