#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INSTRUCTIONS 100
#define MAX_PARAMETERS 10
#define MAX_PARAMETER_LENGTH 50

// Structure to represent an instruction
typedef struct
{
    int instruccion;
    int numero1;
    int numero2;
    char string1[15];
    char string2[15];
} Instruction;

typedef enum
{
    F_READ,
    F_WRITE,
    SET,
    MOV_IN,
    MOV_OUT,
    F_TRUNCATE,
    F_SEEK,
    CREATE_SEGMENT,
    IO,
    WAIT,
    SIGNAL,
    F_OPEN,
    F_CLOSE,
    DELETE_SEGMENT,
    YIELD,
    EXIT,
    INVALID
} InstructionType;

// Global variables
Instruction instructions[MAX_INSTRUCTIONS];
int instructionCount = 0;

// Function prototypes
void readNextWordFromFile(FILE *file, int index);
void readIntegerFromFile(FILE *file, int index);
InstructionType getNextInstruction(FILE *file);
void parseInstructions(FILE *file);
void match(FILE *file, const char *expected);
void error();

InstructionType getNextInstruction(FILE *file)
{
    char instruction[20];
    fscanf(file, "%s", instruction);

    if (strcmp(instruction, "SET") == 0)
    {
        return SET;
    }
    else if (strcmp(instruction, "MOV_OUT") == 0)
    {
        return MOV_OUT;
    }
    else if (strcmp(instruction, "WAIT") == 0)
    {
        return WAIT;
    }
    else if (strcmp(instruction, "I/O") == 0)
    {
        return IO;
    }
    else if (strcmp(instruction, "SIGNAL") == 0)
    {
        return SIGNAL;
    }
    else if (strcmp(instruction, "MOV_IN") == 0)
    {
        return MOV_IN;
    }
    else if (strcmp(instruction, "F_OPEN") == 0)
    {
        return F_OPEN;
    }
    else if (strcmp(instruction, "YIELD") == 0)
    {
        return YIELD;
    }
    else if (strcmp(instruction, "F_TRUNCATE") == 0)
    {
        return F_TRUNCATE;
    }
    else if (strcmp(instruction, "F_SEEK") == 0)
    {
        return F_SEEK;
    }
    else if (strcmp(instruction, "CREATE_SEGMENT") == 0)
    {
        return CREATE_SEGMENT;
    }
    else if (strcmp(instruction, "F_WRITE") == 0)
    {
        return F_WRITE;
    }
    else if (strcmp(instruction, "F_READ") == 0)
    {
        return F_READ;
    }
    else if (strcmp(instruction, "DELETE_SEGMENT") == 0)
    {
        return DELETE_SEGMENT;
    }
    else if (strcmp(instruction, "F_CLOSE") == 0)
    {
        return F_CLOSE;
    }
    else if (strcmp(instruction, "EXIT") == 0)
    {
        return EXIT;
    }
    else
    {
        return INVALID;
    }
}
void readIntegerFromFile(FILE *file, int index)
{
    int number;
    fscanf(file, "%d", &number);
    if (index == 1)
        instructions[instructionCount].numero1 = number;
    else
        instructions[instructionCount].numero2 = number;
}
void readNextWordFromFile(FILE *file, int index)
{
    char buffer[15];
    fscanf(file, "%s", buffer);
    if (index == 1)
        strcpy(instructions[instructionCount].string1, buffer);
    else
        strcpy(instructions[instructionCount].string2, buffer);
}

void parseInstructions(FILE *file)
{
    char *token = strtok(file, " ");
    int instruccion_actual;
    while (1)
    {
        instruccion_actual = getNextInstruction(file);
        instructions[instructionCount].instruccion = instruccion_actual;
        switch (instruccion_actual)
        {
        case F_READ:
            readNextWordFromFile(file, 1);
            readIntegerFromFile(file, 1);
            readIntegerFromFile(file, 2);
            break;
        case F_WRITE:
            readNextWordFromFile(file, 1);
            readIntegerFromFile(file, 1);
            readIntegerFromFile(file, 2);
            break;
        case SET:
            readNextWordFromFile(file, 1);
            readNextWordFromFile(file, 2);
            break;
        case MOV_IN:
            readNextWordFromFile(file, 1);
            readIntegerFromFile(file, 1);
            break;
        case MOV_OUT:
            readIntegerFromFile(file, 1);
            readNextWordFromFile(file, 1);
            break;
        case F_TRUNCATE:
            readNextWordFromFile(file, 1);
            readIntegerFromFile(file, 1);
            break;
        case F_SEEK:
            readNextWordFromFile(file, 1);
            readIntegerFromFile(file, 1);

            break;
        case CREATE_SEGMENT:
            readIntegerFromFile(file, 1);
            readIntegerFromFile(file, 2);
            break;
        case IO:
            readIntegerFromFile(file, 1);

            break;
        case WAIT:
            readNextWordFromFile(file, 1);
            break;
        case SIGNAL:
            readNextWordFromFile(file, 1);

            break;
        case F_OPEN:
            readNextWordFromFile(file, 1);
            break;
        case F_CLOSE:
            readNextWordFromFile(file, 1);
            break;
        case DELETE_SEGMENT:
            readIntegerFromFile(file, 1);
            break;
        case YIELD:

            break;
        case EXIT:
            instructionCount++;
            return;

            break;

        default:
            break;
        }
        instructionCount++;
    }
}

void match(FILE *file, const char *expected)
{
    char input[MAX_PARAMETER_LENGTH];
    fscanf(file, "%s", input);
    if (strcmp(input, expected) != 0)
    {
        error();
    }
}

void error()
{
    printf("Syntax error\n");
    exit(1);
}

int main()
{
    FILE *file = fopen("instructions.txt", "r");
    if (file == NULL)
    {
        printf("Failed to open file.\n");
        return 1;
    }
    parseInstructions(file);
    fclose(file);

    printf("Instructions:\n");
    for (int i = 0; i < instructionCount; i++)
    {
        printf("%d ", instructions[i].instruccion);
        if (instructions[i].numero1 != 0)
            printf("%d ", instructions[i].numero1);
        if (instructions[i].numero2 != 0)
            printf("%d ", instructions[i].numero2);
        if (strcmp(instructions[i].string1, "") != 0)
            printf("%s ", instructions[i].string1);
        if (strcmp(instructions[i].string2, "") != 0)
            printf("%s ", instructions[i].string2);
        printf("\n");
    }

    return 0;
}
