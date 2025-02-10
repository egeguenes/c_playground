#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

void die(char* msg) {
    perror(msg);
    exit(1);
}

typedef struct {
    char uuid[64];
    char param[256];
    int com;
} job_t;

void init_server(const char *socket_spec); // angenommen gegeben
job_t *get_job(void); // angenommen gegeben

void start_worker(job_t *job);
void collect_finished_workers(void);
void redirect_communication(job_t *job);
void free_job(job_t *job);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s SOCKET_SPEC\n", argv[0]);
        exit(1);
    }
    init_server(argv[1]);
    while(1) {
        job_t *job = get_job();
        if (!job) {
            die("get job failed");
        }
        start_worker();
        collect_finished_workers();
    }

    return 0;
}

void start_worker(job_t *job) {
    pid_t pid = fork();
    if (pid < 0) {
        die("fork failed!");
    } else if (pid == 0) {
        redirect_communication(job);
        execlp("gz", "gz", job->param, NULL);
        die("execlp failed");
    } else {
        printf("started %d with param %s.\n", pid, job->param);
        free_job(job);
    }
}

void collect_finished_workers(void) {
    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("%d beendet. Normal beendet %s\n", pid, WIFEXITED(status) ? "ja" : "nein");
    }
}

void redirect_communication(job_t *job) {
    int fd = open(job->uuid, O_WRONLY | O_CREAT | O_TRUNC, 0370);
    if (fd < 0) {
        die("open failed");
    }

    if (dup2(fd, STDOUT_FILENO) < 0) {
        die("dup2 failed");
    }
    close(fd);

    if (dp2(job->com, STDIN_FILENO) < 0) {
        die("dup2 failed");
    }
    close(job->com);
}

void free_job(job_t *job) {
    free(job);
}
