#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int instruccion;
    int numero1;
    int numero2;
    char string1[15];
    char string2[15];
} Instruction;

// Serialize the array of structs
void serializeInstructions(Instruction *instructions, int instructionCount, char *serializedData, int *serializedLength)
{
    int index = 0;
    for (int i = 0; i < instructionCount; i++)
    {
        memcpy(serializedData + index, &(instructions[i]), sizeof(Instruction));
        index += sizeof(Instruction);
    }
    *serializedLength = index;
}

// Deserialize the serialized data to the array of structs
void deserializeInstructions(char *serializedData, int serializedLength, Instruction *instructions, int *instructionCount)
{
    *instructionCount = serializedLength / sizeof(Instruction);
    memcpy(instructions, serializedData, serializedLength);
}

int main()
{
    // Sample data
    Instruction instructions[] = {
        {1, 10, 20, "Hello", "World"},
        {2, 30, 40, "Foo", "Bar"},
        {3, 50, 60, "Baz", "Qux"},
        {4, 60, 0, "Lets", "GO"}};
    int instructionCount = sizeof(instructions) / sizeof(Instruction);

    // Serialize the data
    char serializedData[1024];
    int serializedLength;
    serializeInstructions(instructions, instructionCount, serializedData, &serializedLength);

    // Print the serialized data
    printf("Serialized Data:\n");
    for (int i = 0; i < serializedLength; i++)
    {
        printf("%02X ", serializedData[i]);
    }
    printf("\n");

    // Deserialize the data
    Instruction deserializedInstructions[100];
    int deserializedInstructionCount;
    deserializeInstructions(serializedData, serializedLength, deserializedInstructions, &deserializedInstructionCount);

    // Print the deserialized data
    printf("\nDeserialized Instructions:\n");
    for (int i = 0; i < deserializedInstructionCount; i++)
    {
        printf("Instruction %d:\n", i + 1);
        printf("Instruccion: %d\n", deserializedInstructions[i].instruccion);
        printf("Numero1: %d\n", deserializedInstructions[i].numero1);
        printf("Numero2: %d\n", deserializedInstructions[i].numero2);
        printf("String1: %s\n", deserializedInstructions[i].string1);
        printf("String2: %s\n\n", deserializedInstructions[i].string2);
    }

    return 0;
}
