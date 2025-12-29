// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class ASSIGNMENT5UECPLUS_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	void Turn(const FRotator& DeltaRotation);
	void Move(const FVector& DeltaMove);
	void ExecuteEvent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RandomTurnAndMove();
	
private:
	float RotationRange = 50.0f;
	float MoveRange = 5.0f;

	int32 RandomEventCount = 0;
	float AccumulatedMoveDistance = 0.0f;
};
