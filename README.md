# Amorfos Console

This is a console I made as a project for university. It has a joystick and 4 buttons as input and an LCD, a buzzer and 2 LEDs for output.

In this repo you can find a framework I made to make games for this console. Games are compiled using Arduino IDE. You can put the games on an SD card to be loaded at start.

The framework can be found in src/framework. It uses C++, but since the console isn't very powerful, it doesn't use classes. Instead it uses structs and functions, like in C.

Game examples and a template for starting a new project can be found in src/game.

## Amorfos Framework

### Requirements

You need this library for the LCD to work: https://github.com/olikraus/ucglib

### Usage

You have manual access to the buzzer and the 2 LEDs.

The functions are documented in the header files, so look there for more information. Below I will detail the general thought behind this framework.

The namespace amorfos contains functions to be used when coding your game. The namespace amorfos_internal is for functions only used by the framework.

The main file that runs the program is Amorfos-Console.ino. You shouldn't touch that, as that is what binds everything together with the hardware.

### Basic Setup

In src/game you can find template.cpp. This is the template for starting to code a new game.

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
        Vector2 position;   // the position of the object
        struct Entity **children;   // the children of the object
        unsigned int childCount;    // the number of children the object has
        struct Entity *parent;  // the parent of the object
        Vector3 color;  // the color of the object
        bool isVisible; // whether the object is visible or not
        bool hasCollision;  // whether the object has collision or not
        void *data; // a pointer to any data you want to attach to the object
    } Entity;

To create and destroy objects use the following functions from amorfos.h:
	
	Entity* createEntity(int type=0, Vector2 position=newVector2(0, 0), Vector3 color=newVector3(1, 1, 1), bool isVisible=true, bool hasCollision=false, void* data=NULL);
	void destroyEntity(Entity* entity);
	
These functions also take care of adding or removing the object from the scene. Using newEntity will only allocate an Entity and set default values, but will not add it to the scene.

Children of entities move at the same time as the parent entity.

### Input

Input can be read in 2 ways. Either from the input structure:

	typedef struct Input {
        float joystickX;
        float joystickY;
        bool buttonNorth;
        bool buttonWest;
        bool buttonSouth;
        bool buttonEast;
        bool buttonStart;
        bool buttonSelect;
        bool buttonJoystick;
    } Input;
	
Or the input callbacks:

    extern void onButtonPress(int button);
    extern void onButtonRelease(int button);
	
These functions are called whenever any button is pressed/released. The parameter represents the button that was activated. input.h defines some constants for the button ids.

You should only have 1 instance of each of those functions in the code of your game and treat different button presses with using a switch in those functions.

### Rendering

Rendering is done automatically for each entity. An entity uses it's color property for rendering. If an entity has isVisible=false it will not be rendered.

The only thing you can use from rendering.h is the function for switching the LEDs on and off.

### Audio

You have a buzzer available for audio that can play different notes for different durations.

### Physics

For the moment this only means collisions. A collision is triggered when 2 entities occupy the same pixel and if both of them have hasCollision=true.

	void amorfos::onCollision(amorfos::Entity* entity1, amorfos::Entity* entity2);
	
As with the input, there is 1 instance of this function in the game code. Use ifs to differentiate the different collision behaviours entities can have.

A good idea is to use the type parameter of an entity.
