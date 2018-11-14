// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
  #include "Camera/CameraComponent.h"
#include "RTSPlayerController.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

UCLASS()
class RTSCPP_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	USceneComponent* RootScene;
	
	UPROPERTY()
	USpringArmComponent* SpringArm;
	
	UPROPERTY()
	UCameraComponent* CameraComponent;

	UPROPERTY()
	ARTSPlayerController* pc;

	UPROPERTY()
	float margin = 15;

	UPROPERTY()
	int32 screenSizeX;

	UPROPERTY()
	int32 screenSizeY;

	UPROPERTY()
	float camSpeed = 15;

	UFUNCTION()
	FVector GetCameraAndDirection();

	UFUNCTION()
		void panMoveCamera(FVector panDirection);
};
