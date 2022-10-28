// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ReturnFoodToColony.h"

#include "AIController.h"
#include "Ant.h"
#include "Colony.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ReturnFoodToColony::UBTTask_ReturnFoodToColony()
{
	NodeName = TEXT("Return food to colony");
}

EBTNodeResult::Type UBTTask_ReturnFoodToColony::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	AAnt* Ant = Cast<AAnt>(AIController->GetPawn());

	AColony* Colony= Cast<AColony>(AIController->GetBlackboardComponent()->GetValueAsObject("Colony"));

	if(Colony)
	{
		Colony->FoodAmount++;
		Ant->bHasFood = false;
		Ant->Food = nullptr;

		AIController->GetBlackboardComponent()->ClearValue("NewLocation");
		AIController->GetBlackboardComponent()->ClearValue("FoodLocation");
		AIController->GetBlackboardComponent()->ClearValue("FoodObject");
		AIController->GetBlackboardComponent()->ClearValue("FoodSource");
		AIController->GetBlackboardComponent()->ClearValue("Pheromone");
		AIController->GetBlackboardComponent()->ClearValue("PheromoneForwardVector");
		AIController->GetBlackboardComponent()->ClearValue("ColonyLocation");
		AIController->GetBlackboardComponent()->ClearValue("Colony");

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, TEXT("Cleared"));
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_ReturnFoodToColony::GetStaticDescription() const
{
	return FString::Printf(TEXT("Task to return food to the colony"));
}
