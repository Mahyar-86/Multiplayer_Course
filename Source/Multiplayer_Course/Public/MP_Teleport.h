// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MP_Teleport.generated.h"

class UBoxComponent;

UCLASS()
class MULTIPLAYER_COURSE_API AMP_Teleport : public AActor
{
	GENERATED_BODY()

public:
	AMP_Teleport();
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;
};
