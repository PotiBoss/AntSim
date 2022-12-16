// Fill out your copyright notice in the Description page of Project Settings.


#include "PC.h"

#include "Colony.h"
#include "HUDWidget.h"
#include "Pheromone.h"
#include "Kismet/GameplayStatics.h"


void APC::BeginPlay()
{
	Super::BeginPlay();

	Colony = Cast<AColony>(UGameplayStatics::GetActorOfClass(GetWorld(), AColony::StaticClass()));

	if(HUDClass)
	{
		HUDWidget = Cast<UHUDWidget>(CreateWidget(this, HUDClass));
	}
	if(HUDWidget)
	{
		HUDWidget->AddToViewport();
		HUDWidget->PC = this;
		bShowMouseCursor = true;
	}
}

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
