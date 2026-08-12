#include "MonsterStaggerComponent.h"
#include "MonsterMotivationComponent.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UMonsterStaggerComponent::UMonsterStaggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMonsterStaggerComponent::BeginPlay()
{
    Super::BeginPlay();

    // Cache motivation component from owner
    MotivationComponent = GetOwner()->
        FindComponentByClass<UMonsterMotivationComponent>();
}

void UMonsterStaggerComponent::TickComponent(float DeltaTime,
    ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    TickDecay(DeltaTime);
}

void UMonsterStaggerComponent::ApplyExplosionHit(float DamageAmount)
{
    if (bStaggerTriggered) return;

    StaggerGauge = FMath::Clamp(StaggerGauge + DamageAmount, 0.0f, 1.0f);

    if (IsStaggered())
    {
        bStaggerTriggered = true;

        if (bIsInDeathZone)
        {
            // Monster dies — fire death event
            OnMonsterDeath.Broadcast();

            if (MotivationComponent)
            {
                MotivationComponent->AddMotivation(
                    EMonsterMotivation::DESPAWN, 100);
            }
        }
        else
        {
            // Monster retreats backstage
            OnMonsterStaggered.Broadcast();

            if (MotivationComponent)
            {
                MotivationComponent->AddMotivation(
                    EMonsterMotivation::BREAKOUT, 90);
            }

            // Reset after brief delay so animation can play
            // Blueprint binds to OnMonsterStaggered and calls Reset()
            // after stagger animation completes
        }
    }
}

void UMonsterStaggerComponent::TickDecay(float DeltaTime)
{
    if (StaggerGauge <= 0.0f) return;
    if (bStaggerTriggered) return;

    StaggerGauge = FMath::Max(0.0f,
        StaggerGauge - (DecayRate * DeltaTime));
}

bool UMonsterStaggerComponent::IsStaggered() const
{
    return StaggerGauge >= StaggerThreshold;
}

void UMonsterStaggerComponent::Reset()
{
    StaggerGauge = 0.0f;
    bStaggerTriggered = false;
}

void UMonsterStaggerComponent::SetIsInDeathZone(bool bInDeathZone)
{
    bIsInDeathZone = bInDeathZone;
}