// #include <ctype.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
//
// typedef struct {
//     int row, col;
//     int numbers[2];
//     int count;
// } Gear;
//
// Gear* findGear(Gear *gears, int *gearCount, int row, int col) {
//     for (int i = 0; i < *gearCount; i++) {
//         if (gears[i].row == row && gears[i].col == col) {
//             return &gears[i];
//         }
//     }
//     gears[*gearCount].row = row;
//     gears[*gearCount].col = col;
//     gears[*gearCount].count = 0;
//     (*gearCount)++;
//     return &gears[*gearCount - 1];
// }
//
// void missingGear(char matrix[200][200], int rows, int columns, int *engineSum) {
//     *engineSum = 0;
//     Gear gears[10000];
//     int gearCount = 0;
//
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < columns; j++) {
//             if (isdigit(matrix[i][j])) {
//                 int num = 0;
//                 int start_j = j;
//                 int len = 0;
//                 while (j < columns && isdigit(matrix[i][j])) {
//                     num = num * 10 + (matrix[i][j] - '0');
//                     len++;
//                     j++;
//                 }
//                 // Check the perimeter of the number for '*' symbols
//                 for (int jj = start_j; jj < start_j + len; jj++) {
//                     for (int di = -1; di <= 1; di++) {
//                         for (int dj = -1; dj <= 1; dj++) {
//                             if (di == 0 && dj == 0) continue;
//                             int ni = i + di;
//                             int nj = jj + dj;
//                             if (ni >= 0 && ni < rows && nj >= 0 && nj < columns && matrix[ni][nj] == '*') {
//                                 Gear *gear = findGear(gears, &gearCount, ni, nj);
//                                 if (gear->count < 2) {
//                                     int already_added = 0;
//                                     for (int k = 0; k < gear->count; k++) {
//                                         if (gear->numbers[k] == num) {
//                                             already_added = 1;
//                                             break;
//                                         }
//                                     }
//                                     if (!already_added) {
//                                         gear->numbers[gear->count] = num;
//                                         gear->count++;
//                                     }
//                                 }
//                             }
//                         }
//                     }
//                 }
//                 j--;
//             }
//         }
//     }
//
//     for (int i = 0; i < gearCount; i++) {
//         if (gears[i].count == 2) {
//             *engineSum += gears[i].numbers[0] * gears[i].numbers[1];
//         }
//     }
// }
//
// int main(void) {
//     char line[256];
//     int engineSum = 0;
//     char matrix[200][200];
//     int rows = 0, columns = 0;
//
//     FILE *file = fopen("C:\\Users\\Sleepy Ako\\CLionProjects\\untitled6\\input.txt", "r");
//     if (file == NULL) {
//         printf("Error opening file!\n");
//         return 1;
//     }
//
//     while (fgets(line, sizeof(line), file)) {
//         int len = strlen(line);
//         if (line[len - 1] == '\n') {
//             line[len - 1] = '\0';
//             len--;
//         }
//         columns = len;
//
//         for (int i = 0; i < len; i++) {
//             matrix[rows][i] = line[i];
//         }
//         rows++;
//     }
//
//     fclose(file);
//
//     missingGear(matrix, rows, columns, &engineSum);
//
//     printf("Engine Sum: %d\n", engineSum);
//     return 0;
// }