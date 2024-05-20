# Turing_Machine_Simulator

# Overview
This project implements a basic Turing Machine simulator in C. A Turing Machine is a mathematical model of computation that defines an abstract machine which manipulates symbols on a strip of tape according to a set of rules. This simulator allows you to define states, input and tape alphabets, and transitions, and then execute the machine on a given input string.

# Features
Define states, input alphabet, tape alphabet, and transitions.
Execute the Turing Machine on an input string.
Display step-by-step execution details.
Encode the Turing Machine's configuration and transitions in unary.

# Requirements
A C compiler (e.g., gcc).

# How to Use
1.Compile the program
2.Run the program
3.Input the required details:
- Number of states and the states themselves.
- Size of the input alphabet and the alphabet symbols.
- Size of the tape alphabet and the alphabet symbols.
- Initial state.
- Number of transitions and the transitions in the format (currentState currentSymbol nextState nextSymbol action).
- The input tape and initial head position.

4.View the output:
- The program will execute the Turing Machine and display each step.
- The final tape configuration and acceptance/rejection status will be displayed.

 # Example :
 - TM to erase string till first #:
 
Enter number of states: 1
Enter states <one charachter only> : 0
Enter size of input alphabet: 2
Enter input alphabet: ab
Enter size of tape alphabet: 3
Enter tape alphabet: ab#
Enter initial state: 0
Enter number of transitions: 3
Enter transitions in the format (currentState currentSymbol nextState nextSymbol action:L OR R OR Y OR N:
0 a 0 # R
0 b 0 # R
0 # 0 # Y
Enter tape: ab#
Enter head position: 0
Step 0: State=0, Head=1, Tape=#b#
Step 1: State=0, Head=2, Tape=###
Step 2: State=0, Head=2, Tape=###
Output Tape: ###
String accepted.
Encoded Turing Machine: 1010101110110010110101110110010111010111011100
