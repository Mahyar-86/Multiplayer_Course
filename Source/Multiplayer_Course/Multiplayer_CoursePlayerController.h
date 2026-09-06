// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Multiplayer_CoursePlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;
class UMP_PickupCountWidget;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS(abstract)
class AMultiplayer_CoursePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void OnRep_PlayerState() override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMP_PickupCountWidget> PickupCountWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UMP_PickupCountWidget> PickupCountWidget;
	
	void OnPickedUpCountChanged(int32 NewPickupCount) const;
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
	
private:
	void OnPlayerStateInitialized();
};
