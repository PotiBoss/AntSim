// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ColonyWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANTSIM_API UColonyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class AFood* CurrentBestFoodSource;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 FoodSourceAmount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PheromoneAmount;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* FoodSourceName;
	
};
