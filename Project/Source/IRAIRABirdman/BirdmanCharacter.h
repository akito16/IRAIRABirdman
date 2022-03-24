// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/AudioComponent.h"
#include "BirdmanCharacter.generated.h"

UCLASS()
class IRAIRABIRDMAN_API ABirdmanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABirdmanCharacter();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
		class UBoxComponent* HeadCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
		class UBoxComponent* RightArmCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
		class UBoxComponent* LeftArmCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
		class UBoxComponent* RightFootCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Collision)
		class UBoxComponent* LeftFootCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		class UAnimMontage* FlyingMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio)
		class USoundCue* SuccessSoundCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Audio)
		class USoundCue* FailureSoundCue;

	UAudioComponent* SuccessSoundComp;
	UAudioComponent* FailureSoundComp;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMenuWidget> MenuWidgetClass;

	UPROPERTY(EditAnywhere)
		class UMenuWidget* MenuCurrentWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void RotateRight(float Value);

	void MoveUp();

	void MoveDown();

	float MaxSpeed = 100.0f;

	void MenuToggle();

	void Respawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void OverlapBegin(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	bool DontHit;

	int MissCount = 0;
};
