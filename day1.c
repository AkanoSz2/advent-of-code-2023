 #include <ctype.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 // PART 1
 void line_tracker(char line[256], int *calibrate) {
     int first_digit = 10, first_index = 0, last_digit = 10, i;
     for (i = 0; i < strlen(line); i++) {
         if (isdigit(line[i])) {
             first_index = i;
             first_digit = line[i] - '0';
             break;
         }
     }
     for (i = strlen(line) - 1; i > first_index; i--) {
         if (isdigit(line[i])) {
             last_digit = line[i] - '0';
             break;
         }
     }
     // printf("%s %d %d\n", line, first_digit, last_digit);


     if (last_digit == 10) last_digit = first_digit;
     *calibrate += first_digit * 10 + last_digit;
 }

 // PART 2
 void line_convertor(char line[256], int *calibrate) {
     const char *numbers[] = {"zero","one","two","three","four","five","six","seven","eight","nine"};
     char fixed_line[256] = "";
     int len = strlen(line);
     for (int k = 0; k < len; k++) {
         for (int i = 0; i <= 9; i++) {
             int word_len = strlen(numbers[i]);
             if (k + word_len <= len && strncmp(&line[k], numbers[i], word_len) == 0) {
                 char digit[2] = { '0' + i, '\0' };
                 strcat(fixed_line, digit);
                 break;
             }
         }
         if (isdigit(line[k])) {
             char digit[2] = { line[k], '\0' };
             strcat(fixed_line, digit);
         }
     }
     line_tracker(fixed_line, calibrate);
 }

 int main(void) {
     char line[256];
     int calibrate = 0;
     FILE *file = fopen("C:\\Users\\Sleepy Ako\\CLionProjects\\aoc2023\\input.txt", "r");
     while (fgets(line, sizeof(line), file)) {
         line[strcspn(line, "\n")] = 0;
         line_convertor(line, &calibrate);
     }
     fclose(file);
     printf("%d", calibrate);
     return 0;
 }