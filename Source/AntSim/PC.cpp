// Fill out your copyright notice in the Description page of Project Settings.


#include "PC.h"

#include "Colony.h"
#include "Pheromone.h"


void APC::SwitchPheromoneVisibilty()
{
	if(!bArePheromonesVisible)
	{
		bArePheromonesVisible = true;
		for (auto Pheromone : PheromoneArray)
		{
			Pheromone->SphereComponent->SetHiddenInGame(true);
		}
	}
	else
	{
		bArePheromonesVisible = false;
		for (auto Pheromone : PheromoneArray)
		{
			Pheromone->SphereComponent->SetHiddenInGame(false);
		}
	}
}
