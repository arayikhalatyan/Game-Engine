# Game-Engine

In this project, I created a game engine that can help game developers program ASCII-art video games. The game engine is written in C++ and utilizes many OOP design principles. For example, on a higher design level, utilizing the dependency inversion principle and implementing a solution like the observer pattern were super helpful. There is a move method in the object class, which has an identical purpose as the notify method. And my Model part uses that to move all the objects, or “notify the observers.” Here is a brief explanation of the game engine's provided functionality.

Can create different types of shapes:
1. a single character
2. a rectangle
3. a bitmap, specified by a vector of (x, y, char) triples

Can add several kinds of movements to objects:
1. moving in a straight-line path
2. stationary, cycling through a sequence of shapes (eg blinking, rotating, etc.)
3. gravitating towards one of the borders of the screen 
4. player-controlled
5. ability to spawn other objects under circumstances the game developer specifies
6. combinations of the above may be possible

Define collisions between objects:
1. pass through each other.
2. collide and bounce off one another.
3. collide and stay
4. collide and stop
5. get damaged or destroyed.

On top of that, there are 2 sample games implemented using the game engine.
1. *"Good Ice Cream"* - This game was inspired by the game "Bad Ice Creams". The objective of the game is to collect all of the fruits. However, there are NPC(s) in the game as well, and if they touch you until you collect all of the fruits, you will lose. Additionally, you can create an ice block in front of you or break any ice blocks in the game. This game demonstrates all of the shape cases, stationary movement, and player-controlled movement in combination. Also, collisions like destroying, colliding, and stopping.

   ![image](https://github.com/arayikhalatyan/Game-Engine/assets/127004086/b416587e-de31-4c3d-a19e-045285c3fe80)

2. *"Starship Showdown"* - This game is a simple two-player shooter. Two players have a starship on the opposite sides of the game, and they can shoot each other. If someone hits the other person, they win. This game demonstrates linear movement, player-controlled movement, stationary movement, and shooting a projectile during the game.


![image](https://github.com/arayikhalatyan/Game-Engine/assets/127004086/2c484e8d-018b-4be2-9d06-9e2c67712100)

For more information on the design of the engine look at the design folder.
