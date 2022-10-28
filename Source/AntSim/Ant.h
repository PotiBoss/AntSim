// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pheromone.h"
#include "GameFramework/Character.h"
#include "Ant.generated.h"

UCLASS()
class ANTSIM_API AAnt : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAnt();

	// How much should an Ant prefer to follow trail instead of 
	UPROPERTY(EditAnywhere, Category = "C++", meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))
	float TrailFollowStrength = 0.0f;

	UPROPERTY(EditAnywhere, Category = "C++", meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))
	float NewTrailStrength = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class AFood* Food;

	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* FoodSocketComponent;

	UPROPERTY(EditAnywhere, Category = "C++")
	UParticleSystem* Particle;

	UFUNCTION()
	void SpawnPheromone();
	
	UPROPERTY(EditAnywhere, Category = "C++")
	TSubclassOf<APheromone> PheromoneClass;
;

	UPROPERTY(VisibleAnywhere)
	TArray<APheromone*> Pheromones;
	
	FTimerHandle PheromoneHandle;
	FTimerDelegate PheromoneDelegate;

	UPROPERTY()
	bool bHasFood = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
