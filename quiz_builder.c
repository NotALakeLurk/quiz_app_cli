#include<stdio.h>
#include<string.h>
#include"quiz_utils.h"

int main(int argc, char *argv[]) {
    FILE *fp;
    char opentype[] = "w";
    int filename_specified;

    if (argc > 1) {
        if (argc > 2) {
            filename_specified = 1;

            if (!strcmp(argv[1], "-a")) {
                strcpy(opentype, "a");
            }
        } else {
            puts("Option not recognized, showing help.");
            puts("Usage:");
            puts("quiz_builder");
            puts("quiz_builder -a [quizname]");
            puts("quiz_builder -n [quizname]");
            puts("-a\tAppend to a previous quiz.");
            puts("-n\tPre-specify quizname");
        }
    }

    char filename[50];

    if (filename_specified) {
        strcpy(filename, argv[2]);
    } else {
        fputs("Please enter a filename for your quiz: ", stdout);
        fgets(filename, 50, stdin);
        trim_newline(filename);
    }

    fp = fopen(filename, opentype);

    // Buffer array for tmp values
    char buffer[LINE_MAX];

    // Quiz needs title line if not appending
    if (!strcmp(opentype, "w")) {
        fputs("Quiz title line: ", stdout);
        fgets(buffer, LINE_MAX, stdin);
        fputs(buffer, fp);
    }

    // Get and add questions
    for(;;) {
        // Get and add question
        fputs("Question (enter 'quit' to quit): ", stdout);
        fgets(buffer, LINE_MAX, stdin);
        // Quit without writing if desired
        if (!strcmp(buffer, "quit\n")) { break;}
        fputs(buffer, fp);

        // Get and add answer
        fputs("Answer: ", stdout);
        fgets(buffer, LINE_MAX, stdin);
        fputs(buffer, fp);
    }

    fclose(fp);
    // Point user to quiz
    printf("Quiz created: %s\n", filename);
}
