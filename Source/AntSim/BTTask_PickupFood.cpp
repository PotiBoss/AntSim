// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PickupFood.h"

#include "AIController.h"
#include "Ant.h"
#include "Food.h"
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

	AFood* Food = Cast<AFood>(AIController->GetBlackboardComponent()->GetValueAsObject("FoodObject"));

	AIController->GetBlackboardComponent()->SetValueAsBool("HasFood", true);

	Food->AttachToComponent(Ant->FoodSocketComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTTask_PickupFood::GetStaticDescription() const
{
	return FString::Printf(TEXT("Hello"));
}
