// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FoodWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANTSIM_API UFoodWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	void Init();
	
	UFUNCTION(BlueprintCallable)
	void CloseButtonClicked();
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* FoodText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* PheromonesText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* FoodName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* CloseButton;

	UPROPERTY(BlueprintReadWrite)
	class AFood* Food;
};
