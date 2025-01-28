/* TODO: includes */
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

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

/*
 * Fehlerbehandlung weggelassen bei:
 * 		- sigaction -> Fehler kann nur durch eigene Argumente verursacht werden.
 * 		- sigemptyset -> "
 * 		- gettimeofday -> " */

/* TODO: helpers, signal handlers */

// round start, round end, best lap, round change, points

void sigint_action(int sig) {
    if (!race_on) {
        race_on = true;
        gettimeofday(&start, NULL); // start the global timer
        round_start = start; // a new round is started
        fprintf(stderr, " race started, press Ctrl+C for next round!\n");
    } else {
        gettimeofday(&round_end, NULL);
        struct timeval current_lap_dur;
        timersub(&round_end, &round_start, &current_lap_dur);
        timeradd(&total, &current_lap_dur, &total);

        // check the fastest lap
        if (current_lap_num == 0 || timercmp(&current_lap_dur, &fastest_lap_dur, <)) {
            fastest_lap_dur = current_lap_dur;
        }
        fprintf(stderr, " lap %03d %02ld:%02ld.%04ld\n", current_lap_num + 1,
                                                        current_lap_dur.tv_sec / 60,
                                                        current_lap_dur.tv_sec % 60,
                                                        (long)current_lap_dur.tv_usec / 100);
        current_lap_num++;
        round_start = round_end;
        if (current_lap_num >= total_laps) {
            // total time output
            fprintf(stderr, "sum: %02ld:%02ld.%04ld\n", total.tv_sec / 60,
                                                        total.tv_sec % 60,
                                                        (long)total.tv_usec / 100);
            // fastest lap output
            fprintf(stderr, "fastest: %02ld:%02ld.%04ld\n", fastest_lap_dur.tv_sec / 100,
                                                            fastest_lap_dur.tv_sec % 60,
                                                            (long)fastest_lap_dur.tv_usec / 100);

            fprintf(stderr, "points: %d\n", points);
            exit(EXIT_SUCCESS);
        }
    }
}

void sigquit_action(int sig) {
    fprintf(stderr, "race cancelled\n");
}

void sigusr1_action(int sig) {
    points++;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage %s [number of laps]\n", argv[0]);
        return EXIT_FAILURE;
    }
    total_laps = atoi(argv[1]);
    if (total_laps <= 0) {
        fprintf(stderr, "total number of laps should be more than 0, invalid number : %d", total_laps);
        return EXIT_FAILURE;
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
        sleep(1);
    }

    return EXIT_SUCCESS;
}
