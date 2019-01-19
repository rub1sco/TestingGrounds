// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
//#include "PatrollingGuard.h" //TODO remove coupling
#include "PatrolRoute.h"


EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    
//    UE_LOG(LogTemp, Warning, TEXT("C++"));
    
    
    //TODO protect against empty roots
    //TODO protect against empty patrol route
    
    //Get Patrol Points
    auto AIController = OwnerComp.GetAIOwner();
    auto ControlledPawn = AIController -> GetPawn();
    auto PatrolRoute = ControlledPawn ->FindComponentByClass<UPatrolRoute>();
    
    if(!ensure(PatrolRoute)){return EBTNodeResult::Failed;}
    

    auto PatrolPoints = PatrolRoute -> GetPatrolPoints();
    if(PatrolPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Missing Patrol Points"))
        return EBTNodeResult::Failed;
    }
    
    
    //set next waypoints
    auto BlackboardComp = OwnerComp.GetBlackboardComponent();
    auto Index = BlackboardComp -> GetValueAsInt(IndexKey.SelectedKeyName);
    BlackboardComp -> SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
    
    //cycle index
    auto nextIndex = (Index+1)% PatrolPoints.Num();
    BlackboardComp -> SetValueAsInt(IndexKey.SelectedKeyName, nextIndex);
    
//    UE_LOG(LogTemp, Warning, TEXT("waypoint index is %i"), Index);
    
    return EBTNodeResult::Succeeded;
}
