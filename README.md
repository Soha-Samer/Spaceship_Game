Developed a 2D arcade-style game using C++ in Visual Studio, where the player controls a spaceship navigating through space while avoiding or destroying asteroids. The project involved creating an engaging gameplay experience with smooth controls, collision detection, and dynamic graphics.
Key Features:

    Spaceship Control:
        Functionality: Players can control the spaceship using keyboard inputs to move up, down, left, and right.
        Implementation: Used event handling to capture and respond to player inputs.

    Asteroid Generation:
        Functionality: Randomly generates asteroids that move towards the spaceship, increasing in number and speed over time.
        Implementation: Created functions to spawn asteroids at random positions and move them across the screen.

    Collision Detection:
        Functionality: Detects collisions between the spaceship and asteroids, resulting in game-over conditions.
        Implementation: Implemented bounding box collision detection to check for overlaps between the spaceship and asteroids.

    Shooting Mechanism:
        Functionality: Allows the spaceship to shoot projectiles to destroy incoming asteroids.
        Implementation: Developed a shooting system with projectiles moving in the direction fired and checking for collisions with asteroids.

    Score Tracking:
        Functionality: Tracks and displays the player's score based on the number of asteroids destroyed and time survived.
        Implementation: Updated the score dynamically and displayed it on the screen using text rendering.

    Graphics and Animation:
        Functionality: Utilizes 2D sprites for the spaceship, asteroids, and projectiles, with animations for movement and explosions.
        Implementation: Loaded and managed sprites using a graphics library, and created animations for various game events.

Technical Specifications:

    Programming Language: C++
    Development Environment: Visual Studio
    Graphics Library: Used a library like SDL (Simple DirectMedia Layer) for rendering graphics and handling input.
    Game Loop: Implemented the main game loop to handle game state updates, rendering, and event processing.

Source Files Structure:

    Main.cpp:
        Entry point of the game.
        Initializes the game window, loads resources, and starts the game loop.

    Spaceship.cpp and Spaceship.h:
        Defines the Spaceship class, including properties for position, speed, and health.
        Implements methods for movement, shooting, and collision detection.

    Asteroid.cpp and Asteroid.h:
        Defines the Asteroid class, including properties for position and speed.
        Implements methods for random generation, movement, and collision detection.

    Projectile.cpp and Projectile.h:
        Defines the Projectile class, including properties for position and speed.
        Implements methods for movement and collision detection with asteroids.

    Game.cpp and Game.h:
        Manages the overall game state, including the game loop, score tracking, and rendering.
        Implements methods for updating game objects, checking collisions, and handling game-over conditions.

    Graphics.cpp and Graphics.h:
        Handles the loading and rendering of sprites and text.
        Implements methods for drawing the spaceship, asteroids, projectiles, and UI elements.

    Utils.cpp and Utils.h:
        Utility functions for random number generation, collision detection logic, and other helper methods.

Contributions:

    Game Design:
        Conceptualized the game mechanics and user experience.
        Designed the spaceship control system, shooting mechanics, and asteroid behavior.

    Implementation:
        Developed core gameplay functionalities, including player controls, asteroid spawning, and projectile shooting.
        Implemented collision detection logic to handle interactions between game objects.
        Integrated a scoring system and graphical UI elements to enhance gameplay feedback.

    Graphics and Animation:
        Loaded and managed 2D sprites for various game elements.
        Created animations for spaceship movement, projectile firing, and asteroid explosions.

    Testing and Debugging:
        Conducted extensive testing to ensure smooth gameplay and responsiveness.
        Debugged issues related to collision detection, game loop performance, and graphical rendering.

Skills Demonstrated:

    C++ Programming: Demonstrated proficiency in C++ with a focus on object-oriented programming, memory management, and efficient code design.
    Game Development: Showcased ability to develop a complete game, from conceptualization to implementation and testing.
    Graphics Programming: Gained experience with 2D graphics rendering, sprite management, and animation using a graphics library.
    Problem-Solving: Applied logical thinking to overcome challenges related to game mechanics, collision detection, and performance optimization.
