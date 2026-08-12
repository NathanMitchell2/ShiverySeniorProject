#include "MonsterSenseComponent.h"

UMonsterSenseComponent::UMonsterSenseComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMonsterSenseComponent::BeginPlay()
{
    Super::BeginPlay();

    // Initialize all sense types to 0
    for (uint8 i = 0; i <= (uint8)EMonsterSenseType::COMBINED; i++)
    {
        EMonsterSenseType Type = (EMonsterSenseType)i;
        SenseActivationLevels.Add(Type, 0.0f);
        LastTimeAboveLower.Add(Type, -999.0f);
        LastTimeAboveActivated.Add(Type, -999.0f);
        LastTimeAboveUpper.Add(Type, -999.0f);
        LastIncreaseAboveLower.Add(Type, false);
        LastIncreaseAboveActivated.Add(Type, false);
        LastIncreaseAboveUpper.Add(Type, false);
    }
}

void UMonsterSenseComponent::TickComponent(float DeltaTime,
    ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Decay all senses over time
    TArray<EMonsterSenseType> Keys;
    SenseActivationLevels.GetKeys(Keys);

    for (EMonsterSenseType SenseType : Keys)
    {
        float Current = SenseActivationLevels[SenseType];
        if (Current <= 0.0f) continue;

        float Decay = GetDecayRate(SenseType) * DeltaTime;
        float NewLevel = FMath::Max(0.0f, Current - Decay);

        // Update threshold times during decay too
        UpdateThresholdTimes(SenseType, Current, NewLevel);

        SenseActivationLevels[SenseType] = NewLevel;
    }
}

void UMonsterSenseComponent::IncreaseSense(
    EMonsterSenseType SenseType, float Amount)
{
    if (!SenseActivationLevels.Contains(SenseType)) return;

    float OldLevel = SenseActivationLevels[SenseType];
    float NewLevel = FMath::Clamp(OldLevel + Amount, 0.0f, 1.0f);
    SenseActivationLevels[SenseType] = NewLevel;

    UpdateThresholdTimes(SenseType, OldLevel, NewLevel);
}

void UMonsterSenseComponent::DecreaseSense(
    EMonsterSenseType SenseType, float Amount)
{
    if (!SenseActivationLevels.Contains(SenseType)) return;

    float Current = SenseActivationLevels[SenseType];
    SenseActivationLevels[SenseType] =
        FMath::Max(0.0f, Current - Amount);
}

bool UMonsterSenseComponent::IsSenseActivationAbove(
    EMonsterSenseType SenseType, ESenseThreshold Threshold) const
{
    if (!SenseActivationLevels.Contains(SenseType)) return false;

    float Level = SenseActivationLevels[SenseType];
    return Level >= GetThresholdValue(Threshold);
}

float UMonsterSenseComponent::GetLastTimeSensed(
    EMonsterSenseType SenseType, ESenseThreshold Threshold) const
{
    float LastTime = -999.0f;
    float CurrentTime = GetWorld()->GetTimeSeconds();

    switch (Threshold)
    {
    case ESenseThreshold::LOWER_THRESHOLD:
        if (LastTimeAboveLower.Contains(SenseType))
            LastTime = LastTimeAboveLower[SenseType];
        break;
    case ESenseThreshold::ACTIVATED_THRESHOLD:
        if (LastTimeAboveActivated.Contains(SenseType))
            LastTime = LastTimeAboveActivated[SenseType];
        break;
    case ESenseThreshold::UPPER_THRESHOLD:
        if (LastTimeAboveUpper.Contains(SenseType))
            LastTime = LastTimeAboveUpper[SenseType];
        break;
    }

    if (LastTime < 0.0f) return 999.0f;
    return CurrentTime - LastTime;
}

bool UMonsterSenseComponent::WasSenseThresholdLastIncreaseAbove(
    EMonsterSenseType SenseType, ESenseThreshold Threshold) const
{
    switch (Threshold)
    {
    case ESenseThreshold::LOWER_THRESHOLD:
        return LastIncreaseAboveLower.Contains(SenseType)
            && LastIncreaseAboveLower[SenseType];
    case ESenseThreshold::ACTIVATED_THRESHOLD:
        return LastIncreaseAboveActivated.Contains(SenseType)
            && LastIncreaseAboveActivated[SenseType];
    case ESenseThreshold::UPPER_THRESHOLD:
        return LastIncreaseAboveUpper.Contains(SenseType)
            && LastIncreaseAboveUpper[SenseType];
    }
    return false;
}

float UMonsterSenseComponent::GetSenseLevel(
    EMonsterSenseType SenseType) const
{
    if (!SenseActivationLevels.Contains(SenseType)) return 0.0f;
    return SenseActivationLevels[SenseType];
}

void UMonsterSenseComponent::ResetSense(EMonsterSenseType SenseType)
{
    if (SenseActivationLevels.Contains(SenseType))
        SenseActivationLevels[SenseType] = 0.0f;
}

void UMonsterSenseComponent::ResetAllSenses()
{
    TArray<EMonsterSenseType> Keys;
    SenseActivationLevels.GetKeys(Keys);
    for (EMonsterSenseType Key : Keys)
        SenseActivationLevels[Key] = 0.0f;
}

void UMonsterSenseComponent::UpdateLampSense(float LampIntensity)
{
    // Lamp sense is driven directly by intensity
    // not through the normal increase/decay system
    if (SenseActivationLevels.Contains(EMonsterSenseType::SEE_LAMP))
    {
        float OldLevel =
            SenseActivationLevels[EMonsterSenseType::SEE_LAMP];
        float NewLevel = FMath::Clamp(LampIntensity, 0.0f, 1.0f);
        SenseActivationLevels[EMonsterSenseType::SEE_LAMP] = NewLevel;
        UpdateThresholdTimes(
            EMonsterSenseType::SEE_LAMP, OldLevel, NewLevel);
    }
}

float UMonsterSenseComponent::GetThresholdValue(
    ESenseThreshold Threshold) const
{
    switch (Threshold)
    {
    case ESenseThreshold::LOWER_THRESHOLD:     return LowerThreshold;
    case ESenseThreshold::ACTIVATED_THRESHOLD: return ActivatedThreshold;
    case ESenseThreshold::UPPER_THRESHOLD:     return UpperThreshold;
    }
    return ActivatedThreshold;
}

float UMonsterSenseComponent::GetDecayRate(
    EMonsterSenseType SenseType) const
{
    switch (SenseType)
    {
    case EMonsterSenseType::VISUAL:
        return VisualDecayRate;
    case EMonsterSenseType::DAMAGED_BY_EXPLOSION:
        return ExplosionDecayRate;
    default:
        return DefaultDecayRate;
    }
}

void UMonsterSenseComponent::UpdateThresholdTimes(
    EMonsterSenseType SenseType, float OldLevel, float NewLevel)
{
    float CurrentTime = GetWorld()->GetTimeSeconds();

    // Lower threshold
    bool bIsAboveLower = NewLevel >= LowerThreshold;
    if (bIsAboveLower)
        LastTimeAboveLower[SenseType] = CurrentTime;
    // Stay true as long as above threshold
    LastIncreaseAboveLower[SenseType] = bIsAboveLower;

    // Activated threshold
    bool bIsAboveActivated = NewLevel >= ActivatedThreshold;
    if (bIsAboveActivated)
        LastTimeAboveActivated[SenseType] = CurrentTime;
    LastIncreaseAboveActivated[SenseType] = bIsAboveActivated;

    // Upper threshold
    bool bIsAboveUpper = NewLevel >= UpperThreshold;
    if (bIsAboveUpper)
        LastTimeAboveUpper[SenseType] = CurrentTime;
    LastIncreaseAboveUpper[SenseType] = bIsAboveUpper;
}