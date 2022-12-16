// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodWidget.h"

#include "Food.h"
#include "PC.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UFoodWidget::Init()
{
	if(Food)
	{
		FoodName->SetText(Food->Name);
		FoodText->SetText(FText::AsNumber(Food->FoodAmount));
		PheromonesText->SetText(FText::AsNumber(Food->PheromoneAmount));
	}
}

void UFoodWidget::CloseButtonClicked()
{
	APC* PC = Cast<APC>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	PC->FoodWidget = nullptr;
	RemoveFromViewport();
	Destruct();
}
