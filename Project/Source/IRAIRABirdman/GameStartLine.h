// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "GameStartLine.generated.h"

UCLASS()
class IRAIRABIRDMAN_API AGameStartLine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameStartLine();

protected:
	UFUNCTION()
		void OverlapBegins(AActor* MyOverlapActor, AActor* OtherActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* OverlapVolume;

};
