#define _GNU_SOURCE

#include "./include/common.h"

#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define MICROSERVICES_NUM 4

struct stdin_settings {
    struct pollfd new;
    struct termios prev;
};

struct stdin_settings input_nb_init() {
    // Save original settings first
    struct stdin_settings settings = {};
    struct termios        orig;
    tcgetattr(0, &orig);

    struct pollfd  pfd = {.fd = 0, .events = POLLIN};
    struct termios tc;
    tcgetattr(0, &tc);
    tc.c_lflag &= ~(ICANON | ECHO);
    tc.c_cc[VMIN] = 0;
    tc.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &tc);

    settings.prev = orig;
    settings.new = pfd;
    return settings;
}

void input_restore(struct termios* orig) {
    // Restore original settings
    tcsetattr(0, TCSANOW, orig);
}

int main() {
    struct stdin_settings settings = input_nb_init();
    struct pollfd         pfd = settings.new;
    list_of_instructions();
    while (1) {
        int ret = poll(&pfd, 1, 1000); // Wait 1 second

        if (ret > 0 && (pfd.revents & POLLIN)) {
            char c;
            read(0, &c, 1);
            if (c == 'q') {
                break;
            } else if (c == 'h') {
                list_of_instructions();
            }
        }
    }
    input_restore(&settings.prev);
    return 0;
}

void list_of_instructions() {
    printf("q - stop all instances, exit server orchestrator\nr - run new instance\ns - stop existing instance\nl - list of all instances\nc - list of all running instances\nh - list of all instructions\n");
}