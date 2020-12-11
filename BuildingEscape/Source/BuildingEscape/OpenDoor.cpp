// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// Set up initial Yaw
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw = InitialYaw + TargetDeltaYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Pressure Plate is : %s"), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//UE_LOG(LogTemp, Warning, TEXT("Yaw is : %f"), GetOwner()->GetActorRotation().Yaw);
	//OpenDoor(DeltaTime);
	// null pointer protection.
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
	}
	
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Yaw difference is : %f"),
		   *GetOwner()->GetName(), GetOwner()->GetActorRotation().Yaw - CurrentYaw);
	//CurrentYaw = FMath::Lerp(GetOwner()->GetActorRotation().Yaw, TargetYaw, 0.02f);
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * 1.f);
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	CurrentRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(CurrentRotation);
}