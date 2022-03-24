// Fill out your copyright notice in the Description page of Project Settings.


#include "GameGoalLine.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "BirdmanCharacter.h"
#include "ClearWidget.h"

// Sets default values
AGameGoalLine::AGameGoalLine()
{
	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolume"));
	OverlapVolume->BodyInstance.SetCollisionProfileName("StartGoalLine");
	RootComponent = OverlapVolume;
	OnActorBeginOverlap.AddDynamic(this, &AGameGoalLine::OverlapBegins);

	static ConstructorHelpers::FClassFinder<UClearWidget> ClearWidgetObj(TEXT("/Game/Blueprints/UI/UI_Clear"));
	ClearWidgetClass = ClearWidgetObj.Class;
}

void AGameGoalLine::OverlapBegins(AActor* MyOverlapActor, AActor* OtherActor)
{
	ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	ABirdmanCharacter* BCharacter = Cast<ABirdmanCharacter>(MyCharacter);

	if (OtherActor == MyCharacter)
	{
		if (BCharacter->DontHit)
		{
			BCharacter->DontHit = false;
		}
	}

	CurrentClearWidget = CreateWidget<UClearWidget>(GetWorld(), ClearWidgetClass);
	if (IsValid(CurrentClearWidget))
	{
		CurrentClearWidget->OpenUI();
	}
}
