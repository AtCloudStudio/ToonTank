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

* Created new C++ class PawnBase
* Created new blueprint class BP_PawnTank and BP_PawnTurret based on PawnBase
* Created child C++ class PawnTank derived from PawnBase, set parent class of BP_PawnTank to this child class
* Created child C++ class PawnTurret derived from PawnBase, set parent class of BP_PawnTurret to this child class
* Implemented enemy turret rotating towards player tank
* Implemented player tank turret rotating towards mouse cursor
* Created new C++ class ProjectileBase
* Implemented player and enemy firing