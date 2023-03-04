#ifndef FIREWORK_B_H
#define FIREWORK_B_H

#include "../element.h"

class FireworkB: public Element {
public:
    const double PROCESS = 1.0 / 1.05;
    const double HORIZONTAL = 1.0 / 2;
    const double TRAIL = 1.0 / 1.5;
    const double DECAY = 1.0 / 32;
    const double FRAG = 1.0 / 64;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < FRAG) {
            sim->set_cell(row, col, sim->randf() < 0.5 ? 66 : 68);
        }
        
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 0);
            return;
        }
        
        if (sim->randf() < TRAIL) {
            sim->grow(row + 1, col, 0, 69);
        }

        if (sim->randf() >= PROCESS) {
            return;
        }

        if (sim->randf() < HORIZONTAL) {
            sim->move_and_swap(row, col, row - 1, col + 1);
        } else {
            sim->move_and_swap(row, col, row - 1, col);
        }
    }

    double get_density() override {
        return 64.0;
    }

    double get_explode_resistance() override {
        return 0.85;
    }

    double get_acid_resistance() override {
        return 0.05;
    }

    int get_state() override {
        return 2;
    }
};

#endif // FIREWORK_B_H