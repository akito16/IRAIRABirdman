// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (TutorialBtn)
	{
		TutorialBtn->OnClicked.AddDynamic(this, &UTitleWidget::TutorialStart);
	}
	if (Stage1Btn)
	{
		Stage1Btn->OnClicked.AddDynamic(this, &UTitleWidget::Stage1Start);
	}
	if (Stage2Btn)
	{
		Stage2Btn->OnClicked.AddDynamic(this, &UTitleWidget::Stage2Start);
	}
	if (QuitGameBtn)
	{
		QuitGameBtn->OnClicked.AddDynamic(this, &UTitleWidget::QuitGame);
	}
}

void UTitleWidget::OpenUI()
{
	UWidgetBase::OpenUI();
}

void UTitleWidget::CloseUI()
{
	UWidgetBase::CloseUI();
}

void UTitleWidget::TutorialStart()
{
	CloseUI();
	UGameplayStatics::OpenLevel(this, "Tutorial");
}

void UTitleWidget::Stage1Start()
{
	CloseUI();
	UGameplayStatics::OpenLevel(this, "Stage1");
}

void UTitleWidget::Stage2Start()
{
	CloseUI();
	UGameplayStatics::OpenLevel(this, "Stage2");
}

void UTitleWidget::QuitGame()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (IsValid(Controller))
	{
		Controller->ConsoleCommand("quit");
	}
}