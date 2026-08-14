// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MP_HealthPotion.generated.h"

class UBoxComponent;

UCLASS()
class MULTIPLAYER_COURSE_API AMP_HealthPotion : public AActor
{
	GENERATED_BODY()

public:
	AMP_HealthPotion();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere)
	UMeshComponent* HealthPotionMesh;
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* HealthPotionCollision;
	
	UPROPERTY(EditAnywhere)
	float PotionEffect = 20;
};
