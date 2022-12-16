// Fill out your copyright notice in the Description page of Project Settings.


#include "Ant.h"

#include "AIControllerAnt.h"
#include "PC.h"
#include "Pheromone.h"
#include "Components/TextBlock.h"
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


	SpawnPheromone();
	PheromoneDelegate.BindUFunction(this, "SpawnPheromone", 2.0f);
	GetWorld()->GetTimerManager().SetTimer(PheromoneHandle, PheromoneDelegate, 2.0f, true);
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

void AAnt::SpawnPheromone(bool bLastInPath)
{
/*	if(bSkipNext)
	{
		bSkipNext = false;
		return;
	}
*/
	
	if(!bHasFood)
	{
		APheromone* Pheromone = GetWorld()->SpawnActor<APheromone>(PheromoneClassToHome, GetActorLocation() + GetActorForwardVector() * - 75, GetActorRotation());
		Pheromone->SpawnPheromone(bHasFood);
		
		if(LastPheromone != nullptr)
		{
			Pheromone->LastPheromone = LastPheromone;
			Pheromone->LastPheromoneLocation = LastPheromone->GetActorLocation();
		}
		LastPheromone = Pheromone;

		if(bLastInPath)
		{
			Pheromone->bLastInPath = true;
			AAIControllerAnt* AntController = Cast<AAIControllerAnt>(GetController());
			AntController->Food->PheromoneAmount++;

			Pheromone->FoodForLastInPath = AntController->Food;

			APC* PC = Cast<APC>(UGameplayStatics::GetPlayerController(GetWorld(),0));
			if(PC->FoodWidget)
			{
				if(AntController->Food == PC->FoodWidget->Food)
				{
					PC->FoodWidget->PheromonesText->SetText(FText::AsNumber(AntController->Food->PheromoneAmount));
				}
			}
		}
	}
	else
	{
		APheromone* Pheromone = GetWorld()->SpawnActor<APheromone>(PheromoneClassToFood, GetActorLocation() + GetActorForwardVector() * - 75, GetActorRotation());
		Pheromone->SpawnPheromone(bHasFood);
		if(LastPheromone != nullptr)
		{
			Pheromone->LastPheromone = LastPheromone;
			Pheromone->LastPheromoneLocation = LastPheromone->GetActorLocation();
		}
		LastPheromone = Pheromone;
		
		if(bLastInPath)
		{
			Pheromone->bLastInPath = true;
		}
	}
}

void AAnt::SpawnPheromoneRepel()
{
	APheromone* Pheromone = GetWorld()->SpawnActor<APheromone>(PheromoneClassToRepel, GetActorLocation() + GetActorForwardVector() * - 75, GetActorRotation());
	Pheromone->SpawnPheromone(false, true);
	if(LastPheromone != nullptr)
	{
		Pheromone->LastPheromone = LastPheromone;
		Pheromone->LastPheromoneLocation = LastPheromone->GetActorLocation();
	}
	LastPheromone = Pheromone;
}

