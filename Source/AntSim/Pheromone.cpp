// Fill out your copyright notice in the Description page of Project Settings.


#include "Pheromone.h"

// Sets default values
APheromone::APheromone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APheromone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APheromone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

