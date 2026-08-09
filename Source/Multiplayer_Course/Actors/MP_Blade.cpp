// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_Blade.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/MP_PlayerInteraction.h"


AMP_Blade::AMP_Blade()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root"));
	
	BladeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Blade Mesh");
	BladeMesh->SetupAttachment(RootComponent);
	
	BladeCollision = CreateDefaultSubobject<UBoxComponent>("Blade Collision");
	BladeCollision->SetupAttachment(RootComponent);
}

void AMP_Blade::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMP_Blade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMP_Blade::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!HasAuthority()) return;
	
	if (OtherActor->Implements<UMP_PlayerInteraction>())
	{
		USkeletalMeshComponent* Mesh = IMP_PlayerInteraction::Execute_GetPlayerMesh(OtherActor);
			
		AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "HandGrip_R");
			
		IMP_PlayerInteraction::Execute_GrantBladePower(OtherActor, Power);
	}
}
