# Artificial Ecologies

This project implements a artificial ecology made up by two species, using the Empirical library.

## Species and Interactions

- **Seaweed/Prey (green)**:

  - Grow 150 points each update, can not move
  - reproduces when energy meets 550 points

- **Fish/Predators (blue)**:
- lose 70 points each update, can move
- gain all points of the seaweed it eats
- reproduces when energy meets 1000 points

## Simulation Dynamics

Predators move randomly each turn. Predators consumes prey they encounter(in the same grid). Prey gain energy in each update, regrow to sustain the population. Together the two species form a dynamic ecosystem. The simulation balances predator-prey interactions to ensure a prolonged coexistence.

# Acknowledge

In process of writing this assignment, I referenced class materials and Labs developed by Professor Anya Vostinar for CS361 Artificial Life and Digital Evolution(Spring 2025), and recieved help from Anya and Course staff Kai.
