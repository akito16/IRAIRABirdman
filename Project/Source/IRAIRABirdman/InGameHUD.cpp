// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameHUD.h"
#include "Blueprint/UserWidget.h"

AInGameHUD::AInGameHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> OperatingHUDObj(TEXT("/Game/Blueprints/UI/UI_OperatingMethod"));
	OperatingWidgetClass = OperatingHUDObj.Class;
}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(OperatingWidgetClass))
	{
		CurrentOperatingWidget = CreateWidget<UUserWidget>(GetWorld(), OperatingWidgetClass);
		if (IsValid(CurrentOperatingWidget))
		{
			CurrentOperatingWidget->AddToViewport();
		}
	}
}