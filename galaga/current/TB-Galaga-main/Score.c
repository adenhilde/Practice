#include <stdio.h>
#include <stdlib.h>

static int current_score = 0;  // Tracks the current score during the game
static int highest_score = 0;  // Tracks the highest score ever achieved

// Function to reset current score
void reset_score() {
    current_score = 0;
}

// Function to add points to the current score
void add_score(int points) {
    current_score += points;
}

// Function to check if the player has reached a high score
void check() {
    if (current_score > highest_score) {
        highest_score = current_score;
    }
}

// Function to get the current score
int get_score() {
    return current_score;
}

// Function to get the highest score
int get_highest_score() {
    return highest_score;
}

// Function to save the highest score to a file
void save_score() {
    FILE *file = fopen("highscore.txt", "w");
    fprintf(file, "%d\n", highest_score);  // Save the highest score
    fclose(file);
    
}

// Function to load the highest score from a file
void load_highest_score() {
    FILE *file = fopen("highscore.txt", "r");
    fscanf(file, "%d", &highest_score);  // Load the highest score
    fclose(file);
}
