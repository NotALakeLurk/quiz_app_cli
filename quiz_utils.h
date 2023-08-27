#ifndef QUIZ_UTILS_H_
#define QUIZ_UTILS_H_

const int LINE_MAX = 255;

int trim_newline(char string[]) {
    string[strcspn(string, "\n")] = 0;
    return 0;
}

#endif
