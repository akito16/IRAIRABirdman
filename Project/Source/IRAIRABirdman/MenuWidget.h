// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBase.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class IRAIRABIRDMAN_API UMenuWidget : public UWidgetBase
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* ReturnGameBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* ReturnTitleBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UButton* QuitGameBtn;

	UFUNCTION()
		void ReturnGame();

	UFUNCTION()
		void ReturnTitle();

	UFUNCTION()
		void QuitGame();

public:
	virtual void OpenUI() override;

	virtual void CloseUI() override;
};
