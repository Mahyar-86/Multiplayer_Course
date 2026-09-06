// Copyright Epic Games, Inc. All Rights Reserved.


#include "Multiplayer_CoursePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "Multiplayer_Course.h"
#include "Widgets/MP_PickupCountWidget.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "Game/MP_PlayerState.h"


void AMultiplayer_CoursePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogMultiplayer_Course, Error, TEXT("Could not spawn mobile controls widget."));

		}
	}
	
	if (IsLocalPlayerController() && PickupCountWidgetClass)
	{
		PickupCountWidget = CreateWidget<UMP_PickupCountWidget>(this, PickupCountWidgetClass);
		PickupCountWidget->AddToViewport();
	}
	
	if (HasAuthority() && IsLocalPlayerController())
	{
		OnPlayerStateInitialized();
	}
}

void AMultiplayer_CoursePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

void AMultiplayer_CoursePlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	OnPlayerStateInitialized();
}

void AMultiplayer_CoursePlayerController::OnPickedUpCountChanged(const int32 NewPickupCount) const
{
	if (PickupCountWidget)
	{
		PickupCountWidget->SetPickupCount(NewPickupCount);
	}
}

void AMultiplayer_CoursePlayerController::OnPlayerStateInitialized()
{
	if (AMP_PlayerState* MP_PlayerState = Cast<AMP_PlayerState>(PlayerState))
	{
		MP_PlayerState->FOnPickedUpItems.AddUObject(this, &ThisClass::OnPickedUpCountChanged);
	}
}
