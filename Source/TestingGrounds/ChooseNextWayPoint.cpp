// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    
//    UE_LOG(LogTemp, Warning, TEXT("C++"));
    
    //Get Patrol Points
    OwnerComp.GetAIOwner();
    
    
    auto BlackboardComp = OwnerComp.GetBlackboardComponent();
    auto Index = BlackboardComp -> GetValueAsInt(IndexKey.SelectedKeyName);
    
    UE_LOG(LogTemp, Warning, TEXT("waypoint index is %i"), Index);
    
    return EBTNodeResult::Succeeded;
}
