// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class PROJECTIDLE_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* CollisionBox;

	class UGameManager* GM;
	UPROPERTY() FVector DoorLocation;
	UPROPERTY() USceneComponent* Root;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* DoorMesh;
	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* DoorFrameMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor") int FloorLevel = -1;
	bool Moved = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
