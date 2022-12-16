// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("StimuliSourceComponent");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	SetRootComponent(Mesh);

	TextRenderFoodAmount = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRendererFood"));
	TextRenderFoodAmount->SetupAttachment(Mesh);

	TextRenderPheromoneAmount = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRendererPheromone"));
	TextRenderPheromoneAmount->SetupAttachment(Mesh);

	FoodAmount = 11;
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

