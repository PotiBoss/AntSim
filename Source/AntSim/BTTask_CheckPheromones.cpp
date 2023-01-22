// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckPheromones.h"

#include "AIControllerAnt.h"
#include "Ant.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UBTTask_CheckPheromones::UBTTask_CheckPheromones()
{
	NodeName = TEXT("Check for pheromones around ant");
}

EBTNodeResult::Type UBTTask_CheckPheromones::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIControllerAnt* AIController = Cast<AAIControllerAnt>(OwnerComp.GetAIOwner());
	AAnt* Ant = Cast<AAnt>(AIController->GetPawn());

	TArray<FHitResult> TraceArray;
	TArray<AActor*> ActorsToIgnore;

	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), Ant->GetActorLocation(), Ant->GetActorLocation(), 200.0f,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false, ActorsToIgnore, EDrawDebugTrace::None,
		TraceArray,true, FLinearColor::Green,FLinearColor::Blue, 1.0f);

	if(Hit)
	{
		TArray<APheromone*> Pheromones;
		
		for(FHitResult HitResult : TraceArray)
		{
			APheromone* Pheromone = Cast<APheromone>(HitResult.GetActor());
			if(Pheromone && Pheromone->PheromoneToSpawn == ToFood)
			{
				Pheromones.Add(Pheromone);
			}
		}
		APheromone* ChosenPheromone = Pheromones[FMath::RandRange(0, Pheromones.Num() - 1)];
		
		if(AIController && Ant->LastPheromone == nullptr)
		{
			AIController->GetBlackboardComponent()->SetValueAsObject("Pheromone", ChosenPheromone);
			FVector ForwardVector = ChosenPheromone->GetActorLocation() + ChosenPheromone->GetActorForwardVector() * 60;
			AIController->GetBlackboardComponent()->SetValueAsVector("PheromoneForwardVector", ForwardVector);
		}
		else
		{
			AIController->GetBlackboardComponent()->SetValueAsObject("Pheromone", ChosenPheromone);
			AIController->GetBlackboardComponent()->SetValueAsVector("PheromoneForwardVector", ChosenPheromone->LastPheromone->GetActorLocation());
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_CheckPheromones::GetStaticDescription() const
{
	return FString::Printf(TEXT("Task to check for pheromones around ant after returning food"));
}
