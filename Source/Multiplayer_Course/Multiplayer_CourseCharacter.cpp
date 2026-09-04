// Copyright Epic Games, Inc. All Rights Reserved.

#include "Multiplayer_CourseCharacter.h"

#include <string>

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Multiplayer_Course.h"
#include "Actors/MP_Actor.h"
#include "Components/MP_HealthComponent.h"
#include "Net/UnrealNetwork.h"
#include "Utilities/MP_Utilities.h"
#include "Game/MP_GameState.h"
#include "Game/MP_PlayerState.h"

AMultiplayer_CourseCharacter::AMultiplayer_CourseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	
	HealthComponent = CreateDefaultSubobject<UMP_HealthComponent>("Health");
}

void AMultiplayer_CourseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMultiplayer_CourseCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AMultiplayer_CourseCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMultiplayer_CourseCharacter::Look);
		
		EnhancedInputComponent->BindAction(GeneralAction, ETriggerEvent::Triggered, this, &ThisClass::OnGeneralButtonPressed);
	}
	else
	{
		UE_LOG(LogMultiplayer_Course, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AMultiplayer_CourseCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AMultiplayer_CourseCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AMultiplayer_CourseCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AMultiplayer_CourseCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AMultiplayer_CourseCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void AMultiplayer_CourseCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void AMultiplayer_CourseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(RPCDelayTimer, this, &AMultiplayer_CourseCharacter::OnRPCDelayTimer, 4, false);
}

USkeletalMeshComponent* AMultiplayer_CourseCharacter::GetPlayerMesh_Implementation() const
{
	return GetMesh();
}

void AMultiplayer_CourseCharacter::OnGeneralButtonPressed()
{
	/*
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Blade Power is: %f"), BladePower));
	
	bReplicatePickedUpItems = !bReplicatePickedUpItems;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::Printf(TEXT("Replicate Pickup Items Status is: %d"), bReplicatePickedUpItems));
	*/
	
	// Server_PrintMessage("Run it on server");

	const AMP_GameState* GameState = GetWorld()->GetGameState<AMP_GameState>();

	if (GameState == nullptr)
	{
		return;
	}

	const int32 TeamNumber = GameState->GetTeamOfPlayerController(GetController<APlayerController>());
	const FString TeamNumberText = TeamNumber > 0 ? FString::FromInt(TeamNumber) : "NO TEAM";
	
	UMP_Utilities::PrintNetworkLogMessage(FString::Printf(TEXT("This character is in team: %s"), *TeamNumberText), this, 30);
}

void AMultiplayer_CourseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	//DOREPLIFETIME(ThisClass, BladePower)
	//DOREPLIFETIME(ThisClass, PickedUpItems)
	
	DOREPLIFETIME_CONDITION(ThisClass,BladePower, COND_Custom)
	DOREPLIFETIME_CONDITION(ThisClass, PickedUpItems, COND_Custom)
}

void AMultiplayer_CourseCharacter::PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);
	
	DOREPLIFETIME_ACTIVE_OVERRIDE(ThisClass, PickedUpItems, bReplicatePickedUpItems);
}

void AMultiplayer_CourseCharacter::GrantBladePower_Implementation(const float Power)
{
	BladePower = Power;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Blade Power Granted: %f"), BladePower));
}

void AMultiplayer_CourseCharacter::PlusPickedUp_Implementation()
{
	PickedUpItems++;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Picked Up! Total %d"), PickedUpItems));

	if (AMP_PlayerState* PlayerState = GetPlayerState<AMP_PlayerState>())
	{
		PlayerState->PickupNum += 1;
	}
}

void AMultiplayer_CourseCharacter::GetHealthPotion_Implementation(float PotionEffect)
{
	HealthComponent->SetHealth(HealthComponent->GetHealth() + PotionEffect);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Potion Picked Up! Health: %f"), HealthComponent->GetHealth()));
}

void AMultiplayer_CourseCharacter::OnRep_BladePower()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("REPNOTIFY Blade Power is: %f"), BladePower));
}

void AMultiplayer_CourseCharacter::OnRep_PickedUpItems(int32 PreviousValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("REPNOTIFY Picked Up! Total: From %d to %d"), PreviousValue, PickedUpItems));
}

void AMultiplayer_CourseCharacter::OnRPCDelayTimer()
{
	if (HasAuthority())
	{
		//Client_PrintMessage("This is a message running on owning client");
		/*	
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			
			GetWorld()->SpawnActor<AMP_Actor>(SpawnParams); 
		*/
		//Multicast_PrintMessage("This is a message to run on server and related clients.");
		//Remote_PrintMessage("This is a remote RPC func.");
	}
}

void AMultiplayer_CourseCharacter::Client_PrintMessage_Implementation(const FString& Message)
{
	UMP_Utilities::PrintNetworkLogMessage(Message, this, 30);	
}

void AMultiplayer_CourseCharacter::Server_PrintMessage_Implementation(const FString& Message)
{
	UMP_Utilities::PrintNetworkLogMessage(Message, this, 30);	
}

bool AMultiplayer_CourseCharacter::Server_PrintMessage_Validate(const FString& Message)
{
	return !Message.IsEmpty();
}

void AMultiplayer_CourseCharacter::Multicast_PrintMessage_Implementation(const FString& Message)
{
	UMP_Utilities::PrintNetworkLogMessage(Message, this, 30);	
}

void AMultiplayer_CourseCharacter::Remote_PrintMessage_Implementation(const FString& Message)
{
	UMP_Utilities::PrintNetworkLogMessage(Message, this, 30);	
}
