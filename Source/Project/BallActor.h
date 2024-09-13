#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallActor.generated.h"

UCLASS()
class PROJECT_API ABallActor : public AActor
{
    GENERATED_BODY()

public:
    ABallActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    
    void StartGame();

    UFUNCTION()
    void OnRep_ReplicatedLocation();

    UPROPERTY(Replicated)
    bool bGameStarted = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ball")
    float Speed;

    FVector MovementDirection;

    UPROPERTY(ReplicatedUsing = OnRep_ReplicatedLocation)
    FVector ReplicatedLocation;

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* BallMesh;
};
