// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStartLine.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "BirdmanCharacter.h"

// Sets default values
AGameStartLine::AGameStartLine()
{
	OverlapVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapVolume"));
	OverlapVolume->BodyInstance.SetCollisionProfileName("StartGoalLine");
	RootComponent = OverlapVolume;
	OnActorBeginOverlap.AddDynamic(this, &AGameStartLine::OverlapBegins);
}

void AGameStartLine::OverlapBegins(AActor* MyOverlapActor, AActor* OtherActor)
{
	ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	ABirdmanCharacter* BCharacter = Cast<ABirdmanCharacter>(MyCharacter);

	if (OtherActor == MyCharacter)
	{
		if (BCharacter->DontHit != true)
		{
			BCharacter->DontHit = true;
		}
	}
}

