#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToAttackTarget.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class SHIVERY_API UBTTask_MoveToAttackTarget : public UBTTask_MoveTo
{
    GENERATED_BODY()

public:
    UBTTask_MoveToAttackTarget();

    /** Movement speed override when this task runs */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MoveSpeed = 600.0f;

    /**
     * How long (seconds) the monster must be stuck before triggering BREAKOUT.
     * "Stuck" means distance to target hasn't decreased by at least 50 units
     * over StuckCheckInterval seconds, repeated for StuckChecksRequired checks.
     * Set to 0 to disable stuck detection entirely.
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0"))
    float PathFailTimeout = 15.0f;

    /** How often to check if the monster is making progress (seconds) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.1"))
    float StuckCheckInterval = 1.0f;

    /** Minimum distance reduction per check to count as "making progress" (units) */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0"))
    float MinProgressDistance = 50.0f;

protected:
    virtual EBTNodeResult::Type ExecuteTask(
        UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    virtual void OnTaskFinished(
        UBehaviorTreeComponent& OwnerComp,
        uint8* NodeMemory,
        EBTNodeResult::Type TaskResult) override;

private:
    /** Cached owner comp for use in lambda timers */
    UPROPERTY()
    UBehaviorTreeComponent* CachedOwnerComp = nullptr;

    /** Timer handle for the stuck detection loop */
    FTimerHandle StuckCheckTimerHandle;

    /** Last recorded distance to target — used to detect lack of progress */
    float LastDistanceToTarget = 999999.0f;

    /** Number of consecutive checks where monster failed to make progress */
    int32 StuckChecks = 0;

    /** Required consecutive stuck checks before triggering BREAKOUT */
    int32 StuckChecksRequired = 5;
};