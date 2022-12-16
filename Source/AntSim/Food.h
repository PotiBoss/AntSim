// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoodWidget.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "Food.generated.h"

class UAIPerceptionStimuliSourceComponent;

UCLASS()
class ANTSIM_API AFood : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFood();

	UPROPERTY(EditAnywhere, Category = "C++")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++")
	UAIPerceptionStimuliSourceComponent* StimuliSourceComponent;

	UPROPERTY(EditAnywhere, Category = "C++")
	TSubclassOf<class AFoodAnt> FoodClass;

	UPROPERTY(EditAnywhere, Category = "C++")
	UTextRenderComponent* TextRenderFoodAmount;

	UPROPERTY(EditAnywhere, Category = "C++")
	UTextRenderComponent* TextRenderPheromoneAmount;

	UPROPERTY(EditAnywhere, Category = "C++")
	uint8 FoodAmount;
	
	UPROPERTY(EditAnywhere, Category = "C++")
	uint8 PheromoneAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "C++")
	FText Name;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
