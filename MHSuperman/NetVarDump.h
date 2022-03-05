#pragma once
#ifndef _USE_MFC
	#include <Windows.h>
	#include <WinDef.h>
#else
	#include "stdafx.h"
#endif
//#ifndef GAME_DLL
#include "sdk.h"
//#endif
;
#ifndef uchar
#define uchar unsigned char
#endif
//#pragma once
template<typename T> inline T* MakePointerGEN( PVOID thisptr, int offset ) { return reinterpret_cast<T*>( reinterpret_cast<UINT_PTR>( thisptr ) + offset ); }
struct GenDT_TEHeroesEFXBlood
{
	inline Vector* offset() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline int* normal() { return MakePointerGEN< int >( this, 0x1c ); }
	inline float* magnitude() { return MakePointerGEN< float >( this, 0x28 ); }
	inline EHANDLE* hParent() { return MakePointerGEN< EHANDLE >( this, 0x2c ); }
	inline EHANDLE* hitboxBone() { return MakePointerGEN< EHANDLE >( this, 0x30 ); }
	inline int* damageType() { return MakePointerGEN< int >( this, 0x34 ); }
};
struct GenDT_BaseEntity
{
	struct CAnimTimeMustBeFirst
	{
		inline float* flAnimTime() { return MakePointerGEN< float >( this, 0x60 ); }
	};
	struct CCollisionProperty
	{
		inline Vector* vecMins() { return MakePointerGEN< Vector >( this, 0x14 ); }
		inline Vector* vecMaxs() { return MakePointerGEN< Vector >( this, 0x20 ); }
		inline int* nSolidType() { return MakePointerGEN< int >( this, 0x35 ); }
		inline int* usSolidFlags() { return MakePointerGEN< int >( this, 0x30 ); }
		inline int* nSurroundType() { return MakePointerGEN< int >( this, 0x34 ); }
		inline int* triggerBloat() { return MakePointerGEN< int >( this, 0x36 ); }
		inline Vector* vecSpecifiedSurroundingMins() { return MakePointerGEN< Vector >( this, 0x38 ); }
		inline Vector* vecSpecifiedSurroundingMaxs() { return MakePointerGEN< Vector >( this, 0x44 ); }
	};
	struct CPredictableId
	{
		inline int* PredictableID() { return MakePointerGEN< int >( this, 0x94 ); }
		inline bool* bIsPlayerSimulated() { return MakePointerGEN< bool >( this, 0x460 ); }
	};
	inline CAnimTimeMustBeFirst* AnimTimeMustBeFirst() { return MakePointerGEN< CAnimTimeMustBeFirst >( this, 0x0 ); }
	inline float* flSimulationTime() { return MakePointerGEN< float >( this, 0x68 ); }
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2d4 ); }
	inline QAngle* angRotation() { return MakePointerGEN< QAngle >( this, 0x2e0 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x84 ); }
	inline int* fEffects() { return MakePointerGEN< int >( this, 0x70 ); }
	inline int* nRenderMode() { return MakePointerGEN< int >( this, 0x74 ); }
	inline int* nRenderFX() { return MakePointerGEN< int >( this, 0x54 ); }
	inline int* clrRender() { return MakePointerGEN< int >( this, 0x58 ); }
	inline int* iTeamNum() { return MakePointerGEN< int >( this, 0x90 ); }
	inline int* CollisionGroup() { return MakePointerGEN< int >( this, 0x2f0 ); }
	inline float* flElasticity() { return MakePointerGEN< float >( this, 0x1d4 ); }
	inline float* flShadowCastDistance() { return MakePointerGEN< float >( this, 0x1d8 ); }
	inline EHANDLE* hOwnerEntity() { return MakePointerGEN< EHANDLE >( this, 0x470 ); }
	inline EHANDLE* hEffectEntity() { return MakePointerGEN< EHANDLE >( this, 0x474 ); }
	inline int* moveparent() { return MakePointerGEN< int >( this, 0x160 ); }
	inline int* iParentAttachment() { return MakePointerGEN< int >( this, 0x13c ); }
	inline int* iParentBoneIndex() { return MakePointerGEN< int >( this, 0x140 ); }
	inline int* movetype() { return MakePointerGEN< int >( this, 0x0 ); }
	inline int* movecollide() { return MakePointerGEN< int >( this, 0x0 ); }
	inline CCollisionProperty* Collision() { return MakePointerGEN< CCollisionProperty >( this, 0x16c ); }
	inline int* iTextureFrameIndex() { return MakePointerGEN< int >( this, 0x464 ); }
	inline CPredictableId* predictable_id() { return MakePointerGEN< CPredictableId >( this, 0x0 ); }
	inline bool* bSimulatedEveryTick() { return MakePointerGEN< bool >( this, 0x461 ); }
	inline bool* bAnimatedEveryTick() { return MakePointerGEN< bool >( this, 0x462 ); }
	inline bool* bAlternateSorting() { return MakePointerGEN< bool >( this, 0x463 ); }
	inline int* spawnflags() { return MakePointerGEN< int >( this, 0x4ac ); }
	inline int* isExcludeEyeTarget() { return MakePointerGEN< int >( this, 0x4b0 ); }
	inline int* isExcludeAutoTargeting() { return MakePointerGEN< int >( this, 0x4b1 ); }
	inline float* flRenderTimeScale() { return MakePointerGEN< float >( this, 0x4b4 ); }
};
struct GenDT_FootstepControl : public GenDT_BaseEntity
{
}; // Fail count = 2
struct GenDT_BaseAnimating : public GenDT_BaseEntity
{
	struct CServerAnimationData
	{
		inline float* flCycle() { return MakePointerGEN< float >( this, 0x6fc ); }
	};
	inline int* nSequence() { return MakePointerGEN< int >( this, 0x6f8 ); }
	inline int* nForceBone() { return MakePointerGEN< int >( this, 0x59c ); }
	inline Vector* vecForce() { return MakePointerGEN< Vector >( this, 0x590 ); }
	inline int* nSkin() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline int* nBody() { return MakePointerGEN< int >( this, 0x4f0 ); }
	inline int* nHitboxSet() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline float* flModelWidthScale() { return MakePointerGEN< float >( this, 0x5d0 ); }
	inline float* flPoseParameter() { return MakePointerGEN< float >( this, 0x5d4 ); } // Array size = 24
	inline float* flPlaybackRate() { return MakePointerGEN< float >( this, 0x514 ); }
	inline float* flEncodedController() { return MakePointerGEN< float >( this, 0x68c ); } // Array size = 4
	inline bool* bClientSideAnimation() { return MakePointerGEN< bool >( this, 0x6c8 ); }
	inline bool* bClientSideFrameReset() { return MakePointerGEN< bool >( this, 0x550 ); }
	inline int* nNewSequenceParity() { return MakePointerGEN< int >( this, 0x6cc ); }
	inline int* nResetEventsParity() { return MakePointerGEN< int >( this, 0x6d0 ); }
	inline int* nMuzzleFlashParity() { return MakePointerGEN< int >( this, 0x770 ); }
	inline EHANDLE* hLightingOrigin() { return MakePointerGEN< EHANDLE >( this, 0x768 ); }
	inline EHANDLE* hLightingOriginRelative() { return MakePointerGEN< EHANDLE >( this, 0x76c ); }
	inline CServerAnimationData* serveranimdata() { return MakePointerGEN< CServerAnimationData >( this, 0x0 ); }
	inline int* fadeMinDist() { return MakePointerGEN< int >( this, 0x554 ); }
	inline int* fadeMaxDist() { return MakePointerGEN< int >( this, 0x558 ); }
	inline float* flFadeScale() { return MakePointerGEN< float >( this, 0x55c ); }
	inline EHANDLE* hRagdollBlender() { return MakePointerGEN< EHANDLE >( this, 0x7fc ); }
	inline int* isLiftable() { return MakePointerGEN< int >( this, 0x800 ); }
	inline float* lastSpeakTime() { return MakePointerGEN< float >( this, 0x8b4 ); }
};
struct GenDT_BaseCombatWeapon : public GenDT_BaseAnimating
{
	struct CLocalWeaponData
	{
		inline int* iClip1() { return MakePointerGEN< int >( this, 0x934 ); }
		inline int* iClip2() { return MakePointerGEN< int >( this, 0x938 ); }
		inline int* iPrimaryAmmoType() { return MakePointerGEN< int >( this, 0x92c ); }
		inline int* iSecondaryAmmoType() { return MakePointerGEN< int >( this, 0x930 ); }
		inline int* nViewModelIndex() { return MakePointerGEN< int >( this, 0x8ec ); }
	};
	struct CLocalActiveWeaponData
	{
		inline float* flNextPrimaryAttack() { return MakePointerGEN< float >( this, 0x8f0 ); }
		inline float* flNextSecondaryAttack() { return MakePointerGEN< float >( this, 0x8f4 ); }
		inline int* nNextThinkTick() { return MakePointerGEN< int >( this, 0x7c ); }
		inline float* flTimeWeaponIdle() { return MakePointerGEN< float >( this, 0x8f8 ); }
	};
	inline CLocalWeaponData* LocalWeaponData() { return MakePointerGEN< CLocalWeaponData >( this, 0x0 ); }
	inline CLocalActiveWeaponData* LocalActiveWeaponData() { return MakePointerGEN< CLocalActiveWeaponData >( this, 0x0 ); }
	inline int* iViewModelIndex() { return MakePointerGEN< int >( this, 0x900 ); }
	inline int* iWorldModelIndex() { return MakePointerGEN< int >( this, 0x904 ); }
	inline int* iState() { return MakePointerGEN< int >( this, 0x924 ); }
	inline EHANDLE* hOwner() { return MakePointerGEN< EHANDLE >( this, 0x8e8 ); }
	inline int* iSubType() { return MakePointerGEN< int >( this, 0x958 ); }
};
struct GenDT_WeaponHeroesBase : public GenDT_BaseCombatWeapon
{
	struct CHEROES_MATERIAL_GAME_DATA
	{
		inline int* materialType() { return MakePointerGEN< int >( this, 0x10 ); }
		inline int* pollution() { return MakePointerGEN< int >( this, 0x14 ); }
		inline int* color0() { return MakePointerGEN< int >( this, 0x4 ); }
		inline int* enhanceEffectID() { return MakePointerGEN< int >( this, 0x18 ); }
		inline char* changeParity() { return MakePointerGEN< char >( this, 0x1c ); }
	}; // Fail count = 1
	inline CHEROES_MATERIAL_GAME_DATA* materialGameData() { return MakePointerGEN< CHEROES_MATERIAL_GAME_DATA >( this, 0x9b8 ); }
	inline int* virtualSequence() { return MakePointerGEN< int >( this, 0xa10 ); }
};
struct GenDT_WeaponMeleeBase : public GenDT_WeaponHeroesBase
{
};
struct GenDT_WeaponSword : public GenDT_WeaponMeleeBase
{
};
struct GenDT_WeaponLongBow : public GenDT_WeaponSword
{
};
struct GenDT_WeaponShortBow : public GenDT_WeaponLongBow
{
};
struct GenDT_WeaponScythe : public GenDT_WeaponSword
{
};
struct GenDT_WeaponBlaster : public GenDT_WeaponSword
{
};
struct GenDT_WeaponPillar : public GenDT_WeaponSword
{
};
struct GenDT_WeaponStaff : public GenDT_WeaponSword
{
};
struct GenDT_WeaponDualSpear : public GenDT_WeaponSword
{
};
struct GenDT_WeaponHammer : public GenDT_WeaponSword
{
};
struct GenDT_WeaponDualSword : public GenDT_WeaponSword
{
};
struct GenDT_WeaponLongSword : public GenDT_WeaponSword
{
};
struct GenDT_WeaponBareHand : public GenDT_WeaponSword
{
};
struct GenDT_WeaponRangeBase : public GenDT_WeaponHeroesBase
{
};
struct GenDT_WeaponSnowball : public GenDT_WeaponRangeBase
{
	inline int* projectile() { return MakePointerGEN< int >( this, 0xa18 ); }
};
struct GenDT_WeaponMixedBase : public GenDT_WeaponMeleeBase
{
};
struct GenDT_WeaponLift : public GenDT_WeaponMeleeBase
{
	inline int* targetEntity() { return MakePointerGEN< int >( this, 0xa58 ); }
	inline int* isAttached() { return MakePointerGEN< int >( this, 0xa5c ); }
	inline int* liftObjHealth() { return MakePointerGEN< int >( this, 0xa64 ); }
	inline float* liftObjMass() { return MakePointerGEN< float >( this, 0xa60 ); }
	inline float* liftDamageScale() { return MakePointerGEN< float >( this, 0xa68 ); }
	inline float* liftDamageTakeScale() { return MakePointerGEN< float >( this, 0xa6c ); }
	inline int* liftType() { return MakePointerGEN< int >( this, 0xa70 ); }
	inline float* throwSpeed() { return MakePointerGEN< float >( this, 0xa74 ); }
	inline Vector* throwAngularImpulse() { return MakePointerGEN< Vector >( this, 0xa78 ); }
};
struct GenDT_WeaponJavelin : public GenDT_WeaponRangeBase
{
	inline int* projectile() { return MakePointerGEN< int >( this, 0xa18 ); }
};
struct GenDT_BaseAnimatingOverlay : public GenDT_BaseAnimating
{
	struct COverlayVars
	{
	}; // Fail count = 1
	inline COverlayVars* overlay_vars() { return MakePointerGEN< COverlayVars >( this, 0x0 ); }
};
struct GenDT_BaseFlex : public GenDT_BaseAnimatingOverlay
{
	inline float* flexWeight() { return MakePointerGEN< float >( this, 0x998 ); } // Array size = 64
	inline bool* blinktoggle() { return MakePointerGEN< bool >( this, 0xac4 ); }
	inline Vector* viewtarget() { return MakePointerGEN< Vector >( this, 0x960 ); }
};
struct GenDT_BaseCombatCharacter : public GenDT_BaseFlex
{
	struct CBCCLocalPlayerExclusive
	{
		inline float* flNextAttack() { return MakePointerGEN< float >( this, 0xc40 ); }
	};
	struct CHAND_IK_CONTROLLER_DATA
	{
		inline EHANDLE* handIKTargetEntity() { return MakePointerGEN< EHANDLE >( this, 0x4 ); }
		inline EHANDLE* handIKOption() { return MakePointerGEN< EHANDLE >( this, 0x8 ); }
	};
	inline CBCCLocalPlayerExclusive* bcc_localdata() { return MakePointerGEN< CBCCLocalPlayerExclusive >( this, 0x0 ); }
	inline EHANDLE* hActiveWeapon() { return MakePointerGEN< EHANDLE >( this, 0xd88 ); }
	inline EHANDLE* hMyWeapons() { return MakePointerGEN< EHANDLE >( this, 0xcc8 ); } // Array size = 48
	inline int* iHealth() { return MakePointerGEN< int >( this, 0x88 ); }
	inline int* lifeState() { return MakePointerGEN< int >( this, 0x87 ); }
	inline int* iMaxHealth() { return MakePointerGEN< int >( this, 0xda0 ); }
	inline int* stamina() { return MakePointerGEN< int >( this, 0xda4 ); }
	inline int* maxStamina() { return MakePointerGEN< int >( this, 0xdac ); }
	inline float* downGauge() { return MakePointerGEN< float >( this, 0xdb4 ); }
	inline int* level() { return MakePointerGEN< int >( this, 0xdb8 ); }
	inline int* surfaceType() { return MakePointerGEN< int >( this, 0xdbc ); }
	inline int* figureHeightRatio() { return MakePointerGEN< int >( this, 0xe04 ); }
	inline int* figureBustRatio() { return MakePointerGEN< int >( this, 0xe08 ); }
	inline bool* bShouldDrawHudName() { return MakePointerGEN< bool >( this, 0xe14 ); }
	inline int* useHeightCorrection() { return MakePointerGEN< int >( this, 0xd9c ); }
	inline int* isAllowInternalMovement() { return MakePointerGEN< int >( this, 0xe23 ); }
	inline float* motionSpeedStatusEffect() { return MakePointerGEN< float >( this, 0xe24 ); }
	inline int* isMotionEnabled() { return MakePointerGEN< int >( this, 0xe40 ); }
	inline CHAND_IK_CONTROLLER_DATA* handIKController() { return MakePointerGEN< CHAND_IK_CONTROLLER_DATA >( this, 0xe28 ); }
};
struct GenDT_HookshotHook : public GenDT_BaseCombatCharacter
{
};
struct GenDT_WeaponHookshot : public GenDT_WeaponHeroesBase
{
	inline int* hookState() { return MakePointerGEN< int >( this, 0xa18 ); }
	inline int* attachType() { return MakePointerGEN< int >( this, 0xa1c ); }
	inline int* pTargetNPC() { return MakePointerGEN< int >( this, 0xa8c ); }
	inline int* pTargetProp() { return MakePointerGEN< int >( this, 0xa90 ); }
	inline float* length() { return MakePointerGEN< float >( this, 0xa78 ); }
	inline int* hook() { return MakePointerGEN< int >( this, 0xa88 ); }
};
struct GenDT_WeaponHarpoon : public GenDT_WeaponHookshot
{
	inline int* pTargetFish() { return MakePointerGEN< int >( this, 0xa98 ); }
};
struct GenDT_WeaponGrappling : public GenDT_WeaponHeroesBase
{
	inline int* pTargetNPC() { return MakePointerGEN< int >( this, 0xa18 ); }
	inline int* pAttackTargetEntity() { return MakePointerGEN< int >( this, 0xa1c ); }
	inline int* isAttached() { return MakePointerGEN< int >( this, 0xa39 ); }
	inline int* isFinishMotion() { return MakePointerGEN< int >( this, 0xa40 ); }
};
struct GenDT_WeaponFishingRod : public GenDT_WeaponHeroesBase
{
	inline int* state() { return MakePointerGEN< int >( this, 0xa1c ); }
	inline float* ffloat() { return MakePointerGEN< float >( this, 0xa18 ); }
};
struct GenDT_WeaponCarry : public GenDT_WeaponMeleeBase
{
	inline int* targetEntity() { return MakePointerGEN< int >( this, 0xa58 ); }
	inline int* isAttached() { return MakePointerGEN< int >( this, 0xa5c ); }
	inline int* carryType() { return MakePointerGEN< int >( this, 0xa60 ); }
};
struct GenDT_TEReverseGravity
{
	inline Vector* vecSrc() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline float* radius() { return MakePointerGEN< float >( this, 0x1c ); }
	inline int* intense() { return MakePointerGEN< int >( this, 0x20 ); }
};
struct GenDT_PointLandMark : public GenDT_BaseEntity
{
}; // Fail count = 1
struct GenDT_InfoCustomEyeTarget : public GenDT_BaseEntity
{
	inline int* isEnable() { return MakePointerGEN< int >( this, 0x4e8 ); }
};
struct GenDT_HeroesTEEffectExecutor
{
	inline int* efxFileName() { return MakePointerGEN< int >( this, 0x10 ); }
	inline int* efxIndex() { return MakePointerGEN< int >( this, 0x14 ); }
	inline EHANDLE* hParent() { return MakePointerGEN< EHANDLE >( this, 0x18 ); }
};
struct GenDT_HeroesTEParticleBase : public GenDT_HeroesTEEffectExecutor
{
	inline Vector* position() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline QAngle* angle() { return MakePointerGEN< QAngle >( this, 0x28 ); }
	inline Vector* direction() { return MakePointerGEN< Vector >( this, 0x34 ); }
	inline bool* bone() { return MakePointerGEN< bool >( this, 0x40 ); }
};
struct GenDT_TE_BaseAnimating
{
	inline EHANDLE* hEntity() { return MakePointerGEN< EHANDLE >( this, 0x10 ); }
	inline int* eventType() { return MakePointerGEN< int >( this, 0x14 ); }
}; // Fail count = 1
struct GenDT_HeroesTaskFunctionEvent
{
	struct CHEROES_TASK_FUNCTION
	{
		inline int* funcType() { return MakePointerGEN< int >( this, 0x4 ); }
		inline float* calledTime() { return MakePointerGEN< float >( this, 0x8 ); }
		inline float* argList0() { return MakePointerGEN< float >( this, 0xc ); }
	}; // Fail count = 1
	inline EHANDLE* hCaller() { return MakePointerGEN< EHANDLE >( this, 0x10 ); }
	inline CHEROES_TASK_FUNCTION* taskFunc() { return MakePointerGEN< CHEROES_TASK_FUNCTION >( this, 0x14 ); }
};
struct GenDT_FuncClip : public GenDT_BaseEntity
{
	inline int* iDisabled() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline int* iszExcludedClass() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline bool* bInvertExcludeClass() { return MakePointerGEN< bool >( this, 0x4f0 ); }
	inline int* iszExcludedTargetName() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline bool* bInvertExcludeTargetName() { return MakePointerGEN< bool >( this, 0x4f8 ); }
};
struct GenDT_Sprite : public GenDT_BaseEntity
{
	inline EHANDLE* hAttachedToEntity() { return MakePointerGEN< EHANDLE >( this, 0x4f8 ); }
	inline int* nAttachment() { return MakePointerGEN< int >( this, 0x4fc ); }
	inline float* flScaleTime() { return MakePointerGEN< float >( this, 0x51c ); }
	inline float* flSpriteScale() { return MakePointerGEN< float >( this, 0x518 ); }
	inline float* flSpriteFramerate() { return MakePointerGEN< float >( this, 0x500 ); }
	inline float* flGlowProxySize() { return MakePointerGEN< float >( this, 0x524 ); }
	inline float* flHDRColorScale() { return MakePointerGEN< float >( this, 0x528 ); }
	inline float* flFrame() { return MakePointerGEN< float >( this, 0x504 ); }
	inline float* flMaxFrame() { return MakePointerGEN< float >( this, 0x508 ); }
	inline float* flBrightnessTime() { return MakePointerGEN< float >( this, 0x514 ); }
	inline int* nBrightness() { return MakePointerGEN< int >( this, 0x510 ); }
	inline bool* bWorldSpaceScale() { return MakePointerGEN< bool >( this, 0x520 ); }
	inline float* zBias() { return MakePointerGEN< float >( this, 0x52c ); }
	inline int* fadeMinDist() { return MakePointerGEN< int >( this, 0x530 ); }
	inline int* fadeMaxDist() { return MakePointerGEN< int >( this, 0x534 ); }
};
struct GenDT_HeroesItemSprite : public GenDT_Sprite
{
};
struct GenDT_GameRulesProxy
{
};
struct GenDT_HeroesGameRulesProxy : public GenDT_GameRulesProxy
{
	struct CHeroesGameRules
	{
		inline bool* bFreezePeriod() { return MakePointerGEN< bool >( this, 0xc ); }
		inline int* iRoundTime() { return MakePointerGEN< int >( this, 0x10 ); }
		inline int* fRoundStartTime() { return MakePointerGEN< int >( this, 0x14 ); }
		inline float* flGameStartTime() { return MakePointerGEN< float >( this, 0x18 ); }
		inline int* isPvPMap() { return MakePointerGEN< int >( this, 0x1c ); }
	};
	inline CHeroesGameRules* heroes_gamerules_data() { return MakePointerGEN< CHeroesGameRules >( this, 0x0 ); }
};
struct GenDT_Prop_Bunker : public GenDT_BaseAnimating
{
	inline int* constructLevel() { return MakePointerGEN< int >( this, 0x8f8 ); }
	inline Vector* protectMin() { return MakePointerGEN< Vector >( this, 0x8fc ); }
	inline Vector* protectMax() { return MakePointerGEN< Vector >( this, 0x908 ); }
	inline int* destroyLevel() { return MakePointerGEN< int >( this, 0x914 ); }
};
struct GenDT_NeoMMOPC : public GenDT_BaseCombatCharacter
{
	struct CHEROES_NPC_COSTUME_LOADABLE_DATA
	{
		struct CHEROES_COSTUME_DATA
		{
			inline int* serialList0() { return MakePointerGEN< int >( this, 0x7c ); }
			inline bool* brokenList0() { return MakePointerGEN< bool >( this, 0xa4 ); }
			inline bool* brokenList() { return MakePointerGEN< bool >( this, 0x0 ); } // Array size = 10
			inline int* color0() { return MakePointerGEN< int >( this, 0xb0 ); }
			inline int* pollutionList0() { return MakePointerGEN< int >( this, 0x128 ); }
			inline int* faceLayerList0() { return MakePointerGEN< int >( this, 0x178 ); }
			inline int* faceLayerList() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 6
			inline int* faceLayerColor0() { return MakePointerGEN< int >( this, 0x190 ); }
			inline int* faceLayerColor() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 18
			inline int* lookList0() { return MakePointerGEN< int >( this, 0x150 ); }
			inline int* facePaintRotate() { return MakePointerGEN< int >( this, 0x1d8 ); }
			inline int* facePaintX() { return MakePointerGEN< int >( this, 0x1dc ); }
			inline int* facePaintY() { return MakePointerGEN< int >( this, 0x1e0 ); }
			inline int* facePaintScale() { return MakePointerGEN< int >( this, 0x1e4 ); }
			inline int* faceShinenessLevel() { return MakePointerGEN< int >( this, 0x1e8 ); }
			inline bool* bodyLayerList0() { return MakePointerGEN< bool >( this, 0x1ec ); }
			inline bool* bodyLayerList() { return MakePointerGEN< bool >( this, 0x0 ); }
			inline bool* bodyLayerColor0() { return MakePointerGEN< bool >( this, 0x1f0 ); }
			inline bool* bodyLayerColor() { return MakePointerGEN< bool >( this, 0x0 ); } // Array size = 3
			inline bool* bodyPaintSurfaceSide() { return MakePointerGEN< bool >( this, 0x1fc ); }
			inline bool* bodyPaintRotateZ() { return MakePointerGEN< bool >( this, 0x200 ); }
			inline bool* bodyPaintX() { return MakePointerGEN< bool >( this, 0x204 ); }
			inline bool* bodyPaintY() { return MakePointerGEN< bool >( this, 0x208 ); }
			inline bool* bodyPaintScale() { return MakePointerGEN< bool >( this, 0x20c ); }
			inline bool* bodyPaintClip() { return MakePointerGEN< bool >( this, 0x210 ); }
			inline bool* bodyPaintBlend() { return MakePointerGEN< bool >( this, 0x214 ); }
			inline char* changeParity() { return MakePointerGEN< char >( this, 0x218 ); }
			inline int* enhanceEffectPartIndex0() { return MakePointerGEN< int >( this, 0x234 ); }
			inline int* enhanceEffectValue0() { return MakePointerGEN< int >( this, 0x274 ); }
			inline int* costumeSkins0() { return MakePointerGEN< int >( this, 0x2d0 ); }
			inline int* costumeBodies0() { return MakePointerGEN< int >( this, 0x2f8 ); }
		}; // Fail count = 8
		inline CHEROES_COSTUME_DATA* curCostumeData() { return MakePointerGEN< CHEROES_COSTUME_DATA >( this, 0x4 ); }
	};
	struct CMMO_ACTION_MESSAGE
	{
		inline Vector* position() { return MakePointerGEN< Vector >( this, 0x8 ); }
		inline Vector* velocity() { return MakePointerGEN< Vector >( this, 0x14 ); }
		inline float* yaw() { return MakePointerGEN< float >( this, 0x20 ); }
		inline int* sequence() { return MakePointerGEN< int >( this, 0x24 ); }
		inline int* actionStateIndex() { return MakePointerGEN< int >( this, 0x26 ); }
		inline float* startTime() { return MakePointerGEN< float >( this, 0x28 ); }
		inline int* state() { return MakePointerGEN< int >( this, 0x2c ); }
		inline int* checkParity() { return MakePointerGEN< int >( this, 0x30 ); }
	};
	inline CHEROES_NPC_COSTUME_LOADABLE_DATA* costumeLoadable() { return MakePointerGEN< CHEROES_NPC_COSTUME_LOADABLE_DATA >( this, 0x10a8 ); }
	inline int* titleId() { return MakePointerGEN< int >( this, 0xefc ); }
	inline int* guildSN() { return MakePointerGEN< int >( this, 0xf80 ); }
	inline int* isCafe() { return MakePointerGEN< int >( this, 0x1084 ); }
	inline int* isReturn() { return MakePointerGEN< int >( this, 0x1085 ); }
	inline int* VIPCode() { return MakePointerGEN< int >( this, 0x1088 ); }
	inline CMMO_ACTION_MESSAGE* actionMessage() { return MakePointerGEN< CMMO_ACTION_MESSAGE >( this, 0xe48 ); }
	inline int* initOriginParity() { return MakePointerGEN< int >( this, 0x1098 ); }
	inline int* summaryChangeParity() { return MakePointerGEN< int >( this, 0x10a0 ); }
}; // Fail count = 3
struct GenDT_PropCannon : public GenDT_BaseAnimating
{
	inline EHANDLE* hPlayer() { return MakePointerGEN< EHANDLE >( this, 0x8ec ); }
	inline bool* bEnterAnimOn() { return MakePointerGEN< bool >( this, 0x8f4 ); }
	inline bool* bExitAnimOn() { return MakePointerGEN< bool >( this, 0x8f5 ); }
	inline Vector* vecEyeExitEndpoint() { return MakePointerGEN< Vector >( this, 0x8f8 ); }
};
struct GenDT_PropBallista : public GenDT_PropCannon
{
	inline float* launchSpeed() { return MakePointerGEN< float >( this, 0x990 ); }
	inline float* gravityMutiplier() { return MakePointerGEN< float >( this, 0x98c ); }
	inline int* guideTrailShow() { return MakePointerGEN< int >( this, 0x988 ); }
};
struct GenDT_PropCatapult : public GenDT_PropBallista
{
	inline int* showRangeTrail() { return MakePointerGEN< int >( this, 0x998 ); }
	inline int* isFirst() { return MakePointerGEN< int >( this, 0x999 ); }
}; // Fail count = 1
struct GenDT_PropBallistaRope : public GenDT_PropBallista
{
	inline int* ropeStartEntity() { return MakePointerGEN< int >( this, 0x998 ); }
	inline int* ropeEndEntity() { return MakePointerGEN< int >( this, 0x99c ); }
	inline int* ropeStartBone() { return MakePointerGEN< int >( this, 0x9a0 ); }
	inline int* ropeEndBone() { return MakePointerGEN< int >( this, 0x9a4 ); }
	inline int* ropeCreated() { return MakePointerGEN< int >( this, 0x9a8 ); }
	inline int* projectileTouched() { return MakePointerGEN< int >( this, 0x9a9 ); }
	inline int* isForceChangeView() { return MakePointerGEN< int >( this, 0x9aa ); }
};
struct GenDT_Prop_ReviveTorch : public GenDT_BaseAnimating
{
}; // Fail count = 1
struct GenDT_AI_BaseNPC : public GenDT_BaseCombatCharacter
{
	inline int* lifeState() { return MakePointerGEN< int >( this, 0x87 ); }
	inline bool* bPerformAvoidance() { return MakePointerGEN< bool >( this, 0xe48 ); }
	inline bool* bIsMoving() { return MakePointerGEN< bool >( this, 0xe49 ); }
	inline bool* bFadeCorpse() { return MakePointerGEN< bool >( this, 0xe4a ); }
	inline int* iDeathPose() { return MakePointerGEN< int >( this, 0xe4c ); }
	inline int* iDeathFrame() { return MakePointerGEN< int >( this, 0xe50 ); }
	inline int* iSpeedModRadius() { return MakePointerGEN< int >( this, 0xe54 ); }
	inline int* iSpeedModSpeed() { return MakePointerGEN< int >( this, 0xe58 ); }
	inline bool* bSpeedModActive() { return MakePointerGEN< bool >( this, 0xe5c ); }
	inline bool* bImportanRagdoll() { return MakePointerGEN< bool >( this, 0xe5d ); }
	inline bool* bInChoreo() { return MakePointerGEN< bool >( this, 0xe5e ); }
};
struct GenDT_Heroes_AI_BaseActor : public GenDT_AI_BaseNPC
{
	struct CHEROES_MATERIAL_GAME_DATA
	{
		inline int* materialType() { return MakePointerGEN< int >( this, 0x10 ); }
		inline int* pollution() { return MakePointerGEN< int >( this, 0x14 ); }
		inline int* color0() { return MakePointerGEN< int >( this, 0x4 ); }
		inline int* enhanceEffectID() { return MakePointerGEN< int >( this, 0x18 ); }
		inline char* changeParity() { return MakePointerGEN< char >( this, 0x1c ); }
	}; // Fail count = 1
	struct CHeroes_AI_BaseActor_OverMediumSizeOnly
	{
		struct CBindingData
		{
			inline int* bindingCount() { return MakePointerGEN< int >( this, 0x4 ); }
			inline int* pinUpCount() { return MakePointerGEN< int >( this, 0x8 ); }
			inline int* boneIndex0() { return MakePointerGEN< int >( this, 0xc ); }
			inline Vector* targetPos0() { return MakePointerGEN< Vector >( this, 0x4c ); }
			inline int* pBindingPlayer0() { return MakePointerGEN< int >( this, 0x10c ); }
		}; // Fail count = 3
		inline CBindingData* bindingData() { return MakePointerGEN< CBindingData >( this, 0xfe0 ); }
		inline int* limbDominateStates0() { return MakePointerGEN< int >( this, 0x112c ); }
	}; // Fail count = 1
	struct CDUEL_CONTROLLER_MONSTER_DATA
	{
		struct CDUEL_CONTROLLER_DATA
		{
			inline EHANDLE* hDuelTarget() { return MakePointerGEN< EHANDLE >( this, 0x8 ); }
			inline int* isReadyToDuel() { return MakePointerGEN< int >( this, 0xc ); }
			inline int* isDuelBegin() { return MakePointerGEN< int >( this, 0xd ); }
			inline float* duelStance() { return MakePointerGEN< float >( this, 0x10 ); }
			inline int* isDuelCompeting() { return MakePointerGEN< int >( this, 0x14 ); }
			inline int* duelTypeProxy() { return MakePointerGEN< int >( this, 0x58 ); }
		}; // Fail count = 1
		inline CDUEL_CONTROLLER_DATA* duelController() { return MakePointerGEN< CDUEL_CONTROLLER_DATA >( this, 0x4 ); }
	};
	struct CFRAME_SYNCHRONIZER_DATA
	{
		inline int* isSynchronizing() { return MakePointerGEN< int >( this, 0x4 ); }
		inline EHANDLE* hLeader() { return MakePointerGEN< EHANDLE >( this, 0x8 ); }
		inline EHANDLE* hFollower() { return MakePointerGEN< EHANDLE >( this, 0xc ); }
		inline int* syncSequenceLeader() { return MakePointerGEN< int >( this, 0x10 ); }
		inline int* syncSequenceFollower() { return MakePointerGEN< int >( this, 0x14 ); }
		inline int* frameOffset() { return MakePointerGEN< int >( this, 0x18 ); }
	};
	inline EHANDLE* hitPositionCapabilities() { return MakePointerGEN< EHANDLE >( this, 0xe98 ); }
	inline int* downFacing() { return MakePointerGEN< int >( this, 0xe9c ); }
	inline int* postureState() { return MakePointerGEN< int >( this, 0xea0 ); }
	inline int* isSuperArmorNoDownMode() { return MakePointerGEN< int >( this, 0xf64 ); }
	inline int* isSuperArmor() { return MakePointerGEN< int >( this, 0xf65 ); }
	inline int* npcSizeType() { return MakePointerGEN< int >( this, 0xf68 ); }
	inline int* unconditionalAttack() { return MakePointerGEN< int >( this, 0xf6c ); }
	inline int* ATK() { return MakePointerGEN< int >( this, 0xf70 ); }
	inline int* DEF() { return MakePointerGEN< int >( this, 0xf74 ); }
	inline int* DEFNaked() { return MakePointerGEN< int >( this, 0xf78 ); }
	inline int* ATKBonusHero() { return MakePointerGEN< int >( this, 0xf7c ); }
	inline int* collisionUpdateAll() { return MakePointerGEN< int >( this, 0xf81 ); }
	inline int* isGrapplingable() { return MakePointerGEN< int >( this, 0xf80 ); }
	inline int* isGrapplingNow() { return MakePointerGEN< int >( this, 0xf82 ); }
	inline bool* bBigBloodEffectEnabled() { return MakePointerGEN< bool >( this, 0xf88 ); }
	inline bool* bNoBloodEffect() { return MakePointerGEN< bool >( this, 0xf89 ); }
	inline bool* bHitGroupFlinchEnabled() { return MakePointerGEN< bool >( this, 0xf8a ); }
	inline bool* bGuardActivated() { return MakePointerGEN< bool >( this, 0xf8b ); }
	inline float* guardAllowingAngle() { return MakePointerGEN< float >( this, 0xf8c ); }
	inline bool* bDiableIKHeight() { return MakePointerGEN< bool >( this, 0xf90 ); }
	inline int* isInvincible() { return MakePointerGEN< int >( this, 0xf91 ); }
	inline EHANDLE* hIgnoredAttacker() { return MakePointerGEN< EHANDLE >( this, 0xf94 ); }
	inline int* lastMoveParent() { return MakePointerGEN< int >( this, 0xf98 ); }
	inline int* talkEnable() { return MakePointerGEN< int >( this, 0x1228 ); }
	inline CHEROES_MATERIAL_GAME_DATA* materialGameData() { return MakePointerGEN< CHEROES_MATERIAL_GAME_DATA >( this, 0xf9c ); }
	inline CHeroes_AI_BaseActor_OverMediumSizeOnly* baseactor_over_medium_size_only() { return MakePointerGEN< CHeroes_AI_BaseActor_OverMediumSizeOnly >( this, 0x0 ); }
	inline int* nDropItem() { return MakePointerGEN< int >( this, 0x126c ); }
	inline bool* bBoss() { return MakePointerGEN< bool >( this, 0x1269 ); }
	inline int* lootedPlayerIndex0() { return MakePointerGEN< int >( this, 0x1270 ); }
	inline EHANDLE* hGroundEntity() { return MakePointerGEN< EHANDLE >( this, 0x1e0 ); }
	inline int* curBrokenModel() { return MakePointerGEN< int >( this, 0x114c ); }
	inline bool* bShouldKeepAttackCollision() { return MakePointerGEN< bool >( this, 0x1154 ); }
	inline int* isRagdollFlying() { return MakePointerGEN< int >( this, 0x129c ); }
	inline int* isBossNamingSceneable() { return MakePointerGEN< int >( this, 0x129d ); }
	inline Vector* localBBoxOffset() { return MakePointerGEN< Vector >( this, 0xe60 ); }
	inline int* isBBoxOffsetEnable() { return MakePointerGEN< int >( this, 0xe6c ); }
	inline Vector* VPhysicsShadowMins() { return MakePointerGEN< Vector >( this, 0xe7c ); }
	inline Vector* VPhysicsShadowMaxs() { return MakePointerGEN< Vector >( this, 0xe88 ); }
	inline int* isVPhysicsShadowBBoxOverrided() { return MakePointerGEN< int >( this, 0xe94 ); }
	inline EHANDLE* hGoldCoreOwner() { return MakePointerGEN< EHANDLE >( this, 0x12a0 ); }
	inline int* eliteLevel() { return MakePointerGEN< int >( this, 0x12c4 ); }
	inline bool* bDisableEliteEffect() { return MakePointerGEN< bool >( this, 0x12c8 ); }
	inline int* isResetRotateInterp() { return MakePointerGEN< int >( this, 0x12d1 ); }
	inline int* isResetRotateInterpCheckBit() { return MakePointerGEN< int >( this, 0x12d4 ); }
	inline int* eliteGlowBlink() { return MakePointerGEN< int >( this, 0x12d0 ); }
	inline int* materialModificationStatus() { return MakePointerGEN< int >( this, 0x12d8 ); }
	inline int* shouldDrawOwnerName() { return MakePointerGEN< int >( this, 0x12dc ); }
	inline CDUEL_CONTROLLER_MONSTER_DATA* duelControllerMonster() { return MakePointerGEN< CDUEL_CONTROLLER_MONSTER_DATA >( this, 0x12e0 ); }
	inline int* rapidGrapplingType() { return MakePointerGEN< int >( this, 0x1364 ); }
	inline CFRAME_SYNCHRONIZER_DATA* frameSynchronizer() { return MakePointerGEN< CFRAME_SYNCHRONIZER_DATA >( this, 0x136c ); }
	inline float* criticalDmgFactor() { return MakePointerGEN< float >( this, 0x1388 ); }
	inline int* criticalHitRatio() { return MakePointerGEN< int >( this, 0x138c ); }
	inline int* criticalResistance() { return MakePointerGEN< int >( this, 0x1390 ); }
	inline int* isBeginRapidGrappling() { return MakePointerGEN< int >( this, 0x1368 ); }
}; // Fail count = 5
struct GenDT_NPC_Succubus : public GenDT_Heroes_AI_BaseActor
{
	inline bool* bIsInHasteMode() { return MakePointerGEN< bool >( this, 0x13b8 ); }
};
struct GenDT_NPC_PropGolem : public GenDT_Heroes_AI_BaseActor
{
	inline int* updateHitboxCollisionCheckerID() { return MakePointerGEN< int >( this, 0x13d0 ); }
	inline Vector* updateHitboxCollisionCheckerMins() { return MakePointerGEN< Vector >( this, 0x13d4 ); }
	inline Vector* updateHitboxCollisionCheckerMaxs() { return MakePointerGEN< Vector >( this, 0x13e0 ); }
	inline float* attackDamageMultiply() { return MakePointerGEN< float >( this, 0x13c0 ); }
	inline float* attackDownDamageMultiply() { return MakePointerGEN< float >( this, 0x13cc ); }
};
struct GenDT_NPC_PlayerCutSceneActor : public GenDT_Heroes_AI_BaseActor
{
	struct CHEROES_NPC_COSTUME_LOADABLE_DATA
	{
		struct CHEROES_COSTUME_DATA
		{
			inline int* serialList0() { return MakePointerGEN< int >( this, 0x7c ); }
			inline bool* brokenList0() { return MakePointerGEN< bool >( this, 0xa4 ); }
			inline bool* brokenList() { return MakePointerGEN< bool >( this, 0x0 ); } // Array size = 10
			inline int* color0() { return MakePointerGEN< int >( this, 0xb0 ); }
			inline int* pollutionList0() { return MakePointerGEN< int >( this, 0x128 ); }
			inline int* faceLayerList0() { return MakePointerGEN< int >( this, 0x178 ); }
			inline int* faceLayerList() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 6
			inline int* faceLayerColor0() { return MakePointerGEN< int >( this, 0x190 ); }
			inline int* faceLayerColor() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 18
			inline int* lookList0() { return MakePointerGEN< int >( this, 0x150 ); }
			inline int* facePaintRotate() { return MakePointerGEN< int >( this, 0x1d8 ); }
			inline int* facePaintX() { return MakePointerGEN< int >( this, 0x1dc ); }
			inline int* facePaintY() { return MakePointerGEN< int >( this, 0x1e0 ); }
			inline int* facePaintScale() { return MakePointerGEN< int >( this, 0x1e4 ); }
			inline int* faceShinenessLevel() { return MakePointerGEN< int >( this, 0x1e8 ); }
			inline bool* bodyLayerList0() { return MakePointerGEN< bool >( this, 0x1ec ); }
			inline bool* bodyLayerList() { return MakePointerGEN< bool >( this, 0x0 ); }
			inline bool* bodyLayerColor0() { return MakePointerGEN< bool >( this, 0x1f0 ); }
			inline bool* bodyLayerColor() { return MakePointerGEN< bool >( this, 0x0 ); } // Array size = 3
			inline bool* bodyPaintSurfaceSide() { return MakePointerGEN< bool >( this, 0x1fc ); }
			inline bool* bodyPaintRotateZ() { return MakePointerGEN< bool >( this, 0x200 ); }
			inline bool* bodyPaintX() { return MakePointerGEN< bool >( this, 0x204 ); }
			inline bool* bodyPaintY() { return MakePointerGEN< bool >( this, 0x208 ); }
			inline bool* bodyPaintScale() { return MakePointerGEN< bool >( this, 0x20c ); }
			inline bool* bodyPaintClip() { return MakePointerGEN< bool >( this, 0x210 ); }
			inline bool* bodyPaintBlend() { return MakePointerGEN< bool >( this, 0x214 ); }
			inline char* changeParity() { return MakePointerGEN< char >( this, 0x218 ); }
			inline int* enhanceEffectPartIndex0() { return MakePointerGEN< int >( this, 0x234 ); }
			inline int* enhanceEffectValue0() { return MakePointerGEN< int >( this, 0x274 ); }
			inline int* costumeSkins0() { return MakePointerGEN< int >( this, 0x2d0 ); }
			inline int* costumeBodies0() { return MakePointerGEN< int >( this, 0x2f8 ); }
		}; // Fail count = 8
		inline CHEROES_COSTUME_DATA* curCostumeData() { return MakePointerGEN< CHEROES_COSTUME_DATA >( this, 0x4 ); }
	};
	inline CHEROES_NPC_COSTUME_LOADABLE_DATA* costumeLoadable() { return MakePointerGEN< CHEROES_NPC_COSTUME_LOADABLE_DATA >( this, 0x13b8 ); }
};
struct GenDT_NPC_Player : public GenDT_Heroes_AI_BaseActor
{
	struct CHEROES_NPC_COSTUME_LOADABLE_DATA
	{
		struct CHEROES_COSTUME_DATA
		{
			inline int* serialList0() { return MakePointerGEN< int >( this, 0x7c ); }
			inline bool* brokenList0() { return MakePointerGEN< bool >( this, 0xa4 ); }
			inline bool* brokenList() { return MakePointerGEN< bool >( this, 0x0 ); } // Array size = 10
			inline int* color0() { return MakePointerGEN< int >( this, 0xb0 ); }
			inline int* pollutionList0() { return MakePointerGEN< int >( this, 0x128 ); }
			inline int* faceLayerList0() { return MakePointerGEN< int >( this, 0x178 ); }
			inline int* faceLayerList() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 6
			inline int* faceLayerColor0() { return MakePointerGEN< int >( this, 0x190 ); }
			inline int* faceLayerColor() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 18
			inline int* lookList0() { return MakePointerGEN< int >( this, 0x150 ); }
			inline int* facePaintRotate() { return MakePointerGEN< int >( this, 0x1d8 ); }
			inline int* facePaintX() { return MakePointerGEN< int >( this, 0x1dc ); }
			inline int* facePaintY() { return MakePointerGEN< int >( this, 0x1e0 ); }
			inline int* facePaintScale() { return MakePointerGEN< int >( this, 0x1e4 ); }
			inline int* faceShinenessLevel() { return MakePointerGEN< int >( this, 0x1e8 ); }
			inline bool* bodyLayerList0() { return MakePointerGEN< bool >( this, 0x1ec ); }
			inline bool* bodyLayerList() { return MakePointerGEN< bool >( this, 0x0 ); }
			inline bool* bodyLayerColor0() { return MakePointerGEN< bool >( this, 0x1f0 ); }
			inline bool* bodyLayerColor() { return MakePointerGEN< bool >( this, 0x0 ); } // Array size = 3
			inline bool* bodyPaintSurfaceSide() { return MakePointerGEN< bool >( this, 0x1fc ); }
			inline bool* bodyPaintRotateZ() { return MakePointerGEN< bool >( this, 0x200 ); }
			inline bool* bodyPaintX() { return MakePointerGEN< bool >( this, 0x204 ); }
			inline bool* bodyPaintY() { return MakePointerGEN< bool >( this, 0x208 ); }
			inline bool* bodyPaintScale() { return MakePointerGEN< bool >( this, 0x20c ); }
			inline bool* bodyPaintClip() { return MakePointerGEN< bool >( this, 0x210 ); }
			inline bool* bodyPaintBlend() { return MakePointerGEN< bool >( this, 0x214 ); }
			inline char* changeParity() { return MakePointerGEN< char >( this, 0x218 ); }
			inline int* enhanceEffectPartIndex0() { return MakePointerGEN< int >( this, 0x234 ); }
			inline int* enhanceEffectValue0() { return MakePointerGEN< int >( this, 0x274 ); }
			inline int* costumeSkins0() { return MakePointerGEN< int >( this, 0x2d0 ); }
			inline int* costumeBodies0() { return MakePointerGEN< int >( this, 0x2f8 ); }
		}; // Fail count = 8
		inline CHEROES_COSTUME_DATA* curCostumeData() { return MakePointerGEN< CHEROES_COSTUME_DATA >( this, 0x4 ); }
	};
	inline CHEROES_NPC_COSTUME_LOADABLE_DATA* costumeLoadable() { return MakePointerGEN< CHEROES_NPC_COSTUME_LOADABLE_DATA >( this, 0x13b8 ); }
	inline int* titleId() { return MakePointerGEN< int >( this, 0x16dc ); }
	inline int* guildSN() { return MakePointerGEN< int >( this, 0x1760 ); }
	inline int* isCafe() { return MakePointerGEN< int >( this, 0x1864 ); }
	inline int* isReturn() { return MakePointerGEN< int >( this, 0x1865 ); }
	inline int* VIPCode() { return MakePointerGEN< int >( this, 0x1868 ); }
}; // Fail count = 2
struct GenDT_NPC_PlayerForCharacterSelection : public GenDT_NPC_Player
{
};
struct GenDT_NPC_ManKind : public GenDT_Heroes_AI_BaseActor
{
	struct CHEROES_NPC_COSTUME_LOADABLE_DATA
	{
		struct CHEROES_COSTUME_DATA
		{
			inline int* serialList0() { return MakePointerGEN< int >( this, 0x7c ); }
			inline bool* brokenList0() { return MakePointerGEN< bool >( this, 0xa4 ); }
			inline bool* brokenList() { return MakePointerGEN< bool >( this, 0x0 ); } // Array size = 10
			inline int* color0() { return MakePointerGEN< int >( this, 0xb0 ); }
			inline int* pollutionList0() { return MakePointerGEN< int >( this, 0x128 ); }
			inline int* faceLayerList0() { return MakePointerGEN< int >( this, 0x178 ); }
			inline int* faceLayerList() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 6
			inline int* faceLayerColor0() { return MakePointerGEN< int >( this, 0x190 ); }
			inline int* faceLayerColor() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 18
			inline int* lookList0() { return MakePointerGEN< int >( this, 0x150 ); }
			inline int* facePaintRotate() { return MakePointerGEN< int >( this, 0x1d8 ); }
			inline int* facePaintX() { return MakePointerGEN< int >( this, 0x1dc ); }
			inline int* facePaintY() { return MakePointerGEN< int >( this, 0x1e0 ); }
			inline int* facePaintScale() { return MakePointerGEN< int >( this, 0x1e4 ); }
			inline int* faceShinenessLevel() { return MakePointerGEN< int >( this, 0x1e8 ); }
			inline bool* bodyLayerList0() { return MakePointerGEN< bool >( this, 0x1ec ); }
			inline bool* bodyLayerList() { return MakePointerGEN< bool >( this, 0x0 ); }
			inline bool* bodyLayerColor0() { return MakePointerGEN< bool >( this, 0x1f0 ); }
			inline bool* bodyLayerColor() { return MakePointerGEN< bool >( this, 0x0 ); } // Array size = 3
			inline bool* bodyPaintSurfaceSide() { return MakePointerGEN< bool >( this, 0x1fc ); }
			inline bool* bodyPaintRotateZ() { return MakePointerGEN< bool >( this, 0x200 ); }
			inline bool* bodyPaintX() { return MakePointerGEN< bool >( this, 0x204 ); }
			inline bool* bodyPaintY() { return MakePointerGEN< bool >( this, 0x208 ); }
			inline bool* bodyPaintScale() { return MakePointerGEN< bool >( this, 0x20c ); }
			inline bool* bodyPaintClip() { return MakePointerGEN< bool >( this, 0x210 ); }
			inline bool* bodyPaintBlend() { return MakePointerGEN< bool >( this, 0x214 ); }
			inline char* changeParity() { return MakePointerGEN< char >( this, 0x218 ); }
			inline int* enhanceEffectPartIndex0() { return MakePointerGEN< int >( this, 0x234 ); }
			inline int* enhanceEffectValue0() { return MakePointerGEN< int >( this, 0x274 ); }
			inline int* costumeSkins0() { return MakePointerGEN< int >( this, 0x2d0 ); }
			inline int* costumeBodies0() { return MakePointerGEN< int >( this, 0x2f8 ); }
		}; // Fail count = 8
		inline CHEROES_COSTUME_DATA* curCostumeData() { return MakePointerGEN< CHEROES_COSTUME_DATA >( this, 0x4 ); }
	};
	inline CHEROES_NPC_COSTUME_LOADABLE_DATA* costumeLoadable() { return MakePointerGEN< CHEROES_NPC_COSTUME_LOADABLE_DATA >( this, 0x13b8 ); }
};
struct GenDT_NPC_Kobold : public GenDT_Heroes_AI_BaseActor
{
};
struct GenDT_NPC_Fish : public GenDT_Heroes_AI_BaseActor
{
	inline EHANDLE* hOwner() { return MakePointerGEN< EHANDLE >( this, 0x13b8 ); }
	inline bool* bMonster() { return MakePointerGEN< bool >( this, 0x13bc ); }
};
struct GenDT_WeaponFragThrower : public GenDT_WeaponRangeBase
{
};
struct GenDT_BreakableProp : public GenDT_BaseAnimating
{
	inline int* iHealth() { return MakePointerGEN< int >( this, 0x88 ); }
};
struct GenDT_PhysicsProp : public GenDT_BreakableProp
{
	inline int* liftableType() { return MakePointerGEN< int >( this, 0x8e8 ); }
	inline int* collideWithPlayerType() { return MakePointerGEN< int >( this, 0x8ec ); }
	inline bool* bAwake() { return MakePointerGEN< bool >( this, 0x908 ); }
	inline Vector* collisionMins() { return MakePointerGEN< Vector >( this, 0x8f0 ); }
	inline Vector* collisionMaxs() { return MakePointerGEN< Vector >( this, 0x8fc ); }
};
struct GenDT_PhysicsPropMultiplayer : public GenDT_PhysicsProp
{
	inline int* iPhysicsMode() { return MakePointerGEN< int >( this, 0x914 ); }
	inline int* fMass() { return MakePointerGEN< int >( this, 0x918 ); }
};
struct GenDT_RangeBaseProjectile : public GenDT_PhysicsPropMultiplayer
{
};
struct GenDT_TimebombProjectile : public GenDT_RangeBaseProjectile
{
	inline float* detonateTime() { return MakePointerGEN< float >( this, 0x920 ); }
};
struct GenDT_HeroesBaseFrag : public GenDT_RangeBaseProjectile
{
	inline float* detonateTime() { return MakePointerGEN< float >( this, 0x920 ); }
};
struct GenDT_BasePinupable : public GenDT_RangeBaseProjectile
{
	inline int* pTargetNpc() { return MakePointerGEN< int >( this, 0x920 ); }
	inline int* pinnupBoneIndex() { return MakePointerGEN< int >( this, 0x924 ); }
};
struct GenDT_HeroesShield : public GenDT_BaseAnimating
{
	struct CHEROES_MATERIAL_GAME_DATA
	{
		inline int* materialType() { return MakePointerGEN< int >( this, 0x10 ); }
		inline int* pollution() { return MakePointerGEN< int >( this, 0x14 ); }
		inline int* color0() { return MakePointerGEN< int >( this, 0x4 ); }
		inline int* enhanceEffectID() { return MakePointerGEN< int >( this, 0x18 ); }
		inline char* changeParity() { return MakePointerGEN< char >( this, 0x1c ); }
	}; // Fail count = 1
	inline CHEROES_MATERIAL_GAME_DATA* shieldMaterialData() { return MakePointerGEN< CHEROES_MATERIAL_GAME_DATA >( this, 0x8e8 ); }
	inline int* isBroken() { return MakePointerGEN< int >( this, 0x92c ); }
	inline EHANDLE* hParent() { return MakePointerGEN< EHANDLE >( this, 0x930 ); }
	inline int* normalModelName() { return MakePointerGEN< int >( this, 0x934 ); }
	inline int* isShieldEquipped() { return MakePointerGEN< int >( this, 0xa38 ); }
	inline int* shieldUpdateBit() { return MakePointerGEN< int >( this, 0xa39 ); }
	inline float* maxDurability() { return MakePointerGEN< float >( this, 0xa3c ); }
	inline float* curDurability() { return MakePointerGEN< float >( this, 0xa40 ); }
}; // Fail count = 1
struct GenDT_BasePlayer : public GenDT_BaseCombatCharacter
{
	struct CLocalPlayerExclusive
	{
		struct CLocal
		{
			inline char* chAreaBits() { return MakePointerGEN< char >( this, 0x4 ); } // Array size = 32
			inline char* chAreaPortalBits() { return MakePointerGEN< char >( this, 0x24 ); } // Array size = 24
			inline int* iHideHUD() { return MakePointerGEN< int >( this, 0x3c ); }
			inline float* flFOVRate() { return MakePointerGEN< float >( this, 0x40 ); }
			inline bool* bDucked() { return MakePointerGEN< bool >( this, 0x44 ); }
			inline bool* bDucking() { return MakePointerGEN< bool >( this, 0x45 ); }
			inline bool* bInDuckJump() { return MakePointerGEN< bool >( this, 0x46 ); }
			inline float* flDucktime() { return MakePointerGEN< float >( this, 0x48 ); }
			inline float* flDuckJumpTime() { return MakePointerGEN< float >( this, 0x4c ); }
			inline float* flJumpTime() { return MakePointerGEN< float >( this, 0x50 ); }
			inline float* flFallVelocity() { return MakePointerGEN< float >( this, 0x58 ); }
			inline Vector* vecPunchAngle() { return MakePointerGEN< Vector >( this, 0x6c ); }
			inline Vector* vecPunchAngleVel() { return MakePointerGEN< Vector >( this, 0xa4 ); }
			inline bool* bDrawViewmodel() { return MakePointerGEN< bool >( this, 0xb0 ); }
			inline bool* bWearingSuit() { return MakePointerGEN< bool >( this, 0xb1 ); }
			inline bool* bPoisoned() { return MakePointerGEN< bool >( this, 0xb2 ); }
			inline float* flStepSize() { return MakePointerGEN< float >( this, 0xb4 ); }
			inline bool* bAllowAutoMovement() { return MakePointerGEN< bool >( this, 0xb8 ); }
			inline int* skybox3d_scale() { return MakePointerGEN< int >( this, 0xc0 ); }
			inline Vector* skybox3d_origin() { return MakePointerGEN< Vector >( this, 0xc4 ); }
			inline int* skybox3d_area() { return MakePointerGEN< int >( this, 0xd0 ); }
			inline int* skybox3d_fog_enable() { return MakePointerGEN< int >( this, 0xd8 ); }
			inline int* skybox3d_fog_blend() { return MakePointerGEN< int >( this, 0xd9 ); }
			inline Vector* skybox3d_fog_dirPrimary() { return MakePointerGEN< Vector >( this, 0xdc ); }
			inline int* skybox3d_fog_colorPrimary() { return MakePointerGEN< int >( this, 0xe8 ); }
			inline int* skybox3d_fog_colorSecondary() { return MakePointerGEN< int >( this, 0xec ); }
			inline float* skybox3d_fog_start() { return MakePointerGEN< float >( this, 0xf0 ); }
			inline float* skybox3d_fog_end() { return MakePointerGEN< float >( this, 0xf4 ); }
			inline int* fog_enable() { return MakePointerGEN< int >( this, 0x118 ); }
			inline int* fog_blend() { return MakePointerGEN< int >( this, 0x119 ); }
			inline int* fog_dirPrimary() { return MakePointerGEN< int >( this, 0x11c ); }
			inline int* fog_colorPrimary() { return MakePointerGEN< int >( this, 0x128 ); }
			inline int* fog_colorSecondary() { return MakePointerGEN< int >( this, 0x12c ); }
			inline int* fog_start() { return MakePointerGEN< int >( this, 0x130 ); }
			inline int* fog_end() { return MakePointerGEN< int >( this, 0x134 ); }
			inline int* fog_farz() { return MakePointerGEN< int >( this, 0x138 ); }
			inline int* fog_colorPrimaryLerpTo() { return MakePointerGEN< int >( this, 0x13c ); }
			inline int* fog_colorSecondaryLerpTo() { return MakePointerGEN< int >( this, 0x140 ); }
			inline int* fog_startLerpTo() { return MakePointerGEN< int >( this, 0x144 ); }
			inline int* fog_endLerpTo() { return MakePointerGEN< int >( this, 0x148 ); }
			inline int* fog_lerptime() { return MakePointerGEN< int >( this, 0x14c ); }
			inline int* fog_duration() { return MakePointerGEN< int >( this, 0x150 ); }
			inline Vector* audio_localSound0() { return MakePointerGEN< Vector >( this, 0x158 ); }
			inline Vector* audio_localSound1() { return MakePointerGEN< Vector >( this, 0x164 ); }
			inline Vector* audio_localSound2() { return MakePointerGEN< Vector >( this, 0x170 ); }
			inline Vector* audio_localSound3() { return MakePointerGEN< Vector >( this, 0x17c ); }
			inline Vector* audio_localSound4() { return MakePointerGEN< Vector >( this, 0x188 ); }
			inline Vector* audio_localSound5() { return MakePointerGEN< Vector >( this, 0x194 ); }
			inline Vector* audio_localSound6() { return MakePointerGEN< Vector >( this, 0x1a0 ); }
			inline Vector* audio_localSound7() { return MakePointerGEN< Vector >( this, 0x1ac ); }
			inline int* audio_soundscapeIndex() { return MakePointerGEN< int >( this, 0x1b8 ); }
			inline int* audio_localBits() { return MakePointerGEN< int >( this, 0x1bc ); }
			inline int* audio_ent() { return MakePointerGEN< int >( this, 0x1c0 ); }
		};
		inline CLocal* Local() { return MakePointerGEN< CLocal >( this, 0xe4c ); }
		inline Vector* vecViewOffset0() { return MakePointerGEN< Vector >( this, 0xd4 ); }
		inline Vector* vecViewOffset1() { return MakePointerGEN< Vector >( this, 0xd8 ); }
		inline Vector* vecViewOffset2() { return MakePointerGEN< Vector >( this, 0xdc ); }
		inline float* flFriction() { return MakePointerGEN< float >( this, 0x1e8 ); }
		inline int* iAmmo() { return MakePointerGEN< int >( this, 0xc48 ); } // Array size = 32
		inline int* fOnTarget() { return MakePointerGEN< int >( this, 0x1038 ); }
		inline int* nTickBase() { return MakePointerGEN< int >( this, 0x1114 ); }
		inline int* nNextThinkTick() { return MakePointerGEN< int >( this, 0x7c ); }
		inline EHANDLE* hLastWeapon() { return MakePointerGEN< EHANDLE >( this, 0x1124 ); }
		inline EHANDLE* hGroundEntity() { return MakePointerGEN< EHANDLE >( this, 0x1e0 ); }
		inline Vector* vecVelocity0() { return MakePointerGEN< Vector >( this, 0xe0 ); }
		inline Vector* vecVelocity1() { return MakePointerGEN< Vector >( this, 0xe4 ); }
		inline Vector* vecVelocity2() { return MakePointerGEN< Vector >( this, 0xe8 ); }
		inline Vector* vecBaseVelocity() { return MakePointerGEN< Vector >( this, 0x114 ); }
		inline EHANDLE* hConstraintEntity() { return MakePointerGEN< EHANDLE >( this, 0x1070 ); }
		inline Vector* vecConstraintCenter() { return MakePointerGEN< Vector >( this, 0x1074 ); }
		inline float* flConstraintRadius() { return MakePointerGEN< float >( this, 0x1080 ); }
		inline float* flConstraintWidth() { return MakePointerGEN< float >( this, 0x1084 ); }
		inline float* flConstraintSpeedFactor() { return MakePointerGEN< float >( this, 0x1088 ); }
		inline float* flDeathTime() { return MakePointerGEN< float >( this, 0x1098 ); }
		inline int* nWaterLevel() { return MakePointerGEN< int >( this, 0x148 ); }
		inline float* flLaggedMovementValue() { return MakePointerGEN< float >( this, 0x12b4 ); }
	};
	struct CPlayerState
	{
		inline int* deadflag() { return MakePointerGEN< int >( this, 0x4 ); }
	};
	inline CLocalPlayerExclusive* localdata() { return MakePointerGEN< CLocalPlayerExclusive >( this, 0x0 ); }
	inline CPlayerState* pl() { return MakePointerGEN< CPlayerState >( this, 0x1014 ); }
	inline int* iFOV() { return MakePointerGEN< int >( this, 0x1028 ); }
	inline int* iDefaultFOV() { return MakePointerGEN< int >( this, 0x1034 ); }
	inline EHANDLE* hVehicle() { return MakePointerGEN< EHANDLE >( this, 0x10a0 ); }
	inline EHANDLE* hUseEntity() { return MakePointerGEN< EHANDLE >( this, 0x10a8 ); }
	inline int* lifeState() { return MakePointerGEN< int >( this, 0x87 ); }
	inline float* flMaxspeed() { return MakePointerGEN< float >( this, 0x10ac ); }
	inline int* fFlags() { return MakePointerGEN< int >( this, 0x2ec ); }
	inline int* iObserverMode() { return MakePointerGEN< int >( this, 0x108c ); }
	inline EHANDLE* hObserverTarget() { return MakePointerGEN< EHANDLE >( this, 0x1090 ); }
	inline EHANDLE* hViewModel0() { return MakePointerGEN< EHANDLE >( this, 0x113c ); }
	inline EHANDLE* hViewModel() { return MakePointerGEN< EHANDLE >( this, 0x0 ); } // Array size = 2
	inline char** szLastPlaceName() { return MakePointerGEN< char* >( this, 0x12c8 ); }
};
struct GenDT_HeroesPlayer : public GenDT_BasePlayer
{
	struct CHEROES_COSTUME_DATA
	{
		inline int* serialList0() { return MakePointerGEN< int >( this, 0x7c ); }
		inline bool* brokenList0() { return MakePointerGEN< bool >( this, 0xa4 ); }
		inline bool* brokenList() { return MakePointerGEN< bool >( this, 0x0 ); } // Array size = 10
		inline int* color0() { return MakePointerGEN< int >( this, 0xb0 ); }
		inline int* pollutionList0() { return MakePointerGEN< int >( this, 0x128 ); }
		inline int* faceLayerList0() { return MakePointerGEN< int >( this, 0x178 ); }
		inline int* faceLayerList() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 6
		inline int* faceLayerColor0() { return MakePointerGEN< int >( this, 0x190 ); }
		inline int* faceLayerColor() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 18
		inline int* lookList0() { return MakePointerGEN< int >( this, 0x150 ); }
		inline int* facePaintRotate() { return MakePointerGEN< int >( this, 0x1d8 ); }
		inline int* facePaintX() { return MakePointerGEN< int >( this, 0x1dc ); }
		inline int* facePaintY() { return MakePointerGEN< int >( this, 0x1e0 ); }
		inline int* facePaintScale() { return MakePointerGEN< int >( this, 0x1e4 ); }
		inline int* faceShinenessLevel() { return MakePointerGEN< int >( this, 0x1e8 ); }
		inline bool* bodyLayerList0() { return MakePointerGEN< bool >( this, 0x1ec ); }
		inline bool* bodyLayerList() { return MakePointerGEN< bool >( this, 0x0 ); }
		inline bool* bodyLayerColor0() { return MakePointerGEN< bool >( this, 0x1f0 ); }
		inline bool* bodyLayerColor() { return MakePointerGEN< bool >( this, 0x0 ); } // Array size = 3
		inline bool* bodyPaintSurfaceSide() { return MakePointerGEN< bool >( this, 0x1fc ); }
		inline bool* bodyPaintRotateZ() { return MakePointerGEN< bool >( this, 0x200 ); }
		inline bool* bodyPaintX() { return MakePointerGEN< bool >( this, 0x204 ); }
		inline bool* bodyPaintY() { return MakePointerGEN< bool >( this, 0x208 ); }
		inline bool* bodyPaintScale() { return MakePointerGEN< bool >( this, 0x20c ); }
		inline bool* bodyPaintClip() { return MakePointerGEN< bool >( this, 0x210 ); }
		inline bool* bodyPaintBlend() { return MakePointerGEN< bool >( this, 0x214 ); }
		inline char* changeParity() { return MakePointerGEN< char >( this, 0x218 ); }
		inline int* enhanceEffectPartIndex0() { return MakePointerGEN< int >( this, 0x234 ); }
		inline int* enhanceEffectValue0() { return MakePointerGEN< int >( this, 0x274 ); }
		inline int* costumeSkins0() { return MakePointerGEN< int >( this, 0x2d0 ); }
		inline int* costumeBodies0() { return MakePointerGEN< int >( this, 0x2f8 ); }
	}; // Fail count = 8
	struct CHEROES_ACCESSORY_GAME_DATA
	{
		inline int* serialList0() { return MakePointerGEN< int >( this, 0x64 ); }
		inline int* color0() { return MakePointerGEN< int >( this, 0x7c ); }
	}; // Fail count = 2
	struct CHEROES_ARMOR_DATA
	{
		inline float* curArmorDurability0() { return MakePointerGEN< float >( this, 0x4 ); }
		inline float* maxArmorDurability0() { return MakePointerGEN< float >( this, 0x2c ); }
	}; // Fail count = 2
	struct CHEROES_QUICKSLOT_GAME_DATA
	{
		inline int* itemIDList0() { return MakePointerGEN< int >( this, 0x4 ); }
		inline int* itemIDList() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 5
		inline int* itemCountList0() { return MakePointerGEN< int >( this, 0x18 ); }
		inline int* itemCountList() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 5
		inline int* itemDraftList0() { return MakePointerGEN< int >( this, 0x2c ); }
		inline int* itemDraftList() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 5
		inline int* itemClassList0() { return MakePointerGEN< int >( this, 0x40 ); }
		inline int* itemClassList() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 5
	};
	struct CHEROES_STAT_GAME_DATA
	{
		inline int* addedStatList0() { return MakePointerGEN< int >( this, 0x4 ); }
		inline int* lastStatList0() { return MakePointerGEN< int >( this, 0x90 ); }
	}; // Fail count = 2
	struct CPLAYER_ACTION_STATE_SHARED_DATA
	{
		inline int* restrictedStateList0() { return MakePointerGEN< int >( this, 0x4 ); }
		inline int* iEventProxy() { return MakePointerGEN< int >( this, 0x2c ); }
		inline int* weaponSub() { return MakePointerGEN< int >( this, 0x284 ); }
	}; // Fail count = 3
	struct CSTATUS_EFFECT_SHARED_DATA
	{
		inline int* indexList0() { return MakePointerGEN< int >( this, 0x4 ); }
		inline int* indexList() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 10
		inline bool* beginTimeList0() { return MakePointerGEN< bool >( this, 0x2c ); }
		inline bool* beginTimeList() { return MakePointerGEN< bool >( this, 0x0 ); } // Array size = 10
	};
	struct CHEROES_SPSKILL
	{
		inline int* SPSkillSlot0() { return MakePointerGEN< int >( this, 0x8 ); }
		inline int* usableSPSkillSlot0() { return MakePointerGEN< int >( this, 0x28 ); }
		inline float* SPGauge() { return MakePointerGEN< float >( this, 0x30 ); }
		inline float* maxSPGauge() { return MakePointerGEN< float >( this, 0x34 ); }
		inline int* existSPSkill() { return MakePointerGEN< int >( this, 0x38 ); }
		inline int* curSelectedSPSlot() { return MakePointerGEN< int >( this, 0x3c ); }
	}; // Fail count = 2
	struct CPVP_GRAPPLING
	{
		inline EHANDLE* hGrapplingTarget() { return MakePointerGEN< EHANDLE >( this, 0x8 ); }
		inline Vector* grapplingPos() { return MakePointerGEN< Vector >( this, 0xc ); }
		inline Vector* grapplingAng() { return MakePointerGEN< Vector >( this, 0x18 ); }
	};
	struct CHEROES_PLAYERANIMSTATE_EVENT_DATA
	{
		inline int* iEvent() { return MakePointerGEN< int >( this, 0x8 ); }
		inline int* iSequence() { return MakePointerGEN< int >( this, 0xc ); }
		inline int* iChangeParity() { return MakePointerGEN< int >( this, 0x10 ); }
	};
	struct CHEROES_PLAYER_METAMORPHOSIS_DATA
	{
		struct CHEROES_PALADINSHIELD
		{
			inline int* isEnabled() { return MakePointerGEN< int >( this, 0x8 ); }
			inline float* paladinShieldHP() { return MakePointerGEN< float >( this, 0xc ); }
			inline float* paladinShieldMaxHP() { return MakePointerGEN< float >( this, 0x10 ); }
		};
		inline int* isActive() { return MakePointerGEN< int >( this, 0x4 ); }
		inline float* playbackRateByFigureHeightRatio() { return MakePointerGEN< float >( this, 0x14 ); }
		inline int* figureHeightRatio() { return MakePointerGEN< int >( this, 0x18 ); }
		inline float* attackHitLatchTimeRatio() { return MakePointerGEN< float >( this, 0x1c ); }
		inline int* vocationLevel() { return MakePointerGEN< int >( this, 0xc ); }
		inline int* metamorphosisLevel() { return MakePointerGEN< int >( this, 0x10 ); }
		inline int* addedStatList0() { return MakePointerGEN< int >( this, 0x20 ); }
		inline float* projectileRangeRatio() { return MakePointerGEN< float >( this, 0xac ); }
		inline float* projectileDamageRangeRatio() { return MakePointerGEN< float >( this, 0xb0 ); }
		inline float* attackCollisionRangeRatio() { return MakePointerGEN< float >( this, 0xb4 ); }
		inline int* impulsedamageAdder() { return MakePointerGEN< int >( this, 0xb8 ); }
		inline int* impulseRagdollDownDamageAdder() { return MakePointerGEN< int >( this, 0xbc ); }
		inline CHEROES_PALADINSHIELD* paladinShield() { return MakePointerGEN< CHEROES_PALADINSHIELD >( this, 0xc0 ); }
	}; // Fail count = 1
	inline int* iPlayerState() { return MakePointerGEN< int >( this, 0x138c ); }
	inline int* iClass() { return MakePointerGEN< int >( this, 0x13d4 ); }
	inline QAngle* angEyeAngles0() { return MakePointerGEN< QAngle >( this, 0x13d8 ); }
	inline QAngle* angEyeAngles1() { return MakePointerGEN< QAngle >( this, 0x13dc ); }
	inline float* flStamina() { return MakePointerGEN< float >( this, 0x1390 ); }
	inline Vector* vecRagdollVelocity() { return MakePointerGEN< Vector >( this, 0x13e8 ); }
	inline float* flFlashDuration() { return MakePointerGEN< float >( this, 0x13ac ); }
	inline float* flFlashMaxAlpha() { return MakePointerGEN< float >( this, 0x13a8 ); }
	inline CHEROES_COSTUME_DATA* playerCostumeData() { return MakePointerGEN< CHEROES_COSTUME_DATA >( this, 0x1458 ); }
	inline CHEROES_ACCESSORY_GAME_DATA* accessoryGameData() { return MakePointerGEN< CHEROES_ACCESSORY_GAME_DATA >( this, 0x1778 ); }
	inline Vector* vecLastAimTargetPos() { return MakePointerGEN< Vector >( this, 0x1878 ); }
	inline EHANDLE* hCurAimTarget() { return MakePointerGEN< EHANDLE >( this, 0x1884 ); }
	inline int* activatedSubWeaponIndex() { return MakePointerGEN< int >( this, 0x2584 ); }
	inline EHANDLE* hLastThrownJavelin() { return MakePointerGEN< EHANDLE >( this, 0x2588 ); }
	inline float* flBulletViewFinishTime() { return MakePointerGEN< float >( this, 0x258c ); }
	inline bool* bTouchingItem() { return MakePointerGEN< bool >( this, 0x2590 ); }
	inline int* isFallingHeight() { return MakePointerGEN< int >( this, 0x1365 ); }
	inline float* staminaUsageModifierAdder() { return MakePointerGEN< float >( this, 0x2594 ); }
	inline float* staminaUsageModifierMultiplier() { return MakePointerGEN< float >( this, 0x2598 ); }
	inline float* lastTeleportTime() { return MakePointerGEN< float >( this, 0x259c ); }
	inline float* attackMotionSpeedStatusEffect() { return MakePointerGEN< float >( this, 0x25a0 ); }
	inline float* downResistanceRatioModifier() { return MakePointerGEN< float >( this, 0x25a4 ); }
	inline float* criticalHitRatioModifier() { return MakePointerGEN< float >( this, 0x25a8 ); }
	inline float* totalDamageRatioModifier() { return MakePointerGEN< float >( this, 0x25ac ); }
	inline float* magicCriticalHitRatioModifier() { return MakePointerGEN< float >( this, 0x25b0 ); }
	inline int* isForceMagicCritical() { return MakePointerGEN< int >( this, 0x25b4 ); }
	inline CHEROES_ARMOR_DATA* armorData() { return MakePointerGEN< CHEROES_ARMOR_DATA >( this, 0x19bc ); }
	inline CHEROES_QUICKSLOT_GAME_DATA* quickSlotGameData() { return MakePointerGEN< CHEROES_QUICKSLOT_GAME_DATA >( this, 0x1a10 ); }
	inline CHEROES_STAT_GAME_DATA* statGameData() { return MakePointerGEN< CHEROES_STAT_GAME_DATA >( this, 0x1f4c ); }
	inline int* spawnPendingExp() { return MakePointerGEN< int >( this, 0x20f8 ); }
	inline EHANDLE* hShield() { return MakePointerGEN< EHANDLE >( this, 0x210c ); }
	inline EHANDLE* hGroundEntity() { return MakePointerGEN< EHANDLE >( this, 0x1e0 ); }
	inline int* isPushingPhysicsObject() { return MakePointerGEN< int >( this, 0x2110 ); }
	inline int* LastPushingEntity() { return MakePointerGEN< int >( this, 0x2114 ); }
	inline EHANDLE* hHandActionTarget() { return MakePointerGEN< EHANDLE >( this, 0x25b8 ); }
	inline CPLAYER_ACTION_STATE_SHARED_DATA* actionStateSharedData() { return MakePointerGEN< CPLAYER_ACTION_STATE_SHARED_DATA >( this, 0x25cc ); }
	inline Vector* curLadderNormal() { return MakePointerGEN< Vector >( this, 0x253c ); }
	inline Vector* curLadderPosition() { return MakePointerGEN< Vector >( this, 0x2548 ); }
	inline int* curLadderState() { return MakePointerGEN< int >( this, 0x2554 ); }
	inline EHANDLE* hasLadder_nextPlayerPos() { return MakePointerGEN< EHANDLE >( this, 0x2558 ); }
	inline Vector* ladder_nextPlayerPos() { return MakePointerGEN< Vector >( this, 0x255c ); }
	inline Vector* ladder_nextPlayerAng() { return MakePointerGEN< Vector >( this, 0x2568 ); }
	inline int* myTitleID() { return MakePointerGEN< int >( this, 0x2248 ); }
	inline int* isCafe() { return MakePointerGEN< int >( this, 0x244a ); }
	inline int* isReturn() { return MakePointerGEN< int >( this, 0x244b ); }
	inline int* VIPCode() { return MakePointerGEN< int >( this, 0x244c ); }
	inline EHANDLE* hLastPrimaryWeapon() { return MakePointerGEN< EHANDLE >( this, 0x2574 ); }
	inline EHANDLE* hTargetEvilCore() { return MakePointerGEN< EHANDLE >( this, 0x2450 ); }
	inline EHANDLE* hTargetCollect() { return MakePointerGEN< EHANDLE >( this, 0x2454 ); }
	inline EHANDLE* hTargetFish() { return MakePointerGEN< EHANDLE >( this, 0x2458 ); }
	inline EHANDLE* hReviveTarget() { return MakePointerGEN< EHANDLE >( this, 0x245c ); }
	inline CSTATUS_EFFECT_SHARED_DATA* statusEffectSharedData() { return MakePointerGEN< CSTATUS_EFFECT_SHARED_DATA >( this, 0x2470 ); }
	inline CSTATUS_EFFECT_SHARED_DATA* serverSideEffectSharedData() { return MakePointerGEN< CSTATUS_EFFECT_SHARED_DATA >( this, 0x24c4 ); }
	inline int* isInputDisabled() { return MakePointerGEN< int >( this, 0x2518 ); }
	inline int* cameraEnemyTarget() { return MakePointerGEN< int >( this, 0x2140 ); }
	inline int* eyeTarget() { return MakePointerGEN< int >( this, 0x2144 ); }
	inline Vector* eyeTargetPos() { return MakePointerGEN< Vector >( this, 0x2148 ); }
	inline int* camLookAtTarget() { return MakePointerGEN< int >( this, 0x2154 ); }
	inline int* canStareEnemy() { return MakePointerGEN< int >( this, 0x2158 ); }
	inline int* townActionState() { return MakePointerGEN< int >( this, 0x215c ); }
	inline Vector* townActionTargetPos() { return MakePointerGEN< Vector >( this, 0x2160 ); }
	inline int* isAtTownCampfire() { return MakePointerGEN< int >( this, 0x216c ); }
	inline CHEROES_SPSKILL* spSkillManager() { return MakePointerGEN< CHEROES_SPSKILL >( this, 0x285c ); }
	inline EHANDLE* hCampfireAnvil() { return MakePointerGEN< EHANDLE >( this, 0x289c ); }
	inline EHANDLE* hSelectedPartyMember() { return MakePointerGEN< EHANDLE >( this, 0x28c0 ); }
	inline int* invincibleStatusEffectCount() { return MakePointerGEN< int >( this, 0x28cc ); }
	inline int* superArmorStatusEffectCount() { return MakePointerGEN< int >( this, 0x28d0 ); }
	inline CPVP_GRAPPLING* pvpGrappling() { return MakePointerGEN< CPVP_GRAPPLING >( this, 0x28d8 ); }
	inline CHEROES_PLAYERANIMSTATE_EVENT_DATA* playerAnimStateEvent() { return MakePointerGEN< CHEROES_PLAYERANIMSTATE_EVENT_DATA >( this, 0x2908 ); }
	inline CHEROES_PLAYER_METAMORPHOSIS_DATA* pMetamorphosis() { return MakePointerGEN< CHEROES_PLAYER_METAMORPHOSIS_DATA >( this, 0x2920 ); }
	inline EHANDLE* hTargetVehicle() { return MakePointerGEN< EHANDLE >( this, 0x29fc ); }
	inline EHANDLE* hTargetConstruction() { return MakePointerGEN< EHANDLE >( this, 0x2a00 ); }
	inline int* isConstructing() { return MakePointerGEN< int >( this, 0x2a04 ); }
	inline EHANDLE* hFreeMatch() { return MakePointerGEN< EHANDLE >( this, 0x2a08 ); }
	inline int* isCameramanMode() { return MakePointerGEN< int >( this, 0x2a0c ); }
	inline int* initiallyEquippedMainWeaponClass() { return MakePointerGEN< int >( this, 0x2578 ); }
}; // Fail count = 3
struct GenDT_HeroesPlayerLethita : public GenDT_HeroesPlayer
{
};
struct GenDT_HeroesPlayerKay : public GenDT_HeroesPlayer
{
	inline int* showAimGuide() { return MakePointerGEN< int >( this, 0x2a19 ); }
	inline float* curAimGuideVelocity() { return MakePointerGEN< float >( this, 0x2a1c ); }
	inline float* curAimGuideGravityScale() { return MakePointerGEN< float >( this, 0x2a20 ); }
};
struct GenDT_HeroesPlayerKalok : public GenDT_HeroesPlayer
{
	struct CHEROES_PLAYER_RAPID_GRAPPLING_DATA
	{
		inline EHANDLE* hGrapplingCandidateBoss() { return MakePointerGEN< EHANDLE >( this, 0x4 ); }
		inline EHANDLE* hGrapplingCandidateNormal() { return MakePointerGEN< EHANDLE >( this, 0x8 ); }
		inline EHANDLE* hGrapplingCandidateMulti_1() { return MakePointerGEN< EHANDLE >( this, 0xc ); }
		inline EHANDLE* hGrapplingCandidateMulti_2() { return MakePointerGEN< EHANDLE >( this, 0x10 ); }
		inline EHANDLE* hLastGrapplingTargetBoss() { return MakePointerGEN< EHANDLE >( this, 0x14 ); }
		inline EHANDLE* hLastGrapplingTargetNormal() { return MakePointerGEN< EHANDLE >( this, 0x18 ); }
		inline EHANDLE* hLastGrapplingTargetMulti_1() { return MakePointerGEN< EHANDLE >( this, 0x1c ); }
		inline EHANDLE* hLastGrapplingTargetMulti_2() { return MakePointerGEN< EHANDLE >( this, 0x20 ); }
		inline int* isAttached() { return MakePointerGEN< int >( this, 0x24 ); }
	};
	struct CDUEL_CONTROLLER_PLAYER_DATA
	{
		struct CDUEL_CONTROLLER_DATA
		{
			inline EHANDLE* hDuelTarget() { return MakePointerGEN< EHANDLE >( this, 0x8 ); }
			inline int* isReadyToDuel() { return MakePointerGEN< int >( this, 0xc ); }
			inline int* isDuelBegin() { return MakePointerGEN< int >( this, 0xd ); }
			inline float* duelStance() { return MakePointerGEN< float >( this, 0x10 ); }
			inline int* isDuelCompeting() { return MakePointerGEN< int >( this, 0x14 ); }
			inline int* duelTypeProxy() { return MakePointerGEN< int >( this, 0x58 ); }
		}; // Fail count = 1
		inline CDUEL_CONTROLLER_DATA* duelController() { return MakePointerGEN< CDUEL_CONTROLLER_DATA >( this, 0x4 ); }
	};
	struct CWEAPON_TRHOWABLE_DATA
	{
		inline EHANDLE* hDropWeapon() { return MakePointerGEN< EHANDLE >( this, 0x8 ); }
		inline int* nextLiftableTime() { return MakePointerGEN< int >( this, 0xc ); }
	};
	inline CHEROES_PLAYER_RAPID_GRAPPLING_DATA* rapidGrappling() { return MakePointerGEN< CHEROES_PLAYER_RAPID_GRAPPLING_DATA >( this, 0x2a18 ); }
	inline CDUEL_CONTROLLER_PLAYER_DATA* duelControllerPlayer() { return MakePointerGEN< CDUEL_CONTROLLER_PLAYER_DATA >( this, 0x2a6c ); }
	inline CWEAPON_TRHOWABLE_DATA* weaponThrowable() { return MakePointerGEN< CWEAPON_TRHOWABLE_DATA >( this, 0x2aec ); }
};
struct GenDT_HeroesPlayerFiona : public GenDT_HeroesPlayer
{
};
struct GenDT_HeroesPlayerEvy : public GenDT_HeroesPlayer
{
	struct CHEROES_PLAYER_SCYTHE_BIND_STRING_DATA
	{
		inline EHANDLE* hTarget() { return MakePointerGEN< EHANDLE >( this, 0x1c ); }
		inline Vector* lastAttackPos() { return MakePointerGEN< Vector >( this, 0x20 ); }
	};
	struct CHEROES_PLAYER_SCYTHE_DRAG_RAGDOLL_DATA
	{
		inline EHANDLE* hTarget() { return MakePointerGEN< EHANDLE >( this, 0x8 ); }
		inline int* isRagdollDragging() { return MakePointerGEN< int >( this, 0xc ); }
		inline int* isBegin() { return MakePointerGEN< int >( this, 0xd ); }
	};
	struct CHEROES_MANASHIELD
	{
		inline int* isEnabled() { return MakePointerGEN< int >( this, 0x8 ); }
		inline float* manaShieldHP() { return MakePointerGEN< float >( this, 0xc ); }
		inline float* manaShieldMaxHP() { return MakePointerGEN< float >( this, 0x10 ); }
		inline float* manaShieldDEF() { return MakePointerGEN< float >( this, 0x14 ); }
	};
	inline CHEROES_PLAYER_SCYTHE_BIND_STRING_DATA* scytheBindString() { return MakePointerGEN< CHEROES_PLAYER_SCYTHE_BIND_STRING_DATA >( this, 0x2a18 ); }
	inline CHEROES_PLAYER_SCYTHE_DRAG_RAGDOLL_DATA* scytheDragRagdoll() { return MakePointerGEN< CHEROES_PLAYER_SCYTHE_DRAG_RAGDOLL_DATA >( this, 0x2a64 ); }
	inline CHEROES_MANASHIELD* manaShield() { return MakePointerGEN< CHEROES_MANASHIELD >( this, 0x2ab0 ); }
	inline int* curMagicCycle() { return MakePointerGEN< int >( this, 0x2ae0 ); }
	inline char* chargeCoolTime0() { return MakePointerGEN< char >( this, 0x2ae4 ); }
	inline char* chargeCoolTime() { return MakePointerGEN< char >( this, 0x0 ); } // Array size = 20
	inline int* isBubbleBallBegined() { return MakePointerGEN< int >( this, 0x2acc ); }
	inline int* isFeverMode() { return MakePointerGEN< int >( this, 0x2adc ); }
	inline float* reverseGravityDuration() { return MakePointerGEN< float >( this, 0x2b34 ); }
};
struct GenDT_BubbleBall : public GenDT_PhysicsPropMultiplayer
{
};
struct GenDT_HeroesEnvEffectExecutor : public GenDT_BaseEntity
{
	inline int* startDisabled() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline int* refreshCount() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2d4 ); }
	inline QAngle* angRotation() { return MakePointerGEN< QAngle >( this, 0x2e0 ); }
	inline int* moveparent() { return MakePointerGEN< int >( this, 0x160 ); }
}; // Fail count = 1
struct GenDT_PointText : public GenDT_BaseEntity
{
	inline int* fontSize() { return MakePointerGEN< int >( this, 0x628 ); }
	inline int* color() { return MakePointerGEN< int >( this, 0x62c ); }
	inline float* duration() { return MakePointerGEN< float >( this, 0x630 ); }
	inline int* effect() { return MakePointerGEN< int >( this, 0x634 ); }
	inline float* fadeOutDistMin() { return MakePointerGEN< float >( this, 0x638 ); }
	inline float* fadeOutDistMax() { return MakePointerGEN< float >( this, 0x63c ); }
	inline int* isShow() { return MakePointerGEN< int >( this, 0x640 ); }
}; // Fail count = 2
struct GenDT_HeroesScreen : public GenDT_BaseEntity
{
	inline float* flWidth() { return MakePointerGEN< float >( this, 0x4f0 ); }
	inline float* flHeight() { return MakePointerGEN< float >( this, 0x4f4 ); }
	inline int* fScreenFlags() { return MakePointerGEN< int >( this, 0x51c ); }
	inline int* nPanelName() { return MakePointerGEN< int >( this, 0x4f8 ); }
	inline int* nAttachmentIndex() { return MakePointerGEN< int >( this, 0x514 ); }
	inline int* nOverlayMaterial() { return MakePointerGEN< int >( this, 0x518 ); }
	inline int* iconName() { return MakePointerGEN< int >( this, 0x5b8 ); }
	inline int* facingMode() { return MakePointerGEN< int >( this, 0x5f8 ); }
}; // Fail count = 2
struct GenDT_TriggerPuddle : public GenDT_BaseEntity
{
	inline float* currentChargeCount() { return MakePointerGEN< float >( this, 0x6f0 ); }
}; // Fail count = 2
struct GenDT_TriggerCamera : public GenDT_BaseEntity
{
	inline int* fov() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline int* enableFovAttachment() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline int* iParentFovAttachment() { return MakePointerGEN< int >( this, 0x4f0 ); }
};
struct GenDT_ScriptGame : public GenDT_BaseEntity
{
	inline int* tickStatusChanged() { return MakePointerGEN< int >( this, 0xfe8 ); }
	inline int* tickResultChanged() { return MakePointerGEN< int >( this, 0xfec ); }
	inline int* clientTags0() { return MakePointerGEN< int >( this, 0xff0 ); }
}; // Fail count = 3
struct GenDT_ScriptListener : public GenDT_BaseEntity
{
};
struct GenDT_ScoreCTF : public GenDT_BaseEntity
{
	inline int* scoreBlue() { return MakePointerGEN< int >( this, 0x524 ); }
	inline int* scoreRed() { return MakePointerGEN< int >( this, 0x528 ); }
	inline int* pvpStatus() { return MakePointerGEN< int >( this, 0x5dc ); }
	inline float* statusEndTime() { return MakePointerGEN< float >( this, 0x5e0 ); }
	inline int* totals0() { return MakePointerGEN< int >( this, 0x52c ); }
	inline int* deaths0() { return MakePointerGEN< int >( this, 0x558 ); }
	inline int* kills0() { return MakePointerGEN< int >( this, 0x584 ); }
	inline int* tags0() { return MakePointerGEN< int >( this, 0x5b0 ); }
}; // Fail count = 4
struct GenDT_PropCTF : public GenDT_PhysicsPropMultiplayer
{
	inline EHANDLE* hLiftOwner() { return MakePointerGEN< EHANDLE >( this, 0x920 ); }
}; // Fail count = 1
struct GenDT_Team
{
	inline int* iTeamNum() { return MakePointerGEN< int >( this, 0x52c ); }
	inline int* iScore() { return MakePointerGEN< int >( this, 0x51c ); }
	inline char** szTeamname() { return MakePointerGEN< char* >( this, 0x4fc ); }
}; // Fail count = 2
struct GenDT_HeroesTeam : public GenDT_Team
{
};
struct GenDT_RopeKeyframe
{
	inline int* iRopeMaterialModel() { return MakePointerGEN< int >( this, 0x528 ); }
	inline EHANDLE* hStartPoint() { return MakePointerGEN< EHANDLE >( this, 0x7bc ); }
	inline EHANDLE* hEndPoint() { return MakePointerGEN< EHANDLE >( this, 0x7c0 ); }
	inline int* iStartAttachment() { return MakePointerGEN< int >( this, 0x7c4 ); }
	inline int* iEndAttachment() { return MakePointerGEN< int >( this, 0x7c6 ); }
	inline int* fLockedPoints() { return MakePointerGEN< int >( this, 0x7d8 ); }
	inline int* Slack() { return MakePointerGEN< int >( this, 0x7d0 ); }
	inline int* RopeLength() { return MakePointerGEN< int >( this, 0x7cc ); }
	inline int* RopeFlags() { return MakePointerGEN< int >( this, 0x524 ); }
	inline float* TextureScale() { return MakePointerGEN< float >( this, 0x7d4 ); }
	inline int* nSegments() { return MakePointerGEN< int >( this, 0x7b8 ); }
	inline int* Subdiv() { return MakePointerGEN< int >( this, 0x7c8 ); }
	inline float* Width() { return MakePointerGEN< float >( this, 0x7dc ); }
	inline float* flScrollSpeed() { return MakePointerGEN< float >( this, 0x520 ); }
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2d4 ); }
	inline int* moveparent() { return MakePointerGEN< int >( this, 0x160 ); }
	inline int* iParentAttachment() { return MakePointerGEN< int >( this, 0x13c ); }
};
struct GenDT_HeroesRagdollBlender
{
	inline Vector* ragdollAngleArray0() { return MakePointerGEN< Vector >( this, 0x6b8 ); }
	inline Vector* ragdollPosArray0() { return MakePointerGEN< Vector >( this, 0x598 ); }
	inline Vector* ragdollPos() { return MakePointerGEN< Vector >( this, 0x7d8 ); }
	inline Vector* ragdollAngle() { return MakePointerGEN< Vector >( this, 0x7e4 ); }
	inline Vector* ragdollForceVector() { return MakePointerGEN< Vector >( this, 0x7f0 ); }
	inline int* ragdollForceBoneIndex() { return MakePointerGEN< int >( this, 0x7fc ); }
	inline int* isBlendingEnabled() { return MakePointerGEN< int >( this, 0x800 ); }
	inline int* isAllBlendingFactorZero() { return MakePointerGEN< int >( this, 0x801 ); }
	inline int* isStatue() { return MakePointerGEN< int >( this, 0x802 ); }
	inline int* useSequenceAsLocalBone() { return MakePointerGEN< int >( this, 0x80c ); }
	inline float* unragdollStartTime() { return MakePointerGEN< float >( this, 0x810 ); }
	inline float* unragdollTimeTotal() { return MakePointerGEN< float >( this, 0x814 ); }
	inline float* unragdollYawBias() { return MakePointerGEN< float >( this, 0x818 ); }
	inline EHANDLE* hParent() { return MakePointerGEN< EHANDLE >( this, 0x804 ); }
	inline int* ragdollNetType() { return MakePointerGEN< int >( this, 0x808 ); }
}; // Fail count = 2
struct GenDT_PlayerResource
{
	inline int* iPing() { return MakePointerGEN< int >( this, 0x90c ); } // Array size = 33
	inline int* iPacketloss() { return MakePointerGEN< int >( this, 0x990 ); } // Array size = 33
	inline int* iScore() { return MakePointerGEN< int >( this, 0xa14 ); } // Array size = 33
	inline int* iDeaths() { return MakePointerGEN< int >( this, 0xa98 ); } // Array size = 33
	inline bool* bConnected() { return MakePointerGEN< bool >( this, 0xb1c ); } // Array size = 33
	inline int* iTeam() { return MakePointerGEN< int >( this, 0xb40 ); } // Array size = 33
	inline bool* bAlive() { return MakePointerGEN< bool >( this, 0xbc4 ); } // Array size = 33
	inline int* iHealth() { return MakePointerGEN< int >( this, 0xbe8 ); } // Array size = 33
};
struct GenDT_HeroesPlayerResource : public GenDT_PlayerResource
{
};
struct GenDT_HeroesCollectibleItem : public GenDT_BaseAnimating
{
	inline EHANDLE* hItemOwner() { return MakePointerGEN< EHANDLE >( this, 0xc68 ); }
	inline int* isLooted() { return MakePointerGEN< int >( this, 0xc6c ); }
}; // Fail count = 2
struct GenDT_HeroesFishingItemBox : public GenDT_HeroesCollectibleItem
{
	inline bool* bShouldDraw() { return MakePointerGEN< bool >( this, 0xcf0 ); }
};
struct GenDT_HeroesServerErg : public GenDT_BaseAnimating
{
	inline int* Quantity() { return MakePointerGEN< int >( this, 0x8e8 ); }
};
struct GenDT_FuncBrush : public GenDT_BaseEntity
{
};
struct GenDT_Breakable : public GenDT_BaseEntity
{
	inline int* iHealth() { return MakePointerGEN< int >( this, 0x88 ); }
};
struct GenDT_GoldenBall : public GenDT_PhysicsPropMultiplayer
{
};
struct GenDT_FuncRotating : public GenDT_BaseEntity
{
	inline Vector* cVecMoveAng() { return MakePointerGEN< Vector >( this, 0x504 ); }
	inline Vector* cAngStart() { return MakePointerGEN< Vector >( this, 0x510 ); }
	inline float* flFanFriction() { return MakePointerGEN< float >( this, 0x51c ); }
	inline float* flAttenuation() { return MakePointerGEN< float >( this, 0x520 ); }
	inline float* flVolume() { return MakePointerGEN< float >( this, 0x524 ); }
	inline float* flTargetSpeed() { return MakePointerGEN< float >( this, 0x528 ); }
	inline float* flMaxSpeed() { return MakePointerGEN< float >( this, 0x52c ); }
	inline bool* bStopAtStartPos() { return MakePointerGEN< bool >( this, 0x530 ); }
	inline bool* bReversed() { return MakePointerGEN< bool >( this, 0x531 ); }
	inline int* isClientsimulation() { return MakePointerGEN< int >( this, 0x532 ); }
};
struct GenDT_ChannelPortal : public GenDT_BaseAnimating
{
	inline int* ChannelNumber() { return MakePointerGEN< int >( this, 0x908 ); }
}; // Fail count = 1
struct GenDT_PropBeanBag : public GenDT_PhysicsPropMultiplayer
{
};
struct GenDT_PropGourd : public GenDT_PhysicsProp
{
};
struct GenDT_WeaponCubemap : public GenDT_BaseCombatWeapon
{
};
struct GenDT_WeaponCycler : public GenDT_BaseCombatWeapon
{
};
struct GenDT_PvPFreeMatchRule : public GenDT_BaseEntity
{
	inline EHANDLE* hPlayer1() { return MakePointerGEN< EHANDLE >( this, 0x4e8 ); }
	inline EHANDLE* hPlayer2() { return MakePointerGEN< EHANDLE >( this, 0x4ec ); }
	inline int* options0() { return MakePointerGEN< int >( this, 0x4f0 ); }
	inline int* modifier1() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline int* modifier2() { return MakePointerGEN< int >( this, 0x4f8 ); }
	inline int* state1() { return MakePointerGEN< int >( this, 0x4fc ); }
	inline int* state2() { return MakePointerGEN< int >( this, 0x500 ); }
}; // Fail count = 1
struct GenDT_TestTraceline
{
	inline int* clrRender() { return MakePointerGEN< int >( this, 0x58 ); }
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2d4 ); }
	inline QAngle* angRotation0() { return MakePointerGEN< QAngle >( this, 0x2e0 ); }
	inline QAngle* angRotation1() { return MakePointerGEN< QAngle >( this, 0x2e4 ); }
	inline QAngle* angRotation2() { return MakePointerGEN< QAngle >( this, 0x2e8 ); }
	inline int* moveparent() { return MakePointerGEN< int >( this, 0x160 ); }
};
struct GenDT_BaseTempEntity
{
};
struct GenDT_TEWorldDecal : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline int* nIndex() { return MakePointerGEN< int >( this, 0x1c ); }
};
struct GenDT_TESpriteSpray : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecDirection() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* fNoise() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* nCount() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* nSpeed() { return MakePointerGEN< int >( this, 0x2c ); }
};
struct GenDT_TESprite : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* fScale() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* nBrightness() { return MakePointerGEN< int >( this, 0x24 ); }
};
struct GenDT_TEParticleSystem : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin0() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecOrigin1() { return MakePointerGEN< Vector >( this, 0x14 ); }
	inline Vector* vecOrigin2() { return MakePointerGEN< Vector >( this, 0x18 ); }
};
struct GenDT_TESparks : public GenDT_TEParticleSystem
{
	inline int* nMagnitude() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* nTrailLength() { return MakePointerGEN< int >( this, 0x20 ); }
	inline Vector* vecDir() { return MakePointerGEN< Vector >( this, 0x24 ); }
};
struct GenDT_TESmoke : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* fScale() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* nFrameRate() { return MakePointerGEN< int >( this, 0x24 ); }
};
struct GenDT_TEShowLine : public GenDT_TEParticleSystem
{
	inline Vector* vecEnd() { return MakePointerGEN< Vector >( this, 0x1c ); }
};
struct GenDT_TEProjectedDecal : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline QAngle* angRotation() { return MakePointerGEN< QAngle >( this, 0x1c ); }
	inline float* flDistance() { return MakePointerGEN< float >( this, 0x28 ); }
	inline int* nIndex() { return MakePointerGEN< int >( this, 0x2c ); }
};
struct GenDT_TEPlayerDecal : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x14 ); }
	inline int* nEntity() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* nPlayer() { return MakePointerGEN< int >( this, 0x10 ); }
};
struct GenDT_TEPhysicsProp : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline QAngle* angRotation0() { return MakePointerGEN< QAngle >( this, 0x1c ); }
	inline QAngle* angRotation1() { return MakePointerGEN< QAngle >( this, 0x20 ); }
	inline QAngle* angRotation2() { return MakePointerGEN< QAngle >( this, 0x24 ); }
	inline Vector* vecVelocity() { return MakePointerGEN< Vector >( this, 0x28 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* nFlags() { return MakePointerGEN< int >( this, 0x3c ); }
	inline int* nSkin() { return MakePointerGEN< int >( this, 0x38 ); }
	inline int* nEffects() { return MakePointerGEN< int >( this, 0x40 ); }
	inline float* disposeDelay() { return MakePointerGEN< float >( this, 0x44 ); }
};
struct GenDT_TEMuzzleFlash : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecAngles() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline float* flScale() { return MakePointerGEN< float >( this, 0x28 ); }
	inline int* nType() { return MakePointerGEN< int >( this, 0x2c ); }
};
struct GenDT_TELargeFunnel : public GenDT_TEParticleSystem
{
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* nReversed() { return MakePointerGEN< int >( this, 0x20 ); }
};
struct GenDT_TEKillPlayerAttachments : public GenDT_BaseTempEntity
{
	inline int* nPlayer() { return MakePointerGEN< int >( this, 0x10 ); }
};
struct GenDT_TEImpact : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecNormal() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* iType() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* ucFlags() { return MakePointerGEN< int >( this, 0x2c ); }
};
struct GenDT_TEGlowSprite : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* fScale() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* fLife() { return MakePointerGEN< int >( this, 0x24 ); }
	inline int* nBrightness() { return MakePointerGEN< int >( this, 0x28 ); }
};
struct GenDT_TEShatterSurface : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecAngles() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline Vector* vecForce() { return MakePointerGEN< Vector >( this, 0x28 ); }
	inline Vector* vecForcePos() { return MakePointerGEN< Vector >( this, 0x34 ); }
	inline float* flWidth() { return MakePointerGEN< float >( this, 0x40 ); }
	inline float* flHeight() { return MakePointerGEN< float >( this, 0x44 ); }
	inline float* flShardSize() { return MakePointerGEN< float >( this, 0x48 ); }
	inline int* nSurfaceType() { return MakePointerGEN< int >( this, 0x50 ); }
	inline uchar* uchFrontColor0() { return MakePointerGEN< uchar >( this, 0x54 ); }
	inline uchar* uchFrontColor1() { return MakePointerGEN< uchar >( this, 0x55 ); }
	inline uchar* uchFrontColor2() { return MakePointerGEN< uchar >( this, 0x56 ); }
	inline uchar* uchBackColor0() { return MakePointerGEN< uchar >( this, 0x57 ); }
	inline uchar* uchBackColor1() { return MakePointerGEN< uchar >( this, 0x58 ); }
	inline uchar* uchBackColor2() { return MakePointerGEN< uchar >( this, 0x59 ); }
};
struct GenDT_TEFootprintDecal : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecDirection() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* nEntity() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* nIndex() { return MakePointerGEN< int >( this, 0x38 ); }
	inline char* chMaterialType() { return MakePointerGEN< char >( this, 0x3c ); }
};
struct GenDT_TEFizz : public GenDT_BaseTempEntity
{
	inline int* nEntity() { return MakePointerGEN< int >( this, 0x10 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x14 ); }
	inline int* nDensity() { return MakePointerGEN< int >( this, 0x18 ); }
	inline int* nCurrent() { return MakePointerGEN< int >( this, 0x1c ); }
};
struct GenDT_TEExplosion : public GenDT_TEParticleSystem
{
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* fScale() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* nFrameRate() { return MakePointerGEN< int >( this, 0x24 ); }
	inline int* nFlags() { return MakePointerGEN< int >( this, 0x28 ); }
	inline Vector* vecNormal() { return MakePointerGEN< Vector >( this, 0x2c ); }
	inline char* chMaterialType() { return MakePointerGEN< char >( this, 0x38 ); }
	inline int* nRadius() { return MakePointerGEN< int >( this, 0x3c ); }
	inline int* nMagnitude() { return MakePointerGEN< int >( this, 0x40 ); }
};
struct GenDT_TEEnergySplash
{
	inline Vector* vecPos() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecDir() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline bool* bExplosive() { return MakePointerGEN< bool >( this, 0x28 ); }
};
struct GenDT_TEEffectDispatch : public GenDT_BaseTempEntity
{
	struct CEffectData
	{
		inline float* vOrigin0() { return MakePointerGEN< float >( this, 0x0 ); }
		inline float* vOrigin1() { return MakePointerGEN< float >( this, 0x4 ); }
		inline float* vOrigin2() { return MakePointerGEN< float >( this, 0x8 ); }
		inline float* vStart0() { return MakePointerGEN< float >( this, 0xc ); }
		inline float* vStart1() { return MakePointerGEN< float >( this, 0x10 ); }
		inline float* vStart2() { return MakePointerGEN< float >( this, 0x14 ); }
		inline Vector* vAngles() { return MakePointerGEN< Vector >( this, 0x24 ); }
		inline Vector* vNormal() { return MakePointerGEN< Vector >( this, 0x18 ); }
		inline int* fFlags() { return MakePointerGEN< int >( this, 0x30 ); }
		inline float* flMagnitude() { return MakePointerGEN< float >( this, 0x3c ); }
		inline float* flScale() { return MakePointerGEN< float >( this, 0x38 ); }
		inline int* nAttachmentIndex() { return MakePointerGEN< int >( this, 0x44 ); }
		inline int* nSurfaceProp() { return MakePointerGEN< int >( this, 0x48 ); }
		inline int* iEffectName() { return MakePointerGEN< int >( this, 0x5c ); }
		inline int* iEffectArgs() { return MakePointerGEN< int >( this, 0x60 ); }
		inline int* nMaterial() { return MakePointerGEN< int >( this, 0x4c ); }
		inline int* nDamageType() { return MakePointerGEN< int >( this, 0x50 ); }
		inline int* nHitBox() { return MakePointerGEN< int >( this, 0x54 ); }
		inline int* entindex() { return MakePointerGEN< int >( this, 0x0 ); }
		inline int* nColor() { return MakePointerGEN< int >( this, 0x58 ); }
		inline float* flRadius() { return MakePointerGEN< float >( this, 0x40 ); }
	};
	inline CEffectData* EffectData() { return MakePointerGEN< CEffectData >( this, 0x10 ); }
};
struct GenDT_TEDynamicLight : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline int* r() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* g() { return MakePointerGEN< int >( this, 0x24 ); }
	inline int* b() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* exponent() { return MakePointerGEN< int >( this, 0x2c ); }
	inline int* fRadius() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* fTime() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* fDecay() { return MakePointerGEN< int >( this, 0x34 ); }
	inline bool* bCheap() { return MakePointerGEN< bool >( this, 0x38 ); }
};
struct GenDT_TEDecal : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecStart() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* nEntity() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* nHitbox() { return MakePointerGEN< int >( this, 0x2c ); }
	inline int* nIndex() { return MakePointerGEN< int >( this, 0x30 ); }
};
struct GenDT_TEBubbleTrail : public GenDT_BaseTempEntity
{
	inline Vector* vecMins() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecMaxs() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x2c ); }
	inline float* flWaterZ() { return MakePointerGEN< float >( this, 0x28 ); }
	inline int* nCount() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* fSpeed() { return MakePointerGEN< int >( this, 0x34 ); }
};
struct GenDT_TEBubbles : public GenDT_BaseTempEntity
{
	inline Vector* vecMins() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecMaxs() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x2c ); }
	inline int* fHeight() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* nCount() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* fSpeed() { return MakePointerGEN< int >( this, 0x34 ); }
};
struct GenDT_TEBSPDecal : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline int* nEntity() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* nIndex() { return MakePointerGEN< int >( this, 0x20 ); }
};
struct GenDT_TEBreakModel : public GenDT_BaseTempEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline QAngle* angRotation0() { return MakePointerGEN< QAngle >( this, 0x1c ); }
	inline QAngle* angRotation1() { return MakePointerGEN< QAngle >( this, 0x20 ); }
	inline QAngle* angRotation2() { return MakePointerGEN< QAngle >( this, 0x24 ); }
	inline Vector* vecSize() { return MakePointerGEN< Vector >( this, 0x28 ); }
	inline Vector* vecVelocity() { return MakePointerGEN< Vector >( this, 0x34 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x44 ); }
	inline int* nRandomization() { return MakePointerGEN< int >( this, 0x40 ); }
	inline int* nCount() { return MakePointerGEN< int >( this, 0x48 ); }
	inline int* fTime() { return MakePointerGEN< int >( this, 0x4c ); }
	inline int* nFlags() { return MakePointerGEN< int >( this, 0x50 ); }
};
struct GenDT_TEBloodStream : public GenDT_TEParticleSystem
{
	inline Vector* vecDirection() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* r() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* g() { return MakePointerGEN< int >( this, 0x2c ); }
	inline int* b() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* a() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* nAmount() { return MakePointerGEN< int >( this, 0x38 ); }
};
struct GenDT_TEBloodSprite
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecDirection() { return MakePointerGEN< Vector >( this, 0x1c ); }
	inline int* r() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* g() { return MakePointerGEN< int >( this, 0x2c ); }
	inline int* b() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* a() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* nSprayModel() { return MakePointerGEN< int >( this, 0x3c ); }
	inline int* nDropModel() { return MakePointerGEN< int >( this, 0x38 ); }
	inline int* nSize() { return MakePointerGEN< int >( this, 0x40 ); }
};
struct GenDT_TEBeamSpline
{
	inline int* nPoints() { return MakePointerGEN< int >( this, 0xd0 ); }
	inline Vector* vecPoints0() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecPoints() { return MakePointerGEN< Vector >( this, 0x0 ); } // Array size = 16
};
struct GenDT_BaseBeam
{
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x10 ); }
	inline int* nHaloIndex() { return MakePointerGEN< int >( this, 0x14 ); }
	inline int* nStartFrame() { return MakePointerGEN< int >( this, 0x18 ); }
	inline int* nFrameRate() { return MakePointerGEN< int >( this, 0x1c ); }
	inline int* fLife() { return MakePointerGEN< int >( this, 0x20 ); }
	inline int* fWidth() { return MakePointerGEN< int >( this, 0x24 ); }
	inline int* fEndWidth() { return MakePointerGEN< int >( this, 0x28 ); }
	inline int* nFadeLength() { return MakePointerGEN< int >( this, 0x2c ); }
	inline int* fAmplitude() { return MakePointerGEN< int >( this, 0x30 ); }
	inline int* nSpeed() { return MakePointerGEN< int >( this, 0x44 ); }
	inline int* r() { return MakePointerGEN< int >( this, 0x34 ); }
	inline int* g() { return MakePointerGEN< int >( this, 0x38 ); }
	inline int* b() { return MakePointerGEN< int >( this, 0x3c ); }
	inline int* a() { return MakePointerGEN< int >( this, 0x40 ); }
	inline int* nFlags() { return MakePointerGEN< int >( this, 0x48 ); }
};
struct GenDT_TEBeamRingPoint : public GenDT_BaseBeam
{
	inline Vector* vecCenter() { return MakePointerGEN< Vector >( this, 0x4c ); }
	inline float* flStartRadius() { return MakePointerGEN< float >( this, 0x58 ); }
	inline float* flEndRadius() { return MakePointerGEN< float >( this, 0x5c ); }
};
struct GenDT_TEBeamRing : public GenDT_BaseBeam
{
	inline int* nStartEntity() { return MakePointerGEN< int >( this, 0x4c ); }
	inline int* nEndEntity() { return MakePointerGEN< int >( this, 0x50 ); }
};
struct GenDT_TEBeamPoints : public GenDT_BaseBeam
{
	inline Vector* vecStartPoint() { return MakePointerGEN< Vector >( this, 0x4c ); }
	inline Vector* vecEndPoint() { return MakePointerGEN< Vector >( this, 0x58 ); }
};
struct GenDT_TEBeamLaser : public GenDT_BaseBeam
{
	inline int* nStartEntity() { return MakePointerGEN< int >( this, 0x4c ); }
	inline int* nEndEntity() { return MakePointerGEN< int >( this, 0x50 ); }
};
struct GenDT_TEBeamEnts : public GenDT_BaseBeam
{
	inline int* nStartEntity() { return MakePointerGEN< int >( this, 0x4c ); }
	inline int* nEndEntity() { return MakePointerGEN< int >( this, 0x50 ); }
};
struct GenDT_TEBeamEntPoint : public GenDT_BaseBeam
{
	inline int* nStartEntity() { return MakePointerGEN< int >( this, 0x4c ); }
	inline int* nEndEntity() { return MakePointerGEN< int >( this, 0x50 ); }
	inline Vector* vecStartPoint() { return MakePointerGEN< Vector >( this, 0x54 ); }
	inline Vector* vecEndPoint() { return MakePointerGEN< Vector >( this, 0x60 ); }
};
struct GenDT_TEMetalSparks
{
	inline Vector* vecPos() { return MakePointerGEN< Vector >( this, 0x10 ); }
	inline Vector* vecDir() { return MakePointerGEN< Vector >( this, 0x1c ); }
};
struct GenDT_TEArmorRicochet : public GenDT_TEMetalSparks
{
};
struct GenDT_BaseParticleEntity : public GenDT_BaseEntity
{
};
struct GenDT_SteamJet : public GenDT_BaseParticleEntity
{
	inline float* SpreadSpeed() { return MakePointerGEN< float >( this, 0x5e4 ); }
	inline float* Speed() { return MakePointerGEN< float >( this, 0x5e8 ); }
	inline float* StartSize() { return MakePointerGEN< float >( this, 0x5ec ); }
	inline float* EndSize() { return MakePointerGEN< float >( this, 0x5f0 ); }
	inline float* Rate() { return MakePointerGEN< float >( this, 0x5f4 ); }
	inline float* JetLength() { return MakePointerGEN< float >( this, 0x5f8 ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x5fc ); }
	inline bool* bFaceLeft() { return MakePointerGEN< bool >( this, 0x604 ); }
	inline int* nType() { return MakePointerGEN< int >( this, 0x600 ); }
	inline int* spawnflags() { return MakePointerGEN< int >( this, 0x608 ); }
	inline float* flRollSpeed() { return MakePointerGEN< float >( this, 0x60c ); }
};
struct GenDT_SmokeStack : public GenDT_BaseParticleEntity
{
	inline float* SpreadSpeed() { return MakePointerGEN< float >( this, 0x634 ); }
	inline float* Speed() { return MakePointerGEN< float >( this, 0x638 ); }
	inline float* StartSize() { return MakePointerGEN< float >( this, 0x63c ); }
	inline float* EndSize() { return MakePointerGEN< float >( this, 0x640 ); }
	inline float* Rate() { return MakePointerGEN< float >( this, 0x644 ); }
	inline float* JetLength() { return MakePointerGEN< float >( this, 0x648 ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x64c ); }
	inline float* flBaseSpread() { return MakePointerGEN< float >( this, 0x650 ); }
	inline float* flTwist() { return MakePointerGEN< float >( this, 0x6a4 ); }
	inline float* flRollSpeed() { return MakePointerGEN< float >( this, 0x6e0 ); }
	inline int* iMaterialModel() { return MakePointerGEN< int >( this, 0x6a8 ); }
	inline Vector* AmbientLight_m_vPos() { return MakePointerGEN< Vector >( this, 0x654 ); }
	inline Vector* AmbientLight_m_vColor() { return MakePointerGEN< Vector >( this, 0x660 ); }
	inline float* AmbientLight_m_flIntensity() { return MakePointerGEN< float >( this, 0x66c ); }
	inline Vector* DirLight_m_vPos() { return MakePointerGEN< Vector >( this, 0x670 ); }
	inline Vector* DirLight_m_vColor() { return MakePointerGEN< Vector >( this, 0x67c ); }
	inline float* DirLight_m_flIntensity() { return MakePointerGEN< float >( this, 0x688 ); }
	inline Vector* vWind() { return MakePointerGEN< Vector >( this, 0x698 ); }
};
struct GenDT_FireTrail : public GenDT_BaseParticleEntity
{
	inline int* nAttachment() { return MakePointerGEN< int >( this, 0x5e4 ); }
	inline float* flLifetime() { return MakePointerGEN< float >( this, 0x5e8 ); }
};
struct GenDT_SporeTrail : public GenDT_BaseParticleEntity
{
	inline float* flSpawnRate() { return MakePointerGEN< float >( this, 0x5ec ); }
	inline Vector* vecEndColor() { return MakePointerGEN< Vector >( this, 0x5e0 ); }
	inline float* flParticleLifetime() { return MakePointerGEN< float >( this, 0x5f0 ); }
	inline float* flStartSize() { return MakePointerGEN< float >( this, 0x5f4 ); }
	inline float* flEndSize() { return MakePointerGEN< float >( this, 0x5f8 ); }
	inline float* flSpawnRadius() { return MakePointerGEN< float >( this, 0x5fc ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x60c ); }
};
struct GenDT_SporeExplosion : public GenDT_BaseParticleEntity
{
	inline float* flSpawnRate() { return MakePointerGEN< float >( this, 0x5e4 ); }
	inline float* flParticleLifetime() { return MakePointerGEN< float >( this, 0x5e8 ); }
	inline float* flStartSize() { return MakePointerGEN< float >( this, 0x5ec ); }
	inline float* flEndSize() { return MakePointerGEN< float >( this, 0x5f0 ); }
	inline float* flSpawnRadius() { return MakePointerGEN< float >( this, 0x5f4 ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x5fc ); }
	inline bool* bDontRemove() { return MakePointerGEN< bool >( this, 0x5fd ); }
};
struct GenDT_RocketTrail : public GenDT_BaseParticleEntity
{
	inline float* SpawnRate() { return MakePointerGEN< float >( this, 0x5e4 ); }
	inline Vector* StartColor() { return MakePointerGEN< Vector >( this, 0x5e8 ); }
	inline Vector* EndColor() { return MakePointerGEN< Vector >( this, 0x5f4 ); }
	inline float* ParticleLifetime() { return MakePointerGEN< float >( this, 0x604 ); }
	inline float* StopEmitTime() { return MakePointerGEN< float >( this, 0x608 ); }
	inline float* MinSpeed() { return MakePointerGEN< float >( this, 0x60c ); }
	inline float* MaxSpeed() { return MakePointerGEN< float >( this, 0x610 ); }
	inline float* StartSize() { return MakePointerGEN< float >( this, 0x614 ); }
	inline float* EndSize() { return MakePointerGEN< float >( this, 0x618 ); }
	inline float* SpawnRadius() { return MakePointerGEN< float >( this, 0x61c ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x62c ); }
	inline int* nAttachment() { return MakePointerGEN< int >( this, 0x630 ); }
	inline float* Opacity() { return MakePointerGEN< float >( this, 0x600 ); }
	inline bool* bDamaged() { return MakePointerGEN< bool >( this, 0x62d ); }
	inline float* flFlareScale() { return MakePointerGEN< float >( this, 0x640 ); }
};
struct GenDT_SmokeTrail : public GenDT_BaseParticleEntity
{
	inline float* SpawnRate() { return MakePointerGEN< float >( this, 0x5e4 ); }
	inline Vector* StartColor() { return MakePointerGEN< Vector >( this, 0x5e8 ); }
	inline Vector* EndColor() { return MakePointerGEN< Vector >( this, 0x5f4 ); }
	inline float* ParticleLifetime() { return MakePointerGEN< float >( this, 0x604 ); }
	inline float* StopEmitTime() { return MakePointerGEN< float >( this, 0x608 ); }
	inline float* MinSpeed() { return MakePointerGEN< float >( this, 0x60c ); }
	inline float* MaxSpeed() { return MakePointerGEN< float >( this, 0x610 ); }
	inline float* MinDirectedSpeed() { return MakePointerGEN< float >( this, 0x614 ); }
	inline float* MaxDirectedSpeed() { return MakePointerGEN< float >( this, 0x618 ); }
	inline float* StartSize() { return MakePointerGEN< float >( this, 0x61c ); }
	inline float* EndSize() { return MakePointerGEN< float >( this, 0x620 ); }
	inline float* SpawnRadius() { return MakePointerGEN< float >( this, 0x624 ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x634 ); }
	inline int* nAttachment() { return MakePointerGEN< int >( this, 0x638 ); }
	inline float* Opacity() { return MakePointerGEN< float >( this, 0x600 ); }
};
struct GenDT_PropVehicleDriveable : public GenDT_BaseAnimating
{
	inline EHANDLE* hPlayer() { return MakePointerGEN< EHANDLE >( this, 0x8ec ); }
	inline int* nSpeed() { return MakePointerGEN< int >( this, 0x8f0 ); }
	inline int* nRPM() { return MakePointerGEN< int >( this, 0x8f4 ); }
	inline float* flThrottle() { return MakePointerGEN< float >( this, 0x8f8 ); }
	inline int* nBoostTimeLeft() { return MakePointerGEN< int >( this, 0x8fc ); }
	inline int* nHasBoost() { return MakePointerGEN< int >( this, 0x900 ); }
	inline int* nScannerDisabledWeapons() { return MakePointerGEN< int >( this, 0x904 ); }
	inline int* nScannerDisabledVehicle() { return MakePointerGEN< int >( this, 0x908 ); }
	inline bool* bEnterAnimOn() { return MakePointerGEN< bool >( this, 0x928 ); }
	inline bool* bExitAnimOn() { return MakePointerGEN< bool >( this, 0x929 ); }
	inline bool* bUnableToFire() { return MakePointerGEN< bool >( this, 0x975 ); }
	inline Vector* vecEyeExitEndpoint() { return MakePointerGEN< Vector >( this, 0x968 ); }
	inline bool* bHasGun() { return MakePointerGEN< bool >( this, 0x974 ); }
	inline Vector* vecGunCrosshair() { return MakePointerGEN< Vector >( this, 0x930 ); }
};
struct GenDT_ParticleSmokeGrenade : public GenDT_BaseParticleEntity
{
	inline float* flSpawnTime() { return MakePointerGEN< float >( this, 0x5f4 ); }
	inline float* FadeStartTime() { return MakePointerGEN< float >( this, 0x5f8 ); }
	inline float* FadeEndTime() { return MakePointerGEN< float >( this, 0x5fc ); }
	inline int* CurrentStage() { return MakePointerGEN< int >( this, 0x5e4 ); }
};
struct GenDT_ParticleFire
{
	inline Vector* vOrigin() { return MakePointerGEN< Vector >( this, 0x5ec ); }
	inline Vector* vDirection() { return MakePointerGEN< Vector >( this, 0x5f8 ); }
};
struct GenDT_MovieExplosion : public GenDT_BaseParticleEntity
{
};
struct GenDT_TEGaussExplosion : public GenDT_TEParticleSystem
{
	inline int* nType() { return MakePointerGEN< int >( this, 0x1c ); }
	inline Vector* vecDirection() { return MakePointerGEN< Vector >( this, 0x20 ); }
};
struct GenDT_QuadraticBeam : public GenDT_BaseEntity
{
	inline Vector* targetPosition() { return MakePointerGEN< Vector >( this, 0x4e8 ); }
	inline Vector* controlPosition() { return MakePointerGEN< Vector >( this, 0x4f4 ); }
	inline float* scrollRate() { return MakePointerGEN< float >( this, 0x500 ); }
	inline float* flWidth() { return MakePointerGEN< float >( this, 0x504 ); }
};
struct GenDT_Embers : public GenDT_BaseEntity
{
	inline int* nDensity() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline int* nLifetime() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline int* nSpeed() { return MakePointerGEN< int >( this, 0x4f0 ); }
	inline bool* bEmit() { return MakePointerGEN< bool >( this, 0x4f4 ); }
};
struct GenDT_EnvWind : public GenDT_BaseEntity
{
	struct CEnvWindShared
	{
		inline int* iMinWind() { return MakePointerGEN< int >( this, 0xc ); }
		inline int* iMaxWind() { return MakePointerGEN< int >( this, 0x10 ); }
		inline int* iMinGust() { return MakePointerGEN< int >( this, 0x14 ); }
		inline int* iMaxGust() { return MakePointerGEN< int >( this, 0x18 ); }
		inline float* flMinGustDelay() { return MakePointerGEN< float >( this, 0x1c ); }
		inline float* flMaxGustDelay() { return MakePointerGEN< float >( this, 0x20 ); }
		inline int* iGustDirYawChange() { return MakePointerGEN< int >( this, 0x28 ); }
		inline int* iGustDirPitchChange() { return MakePointerGEN< int >( this, 0x2c ); }
		inline int* iWindSeed() { return MakePointerGEN< int >( this, 0x8 ); }
		inline int* iInitialWindDirYaw() { return MakePointerGEN< int >( this, 0x40 ); }
		inline int* iInitialWindDirPitch() { return MakePointerGEN< int >( this, 0x44 ); }
		inline float* flInitialWindSpeed() { return MakePointerGEN< float >( this, 0x48 ); }
		inline float* flStartTime() { return MakePointerGEN< float >( this, 0x4 ); }
		inline float* flGustDuration() { return MakePointerGEN< float >( this, 0x24 ); }
	};
	inline CEnvWindShared* EnvWindShared() { return MakePointerGEN< CEnvWindShared >( this, 0x4e8 ); }
};
struct GenDT_Precipitation : public GenDT_BaseEntity
{
	inline int* nPrecipType() { return MakePointerGEN< int >( this, 0x510 ); }
};
struct GenDT_WaterBullet : public GenDT_BaseAnimating
{
};
struct GenDT_PropCrane : public GenDT_BaseAnimating
{
	inline EHANDLE* hPlayer() { return MakePointerGEN< EHANDLE >( this, 0x8ec ); }
	inline bool* bMagnetOn() { return MakePointerGEN< bool >( this, 0x904 ); }
	inline bool* bEnterAnimOn() { return MakePointerGEN< bool >( this, 0x8f4 ); }
	inline bool* bExitAnimOn() { return MakePointerGEN< bool >( this, 0x8f5 ); }
	inline Vector* vecEyeExitEndpoint() { return MakePointerGEN< Vector >( this, 0x8f8 ); }
};
struct GenDT_ScriptIntro : public GenDT_BaseEntity
{
	inline Vector* vecCameraView() { return MakePointerGEN< Vector >( this, 0x548 ); }
	inline Vector* vecCameraViewAngles() { return MakePointerGEN< Vector >( this, 0x554 ); }
	inline int* iBlendMode() { return MakePointerGEN< int >( this, 0x560 ); }
	inline int* iNextBlendMode() { return MakePointerGEN< int >( this, 0x564 ); }
	inline float* flNextBlendTime() { return MakePointerGEN< float >( this, 0x568 ); }
	inline float* flBlendStartTime() { return MakePointerGEN< float >( this, 0x56c ); }
	inline bool* bActive() { return MakePointerGEN< bool >( this, 0x570 ); }
	inline int* iFOV() { return MakePointerGEN< int >( this, 0x4f0 ); }
	inline int* iNextFOV() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline float* flNextFOVBlendTime() { return MakePointerGEN< float >( this, 0x4f8 ); }
	inline float* flFOVBlendStartTime() { return MakePointerGEN< float >( this, 0x4fc ); }
	inline bool* bAlternateFOV() { return MakePointerGEN< bool >( this, 0x500 ); }
	inline float* flFadeAlpha() { return MakePointerGEN< float >( this, 0x584 ); }
	inline float* flFadeColor0() { return MakePointerGEN< float >( this, 0x578 ); }
	inline float* flFadeColor() { return MakePointerGEN< float >( this, 0x0 ); } // Array size = 3
	inline float* flFadeDuration() { return MakePointerGEN< float >( this, 0x58c ); }
	inline EHANDLE* hCameraEntity() { return MakePointerGEN< EHANDLE >( this, 0x574 ); }
};
struct GenDT_RollerMine : public GenDT_AI_BaseNPC
{
	inline bool* bIsOpen() { return MakePointerGEN< bool >( this, 0xe60 ); }
	inline float* flActiveTime() { return MakePointerGEN< float >( this, 0xe64 ); }
	inline bool* bHackedByAlyx() { return MakePointerGEN< bool >( this, 0xe68 ); }
	inline bool* bPowerDown() { return MakePointerGEN< bool >( this, 0xe69 ); }
};
struct GenDT_HandleTest : public GenDT_BaseEntity
{
	inline int* Handle() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline bool* bSendHandle() { return MakePointerGEN< bool >( this, 0x4ec ); }
};
struct GenDT_SpriteTrail : public GenDT_Sprite
{
	inline float* flLifeTime() { return MakePointerGEN< float >( this, 0x118c ); }
	inline float* flStartWidth() { return MakePointerGEN< float >( this, 0x1190 ); }
	inline float* flEndWidth() { return MakePointerGEN< float >( this, 0x1194 ); }
	inline float* flStartWidthVariance() { return MakePointerGEN< float >( this, 0x1198 ); }
	inline float* flTextureRes() { return MakePointerGEN< float >( this, 0x119c ); }
	inline float* flMinFadeLength() { return MakePointerGEN< float >( this, 0x11a0 ); }
	inline Vector* vecSkyboxOrigin() { return MakePointerGEN< Vector >( this, 0x11a4 ); }
	inline float* flSkyboxScale() { return MakePointerGEN< float >( this, 0x11b0 ); }
};
struct GenDT_Ragdoll : public GenDT_BaseAnimating
{
	inline Vector* ragAngles0() { return MakePointerGEN< Vector >( this, 0xa08 ); }
	inline Vector* ragPos0() { return MakePointerGEN< Vector >( this, 0x8e8 ); }
	inline EHANDLE* hUnragdoll() { return MakePointerGEN< EHANDLE >( this, 0xbe4 ); }
	inline float* flBlendWeight() { return MakePointerGEN< float >( this, 0xbe8 ); }
	inline int* nOverlaySequence() { return MakePointerGEN< int >( this, 0xbf0 ); }
}; // Fail count = 2
struct GenDT_Ragdoll_Attached : public GenDT_Ragdoll
{
	inline bool* boneIndexAttached() { return MakePointerGEN< bool >( this, 0xc20 ); }
	inline int* ragdollAttachedObjectIndex() { return MakePointerGEN< int >( this, 0xc1c ); }
	inline Vector* attachmentPointBoneSpace() { return MakePointerGEN< Vector >( this, 0xbf8 ); }
	inline Vector* attachmentPointRagdollSpace() { return MakePointerGEN< Vector >( this, 0xc10 ); }
};
struct GenDT_BaseViewModel
{
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x84 ); }
	inline int* nSkin() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline int* nBody() { return MakePointerGEN< int >( this, 0x4f0 ); }
	inline int* nSequence() { return MakePointerGEN< int >( this, 0x6f8 ); }
	inline int* nViewModelIndex() { return MakePointerGEN< int >( this, 0x8e8 ); }
	inline float* flPlaybackRate() { return MakePointerGEN< float >( this, 0x514 ); }
	inline int* fEffects() { return MakePointerGEN< int >( this, 0x70 ); }
	inline int* nAnimationParity() { return MakePointerGEN< int >( this, 0x8f8 ); }
	inline EHANDLE* hWeapon() { return MakePointerGEN< EHANDLE >( this, 0x914 ); }
	inline EHANDLE* hOwner() { return MakePointerGEN< EHANDLE >( this, 0x8ec ); }
	inline int* nNewSequenceParity() { return MakePointerGEN< int >( this, 0x6cc ); }
	inline int* nResetEventsParity() { return MakePointerGEN< int >( this, 0x6d0 ); }
	inline int* nMuzzleFlashParity() { return MakePointerGEN< int >( this, 0x770 ); }
	inline float* flPoseParameter0() { return MakePointerGEN< float >( this, 0x5d4 ); }
	inline float* flPoseParameter() { return MakePointerGEN< float >( this, 0x0 ); } // Array size = 24
};
struct GenDT_PredictedViewModel : public GenDT_BaseViewModel
{
};
struct GenDT_PoseController : public GenDT_BaseEntity
{
	inline EHANDLE* hProps() { return MakePointerGEN< EHANDLE >( this, 0x4e8 ); } // Array size = 4
	inline char* chPoseIndex() { return MakePointerGEN< char >( this, 0x4f8 ); } // Array size = 4
	inline bool* bPoseValueParity() { return MakePointerGEN< bool >( this, 0x4fc ); }
	inline int* fPoseValue() { return MakePointerGEN< int >( this, 0x500 ); }
	inline int* fCycleFrequency() { return MakePointerGEN< int >( this, 0x504 ); }
	inline int* nFModType() { return MakePointerGEN< int >( this, 0x508 ); }
	inline int* fFModTimeOffset() { return MakePointerGEN< int >( this, 0x50c ); }
	inline int* fFModRate() { return MakePointerGEN< int >( this, 0x510 ); }
	inline int* fFModAmplitude() { return MakePointerGEN< int >( this, 0x514 ); }
};
struct GenDT_InfoLadderDismount : public GenDT_BaseEntity
{
};
struct GenDT_FuncLadder : public GenDT_BaseEntity
{
	inline Vector* vecPlayerMountPositionTop() { return MakePointerGEN< Vector >( this, 0x508 ); }
	inline Vector* vecPlayerMountPositionBottom() { return MakePointerGEN< Vector >( this, 0x514 ); }
	inline Vector* vecLadderDir() { return MakePointerGEN< Vector >( this, 0x4e8 ); }
	inline bool* bFakeLadder() { return MakePointerGEN< bool >( this, 0x521 ); }
};
struct GenDT_DetailController
{
	inline float* flFadeStartDist() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline float* flFadeEndDist() { return MakePointerGEN< float >( this, 0x4ec ); }
};
struct GenDT_World : public GenDT_BaseEntity
{
	inline float* flWaveHeight() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline Vector* WorldMins() { return MakePointerGEN< Vector >( this, 0x4ec ); }
	inline Vector* WorldMaxs() { return MakePointerGEN< Vector >( this, 0x4f8 ); }
	inline bool* bStartDark() { return MakePointerGEN< bool >( this, 0x504 ); }
	inline float* flMaxOccludeeArea() { return MakePointerGEN< float >( this, 0x508 ); }
	inline float* flMinOccluderArea() { return MakePointerGEN< float >( this, 0x50c ); }
	inline float* flMaxPropScreenSpaceWidth() { return MakePointerGEN< float >( this, 0x514 ); }
	inline float* flMinPropScreenSpaceWidth() { return MakePointerGEN< float >( this, 0x510 ); }
	inline int* iszDetailSpriteMaterial() { return MakePointerGEN< int >( this, 0x519 ); }
	inline bool* bColdWorld() { return MakePointerGEN< bool >( this, 0x518 ); }
};
struct GenDT_WaterLODControl : public GenDT_BaseEntity
{
	inline float* flCheapWaterStartDistance() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline float* flCheapWaterEndDistance() { return MakePointerGEN< float >( this, 0x4ec ); }
};
struct GenDT_VGuiScreen : public GenDT_BaseEntity
{
	inline float* flWidth() { return MakePointerGEN< float >( this, 0x4f0 ); }
	inline float* flHeight() { return MakePointerGEN< float >( this, 0x4f4 ); }
	inline int* fScreenFlags() { return MakePointerGEN< int >( this, 0x51c ); }
	inline int* nPanelName() { return MakePointerGEN< int >( this, 0x4f8 ); }
	inline int* nAttachmentIndex() { return MakePointerGEN< int >( this, 0x514 ); }
	inline int* nOverlayMaterial() { return MakePointerGEN< int >( this, 0x518 ); }
};
struct GenDT_VguiTexturePanel : public GenDT_BaseEntity
{
	inline int* width() { return MakePointerGEN< int >( this, 0x5e8 ); }
	inline int* height() { return MakePointerGEN< int >( this, 0x5ec ); }
	inline int* align() { return MakePointerGEN< int >( this, 0x5f0 ); }
	inline int* offsetx() { return MakePointerGEN< int >( this, 0x5f4 ); }
	inline int* offsety() { return MakePointerGEN< int >( this, 0x5f8 ); }
	inline int* entityid() { return MakePointerGEN< int >( this, 0x5fc ); }
	inline float* duration() { return MakePointerGEN< float >( this, 0x608 ); }
	inline float* fadein() { return MakePointerGEN< float >( this, 0x60c ); }
	inline float* fadeout() { return MakePointerGEN< float >( this, 0x610 ); }
	inline int* showpanelproxy() { return MakePointerGEN< int >( this, 0x600 ); }
	inline int* hidepanelproxy() { return MakePointerGEN< int >( this, 0x604 ); }
}; // Fail count = 1
struct GenDT_PropJeep : public GenDT_PropVehicleDriveable
{
	inline bool* bHeadlightIsOn() { return MakePointerGEN< bool >( this, 0xa34 ); }
};
struct GenDT_ProxyToggle : public GenDT_BaseEntity
{
	struct CProxyToggle_ProxiedData
	{
		inline int* WithProxy() { return MakePointerGEN< int >( this, 0x4e8 ); }
	};
	inline CProxyToggle_ProxiedData* blah() { return MakePointerGEN< CProxyToggle_ProxiedData >( this, 0x0 ); }
};
struct GenDT_Tesla : public GenDT_BaseEntity
{
	inline int* iszSpriteName() { return MakePointerGEN< int >( this, 0x54c ); }
}; // Fail count = 1
struct GenDT_TEBeamFollow : public GenDT_BaseBeam
{
	inline int* iEntIndex() { return MakePointerGEN< int >( this, 0x4c ); }
};
struct GenDT_Sun
{
	inline int* clrRender() { return MakePointerGEN< int >( this, 0x58 ); }
	inline int* clrOverlay() { return MakePointerGEN< int >( this, 0x638 ); }
	inline Vector* vDirection() { return MakePointerGEN< Vector >( this, 0x644 ); }
	inline bool* bOn() { return MakePointerGEN< bool >( this, 0x650 ); }
	inline int* nSize() { return MakePointerGEN< int >( this, 0x63c ); }
	inline int* nOverlaySize() { return MakePointerGEN< int >( this, 0x640 ); }
	inline int* nMaterial() { return MakePointerGEN< int >( this, 0x654 ); }
	inline int* nOverlayMaterial() { return MakePointerGEN< int >( this, 0x658 ); }
	inline float* HDRColorScale() { return MakePointerGEN< float >( this, 0x0 ); }
};
struct GenDT_SpotlightEnd : public GenDT_BaseEntity
{
	inline float* flLightScale() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline float* Radius() { return MakePointerGEN< float >( this, 0x4ec ); }
};
struct GenDT_ShadowControl : public GenDT_BaseEntity
{
	inline Vector* shadowDirection() { return MakePointerGEN< Vector >( this, 0x4e8 ); }
	inline int* shadowColor() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline float* flShadowMaxDist() { return MakePointerGEN< float >( this, 0x4f8 ); }
	inline bool* bDisableShadows() { return MakePointerGEN< bool >( this, 0x4fc ); }
};
struct GenDT_SceneEntity : public GenDT_BaseEntity
{
	inline int* nSceneStringIndex() { return MakePointerGEN< int >( this, 0x4f8 ); }
	inline bool* bIsPlayingBack() { return MakePointerGEN< bool >( this, 0x4ec ); }
	inline bool* bPaused() { return MakePointerGEN< bool >( this, 0x4ed ); }
	inline float* flForceClientTime() { return MakePointerGEN< float >( this, 0x4f4 ); }
	inline EHANDLE* hActorList() { return MakePointerGEN< EHANDLE >( this, 0x0 ); } // Array size = 33
};
struct GenDT_RagdollManager
{
	inline int* iMaxRagdollCount() { return MakePointerGEN< int >( this, 0x4e8 ); }
};
struct GenDT_DynamicProp : public GenDT_BreakableProp
{
	inline bool* bUseHitboxesForRenderBox() { return MakePointerGEN< bool >( this, 0x8e8 ); }
}; // Fail count = 1
struct GenDT_DynamicPropCarryable : public GenDT_DynamicProp
{
	inline int* isCarryable() { return MakePointerGEN< int >( this, 0xa0c ); }
	inline int* carryalbeType() { return MakePointerGEN< int >( this, 0xa10 ); }
};
struct GenDT_PhysicsPropDroppedWeapon : public GenDT_PhysicsPropMultiplayer
{
};
struct GenDT_PhysBox : public GenDT_Breakable
{
	inline float* mass() { return MakePointerGEN< float >( this, 0x4e8 ); }
};
struct GenDT_PhysBoxMultiplayer : public GenDT_PhysBox
{
	inline int* iPhysicsMode() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline int* fMass() { return MakePointerGEN< int >( this, 0x4f8 ); }
};
struct GenDT_BasePropDoor : public GenDT_DynamicProp
{
};
struct GenDT_PointLetterbox : public GenDT_BaseEntity
{
	inline float* beginTallRatio() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline float* endTallRatio() { return MakePointerGEN< float >( this, 0x4ec ); }
	inline float* duration() { return MakePointerGEN< float >( this, 0x4f0 ); }
	inline int* interpolator() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline int* beginTallWide() { return MakePointerGEN< int >( this, 0x4f8 ); }
	inline int* endTallWide() { return MakePointerGEN< int >( this, 0x4fc ); }
	inline int* running() { return MakePointerGEN< int >( this, 0x504 ); }
	inline int* runAnimate() { return MakePointerGEN< int >( this, 0x500 ); }
};
struct GenDT_PointCommentaryNode : public GenDT_BaseAnimating
{
	inline bool* bActive() { return MakePointerGEN< bool >( this, 0x8e8 ); }
	inline float* flStartTime() { return MakePointerGEN< float >( this, 0x8ec ); }
	inline int* iszCommentaryFile() { return MakePointerGEN< int >( this, 0x8f0 ); }
	inline int* iszCommentaryFileNoHDR() { return MakePointerGEN< int >( this, 0x9f4 ); }
	inline int* iszSpeakers() { return MakePointerGEN< int >( this, 0xaf8 ); }
	inline int* iNodeNumber() { return MakePointerGEN< int >( this, 0xbf8 ); }
	inline int* iNodeNumberMax() { return MakePointerGEN< int >( this, 0xbfc ); }
	inline EHANDLE* hViewPosition() { return MakePointerGEN< EHANDLE >( this, 0xc04 ); }
};
struct GenDT_PointCamera : public GenDT_BaseEntity
{
	inline float* FOV() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline float* Resolution() { return MakePointerGEN< float >( this, 0x4ec ); }
	inline bool* bFogEnable() { return MakePointerGEN< bool >( this, 0x4f0 ); }
	inline int* FogColor() { return MakePointerGEN< int >( this, 0x4f1 ); }
	inline float* flFogStart() { return MakePointerGEN< float >( this, 0x4f8 ); }
	inline float* flFogEnd() { return MakePointerGEN< float >( this, 0x4fc ); }
	inline bool* bActive() { return MakePointerGEN< bool >( this, 0x500 ); }
	inline bool* bUseScreenAspectRatio() { return MakePointerGEN< bool >( this, 0x501 ); }
};
struct GenDT_Plasma : public GenDT_BaseEntity
{
	inline float* flStartScale() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline float* flScale() { return MakePointerGEN< float >( this, 0x4ec ); }
	inline float* flScaleTime() { return MakePointerGEN< float >( this, 0x4f0 ); }
	inline int* nFlags() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline int* nPlasmaModelIndex() { return MakePointerGEN< int >( this, 0x4f8 ); }
	inline int* nPlasmaModelIndex2() { return MakePointerGEN< int >( this, 0x4fc ); }
	inline int* nGlowModelIndex() { return MakePointerGEN< int >( this, 0x500 ); }
};
struct GenDT_PhysMagnet : public GenDT_BaseAnimating
{
};
struct GenDT_MaterialModifyControl : public GenDT_BaseEntity
{
	inline char** szMaterialName() { return MakePointerGEN< char* >( this, 0x4e8 ); }
	inline char** szMaterialVar() { return MakePointerGEN< char* >( this, 0x5e7 ); }
	inline char** szMaterialVarValue() { return MakePointerGEN< char* >( this, 0x6e6 ); }
	inline int* iFrameStart() { return MakePointerGEN< int >( this, 0x7f0 ); }
	inline int* iFrameEnd() { return MakePointerGEN< int >( this, 0x7f4 ); }
	inline bool* bWrap() { return MakePointerGEN< bool >( this, 0x7f8 ); }
	inline float* flFramerate() { return MakePointerGEN< float >( this, 0x7fc ); }
	inline bool* bNewAnimCommandsSemaphore() { return MakePointerGEN< bool >( this, 0x800 ); }
	inline float* flFloatLerpStartValue() { return MakePointerGEN< float >( this, 0x804 ); }
	inline float* flFloatLerpEndValue() { return MakePointerGEN< float >( this, 0x808 ); }
	inline float* flFloatLerpTransitionTime() { return MakePointerGEN< float >( this, 0x80c ); }
	inline bool* bFloatLerpWrap() { return MakePointerGEN< bool >( this, 0x810 ); }
	inline int* nModifyMode() { return MakePointerGEN< int >( this, 0x818 ); }
};
struct GenDT_LightGlow
{
	inline int* clrRender() { return MakePointerGEN< int >( this, 0x58 ); }
	inline int* nHorizontalSize() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline int* nVerticalSize() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline int* nMinDist() { return MakePointerGEN< int >( this, 0x4f0 ); }
	inline int* nMaxDist() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline int* nOuterMaxDist() { return MakePointerGEN< int >( this, 0x4f8 ); }
	inline int* spawnflags() { return MakePointerGEN< int >( this, 0x4fc ); }
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2d4 ); }
	inline QAngle* angRotation() { return MakePointerGEN< QAngle >( this, 0x2e0 ); }
	inline int* moveparent() { return MakePointerGEN< int >( this, 0x160 ); }
	inline float* flGlowProxySize() { return MakePointerGEN< float >( this, 0x5cc ); }
	inline float* HDRColorScale() { return MakePointerGEN< float >( this, 0x0 ); }
};
struct GenDT_FuncTrackTrain : public GenDT_BaseEntity
{
};
struct GenDT_FuncSmokeVolume : public GenDT_BaseParticleEntity
{
	inline int* Color1() { return MakePointerGEN< int >( this, 0x5e4 ); }
	inline int* Color2() { return MakePointerGEN< int >( this, 0x5e8 ); }
	inline float* ParticleDrawWidth() { return MakePointerGEN< float >( this, 0x6ec ); }
	inline float* ParticleSpacingDistance() { return MakePointerGEN< float >( this, 0x6f0 ); }
	inline float* DensityRampSpeed() { return MakePointerGEN< float >( this, 0x6f4 ); }
	inline float* RotationSpeed() { return MakePointerGEN< float >( this, 0x6f8 ); }
	inline float* MovementSpeed() { return MakePointerGEN< float >( this, 0x6fc ); }
	inline float* Density() { return MakePointerGEN< float >( this, 0x700 ); }
	inline int* spawnflags() { return MakePointerGEN< int >( this, 0x704 ); }
	inline CCollisionProperty* Collision() { return MakePointerGEN< CCollisionProperty >( this, 0x16c ); }
}; // Fail count = 1
struct GenDT_FuncOccluder : public GenDT_BaseEntity
{
	inline bool* bActive() { return MakePointerGEN< bool >( this, 0x4ec ); }
	inline int* nOccluderIndex() { return MakePointerGEN< int >( this, 0x4e8 ); }
};
struct GenDT_FuncMonitor : public GenDT_FuncBrush
{
};
struct GenDT_Func_LOD : public GenDT_BaseEntity
{
	inline int* fDisappearDist() { return MakePointerGEN< int >( this, 0x4e8 ); }
};
struct GenDT_TEDust : public GenDT_TEParticleSystem
{
	inline float* flSize() { return MakePointerGEN< float >( this, 0x1c ); }
	inline float* flSpeed() { return MakePointerGEN< float >( this, 0x20 ); }
	inline Vector* vecDirection() { return MakePointerGEN< Vector >( this, 0x24 ); }
};
struct GenDT_Func_Dust
{
	struct CCollisionProperty
	{
		inline Vector* vecMins() { return MakePointerGEN< Vector >( this, 0x14 ); }
		inline Vector* vecMaxs() { return MakePointerGEN< Vector >( this, 0x20 ); }
		inline int* nSolidType() { return MakePointerGEN< int >( this, 0x35 ); }
		inline int* usSolidFlags() { return MakePointerGEN< int >( this, 0x30 ); }
		inline int* nSurroundType() { return MakePointerGEN< int >( this, 0x34 ); }
		inline int* triggerBloat() { return MakePointerGEN< int >( this, 0x36 ); }
		inline Vector* vecSpecifiedSurroundingMins() { return MakePointerGEN< Vector >( this, 0x38 ); }
		inline Vector* vecSpecifiedSurroundingMaxs() { return MakePointerGEN< Vector >( this, 0x44 ); }
	};
	inline int* Color() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline int* SpawnRate() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline float* flSizeMin() { return MakePointerGEN< float >( this, 0x4f0 ); }
	inline float* flSizeMax() { return MakePointerGEN< float >( this, 0x4f4 ); }
	inline int* LifetimeMin() { return MakePointerGEN< int >( this, 0x4fc ); }
	inline int* LifetimeMax() { return MakePointerGEN< int >( this, 0x500 ); }
	inline int* DustFlags() { return MakePointerGEN< int >( this, 0x50c ); }
	inline int* SpeedMax() { return MakePointerGEN< int >( this, 0x4f8 ); }
	inline int* DistMax() { return MakePointerGEN< int >( this, 0x504 ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x84 ); }
	inline float* FallSpeed() { return MakePointerGEN< float >( this, 0x508 ); }
	inline CCollisionProperty* Collision() { return MakePointerGEN< CCollisionProperty >( this, 0x16c ); }
};
struct GenDT_FuncConveyor : public GenDT_BaseEntity
{
	inline float* flConveyorSpeed() { return MakePointerGEN< float >( this, 0x4e8 ); }
};
struct GenDT_BreakableSurface : public GenDT_Breakable
{
	inline int* nNumWide() { return MakePointerGEN< int >( this, 0x4ec ); }
	inline int* nNumHigh() { return MakePointerGEN< int >( this, 0x4f0 ); }
	inline float* flPanelWidth() { return MakePointerGEN< float >( this, 0x4f4 ); }
	inline float* flPanelHeight() { return MakePointerGEN< float >( this, 0x4f8 ); }
	inline Vector* vNormal() { return MakePointerGEN< Vector >( this, 0x4fc ); }
	inline Vector* vCorner() { return MakePointerGEN< Vector >( this, 0x508 ); }
	inline bool* bIsBroken() { return MakePointerGEN< bool >( this, 0x514 ); }
	inline int* nSurfaceType() { return MakePointerGEN< int >( this, 0x518 ); }
}; // Fail count = 1
struct GenDT_FuncAreaPortalWindow : public GenDT_BaseEntity
{
	inline float* flFadeStartDist() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline float* flFadeDist() { return MakePointerGEN< float >( this, 0x4ec ); }
	inline float* flTranslucencyLimit() { return MakePointerGEN< float >( this, 0x4f0 ); }
	inline int* iBackgroundModelIndex() { return MakePointerGEN< int >( this, 0x4f4 ); }
};
struct GenDT_CFish
{
	inline Vector* poolOrigin() { return MakePointerGEN< Vector >( this, 0x944 ); }
	inline float* x() { return MakePointerGEN< float >( this, 0x92c ); }
	inline float* y() { return MakePointerGEN< float >( this, 0x930 ); }
	inline float* z() { return MakePointerGEN< float >( this, 0x934 ); }
	inline QAngle* angle() { return MakePointerGEN< QAngle >( this, 0x93c ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x84 ); }
	inline int* lifeState() { return MakePointerGEN< int >( this, 0x87 ); }
	inline float* waterLevel() { return MakePointerGEN< float >( this, 0x950 ); }
};
struct GenDT_EntityFlame : public GenDT_BaseEntity
{
	inline float* flSize() { return MakePointerGEN< float >( this, 0x518 ); }
	inline EHANDLE* hEntAttached() { return MakePointerGEN< EHANDLE >( this, 0x4e8 ); }
	inline bool* bUseHitboxes() { return MakePointerGEN< bool >( this, 0x4ec ); }
	inline float* flLifetime() { return MakePointerGEN< float >( this, 0x52c ); }
};
struct GenDT_FireSmoke : public GenDT_BaseEntity
{
	inline float* flStartScale() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline float* flScale() { return MakePointerGEN< float >( this, 0x4ec ); }
	inline float* flScaleTime() { return MakePointerGEN< float >( this, 0x4f0 ); }
	inline int* nFlags() { return MakePointerGEN< int >( this, 0x4f4 ); }
	inline int* nFlameModelIndex() { return MakePointerGEN< int >( this, 0x4f8 ); }
	inline int* nFlameFromAboveModelIndex() { return MakePointerGEN< int >( this, 0x4fc ); }
};
struct GenDT_EnvTonemapController : public GenDT_BaseEntity
{
	inline bool* bUseCustomAutoExposureMin() { return MakePointerGEN< bool >( this, 0x4e8 ); }
	inline bool* bUseCustomAutoExposureMax() { return MakePointerGEN< bool >( this, 0x4e9 ); }
	inline bool* bUseCustomBloomScale() { return MakePointerGEN< bool >( this, 0x4ea ); }
	inline float* flCustomAutoExposureMin() { return MakePointerGEN< float >( this, 0x4ec ); }
	inline float* flCustomAutoExposureMax() { return MakePointerGEN< float >( this, 0x4f0 ); }
	inline float* flCustomBloomScale() { return MakePointerGEN< float >( this, 0x4f4 ); }
	inline float* flCustomBloomScaleMinimum() { return MakePointerGEN< float >( this, 0x4f8 ); }
};
struct GenDT_EnvScreenEffect : public GenDT_BaseEntity
{
	inline float* flDuration() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline int* nType() { return MakePointerGEN< int >( this, 0x4ec ); }
};
struct GenDT_EnvScreenOverlay : public GenDT_BaseEntity
{
	inline int* iszOverlayNames0() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline int* iszOverlayNames() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 10
	inline float* flOverlayTimes0() { return MakePointerGEN< float >( this, 0xee0 ); }
	inline float* flOverlayTimes() { return MakePointerGEN< float >( this, 0x0 ); } // Array size = 10
	inline float* flStartTime() { return MakePointerGEN< float >( this, 0xf08 ); }
	inline int* iDesiredOverlay() { return MakePointerGEN< int >( this, 0xf0c ); }
	inline bool* bIsActive() { return MakePointerGEN< bool >( this, 0xf10 ); }
};
struct GenDT_EnvProjectedTexture : public GenDT_BaseEntity
{
	inline EHANDLE* hTargetEntity() { return MakePointerGEN< EHANDLE >( this, 0x4ec ); }
	inline bool* bState() { return MakePointerGEN< bool >( this, 0x4f0 ); }
	inline float* flLightFOV() { return MakePointerGEN< float >( this, 0x4f4 ); }
	inline bool* bEnableShadows() { return MakePointerGEN< bool >( this, 0x4f8 ); }
	inline bool* bLightOnlyTarget() { return MakePointerGEN< bool >( this, 0x4f9 ); }
	inline bool* bLightWorld() { return MakePointerGEN< bool >( this, 0x4fa ); }
	inline bool* bCameraSpace() { return MakePointerGEN< bool >( this, 0x4fb ); }
	inline int* cLightColor() { return MakePointerGEN< int >( this, 0x4fc ); }
};
struct GenDT_EnvParticleScript : public GenDT_BaseAnimating
{
	inline float* flSequenceScale() { return MakePointerGEN< float >( this, 0x9e0 ); }
};
struct GenDT_EntityParticleTrail : public GenDT_BaseParticleEntity
{
	struct CEntityParticleTrailInfo
	{
		inline float* flLifetime() { return MakePointerGEN< float >( this, 0x8 ); }
		inline float* flStartSize() { return MakePointerGEN< float >( this, 0xc ); }
		inline float* flEndSize() { return MakePointerGEN< float >( this, 0x10 ); }
	};
	inline int* iMaterialName() { return MakePointerGEN< int >( this, 0x5e0 ); }
	inline CEntityParticleTrailInfo* Info() { return MakePointerGEN< CEntityParticleTrailInfo >( this, 0x5e4 ); }
	inline EHANDLE* hConstraintEntity() { return MakePointerGEN< EHANDLE >( this, 0x5f8 ); }
};
struct GenDT_EntityDissolve : public GenDT_BaseEntity
{
	inline float* flStartTime() { return MakePointerGEN< float >( this, 0x4ec ); }
	inline float* flFadeOutStart() { return MakePointerGEN< float >( this, 0x4f0 ); }
	inline float* flFadeOutLength() { return MakePointerGEN< float >( this, 0x4f4 ); }
	inline float* flFadeOutModelStart() { return MakePointerGEN< float >( this, 0x4f8 ); }
	inline float* flFadeOutModelLength() { return MakePointerGEN< float >( this, 0x4fc ); }
	inline float* flFadeInStart() { return MakePointerGEN< float >( this, 0x500 ); }
	inline float* flFadeInLength() { return MakePointerGEN< float >( this, 0x504 ); }
	inline int* nDissolveType() { return MakePointerGEN< int >( this, 0x508 ); }
	inline Vector* vDissolverOrigin() { return MakePointerGEN< Vector >( this, 0x510 ); }
	inline int* nMagnitude() { return MakePointerGEN< int >( this, 0x51c ); }
};
struct GenDT_DynamicLight : public GenDT_BaseEntity
{
	inline int* Flags() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline int* LightStyle() { return MakePointerGEN< int >( this, 0x4e9 ); }
	inline float* Radius() { return MakePointerGEN< float >( this, 0x4ec ); }
	inline int* Exponent() { return MakePointerGEN< int >( this, 0x4f0 ); }
	inline float* InnerAngle() { return MakePointerGEN< float >( this, 0x4f4 ); }
	inline float* OuterAngle() { return MakePointerGEN< float >( this, 0x4f8 ); }
	inline float* SpotRadius() { return MakePointerGEN< float >( this, 0x4fc ); }
};
struct GenDT_ColorCorrectionVolume : public GenDT_BaseEntity
{
	inline float* Weight() { return MakePointerGEN< float >( this, 0x4e8 ); }
}; // Fail count = 1
struct GenDT_ColorCorrection : public GenDT_BaseEntity
{
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x4e8 ); }
	inline float* minFalloff() { return MakePointerGEN< float >( this, 0x4f4 ); }
	inline float* maxFalloff() { return MakePointerGEN< float >( this, 0x4f8 ); }
	inline float* maxWeight() { return MakePointerGEN< float >( this, 0x4fc ); }
	inline int* netLookupFilename() { return MakePointerGEN< int >( this, 0x500 ); }
	inline bool* bEnabled() { return MakePointerGEN< bool >( this, 0x604 ); }
};
struct GenDT_BaseDoor : public GenDT_BaseEntity
{
	inline float* flWaveHeight() { return MakePointerGEN< float >( this, 0x4e8 ); }
};
struct GenDT_BoneFollower : public GenDT_BaseEntity
{
	inline int* modelIndex() { return MakePointerGEN< int >( this, 0x4e8 ); }
	inline int* solidIndex() { return MakePointerGEN< int >( this, 0x4ec ); }
};
struct GenDT_TEEffectEvent
{
	inline EHANDLE* hAnimating() { return MakePointerGEN< EHANDLE >( this, 0x10 ); }
	inline int* event() { return MakePointerGEN< int >( this, 0x14 ); }
	inline int* effectGroup() { return MakePointerGEN< int >( this, 0x18 ); }
	inline int* effectFileName() { return MakePointerGEN< int >( this, 0x1c ); }
};
struct GenDT_InfoLightingRelative : public GenDT_BaseEntity
{
	inline EHANDLE* hLightingLandmark() { return MakePointerGEN< EHANDLE >( this, 0x4e8 ); }
};
struct GenDT_Beam
{
	struct CBeamPredictableId
	{
		inline int* PredictableID() { return MakePointerGEN< int >( this, 0x94 ); }
		inline bool* bIsPlayerSimulated() { return MakePointerGEN< bool >( this, 0x460 ); }
	};
	inline int* nBeamType() { return MakePointerGEN< int >( this, 0x504 ); }
	inline int* nBeamFlags() { return MakePointerGEN< int >( this, 0x508 ); }
	inline int* nNumBeamEnts() { return MakePointerGEN< int >( this, 0x4f8 ); }
	inline EHANDLE* hAttachEntity0() { return MakePointerGEN< EHANDLE >( this, 0x50c ); }
	inline EHANDLE* hAttachEntity() { return MakePointerGEN< EHANDLE >( this, 0x0 ); } // Array size = 10
	inline int* nAttachIndex0() { return MakePointerGEN< int >( this, 0x534 ); }
	inline int* nAttachIndex() { return MakePointerGEN< int >( this, 0x0 ); } // Array size = 10
	inline int* nHaloIndex() { return MakePointerGEN< int >( this, 0x500 ); }
	inline int* fHaloScale() { return MakePointerGEN< int >( this, 0x568 ); }
	inline int* fWidth() { return MakePointerGEN< int >( this, 0x55c ); }
	inline int* fEndWidth() { return MakePointerGEN< int >( this, 0x560 ); }
	inline int* fFadeLength() { return MakePointerGEN< int >( this, 0x564 ); }
	inline int* fAmplitude() { return MakePointerGEN< int >( this, 0x56c ); }
	inline int* fStartFrame() { return MakePointerGEN< int >( this, 0x570 ); }
	inline int* fSpeed() { return MakePointerGEN< int >( this, 0x574 ); }
	inline float* flFrameRate() { return MakePointerGEN< float >( this, 0x4e8 ); }
	inline float* flHDRColorScale() { return MakePointerGEN< float >( this, 0x4ec ); }
	inline int* clrRender() { return MakePointerGEN< int >( this, 0x58 ); }
	inline int* nRenderFX() { return MakePointerGEN< int >( this, 0x54 ); }
	inline int* nRenderMode() { return MakePointerGEN< int >( this, 0x74 ); }
	inline float* flFrame() { return MakePointerGEN< float >( this, 0x578 ); }
	inline Vector* vecEndPos() { return MakePointerGEN< Vector >( this, 0x57c ); }
	inline int* nModelIndex() { return MakePointerGEN< int >( this, 0x84 ); }
	inline Vector* vecOrigin() { return MakePointerGEN< Vector >( this, 0x2d4 ); }
	inline int* moveparent() { return MakePointerGEN< int >( this, 0x160 ); }
	inline CBeamPredictableId* beampredictable_id() { return MakePointerGEN< CBeamPredictableId >( this, 0x0 ); }
};
struct GenDT_BaseGrenade : public GenDT_BaseCombatCharacter
{
	inline float* flDamage() { return MakePointerGEN< float >( this, 0xe58 ); }
	inline float* DmgRadius() { return MakePointerGEN< float >( this, 0xe4c ); }
	inline bool* bIsLive() { return MakePointerGEN< bool >( this, 0xe49 ); }
	inline EHANDLE* hThrower() { return MakePointerGEN< EHANDLE >( this, 0xe60 ); }
	inline Vector* vecVelocity() { return MakePointerGEN< Vector >( this, 0xe0 ); }
	inline int* fFlags() { return MakePointerGEN< int >( this, 0x2ec ); }
};
