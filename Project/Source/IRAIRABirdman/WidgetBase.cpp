// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetBase.h"
#include "Kismet/GameplayStatics.h"

void UWidgetBase::OpenUI()
{
	AddToViewport();
	SetGameAndUI();
}

void UWidgetBase::OpenUI_UIOnly()
{
	AddToViewport();
	SetUIOnly();
}

void UWidgetBase::CloseUI()
{
	RemoveFromParent();
	SetGameOnly();
}

void UWidgetBase::SetUIOnly()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(Controller) == true)
	{
		Controller->SetInputMode(FInputModeUIOnly());
		Controller->bShowMouseCursor = true;
	}
}

void UWidgetBase::SetGameAndUI()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(Controller) == true)
	{
		Controller->SetInputMode(FInputModeGameAndUI());
		Controller->bShowMouseCursor = true;
		Controller->SetIgnoreMoveInput(true);
		Controller->SetIgnoreLookInput(true);
	}
}

void UWidgetBase::SetGameOnly()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(Controller) == true)
	{
		Controller->SetInputMode(FInputModeGameOnly());
		Controller->bShowMouseCursor = false;
		Controller->SetIgnoreMoveInput(false);
		Controller->SetIgnoreLookInput(false);
	}
}
