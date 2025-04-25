#ifndef FISH_H
#define FISH_H

#include "Org.h"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"

/**
 * Fish (Predator species)
 * lose 70 points each update(metabolism), can move
 * gain all points of the seaweed it eats
 * reproduces when energy meets 1000 points
 */

class Fish : public Organism{
    private :
        int species = 2;
    public:
        Fish(emp::Ptr<emp::Random> _random, double _points=0.0) : 
            Organism(_random, _points) { SetSpeciesType(2);}

        //lose 70 points each update
        void Process() override {
            AddPoints(-70);
            SetHasMoved(false);
            
        }

         //reproduce when energy meets 1000 points
        emp::Ptr<Organism> CheckReproduction() override{
            int points = GetPoints();
            if (points > 1000) {
                emp::Ptr<Fish> offspring = new Fish(*this);
                offspring->SetPoints(400); //for initial saurvival
                points -= 1000;
                SetPoints(points);
                return offspring;
            }
            return nullptr;
        }
};

#endif