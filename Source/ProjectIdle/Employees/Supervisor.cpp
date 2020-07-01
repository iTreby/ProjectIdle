// Fill out your copyright notice in the Description page of Project Settings.


#include "Supervisor.h"
#include "ProjectIdle/GameManager.h"

ASupervisor::ASupervisor() {
	Salary = 100.f;
	Position = EPosition::Supervisor;
}

// Sets default values
ASupervisor::ASupervisor(ERole Department)
{
	Salary = 100.f;
	EmployeeRole = Department;
	Position = EPosition::Supervisor;
}

void ASupervisor::EvaluateEmployee() {
	auto Count = 0;
	for (auto Departments : GM->DepartmentList) {
		if (Departments->DepRole == EmployeeRole) {
			Count = Departments->EmpCount;
		}
	}

	for (auto DepartmentEmployee : GM->EmployeeList) {
		if (DepartmentEmployee->EmployeeRole == EmployeeRole && !DepartmentEmployee->HasBeenEvaluated && !IsEvaluating && Cast<ASupervisor>(DepartmentEmployee) == nullptr && DepartmentEmployee->IsWorking) {
			EmployeeToEval = DepartmentEmployee;
			MoveEmployee(EmployeeToEval->GetActorLocation(), 75.f);
			IsEvaluating = true;
		}
		else if (DepartmentEmployee->HasBeenEvaluated) {
			Count--;
			if (Count == 0) { //Scouting over
				MoveEmployee(StartPosition);
			}
		}
	}
}

void ASupervisor::BeginPlay()
{
	Super::BeginPlay();
	//StartPosition = FVector(0, 0, 0);


		//GM->WorkStation->UpdateWorkstationPosition();
	for (auto Workstation : GM->WorkstationList) {
		if (Workstation->IsEnabled == true && !Workstation->HasEmployee && Workstation->StationRole == EmployeeRole && Workstation->StationOwnerPosition == EPosition::Supervisor) {
			Workstation->UpdateWorkstationPosition(this);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Assigning Sup Workstation");
			break;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Looping Workstation");
	}
	//IsDepartmentWorking();
	MoveEmployee(StartPosition);


}


void ASupervisor::Tick(float DeltaTime)
{
	//Super::Tick(DeltaTime);
	if (IsEvaluating && !AI->IsMoving) {
		if (!IsWorking) {
			WorkProgressBar->SetVisibility(true);
			AssignedWorkload = 10.f;
			CurrentWorkload = AssignedWorkload;
			IsWorking = true;
		}
		//Implement progress bar calc here
		if (WorkProgressBar != nullptr && IsWorking) {
			WorkProgressBar->SetWorldRotation(Camera->GetCameraRotation());
			WorkProgressBar->AddLocalRotation(FRotator(0, 180, 0));
			CurrentWorkload -= DeltaTime * 1.25f;
		}

		if (CurrentWorkload <= 0) {
			IsEvaluating = false;
			IsWorking = false;
			EmployeeToEval->HasBeenEvaluated = true;
			//MoveEmployee(StartPosition);
			EvaluateEmployee();
			WorkProgressBar->SetVisibility(false);
		}

	}

}

void ASupervisor::InitSupervisor(ERole Department) {
	if (Department == ERole::Programmer) {
		this->EmployeeRole = Department;
		GM->ProgrammingDepartment->HasSupervisor = true;
		GM->ProgrammingDepartment->SupervisorRef = this;
	}
	else if (Department == ERole::Artist) {
		this->EmployeeRole = Department;
		GM->ArtistDepartment->HasSupervisor = true;
		GM->ArtistDepartment->SupervisorRef = this;
	}
	//EvaluateEmployee();
}

void ASupervisor::FiredFinal()
{
	Super::FiredFinal();
	if (EmployeeRole == ERole::Programmer) {
		GM->ProgrammingDepartment->HasSupervisor = false;
		GM->ProgrammingDepartment->SupervisorRef = nullptr;
	}
	else if (EmployeeRole == ERole::Artist) {
		GM->ArtistDepartment->HasSupervisor = false;
		GM->ArtistDepartment->SupervisorRef = nullptr;
	}
}


