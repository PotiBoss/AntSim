// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PickupFood.h"

#include "AIController.h"
#include "Ant.h"
#include "Food.h"
#include "FoodAnt.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_PickupFood::UBTTask_PickupFood()
{
	NodeName = TEXT("Pickup food for ants");

	//  Get only vector key
//	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(
//		UBTTask_FindRandomLocation, BlackboardKey));
}

EBTNodeResult::Type UBTTask_PickupFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	AAnt* Ant = Cast<AAnt>(AIController->GetPawn());

	

	AFood* Food = Cast<AFood>(AIController->GetBlackboardComponent()->GetValueAsObject("FoodSource"));

	if(!Food)
	{
		Ant->SpawnPheromoneRepel();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	Ant->SpawnPheromone(true);
	
	Food->FoodAmount--;
	
	FActorSpawnParameters SpawnParams;

	Ant->bHasFood = true;
	
	AFoodAnt* FoodAnt = GetWorld()->SpawnActor<AFoodAnt>(Food->FoodClass, Ant->GetActorLocation(), Ant->GetActorRotation(), SpawnParams);
	AIController->GetBlackboardComponent()->SetValueAsObject("FoodObject", FoodAnt);
	Ant->Food = FoodAnt;
	
	FoodAnt->AttachToComponent(Ant->FoodSocketComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	
	AIController->GetBlackboardComponent()->SetValueAsVector("PheromoneForwardVector", Ant->LastPheromone->GetActorLocation());
	//AIController->GetBlackboardComponent()->SetValueAsVector("PheromoneForwardVector", Ant->GetActorLocation() + Ant->GetActorForwardVector() * - 100);
	Ant->LastPheromone = nullptr;
	Ant->bSkipNext = true;

	if(Food->FoodAmount <= 0)
	{
		Food->Destroy();
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_PickupFood::GetStaticDescription() const
{
	return FString::Printf(TEXT("Task when ant picks up the food"));
}
