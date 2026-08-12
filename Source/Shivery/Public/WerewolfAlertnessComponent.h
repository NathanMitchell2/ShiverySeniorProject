#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WerewolfAlertnessComponent.generated.h"

UENUM(BlueprintType)
enum class EAlertStage : uint8
{
	Calm        UMETA(DisplayName = "Calm"),
	Curious     UMETA(DisplayName = "Curious"),
	Investigate UMETA(DisplayName = "Investigate"),
	Alerted     UMETA(DisplayName = "Alerted"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(
	FOnAlertPointsChanged,
	float, NewPoints,
	float, DeltaPoints,
	FName, Reason,
	FVector, SourceLocation
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnAlertStageChanged,
	EAlertStage, NewStage,
	EAlertStage, OldStage
);

UCLASS(ClassGroup = (AI), meta = (BlueprintSpawnableComponent))
class SHIVERY_API UWerewolfAlertnessComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWerewolfAlertnessComponent();

	UFUNCTION(BlueprintCallable, Category = "Alert")
	void AddAlert(float Points, FName Reason = "Unknown", FVector SourceLocation = FVector::ZeroVector);

	UFUNCTION(BlueprintCallable, Category = "Alert")
	void SetAlertPoints(float NewPoints, FName Reason = "Set", FVector SourceLocation = FVector::ZeroVector);

	UFUNCTION(BlueprintCallable, Category = "Alert")
	void ResetAlert(FName Reason = "Reset");

	UFUNCTION(BlueprintPure, Category = "Alert")
	float GetAlertPoints() const { return AlertPoints; }

	UFUNCTION(BlueprintCallable, Category = "Alert|Decay")
	void SetDecayEnabled(bool bEnabled);

	UFUNCTION(BlueprintPure, Category = "Alert")
	EAlertStage GetStage() const { return Stage; }

	UPROPERTY(BlueprintAssignable, Category = "Alert|Events")
	FOnAlertPointsChanged OnAlertPointsChanged;

	UPROPERTY(BlueprintAssignable, Category = "Alert|Events")
	FOnAlertStageChanged OnAlertStageChanged;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ---- Tunables (edit in BP defaults) ----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert|Tuning", meta = (ClampMin = "0.0"))
	float MaxPoints = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert|Thresholds", meta = (ClampMin = "0.0"))
	float CuriousThreshold = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert|Thresholds", meta = (ClampMin = "0.0"))
	float InvestigateThreshold = 70.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert|Thresholds", meta = (ClampMin = "0.0"))
	float AlertedThreshold = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert|Decay", meta = (ClampMin = "0.0"))
	float DecayPerSecond_Calm = 4.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert|Decay", meta = (ClampMin = "0.0"))
	float DecayPerSecond_Investigate = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert|Decay", meta = (ClampMin = "0.0"))
	float StickyTimeAfterStimulus = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Alert|Decay")
	bool bEnableDecay = true;

	// ---- Runtime state ----
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Alert")
	float AlertPoints = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Alert")
	EAlertStage Stage = EAlertStage::Calm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Alert")
	FVector LastStimulusLocation = FVector::ZeroVector;

private:
	float TimeSinceStimulus = 9999.f;

	void ApplyDecay(float DeltaTime);
	void UpdateStageIfNeeded();
	EAlertStage ComputeStage(float Points) const;
};