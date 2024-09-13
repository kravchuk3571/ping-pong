#include "PaddlePawn.h"

APaddlePawn::APaddlePawn()
{
    PrimaryActorTick.bCanEverTick = true;

    PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
    RootComponent = PaddleMesh;

    MoveSpeed = 500.f;

    bReplicates = true;
    bAlwaysRelevant = true;
}

void APaddlePawn::BeginPlay()
{
    Super::BeginPlay();
}

void APaddlePawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APaddlePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APaddlePawn::ServerMovePawn_Implementation(const FVector& Movement)
{
    AddActorLocalOffset(Movement, true);
}

bool APaddlePawn::ServerMovePawn_Validate(const FVector& Movement)
{
    return true;
}

void APaddlePawn::Move(const FInputActionValue& Value)
{
    const float MovementValue = Value.Get<float>();
    const FVector Movement(0.f, MovementValue * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0.f);
    AddActorLocalOffset(Movement, true);
    ServerMovePawn(Movement);
}
