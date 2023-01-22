// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

#include "Colony.h"
#include "PC.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UHUDWidget::PressedStartSimulation()
{
	if(PC && !bSimulationStarted)
	{
		bSimulationStarted = true;
		if(PC->Colony && ColonyWidgetClass)
		{
			PC->Colony->StartSimulation();
			ColonyWidget = Cast<UColonyWidget>(CreateWidget(this, ColonyWidgetClass));
			ColonyWidget->AddToViewport();

			ColonyWidget->CurrentBestFoodSource = Cast<AFood>(PC->Colony->FoodSourceArray[0]);
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

void UHUDWidget::SpeedUp()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), UGameplayStatics::GetGlobalTimeDilation(GetWorld()) * 2);
}

void UHUDWidget::SpeedDown()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), UGameplayStatics::GetGlobalTimeDilation(GetWorld()) / 2);
}

void UHUDWidget::CheckBestSource()
{
	if(PC->Colony)
	{
		for (auto Actor : PC->Colony->FoodSourceArray)
		{
			AFood* FoodSource = Cast<AFood>(Actor);

			if(FoodSource)
			{
				if(FoodSource->PheromoneAmount > ColonyWidget->FoodSourceAmount)
				{
					ColonyWidget->CurrentBestFoodSource->Mesh->SetMaterial(0, ColonyWidget->CurrentBestFoodSource->MaterialBase);
					ColonyWidget->FoodSourceAmount = FoodSource->PheromoneAmount;
					ColonyWidget->FoodSourceName->SetText(FText::FromString(*FoodSource->GetName()));
					ColonyWidget->CurrentBestFoodSource = FoodSource;
					ColonyWidget->CurrentBestFoodSource->Mesh->SetMaterial(0, ColonyWidget->CurrentBestFoodSource->MaterialBest);
				}
			}
		}
		
		if(ColonyWidget->CurrentBestFoodSource)
		{
			//GEngine->AddOnScreenDebugMessage(-1 ,3.0f, FColor::Orange, FString::Printf(TEXT("%d"),ColonyWidget->CurrentBestFoodSource->PheromoneAmount));
			ColonyWidget->PheromoneAmount->SetText(FText::AsNumber(ColonyWidget->CurrentBestFoodSource->PheromoneAmount));
		}
	}


	
}

