# Final Design

## Overview
The basic structure of my project is the same as was outlined in the initial plan of attack. The program is built around the MVC pattern. And it has three distinct components: Model, View, and Controller. On top of those, the program can be divided into other parts to help organize the whole project. The shape part is for creating new shapes. The movement part is for creating movements. Characters and objects are for combining shapes and movements. Collision is to handle different collisions.

This overall structure worked well for me, and I made little changes to the higher-level design of the program. For example, on a higher design level, utilizing the dependency inversion principle and implementing a solution like the observer pattern were super helpful. I have the move method in my object class, which has an identical purpose as the notify method. And my model part uses that to move all the objects, or “notify the observers.”.

However, there were many little difficulties that needed to be solved during the project. I will discuss those problems and the solutions I found for them.

Finally, I have implemented two games that use the game engine and its functionalities. The first game I implemented was inspired by the game Bad Ice Creams. The objective of the game is to collect all of the fruits. However, there are NPCs in the game as well, and if they touch you until you finish all of the fruits, you will lose. Additionally, you can produce an ice block in front of you or break any ice blocks in the game. This game demonstrates all of the shape cases, stationary movement, and player-controlled movement in combination. Also, collisions like destroying, colliding, and stopping.

The second game I implemented is a two-player shooter. Two players have a starship on opposite sides of the game, and they can shoot each other. If someone hits the other person, they win. This game demonstrates linear movement, player-controlled movement, stationary movement, and shooting a projectile during the game.

## Design
### Clone
My abstract classes Shape, Movement and Collision all have a pure virtual function called clone(). Several times during the project, I needed to copy a bitmap_shape or a collide_stop object having only a pointer or a reference to the abstract base class. Moreover, I couldn’t know the actual concrete class the pointer refers to (using a dynamic_cast approach was not a good solution). So I had to come up with the clone method. This method returns a unique_ptr to the base class but copies the actual concrete class from within the concrete class. So, using this method, I was able to copy only having access to a unique_ptr to the base class. (Clone was added to the new UML and was not in the initial one.)

### Iterator pattern
In my code, I’ve utilized the iterator pattern as well. More precisely implemented the iterator and const_iterator patterns in the board_state class. This made it more convenient to go through all the board states. It was especially used in the View component for producing an output from the given board_state.

### Collisions
I think the most challenging part of this project was handling the collisions. As there can be many scenarios, when implementing collisions between different objects, it is necessary to consider a lot of cases. Here is the breakdown of the collision’s logic in my program. First, the game programmer is going to provide a type for every object. Then they will provide collision objects between the two types. That is, if an object of type A collides with an object of type B, the provided collision object will be used. The next part of the logic is that when moving the objects in the game, I first try to move them and see what objects are going to collide. And then the engine first handles the collisions and then moves the other objects. The try_move method was added to the object class.

## Extra Features
### RAII
Throughout my project, I followed the resource acquisition is initialization principle. There are no delete and no new keywords in the project. All of the memory management is done through unique_ptr's and make_unique statements.
### Pause/quit
The games can be paused and then unpaused by the player in the middle of the game. This was done by adding a control object to the engine that had a player-controlled movement. For example, player-controlled movement can specify that when the ‘p’ key is pressed, the game::pause() method will be called. That method will throw an exception that will then be caught in the infinite running loop, and the loop will break. 

## Reflection
### What would I have done differently if you had the chance to start over? 
There are two major things that I would change if I had the chance to start over. The first thing is that the files in my project got messy, especially towards the end of the project. This was because I was doing everything in one single folder. I think it would have been better if I had started organizing the project files into different folders from the beginning.
Second, I ought to have anticipated and given myself more time to dedicate to the project and each of its parts.
