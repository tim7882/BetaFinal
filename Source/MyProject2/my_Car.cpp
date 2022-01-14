// Fill out your copyright notice in the Description page of Project Settings.


#include "my_Car.h"

// Sets default values
Amy_Car::Amy_Car()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Amy_Car::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Amy_Car::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Amy_Car::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

