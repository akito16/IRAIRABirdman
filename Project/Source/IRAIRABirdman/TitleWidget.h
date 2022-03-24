// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "TitleWidget.generated.h"

/**
 * 
 */
UCLASS()
class IRAIRABIRDMAN_API UTitleWidget : public UWidgetBase
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* TutorialBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Stage1Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* Stage2Btn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* QuitGameBtn;

	UFUNCTION()
		void TutorialStart();

	UFUNCTION()
		void Stage1Start();

	UFUNCTION()
		void Stage2Start();

	UFUNCTION()
		void QuitGame();

public:
	virtual void OpenUI() override;

	virtual void CloseUI() override;
};
