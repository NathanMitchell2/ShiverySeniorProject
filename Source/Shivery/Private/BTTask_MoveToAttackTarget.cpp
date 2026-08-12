#include "BTTask_MoveToAttackTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "MonsterMotivationComponent.h"
#include "MonsterEnums.h"
#include "TimerManager.h"
#include "Engine/World.h"

UBTTask_MoveToAttackTarget::UBTTask_MoveToAttackTarget()
{
    NodeName = "Move To Attack Target";

    // Use TargetActor BB key by default
    BlackboardKey.AddObjectFilter(
        this,
        GET_MEMBER_NAME_CHECKED(UBTTask_MoveToAttackTarget, BlackboardKey),
        AActor::StaticClass());
}

EBTNodeResult::Type UBTTask_MoveToAttackTarget::ExecuteTask(
    UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    CachedOwnerComp = &OwnerComp;

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController)
    {
        return EBTNodeResult::Failed;
    }

    // Set movement speed override
    ACharacter* Monster = Cast<ACharacter>(AIController->GetPawn());
    if (Monster && Monster->GetCharacterMovement())
    {
        Monster->GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
    }

    // Calculate how many consecutive stuck checks before triggering breakout
    // Based on PathFailTimeout / StuckCheckInterval
    if (PathFailTimeout > 0.0f && StuckCheckInterval > 0.0f)
    {
        StuckChecksRequired = FMath::Max(
            1, FMath::FloorToInt(PathFailTimeout / StuckCheckInterval));

        // Reset stuck tracking state
        LastDistanceToTarget = 999999.0f;
        StuckChecks = 0;

        UWorld* World = AIController->GetWorld();
        if (World)
        {
            FTimerDelegate StuckCheckDelegate;
            StuckCheckDelegate.BindLambda([this]()
                {
                    // Hard validation — if anything is invalid, just bail
                    if (!IsValid(this) || !CachedOwnerComp || !IsValid(CachedOwnerComp))
                    {
                        return;
                    }

                    // Verify the BT is still actually running this task
                    if (CachedOwnerComp->GetActiveNode() != this)
                    {
                        // Task is no longer active, clean up our timer
                        if (UWorld* W = CachedOwnerComp->GetWorld())
                        {
                            W->GetTimerManager().ClearTimer(StuckCheckTimerHandle);
                        }
                        return;
                    }

                    AAIController* AIC = CachedOwnerComp->GetAIOwner();
                    if (!AIC)
                    {
                        return;
                    }

                    ACharacter* Pawn = Cast<ACharacter>(AIC->GetPawn());
                    if (!Pawn)
                    {
                        return;
                    }

                    UBlackboardComponent* BB = AIC->GetBlackboardComponent();
                    if (!BB)
                    {
                        return;
                    }

                    // Get target actor from BB
                    AActor* Target = Cast<AActor>(
                        BB->GetValueAsObject(FName("TargetActor")));
                    if (!Target)
                    {
                        // No target — task will likely finish soon, just abort check
                        return;
                    }

                    // Calculate current distance
                    float CurrentDistance = FVector::Dist(
                        Pawn->GetActorLocation(),
                        Target->GetActorLocation());

                    // Check if monster is making progress
                    // Progress = distance has decreased by at least MinProgressDistance
                    if (CurrentDistance >= LastDistanceToTarget - MinProgressDistance)
                    {
                        StuckChecks++;
                    }
                    else
                    {
                        // Made progress — reset stuck counter
                        StuckChecks = 0;
                    }

                    LastDistanceToTarget = CurrentDistance;

                    // After enough consecutive stuck checks, trigger breakout
                    if (StuckChecks >= StuckChecksRequired)
                    {
                        UMonsterMotivationComponent* MotComp =
                            Pawn->FindComponentByClass<UMonsterMotivationComponent>();

                        if (MotComp)
                        {
                            MotComp->AddMotivation(
                                EMonsterMotivation::BREAKOUT, 80);
                        }

                        UE_LOG(LogTemp, Warning,
                            TEXT("[MoveToAttackTarget] Monster stuck for %.1fs — triggering BREAKOUT"),
                            StuckChecksRequired * StuckCheckInterval);

                        // Stop the timer to prevent re-firing
                        if (UWorld* TimerWorld = AIC->GetWorld())
                        {
                            TimerWorld->GetTimerManager().ClearTimer(
                                StuckCheckTimerHandle);
                        }

                        FinishLatentTask(*CachedOwnerComp, EBTNodeResult::Failed);
                    }
                });

            // Looping timer — checks every StuckCheckInterval seconds
            World->GetTimerManager().SetTimer(
                StuckCheckTimerHandle,
                StuckCheckDelegate,
                StuckCheckInterval,
                true);  // looping = true
        }
    }

    // Delegate to parent BTTask_MoveTo for actual movement
    return Super::ExecuteTask(OwnerComp, NodeMemory);
}

void UBTTask_MoveToAttackTarget::OnTaskFinished(
    UBehaviorTreeComponent& OwnerComp,
    uint8* NodeMemory,
    EBTNodeResult::Type TaskResult)
{
    // Aggressively clear timer using world from OwnerComp (more reliable than AIController)
    if (UWorld* World = OwnerComp.GetWorld())
    {
        World->GetTimerManager().ClearTimer(StuckCheckTimerHandle);
    }

    // Invalidate handle explicitly
    StuckCheckTimerHandle.Invalidate();

    // Clear cached references BEFORE calling super
    CachedOwnerComp = nullptr;
    StuckChecks = 0;
    LastDistanceToTarget = 999999.0f;

    Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}