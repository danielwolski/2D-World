# Zoo-Game
Consol game implemented in C++ based on OOP. 
Initially implemented as university project, here I am going to put a initial project files and refresh them by the time.
Initial project code is not normalized when it comes to names of functions and classses, also comments should be added.

Description of the simulator:

Implementation of a 2D virtual world simulator. The virtual
world has the structure of a two-dimensional NxN grid. In this world, simple life
forms exist, each with different behavior depending on its species. Every organism  occupies exactly one cell of the world's 2D grid array. Each cell can contain no more than a single organism at a time (in case of a collision, one of the organisms is
removed from this cell).
All action in the simulator are performed in turns. During each turn, every living
organism in the world performs an action appropriate to their kind. Some of them
move (animals), while others remain static (plants). In case of a collision (one of the
organisms enters a cell occupied by another organism) one of them wins, either by killing its
opponent (i.e. wolf) or by reflecting the opponent's attack (i.e. turtle). The order of all actions
during a single turn depends on the initiative of each living organism. The animals with the
highest initiative move first. In case of animals with the same initiative, the order is
determined by the animal's age (the oldest animal will move first). In case of a collision, the
victory depends on the strength of both organisms - the stronger organism wins (with some
exceptions, eg. turtle). In case of equal strength, the encounter is won by the attacker. The
game also includes a human player, who is a specific kind of animal. Unlike regular
animals, his movement is not random. Instead, the direction of the human's movement is
determined by the player by pressing the appropriate arrow key before the start of every
round. Human also possesses a special ability,
which can be activated with a separate key. Once activated, the ability works for 5 turns,
after which it is automatically deactivated. After deactivation, the ability cannot be activated
for the next 5 turns. The simulation startrs with several instances of every kind of
organism already placed in the game world. The program window includes a text box
for displaying messages about the results of fights between animals, consumption of plants
and other events occurring inside the simulated world.

--------------------------------------------------------------------------------------------

Animals:
-Human (Player)
-Wolf
-Fox
-Sheep
-Turtle
-Antelopa

Plants:
-Belladonna
-Sosnowskys Hogweed
-Grass
-Guarana
-SowThistle

