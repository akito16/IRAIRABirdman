// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleHUD.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.h"

ATitleHUD::ATitleHUD()
{
	static ConstructorHelpers::FClassFinder<UTitleWidget> TitleHUDObj(TEXT("/Game/Blueprints/UI/UI_Title"));
	TitleWidgetClass = TitleHUDObj.Class;
}

void ATitleHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(TitleWidgetClass))
	{
		CurrentTitleWidget = CreateWidget<UTitleWidget>(GetWorld(), TitleWidgetClass);
		if (IsValid(CurrentTitleWidget))
		{
			CurrentTitleWidget->OpenUI();
		}
	}
}