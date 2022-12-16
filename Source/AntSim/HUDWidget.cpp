// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

#include "Colony.h"
#include "PC.h"
#include "Kismet/GameplayStatics.h"

void UHUDWidget::PressedStartSimulation()
{
	if(PC && !bSimulationStarted)
	{
		bSimulationStarted = true;
		if(PC->Colony)
		{
			PC->Colony->StartSimulation();	
		}
	}
}

void UHUDWidget::PressedRestartSimulation()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void UHUDWidget::PressedCircle()
{
	UGameplayStatics::OpenLevel(this, FName("Circle"), false);
}

void UHUDWidget::PressedBox()
{
	UGameplayStatics::OpenLevel(this, FName("Gaps"), false);
}

void UHUDWidget::PressedLabyrinth()
{
	UGameplayStatics::OpenLevel(this, FName("Labirynth"), false);
}

