// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Colony.generated.h"

class UBoxComponent;
class AAnt;

UCLASS()
class ANTSIM_API AColony : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AColony();

	UPROPERTY(EditAnywhere, Category = "C++")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "C++")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, Category = "C++")
	TArray<TWeakObjectPtr<AAnt>> AntArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
