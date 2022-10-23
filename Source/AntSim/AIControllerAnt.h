// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "AIControllerAnt.generated.h"

class AFood;
/**
 * 
 */
UCLASS()
class ANTSIM_API AAIControllerAnt : public AAIController
{
	GENERATED_BODY()
public:
	AAIControllerAnt();

	UFUNCTION(BlueprintCallable)
	void HandleSeenFood(AActor* Actor);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AFood* Food;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FBlackboardKeySelector FoodLocation;

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	UAIPerceptionComponent* AIPerceptionComponent;

	
};
