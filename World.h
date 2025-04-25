#ifndef ORGWORLD_H
#define ORGWORLD_H

#include "emp/Evolve/World.hpp"
#include "emp/math/random_utils.hpp"
#include "emp/math/Random.hpp"
#include "Org.h"
#include "Fish.h"
#include "Seaweed.h"

class OrgWorld : public emp::World<Organism> {
    emp::Random &random;
    emp::Ptr<emp::Random> random_ptr;

public:
    OrgWorld(emp::Random &_random) : emp::World<Organism>(_random), random(_random) {
        random_ptr.New(_random);
    }

    ~OrgWorld() {}

    // Initiate each updates
    void Update() {
        ResetMovementFlags();
        BehaviorPhases();
        ReproductionPhase();
        RegrowSeaweed();
    }

    // handles removing organisms from the world
    emp::Ptr<Organism> ExtractOrganism(int i) {
        emp::Ptr<Organism> org = pop[i];
        pop[i] = nullptr;
        return org;
    }

    // handles movement entry
    int moveOrg(int index) {
        emp::Ptr<Organism> org = ExtractOrganism(index);
        if (org->GetSpeciesType() == 2) {
            return ActiveMove(org, index);
        } else {
            return ReturnToOrigin(org, index);  // Seaweed doesn't move
        }
    }

    void checkDeath(int i) {
        emp::Ptr<Organism> org = pop[i];
        if (org->GetSpeciesType() == 2 && org->GetPoints() <= 0) {
            ExtractOrganism(i);
        }
    }

    void AttemptReproduce(int index) {
        emp::Ptr<Organism> child = pop[index]->CheckReproduction();
        if (!child) return;

        emp::WorldPosition target = GetRandomNeighborPos(index);
        int targetIndex = target.GetIndex();

        if (!IsOccupied(target)) {
            AddOrgAt(child, target);
        } else {
            HandleOccupiedReproduction(child, targetIndex, target);
        }
    }

private:
    // Seaweed doesn't move, just returns to its original position
    int ReturnToOrigin(emp::Ptr<Organism> org, int index) {
        AddOrgAt(org, index);
        return index;
    }

    // Fish moves to a random neighbor
    int ActiveMove(emp::Ptr<Organism> org, int origin) {
        emp::WorldPosition candidate = GetRandomNeighborPos(origin);
        int targetIndex = candidate.GetIndex();

        if (IsOccupied(candidate)) {
            return ResolveInteraction(org, targetIndex, origin);
        } else {
            AddOrgAt(org, candidate);
            return targetIndex;
        }
    }

    // Determines what happens when fish encounters another organism
    int ResolveInteraction(emp::Ptr<Organism> org, int targetIndex, int fallbackIndex) {
        emp::Ptr<Organism> neighbor = pop[targetIndex];
        if (neighbor->GetSpeciesType() == 1) {
            ConsumePoints(org, neighbor);
            ExtractOrganism(targetIndex);
            AddOrgAt(org, targetIndex);
            return targetIndex;
        } else {
            AddOrgAt(org, fallbackIndex);
            return fallbackIndex;
        }
    }

    void ConsumePoints(emp::Ptr<Organism> predator, emp::Ptr<Organism> prey) {
        predator->AddPoints(prey->GetPoints());
    }

    void HandleOccupiedReproduction(emp::Ptr<Organism> offspring, int targetIndex, emp::WorldPosition targetPos) {
        emp::Ptr<Organism> resident = pop[targetIndex];
        if (resident->GetSpeciesType() == 1) {
            ConsumePoints(offspring, resident);
            ExtractOrganism(targetIndex);
            AddOrgAt(offspring, targetPos);
        }
    }

    void ResetMovementFlags() {
        for (size_t i = 0; i < GetSize(); i++) {
            if (IsOccupied(i)) pop[i]->SetHasMoved(false);
        }
    }

    void BehaviorPhases() {
        emp::vector<size_t> order = emp::GetPermutation(random, GetSize());
        for (int i : order) {
            if (!IsOccupied(i)) continue;
            emp::Ptr<Organism> currentOrg = pop[i];
            if (currentOrg->GetHasMoved()) continue;

            currentOrg->Process();
            int newIndex = moveOrg(i);
            checkDeath(newIndex);
            currentOrg->SetHasMoved(true);
        }
    }

    void ReproductionPhase() {
        emp::vector<size_t> spawn_order = emp::GetPermutation(random, GetSize());
        for (int i : spawn_order) {
            if (IsOccupied(i)) AttemptReproduce(i);
        }
    }

    void RegrowSeaweed() {
        for (size_t i = 0; i < GetSize(); ++i) {
            if (!IsOccupied(i) && random.GetDouble() < 0.02) {
                AddOrgAt(new Seaweed(&random), i);
            }
        }
    }
};

#endif


