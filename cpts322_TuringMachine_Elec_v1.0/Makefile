# Compiler and options
CC = g++
OPTIONS = -g -Wall

# Main executable
all: tm

# Test executables
test: main_state_test main_tape_test

# Object file rules
string_play.o: string_play.cpp string_play.h 
	$(CC) $(OPTIONS) -c $< -o $@

tape.o: tape.cpp tape.h
	$(CC) $(OPTIONS) -c $< -o $@

state.o: state.cpp state.h
	$(CC) $(OPTIONS) -c $< -o $@

final_state.o: final_state.cpp final_state.h
	$(CC) $(OPTIONS) -c $< -o $@

final_states.o: final_states.cpp final_states.h
	$(CC) $(OPTIONS) -c $< -o $@

crash.o: crash.cpp crash.h
	$(CC) $(OPTIONS) -c $< -o $@

transition.o: transition.cpp transition.h
	$(CC) $(OPTIONS) -c $< -o $@

transition_function.o: transition_function.cpp transition_function.h
	$(CC) $(OPTIONS) -c $< -o $@

visible.o: visible.cpp visible.h 
	$(CC) $(OPTIONS) -c $< -o $@

turing_machine.o: turing_machine.cpp turing_machine.h
	$(CC) $(OPTIONS) -c $< -o $@

input_alphabet.o: input_alphabet.cpp input_alphabet.h
	$(CC) $(OPTIONS) -c $< -o $@

tape_alphabet.o: tape_alphabet.cpp tape_alphabet.h
	$(CC) $(OPTIONS) -c $< -o $@

states.o: states.cpp states.h
	$(CC) $(OPTIONS) -c $< -o $@

# Main program object
tm.o: main.cpp
	$(CC) $(OPTIONS) -c $< -o $@

# Final executable build
tm: tm.o tape.o crash.o state.o final_state.o final_states.o states.o \
	transition.o transition_function.o visible.o turing_machine.o \
	input_alphabet.o tape_alphabet.o string_play.o
	$(CC) $(OPTIONS) $^ -o $@

# State test
main_state_test.o: main_state_test.cpp
	$(CC) $(OPTIONS) -c $< -o $@

main_state_test: main_state_test.o state.o
	$(CC) $(OPTIONS) $^ -o $@

# Tape test
main_tape_test.o: main_tape_test.cpp
	$(CC) $(OPTIONS) -c $< -o $@

main_tape_test: main_tape_test.o tape.o crash.o
	$(CC) $(OPTIONS) $^ -o $@

# Clean target
clean:
	@rm -f tm main_state_test main_tape_test *.o
