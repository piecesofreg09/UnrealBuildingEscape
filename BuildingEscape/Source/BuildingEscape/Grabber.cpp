// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

// if will be replaced with nothing
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber."));

	// Check Physics handle components
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	UE_LOG(LogTemp, Warning, TEXT("Checking."));
	if (PhysicsHandle) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Physics handle is found."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No physics handle is found on %s."), *GetOwner()->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	FVector PlayerViewPointLocation;
	FRotator PlayViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayViewPointRotation);
	/*UE_LOG(LogTemp, Warning, TEXT("%s, %s"), 
		*PlayerViewPointLocation.ToString(),
		*PlayViewPointRotation.ToString());
	*/

	FVector LineTraceEnd = PlayerViewPointLocation + PlayViewPointRotation.Vector() * Reach;
	//UE_LOG(LogTemp, Warning, TEXT("trace: %s"), *LineTraceEnd.ToString());
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 255, 0),
		false,
		0.f,
		0,
		5.f
	);

	// Ray cast to a certain distance
	FHitResult Hit;
	//  The firat parameter is intracetag: we are not using tags
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *ActorHit->GetName());
	}
	
}

