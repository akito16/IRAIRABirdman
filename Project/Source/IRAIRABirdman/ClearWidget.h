// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "ClearWidget.generated.h"

/**
 * 
 */
UCLASS()
class IRAIRABIRDMAN_API UClearWidget : public UWidgetBase
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* NextStageBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* ReturnTitleBtn;

	UFUNCTION()
		void NextStage();

	UFUNCTION()
		void ReturnTitle();

	TArray<FString> StageName = {"Tutorial", "Stage1", "Stage2"};

public:
	virtual void OpenUI() override;

	virtual void CloseUI() override;
};
