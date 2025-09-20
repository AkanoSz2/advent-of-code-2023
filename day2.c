// #include <ctype.h>
// #include <stdio.h>
// #include <string.h>
//
// void rendercubes(char line[256], int *gameSum) {
//     int colorPower = 1;
//     int maxRed = 12, maxGreen = 13, maxBlue = 14;
//     int red = 0, green = 0, blue = 0, ID = 0, current_value = 0;
//     int max_red = 0, max_green = 0, max_blue = 0;
//     int i;
//
//     for (i = 5; i <= strlen(line); i++) {
//         if (isdigit(line[i])) {
//             current_value = current_value * 10 + (line[i] - '0');
//         } else {
//             if (line[i] == ':' || line[i] == ';') {
//                 ID = (line[i] == ':') ? current_value : ID;
//                 if (line[i] == ';') {
//                     if (red > max_red) max_red = red;
//                     if (green > max_green) max_green = green;
//                     if (blue > max_blue) max_blue = blue;
//                     red = green = blue = 0;
//                 }
//                 current_value = 0;
//             }
//             if (line[i] == 'r') {
//                 red += current_value;
//                 current_value = 0;
//             }
//             if (line[i] == 'g') {
//                 green += current_value;
//                 current_value = 0;
//             }
//             if (line[i] == 'b') {
//                 blue += current_value;
//                 current_value = 0;
//             }
//         }
//     }
//
//     if (red > max_red) max_red = red;
//     if (green > max_green) max_green = green;
//     if (blue > max_blue) max_blue = blue;
//
//     // PART 1
//     // if (max_red <= maxRed && max_green <= maxGreen && max_blue <= maxBlue) {
//     //     *gameSum += ID;
//     // }
//
//
//     // PART 2
//     printf("Game %d: Red %d, Blue %d, Green %d\n", ID, max_red, max_blue, max_green);
//
//     colorPower = max_blue * max_green * max_red;
//     printf("Power %d\n", colorPower);
//     *gameSum += colorPower;
// }
//
//
// int main(void) {
//     char line[256];
//     int gameSum = 0;
//     FILE *file = fopen("C:\\Users\\Sleepy Ako\\CLionProjects\\untitled6\\input.txt", "r");
//     if (file == NULL) {
//         printf("Error opening file!\n");
//         return 1;
//     }
//     while (fgets(line, sizeof(line), file)) {
//         rendercubes(line, &gameSum);
//     }
//     printf("%d", gameSum);
//     fclose(file);
//     return 0;
// }