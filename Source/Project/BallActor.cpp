#include "BallActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"

ABallActor::ABallActor()
{
    PrimaryActorTick.bCanEverTick = true;

    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    RootComponent = BallMesh;

    Speed = 1200.f;
    MovementDirection = FVector(FMath::FRandRange(-1.f, 1.f), 0.f, 0.f);

    bReplicates = true;
    bAlwaysRelevant = true;
}

void ABallActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABallActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bGameStarted || !HasAuthority())
        return;

    FVector NewLocation = GetActorLocation() + (MovementDirection * Speed * DeltaTime);
    ReplicatedLocation = NewLocation;

    FHitResult Hit;
    SetActorLocation(NewLocation, true, &Hit);

    if (Hit.bBlockingHit)
    {
        MovementDirection = MovementDirection.MirrorByVector(Hit.Normal);
    }
}

void ABallActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ABallActor, ReplicatedLocation);
}

void ABallActor::StartGame()
{
    bGameStarted = true;
}

void ABallActor::OnRep_ReplicatedLocation()
{
    SetActorLocation(ReplicatedLocation);
}
