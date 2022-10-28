// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerAnt.h"

#include "Colony.h"
#include "Food.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

AAIControllerAnt::AAIControllerAnt()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void AAIControllerAnt::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AIPerceptionComponent = FindComponentByClass<UAIPerceptionComponent>();

	if(Blackboard && BehaviorTree)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

void AAIControllerAnt::BeginPlay()
{
	Super::BeginPlay();

	if(BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}
}
void AAIControllerAnt::HandleSeenFood(AActor* Actor)
{
	if(Colony) { return; }
	
	if(Food)
	{
		Colony = Cast<AColony>(Actor);
		if(Colony)
		{
			Blackboard->SetValueAsVector("ColonyLocation", Colony->GetActorLocation());
			Blackboard->SetValueAsObject("Colony", Colony);
		}
		return;
	}
	
	Food = Cast<AFood>(Actor);

	if(Food)
	{
		Blackboard->SetValueAsVector("FoodLocation", Food->GetActorLocation());
		Blackboard->SetValueAsObject("FoodSource", Food);
	}
}