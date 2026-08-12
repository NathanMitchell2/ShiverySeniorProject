#include "MonsterTrapComponent.h"
#include "MonsterMotivationComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UMonsterTrapComponent::UMonsterTrapComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMonsterTrapComponent::BeginPlay()
{
    Super::BeginPlay();

    MotivationComponent = GetOwner()->
        FindComponentByClass<UMonsterMotivationComponent>();

    ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
    if (OwnerCharacter)
    {
        MovementComponent = OwnerCharacter->GetCharacterMovement();
        if (MovementComponent)
        {
            OriginalMaxWalkSpeed = MovementComponent->MaxWalkSpeed;
        }
    }

    AIController = Cast<AAIController>(
        Cast<APawn>(GetOwner())->GetController());
}

void UMonsterTrapComponent::TickComponent(float DeltaTime,
    ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMonsterTrapComponent::TriggerTrap()
{
    if (bIsTrapped || bIsBanned) return;

    bIsTrapped = true;

    // Freeze movement completely
    if (MovementComponent)
    {
        MovementComponent->MaxWalkSpeed = 0.0f;
        MovementComponent->StopMovementImmediately();
    }

    // Set BB keys
    if (AIController)
    {
        UBlackboardComponent* BB = AIController->
            FindComponentByClass<UBlackboardComponent>();
        if (BB)
        {
            BB->SetValueAsBool(FName("IS_TRAPPED"), true);
            BB->SetValueAsBool(FName("SHOULD_FREEZE"), true);
        }
    }

    // Fire event for Blueprint — play trap animation + sound
    OnTrapTriggered.Broadcast();

    // Start duration timer
    GetWorld()->GetTimerManager().SetTimer(
        TrapDurationHandle,
        this,
        &UMonsterTrapComponent::OnTrapExpired,
        TrapDuration,
        false
    );
}

void UMonsterTrapComponent::OnTrapExpired()
{
    bIsTrapped = false;
    bIsBanned = true;

    // Restore movement
    if (MovementComponent)
    {
        MovementComponent->MaxWalkSpeed = OriginalMaxWalkSpeed;
    }

    // Clear BB keys
    if (AIController)
    {
        UBlackboardComponent* BB = AIController->
            FindComponentByClass<UBlackboardComponent>();
        if (BB)
        {
            BB->SetValueAsBool(FName("IS_TRAPPED"), false);
            BB->SetValueAsBool(FName("SHOULD_FREEZE"), false);
        }
    }

    // Fire recovery event for Blueprint — play recovery animation + roar
    OnTrapExpiredDelegate.Broadcast();

    // Add breakout motivation — monster wants to leave after being freed
    if (MotivationComponent)
    {
        MotivationComponent->AddMotivation(
            EMonsterMotivation::BREAKOUT, 80);
    }

    // Start ban timer — prevents immediate re-trapping
    GetWorld()->GetTimerManager().SetTimer(
        TrapBanHandle,
        [this]() { bIsBanned = false; },
        TrapBanDuration,
        false
    );
}

bool UMonsterTrapComponent::IsTrapped() const
{
    return bIsTrapped;
}

bool UMonsterTrapComponent::CanBeTrapped() const
{
    return !bIsTrapped && !bIsBanned;
}