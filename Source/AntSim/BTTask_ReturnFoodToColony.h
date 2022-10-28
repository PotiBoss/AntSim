// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ReturnFoodToColony.generated.h"

/**
 * 
 */
UCLASS()
class ANTSIM_API UBTTask_ReturnFoodToColony : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTask_ReturnFoodToColony();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual FString GetStaticDescription() const override;
};
