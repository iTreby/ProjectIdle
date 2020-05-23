// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Employee.generated.h"

UCLASS()
class PROJECTIDLE_API AEmployee : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEmployee();

	UPROPERTY(EditAnywhere) float Morale;
	UPROPERTY(EditAnywhere) float Performance;
	UPROPERTY(EditAnywhere) float Salary;
	UPROPERTY(EditAnywhere) FString EmployeeRole;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector MeetingLocation;

	FVector StartPosition;

	//Managers
	class AGameHUD* UI;
	class UGameManager* GM;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	

	//UPROPERTY(EditAnywhere, BlueprintReadWrite) AEmployeeAIC* AI; //custom Cpp AIC ref, unused for now
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void GoMeeting();
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void ToMeeting(FVector Destination);
	UFUNCTION(BlueprintCallable, Category = "TestBPFunc") void ReturnPositionAfterMeeting(FVector Destination);

	// Called every frame

	void NotifyActorOnClicked(FKey ButtonPressed = EKeys::RightMouseButton) override;


	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to inputf
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
