// Fill out your copyright notice in the Description page of Project Settings.


#include "Pheromone.h"

#include "AIControllerAnt.h"
#include "Ant.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
APheromone::APheromone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	
}

// Called when the game starts or when spawned
void APheromone::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APheromone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APheromone::DestroyPheromone()
{
	if(Emitter)
	{
		Emitter->DestroyComponent();
	}
	Destroy();
}

void APheromone::SpawnPheromone(bool bHasFood)
{
	if(bHasFood)
	{
		PheromoneToSpawn = ToFood;
		SphereComponent->ShapeColor = FColor::Blue;
	}
	else
	{
		PheromoneToSpawn = ToHome;
		SphereComponent->ShapeColor = FColor::Red;
	}
	//Emitter = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraParticles[PheromoneToSpawn], GetActorLocation());
	
	//Emitter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[PheromoneToSpawn], GetActorLocation());
	

	PheromoneDestroyDelegate.BindUFunction(this, "DestroyPheromone");
	GetWorld()->GetTimerManager().SetTimer(PheromoneDestroyHandle, PheromoneDestroyDelegate, TimeToFadePheromone, false);
}

void APheromone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	AAnt* Ant = Cast<AAnt>(OtherActor);
	if(Ant)
	{
		if(!Ant->bHasFood && PheromoneToSpawn == ToFood)
		{
			AAIControllerAnt* AIController = Cast<AAIControllerAnt>(Ant->GetController());
		/*	if(AIController && LastPheromone == nullptr)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange,FString::Printf(TEXT("Has Food: %s"), *GetName()));
				UE_LOG(LogTemp, Error, TEXT("Has Food: %s"), *GetName());
				AIController->GetBlackboardComponent()->SetValueAsObject("Pheromone", this);
				FVector ForwardVector = GetActorLocation() + GetActorForwardVector() * 60;
				AIController->GetBlackboardComponent()->SetValueAsVector("PheromoneForwardVector", ForwardVector);
			}
			else*/
		//	{
				AIController->GetBlackboardComponent()->SetValueAsObject("Pheromone", this);
				AIController->GetBlackboardComponent()->SetValueAsVector("PheromoneForwardVector", LastPheromoneLocation);
		//	}
		}
		else if(Ant->bHasFood && PheromoneToSpawn == ToHome)
		{
			AAIControllerAnt* AIController = Cast<AAIControllerAnt>(Ant->GetController());
		/*	if(AIController && LastPheromone == nullptr)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange,FString::Printf(TEXT("No Food: %s"), *GetName()));
				UE_LOG(LogTemp, Error, TEXT("No Food: %s"), *GetName());
				AIController->GetBlackboardComponent()->SetValueAsObject("Pheromone", this);
				FVector ForwardVector = GetActorLocation() + GetActorForwardVector() * - 60;
				AIController->GetBlackboardComponent()->SetValueAsVector("PheromoneForwardVector", ForwardVector);
			}
			else
			{*/
				AIController->GetBlackboardComponent()->SetValueAsObject("Pheromone", this);
				AIController->GetBlackboardComponent()->SetValueAsVector("PheromoneForwardVector", LastPheromoneLocation);
			//}
		}
		Ant->Pheromones.Add(this);
	/*	
		float ChanceToExplore = FMath::RandRange(0.0f, 1.0f);
		if(ChanceToExplore >= Ant->TrailFollowStrength)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, TEXT("Explore"));
			return;
		}

		
		AAIControllerAnt* AIController = Cast<AAIControllerAnt>(Ant->GetController());

		
		float ChanceToPickOldTrail = FMath::RandRange(0.0f, 1.0f);
		if(ChanceToPickOldTrail >= Ant->NewTrailStrength && !Ant->Pheromones.IsEmpty() && AIController)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, TEXT("Old trail"));
			int RandomIndex = FMath::RandRange(0, Ant->Pheromones.Num() - 1);
			AIController->GetBlackboardComponent()->SetValueAsObject("Pheromone", Ant->Pheromones[RandomIndex]);
			FVector ForwardVector = GetActorLocation() + GetActorForwardVector() * 300;
			AIController->GetBlackboardComponent()->SetValueAsVector("PheromoneForwardVector", ForwardVector);
		}
		*/

	}
}

void APheromone::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	AAnt* Ant = Cast<AAnt>(OtherActor);
	if(Ant)
	{
		Ant->Pheromones.Remove(this);
	}
}


