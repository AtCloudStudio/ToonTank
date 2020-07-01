# Toon Tank

---

## Introduction

Hi, I am a beginner of indie game developer, and this is my unreal engine course project named "Toon Tank". 

You're welcome to download and do whatever legal with all these files. Please feel free to leave your comments, that would be greatly appreciated.

---

## Game engine version: 
* Unreal Engine 4.25.1

---

## Daily Updates
### Day 01

* Created new C++ Pawn class PawnBase
* Created new blueprint class BP_PawnTank and BP_PawnTurret based on PawnBase
* Created child C++ class PawnTank derived from PawnBase, set parent class of BP_PawnTank to this child class
* Created child C++ class PawnTurret derived from PawnBase, set parent class of BP_PawnTurret to this child class
* Implemented enemy turret rotating towards player tank
* Implemented player tank turret rotating towards mouse cursor
* Created new C++ Actor class ProjectileBase
* Implemented player and enemy firing

### Day 02
* Created and initially setup new C++ GameModeBase class TankGameModeBase
* Created new C++ ActorComponent class HealthComponent, and added it to both BP_PawnTank and BP_PawnTurret
* Further function implementation of TankGameModeBase
* Created and setup new widget blueprint class WBP_GameStart
* Created and setup new widget blueprint class WBP_GameOver
* Created new C++ PlayerController class PlayerControllerBase, created new blueprint class BP_PlayerContoller based on PlayerControllerBase
* Added projectile hit particle, player and enemy death explosion particle
* Added ParticleSystemComponent ProjectileTrail on projectile class
* Added some sound effects
* Added projectile hit, player death and enemy death camera shake
* Section end