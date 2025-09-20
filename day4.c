// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
//
// void read_card(char line[], int *matches, int *ID) {
//     char *bar = strchr(line, '|');
//     char *colon = strchr(line, ':');
//     *ID = 0;
//     for (int i = 5; i < colon - line; i++) {
//         if (line[i] >= '0' && line[i] <= '9') {
//             *ID = *ID * 10 + (line[i] - '0');
//         }
//     }
//
//     int win[50], own[50], win_count = 0, own_count = 0;
//     char *ptr = colon + 1;
//     while (ptr < bar) {
//         while (ptr < bar && (*ptr < '0' || *ptr > '9')) ptr++;
//         if (ptr >= bar) break;
//         win[win_count++] = atoi(ptr);
//         while (ptr < bar && *ptr >= '0' && *ptr <= '9') ptr++;
//     }
//
//     ptr = bar + 1;
//     while (*ptr) {
//         while (*ptr && (*ptr < '0' || *ptr > '9')) ptr++;
//         if (!*ptr) break;
//         own[own_count++] = atoi(ptr);
//         while (*ptr && *ptr >= '0' && *ptr <= '9') ptr++;
//     }
//
//     *matches = 0;
//     for (int i = 0; i < win_count; i++) {
//         for (int j = 0; j < own_count; j++) {
//             if (win[i] == own[j]) {
//                 (*matches)++;
//             }
//         }
//     }
// }
//
// void add_copies(int ID, int matches, int hashmap[], int max_cards, int copies) {
//     for (int i = 1; i <= matches && ID + i <= max_cards; i++) {
//         hashmap[ID + i - 1] += copies;
//     }
// }
//
// void print_cards(int hashmap[], int max_cards, int current_ID, int matches) {
//     for (int i = 1; i <= max_cards; i++) {
//         if (hashmap[i - 1] > 0) {
//             int added = (i == current_ID) ? matches : 0;
//             int next_ID = (i == current_ID && matches > 0) ? i + 1 : i;
//             // printf("card %d: %d pair, added %d cards to the id %d\n", i, hashmap[i - 1], added, next_ID);
//         }
//     }
// }
//
// int main(void) {
//     char line[256];
//     FILE *file = fopen("C:\\Users\\Sleepy Ako\\CLionProjects\\untitled6\\input.txt", "r");
//     if (file == NULL) {
//         printf("Cannot open file!\n");
//         return 1;
//     }
//
//     int max_cards = 0;
//     int matches_list[1000] = {0};
//     while (fgets(line, 256, file)) {
//         line[strlen(line) - 1] = 0;
//         int matches, ID;
//         read_card(line, &matches, &ID);
//         if (ID > max_cards) max_cards = ID;
//         matches_list[ID - 1] = matches;
//     }
//     rewind(file);
//
//     int *hashmap = (int *)calloc(max_cards, sizeof(int));
//     for (int i = 0; i < max_cards; i++) {
//         hashmap[i] = 1;
//     }
//
//     while (fgets(line, 256, file)) {
//         line[strlen(line) - 1] = 0;
//         int matches, ID;
//         read_card(line, &matches, &ID);
//         int copies = hashmap[ID - 1];
//         add_copies(ID, matches, hashmap, max_cards, copies);
//         printf("After card %d:\n", ID);
//         print_cards(hashmap, max_cards, ID, matches);
//     }
//
//     int total = 0;
//     for (int i = 0; i < max_cards; i++) {
//         total += hashmap[i];
//     }
//
//     fclose(file);
//     free(hashmap);
//     printf("Total cards: %d\n", total);
//     return 0;
// }