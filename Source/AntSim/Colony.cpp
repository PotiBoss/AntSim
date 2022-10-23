// Fill out your copyright notice in the Description page of Project Settings.


#include "Colony.h"

#include "AIControllerAnt.h"
#include "Ant.h"
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

// Called when the game starts or when spawned
void AColony::BeginPlay()
{
	Super::BeginPlay();

	for (auto Ant : AntArray)
	{
		Cast<AAIControllerAnt>(Ant->GetController())->GetBlackboardComponent()->SetValueAsVector("ColonyLocation", GetActorLocation());
	}
}

// Called every frame
void AColony::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

