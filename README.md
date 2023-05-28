# Amorfos Console

This is a console I made as a project for university. It has a joystick and 4 buttons as input and an LCD, a buzzer and 2 LEDs for output.

In this repo you can find a framework I made to make games for this console. Games are compiled using Arduino IDE. You can put the games on an SD card to be loaded at start.

The framework can be found in src/framework. It uses C++, but since the console isn't very powerful, it doesn't use classes. Instead it uses structs and functions, like in C.

Game examples and a template for starting a new project can be found in src/game.

## Amorfos Framework

### Requirements

You need this library for the LCD to work: https://github.com/olikraus/ucglib

### Usage

The functions are documented in the header files, so look there for more information. Below I will detail the general thought behind this framework.

The namespace amorfos contains functions to be used when coding your game. The namespace amorfos_internal is for functions only used by the framework.

The main file that runs the program is Amorfos-Console.ino. You shouldn't touch that, as that is what binds everything together with the hardware.

### Basic Setup

In src/game you can find template.cpp. This is the template for starting to code a new game. It contains the functions you need to implement.

### Game Flow

	/// @brief Called at the start of the game
    void start();

    /// @brief The main game loop. Delta time is the time since the last time the loop was called.
    /// @param deltaTime 
    void update(float deltaTime);
	
There are also callbacks for input and collision which are discused below.

### Entity

The framework is based on Entities. For short, an Entity is an object in a game that is described by a set of parameters. The framework uses entities to manage rendering, collision etc.

	typedef struct Entity {
        unsigned int type;  // a tag you can assign to the object to identify its type
        Vector2<int> position;   // the position of the object
        struct Entity **children;   // the children of the object
        unsigned int childCount;    // the number of children the object has
        struct Entity *parent;  // the parent of the object
        Vector3<int> color;  // the color of the object
        uint16_t graphics;  // the graphics of the object. Represented by a 3x3 matrix of pixels
        bool isVisible; // whether the object is visible or not
        bool hasCollision;  // whether the object has collision or not
        int8_t collisionRadius;   // radius of the collision centered on the object. Radius of 0 means only check for exact position match
        void *data; // a pointer to any data you want to attach to the object
        bool isDestroyed;   // DO NOT USE! whether the object is destroyed or not
    } Entity;

To create and destroy objects use the following functions from amorfos.h:
	
	Entity* createEntity(int type=0, Vector2 position=newVector2(0, 0), Vector3 color=newVector3(1, 1, 1), bool isVisible=true, bool hasCollision=false, void* data=NULL);
	void destroyEntity(Entity* entity);
	
These functions also take care of adding or removing the object from the scene. Using newEntity will only allocate an Entity and set default values, but will not add it to the scene.

You can parent an entity to another. Children of entities move at the same time as the parent entity.

DO NOT set isDestroyed in your code. This is used internally by the framework.

### Input

Input can be read in 2 ways. Either from the input structure:

	typedef struct Input {
        float joystickX;
        float joystickY;
        bool buttonNorth;
        bool buttonWest;
        bool buttonSouth;
        bool buttonEast;
        bool buttonJoystick;
    } Input;
	
Or the input callbacks:

    extern void onButtonPress(int button);
    extern void onButtonRelease(int button);
	
These functions are called whenever any button is pressed/released. The parameter represents the button that was activated. input.h defines some constants for the button ids.

You should only have 1 instance of each of those functions in the code of your game and treat different button presses with using a switch in those functions.

### Rendering

Rendering is done automatically for each entity. An entity uses it's color property for rendering. If an entity has isVisible=false it will not be rendered.

Each entity has a 3x3 matrix of pixels that can be used for rendering. Internally it is stored as a bit field for optimization. All pixels have the same color.

Example of a ship from space_defenders demo:

    uint16_t graphics[3][3] = {
        { 0, 1, 0 },              // _ # _
        { 1, 1, 1 },              // # # #
        { 0, 0, 0 }               // _ _ _
    };
    setGraphics(player, graphics);

There are also 2 LEDs that you can control.

### Audio

You have a buzzer available for audio that can play different notes for different durations.

### Physics

For the moment this only means collisions. A collision is triggered when 2 entities intersect and if both of them have hasCollision=true.

	void amorfos::onCollision(amorfos::Entity* entity1, amorfos::Entity* entity2);

Each entity has a collision radius. If the radius is 0, the collision is triggered only if the 2 entities have the same position. If the radius is greater than 0, the collision is triggered if the distance between the 2 entities is less than the sum of their radii.
	
As with the input, there is 1 instance of this function in the game code. Use ifs to differentiate the different collision behaviours entities can have.

A good idea is to use the type parameter of an entity.
