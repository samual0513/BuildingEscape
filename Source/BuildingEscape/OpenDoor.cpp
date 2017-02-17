// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}
void UOpenDoor::OpenDoor()
{

	Owner->SetActorRelativeRotation(FRotator(0.0f, OpenAngle, 0.0f));
}
void UOpenDoor::CloseDoor()
{

	//Set the door rotation
	Owner->SetActorRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the trigger Volume
	//if the actorthatopens is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	//check 
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}

	
}

