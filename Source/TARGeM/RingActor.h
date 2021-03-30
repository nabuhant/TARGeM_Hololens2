// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RingActor.generated.h"

UCLASS()
class TARGEM_API ARingActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY();
	USceneComponent* Root;

	UPROPERTY(EditAnywhere);
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "My Texture")
		UTexture2D* TextureToUse;
};
