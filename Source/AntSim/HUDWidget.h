// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ColonyWidget.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class ANTSIM_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void PressedStartSimulation();

	UFUNCTION(BlueprintCallable)
	void PressedRestartSimulation();

	UFUNCTION(BlueprintCallable)
	void PressedCircle();

	UFUNCTION(BlueprintCallable)
	void PressedBox();

	UFUNCTION(BlueprintCallable)
	void PressedLabyrinth();

	UFUNCTION(BlueprintCallable)
	void SpeedUp();

	UFUNCTION(BlueprintCallable)
	void SpeedDown();

	UFUNCTION(BlueprintCallable)
	void CheckBestSource();

	UPROPERTY(EditAnywhere)
	class APC* PC;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class TSubclassOf<UColonyWidget> ColonyWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UColonyWidget* ColonyWidget;

	UPROPERTY()
	bool bSimulationStarted = false;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* StartSimulationButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* RestartSimulationButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* CircleMapButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* BoxMap;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* LabyrinthMap;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SpeedUpButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* SpeedDownButton;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* StartSimulationText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* RestartSimulationText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CircleText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* BoxText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LabyrinthText;

	
};
