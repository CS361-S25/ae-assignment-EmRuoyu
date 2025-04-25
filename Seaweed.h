#ifndef SEAWEED_H
#define SEAWEED_H

#include "Org.h"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

/**
 * Seaweed (Prey species)
 * Grow each update, can not move
 * reproduces when energy meets 500 points
 */
class Seaweed : public Organism{

    public:
        Seaweed(emp::Ptr<emp::Random> _random, double _points=0.0) : 
            Organism(_random, _points) { SetSpeciesType(1);}

        //gain 150 points each update
        void Process() override {
            AddPoints(150);
            SetHasMoved(false);
        }

        //reproduce when energy meets 550 points
        emp::Ptr<Organism> CheckReproduction() override{
            int points = GetPoints();
            if (points > 550) {
                emp::Ptr<Seaweed> offspring = new Seaweed(*this);
                offspring->SetPoints(0);
                points -= 550;
                SetPoints(points);
                return offspring;
            }
            return nullptr;
        }
};

#endif