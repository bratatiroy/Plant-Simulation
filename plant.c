#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double water;
    double fert;
    double health;
    double growth_rate;
    double total_growth;
    int alive;
} Plant;

double calc_health(double water, double fert) {
    return 100 - fabs(60 - water) - fabs(40 - fert);
}

double calc_growth(double health) {
    if (health > 40)
        return (health - 40) / 12.0;
    return 0;
}

int check_alive(double water, double fert, double health) {
    if (health < 0) return 0;
    if (water < 10 || fert < 10) return 0;
    if (water > 65 || fert > 65) return 0;
    if (water >= 85 || fert >= 85) return 0;
    return 1;
}

void simulate_time(Plant *p, int seconds) {
    p->water -= 5.0 * seconds;
    p->fert -= (2.5 / 7200.0) * seconds;
    p->health = calc_health(p->water, p->fert);
    p->alive = check_alive(p->water, p->fert, p->health);
    p->growth_rate = calc_growth(p->health);

    if (p->alive) {
        double four_hr_blocks = (seconds / 3600.0) / 4.0;
        p->total_growth += p->growth_rate * four_hr_blocks;
    }
}

void add_button(Plant *p) {
    p->water += 20;
    p->fert  += 20;
    p->health = calc_health(p->water, p->fert);
    p->alive = check_alive(p->water, p->fert, p->health);
    p->growth_rate = calc_growth(p->health);
}

const char* water_status(double water) {
    if (water < 10) return "DEAD";
    if (water >= 85) return "DEAD";
    if (water > 65) return "TOO HIGH (DEAD)";
    if (water > 50) return "HIGH";
    if (water >= 20 && water <= 50) return "MEDIUM";
    if (water >= 10 && water < 20) return "LOW";
    return "UNKNOWN";
}

const char* fert_status(double fert) {
    if (fert < 10) return "DEAD";
    if (fert >= 85) return "DEAD";
    if (fert > 65) return "TOO HIGH (DEAD)";
    if (fert > 50) return "HIGH";
    if (fert >= 20 && fert <= 50) return "MEDIUM";
    if (fert >= 10 && fert < 20) return "LOW";
    return "UNKNOWN";
}

//
void display_status(Plant *p) {
    printf("\n🌱 ----- PLANT TABIYAAT ----- 🌱\n");
    printf("Water Level       : %.2f (%s)\n", p->water, water_status(p->water));
    printf("Fertilizer Level  : %.2f (%s)\n", p->fert, fert_status(p->fert));
    printf("Health            : %.2f\n", p->health);
    printf("Growth Rate (/4h) : %.2f\n", p->growth_rate);
    printf("Total Growth      : %.2f\n", p->total_growth);
    printf("Plant OBOSTA right now   : %s\n", p->alive ? "ALIVE" : "DEAD ❌");
    printf("-----------------------------\n");
}

int main() {
    Plant plant;

    plant.water = 60;
    plant.fert  = 40;
    plant.health = calc_health(plant.water, plant.fert);
    plant.alive = check_alive(plant.water, plant.fert, plant.health);
    plant.growth_rate = calc_growth(plant.health);
    plant.total_growth = 0;

    printf("🌿 Plant Growth Simulation 🌿\n");
    printf("Controls:\n");
    printf(" s -> Show status\n");
    printf(" t <seconds> -> Pass time (seconds)\n");
    printf(" a -> Add button (+20 Water & Fert)\n");
    printf(" q -> Quit\n");

    char cmd;
    while (1) {
        printf("\nEnter command: ");
        scanf(" %c", &cmd);

        if (cmd == 's') {
            display_status(&plant);
        }
        else if (cmd == 't') {
            int secs;
            scanf("%d", &secs);
            simulate_time(&plant, secs);
            display_status(&plant);
        }
        else if (cmd == 'a') {
            add_button(&plant);
            printf("✅ Added +20 Water & +20 Fertilizer!\n");
            display_status(&plant);
        }
        else if (cmd == 'q') {
            printf("🌸 Simulation Ended. Goodbye!\n");
            break;
        }
        else {
            printf("⚠️ Invalid command! Use s, t <seconds>, a, q.\n");
        }
    }
    return 0;
}
