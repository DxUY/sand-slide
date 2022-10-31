#ifndef GERMINATED_SEED_H
#define GERMINATED_SEED_H

#include "element.h"

class GerminatedSeed: public Element {
public:
    const double GROW = 1.0 / 1024;
    const double FLAME = 1.0 / 48;

    void process(SandSimulation *sim, int row, int col) override {
        // Catch on fire
        if (randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        }

        sim->move_and_swap(row, col, row + 1, col);

        // Turn into grass
        if (randf() < GROW && sim->touch_count(row, col, 11) > 0) {
            sim->set_cell(row, col, 14);
        }
    }

    double get_density() override {
        return 2.0;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
    }
};

#endif // GERMINATED_SEED_H