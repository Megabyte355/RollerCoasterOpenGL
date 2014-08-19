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
		//world.LoadScene("../Scenes/CoordinateSystem.scene");
		//world.LoadScene("../Scenes/VehicleTest.scene");
        //world.LoadScene("../Scenes/Sun.scene");
        //world.LoadScene("../Scenes/TankVehicle.scene");
        world.LoadScene("../Scenes/AlienTest.scene");
        //world.LoadScene("../Scenes/BSplineTest.scene");
        //world.LoadScene("../Scenes/RayCastTest.scene");
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
