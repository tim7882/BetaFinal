// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "my_Car.generated.h"

UCLASS()
class MYPROJECT2_API Amy_Car : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Amy_Car();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
