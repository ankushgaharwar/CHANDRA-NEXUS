#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LunarSystem.generated.h"
class UStaticMeshComponent;
class UCameraComponent;
UCLASS()
class CHANDRANEXUS_API ALunarSystem : public AActor {
    GENERATED_BODY()
public:
    ALunarSystem();
    virtual void Tick(float DeltaSeconds) override;
    // Presentation scale: one Unreal unit = 100 km. Distance is compressed for visibility.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Orbit", meta=(ClampMin="100"))
    double OrbitRadius = 350.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Orbit", meta=(ClampMin="1"))
    double OrbitPeriodSeconds = 120.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Orbit")
    bool Paused = false;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> Earth;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UStaticMeshComponent> Moon;
    UPROPERTY(VisibleAnywhere) TObjectPtr<UCameraComponent> Camera;
protected:
    virtual void BeginPlay() override;
private:
    double Phase = 0.0;
    void UpdateOrbit();
};
