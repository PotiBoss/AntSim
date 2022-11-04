// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Pheromone.generated.h"


UENUM()
enum EPheromone
{
	ToHome,
	ToFood,
	NoFood
};

UCLASS()
class ANTSIM_API APheromone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APheromone();

	UPROPERTY(EditAnywhere, Category = "C++")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "C++")
	APheromone* LastPheromone;

	UPROPERTY(VisibleAnywhere, Category = "C++")
	FVector LastPheromoneLocation;

	UPROPERTY(VisibleAnywhere, Category = "C++")
	bool bLastInPath = false;
	
	UPROPERTY(VisibleAnywhere, Category = "C++")
	TEnumAsByte<EPheromone> PheromoneToSpawn = ToHome;

	UPROPERTY(EditAnywhere, Category = "C++")
	TArray<UParticleSystem*> Particles;

	UPROPERTY(EditAnywhere, Category = "C++")
	TArray<UNiagaraSystem*> NiagaraParticles;

	UPROPERTY(EditAnywhere, Category = "C++")
	float TimeToFadePheromone = 20.0f;

	UFUNCTION()
	void DestroyPheromone();

	UFUNCTION()
	void SpawnPheromone(bool bHasFood = false, bool bShouldRepel = false);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UPROPERTY()
	UNiagaraComponent* Emitter;

	FTimerHandle PheromoneDestroyHandle;
	FTimerDelegate PheromoneDestroyDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
