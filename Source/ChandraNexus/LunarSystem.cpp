#include "LunarSystem.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInterface.h"
#include "UObject/ConstructorHelpers.h"
ALunarSystem::ALunarSystem() {
    PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    Earth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Earth"));
    Moon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Moon"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    for (auto* Body : {Earth.Get(), Moon.Get()}) {
        Body->SetupAttachment(RootComponent);
        Body->SetStaticMesh(Sphere.Object);
        Body->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
    Earth->SetRelativeScale3D(FVector(1.2742));
    Moon->SetRelativeScale3D(FVector(0.34748));
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(RootComponent);
    Camera->SetRelativeLocation(FVector(620, -920, 620));
    Camera->SetRelativeRotation((-Camera->GetRelativeLocation()).Rotation());
    Camera->FieldOfView = 45;
    UpdateOrbit();
}
void ALunarSystem::BeginPlay() {
    Super::BeginPlay();
    if (auto* M = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Moon.M_Moon"))) Moon->SetMaterial(0, M);
    if (auto* M = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Earth.M_Earth"))) Earth->SetMaterial(0, M);
    if (auto* PC = UGameplayStatics::GetPlayerController(this, 0)) PC->SetViewTarget(this);
}
void ALunarSystem::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);
    if (!Paused) Phase = FMath::Fmod(Phase + DeltaSeconds * 2.0 * PI / FMath::Max(OrbitPeriodSeconds, 1.0), 2.0 * PI);
    UpdateOrbit();
}
void ALunarSystem::UpdateOrbit() {
    const double Radius = FMath::Max(OrbitRadius, 100.0);
    Moon->SetRelativeLocation(FVector(Radius * FMath::Cos(Phase), Radius * FMath::Sin(Phase), 0));
    // Circular, coplanar prototype; synchronous rotation keeps the same face toward Earth.
    Moon->SetRelativeRotation(FRotator(0, FMath::RadiansToDegrees(Phase) + 180, 0));
}
