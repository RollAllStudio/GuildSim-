// Fill out your copyright notice in the Description page of Project Settings.


#include "Singelton/MyPlayerController.h"
#include "HUDMenager.h"
#include "SimpleInteraction/Public/PlayerInteractionComponent.h"

AMyPlayerController::AMyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerInteractionComponent = CreateDefaultSubobject<UPlayerInteractionComponent>(TEXT("PlayerInteractionComponent"));
}

AHUDMenager* AMyPlayerController::GetMyHudMenager()
{
	if (!MyHudMenager)
	{
		MyHudMenager = Cast<AHUDMenager>(GetHUD());
	}

	return MyHudMenager;
}

void AMyPlayerController::Tick(float DeltaTime)
{
	if (bIsInteractionPressed)
	{
		InteractionPressedTime = InteractionPressedTime + DeltaTime;
	}
}

UPrimitiveComponent* AMyPlayerController::GetCurrentTracedComponent() const
{
	return PlayerInteractionComponent->GetCurrentTracedComponent();
}

AActor* AMyPlayerController::GetCurrentTracedActor() const
{
	return PlayerInteractionComponent->GetCurrentTracedActor();
}

UObject* AMyPlayerController::GetCurrentInteractionObject() const
{
	if (GetCurrentTracedComponent())
	{
		if (GetCurrentTracedComponent()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			return (GetCurrentTracedComponent());
		}

		return (GetCurrentTracedActor());
	}

	return nullptr;
}

void AMyPlayerController::BeginPlay()
{
	GetMyHudMenager();
	SetShowMouseCursor(true);

	PlayerInteractionComponent->Init(this);
	
	Super::BeginPlay();

	InputComponent->BindAction("CallInteraction", IE_Pressed, this, &AMyPlayerController::OnInteractionPressed);
	InputComponent->BindAction("CallInteraction", IE_Released, this, &AMyPlayerController::OnInteractionReleased);
}

void AMyPlayerController::OnInteractionPressed()
{
	bIsInteractionPressed = true;
}

void AMyPlayerController::OnInteractionReleased()
{
	
	if (GetCurrentInteractionObject())
	{
		if (GetCurrentInteractionObject()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			if (IInteractionInterface::Execute_GetCanInteract(GetCurrentInteractionObject()))
			{
				IInteractionInterface::Execute_Interact(GetCurrentInteractionObject());
			}
		}
	}

	InteractionPressedTime = 0;
	bIsInteractionPressed = false;
	
}

