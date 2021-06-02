// Fill out your copyright notice in the Description page of Project Settings.

#include "Gold.h"
#include "CharPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/Vector.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values
AGold::AGold()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
    Coin = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin"));
    TriggerBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Box"));
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AGold::BeginOverlap);
    Coin->AttachTo(RootComponent);
    TriggerBox->AttachTo(RootComponent);
    
}

// Called when the game starts or when spawned
void AGold::BeginPlay()
{
    Super::BeginPlay();
    CharPawn = Cast<ACharPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    
}

/*void AGold::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
 AActor* OtherActor,
 UPrimitiveComponent* OtherComp,
 int32 OtherBodyIndex,
 bool bFromSweep,
 const FHitResult &SweepResult )
 {
 if (OtherActor &&
 (OtherActor != this) && OtherComp){
 CharPawn->AddCoins();
 }
 }*/
void AGold::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
                          AActor* OtherActor,
                          UPrimitiveComponent* OtherComp,
                          int32 OtherBodyIndex,
                          bool bFromSweep,
                          const FHitResult &SweepResult ){
    CharPawn->AddCoins();
    
    AActor::Destroy();
}

// Called every frame
void AGold::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
}

