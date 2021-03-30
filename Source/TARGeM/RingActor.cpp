// Fill out your copyright notice in the Description page of Project Settings.


#include "RingActor.h"

#include "Components/StaticMeshComponent.h"

// Sets default values
ARingActor::ARingActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->AttachTo(Root);
}

// Called when the game starts or when spawned
void ARingActor::BeginPlay()
{
    Super::BeginPlay();

    UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);

    /*
    TArray<FColor> rawTextureData;

    for (int32 i = 0; i < (1000 * 10); i++)
    {
        rawTextureData.Add(FColor(255, 0, 0, 255));
    }

    UTexture2D* Texture = UTexture2D::CreateTransient(1000, 10);
    FTexture2DMipMap& Mip = Texture->PlatformData->Mips[0];
    void* Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
    FMemory::Memcpy(Data, rawTextureData.GetData(), (1000 * 10 * 4));
    Mip.BulkData.Unlock();
    Texture->UpdateResource();

    */

    int32 SrcWidth = 10000;
    int32 SrcHeight = 100;

    TArray<FColor> SrcData;

    int32 g = 0;

    for (int32 i = 0; i < SrcWidth; i++)
    {
        g = 0;

        for (int32 j = 0; j < SrcHeight; j++)
        {
            SrcData.Add(FColor(255, g, 0, 255));

            g += 20;

            if (g > 255) {
                g = 0;
            }
        }
    }

    bool UseAlpha = true;

    // Create the texture
    UTexture2D* MyScreenshot = UTexture2D::CreateTransient(
        SrcWidth,
        SrcHeight,
        PF_B8G8R8A8
    );

    // Lock the texture so it can be modified
    uint8* MipData = static_cast<uint8*>(MyScreenshot->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

    // Create base mip.
    uint8* DestPtr = NULL;
    const FColor* SrcPtr = NULL;
    for (int32 y = 0; y < SrcHeight; y++)
    {
        DestPtr = &MipData[(SrcHeight - 1 - y) * SrcWidth * sizeof(FColor)];
        SrcPtr = const_cast<FColor*>(&SrcData[(SrcHeight - 1 - y) * SrcWidth]);
        for (int32 x = 0; x < SrcWidth; x++)
        {
            *DestPtr++ = SrcPtr->B;
            *DestPtr++ = SrcPtr->G;
            *DestPtr++ = SrcPtr->R;
            if (UseAlpha)
            {
                *DestPtr++ = SrcPtr->A;
            }
            else
            {
                *DestPtr++ = 0xFF;
            }
            SrcPtr++;
        }
    }

    // Unlock the texture
    MyScreenshot->PlatformData->Mips[0].BulkData.Unlock();
    MyScreenshot->UpdateResource();

    DynamicMaterial->SetTextureParameterValue(TEXT("RingTextureParam"), MyScreenshot);

    Mesh->SetMaterial(0, DynamicMaterial);
}

// Called every frame
void ARingActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

