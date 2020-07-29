// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WorldObject/Door.h"
#include "WorldObject/Wall.h"
#include "MeetingDepartment.h"
#include "Shop/Item.h"
#include "Department.h"
#include "Departments/ProgrammingDepartment.h"
#include "Departments/ArtistDepartment.h"
#include "Widgets/WorkstationUpgradeWidget.h"
#include "CeoDepMenuWidget.h"
#include "ProjectIdleCharacter.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTIDLE_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	UGameManager();
	//UPROPERTY(BlueprintReadWrite) TArray<class AItem*> InventoryList;
	UPROPERTY(BlueprintReadWrite) TMap<class AItem*, int> InventoryList;
	UPROPERTY(BlueprintReadWrite) TArray<class AEmployee*> EmployeeList;
	UPROPERTY(BlueprintReadWrite) TArray<class ADepartment*> DepartmentList;
	UPROPERTY(BlueprintReadWrite) TArray<class AWall*> FloorList;
	UPROPERTY(BlueprintReadWrite) TArray<class AWall*> WallList;
	UPROPERTY(BlueprintReadWrite) TArray<class AWall*> UnassignedFloorList;
	UPROPERTY(BlueprintReadWrite) TArray<class AWall*> FullLevel;
	UPROPERTY(BlueprintReadWrite) TArray<class ADoor*> DoorList;
	UPROPERTY(BlueprintReadWrite) TArray<class ADoor*> UnassignedDoorList;
	UPROPERTY(BlueprintReadWrite) TArray<class AOfficeDepartment*> OfficeDepartmentList;
	UPROPERTY(BlueprintReadWrite) TArray<class AOfficeDepartment*> UnassignedOfficeDepartmentList;
	UPROPERTY(BlueprintReadWrite) TArray<class AMeetingDepartment*> MeetingDepartmentList;
	UPROPERTY(BlueprintReadWrite) TArray<class AMeetingDepartment*> UnassignedMeetingDepartmentList;
	UPROPERTY(BlueprintReadWrite) TArray<class AElevator*> ElevatorList;
	UPROPERTY(BlueprintReadWrite) TArray<class AElevator*> UnassignedElevatorList;
	UPROPERTY(BlueprintReadWrite) TArray<class AProgrammingDepartment*> ProgrammingDepList;


	UPROPERTY(BlueprintReadWrite) int NumOfProgrammers;
	UPROPERTY(BlueprintReadWrite) int NumOfArtists;
	UPROPERTY(BlueprintReadWrite) int Money;
	UPROPERTY(BlueprintReadWrite) int TotalSalary;

	UPROPERTY(BlueprintReadWrite) TArray<class AChair*> MeetingChairList;
	UPROPERTY(BlueprintReadWrite) TArray<class AWorkstation*> WorkstationList;

	UPROPERTY(BlueprintReadWrite) class AProjectIdleCharacter* Character;
	UPROPERTY(BlueprintReadWrite) class AOfficeDepartment* OfficeDepartment;
	UPROPERTY(BlueprintReadWrite) class AMeetingDepartment* MeetingDepartment;
	UPROPERTY(BlueprintReadWrite) class AProgrammingDepartment* ProgrammingDepartment;
	UPROPERTY(BlueprintReadWrite) class AArtistDepartment* ArtistDepartment;

	UPROPERTY(BlueprintReadWrite) class AWorkstation* WorkStation;
	UPROPERTY(BlueprintReadWrite) class ADoor* Door;
	UPROPERTY(BlueprintReadWrite) class UWorkstationUpgradeWidget* Upgrade;
	UPROPERTY(BlueprintReadWrite) class UMeetingDepWidget* MeetingWidget;
	UPROPERTY(BlueprintReadWrite) class UShopWidget* ShopWidget;
	UPROPERTY(BlueprintReadWrite) class UElevatorWidget* ElevatorWidget;


	UPROPERTY(BlueprintReadWrite) class AWall* Wall;
	UPROPERTY(BlueprintReadWrite) class AEmployee* Emp;
	UPROPERTY(BlueprintReadWrite) class AFloorManager* FLoorM;
	UPROPERTY(BlueprintReadWrite) class AElevator* Elevator;

	UPROPERTY(BlueprintReadWrite) int EmployeeNameIndex;
	UPROPERTY(BlueprintReadWrite) float SpeedRate = 1;
	UPROPERTY(BlueprintReadWrite) float CheatSpeedRate = 1;
	UPROPERTY(BlueprintReadWrite) int CurrentOfficeFloor = 1;

	UPROPERTY(BlueprintReadWrite) int FloorOneWorkDone = 0;
	UPROPERTY(BlueprintReadWrite) int FloorTwoWorkDone = 0;

	int FloorMaterialID = 0;

	bool IdeaInProduction = false;
	bool IsWidgetInDisplay = false;
	UPROPERTY(BlueprintReadWrite) bool InEditMode = false;
	UPROPERTY() bool IsFloorUpgraded = false;
	UUserWidget* CurrentWidgetInDisplay;
	AEmployee* CurrentEmployeeInDisplay;

public:
	virtual void Init();
	UFUNCTION(BlueprintImplementableEvent) void SaveGameState();
	UFUNCTION(BlueprintImplementableEvent) void LoadGameState();

	UFUNCTION(BlueprintCallable) void SaveGame(FString SaveFile);
	UFUNCTION(BlueprintCallable) void LoadGame(FString SaveFile);
	UFUNCTION(BlueprintCallable) void PopulateSaveFiles();
	void OnGameLoadedFixup(UWorld* World);

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<FString> SaveFileNames;
	TArray<uint8> BinaryData;
};
