#ifndef ORG_H
#define ORG_H

#include "emp/math/Random.hpp"
#include "emp/tools/string_utils.hpp"

/* Organism base class */
class Organism {
    private:
        double points; // energy points
        int species; // species type marker
        bool has_moved = false; // check if organism has moved
        emp::Ptr<emp::Random> random; //random pointer

    public:
    Organism(emp::Ptr<emp::Random> _random, double _points=0.0) :
        points(_points), random(_random) {;}

    /* Handle interactions with a ceratin organism status*/ 
    void SetPoints(double _in) {points = _in;}
    void AddPoints(double _in) {points += _in;}
    int GetPoints() {return points;}
    int GetSpeciesType() {return species;}
    void SetSpeciesType(int s) { species = s; }
    void SetHasMoved(bool move) {has_moved = move;}
    bool GetHasMoved() {return has_moved;}

    /* Process organisms went through each update*/
    virtual void Process() {
        AddPoints(100);
    }
    
    /* Check for organism reproduce prep*/
    virtual emp::Ptr<Organism> CheckReproduction(){
            return nullptr;
    }
};
#endif