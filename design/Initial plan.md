# Plan of Attach

The program will be designed around the MVC pattern. It will have three distinct components: 
model, view, and controller, and additional subcomponents inside them.

## View
First, I will start with the view component. In this part, I will complete the view abstract model and the curses_view models. This part will heavily use the ncurses library, so the main problem will be integrating ncurses into my project. After finishing the classes, we will test simple test cases. For example, by correctly displaying the borders. I expect to finish the View component in one day.

## Model
The Model component is the biggest one of them all. I will complete this part of my project in four steps.

## Characters
First, I will start with single character, rectangular, and bitmap shapes in that order. After completing each of them, I will test them with the View class. Then I will implement the Characters class, test printing multiple objects simultaneously on the screen, and, most importantly, check for collisions. I expect to finish this part in less than a day. 

## Objects
Next, I will start implementing the Objects class first, without any movements. Again, testing with the view. Then, I will start working on the movement class. starting from stationary, then linear, then gravitating. I will implement the user input movement after completing the Controller part. After testing the simple movements, I will start adding some user-defined functions to the movement objects (e.g., a stationary object shoots every second). I expect to finish this part in about a day.

## Game
In this part, I will implement three classes: the abstract Model class, curse_game, and board_state. I will start with the Board_state and Model classes, as they are straightforward to implement and test. Note that the board_state class will use an iterator pattern. Then I will implement the curse_game model, which is kind of the engine of the whole project and links everything together. After implementing these classes, I will test them with previously implemented classes. At this point, I expect to be able to make some simple animations without collisions. I expect to finish this part in about a day.

## Collisions
The last part of the logic is about Collisions. I will complete the Collisions hierarchy and finish the whole Model component. I expect to spend more time on testing in this part, as this is the final part of the logic. After finishing this part, my program should be able to produce some cool animations. I expect to spend a few hours on this part. 

## Controller
Finally, I will implement the Controller component, which will handle the user input. I expect to finish the implementation and testing of this part in a few hours. Games and additional features This will be the most fun part of this project. I will create two games using the engine that demonstrate the main functionalities of the engine. There are a couple of ideas that I might implement as additional features: other controllers and views (e.g., file_view, mouse_controller), features for score management, saving high scores over games, and making my program RAII.
