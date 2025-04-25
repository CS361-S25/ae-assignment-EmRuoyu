# Artificial Ecologies

This program implements a artificial ecology made up by two species with Empirical library.

## Species and Interactions

- **Seaweed/Prey (green)**:

  - Grow each update, can not move
  - reproduces when energy meets 500 points

- **Fish/Predators (blue)**:
- lose points each update, can move
- gain points when eat seaweed
- reproduces when energy meets 500 points

## Simulation Dynamics

Predators move randomly each turn. Predators consumes prey they encounter(in the same grid). Prey gain energy in each update, regrow to sustain the population. Together the two species form a dynamic ecosystem. The simulation balances predator-prey interactions to ensure a prolonged coexistence.

# Acknowledge

In process of writing this assignment, I referenced class materials and Labs developed by Professor Anya Vostinar for CS361 Artificial Life and Digital Evolution(Spring 2025), and recieved help from Anya and Course staff Kai.
