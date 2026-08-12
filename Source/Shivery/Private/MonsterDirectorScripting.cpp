#include "MonsterDirectorScripting.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Misc/OutputDeviceNull.h"   

AActor* UMonsterDirectorScripting::FindMonsterDirector(UObject* WorldContextObject)
{
    if (!WorldContextObject) return nullptr;
    UWorld* World = WorldContextObject->GetWorld();
    if (!World) return nullptr;

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(
        World, FName("MonsterDirector"), FoundActors);

    return FoundActors.Num() > 0 ? FoundActors[0] : nullptr;
}

void UMonsterDirectorScripting::ForceDirectorState(
    UObject* WorldContextObject, EDirectorState NewState)
{
    AActor* Director = FindMonsterDirector(WorldContextObject);
    if (!Director)
    {
        UE_LOG(LogTemp, Warning, TEXT("[MonsterScripting] Director not found"));
        return;
    }

    // Call BP function "TransitionToState" via dynamic Blueprint dispatch
    FOutputDeviceNull OutputDevice;
    FString Command = FString::Printf(TEXT("TransitionToState %d"),
        static_cast<int32>(NewState));
    Director->CallFunctionByNameWithArguments(*Command, OutputDevice, nullptr, true);
}

void UMonsterDirectorScripting::LockDirectorState(
    UObject* WorldContextObject, bool bLock)
{
    AActor* Director = FindMonsterDirector(WorldContextObject);
    if (!Director) return;

    // Set bScriptLocked variable directly via property
    FBoolProperty* LockProperty = FindFProperty<FBoolProperty>(
        Director->GetClass(), TEXT("bScriptLocked"));
    if (LockProperty)
    {
        LockProperty->SetPropertyValue_InContainer(Director, bLock);
    }
}

void UMonsterDirectorScripting::ReleaseDirector(UObject* WorldContextObject)
{
    LockDirectorState(WorldContextObject, false);
    ForceDirectorState(WorldContextObject, EDirectorState::STALKING);
}

EDirectorState UMonsterDirectorScripting::GetCurrentDirectorState(
    UObject* WorldContextObject)
{
    AActor* Director = FindMonsterDirector(WorldContextObject);
    if (!Director) return EDirectorState::DORMANT;

    FByteProperty* StateProperty = FindFProperty<FByteProperty>(
        Director->GetClass(), TEXT("CurrentDirectorState"));
    if (StateProperty)
    {
        uint8 Value = StateProperty->GetPropertyValue_InContainer(Director);
        return static_cast<EDirectorState>(Value);
    }
    return EDirectorState::DORMANT;
}

void UMonsterDirectorScripting::ForceSpawnAt(
    UObject* WorldContextObject, AActor* SpawnPoint)
{
    AActor* Director = FindMonsterDirector(WorldContextObject);
    if (!Director || !SpawnPoint) return;

    // Find monster pawn
    UWorld* World = WorldContextObject->GetWorld();
    if (!World) return;

    TArray<AActor*> Monsters;
    UGameplayStatics::GetAllActorsWithTag(
        World, FName("Monster"), Monsters);

    if (Monsters.Num() == 0) return;

    AActor* Monster = Monsters[0];
    Monster->SetActorLocation(SpawnPoint->GetActorLocation());
    Monster->SetActorRotation(SpawnPoint->GetActorRotation());
    Monster->SetActorHiddenInGame(false);
    Monster->SetActorEnableCollision(true);
}

void UMonsterDirectorScripting::ForceDespawnNow(UObject* WorldContextObject)
{
    ForceDirectorState(WorldContextObject, EDirectorState::DORMANT);
}

void UMonsterDirectorScripting::TeleportMonsterTo(
    UObject* WorldContextObject, FVector Location)
{
    UWorld* World = WorldContextObject->GetWorld();
    if (!World) return;

    TArray<AActor*> Monsters;
    UGameplayStatics::GetAllActorsWithTag(
        World, FName("Monster"), Monsters);

    if (Monsters.Num() > 0)
    {
        Monsters[0]->SetActorLocation(Location);
    }
}

void UMonsterDirectorScripting::ForceTargetActor(
    UObject* WorldContextObject, AActor* NewTarget)
{
    UWorld* World = WorldContextObject->GetWorld();
    if (!World || !NewTarget) return;

    TArray<AActor*> Monsters;
    UGameplayStatics::GetAllActorsWithTag(
        World, FName("Monster"), Monsters);

    if (Monsters.Num() == 0) return;

    ACharacter* Monster = Cast<ACharacter>(Monsters[0]);
    if (!Monster) return;

    AAIController* AIC = Cast<AAIController>(Monster->GetController());
    if (!AIC) return;

    UBlackboardComponent* BB = AIC->GetBlackboardComponent();
    if (!BB) return;

    BB->SetValueAsObject(FName("TargetActor"), NewTarget);
    BB->SetValueAsVector(FName("LastKnownPosition"),
        NewTarget->GetActorLocation());
}

void UMonsterDirectorScripting::ForceMoveTo(
    UObject* WorldContextObject, FVector Location, bool bRunSpeed)
{
    UWorld* World = WorldContextObject->GetWorld();
    if (!World) return;

    TArray<AActor*> Monsters;
    UGameplayStatics::GetAllActorsWithTag(
        World, FName("Monster"), Monsters);

    if (Monsters.Num() == 0) return;

    ACharacter* Monster = Cast<ACharacter>(Monsters[0]);
    if (!Monster) return;

    AAIController* AIC = Cast<AAIController>(Monster->GetController());
    if (!AIC) return;

    AIC->MoveToLocation(Location, 50.0f, true, true, false, true);

    // Set speed
    if (Monster->GetCharacterMovement())
    {
        Monster->GetCharacterMovement()->MaxWalkSpeed = bRunSpeed ? 600.0f : 250.0f;
    }
}

void UMonsterDirectorScripting::ForceAttackPlayer(
    UObject* WorldContextObject, bool bIgnoreCooldowns)
{
    AActor* Director = FindMonsterDirector(WorldContextObject);
    if (!Director) return;

    ForceDirectorState(WorldContextObject, EDirectorState::HUNTING);

    if (bIgnoreCooldowns)
    {
        // Find monster and reset attack cooldowns via BB
        UWorld* World = WorldContextObject->GetWorld();
        if (!World) return;

        TArray<AActor*> Monsters;
        UGameplayStatics::GetAllActorsWithTag(
            World, FName("Monster"), Monsters);

        if (Monsters.Num() == 0) return;

        ACharacter* Monster = Cast<ACharacter>(Monsters[0]);
        if (!Monster) return;

        AAIController* AIC = Cast<AAIController>(Monster->GetController());
        if (!AIC) return;

        UBlackboardComponent* BB = AIC->GetBlackboardComponent();
        if (BB)
        {
            BB->SetValueAsFloat(FName("Attack_Ban_Timer"), 0.0f);
        }
    }
}

void UMonsterDirectorScripting::ForceMonsterSeesPlayer(
    UObject* WorldContextObject, float Duration)
{
    UWorld* World = WorldContextObject->GetWorld();
    if (!World) return;

    TArray<AActor*> Monsters;
    UGameplayStatics::GetAllActorsWithTag(
        World, FName("Monster"), Monsters);

    if (Monsters.Num() == 0) return;

    ACharacter* Monster = Cast<ACharacter>(Monsters[0]);
    if (!Monster) return;

    AAIController* AIC = Cast<AAIController>(Monster->GetController());
    if (!AIC) return;

    UBlackboardComponent* BB = AIC->GetBlackboardComponent();
    if (!BB) return;

    // Find player and set as target
    APawn* Player = UGameplayStatics::GetPlayerPawn(World, 0);
    if (Player)
    {
        BB->SetValueAsObject(FName("TargetActor"), Player);
        BB->SetValueAsVector(FName("LastKnownPosition"),
            Player->GetActorLocation());
    }
}

void UMonsterDirectorScripting::ForceMonsterIgnoresPlayer(
    UObject* WorldContextObject, float Duration)
{
    UWorld* World = WorldContextObject->GetWorld();
    if (!World) return;

    TArray<AActor*> Monsters;
    UGameplayStatics::GetAllActorsWithTag(
        World, FName("Monster"), Monsters);

    if (Monsters.Num() == 0) return;

    ACharacter* Monster = Cast<ACharacter>(Monsters[0]);
    if (!Monster) return;

    AAIController* AIC = Cast<AAIController>(Monster->GetController());
    if (!AIC) return;

    UBlackboardComponent* BB = AIC->GetBlackboardComponent();
    if (!BB) return;

    BB->ClearValue(FName("TargetActor"));
}

void UMonsterDirectorScripting::SetMonsterCinematicMode(
    UObject* WorldContextObject, bool bEnabled)
{
    UWorld* World = WorldContextObject->GetWorld();
    if (!World) return;

    TArray<AActor*> Monsters;
    UGameplayStatics::GetAllActorsWithTag(
        World, FName("Monster"), Monsters);

    if (Monsters.Num() == 0) return;

    ACharacter* Monster = Cast<ACharacter>(Monsters[0]);
    if (!Monster) return;

    AAIController* AIC = Cast<AAIController>(Monster->GetController());
    if (!AIC) return;

    UBlackboardComponent* BB = AIC->GetBlackboardComponent();
    if (!BB) return;

    BB->SetValueAsBool(FName("Has_Script"), bEnabled);
}

void UMonsterDirectorScripting::PlayMontageOnMonster(
    UObject* WorldContextObject, UAnimMontage* Montage)
{
    if (!Montage) return;

    UWorld* World = WorldContextObject->GetWorld();
    if (!World) return;

    TArray<AActor*> Monsters;
    UGameplayStatics::GetAllActorsWithTag(
        World, FName("Monster"), Monsters);

    if (Monsters.Num() == 0) return;

    ACharacter* Monster = Cast<ACharacter>(Monsters[0]);
    if (!Monster || !Monster->GetMesh()) return;

    UAnimInstance* AnimInst = Monster->GetMesh()->GetAnimInstance();
    if (AnimInst)
    {
        AnimInst->Montage_Play(Montage);
    }
}