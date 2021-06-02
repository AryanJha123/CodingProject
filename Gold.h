// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharPawn.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Gold.generated.h"

UCLASS()
class TAKE3_API AGold : public AActor
{
    GENERATED_BODY()
    
public:
    // Sets default values for this actor's properties
    AGold();
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    ACharPawn * CharPawn;
    
    UFUNCTION( )
    void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
                      AActor* OtherActor,
                      UPrimitiveComponent* OtherComp,
                      int32 OtherBodyIndex,
                      bool bFromSweep,
                      const FHitResult &SweepResult );
    
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* Coin;
    UPROPERTY(EditAnywhere)
    UCapsuleComponent* TriggerBox;
    
};
