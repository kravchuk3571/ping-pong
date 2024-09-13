#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputComponent.h"
#include "PaddlePawn.generated.h"

UCLASS()
class PROJECT_API APaddlePawn : public APawn
{
    GENERATED_BODY()

public:
    APaddlePawn();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void Move(const FInputActionValue& Value);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MoveSpeed;

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerMovePawn(const FVector& Movement);

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PaddleMesh;
};
