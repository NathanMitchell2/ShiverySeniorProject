#include "WerewolfAlertnessComponent.h"

UWerewolfAlertnessComponent::UWerewolfAlertnessComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWerewolfAlertnessComponent::BeginPlay()
{
	Super::BeginPlay();

	AlertPoints = FMath::Clamp(AlertPoints, 0.f, MaxPoints);
	Stage = ComputeStage(AlertPoints);
}

void UWerewolfAlertnessComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceStimulus += DeltaTime;
	if (bEnableDecay) { ApplyDecay(DeltaTime); }
	UpdateStageIfNeeded();
}

void UWerewolfAlertnessComponent::AddAlert(float Points, FName Reason, FVector SourceLocation)
{
	if (FMath::IsNearlyZero(Points)) return;

	const float OldPoints = AlertPoints;

	AlertPoints = FMath::Clamp(AlertPoints + Points, 0.f, MaxPoints);

	TimeSinceStimulus = 0.f;
	if (!SourceLocation.IsNearlyZero())
	{
		LastStimulusLocation = SourceLocation;
	}

	const float Delta = AlertPoints - OldPoints;
	OnAlertPointsChanged.Broadcast(AlertPoints, Delta, Reason, LastStimulusLocation);

	UpdateStageIfNeeded();
}

void UWerewolfAlertnessComponent::SetAlertPoints(float NewPoints, FName Reason, FVector SourceLocation)
{
	const float OldPoints = AlertPoints;

	AlertPoints = FMath::Clamp(NewPoints, 0.f, MaxPoints);

	if (!SourceLocation.IsNearlyZero())
	{
		LastStimulusLocation = SourceLocation;
	}

	const float Delta = AlertPoints - OldPoints;
	OnAlertPointsChanged.Broadcast(AlertPoints, Delta, Reason, LastStimulusLocation);

	UpdateStageIfNeeded();
}

void UWerewolfAlertnessComponent::ResetAlert(FName Reason)
{
	SetAlertPoints(0.f, Reason, FVector::ZeroVector);
	TimeSinceStimulus = 9999.f;
}

void UWerewolfAlertnessComponent::ApplyDecay(float DeltaTime)
{
	if (AlertPoints <= 0.f) return;
	if (TimeSinceStimulus < StickyTimeAfterStimulus) return;

	const bool bHighAlert = (Stage == EAlertStage::Investigate || Stage == EAlertStage::Alerted);
	const float DecayRate = bHighAlert ? DecayPerSecond_Investigate : DecayPerSecond_Calm;

	if (DecayRate <= 0.f) return;

	const float OldPoints = AlertPoints;
	AlertPoints = FMath::Clamp(AlertPoints - DecayRate * DeltaTime, 0.f, MaxPoints);

	const float Delta = AlertPoints - OldPoints;
	if (!FMath::IsNearlyZero(Delta))
	{
		OnAlertPointsChanged.Broadcast(AlertPoints, Delta, "Decay", LastStimulusLocation);
	}
}

void UWerewolfAlertnessComponent::SetDecayEnabled(bool bEnabled)
{
	bEnableDecay = bEnabled;
}

EAlertStage UWerewolfAlertnessComponent::ComputeStage(float Points) const
{
	if (Points >= AlertedThreshold) return EAlertStage::Alerted;
	if (Points >= InvestigateThreshold) return EAlertStage::Investigate;
	if (Points >= CuriousThreshold) return EAlertStage::Curious;
	return EAlertStage::Calm;
}

void UWerewolfAlertnessComponent::UpdateStageIfNeeded()
{
	const EAlertStage OldStage = Stage;
	const EAlertStage NewStage = ComputeStage(AlertPoints);

	if (NewStage != OldStage)
	{
		Stage = NewStage;
		OnAlertStageChanged.Broadcast(NewStage, OldStage);
	}

}
