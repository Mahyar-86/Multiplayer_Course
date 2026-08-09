// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MP_Pickup.generated.h"

class UCapsuleComponent;

UCLASS()
class MULTIPLAYER_COURSE_API AMP_Pickup : public AActor
{
	GENERATED_BODY()

public:
	AMP_Pickup();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> PickupMesh;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCapsuleComponent> PickupCollision;
};
