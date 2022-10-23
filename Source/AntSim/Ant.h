// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Ant.generated.h"

UCLASS()
class ANTSIM_API AAnt : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAnt();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class AFood* Food;

	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* FoodSocketComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
