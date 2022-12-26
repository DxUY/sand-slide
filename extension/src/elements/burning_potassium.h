#ifndef BURNING_POTASSIUM_H
#define BURNING_POTASSIUM_H

#include "element.h"

class BurningPotassium: public Element {
public:
    const double DECAY = 1.0 / 512;
    const double PLASMA = 1 / 18.0;
    const double BURN = 1.0 / 48;
    const double POWDER = 1 / 1.025;
    const double WATER = 1 / 32.0;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < PLASMA && (sim->touch_count(row, col, 38) > 0 || sim->touch_count(row, col, 40) > 0)) {
            sim->grow(row + 1, col, 61, 38);
            sim->grow(row - 1, col, 61, 38);
            sim->grow(row, col - 1, 61, 38);
            sim->grow(row, col + 1, 61, 38);
            return;
        }

        if (sim->randf() >= POWDER) {
            return;
        }

        if (sim->randf() < DECAY && sim->touch_count(row, col, 0) > 0) {
            sim->set_cell(row, col, 6);
            return;
        }

        if (sim->randf() < BURN && sim->in_bounds(row - 1, col) && sim->get_cell(row - 1, col) == 0) {
            sim->grow(row - 1, col, 0, 5);
            return;
        }
        
        if (sim->randf() < WATER && sim->touch_count(row, col, 3) + sim->touch_count(row, col, 71) > 0) {
            for (int y = -3; y <= 3; y++) {
                for (int x = -3; x <= 3; x++) {
                    if (sim->in_bounds(row + y, col + x) ) {
                        sim->set_cell(row + y, col + x, 46);
                    }
                }
            }
        }
        sim->move_and_swap(row, col, row + 1, col);
    }

    double get_density() override {
        return 6.0;
    }

    double get_explode_resistance() override {
        return 0.6;
    }

    double get_acid_resistance() override {
        return 0.89;
    }
};

#endif // BURNING_POTASSIUM_H