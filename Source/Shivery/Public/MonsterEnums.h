// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterEnums.generated.h"


UENUM(BlueprintType)
enum class EMonsterMotivation : uint8
{
    NONE                        UMETA(DisplayName = "None"),
    ATTACK                      UMETA(DisplayName = "Attack"),
    THREAT_AWARE                UMETA(DisplayName = "Threat Aware"),
    STALK                       UMETA(DisplayName = "Stalk"),
    BACKSTAGE_STALK             UMETA(DisplayName = "Backstage Stalk"),
    CINEMATIC                   UMETA(DisplayName = "Cinematic"),
    SHOT                        UMETA(DisplayName = "Shot"),
    STUN_DAMAGE                 UMETA(DisplayName = "Stun Damage"),
    BREAKOUT                    UMETA(DisplayName = "Breakout"),
    AMBUSH                      UMETA(DisplayName = "Ambush"),
    DESPAWN                     UMETA(DisplayName = "Despawn"),
    TOTEM                       UMETA(DisplayName = "Totem - investigate/destroy"),
    SEARCH_SYSTEMATIC           UMETA(DisplayName = "Search Systematic"),
    SUSPICIOUS_ITEM             UMETA(DisplayName = "Suspicious Item"),
    PLAYER_HIDE                 UMETA(DisplayName = "Player Hide"),
    SUSPECT_TARGET_RESPONSE     UMETA(DisplayName = "Suspect Target Response"),
    TRAPPED_MOTIVATION          UMETA(DisplayName = "Trapped"),
    EXPLOSION_REACTION_MOTIVATION  UMETA(DisplayName = "Explosion Reaction"),
    PATROL                      UMETA(DisplayName = "Patrol"),
    WITHDRAW                    UMETA(DisplayName = "Withdraw")
};

UENUM(BlueprintType)
enum class EWithdrawState : uint8
{
    NOT_WITHDRAWING     UMETA(DisplayName = "Not Withdrawing"),
    WITHDRAWING         UMETA(DisplayName = "Withdrawing"),
    NEEDS_TO_WITHDRAW   UMETA(DisplayName = "Needs To Withdraw")
};

UENUM(BlueprintType)
enum class EMonsterRole : uint8
{
    IDLE        UMETA(DisplayName = "Idle"),
    PATROL      UMETA(DisplayName = "Patrol"),
    STALK       UMETA(DisplayName = "Stalk"),
    HUNT        UMETA(DisplayName = "Hunt")
};

UENUM(BlueprintType)
enum class EDirectorConfig : uint8
{
    PASSIVE     UMETA(DisplayName = "Passive"),
    ROAMING     UMETA(DisplayName = "Roaming"),
    HUNTING     UMETA(DisplayName = "Hunting"),
    AGGRESSIVE  UMETA(DisplayName = "Aggressive"),
    SCRIPTED    UMETA(DisplayName = "Scripted")
};

UENUM(BlueprintType)
enum class EAwarenessState : uint8
{
    UNAWARE     UMETA(DisplayName = "Unaware"),
    SUSPICIOUS  UMETA(DisplayName = "Suspicious"),
    ALERT       UMETA(DisplayName = "Alert")
};

UENUM(BlueprintType)
enum class ESenseThreshold : uint8
{
    LOWER_THRESHOLD     UMETA(DisplayName = "Lower Threshold"),
    ACTIVATED_THRESHOLD  UMETA(DisplayName = "Activated Threshold"),
    UPPER_THRESHOLD       UMETA(DisplayName = "Upper Threshold")
};

UENUM(BlueprintType)
enum class ESuspiciousItemStage : uint8
{
    NONE                  UMETA(DisplayName = "None"),
    INITIAL_REACTION      UMETA(DisplayName = "Initial Reaction"),
    MOVE_CLOSE_TO         UMETA(DisplayName = "Move Close To"),
    CLOSE_TO_REACTION     UMETA(DisplayName = "Close to Reaction"),
    SEARCH_AREA           UMETA(DisplayName = "Search Area")
};

UENUM(BlueprintType)
enum class EMonsterSenseType : uint8
{
    VISUAL                UMETA(DisplayName = "Visual"),
    HEARD_MOVEMENT        UMETA(DisplayName = "Heard Movement"),
    HEARD_COMBAT          UMETA(DisplayName = "Heard Combat"),
    TOUCHED               UMETA(DisplayName = "Touched"),
    DAMAGED_BY_EXPLOSION  UMETA(DisplayName = "Damaged By Explosion"),
    SEE_LAMP              UMETA(DisplayName = "See Lamp"),
    COMBINED              UMETA(DisplayName = "Combined")
};

UENUM(BlueprintType)
enum class EDirectorState : uint8
{
    DORMANT       UMETA(DisplayName = "Dormant - offscreen"),
    STALKING      UMETA(DisplayName = "Stalking - distant patrol"),
    HUNTING       UMETA(DisplayName = "Hunting - active pursuit"),
    SCRIPTED      UMETA(DisplayName = "Scripted - designer override"),
    RETREAT       UMETA(DisplayName = "Retreat - withdrawing"),
    PATROL        UMETA(DisplayName = "Patrol - Wandering")
};

UENUM(BlueprintType)
enum class EMonsterSpawnIntent : uint8
{
    STALK_DISTANT     UMETA(DisplayName = "Distant glimpse"),
    STALK_NEAR        UMETA(DisplayName = "Close pressure"),
    AMBUSH            UMETA(DisplayName = "Surprise ambush"),
    SCRIPTED_REVEAL   UMETA(DisplayName = "Cinematic reveal"),
    RETREAT_EXIT      UMETA(DisplayName = "Retreat point"),
    PATROL_FAR  UMETA(DisplayName = "Patrol Far - distant spawn for wandering")
};

