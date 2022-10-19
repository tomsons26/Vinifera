/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          EXTENSION_HOOKS.CPP
 *
 *  @author        CCHyper
 *
 *  @brief         Contains the hooks for implementing all the extended classes.
 *
 *  @license       Vinifera is free software: you can redistribute it and/or
 *                 modify it under the terms of the GNU General Public License
 *                 as published by the Free Software Foundation, either version
 *                 3 of the License, or (at your option) any later version.
 *
 *                 Vinifera is distributed in the hope that it will be
 *                 useful, but WITHOUT ANY WARRANTY; without even the implied
 *                 warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *                 PURPOSE. See the GNU General Public License for more details.
 *
 *                 You should have received a copy of the GNU General Public
 *                 License along with this program.
 *                 If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/
#include "extension_hooks.h"

#include "abstractext_hooks.h"
#include "technoext_hooks.h"
#include "footext_hooks.h"

#include "objecttypeext_hooks.h"
#include "technotypeext_hooks.h"

#include "unitext_hooks.h"
#include "aircraftext_hooks.h"
#include "aircrafttypeext_hooks.h"
#include "animext_hooks.h"
#include "animtypeext_hooks.h"
#include "buildingext_hooks.h"
#include "buildingtypeext_hooks.h"
#include "bulletext_hooks.h"
#include "bullettypeext_hooks.h"
#include "campaignext_hooks.h"
#include "cellext_hooks.h"
#include "factoryext_hooks.h"
#include "houseext_hooks.h"
#include "housetypeext_hooks.h"
#include "infantryext_hooks.h"
#include "infantrytypeext_hooks.h"
//EXT_RTTI_ISOTILE
#include "isotiletypeext_hooks.h"
//EXT_RTTI_LIGHT
//EXT_RTTI_OVERLAY
#include "overlaytypeext_hooks.h"
//EXT_RTTI_PARTICLE
#include "particletypeext_hooks.h"
#include "particlesysext_hooks.h"
#include "particlesystypeext_hooks.h"
//EXT_RTTI_SCRIPT
//EXT_RTTI_SCRIPTTYPE
#include "sideext_hooks.h"
//EXT_RTTI_SMUDGE
#include "smudgetypeext_hooks.h"
#include "supertypeext_hooks.h"
//EXT_RTTI_TASKFORCE
#include "teamext_hooks.h"
//EXT_RTTI_TEAMTYPE
#include "terrainext_hooks.h"
#include "terraintypeext_hooks.h"
//EXT_RTTI_TRIGGER
//EXT_RTTI_TRIGGERTYPE
#include "unittypeext_hooks.h"
//EXT_RTTI_VOXELANIM
#include "voxelanimtypeext_hooks.h"
#include "waveext_hooks.h"
//EXT_RTTI_TAG
//EXT_RTTI_TAGTYPE
#include "tiberiumext_hooks.h"
#include "tactionext_hooks.h"
//EXT_RTTI_EVENT
#include "weapontypeext_hooks.h"
#include "warheadtypeext_hooks.h"
//EXT_RTTI_WAYPOINT
//EXT_RTTI_TUBE
//EXT_RTTI_LIGHTSOURCE
#include "empulseext_hooks.h"
//EXT_RTTI_TACTICALMAP
#include "superext_hooks.h"
//EXT_RTTI_AITRIGGER
//EXT_RTTI_AITRIGGERTYPE
//EXT_RTTI_NEURON
//EXT_RTTI_FOGGEDOBJECT
//EXT_RTTI_ALPHASHAPE
//EXT_RTTI_VEINHOLEMONSTER







#include "initext_hooks.h"
#include "mainloopext_hooks.h"
#include "newmenuext_hooks.h"

#include "rulesext_hooks.h"
#include "tacticalext_hooks.h"
#include "scenarioext_hooks.h"
#include "displayext_hooks.h"
#include "sidebarext_hooks.h"
#include "tooltipext_hooks.h"
#include "commandext_hooks.h"
#include "optionsext_hooks.h"
#include "msglistext_hooks.h"
#include "sessionext_hooks.h"
#include "cdext_hooks.h"

#include "playmovie_hooks.h"
#include "vqaext_hooks.h"
#include "themeext_hooks.h"








#include "combatext_hooks.h"

#include "empulseext_hooks.h"
#include "waveext_hooks.h"

#include "txtlabelext_hooks.h"

#include "dropshipext_hooks.h"
#include "endgameext_hooks.h"

#include "mapseedext_hooks.h"
#include "multiscoreext_hooks.h"
#include "multimissionext_hooks.h"

#include "cciniext_hooks.h"
#include "rawfileext_hooks.h"
#include "ccfileext_hooks.h"

#include "theatertype_hooks.h"

#include "fetchres_hooks.h"

#include "skirmishdlg_hooks.h"

#include "filepcx_hooks.h"






#include "iomap.h"

#include "extension.h"
#include "swizzle.h"

#include "hooker.h"
#include "hooker_macros.h"



#include "tracker.h"
static void _Detach_This_From_All_Intercept(TARGET target, bool all)
{
    Extension::Detach_This_From_All(target, all);

    Detach_This_From_All(target, all);
}

#include "tibsun_functions.h"
static void _Clear_Vectors_Intercept()
{
    Extension::Clear_Vectors();

    Clear_Vectors();
}



void Extension_Hooks()
{
    Patch_Call(0x0053DF7A, &_Clear_Vectors_Intercept); // MapSeedClass::Init_Random
    Patch_Call(0x005DC590, &_Clear_Vectors_Intercept); // Clear_Scenario
    Patch_Call(0x00601BA2, &_Clear_Vectors_Intercept); // Game_Shutdown

    Patch_Call(0x0040DBB3, &_Detach_This_From_All_Intercept); // AircraftClass::~AircraftClass
    Patch_Call(0x0040F123, &_Detach_This_From_All_Intercept); // AircraftClass_Fall_To_Death
    Patch_Call(0x0040FCD3, &_Detach_This_From_All_Intercept); // AircraftTypeClass::~AircraftTypeClass
    Patch_Call(0x00410223, &_Detach_This_From_All_Intercept); // AircraftTypeClass::~AircraftTypeClass
    Patch_Call(0x004142C6, &_Detach_This_From_All_Intercept); // AnimClass::~AnimClass
    Patch_Call(0x00426662, &_Detach_This_From_All_Intercept); // BuildingClass::~BuildingClass
    Patch_Call(0x0043F94D, &_Detach_This_From_All_Intercept); // BuildingTypeClass::~BuildingTypeClass
    Patch_Call(0x0044407D, &_Detach_This_From_All_Intercept); // BuildingTypeClass::~BuildingTypeClass
    Patch_Call(0x004445F3, &_Detach_This_From_All_Intercept); // BulletClass::~BulletClass
    Patch_Call(0x004474D3, &_Detach_This_From_All_Intercept); // BulletClass::~BulletClass
    Patch_Call(0x00447DC3, &_Detach_This_From_All_Intercept); // BulletTypeClass::~BulletTypeClass
    Patch_Call(0x00448723, &_Detach_This_From_All_Intercept); // BulletTypeClass::~BulletTypeClass
    Patch_Call(0x00448AE3, &_Detach_This_From_All_Intercept); // CampaignClass::~CampaignClass
    Patch_Call(0x00448EF3, &_Detach_This_From_All_Intercept); // CampaignClass::~CampaignClass
    Patch_Call(0x00456A26, &_Detach_This_From_All_Intercept); // CellClass::Wall_Update
    Patch_Call(0x00456A58, &_Detach_This_From_All_Intercept); // CellClass::Wall_Update
    Patch_Call(0x00456A7F, &_Detach_This_From_All_Intercept); // CellClass::Wall_Update
    Patch_Call(0x00456AAB, &_Detach_This_From_All_Intercept); // CellClass::Wall_Update
    Patch_Call(0x00456AD2, &_Detach_This_From_All_Intercept); // CellClass::Wall_Update
    Patch_Call(0x004571F9, &_Detach_This_From_All_Intercept); // CellClass::Reduce_Wall
    Patch_Call(0x004927D3, &_Detach_This_From_All_Intercept); // EMPulseClass::~EMPulseClass
    Patch_Call(0x004931E3, &_Detach_This_From_All_Intercept); // EMPulseClass::~EMPulseClass
    Patch_Call(0x00496DB3, &_Detach_This_From_All_Intercept); // FactoryClass::~FactoryClass
    Patch_Call(0x00497AA3, &_Detach_This_From_All_Intercept); // FactoryClass::~FactoryClass
    Patch_Call(0x004BB6DB, &_Detach_This_From_All_Intercept); // HouseClass::~HouseClass
    Patch_Call(0x004CDE93, &_Detach_This_From_All_Intercept); // HouseTypeClass::~HouseTypeClass
    Patch_Call(0x004CE603, &_Detach_This_From_All_Intercept); // HouseTypeClass::~HouseTypeClass
    Patch_Call(0x004D22DC, &_Detach_This_From_All_Intercept); // InfantryClass::~InfantryClass
    Patch_Call(0x004DA3B4, &_Detach_This_From_All_Intercept); // InfantryTypeClass::~InfantryTypeClass
    Patch_Call(0x004DB133, &_Detach_This_From_All_Intercept); // InfantryTypeClass::~InfantryTypeClass
    Patch_Call(0x004F2173, &_Detach_This_From_All_Intercept); // IsometricTileClass::~IsometricTileClass
    Patch_Call(0x004F23E3, &_Detach_This_From_All_Intercept); // IsometricTileClass::~IsometricTileClass
    Patch_Call(0x004F3344, &_Detach_This_From_All_Intercept); // IsometricTileTypeClass::~IsometricTileTypeClass
    Patch_Call(0x005015E3, &_Detach_This_From_All_Intercept); // LightSourceClass::~LightSourceClass
    Patch_Call(0x00501DA3, &_Detach_This_From_All_Intercept); // LightSourceClass::~LightSourceClass
    Patch_Call(0x00585F9E, &_Detach_This_From_All_Intercept); // ObjectClass::Detach_All
    Patch_Call(0x00586DB5, &_Detach_This_From_All_Intercept); // ObjectClass::entry_E4
    Patch_Call(0x0058B563, &_Detach_This_From_All_Intercept); // OverlayClass::~OverlayClass
    Patch_Call(0x0058CB13, &_Detach_This_From_All_Intercept); // OverlayClass::~OverlayClass
    Patch_Call(0x0058D196, &_Detach_This_From_All_Intercept); // OverlayTypeClass::~OverlayTypeClass
    Patch_Call(0x0058DC86, &_Detach_This_From_All_Intercept); // OverlayTypeClass::~OverlayTypeClass
    Patch_Call(0x005A32FA, &_Detach_This_From_All_Intercept); // ParticleClass::~ParticleClass
    Patch_Call(0x005A503A, &_Detach_This_From_All_Intercept); // ParticleClass::~ParticleClass
    Patch_Call(0x005A56D4, &_Detach_This_From_All_Intercept); // ParticleSystemClass::~ParticleSystemClass
    Patch_Call(0x005AE573, &_Detach_This_From_All_Intercept); // ParticleSystemTypeClass::~ParticleSystemTypeClass
    Patch_Call(0x005AEC63, &_Detach_This_From_All_Intercept); // ParticleSystemTypeClass::~ParticleSystemTypeClass
    Patch_Call(0x005AF153, &_Detach_This_From_All_Intercept); // ParticleTypeClass::~ParticleTypeClass
    Patch_Call(0x005AFC33, &_Detach_This_From_All_Intercept); // ParticleTypeClass::~ParticleTypeClass
    Patch_Call(0x005E78C3, &_Detach_This_From_All_Intercept); // ScriptClass::~ScriptClass
    Patch_Call(0x005E7B83, &_Detach_This_From_All_Intercept); // ScriptTypeClass::~ScriptTypeClass
    Patch_Call(0x005E81E3, &_Detach_This_From_All_Intercept); // ScriptClass::~ScriptClass
    Patch_Call(0x005E8293, &_Detach_This_From_All_Intercept); // ScriptTypeClass::~ScriptTypeClass
    Patch_Call(0x005F1AE3, &_Detach_This_From_All_Intercept); // SideClass::~SideClass
    Patch_Call(0x005F1D93, &_Detach_This_From_All_Intercept); // SideClass::~SideClass
    Patch_Call(0x005FAAD3, &_Detach_This_From_All_Intercept); // SmudgeClass::~SmudgeClass
    Patch_Call(0x005FAF03, &_Detach_This_From_All_Intercept); // SmudgeClass::~SmudgeClass
    Patch_Call(0x005FB313, &_Detach_This_From_All_Intercept); // SmudgeTypeClass::~SmudgeTypeClass
    Patch_Call(0x005FC023, &_Detach_This_From_All_Intercept); // SmudgeTypeClass::~SmudgeTypeClass
    Patch_Call(0x00618D03, &_Detach_This_From_All_Intercept); // TActionClass::~TActionClass
    Patch_Call(0x0061DAD3, &_Detach_This_From_All_Intercept); // TActionClass::~TActionClass
    Patch_Call(0x0061E4B6, &_Detach_This_From_All_Intercept); // TagClass::~TagClass
    Patch_Call(0x0061E73B, &_Detach_This_From_All_Intercept); // TagClass::~TagClass
    Patch_Call(0x0061E9AA, &_Detach_This_From_All_Intercept); // TagClass::Spring
    Patch_Call(0x0061F164, &_Detach_This_From_All_Intercept); // TagTypeClass::~TagTypeClass
    Patch_Call(0x00621503, &_Detach_This_From_All_Intercept); // TaskForceClass::~TaskForceClass
    Patch_Call(0x00621E43, &_Detach_This_From_All_Intercept); // TaskForceClass::~TaskForceClass
    Patch_Call(0x006224E3, &_Detach_This_From_All_Intercept); // TeamClass::~TeamClass
    Patch_Call(0x00627EF3, &_Detach_This_From_All_Intercept); // TeamTypeClass::~TeamTypeClass
    Patch_Call(0x00629293, &_Detach_This_From_All_Intercept); // TeamTypeClass::~TeamTypeClass
    Patch_Call(0x0063F188, &_Detach_This_From_All_Intercept); // TerrainClass::~TerrainClass
    Patch_Call(0x00640C38, &_Detach_This_From_All_Intercept); // TerrainClass::~TerrainClass
    Patch_Call(0x00641653, &_Detach_This_From_All_Intercept); // TerrainTypeClass::~TerrainTypeClass
    Patch_Call(0x00641D83, &_Detach_This_From_All_Intercept); // TerrainTypeClass::~TerrainTypeClass
    Patch_Call(0x00642223, &_Detach_This_From_All_Intercept); // TEventClass::~TEventClass
    Patch_Call(0x00642F23, &_Detach_This_From_All_Intercept); // TEventClass::~TEventClass
    Patch_Call(0x00644A45, &_Detach_This_From_All_Intercept); // TiberiumClass::~TiberiumClass
    Patch_Call(0x006491A3, &_Detach_This_From_All_Intercept); // TriggerClass::~TriggerClass
    Patch_Call(0x00649943, &_Detach_This_From_All_Intercept); // TriggerClass::~TriggerClass
    Patch_Call(0x00649E03, &_Detach_This_From_All_Intercept); // TriggerTypeClass::~TriggerTypeClass
    Patch_Call(0x0064AFD3, &_Detach_This_From_All_Intercept); // TubeClass::~TubeClass
    Patch_Call(0x0064B603, &_Detach_This_From_All_Intercept); // TubeClass::~TubeClass
    Patch_Call(0x0064D8A9, &_Detach_This_From_All_Intercept); // UnitClass::~UnitClass
    Patch_Call(0x0065BAD3, &_Detach_This_From_All_Intercept); // UnitTypeClass::~UnitTypeClass
    Patch_Call(0x0065C793, &_Detach_This_From_All_Intercept); // UnitTypeClass::~UnitTypeClass
    Patch_Call(0x0065DF23, &_Detach_This_From_All_Intercept); // VoxelAnimClass::~VoxelAnimClass
    Patch_Call(0x0065F5A3, &_Detach_This_From_All_Intercept); // VoxelAnimTypeClass::~VoxelAnimTypeClass
    Patch_Call(0x00660093, &_Detach_This_From_All_Intercept); // VoxelAnimTypeClass::~VoxelAnimTypeClass
    Patch_Call(0x00661227, &_Detach_This_From_All_Intercept); // VeinholeMonsterClass::~VeinholeMonsterClass
    Patch_Call(0x00661C00, &_Detach_This_From_All_Intercept); // VeinholeMonsterClass::Take_Damage
    Patch_Call(0x0066EF73, &_Detach_This_From_All_Intercept); // WarheadTypeClass::~WarheadTypeClass
    Patch_Call(0x0066FA93, &_Detach_This_From_All_Intercept); // WarheadTypeClass::~WarheadTypeClass
    Patch_Call(0x006702D4, &_Detach_This_From_All_Intercept); // WaveClass::~WaveClass
    Patch_Call(0x00672E73, &_Detach_This_From_All_Intercept); // WaveClass::~WaveClass
    Patch_Call(0x00673563, &_Detach_This_From_All_Intercept); // WaypointPathClass::~WaypointPathClass
    Patch_Call(0x00673AA3, &_Detach_This_From_All_Intercept); // WaypointPathClass::~WaypointPathClass
    Patch_Call(0x00680C54, &_Detach_This_From_All_Intercept); // WeaponTypeClass::~WeaponTypeClass
    Patch_Call(0x006818F4, &_Detach_This_From_All_Intercept); // WeaponTypeClass::~WeaponTypeClass






    /**
     *  Abstract and stack class extensions here.
     */
    AbstractClassExtension_Hooks();

//    if (Extension::Is_Support_Enabled(RTTI_UNIT)
//     || Extension::Is_Support_Enabled(RTTI_INFANTRY)
//     || Extension::Is_Support_Enabled(RTTI_BUILDING)
//     || Extension::Is_Support_Enabled(RTTI_AIRCRAFT)) {
//
//        TechnoClassExtension_Hooks();
//        FootClassExtension_Hooks();
//    }
//
//    if (Extension::Is_Support_Enabled(RTTI_UNITTYPE)
//     || Extension::Is_Support_Enabled(RTTI_INFANTRYTYPE)
//     || Extension::Is_Support_Enabled(RTTI_BUILDINGTYPE)
//     || Extension::Is_Support_Enabled(RTTI_AIRCRAFTTYPE)) {
//
//        ObjectTypeClassExtension_Hooks();
//        TechnoTypeClassExtension_Hooks();
//    }

    /**
     *  All game class extensions here.
     */
    if (Extension::Is_Support_Enabled(RTTI_UNIT)) { UnitClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_AIRCRAFT)) { AircraftClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_AIRCRAFTTYPE)) { AircraftTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_ANIM)) { AnimClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_ANIMTYPE)) { AnimTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_BUILDING)) { BuildingClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_BUILDINGTYPE)) { BuildingTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_BULLET)) { BulletClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_BULLETTYPE)) { BulletTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_CAMPAIGN)) { CampaignClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_CELL)) { CellClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_FACTORY)) { FactoryClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_HOUSE)) { HouseClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_HOUSETYPE)) { HouseTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_INFANTRY)) { InfantryClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_INFANTRYTYPE)) { InfantryTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_ISOTILE)) { EXT_RTTI_ISOTILE; }
    if (Extension::Is_Support_Enabled(RTTI_ISOTILETYPE)) { IsometricTileTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_LIGHT)) { EXT_RTTI_LIGHT; }
    if (Extension::Is_Support_Enabled(RTTI_OVERLAY)) { EXT_RTTI_OVERLAY; }
    if (Extension::Is_Support_Enabled(RTTI_OVERLAYTYPE)) { OverlayTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_PARTICLE)) { EXT_RTTI_PARTICLE; }
    if (Extension::Is_Support_Enabled(RTTI_PARTICLETYPE)) { ParticleTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_PARTICLESYSTEM)) { ParticleSystemClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_PARTICLESYSTEMTYPE)) { ParticleSystemTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_SCRIPT)) { EXT_RTTI_SCRIPT; }
    if (Extension::Is_Support_Enabled(RTTI_SCRIPTTYPE)) { EXT_RTTI_SCRIPTTYPE; }
    if (Extension::Is_Support_Enabled(RTTI_SIDE)) { SideClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_SMUDGE)) { EXT_RTTI_SMUDGE; }
    if (Extension::Is_Support_Enabled(RTTI_SMUDGETYPE)) { SmudgeTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_SUPERWEAPONTYPE)) { SuperWeaponTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_TASKFORCE)) { EXT_RTTI_TASKFORCE; }
    if (Extension::Is_Support_Enabled(RTTI_TEAM)) { TeamClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_TEAMTYPE)) { EXT_RTTI_TEAMTYPE; }
    if (Extension::Is_Support_Enabled(RTTI_TERRAIN)) { TerrainClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_TERRAINTYPE)) { TerrainTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_TRIGGER)) { EXT_RTTI_TRIGGER; }
    if (Extension::Is_Support_Enabled(RTTI_TRIGGERTYPE)) { EXT_RTTI_TRIGGERTYPE; }
    if (Extension::Is_Support_Enabled(RTTI_UNITTYPE)) { UnitTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_VOXELANIM)) { EXT_RTTI_VOXELANIM; }
    if (Extension::Is_Support_Enabled(RTTI_VOXELANIMTYPE)) { VoxelAnimTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_WAVE)) { WaveClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_TAG)) { EXT_RTTI_TAG; }
    if (Extension::Is_Support_Enabled(RTTI_TAGTYPE)) { EXT_RTTI_TAGTYPE; }
    if (Extension::Is_Support_Enabled(RTTI_TIBERIUM)) { TiberiumClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_ACTION)) { TActionClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_EVENT)) { EXT_RTTI_EVENT; }
    if (Extension::Is_Support_Enabled(RTTI_WEAPONTYPE)) { WeaponTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_WARHEADTYPE)) { WarheadTypeClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_WAYPOINT)) { EXT_RTTI_WAYPOINT; }
    if (Extension::Is_Support_Enabled(RTTI_TUBE)) { EXT_RTTI_TUBE; }
    if (Extension::Is_Support_Enabled(RTTI_LIGHTSOURCE)) { EXT_RTTI_LIGHTSOURCE; }
    if (Extension::Is_Support_Enabled(RTTI_EMPULSE)) { EMPulseClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_TACTICALMAP)) { EXT_RTTI_TACTICALMAP; }
    if (Extension::Is_Support_Enabled(RTTI_SUPERWEAPON)) { SuperClassExtension_Hooks(); }
    if (Extension::Is_Support_Enabled(RTTI_AITRIGGER)) { EXT_RTTI_AITRIGGER; }
    if (Extension::Is_Support_Enabled(RTTI_AITRIGGERTYPE)) { EXT_RTTI_AITRIGGERTYPE; }
    if (Extension::Is_Support_Enabled(RTTI_NEURON)) { EXT_RTTI_NEURON; }
    if (Extension::Is_Support_Enabled(RTTI_FOGGEDOBJECT)) { EXT_RTTI_FOGGEDOBJECT; }
    if (Extension::Is_Support_Enabled(RTTI_ALPHASHAPE)) { EXT_RTTI_ALPHASHAPE; }
    if (Extension::Is_Support_Enabled(RTTI_VEINHOLEMONSTER)) { EXT_RTTI_VEINHOLEMONSTER; }

    /**
     *  All global class extensions here.
     */
//    RulesClassExtension_Hooks();
//    TacticalExtension_Hooks();
//    ScenarioClassExtension_Hooks();
//    DisplayClassExtension_Hooks();
//    SidebarClassExtension_Hooks();
//    OptionsClassExtension_Hooks();
//    SessionClassExtension_Hooks();
//    ThemeClassExtension_Hooks();

    /**
     *  New classes and interfaces.
     */
    TheaterTypeClassExtension_Hooks();

    /**
     *  Various modules and functions.
     */
    GameInit_Hooks();
    MainLoop_Hooks();
    NewMenuExtension_Hooks();
    CommandExtension_Hooks();
    CDExtension_Hooks();
    PlayMovieExtension_Hooks();
    VQAExtension_Hooks();
    CCINIClassExtension_Hooks();
    RawFileClassExtension_Hooks();
    CCFileClassExtension_Hooks();

    MessageListClassExtension_Hooks();
    TextLabelClassExtension_Hooks();
    ToolTipManagerExtension_Hooks();

    //CombatExtension_Hooks();
    DropshipExtension_Hooks();
    EndGameExtension_Hooks();
    MapSeedClassExtension_Hooks();
    MultiScoreExtension_Hooks();
    MultiMissionExtension_Hooks();

    /**
     *  Dialogs and associated code.
     */
    SkirmishDialog_Hooks();

    /**
     *  Miscellaneous hooks
     */
    FilePCXExtension_Hooks();
    FetchRes_Hooks();
}