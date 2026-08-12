#include "MonsterMotivationComponent.h"
#include "Algo/Sort.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"

UMonsterMotivationComponent::UMonsterMotivationComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMonsterMotivationComponent::OnBreakoutTriggered()
{
    RemoveMotivation(EMonsterMotivation::ATTACK);
    RemoveMotivation(EMonsterMotivation::THREAT_AWARE);
    RemoveMotivation(EMonsterMotivation::SUSPECT_TARGET_RESPONSE);
}

void UMonsterMotivationComponent::UpdateBlackboardMotivation()
{
    AAIController* AIC = Cast<AAIController>(
        Cast<APawn>(GetOwner())->GetController());
    if (!AIC) return;

    UBlackboardComponent* BB = AIC->GetBlackboardComponent();
    if (!BB) return;

    EMonsterMotivation Active = GetActiveMotivation();
    BB->SetValueAsEnum(FName("ActiveMotivation"), (uint8)Active);
}

void UMonsterMotivationComponent::AddMotivation(EMonsterMotivation Motivation, int32 Priority)
{
    // Don't add duplicates — update priority if already exists
    for (FMotivationEntry& Entry : ActiveMotivations)
    {
        if (Entry.Motivation == Motivation)
        {
            Entry.Priority = Priority;
            // Re-sort after priority change
            Algo::Sort(ActiveMotivations, [](const FMotivationEntry& A, const FMotivationEntry& B)
                {
                    return A.Priority > B.Priority;
                });
            return;
        }
    }

    // Add new entry
    FMotivationEntry NewEntry;
    NewEntry.Motivation = Motivation;
    NewEntry.Priority = Priority;
    ActiveMotivations.Add(NewEntry);

    // Sort by priority descending — highest first
    Algo::Sort(ActiveMotivations, [](const FMotivationEntry& A, const FMotivationEntry& B)
        {
            return A.Priority > B.Priority;
        });

    if (Motivation == EMonsterMotivation::BREAKOUT)
    {
        OnBreakoutTriggered();
    }
    BroadcastActiveMotivation();
}

void UMonsterMotivationComponent::RemoveMotivation(EMonsterMotivation Motivation)
{
    ActiveMotivations.RemoveAll([Motivation](const FMotivationEntry& Entry)
        {
            return Entry.Motivation == Motivation;
        });
    BroadcastActiveMotivation();
}

bool UMonsterMotivationComponent::HasMotivation(EMonsterMotivation Motivation) const
{
    for (const FMotivationEntry& Entry : ActiveMotivations)
    {
        if (Entry.Motivation == Motivation)
        {
            return true;
        }
    }
    return false;
}

EMonsterMotivation UMonsterMotivationComponent::GetActiveMotivation() const
{
    if (ActiveMotivations.Num() > 0)
    {
        return ActiveMotivations[0].Motivation;
    }
    return EMonsterMotivation::NONE;
}

TArray<FMotivationEntry> UMonsterMotivationComponent::GetAllMotivations() const
{
    return ActiveMotivations;
}

void UMonsterMotivationComponent::ClearAllMotivations()
{
    ActiveMotivations.Empty();
    BroadcastActiveMotivation();
}

void UMonsterMotivationComponent::UpdateAnimInstanceMotivation()
{
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (!OwnerPawn) return;

    ACharacter* OwnerChar = Cast<ACharacter>(OwnerPawn);
    if (!OwnerChar) return;

    USkeletalMeshComponent* Mesh = OwnerChar->GetMesh();
    if (!Mesh) return;

    UAnimInstance* AnimInst = Mesh->GetAnimInstance();
    if (!AnimInst) return;

    EMonsterMotivation Active = GetActiveMotivation();

    FProperty* Prop = AnimInst->GetClass()->FindPropertyByName(FName("CurrentMotivation"));
    if (FByteProperty* ByteProp = CastField<FByteProperty>(Prop))
    {
        uint8* ValuePtr = ByteProp->ContainerPtrToValuePtr<uint8>(AnimInst);
        *ValuePtr = (uint8)Active;
    }
    else if (FEnumProperty* EnumProp = CastField<FEnumProperty>(Prop))
    {
        void* ValuePtr = EnumProp->ContainerPtrToValuePtr<void>(AnimInst);
        EnumProp->GetUnderlyingProperty()->SetIntPropertyValue(ValuePtr, (int64)Active);
    }
}

void UMonsterMotivationComponent::BroadcastActiveMotivation()
{
    UpdateBlackboardMotivation();
    UpdateAnimInstanceMotivation();
}
