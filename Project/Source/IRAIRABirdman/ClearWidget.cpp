// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "BirdmanCharacter.h"

void UClearWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NextStageBtn)
	{
		NextStageBtn->OnClicked.AddDynamic(this, &UClearWidget::NextStage);
	}
	if (ReturnTitleBtn)
	{
		ReturnTitleBtn->OnClicked.AddDynamic(this, &UClearWidget::ReturnTitle);
	}
}

void UClearWidget::OpenUI()
{
	UWidgetBase::OpenUI();
}

void UClearWidget::CloseUI()
{
	UWidgetBase::CloseUI();
}

void UClearWidget::NextStage()
{
	int index = 0;
	UWorld* World = GetWorld();
	FString NowMap = UGameplayStatics::GetCurrentLevelName(World, true);
	if (StageName.Find(NowMap, index))
	{
		if (index != StageName.Num() - 1)
		{
			CloseUI();
			UGameplayStatics::OpenLevel(this, FName(StageName[index + 1]));
		}
		else
		{
			UGameplayStatics::OpenLevel(this, "Title");
		}
	}
}

void UClearWidget::ReturnTitle()
{
	UGameplayStatics::OpenLevel(this, "Title");
}
