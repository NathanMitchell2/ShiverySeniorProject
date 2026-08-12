#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MonsterEnums.h"
#include "TotemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTotemExpired);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTotemReached);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHIVERY_API UTotemComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTotemComponent();

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    // Call when monster reaches totem position
    UFUNCTION(BlueprintCallable, Category = "Totem")
    void OnMonsterReachedTotem();

    // Manually deactivate totem
    UFUNCTION(BlueprintCallable, Category = "Totem")
    void DeactivateTotem();

    // Is totem currently active?
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Totem")
    bool IsTotemActive() const;

    // Called by Blueprint after RegisterWithDirector finds the director
    UFUNCTION(BlueprintImplementableEvent, Category = "Totem")
    void OnRegisteredWithDirector(AActor* Director);

    // Called by Blueprint to clear from director
    UFUNCTION(BlueprintImplementableEvent, Category = "Totem")
    void OnClearFromDirector(AActor* Director);

    // How far totem attracts monster
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Totem")
    float LureRadius = 2000.0f;

    // How long totem stays active before expiring
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Totem")
    float LureDuration = 30.0f;

    // Priority given to TOTEM_MOTIVATION
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Totem")
    int32 LurePriority = 4;

    // Fired when totem expires naturally
    UPROPERTY(BlueprintAssignable, Category = "Totem")
    FOnTotemExpired OnTotemExpired;

    // Fired when monster reaches totem
    UPROPERTY(BlueprintAssignable, Category = "Totem")
    FOnTotemReached OnTotemReached;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Totem")
    bool bIsTotemActive = false;

private:
    void OnLureDurationExpired();
    FTimerHandle LureDurationHandle;
    AActor* DirectorRef = nullptr;
};