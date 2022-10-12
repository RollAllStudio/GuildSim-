// Fill out your copyright notice in the Description page of Project Settings.


#include "GuildSim/Tests/TestActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GuildSim/Public/Singelton/MyPlayerController.h"

// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp00 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp00"));
	MeshComp01 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp01"));

	MeshComp00->SetupAttachment(RootComponent);
	MeshComp01->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATestActor::GetCanInteract_Implementation()
{
	AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (MyPlayerController)
	{
		if (MyPlayerController->GetInteractionPressedTime() < 0.5f)
		{
			return true;
		}
	}
	return false;
}

bool ATestActor::Interact_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor(255, 0, 0 , 255), "Ineraktuje");
	}
	return false;
}

