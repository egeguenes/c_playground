/* TODO: includes */
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

/* TODO: global variables */
struct timeval start; // start moment
struct timeval total; // end moment
struct timeval round_start; // a new round started
struct timeval round_end; // a round ended
struct timeval fastest_lap_dur; // the fastest lap duration
int total_laps = 0;
int current_lap_num = 0;
int points = 0;
bool race_on = false;
bool lap_finished = false;
bool race_cancelled = false;
bool point_incremented = false;
const char* race_start_message = " race started\n";

/*
 * Fehlerbehandlung weggelassen bei:
 * 		- sigaction -> Fehler kann nur durch eigene Argumente verursacht werden.
 * 		- sigemptyset -> "
 * 		- gettimeofday -> " */

/* TODO: helpers, signal handlers */

bool check_digits(char *arg, int argc, int* output) {
    for (int i=0; i<argc; i++) {
        if (!isdigit(arg[i])) return false;
    }
    if (arg[0] == '0' && arg[1] == 'x') arg[0] = arg[2];
    *output = atoi(arg);
    return (*output > 0);
}

// round start, round end, best lap, round change, points

void sigint_action(int sig) {
    if (!race_on) {
        write(STDERR_FILENO, race_start_message, strlen(race_start_message));
        race_on = true;
        gettimeofday(&start, NULL);
        round_start = start;
    } else {
        gettimeofday(&round_end, NULL);
        lap_finished = true;
    }
}

void sigquit_action(int sig) {
    race_cancelled = true;
}

void sigusr1_action(int sig) {
    point_incremented = true;
}

void print_time(struct timeval *time) {
    fprintf(stderr, "%02ld:%02ld.%04ld", time->tv_sec / 60,
                                         time->tv_sec % 60,
                                         (long)time->tv_usec / 100);
}

void die(char* message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage %s [number of laps]\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (argv[1][0] == '0' && argv[1][1] == 'x') {
        argv[1] += 2;
    }
    if (!check_digits(argv[1], strlen(argv[1]), &total_laps)) {
        die("total number of laps should be an integer and more than 0!\n");
    }

    // start from zero, fastest is 0
    start.tv_sec = 0;
    start.tv_usec = 0;
    fastest_lap_dur.tv_sec = 0;
    fastest_lap_dur.tv_usec = 0;

    // creating signals and assigning the correct functions
    struct sigaction sigint, sigquit, sigusr1;
    memset(&sigint, 0, sizeof(sigint));
    memset(&sigquit, 0, sizeof(sigquit));
    memset(&sigusr1, 0, sizeof(sigusr1));
    sigint.sa_handler = sigint_action;
    sigquit.sa_handler = sigquit_action;
    sigusr1.sa_handler = sigusr1_action;
    sigaction(SIGINT, &sigint, NULL);
    sigaction(SIGQUIT, &sigquit, NULL);
    sigaction(SIGUSR1, &sigusr1, NULL);

    fprintf(stderr, "pid: %d\n", getpid());
    fprintf(stderr, "ready, press Ctrl+C to start...\n");

    while (1) {
        if (race_cancelled) {
            fprintf(stderr, "race cancelled\n");
            break;
        }

        if (lap_finished && !race_cancelled) {
            struct timeval current_lap_dur;
            timersub(&round_end, &round_start, &current_lap_dur);
            timeradd(&total, &current_lap_dur, &total);

            if (current_lap_num == 0 || timercmp(&current_lap_dur, &fastest_lap_dur, <)) {
                fastest_lap_dur = current_lap_dur;
            }

            fprintf(stderr, " lap %03d ", current_lap_num + 1);
            print_time(&current_lap_dur);
            fprintf(stderr, "\n");

            current_lap_num++;
            round_start = round_end;
            lap_finished = false;

            if (current_lap_num >= total_laps) {
                fprintf(stderr, "sum: ");
                print_time(&total);
                fprintf(stderr, "\n");

                fprintf(stderr, "fastest: ");
                print_time(&fastest_lap_dur);
                fprintf(stderr, "\n");

                fprintf(stderr, "points: %d\n", points);
                break;
            }
        }

        if (point_incremented) {
            points++;
            fprintf(stderr, "New point received! Total points: %d\n", points);
            point_incremented = false;
        }
    }

    return EXIT_SUCCESS;
}
