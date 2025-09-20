#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long long start;
    long long end;
} Interval;

typedef struct {
    long long destination;
    long long source;
    long long range;
} MapRule;

typedef struct {
    char name[30];
    MapRule rules[50];
    int rule_count;
} Map;

Map mapHash[10] = {{"", {0}, 0}};
Interval intervalsMap[100] = {{0, 0}};
long long SEEDS_MAP[100];
int seed_count = 0;

int compareIntervals(const void* a, const void* b) {
    Interval* intervalA = (Interval*)a;
    Interval* intervalB = (Interval*)b;
    return (intervalA->start > intervalB->start) - (intervalA->start < intervalB->start);
}

int compareRules(const void* a, const void* b) {
    MapRule* ruleA = (MapRule*)a;
    MapRule* ruleB = (MapRule*)b;
    return (ruleA->source > ruleB->source) - (ruleA->source < ruleB->source);
}

void populateInterval(long long SEEDS[100], int max_seeds) {
    int intervals_count = 0;
    for (int i = 0; i < max_seeds; i += 2) {
        Interval* my_interval = &intervalsMap[intervals_count++];
        my_interval->start = SEEDS[i];
        my_interval->end = SEEDS[i] + SEEDS[i + 1] - 1;
    }
    qsort(intervalsMap, intervals_count, sizeof(Interval), compareIntervals);
}

void populateMap(const char* map_type, int map_index, long long dest, long long src, long long rng) {
    Map* my_map = &mapHash[map_index];
    if (my_map->name[0] == '\0' || strcmp(my_map->name, map_type) != 0) {
        strncpy(my_map->name, map_type, sizeof(my_map->name)-1);
        my_map->name[sizeof(my_map->name)-1] = '\0';
        my_map->rule_count = 0;
    }
    MapRule* rule = &my_map->rules[my_map->rule_count++];
    rule->destination = dest;
    rule->source = src;
    rule->range = rng;
    qsort(my_map->rules, my_map->rule_count, sizeof(MapRule), compareRules);
}

int isValidSeed(long long seed) {
    int left = 0;
    int right = seed_count / 2 - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        Interval* interval = &intervalsMap[mid];

        if (seed >= interval->start && seed <= interval->end) {
            return 1;
        }
        if (seed < interval->start) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return 0;
}

int backtrackMap(Map* m, long long target, long long results[50]) {
    int count = 0;
    int mapped = 0;
    for (int i = 0; i < m->rule_count; i++) {
        MapRule* r = &m->rules[i];
        if (target >= r->destination && target < r->destination + r->range) {
            results[count++] = r->source + (target - r->destination);
            mapped = 1;
        }
    }
    if (!mapped) {
        results[count++] = target;
    }
    return count;
}

int backtrackAll(long long target, int map_index, long long current_path[], int depth) {
    current_path[depth] = target;
    if (map_index < 0) {
        if (isValidSeed(current_path[depth])) {
            return 1;
        }
        return 0;
    }
    long long results[50];
    int count = backtrackMap(&mapHash[map_index], target, results);
    for (int i = 0; i < count; i++) {
        if (backtrackAll(results[i], map_index - 1, current_path, depth + 1)) return 1;
    }
    return 0;
}

void find_lowest(const long long SEEDS_LIST[100], int max_seeds, long long *lowest_number) {
    for (int seed_index = 0; seed_index < max_seeds; seed_index++) {
        long long mapped_value = SEEDS_LIST[seed_index];
        for (int map_index = 0; map_index < 7; map_index++) {
            Map* current_map = &mapHash[map_index];
            int mapped = 0;
            int left = 0;
            int right = current_map->rule_count - 1;

            while (left <= right) {
                int mid = left + (right - left) / 2;
                MapRule* rule = &current_map->rules[mid];
                if (mapped_value >= rule->source && mapped_value < rule->source + rule->range) {
                    mapped_value = rule->destination + (mapped_value - rule->source);
                    mapped = 1;
                    break;
                }
                if (mapped_value < rule->source) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            if (!mapped) {
                mapped_value = mapped_value;
            }
        }
        if (*lowest_number == -1 || mapped_value < *lowest_number)
            *lowest_number = mapped_value;
    }
}

int main(void) {
    char line[256];
    int map_index = 0;
    const char *MAP_TYPES[] = {"soil", "fertilizer", "water", "light", "temperature", "humidity", "location"};
    char current_map[256] = {"TBA"};
    long long lowest_value = -1;
    FILE *file = fopen("C:\\Users\\Sleepy Ako\\CLionProjects\\advent_2023\\input.txt", "r");
    if (!file) {
        printf("Failed to open file.\n");
        return 1;
    }
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        if (strstr(line, "seeds:")) {
            char* ptr = strstr(line, "seeds:") + 6;
            while (*ptr) SEEDS_MAP[seed_count++] = strtoll(ptr, &ptr, 10);
        }
        if (line[0] == '\0') {
            strcpy(current_map, MAP_TYPES[map_index++]);
            continue;
        }
        long long dest, src, rng;
        if (sscanf(line, "%lld %lld %lld", &dest, &src, &rng) == 3) {
            populateMap(current_map, map_index - 1, dest, src, rng);
        }
    }
    fclose(file);
    populateInterval(SEEDS_MAP, seed_count);
    find_lowest(SEEDS_MAP, seed_count, &lowest_value);

    long long path[10];
    long long location = 0;
    while (1) {
        if (backtrackAll(location, 6, path, 0)) {
            printf("Lowest location with valid seed: %lld\n", location);
            break;
        }
        location++;
    }
    printf("\nCompilation Time: %s\n", __TIME__);
    return 0;
}