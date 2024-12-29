#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTIONS 5
#define MAX_OPTIONS 4

typedef struct {
    char question[256];
    char options[MAX_OPTIONS][128];
    int correctOption;
    int difficulty;
} Question;

void displayQuestion(Question q, int questionNumber) {
    printf("\nQuestion %d: %s\n", questionNumber, q.question);
    for (int i = 0; i < MAX_OPTIONS; i++) {
        printf("%d. %s\n", i + 1, q.options[i]);
    }
}

int askQuestion(Question q) {
    int answer;
    displayQuestion(q, 1);
    printf("Enter your answer (1-%d): ", MAX_OPTIONS);
    scanf("%d", &answer);
    return answer == q.correctOption;
}

void levelSelector(Question questions[], int count, int level, Question selectedQuestions[], int *selectedCount) {
    *selectedCount = 0;
    for (int i = 0; i < count; i++) {
        if (questions[i].difficulty == level) {
            selectedQuestions[(*selectedCount)++] = questions[i];
            if (*selectedCount == MAX_QUESTIONS) break;
        }
    }
}

void startQuiz(Question questions[], int questionCount, int timer) {
    int score = 0;
    for (int i = 0; i < questionCount; i++) {
        printf("\nYou have %d seconds to answer.\n", timer);
        clock_t start = clock();
        int correct = askQuestion(questions[i]);
        clock_t end = clock();
        double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;

        if (timeTaken > timer) {
            printf("Time's up! No points awarded for this question.\n");
        } else if (correct) {
            printf("Correct!\n");
            score++;
        } else {
            printf("Wrong answer.\n");
        }
        printf("Time taken: %.2f seconds\n", timeTaken);
    }

    printf("\nQuiz Over! You scored %d out of %d.\n", score, questionCount);
}

int main() {
    Question questions[] = {
        {"What is the capital of France?", {"Paris", "London", "Berlin", "Madrid"}, 1, 1},
        {"Which planet is known as the Red Planet?", {"Earth", "Mars", "Jupiter", "Venus"}, 2, 1},
        {"Who wrote 'To Kill a Mockingbird'?", {"Harper Lee", "Mark Twain", "Ernest Hemingway", "J.K. Rowling"}, 1, 2},
        {"What is the square root of 64?", {"6", "7", "8", "9"}, 3, 1},
        {"What is the chemical symbol for water?", {"H2O", "O2", "CO2", "NaCl"}, 1, 1}
    };

    int level;
    printf("Welcome to the Quiz Application!\n");
    printf("Select difficulty level (1: Easy, 2: Hard): ");
    scanf("%d", &level);

    Question selectedQuestions[MAX_QUESTIONS];
    int selectedCount;
    levelSelector(questions, sizeof(questions) / sizeof(questions[0]), level, selectedQuestions, &selectedCount);

    if (selectedCount == 0) {
        printf("No questions available for the selected difficulty level.\n");
    } else {
        int timer = (level == 1) ? 15 : 10; // Adjust timer based on difficulty level
        startQuiz(selectedQuestions, selectedCount, timer);
    }

    return 0;
}
