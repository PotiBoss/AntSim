// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_PickupFood.generated.h"

/**
 * 
 */
UCLASS()
class ANTSIM_API UBTTask_PickupFood : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_PickupFood();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;
};
