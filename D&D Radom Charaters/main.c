#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//define constants
#define NUM_WEAPONS 5
#define NUM_ABILITIES 4
#define MAX_CHARACTERS 5


//struct for the characters
typedef struct {
    char* name;
    char* ability;
    int gold;
} Character;

Character generateRandomCharacter() {
    const char* weapons[NUM_WEAPONS] = {"Sword", "Axe", "Bow", "Dagger", "Mace"};
    const char* abilities[NUM_ABILITIES] = {"Fire", "Ice", "Lighting", "Poison"};

    //srand(time(NULL));

    Character c;
    c.name = (char*)weapons[rand() % NUM_WEAPONS];
    c.ability = (char*)abilities[rand() % NUM_ABILITIES];
    c.gold = (rand() % 100) + 1;
    return c;
}

void viewCharacters(Character characters[], int count) {
    if(count == 0) {
        printf("No characters to display\n");
    } else {
        for(int i = 0; i < count; i++) {
            printf("%d. %s with %s ability and %d gold coins\n", i + 1, characters[i].name, characters[i].ability, characters[i].gold);
        }
    }
}

void deleteCharacter(Character characters[], int* count, int index) {
    if (index < 0 || index >= *count) {
        printf("Invalid character index\n");
    }
    // Shift the characters count to remove the one at the index
    for (int i = index; i < *count - 1; i++) {
        characters[i] = characters[i + 1];
    }
    (*count)--; // decreases the character count
    printf("Character deleted successfully");
}

int main(void) {
    srand(time(NULL));

    Character characters[MAX_CHARACTERS];
    int characterCount = 0;

    int choice;
    do {
        printf("\n1. Generate Charaters\n");
        printf("2. View Characters\n");
        printf("3. Delete Characters\n");
        printf("Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Generate 5 charaters
                if (characterCount == 0) {
                    for(int i = 0; i < MAX_CHARACTERS; i++) {
                        characters[i] = generateRandomCharacter();
                    }
                    characterCount = MAX_CHARACTERS;
                    printf("Generated 5 characters.\n");
                } else {
                    printf("Characters have already been generated");
                }
                break;

            case 2:
                //View charaters
                viewCharacters(characters, characterCount);
                break;

            case 3:
                if (characterCount == 0) {
                    printf("No characters to delete\n");
                } else {
                    int index;
                    printf("Enter the number of the character to delete");
                    scanf("%d", &index);
                    // -1 to convert to zero-indexed
                    deleteCharacter(characters, &characters, index);
                }
                break;

            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again\n");
        }

    } while (choice != 4);

    return 0;
}
