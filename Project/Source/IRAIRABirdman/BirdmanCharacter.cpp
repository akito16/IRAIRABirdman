// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdmanCharacter.h"
#include "MenuWidget.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "Components/AudioComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ABirdmanCharacter::ABirdmanCharacter()
{
	DontHit = false;

	GetCapsuleComponent()->InitCapsuleSize(21.0f, 96.0f);
	GetCapsuleComponent()->SetHiddenInGame(false);

	GetCharacterMovement()->MaxFlySpeed = MaxSpeed;
	GetCharacterMovement()->GravityScale = 1.0f;
	GetCharacterMovement()->AirControl = 1.0f;

	//Camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(GetMesh());
	
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(GetMesh());
	SpringArmComp->SetRelativeLocation(FVector(0.0f, 0.0f, 130.0f));

	CameraComp->AttachToComponent(SpringArmComp, FAttachmentTransformRules::KeepRelativeTransform);
	
	SpringArmComp->TargetArmLength = 500.0f;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->bEnableCameraLag = false;
	
	//Collision
	HeadCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("HeadCollision"));
	HeadCollision->SetupAttachment(RootComponent);
	HeadCollision->BodyInstance.SetCollisionProfileName("Player");

	RightArmCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightArmCollision"));
	RightArmCollision->SetupAttachment(RootComponent);
	RightArmCollision->BodyInstance.SetCollisionProfileName("Player");

	LeftArmCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftArmCollision"));
	LeftArmCollision->SetupAttachment(RootComponent);
	LeftArmCollision->BodyInstance.SetCollisionProfileName("Player");

	RightFootCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RightFootCollision"));
	RightFootCollision->SetupAttachment(RootComponent);
	RightFootCollision->BodyInstance.SetCollisionProfileName("Player");

	LeftFootCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftFootCollision"));
	LeftFootCollision->SetupAttachment(RootComponent);
	LeftFootCollision->BodyInstance.SetCollisionProfileName("Player");

	//InGameMenu
	static ConstructorHelpers::FClassFinder<UMenuWidget> MenuWidgetObj(TEXT("/Game/Blueprints/UI/UI_Menu"));
	MenuWidgetClass = MenuWidgetObj.Class;

	//Sound Unimplemented
	/*static ConstructorHelpers::FObjectFinder<USoundCue> FailureSoundCueObject(TEXT("/Game/Audios/FailureSoundcue"));
	if (FailureSoundCueObject.Succeeded())
	{
		FailureSoundCue = FailureSoundCueObject.Object;

		FailureSoundComp = CreateDefaultSubobject<UAudioComponent>(TEXT("PunchThrowAudioComponent"));
		FailureSoundComp->SetupAttachment(RootComponent);
	}*/
}

// Called when the game starts or when spawned
void ABirdmanCharacter::BeginPlay()
{
	Super::BeginPlay();

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("BeginPlay")));
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	//attach collision
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false);

	//Collision
	HeadCollision->AttachToComponent(GetMesh(), AttachmentRules, "Head_collision");
	HeadCollision->OnComponentBeginOverlap.AddDynamic(this, &ABirdmanCharacter::OverlapBegin);
	RightArmCollision->AttachToComponent(GetMesh(), AttachmentRules, "Rightarm_collision");
	RightArmCollision->OnComponentBeginOverlap.AddDynamic(this, &ABirdmanCharacter::OverlapBegin);
	LeftArmCollision->AttachToComponent(GetMesh(), AttachmentRules, "Leftarm_collision");
	LeftArmCollision->OnComponentBeginOverlap.AddDynamic(this, &ABirdmanCharacter::OverlapBegin);
	RightFootCollision->AttachToComponent(GetMesh(), AttachmentRules, "RightFoot_collision");
	RightFootCollision->OnComponentBeginOverlap.AddDynamic(this, &ABirdmanCharacter::OverlapBegin);
	LeftFootCollision->AttachToComponent(GetMesh(), AttachmentRules, "LeftFoot_collision");
	LeftFootCollision->OnComponentBeginOverlap.AddDynamic(this, &ABirdmanCharacter::OverlapBegin);

}

// Called every frame
void ABirdmanCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector DownMove = FVector(0.0f, 0.0f, MaxSpeed * DeltaTime * -1.0f);
	AddActorLocalOffset(DownMove, true);
}

// Called to bind functionality to input
void ABirdmanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ABirdmanCharacter::MoveForward);
	PlayerInputComponent->BindAxis("RotateRight", this, &ABirdmanCharacter::RotateRight);

	PlayerInputComponent->BindAction("MoveUp", IE_Pressed, this, &ABirdmanCharacter::MoveUp);
	PlayerInputComponent->BindAction("MoveUp", IE_Released, this, &ABirdmanCharacter::MoveDown);

	PlayerInputComponent->BindAction("Menu", IE_Pressed, this, &ABirdmanCharacter::MenuToggle);
}

void ABirdmanCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f)) 
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}
void ABirdmanCharacter::RotateRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ABirdmanCharacter::MoveUp()
{
	bPressedJump = true;
	this->JumpCurrentCount = 1;
}

void ABirdmanCharacter::MoveDown()
{
	bPressedJump = false;
}

//InGameMenu toggle
void ABirdmanCharacter::MenuToggle()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Menu")));
	if (IsValid(MenuCurrentWidget))
	{
		MenuCurrentWidget->CloseUI();
		MenuCurrentWidget = nullptr;
	}
	else
	{
		MenuCurrentWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuWidgetClass);
		if (IsValid(MenuCurrentWidget))
		{
			MenuCurrentWidget->OpenUI();
		}
	}
}

//Return start positon
void ABirdmanCharacter::Respawn()
{
	FVector RespawnPos(-1210.0f, 0.0f, 172.0f);
	this->SetActorLocation(RespawnPos);
}

//Miss event
void ABirdmanCharacter::OverlapBegin(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Overlap")));
	if (DontHit) {
		Respawn();
		DontHit = false;
	}
}