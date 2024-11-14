all: ex1_2 ex3_4

ex1_2: Exercises2024/Ex1_2/Makefile
	@make -C Exercises2024/Ex1_2

ex3_4: Exercises2024/Ex3_4/Makefile
	@make -C Exercises2024/Ex1_2

cleanall:
	@make -C Exercises2024/Ex1_2 clean
	@make -C Exercises2024/Ex3_4 clean

.PHONY: all ex1_2 ex3_4 cleanall