// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckPheromones.h"

#include "AIControllerAnt.h"
#include "Ant.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_CheckPheromones::UBTTask_CheckPheromones()
{
	NodeName = TEXT("Check for pheromones around ant");
}

EBTNodeResult::Type UBTTask_CheckPheromones::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIControllerAnt* AIController = Cast<AAIControllerAnt>(OwnerComp.GetAIOwner());
	AAnt* Ant = Cast<AAnt>(AIController->GetPawn());

	for (auto Pheromone : Ant->Pheromones)
	{
		if(Pheromone->PheromoneToSpawn == ToFood && !Ant->bHasFood)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange,TEXT("czek"));
			if(AIController && Ant->LastPheromone == nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange,TEXT("null"));
				AIController->GetBlackboardComponent()->SetValueAsObject("Pheromone", Pheromone);
				FVector ForwardVector = Pheromone->GetActorLocation() + Pheromone->GetActorForwardVector() * 60;
				AIController->GetBlackboardComponent()->SetValueAsVector("PheromoneForwardVector", ForwardVector);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange,TEXT("notnull"));
				AIController->GetBlackboardComponent()->SetValueAsObject("Pheromone", Pheromone);
				AIController->GetBlackboardComponent()->SetValueAsVector("PheromoneForwardVector", Pheromone->LastPheromone->GetActorLocation());
			}
			break;
		}
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_CheckPheromones::GetStaticDescription() const
{
	return FString::Printf(TEXT("Task to check for pheromones around ant after returning food"));
}
