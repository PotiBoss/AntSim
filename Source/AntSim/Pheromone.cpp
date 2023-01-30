// Fill out your copyright notice in the Description page of Project Settings.


#include "Pheromone.h"

#include "AIControllerAnt.h"
#include "Ant.h"
#include "Colony.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "PC.h"
#include "Components/TextBlock.h"
#include "Particles/ParticleSystemComponent.h"
#include "Tasks/AITask.h"

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
	APC* PC = Cast<APC>(GetWorld()->GetFirstPlayerController());
	PC->PheromoneArray.Remove(this);
	if(Emitter)
	{
		Emitter->DestroyComponent();
	}
	
	if(bLastInPath && FoodForLastInPath)
	{
		FoodForLastInPath->PheromoneAmount--;
	}

	if(bLastInPath && FoodForLastInPath && PC->FoodWidget && FoodForLastInPath == PC->FoodWidget->Food)
	{
		PC->FoodWidget->PheromonesText->SetText(FText::AsNumber(FoodForLastInPath->PheromoneAmount));
	}
	
	Destroy();
}

void APheromone::SpawnPheromone(bool bHasFood, bool bShouldRepel)
{
	if(bHasFood)
	{
		PheromoneToSpawn = ToFood;
		SphereComponent->ShapeColor = FColor::Yellow;
	}
	else if(bShouldRepel)
	{
		PheromoneToSpawn = NoFood;
		SphereComponent->ShapeColor = FColor::Green;
	}
	else
	{
		PheromoneToSpawn = ToHome;
		SphereComponent->ShapeColor = FColor::Magenta;
	}
	//Emitter = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraParticles[PheromoneToSpawn], GetActorLocation());
	
	//Emitter = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[PheromoneToSpawn], GetActorLocation());

	Cast<APC>(GetWorld()->GetFirstPlayerController())->PheromoneArray.Add(this);
	
	PheromoneDestroyDelegate.BindUFunction(this, "DestroyPheromone");
	GetWorld()->GetTimerManager().SetTimer(PheromoneDestroyHandle, PheromoneDestroyDelegate, TimeToFadePheromone, false);
}

void APheromone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	AAnt* Ant = Cast<AAnt>(OtherActor);
	if(Ant)
	{
		AAIControllerAnt* AIController = Cast<AAIControllerAnt>(Ant->GetController());
		if(!Ant->bHasFood && PheromoneToSpawn == ToFood)
		{
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
		if(!Ant->bHasFood && PheromoneToSpawn == NoFood)
		{
			AIController->GetBlackboardComponent()->ClearValue("NewLocation");
			AIController->GetBlackboardComponent()->ClearValue("FoodLocation");
			AIController->GetBlackboardComponent()->ClearValue("FoodObject");
			AIController->GetBlackboardComponent()->ClearValue("FoodSource");
			AIController->GetBlackboardComponent()->ClearValue("Pheromone");
			AIController->GetBlackboardComponent()->ClearValue("PheromoneForwardVector");

			AIController->GetBlackboardComponent()->SetValueAsVector("RepelNewLocation", FVector::Zero());
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
		
		//AAIControllerAnt* AIController = Cast<AAIControllerAnt>(Ant->GetController());
		if(bLastInPath)
		{

			TArray<FHitResult> TraceArray;
			TArray<AActor*> ActorsToIgnore;

			const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), Ant->GetActorLocation(), Ant->GetActorLocation(), 250.0f,
				UEngineTypes::ConvertToTraceType(ECC_Vehicle), false, ActorsToIgnore, EDrawDebugTrace::None,
				TraceArray,true, FLinearColor::Green,FLinearColor::Blue, 10.0f);

			if(Hit)
			{
				for (auto HitResult : TraceArray)
				{
					if(Cast<AFood>(HitResult.GetActor()))
					{
						//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, FString::Printf(TEXT("%s"), *HitResult.GetActor()->GetName()));
						return;
					}
				}
				Ant->SpawnPheromoneRepel();
			}
			/*
			if(!AIController->GetBlackboardComponent()->GetValueAsObject("FoodSource"))
			{
				Ant->SpawnPheromoneRepel();
			}*/
		}
	}


}


