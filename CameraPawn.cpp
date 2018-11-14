// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPawn.h"


// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent. Root is like Parent.
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;
	//This creates a spring arm (tries to maintain it's children at fixed ditance from parent, but will retract the children if there's a collision, and spring back when there's no collision) 
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootScene);
	//Makes the camera NOT collide with all the objects on the map
	SpringArm->bDoCollisionTest = false;
	//Sets a rotation for the camera
	SpringArm->SetRelativeRotation(FRotator(-50, 0, 0));
	//Creates the Camera and attaches it to the SpringArm. So, we have a Transform to which the SpringArm is attached, to which the camera is attached.
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	//The function GetController gets a player controller. If that controller is a Player Controller, it assigns it to our pointer to APlayerController
	pc = Cast<ARTSPlayerController>(GetController());
	//Gets size of the screen
	pc->GetViewportSize(screenSizeX, screenSizeY);
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//this calls the function panMoveCamera and defines the parameter panDirection to GetCameraAndDirection() and multiplies it by speed to make it faster or slower
	panMoveCamera(GetCameraAndDirection()*camSpeed);
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FVector ACameraPawn::GetCameraAndDirection() {
	float mousePosX;
	float mousePosY;
	float camDirX = 0;
	float camDirY = 0;

	pc->GetMousePosition(mousePosX, mousePosY);

	//In ue4, top left of the screen is (0, 0) and bottom right is (screenSize, screenSize)
	//These 2 if statements check if the mouse position is on the left/up of the screen (mousePosX or mousePosY == 0) or inside a margin (defined in the header file)
	if (mousePosX <= margin) {
		camDirY = -1;
	}
	if (mousePosY <= margin) {
		camDirX = 1;
	}
	//These 2 if statements check if the mouse position is on the right/bottom of the screen (mousePosX or mousePosY == screenSize) or inside a margin (defined in the header file)
	if (mousePosX >= screenSizeX - margin) {
		camDirY = 1;
	}
	if (mousePosY >= screenSizeY - margin) {
		camDirX = -1;
	}
	
	return FVector(camDirX, camDirY, 0);
}

void ACameraPawn::panMoveCamera(FVector panDirection) {
	if (panDirection == FVector::ZeroVector) {//could be FVector(0, 0, 0)
		return;//return nothing because it's a void
	}
	else {
		//Moves the camera
		AddActorWorldOffset(GetCameraAndDirection()*camSpeed);
	}
}



