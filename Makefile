dealer: dealer.c
	gcc dealer.c -o dealer
hand: hand.c
	gcc -I$$HOME/local/gsl-2.5/include hand.c -lgsl -lgslcblas -L$$HOME/local/gsl-2.5/lib -o hand
.PHONY: clean
clean: 
	rm -f hand
	rm -f dealer
