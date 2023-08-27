#include<stdio.h>
#include<string.h>
#include"quiz_utils.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fputs("Expected more arguments\n", stderr);
        fputs("Usage: quiz_taker quizname\n", stderr);
        return 1;
    }

    FILE *questions = fopen (argv[1], "r");

    if (questions == NULL) {
        fprintf(stderr, "Could not open file: %s\n", argv[1]);        
        return 2;
    } 

    const int LINE_MAX = 255;
    char question[LINE_MAX];
    char answer[LINE_MAX];
    char buffer[LINE_MAX];

    int num_questions = 0;
    int score = 0;

    // Get and print intro line
    fgets (buffer, LINE_MAX, questions);
    printf ("%s", buffer);

    while (fgets (question, LINE_MAX, questions) != NULL) {
        fgets (answer, LINE_MAX, questions);

        // Remove the trailing newlines from each
        question[strcspn (question, "\n")] = 0;
        answer[strcspn (answer, "\n")] = 0;
    
        num_questions++;

        printf ("%s: ", question);

        char input[LINE_MAX];
        fgets (input, LINE_MAX, stdin);
        // Remove trailing newline
        input[strcspn (answer, "\n")] = 0;

        if (!strcmp (input, answer)) {
	        puts ("Correct!");
	        score++;
	    } else {
	        printf ("Incorrect. The answer was: %s\n", answer);
	        printf ("You answered: %s\n", input);
	    }
    }

    fclose (questions);

    puts("Quiz completed!");
    printf ("Score: %d/%d (%0.0f%%)\n", score, num_questions,
	    ((float) score) / ((float) num_questions) * 100);

    return 0;
}
