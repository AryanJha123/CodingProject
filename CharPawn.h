// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "CharPawn.generated.h"

UCLASS()
class TAKE3_API ACharPawn : public APawn
{
    GENERATED_BODY()
    
public:
    // Sets default values for this pawn's properties
    ACharPawn();
    
protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
        
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* VisibleActor;
    
    UPROPERTY(EditAnywhere)
    UPawnMovementComponent* CharMove;
    
    void MoveX(float AxisValue);
    void MoveY(float AxisValue);
    void MoveZ(float AxisValue);
    void AddCoins();
    
    
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Score;
    
    FRotator armRot;
    FRotator ObjRot;
    FRotator relativeRot;
    
    FVector CurrentVelocity;
    FVector ForwardVelocity;
    FVector BackVelocity;
    FVector ActorLocation;
    FVector VelocityGoBrr;
    FVector NewLocation;
    FVector ImpulseLocation;
    FVector ForwardVector;
    FVector OffsetVector;
    
    bool goingForward;
    //bGenerateOverlapEvents = true;
    
    void Heal();
    void NoHeal();
    
    float clampvalue = 0.0f;
    float MovementSpeed = 5.0f;
    float HealthUp = 10.0f;
    float ImpulseValue;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float timero;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int ScoreLimit;
    
    FRotator NewRotation;
    float VisibleScale;
    bool Growing;
    
    UPROPERTY(BlueprintReadWrite)
    bool Done = false;
    
    //FQuat QuatRotation = FQuat(0.0f, 0.0f, 0.0f);
    
    void MouseX(float value);
    void MouseY(float value);
    
    UPROPERTY(EditAnywhere)
    USpringArmComponent * arm;
    
    
    
};
