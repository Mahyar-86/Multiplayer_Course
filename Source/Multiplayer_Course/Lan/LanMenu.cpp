// Fill out your copyright notice in the Description page of Project Settings.


#include "LanMenu.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

void ULanMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HandleInputMode(UIOnly);
	
	Button_Host->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	Button_Join->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
}

void ULanMenu::HostButtonClicked()
{
	HandleInputMode(GameOnly);
	
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, HostingLevel, true, TEXT("listen"));
}

void ULanMenu::JoinButtonClicked()
{
	HandleInputMode(GameOnly);
	
	const FString IpAddress = TextBox_IpAddress->GetText().ToString();
	
	UGameplayStatics::OpenLevel(this, *IpAddress);
}

void ULanMenu::HandleInputMode(const EInputMode InputMode) const
{
	APlayerController* PlayerController = GetOwningPlayer();
	
	if (PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("HandleInputMode: PlayerController is nullptr"));
		return;
	}
	
	bool ShowMouseCursor = false;
	
	switch (InputMode)
	{
	case GameOnly:
		PlayerController->SetInputMode(FInputModeGameOnly());
		ShowMouseCursor = false;
		break;
	case UIOnly:
		PlayerController->SetInputMode(FInputModeUIOnly());
		ShowMouseCursor = true;
		break;
	case GameAndUI:
		PlayerController->SetInputMode(FInputModeGameAndUI());
		ShowMouseCursor = true;
		break;
	}
	
	GetOwningPlayer()->SetShowMouseCursor(ShowMouseCursor);
}
