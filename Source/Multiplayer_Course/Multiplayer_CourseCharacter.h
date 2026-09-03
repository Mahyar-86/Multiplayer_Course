// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/MP_PlayerInteraction.h"
#include "Logging/LogMacros.h"
#include "Multiplayer_CourseCharacter.generated.h"

class UMP_HealthComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AMultiplayer_CourseCharacter : public ACharacter, public IMP_PlayerInteraction
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

public:

	/** Constructor */
	AMultiplayer_CourseCharacter();	

protected:

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

public:

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

public:

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	
public:
	
	virtual void BeginPlay() override;
	
	/** IMP_PlayerInteraction Implementations **/
	virtual USkeletalMeshComponent* GetPlayerMesh_Implementation() const override;
	virtual void GrantBladePower_Implementation(float Power) override;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void PreReplication(IRepChangedPropertyTracker& ChangedPropertyTracker) override;
	
	virtual void PlusPickedUp_Implementation() override;
	
	virtual void GetHealthPotion_Implementation(float PotionEffect) override;
	
protected:
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* GeneralAction;
	
private:
	
	UPROPERTY(ReplicatedUsing = "OnRep_BladePower")
	float BladePower = 0;
	
	UFUNCTION()
	void OnGeneralButtonPressed();
	
	UFUNCTION()
	void OnRep_BladePower();
	
	UPROPERTY(ReplicatedUsing = "OnRep_PickedUpItems")
	int32 PickedUpItems = 0;
	
	UFUNCTION()
	void OnRep_PickedUpItems(int32 PreviousValue);
	
	UPROPERTY()
	bool bReplicatePickedUpItems = true;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMP_HealthComponent> HealthComponent;
	
	UFUNCTION(Client, Reliable)
	void Client_PrintMessage(const FString& Message);
	
	FTimerHandle RPCDelayTimer;
	
	void OnRPCDelayTimer();
	
	UFUNCTION(Server, Reliable)
	void Server_PrintMessage(const FString& Message);
	
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PrintMessage(const FString& Message);
	
	UFUNCTION(Remote, Reliable)
	void Remote_PrintMessage(const FString& Message);
};
