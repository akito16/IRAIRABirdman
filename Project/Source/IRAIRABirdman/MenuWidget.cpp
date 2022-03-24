// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (ReturnGameBtn)
	{
		ReturnGameBtn->OnClicked.AddDynamic(this, &UMenuWidget::ReturnGame);
	}
	if (ReturnTitleBtn)
	{
		ReturnTitleBtn->OnClicked.AddDynamic(this, &UMenuWidget::ReturnTitle);
	}
	if (QuitGameBtn)
	{
		QuitGameBtn->OnClicked.AddDynamic(this, &UMenuWidget::QuitGame);
	}
}

void UMenuWidget::OpenUI()
{
	UWidgetBase::OpenUI();
}

void UMenuWidget::CloseUI()
{
	UWidgetBase::CloseUI();
}

void UMenuWidget::ReturnGame()
{
	CloseUI();
}

void UMenuWidget::ReturnTitle()
{
	UGameplayStatics::OpenLevel(this, "Title");
}

void UMenuWidget::QuitGame()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(Controller))
	{
		Controller->ConsoleCommand("quit");
	}
}