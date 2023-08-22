all:
	gcc *.c -o tp1 -Wall

run:
	mkdir -p ../output/n$(TAM)
ifeq ($(ALG),1)
	./tp1 $(ALG) $(TAM) > ../output/n$(TAM)/Insertion_Sort.out
else ifeq ($(ALG),2)
	./tp1 $(ALG) $(TAM) > ../output/n$(TAM)/Merge_Sort.out
else ifeq ($(ALG),3)
	./tp1 $(ALG) $(TAM) > ../output/n$(TAM)/Radix_Sort.out
endif
