// #include <ctype.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
//
// typedef struct {
//     long long destination;
//     long long source;
//     long long range;
// } MapRule;
//
// typedef struct {
//     char name[30];
//     MapRule rules[50];
//     int rule_count;
// } Map;
//
// Map mapHash[10] = {{"", {0}, 0}};
//
// void populateMap(const char* map_type, int map_index, long long dest, long long src, long long rng) {
//     Map* my_map = &mapHash[map_index];
//     if (my_map->name[0] == '\0' || strcmp(my_map->name, map_type) != 0) {
//         strncpy(my_map->name, map_type, sizeof(my_map->name)-1);
//         my_map->name[sizeof(my_map->name)-1] = '\0';
//         my_map->rule_count = 0;
//     }
//     MapRule* rule = &my_map->rules[my_map->rule_count++];
//     rule->destination = dest;
//     rule->source = src;
//     rule->range = rng;
// }
//
// void find_lowest(const long long SEEDS_LIST[100], int max_seeds, long long *lowest_number) {
//     for (int seed_index = 0; seed_index < max_seeds; seed_index++) {
//         long long mapped_value = SEEDS_LIST[seed_index];
//         for (int map_index = 0; map_index < 7; map_index++) {
//
//             Map* current_map = &mapHash[map_index];
//
//             for (int rule_index = 0; rule_index < current_map->rule_count; rule_index++) {
//
//                 MapRule* rule = &current_map->rules[rule_index];
//
//                 if (mapped_value >= rule->source && mapped_value < rule->source + rule->range) {
//                     mapped_value = rule->destination + mapped_value - rule->source;
//                     break;
//                 }
//             }
//         }
//         if (*lowest_number == 1 || mapped_value < *lowest_number)
//             *lowest_number = mapped_value;
//     }
// }
//
// int main(void) {
//     char line[256];
//     long long SEEDS_MAP[100];
//     int seed_count = 0;
//
//     int map_index = 0;
//     const char *MAP_TYPES[] = {"soil", "fertilizer", "water", "light", "temperature", "humidity", "location"};
//     char current_map[256] = {"TBA"};
//
//     long long lowest_value = 1;
//
//   FILE *file = fopen("C:\\Users\\Sleepy Ako\\CLionProjects\\advent_2023\\input.txt", "r");
//     if (!file) return 1;
//
//     while (fgets(line, sizeof(line), file)) {
//         line[strcspn(line, "\n")] = '\0';
//
//         if (strstr(line, "seeds:")) {
//             char* ptr = strstr(line, "seeds:") + 6;
//             while (*ptr) SEEDS_MAP[seed_count++] = strtoll(ptr, &ptr, 10);
//         }
//
//         if (line[0] == '\0') {
//             strcpy(current_map, MAP_TYPES[map_index++]);
//             continue;
//         }
//
//         long long dest, src, rng;
//         if (sscanf(line, "%lld %lld %lld", &dest, &src, &rng) == 3) {
//             populateMap(current_map, map_index - 1, dest, src, rng);
//         }
//     }
//
//     fclose(file);
//
//     find_lowest(SEEDS_MAP, seed_count, &lowest_value);
//     printf("LOWEST: %lld\n", lowest_value);
//
//     return 0;
// }
