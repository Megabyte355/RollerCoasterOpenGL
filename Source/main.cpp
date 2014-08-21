//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
//
// Copyright (c) 2014 Concordia University. All rights reserved.
//

// Contributors:
//      Razvan Alin Cijov
//      Gary Chang
//      Kevin Silva
//      Shahrad Rezaei
//      Dong Li
//      Oleksandr Dymov

#include "Renderer.h"
#include "World.h"
#include "EventManager.h"

int main(int argc, char*argv[])
{
	EventManager::Initialize();
	Renderer::Initialize();

	World world;

	if (argc > 1)
	{
		world.LoadScene(argv[1]);
	}
	else
	{
        // Main Focus: Tank model, Player Input
        //world.LoadScene("../Scenes/VehicleTest.scene");

        // Main Focus: Model importer, Missiles, Texturing, Camera Implementations
        world.LoadScene("../Scenes/AlienTest.scene");

        // Main Focus: Sun and Moon movement with light color changes
        //world.LoadScene("../Scenes/Sun.scene");
        
        // Main Focus: B-splines
        //world.LoadScene("../Scenes/BSplineTest.scene");
        
        // Main Focus: Ray Casting, Particle Emitters and Collision Boxes (don't shoot the floating triangle, it's just a test)
        //world.LoadScene("../Scenes/RayCastTest.scene");
        
        // Main Focus: State machine with state transitions
        //world.LoadScene("../Scenes/StateMachineTest.scene");
	}

	// Main Loop
	do
	{
		// Update Event Manager - Frame time / input / events processing 
		EventManager::Update();

		// Update World
		float dt = EventManager::GetFrameTime();
		world.Update(dt);

		// Draw World
		world.Draw();
	}
	while(EventManager::ExitRequested() == false);

	Renderer::Shutdown();
	EventManager::Shutdown();

	return 0;
}
