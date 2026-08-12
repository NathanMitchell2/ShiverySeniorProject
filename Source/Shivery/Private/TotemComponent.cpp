#include "TotemComponent.h"
#include "Kismet/GameplayStatics.h"

UTotemComponent::UTotemComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTotemComponent::BeginPlay()
{
    Super::BeginPlay();
    bIsTotemActive = true;

    // Find director by tag and notify via Blueprint event
    TArray<AActor*> Directors;
    UGameplayStatics::GetAllActorsWithTag(
        GetWorld(),
        FName("MonsterDirector"),
        Directors
    );

    if (Directors.Num() > 0)
    {
        DirectorRef = Directors[0];
        OnRegisteredWithDirector(DirectorRef);

        // Start expiry timer
        GetWorld()->GetTimerManager().SetTimer(
            LureDurationHandle,
            this,
            &UTotemComponent::OnLureDurationExpired,
            LureDuration,
            false
        );
    }
    else
    {
        UE_LOG(LogTemp, Warning,
            TEXT("TotemComponent: No actor with tag MonsterDirector found!"));
    }
}

void UTotemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    if (bIsTotemActive) DeactivateTotem();
    GetWorld()->GetTimerManager().ClearTimer(LureDurationHandle);
}

void UTotemComponent::OnLureDurationExpired()
{
    bIsTotemActive = false;
    if (DirectorRef) OnClearFromDirector(DirectorRef);
    OnTotemExpired.Broadcast();
}

void UTotemComponent::OnMonsterReachedTotem()
{
    bIsTotemActive = false;
    if (DirectorRef) OnClearFromDirector(DirectorRef);
    OnTotemReached.Broadcast();
}

void UTotemComponent::DeactivateTotem()
{
    if (!bIsTotemActive) return;
    bIsTotemActive = false;
    GetWorld()->GetTimerManager().ClearTimer(LureDurationHandle);
    if (DirectorRef) OnClearFromDirector(DirectorRef);
}

bool UTotemComponent::IsTotemActive() const
{
    return bIsTotemActive;
}