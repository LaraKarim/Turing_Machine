#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define MAX_STATES 100
#define MAX_SYMBOLS 100
#define MAX_TRANSITIONS 1000
#define TAPE_SIZE 1000
#define BLANK_SYMBOL '#'

// Direction constants
#define LEFT 'L'
#define RIGHT 'R'
#define ACCEPT 'Y'
#define REJECT 'N'

// Define the transition structure
typedef struct {
    char currentState;
    char currentSymbol;
    char nextState;
    char nextSymbol;
    char action;  // Can be LEFT, RIGHT, ACCEPT, or REJECT
} Transition;

// Define the Turing Machine structure
typedef struct {
    char states[MAX_STATES];
    char inputAlphabet[MAX_SYMBOLS];
    char tapeAlphabet[MAX_SYMBOLS];
    char initialState;
    Transition transitions[MAX_TRANSITIONS];
    int transitionCount;
} TuringMachine;

// Function prototypes
void initializeTuringMachine(TuringMachine* tm);
void addTransition(TuringMachine* tm, char currentState, char currentSymbol, char nextState, char nextSymbol, char action);
void executeTuringMachine(TuringMachine* tm, char* inputString, int headPosition);
void encodeTuringMachine(TuringMachine* tm, char* encodedString);
void encodeTuringMachineDetailed(TuringMachine* tm, char* detailedString);
void intToBinary(int num, char* binStr);

int main() {
    TuringMachine tm;
    initializeTuringMachine(&tm);

    int numStates, numInputAlphabet, numTapeAlphabet, numTransitions;
    char inputString[TAPE_SIZE];
    int headPosition;

    // Get user input
    printf("Enter number of states: ");
    scanf("%d", &numStates);
    printf("Enter states <one charachter only> : ");
    for (int i = 0; i < numStates; i++) {
        scanf(" %c", &tm.states[i]);
    }
    tm.states[numStates] = '\0';

    printf("Enter size of input alphabet: ");
    scanf("%d", &numInputAlphabet);
    printf("Enter input alphabet: ");
    for (int i = 0; i < numInputAlphabet; i++) {
        scanf(" %c", &tm.inputAlphabet[i]);
    }
    tm.inputAlphabet[numInputAlphabet] = '\0';

    printf("Enter size of tape alphabet: ");
    scanf("%d", &numTapeAlphabet);
    printf("Enter tape alphabet: ");
    for (int i = 0; i < numTapeAlphabet; i++) {
        scanf(" %c", &tm.tapeAlphabet[i]);
    }
    tm.tapeAlphabet[numTapeAlphabet] = '\0';

    printf("Enter initial state: ");
    scanf(" %c", &tm.initialState);

    printf("Enter number of transitions: ");
    scanf("%d", &numTransitions);
    printf("Enter transitions in the format (currentState currentSymbol nextState nextSymbol action:L OR R OR Y OR N: \n");
    for (int i = 0; i < numTransitions; i++) {
        char currentState, currentSymbol, nextState, nextSymbol, action;
        scanf(" %c %c %c %c %c", &currentState, &currentSymbol, &nextState, &nextSymbol, &action);
        addTransition(&tm, currentState, currentSymbol, nextState, nextSymbol, action);
    }

    printf("Enter tape: ");
    scanf("%s", inputString);
    printf("Enter head position: ");
    scanf("%d", &headPosition);

    // Execute the Turing Machine
    executeTuringMachine(&tm, inputString, headPosition);

    // Encode the Turing Machine
    char encodedString[1000];
    encodeTuringMachine(&tm, encodedString);
    printf("Encoded Turing Machine: %s\n", encodedString);

    // Encode the Turing Machine with details
    char detailedString[5000];
    encodeTuringMachineDetailed(&tm, detailedString);
    printf("Detailed Encoded Turing Machine:\n%s\n", detailedString);

    return 0;
}

void initializeTuringMachine(TuringMachine* tm) {
    tm->transitionCount = 0;
}

void addTransition(TuringMachine* tm, char currentState, char currentSymbol, char nextState, char nextSymbol, char action) {
    Transition t;
    t.currentState = currentState;
    t.currentSymbol = currentSymbol;
    t.nextState = nextState;
    t.nextSymbol = nextSymbol;
    t.action = action;
    tm->transitions[tm->transitionCount++] = t;
}

void executeTuringMachine(TuringMachine* tm, char* inputString, int headPosition) {
    char tape[TAPE_SIZE];
    memset(tape, BLANK_SYMBOL, TAPE_SIZE);
    strcpy(tape, inputString);

    char currentState = tm->initialState;
    int currentHeadPosition = headPosition;
    int step = 0;

    while (1) {
        char currentSymbol = tape[currentHeadPosition];

        int found = 0;
        for (int i = 0; i < tm->transitionCount; i++) {
            Transition t = tm->transitions[i];
            if (t.currentState == currentState && t.currentSymbol == currentSymbol) {
                tape[currentHeadPosition] = t.nextSymbol;
                currentState = t.nextState;

                if (t.action == RIGHT) {
                    currentHeadPosition++;
                    // If the head moves beyond the current string length, extend the tape with a blank symbol
                    if (currentHeadPosition >= strlen(tape)) {
                        tape[currentHeadPosition] = BLANK_SYMBOL;
                        tape[currentHeadPosition + 1] = '\0';
                    }
                } else if (t.action == LEFT) {
                    currentHeadPosition--;
                } else if (t.action == ACCEPT) {
                    printf("Step %d: State=%c, Head=%d, Tape=%s\n", step++, currentState, currentHeadPosition, tape);
                    printf("Output Tape: %s\n", tape);
                    printf("String accepted.\n");
                    return;
                } else if (t.action == REJECT) {
                    printf("Step %d: State=%c, Head=%d, Tape=%s\n", step++, currentState, currentHeadPosition, tape);
                    printf("Output Tape: %s\n", tape);
                    printf("String rejected.\n");
                    return;
                }

                printf("Step %d: State=%c, Head=%d, Tape=%s\n", step++, currentState, currentHeadPosition, tape);

                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Halting: No transition found.\n");
            printf("Output Tape: %s\n");
            break;
        }

        if (currentHeadPosition < 0 || currentHeadPosition >= TAPE_SIZE) {
            printf("Error: Head moved out of tape bounds.\n");
            printf("Output Tape: %s\n");
            break;
        }
    }

    printf("Final Tape: %s\n", tape);
}

void intToBinary(int num, char* binStr) {
    binStr[0] = '\0';
    if (num == 0) {
        strcat(binStr, "1");
    } else {
        while (num > 0) {
            strcat(binStr, (num % 2) ? "1" : "11");
            num /= 2;
        }
    }
}

void encodeTuringMachine(TuringMachine* tm, char* encodedString) {
    char buffer[10000] = {0};  // Use a buffer to build the encoded string
    int position = 0;  // Position in the buffer

    // Helper function to append unary encoding of a number to the buffer
    void appendUnary(int n) {
        for (int i = 0; i < n; i++) {
            buffer[position++] = '1';
        }
        buffer[position++] = '0';  // Append a '0' as a separator
    }

    // Create a map of symbols to their unary encodings
    char allSymbols[MAX_SYMBOLS * 2];
    int allSymbolsCount = 0;

    // Collect all unique symbols from inputAlphabet and tapeAlphabet
    for (int i = 0; i < strlen(tm->inputAlphabet); i++) {
        allSymbols[allSymbolsCount++] = tm->inputAlphabet[i];
    }
    for (int i = 0; i < strlen(tm->tapeAlphabet); i++) {
        if (strchr(allSymbols, tm->tapeAlphabet[i]) == NULL) {
            allSymbols[allSymbolsCount++] = tm->tapeAlphabet[i];
        }
    }



    // Encode each input alphabet symbol
    for (int i = 0; i < strlen(tm->inputAlphabet); i++) {
        int symbolIndex = strchr(allSymbols, tm->inputAlphabet[i]) - allSymbols + 1;
        //appendUnary(symbolIndex);
    }

     // Create a separate array for states
    char states[MAX_STATES * 2];
    int statesCount = 0;

    // Collect all unique symbols from states
    for (int i = 0; i < strlen(tm->states); i++) {
        if (strchr(states, tm->states[i]) == NULL) {
            states[statesCount++] = tm->states[i];
        }
    }
    states[statesCount] = '\0';
    // Encode each tape alphabet symbol
    for (int i = 0; i < strlen(tm->tapeAlphabet); i++) {
        int symbolIndex = strchr(allSymbols, tm->tapeAlphabet[i]) - allSymbols + 1;
        //appendUnary(symbolIndex);
    }



    allSymbols[allSymbolsCount] = '\0';
    // Encode each transition
    for (int i = 0; i < tm->transitionCount; i++) {
        Transition t = tm->transitions[i];
        int currentStateIndex = strchr(states, t.currentState) - states + 1;
        appendUnary(currentStateIndex);
        int symbolIndex = strchr(allSymbols, t.currentSymbol) - allSymbols + 1;
        appendUnary(symbolIndex);  // Current symbol
        int nextStateIndex = strchr(states, t.nextState) - states + 1;
        appendUnary(nextStateIndex);
        symbolIndex = strchr(allSymbols, t.nextSymbol) - allSymbols + 1;
        appendUnary(symbolIndex);  // Next symbol
        switch (t.action) {  // Action
            case LEFT:
                appendUnary(1);  // L = 1
                break;
            case RIGHT:
                appendUnary(2);  // R = 11
                break;
            case ACCEPT:
                appendUnary(3);  // Y = 111
                break;
            case REJECT:
                appendUnary(4);  // N = 1111
                break;
        }
        // This is new, adding a zero between characters within a transition
        if (i < tm->transitionCount - 1) {
            buffer[position++] = '0';
        }
    }

    // Append "00" as the separator between transitions
    buffer[position++] = '0';
    buffer[position++] = '0';

    // Copy the buffer to the encodedString
    buffer[position - 1] = '\0';  // Remove the last unnecessary separator
    strcpy(encodedString, buffer);
}





void encodeTuringMachineDetailed(TuringMachine* tm, char* detailedString) {
    detailedString[0] = '\0';
    char binStr[32];

    strcat(detailedString, "(States: ");
    for (int i = 0; i < strlen(tm->states); i++) {
        intToBinary(i, binStr);
        strcat(detailedString, tm->states + i);
        strcat(detailedString, "->");
        strcat(detailedString, binStr);
        if (i < strlen(tm->states) - 1) strcat(detailedString, ", ");
    }
    strcat(detailedString, ")\n");

    strcat(detailedString, "(Input Alphabet: ");
    for (int i = 0; i < strlen(tm->inputAlphabet); i++) {
        intToBinary(i, binStr);
        strcat(detailedString, tm->inputAlphabet + i);
        strcat(detailedString, "->");
        strcat(detailedString, binStr);
        if (i < strlen(tm->inputAlphabet) - 1) strcat(detailedString, ", ");
    }
    strcat(detailedString, ")\n");

    strcat(detailedString, "(Tape Alphabet: ");
    for (int i = 0; i < strlen(tm->tapeAlphabet); i++) {
        intToBinary(i, binStr);
        strcat(detailedString, tm->tapeAlphabet + i);
        strcat(detailedString, "->");
        strcat(detailedString, binStr);
        if (i < strlen(tm->tapeAlphabet) - 1) strcat(detailedString, ", ");
    }
    strcat(detailedString, ")\n");

    strcat(detailedString, "(Initial State: ");
    intToBinary(0, binStr); // Initial state is always first state
    strcat(detailedString, tm->initialState);
    strcat(detailedString, "->");
    strcat(detailedString, binStr);
    strcat(detailedString, ")\n");

    strcat(detailedString, "(Transitions: ");
    for (int i = 0; i < tm->transitionCount; i++) {
        Transition t = tm->transitions[i];
        intToBinary(t.currentState - 'A', binStr);
        strcat(detailedString, "(");
        strcat(detailedString, t.currentState);
        strcat(detailedString, ", ");
        strcat(detailedString, t.currentSymbol);
        strcat(detailedString, ") -> (");
        strcat(detailedString, t.nextState);
        strcat(detailedString, ", ");
        strcat(detailedString, t.nextSymbol);
        strcat(detailedString, ", ");
        strcat(detailedString, t.action == RIGHT ? "R" : t.action == LEFT ? "L" : t.action == ACCEPT ? "Y" : "N");
        strcat(detailedString, ") -> (");
        strcat(detailedString, binStr);
        strcat(detailedString, ", ");
        intToBinary(t.currentSymbol - '0', binStr);
        strcat(detailedString, binStr);
        strcat(detailedString, ", ");
        intToBinary(t.nextState - 'A', binStr);
        strcat(detailedString, binStr);
        strcat(detailedString, ", ");
        intToBinary(t.nextSymbol - '0', binStr);
        strcat(detailedString, binStr);
        strcat(detailedString, ", ");
        strcat(detailedString, t.action == RIGHT ? "1" : t.action == LEFT ? "11" : t.action == ACCEPT ? "111" : "1111");
        strcat(detailedString, ")");
        if (i < tm->transitionCount - 1) strcat(detailedString, ", ");
    }
    strcat(detailedString, ")\n");

}
