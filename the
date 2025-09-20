#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>

#define CYCLE_REAL_SEC 1
#define PAGE_CLEAR_SEC 25
#define TARGET_GROWTH 200
#define HEALTH_THRESHOLD 40
#define DANGER_GROWTH 70  // danger threshold

float water = 60;
float fert  = 40;
int health  = 100;
int growth  = 0;
long cycle_count = 0;
time_t start_time;
time_t last_clear;


const char *danger_captions[] = {
    "WARNING! U NEGLECTING ME LIKE U NEGLECT UR GF TEXTS!",
    " CARE FOR ME, OR I'LL BRING UR EX!",
    "SAVE ME OR UR LOVE WILL GHOST U!",
    "OH NO UR RIZZ ISNT RIZZING ON ME & ON HER !"
};
int danger_count = sizeof(danger_captions)/sizeof(danger_captions[0]);

void set_nonblocking() {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

int kbhit() {
    char ch;
    int n = read(STDIN_FILENO, &ch, 1);
    if (n == 1) return ch; 
    return 0;
}

void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}

void update_health() {
    health = 100 - fabs(60 - water) - fabs(40 - fert);
    if (health < 0) health = 0;
}

void natural_usage() {
    water -= 0.5;
    fert  -= 0.25;
    if (water < 0) water = 0;
    if (fert < 0) fert = 0;
}

int update_growth() {
    int inc = 0;
    if (health > HEALTH_THRESHOLD) {
        inc = (health - HEALTH_THRESHOLD) / 10;
        if (inc < 1) inc = 1;
        growth += inc;
    }
    return inc;
}

void print_time() {
    time_t now = time(NULL);
    int elapsed = (int)(now - start_time);
    int m = elapsed / 60;
    int s = elapsed % 60;
    printf("Time: %02d:%02d | ", m, s);
}

void print_danger_caption() {
    int idx = rand() % danger_count;
    printf("%s\n", danger_captions[idx]);
}

int main() {
    int printed_lines = 0;
    set_nonblocking();
    start_time = time(NULL);
    last_clear = start_time;
    srand(time(NULL));

    clear_screen();
    printf(" PLANT BACHAOOO SIMULATION \n");
    printf(" GIVE A TOUCH OF CARE ON 'S' to WET ME !\n\n");

    while (1) {
        cycle_count++;

        natural_usage();
        update_health();
        update_growth();


        print_time();
        printf("Water: %6.1f | Fert: %6.1f | Health: %3d | Growth: %4d\n",
               water, fert, health, growth);
        printed_lines++;

        if (growth > DANGER_GROWTH && cycle_count % 2 == 0) {
            print_danger_caption();
            printed_lines++;
        }

        fflush(stdout);


        if ((time(NULL) - last_clear) >= PAGE_CLEAR_SEC) {
            clear_screen();
            printf("Plant Simulation Game (Press 'S' to SAVE the plant)\n\n");
            printed_lines = 0;
            last_clear = time(NULL);
        }

      
        if (growth > DANGER_GROWTH) {
            int key = kbhit();
            if (key == 'S' || key == 's') {
                printf("\n do u drink REDBULL as u killed me ! PLANT DIED!\n");
                break;
            }
        }

        int key = kbhit();
        if (key == 'S' || key == 's') {
            if (growth <= DANGER_GROWTH) {
                printf("\n NATURE will LOVE u moree ! btw Final Growth: %d\n", growth);
            }
            break;
        }

   
        if (water < 5 || fert < 5 || health <= 0) {
            printf("\n due to neglect! I DIED ITS OVER BETWEEN US GO AWAY.\n");
            break;
        }

      
        if (growth >= TARGET_GROWTH) {
            printf("\n I NEED U BUT NO YOURE BUSYYYY! Growth = %d\n", growth);
            break;
        }

        sleep(CYCLE_REAL_SEC);
    }

    return 0;
}
