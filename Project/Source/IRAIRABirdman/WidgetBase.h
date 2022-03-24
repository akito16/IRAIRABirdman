// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class IRAIRABIRDMAN_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
		virtual void OpenUI();

	UFUNCTION()
		virtual void OpenUI_UIOnly();

	UFUNCTION()
		virtual void CloseUI();

	void SetUIOnly();
	void SetGameAndUI();
	void SetGameOnly();

};
