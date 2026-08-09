// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MP_Blade.generated.h"

class UBoxComponent;

UCLASS()
class MULTIPLAYER_COURSE_API AMP_Blade : public AActor
{
	GENERATED_BODY()

public:
	AMP_Blade();
	virtual void Tick(float DeltaTime) override;
	
	virtual void NotifyActorBeginOverlap (AActor* OtherActor) override;
protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> BladeMesh;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> BladeCollision;
	
	UPROPERTY(EditAnywhere)
	float Power = 100;
};
 