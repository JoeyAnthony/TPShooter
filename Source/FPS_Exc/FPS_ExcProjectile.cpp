// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FPS_ExcProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

AFPS_ExcProjectile::AFPS_ExcProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFPS_ExcProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 4000.f;
	ProjectileMovement->MaxSpeed = 4000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	

	// Die after 3 seconds by defaultB
	InitialLifeSpan = 10.0f;
}

void AFPS_ExcProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		FVector otherscale = OtherComp->GetComponentScale();
		if (otherscale.GetMin() < 0.4f)
			OtherActor->Destroy();

		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		OtherComp->SetWorldScale3D(otherscale * 0.9f);

		UMaterialInstanceDynamic* Material = OtherComp->CreateAndSetMaterialInstanceDynamic(0);
		Material->SetVectorParameterValue("DiffuseColor", FLinearColor::MakeRandomColor());
		Material->SetVectorParameterValue("MSR", FLinearColor::MakeRandomColor());

		MakeNoise(1.0f, Instigator);
		//Destroy();
	}
}