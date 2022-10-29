// Fill out your copyright notice in the Description page of Project Settings.


#include "Ant.h"

#include "Pheromone.h"
#include "Kismet/GameplayStatics.h"




// Sets default values
AAnt::AAnt()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FoodSocketComponent = CreateDefaultSubobject<USceneComponent>("FoodSocketComponent");

	FoodSocketComponent->SetupAttachment(GetMesh());
}



// Called when the game starts or when spawned
void AAnt::BeginPlay()
{
	Super::BeginPlay();

	PheromoneDelegate.BindUFunction(this, "SpawnPheromone", 1.0f, EPheromone::ToFood);
	GetWorld()->GetTimerManager().SetTimer(PheromoneHandle, PheromoneDelegate, 1.0f, true);
}

// Called every frame
void AAnt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAnt::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAnt::SpawnPheromone()
{
	APheromone* Pheromone = GetWorld()->SpawnActor<APheromone>(PheromoneClass, GetActorLocation() + GetActorForwardVector() * - 75, GetActorRotation());
	Pheromone->SpawnPheromone(bHasFood);
	if(LastPheromone != nullptr)
	{
		Pheromone->LastPheromone = LastPheromone;
	}
	LastPheromone = Pheromone;
}

