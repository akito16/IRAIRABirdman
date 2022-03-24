// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TitleHUD.generated.h"

/**
 * 
 */
UCLASS()
class IRAIRABIRDMAN_API ATitleHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ATitleHUD();

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UTitleWidget> TitleWidgetClass;

	UPROPERTY(EditAnywhere)
		class UTitleWidget* CurrentTitleWidget;
};
