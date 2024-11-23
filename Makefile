all: ex1_2 ex3_4

ex1_2: Exercises2024/Ex1_2/Makefile
	@make -C Exercises2024/Ex1_2

ex3_4: Exercises2024/Ex3_4/Makefile
	@make -C Exercises2024/Ex1_2

run_all:
	@make -C Exercises2024/Ex1_2 clean
	@make -C Exercises2024/Ex3_4 clean

run_ex1_2: Exercises2024/Ex1_2/Makefile
	@make -C Exercises2024/Ex1_2 run

run_ex3_4: Exercises2024/Ex3_4/Makefile
	@make -C Exercises2024/Ex3_4 run

clean_all:
	@make -C Exercises2024/Ex1_2 run
	@make -C Exercises2024/Ex3_4 run

clean_ex1_2: Exercises2024/Ex1_2/Makefile
	@make -C Exercises2024/Ex1_2 clean

clean_ex3_4: Exercises2024/Ex3_4/Makefile
	@make -C Exercises2024/Ex3_4 clean

.PHONY: all ex1_2 ex3_4 run_all run_ex1_2 run_ex3_4 clean_all clean_ex1_2 clean_ex3_4