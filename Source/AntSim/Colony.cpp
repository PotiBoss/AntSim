// Fill out your copyright notice in the Description page of Project Settings.


#include "Colony.h"

#include "AIControllerAnt.h"
#include "Ant.h"
#include "NavigationSystem.h"
#include "PC.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AColony::AColony()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));

	TriggerBox->SetupAttachment(Mesh);
}

void AColony::StartSimulation()
{
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	for(uint16 i = 0; i < AntsToSpawn; i++)
	{
		FActorSpawnParameters SpawnParams;
		
		FNavLocation NavLocation;
		
		NavSystem->GetRandomPointInNavigableRadius(GetActorLocation(), 180.0f, NavLocation);

		float RandomRotationYaw = FMath::RandRange(0, 360);

		FRotator SpawnRotation = FRotator(0.0f, RandomRotationYaw,0.0f);
		
		AntArray.Add(GetWorld()->SpawnActor<AAnt>(AntClass, NavLocation.Location, SpawnRotation, SpawnParams));
	}
}


// Called when the game starts or when spawned
void AColony::BeginPlay()
{
	Super::BeginPlay();

	//StartSimulation();
}

// Called every frame
void AColony::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

