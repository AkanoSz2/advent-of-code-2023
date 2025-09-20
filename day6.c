#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *FILE_INPUT = "C:\\Users\\Sleepy Ako\\CLionProjects\\advent_2023\\input.txt";

void get_total_progress(const int time_values[100], const int distance_values[100], int *result) {
    for (int i = 0; i < 4 ; i ++) {
        int methods = 0;
        int distance = distance_values[i], time = time_values[i], score = 0;
        for (int acceleration = 1; acceleration < distance; acceleration++) {
            score = (time - acceleration) * acceleration;
            if (score > distance) methods++;
        }
        *result *= methods;
    }
}

void get_progress(const long long time, const long long distance, long long *result) {
    printf("Time: %lld, Distance: %lld\n", time, distance);
    long long methods = 0;

    // Don't use hardcoded values - calculate the proper range
    for (long long acceleration = 1; acceleration < time; acceleration++) {
        long long score = (time - acceleration) * acceleration;
        if (score > distance) {
            methods++;
        }
    }
    *result = methods; // Store the result in the long long pointer
}

int main(void) {
    char line[256];
    int time_values[100], distance_values[100];
    int time_count = 0, distance_count = 0;
    long long time = 0, distance = 0;
    long long result = 1; // Use long long for result

    FILE *file = fopen(FILE_INPUT, "r");
    if (!file) return 1;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        char *ptr = NULL;
        if (strncmp(line, "Time:", 5) == 0) {
            char temp[256] = "";
            ptr = line + 5;
            char *token = strtok(ptr, " ");
            while (token) {
                if (*token) {
                    strcat(temp, token);
                    time_values[time_count++] = atoi(token);
                }
                token = strtok(NULL, " ");
            }
            time = atoll(temp);
        }
        else if (strncmp(line, "Distance:", 9) == 0) {
            char temp[256] = "";
            ptr = line + 9;
            char *token = strtok(ptr, " ");
            while (token) {
                if (*token) {
                    strcat(temp, token);
                    distance_values[distance_count++] = atoi(token);
                }
                token = strtok(NULL, " ");
            }
            distance = atoll(temp);
        }
    }
    fclose(file);

    // For part 1 (comment this out for part 2)
    // int part1_result = 1;
    // get_total_progress(time_values, distance_values, &part1_result);
    // printf("Part 1: %d\n", part1_result);

    // For part 2
    get_progress(time, distance, &result);
    printf("Part 2: %lld\n", result);

    return 0;
}