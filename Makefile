
.PHONY: all clean Ex.1-4 Ex.5-6 Ex.7 Ex.8-9 cps

all: Ex.1-4 Ex.5-6 Ex.7 Ex.8-9

Ex.1-4:
	make -C Ex.1-4 all

Ex.5-6:
	make -C Ex.5-6 all

Ex.7:
	make -C Ex.7 all

Ex.8-9: 
	make -C Ex.8-9 all

# Cleaning:
clean:
	make -C Ex.1-4 clean
	make -C Ex.5-6 clean
	make -C Ex.7 clean
	make -C Ex.8-9 clean

cps:
	git commit -a -m "$(m)"
	git push
	git status