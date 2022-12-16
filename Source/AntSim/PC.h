// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC.generated.h"

/**
 * 
 */
UCLASS()
class ANTSIM_API APC : public APlayerController
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;
		
	UFUNCTION(BlueprintCallable)
	void SwitchPheromoneVisibilty();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AColony* Colony;

	UPROPERTY(EditAnywhere, Category = "C++")
	TArray<class APheromone*> PheromoneArray;

	UPROPERTY()
	bool bArePheromonesVisible = false;

	UPROPERTY(EditAnywhere, Category = "C++")
	TSubclassOf<class UHUDWidget> HUDClass;

	UPROPERTY()
	UHUDWidget* HUDWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UFoodWidget* FoodWidget;
};
