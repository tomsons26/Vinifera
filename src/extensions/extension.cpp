/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          EXTENSION_GLOBALS.CPP
 *
 *  @author        CCHyper
 *
 *  @brief         
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
#include "extension.h"
#include "tibsun_functions.h"
#include "debughandler.h"
#include "asserthandler.h"

#include "abstract.h"

#include "aircraft.h"
#include "aircrafttype.h"
#include "anim.h"
#include "animtype.h"
#include "building.h"
#include "buildingtype.h"
#include "bullettype.h"
#include "campaign.h"
#include "side.h"
#include "house.h"
#include "housetype.h"
#include "infantry.h"
#include "infantrytype.h"
#include "isotiletype.h"
#include "objecttype.h"
#include "overlaytype.h"
#include "particlesystype.h"
#include "particletype.h"
#include "smudgetype.h"
#include "super.h"
#include "supertype.h"
#include "terrain.h"
#include "terraintype.h"
#include "tiberium.h"
#include "unit.h"
#include "unittype.h"
#include "voxelanimtype.h"
#include "warheadtype.h"
#include "wave.h"
#include "weapontype.h"

#include "aircraftext.h"
#include "aircrafttypeext.h"
#include "animext.h"
#include "animtypeext.h"
#include "buildingext.h"
#include "buildingtypeext.h"
#include "bullettypeext.h"
#include "campaignext.h"
#include "sideext.h"
#include "houseext.h"
#include "housetypeext.h"
#include "infantryext.h"
#include "infantrytypeext.h"
#include "isotiletypeext.h"
#include "objecttypeext.h"
#include "overlaytypeext.h"
#include "particlesystypeext.h"
#include "particletypeext.h"
#include "smudgetypeext.h"
#include "superext.h"
#include "supertypeext.h"
#include "terrainext.h"
#include "terraintypeext.h"
#include "tiberiumext.h"
#include "unitext.h"
#include "unittypeext.h"
#include "voxelanimtypeext.h"
#include "warheadtypeext.h"
#include "waveext.h"
#include "weapontypeext.h"


/**
 *  x
 */
DynamicVectorClass<AircraftClassExtension *> AircraftExtensions;
DynamicVectorClass<AircraftTypeClassExtension *> AircraftTypeExtensions;
DynamicVectorClass<AnimClassExtension *> AnimExtensions;
DynamicVectorClass<AnimTypeClassExtension *> AnimTypeExtensions;
DynamicVectorClass<BuildingClassExtension *> BuildingExtensions;
DynamicVectorClass<BuildingTypeClassExtension *> BuildingTypeExtensions;
DynamicVectorClass<BulletTypeClassExtension *> BulletTypeExtensions;
DynamicVectorClass<CampaignClassExtension *> CampaignExtensions;
DynamicVectorClass<SideClassExtension *> SideExtensions;
DynamicVectorClass<HouseClassExtension *> HouseExtensions;
DynamicVectorClass<HouseTypeClassExtension *> HouseTypeExtensions;
DynamicVectorClass<InfantryClassExtension *> InfantryExtensions;
DynamicVectorClass<InfantryTypeClassExtension *> InfantryTypeExtensions;
DynamicVectorClass<IsometricTileTypeClassExtension *> IsometricTileTypeExtensions;
DynamicVectorClass<OverlayTypeClassExtension *> OverlayTypeExtensions;
DynamicVectorClass<ParticleSystemTypeClassExtension *> ParticleSystemTypeExtensions;
DynamicVectorClass<ParticleTypeClassExtension *> ParticleTypeExtensions;
DynamicVectorClass<SmudgeTypeClassExtension *> SmudgeTypeExtensions;
DynamicVectorClass<SuperClassExtension *> SuperExtensions;
DynamicVectorClass<SuperWeaponTypeClassExtension *> SuperWeaponTypeExtensions;
DynamicVectorClass<TerrainClassExtension *> TerrainExtensions;
DynamicVectorClass<TerrainTypeClassExtension *> TerrainTypeExtensions;
DynamicVectorClass<TiberiumClassExtension *> TiberiumExtensions;
DynamicVectorClass<UnitClassExtension *> UnitExtensions;
DynamicVectorClass<UnitTypeClassExtension *> UnitTypeExtensions;
DynamicVectorClass<VoxelAnimTypeClassExtension *> VoxelAnimTypeExtensions;
DynamicVectorClass<WarheadTypeClassExtension *> WarheadTypeExtensions;
DynamicVectorClass<WaveClassExtension *> WaveExtensions;
DynamicVectorClass<WeaponTypeClassExtension *> WeaponTypeExtensions;


/**
 *  Set_Extension_Pointer
 * 
 *  @author: CCHyper
 */
static void Set_Extension_Pointer(const AbstractClass *abstract, const AbstractClassExtension *abstract_extension)
{
    ASSERT(abstract != nullptr);
    ASSERT(abstract_extension != nullptr);
    (*(uintptr_t *)((char *)abstract + 0x10)) = (uintptr_t)abstract_extension;
}


/**
 *  Get_Extension_Pointer
 * 
 *  @author: CCHyper
 */
static AbstractClassExtension *Get_Extension_Pointer(const AbstractClass *abstract)
{
    uintptr_t abstract_extension_address = (*(uintptr_t *)((char *)abstract + 0x10));
    AbstractClassExtension *abstract_extension = (AbstractClassExtension *)abstract_extension_address;
    return abstract_extension;
}


/**
 *  Clear_Extension_Pointer
 * 
 *  @author: CCHyper
 */
static void Clear_Extension_Pointer(const AbstractClass *abstract)
{
    (*(uintptr_t *)((char *)abstract + 0x10)) = (uintptr_t)0x00000000;
}


/**
 *  Get_Abstract_Name
 * 
 *  @author: CCHyper
 */
static const char *Get_Abstract_Name(const AbstractClass *abstract)
{
    if (abstract) {
        if (Is_Object(abstract)) {
            return reinterpret_cast<const ObjectClass *>(abstract)->Name();
        }
        if (Is_TypeClass(abstract)) {
            return reinterpret_cast<const ObjectTypeClass *>(abstract)->Name();
        }
        switch (abstract->What_Am_I()) {
            case RTTI_HOUSE:
                return reinterpret_cast<const HouseClass *>(abstract)->Class->Name(); // IHouse interface's Name() returns BSTR (wide), so call the Class one instead.
            case RTTI_SUPERWEAPON:
                return reinterpret_cast<const SuperClass *>(abstract)->Name();
            default:
                break;
        };
    }

    return "<noname>";
}


/**
 *  x
 * 
 *  @author: CCHyper
 */
#define EXT_FIND_OR_MAKE(abstract_ptr, class_name, ext_class_name, list) \
    { \
        /*EXT_DEBUG_INFO("EXT_FIND_OR_MAKE... %s %s %s\n", Get_Abstract_Name(abstract_ptr), #class_name, #ext_class_name);*/ \
        class_name *abs_ptr = (class_name *)abstract_ptr; \
        ext_class_name *chk = (ext_class_name *)Get_Extension_Pointer(abs_ptr); \
        int found_index = list.ID(chk); \
        if (found_index != -1) { \
            extptr = list[found_index]; \
        } else if (allow_make) { \
            ext_class_name *ptr = new ext_class_name(abs_ptr); \
            bool added = list.Add(ptr); \
            ASSERT(added); \
            if (added) { \
                EXT_DEBUG_INFO("%s extension created for \"%s\".\n", #class_name, Get_Abstract_Name(abs_ptr)); \
                created = true; \
                extptr = ptr; \
            } \
        } \
    }

/**
 *  x
 * 
 *  @author: CCHyper
 */
#define EXT_DESTROY(abstract_ptr, class_name, ext_class_name, list) \
    { \
        /*EXT_DEBUG_INFO("EXT_DESTROY... %s %s %s\n", Get_Abstract_Name(abstract_ptr), #class_name, #ext_class_name);*/ \
        ext_class_name *ext_ptr = (ext_class_name *)Get_Extension_Pointer(abstract_ptr); \
        bool removed = list.Delete(ext_ptr); \
        ASSERT_FATAL_PRINT(removed, "Failed to destroy %s extension \"%s\"!\n", #class_name, Get_Abstract_Name(abstract_ptr)); \
        EXT_DEBUG_INFO("Destroyed %s extension for \"%s\".\n", #class_name, Get_Abstract_Name(abstract_ptr)); \
    }


/**
 *  Handy macros for defining the save and load process for an extended classes.
 * 
 *  @author: CCHyper
 */
#define EXT_SAVE(class_name, ext_class_name, list) \
    { \
        DEBUG_INFO("Saving %s extensions\n", #class_name); \
        for (int i = 0; i < list.Count(); ++i) { list[i]->Save(pStm, true); } \
    }

#define EXT_LOAD(class_name, ext_class_name, list) \
    { \
        DEBUG_INFO("Loading %s extensions\n", #class_name); \
        for (int i = 0; i < list.Count(); ++i) { list[i]->Load(pStm); } \
    }



/**
 *  x
 * 
 *  @author: CCHyper
 */
AbstractClassExtension *Find_Or_Make_Extension_Internal(const AbstractClass *abstract, bool allow_make)
{
    ASSERT(abstract != nullptr);

    bool created = false;
    AbstractClassExtension *extptr = nullptr;

    switch (const_cast<AbstractClass *>(abstract)->What_Am_I()) {

        case RTTI_AIRCRAFT:
        {
            EXT_FIND_OR_MAKE(abstract, AircraftClass, AircraftClassExtension, AircraftExtensions);
            break;
        }

        case RTTI_AIRCRAFTTYPE:
        {
            EXT_FIND_OR_MAKE(abstract, AircraftTypeClass, AircraftTypeClassExtension, AircraftTypeExtensions);
            break;
        }

        case RTTI_ANIM:
        {
            EXT_FIND_OR_MAKE(abstract, AnimClass, AnimClassExtension, AnimExtensions);
            break;
        }

        case RTTI_ANIMTYPE:
        {
            EXT_FIND_OR_MAKE(abstract, AnimTypeClass, AnimTypeClassExtension, AnimTypeExtensions);
            break;
        }

        case RTTI_BUILDING:
        {
            EXT_FIND_OR_MAKE(abstract, BuildingClass, BuildingClassExtension, BuildingExtensions);
            break;
        }

        case RTTI_BUILDINGTYPE:
        {
            EXT_FIND_OR_MAKE(abstract, BuildingTypeClass, BuildingTypeClassExtension, BuildingTypeExtensions);
            break;
        }

        case RTTI_BULLETTYPE:
        {
            EXT_FIND_OR_MAKE(abstract, BulletTypeClass, BulletTypeClassExtension, BulletTypeExtensions);
            break;
        }

        case RTTI_CAMPAIGN:
        {
            EXT_FIND_OR_MAKE(abstract, CampaignClass, CampaignClassExtension, CampaignExtensions);
            break;
        }

        case RTTI_SIDE:
        {
            EXT_FIND_OR_MAKE(abstract, SideClass, SideClassExtension, SideExtensions);
            break;
        }

        case RTTI_HOUSE:
        {
            EXT_FIND_OR_MAKE(abstract, HouseClass, HouseClassExtension, HouseExtensions);
            break;
        }

        case RTTI_HOUSETYPE:
        {
            EXT_FIND_OR_MAKE(abstract, HouseTypeClass, HouseTypeClassExtension, HouseTypeExtensions);
            break;
        }

        case RTTI_INFANTRY:
        {
            EXT_FIND_OR_MAKE(abstract, InfantryClass, InfantryClassExtension, InfantryExtensions);
            break;
        }

        case RTTI_INFANTRYTYPE:
        {
            EXT_FIND_OR_MAKE(abstract, InfantryTypeClass, InfantryTypeClassExtension, InfantryTypeExtensions);
            break;
        }

        case RTTI_ISOTILETYPE:
        {
            EXT_FIND_OR_MAKE(abstract, IsometricTileTypeClass, IsometricTileTypeClassExtension, IsometricTileTypeExtensions);
            break;
        }

        case RTTI_OVERLAYTYPE:
        {
            EXT_FIND_OR_MAKE(abstract, OverlayTypeClass, OverlayTypeClassExtension, OverlayTypeExtensions);
            break;
        }

        case RTTI_PARTICLESYSTEMTYPE:
        {
            EXT_FIND_OR_MAKE(abstract, ParticleSystemTypeClass, ParticleSystemTypeClassExtension, ParticleSystemTypeExtensions);
            break;
        }

        case RTTI_PARTICLETYPE:
        {
            EXT_FIND_OR_MAKE(abstract, ParticleTypeClass, ParticleTypeClassExtension, ParticleTypeExtensions);
            break;
        }

        case RTTI_SMUDGETYPE:
        {
            EXT_FIND_OR_MAKE(abstract, SmudgeTypeClass, SmudgeTypeClassExtension, SmudgeTypeExtensions);
            break;
        }

        case RTTI_SUPERWEAPON:
        {
            EXT_FIND_OR_MAKE(abstract, SuperClass, SuperClassExtension, SuperExtensions);
            break;
        }

        case RTTI_SUPERWEAPONTYPE:
        {
            EXT_FIND_OR_MAKE(abstract, SuperWeaponTypeClass, SuperWeaponTypeClassExtension, SuperWeaponTypeExtensions);
            break;
        }

        case RTTI_TERRAIN:
        {
            EXT_FIND_OR_MAKE(abstract, TerrainClass, TerrainClassExtension, TerrainExtensions);
            break;
        }

        case RTTI_TERRAINTYPE:
        {
            EXT_FIND_OR_MAKE(abstract, TerrainTypeClass, TerrainTypeClassExtension, TerrainTypeExtensions);
            break;
        }

        case RTTI_TIBERIUM:
        {
            EXT_FIND_OR_MAKE(abstract, TiberiumClass, TiberiumClassExtension, TiberiumExtensions);
            break;
        }

        case RTTI_UNIT:
        {
            EXT_FIND_OR_MAKE(abstract, UnitClass, UnitClassExtension, UnitExtensions);
            break;
        }

        case RTTI_UNITTYPE:
        {
            EXT_FIND_OR_MAKE(abstract, UnitTypeClass, UnitTypeClassExtension, UnitTypeExtensions);
            break;
        }

        case RTTI_VOXELANIMTYPE:
        {
            EXT_FIND_OR_MAKE(abstract, VoxelAnimTypeClass, VoxelAnimTypeClassExtension, VoxelAnimTypeExtensions);
            break;
        }

        case RTTI_WARHEADTYPE:
        {
            EXT_FIND_OR_MAKE(abstract, WarheadTypeClass, WarheadTypeClassExtension, WarheadTypeExtensions);
            break;
        }

        case RTTI_WAVE:
        {
            EXT_FIND_OR_MAKE(abstract, WaveClass, WaveClassExtension, WaveExtensions);
            break;
        }

        case RTTI_WEAPONTYPE:
        {
            EXT_FIND_OR_MAKE(abstract, WeaponTypeClass, WeaponTypeClassExtension, WeaponTypeExtensions);
            break;
        }

        default:
            DEBUG_ERROR("Find_Or_Make_Extension: No extension support for \"%s\" implemented!\n", Name_From_RTTI((RTTIType)abstract->What_Am_I()));
            break;

    };

    /**
     *  
     */
    if (created && extptr != nullptr) {
        Set_Extension_Pointer(abstract, extptr);
    }

    return extptr;
}


/**
 *  x
 * 
 *  @author: CCHyper
 */
#include "wstring.h"
AbstractClassExtension *Fetch_Extension_Internal(const AbstractClass *abstract)
{
    ASSERT(abstract != nullptr);

    AbstractClassExtension *ext_ptr = Get_Extension_Pointer(abstract);

    if (!ext_ptr) {
        if (Wstring(Get_Abstract_Name(abstract)) == Wstring("GASPOT")) { __debugbreak(); }
        DEBUG_ERROR("Fetch_Extension: Extension for \"%s\" is null!\n", Get_Abstract_Name(abstract));
        return nullptr;
    }

    /**
     *  This is not guanteed to work, but it should capture the majority of possible bad pointers.
     * 
     *  0x00401000 -> GAME.EXE base address.
     *  0x20000000 -> Arbitrary address VINIFERA.DLL 'should' never get to.
     */
    if (((uintptr_t)ext_ptr) <= 0x00401000 || ((uintptr_t)ext_ptr) >= 0x20000000) {
        DEBUG_ERROR("Fetch_Extension: Corrupt extension pointer for \"%s\"!\n", Get_Abstract_Name(abstract));
        return nullptr;
    }

    /**
     *  Its still possible the pointer could be invalid, so perform a final check.
     */
    if (ext_ptr->What_Am_I() <= EXT_RTTI_NONE || ext_ptr->What_Am_I() >= EXT_RTTI_COUNT) {
        DEBUG_ERROR("Fetch_Extension: Invalid extension rtti type for \"%s\"!\n", Get_Abstract_Name(abstract));
        return nullptr;
    }

    //EXT_DEBUG_INFO("Fetch_Extension: Abstract \"%s\", got extension \"%s\".\n", Get_Abstract_Name(abstract), ext_ptr->Name());

    return ext_ptr;
}


/**
 *  x
 * 
 *  @author: CCHyper
 */
bool Destroy_Extension_Internal(const AbstractClass *abstract)
{
    ASSERT(abstract != nullptr);

    switch (abstract->What_Am_I()) {

        case RTTI_AIRCRAFT:
        {
            EXT_DESTROY(abstract, AircraftClass, AircraftClassExtension, AircraftExtensions);
            break;
        }

        case RTTI_AIRCRAFTTYPE:
        {
            EXT_DESTROY(abstract, AicraftTypeClass, AircraftTypeClassExtension, AircraftTypeExtensions);
            break;
        }

        case RTTI_ANIM:
        {
            EXT_DESTROY(abstract, AnimClass, AnimClassExtension, AnimExtensions);
            break;
        }

        case RTTI_ANIMTYPE:
        {
            EXT_DESTROY(abstract, AnimTypeClass, AnimTypeClassExtension, AnimTypeExtensions);
            break;
        }

        case RTTI_BUILDING:
        {
            EXT_DESTROY(abstract, BuildingClass, BuildingClassExtension, BuildingExtensions);
            break;
        }

        case RTTI_BUILDINGTYPE:
        {
            EXT_DESTROY(abstract, BuildingTypeClass, BuildingTypeClassExtension, BuildingTypeExtensions);
            break;
        }

        case RTTI_BULLETTYPE:
        {
            EXT_DESTROY(abstract, BulletTypeClass, BulletTypeClassExtension, BulletTypeExtensions);
            break;
        }

        case RTTI_CAMPAIGN:
        {
            EXT_DESTROY(abstract, CampaignClass, CampaignClassExtension, CampaignExtensions);
            break;
        }

        case RTTI_SIDE:
        {
            EXT_DESTROY(abstract, SideClass, SideClassExtension, SideExtensions);
            break;
        }

        case RTTI_HOUSE:
        {
            EXT_DESTROY(abstract, HouseClass, HouseClassExtension, HouseExtensions);
            break;
        }

        case RTTI_HOUSETYPE:
        {
            EXT_DESTROY(abstract, HouseTypeClass, HouseTypeClassExtension, HouseTypeExtensions);
            break;
        }

        case RTTI_INFANTRY:
        {
            EXT_DESTROY(abstract, InfantryClass, InfantryClassExtension, InfantryExtensions);
            break;
        }

        case RTTI_INFANTRYTYPE:
        {
            EXT_DESTROY(abstract, InfantryTypeClass, InfantryTypeClassExtension, InfantryTypeExtensions);
            break;
        }

        case RTTI_ISOTILETYPE:
        {
            EXT_DESTROY(abstract, IsometricTileTypeClass, IsometricTileTypeClassExtension, IsometricTileTypeExtensions);
            break;
        }

        case RTTI_OVERLAYTYPE:
        {
            EXT_DESTROY(abstract, OverlayTypeClass, OverlayTypeClassExtension, OverlayTypeExtensions);
            break;
        }

        case RTTI_PARTICLESYSTEMTYPE:
        {
            EXT_DESTROY(abstract, ParticleSystemTypeClass, ParticleSystemTypeClassExtension, ParticleSystemTypeExtensions);
            break;
        }

        case RTTI_PARTICLETYPE:
        {
            EXT_DESTROY(abstract, ParticleTypeClass, ParticleTypeClassExtension, ParticleTypeExtensions);
            break;
        }

        case RTTI_SMUDGETYPE:
        {
            EXT_DESTROY(abstract, SmudgeTypeClass, SmudgeTypeClassExtension, SmudgeTypeExtensions);
            break;
        }

        case RTTI_SUPERWEAPON:
        {
            EXT_DESTROY(abstract, SuperClass, SuperClassExtension, SuperExtensions);
            break;
        }

        case RTTI_SUPERWEAPONTYPE:
        {
            EXT_DESTROY(abstract, SuperWeaponTypeClass, SuperWeaponTypeClassExtension, SuperWeaponTypeExtensions);
            break;
        }

        case RTTI_TERRAIN:
        {
            EXT_DESTROY(abstract, TerrainClass, TerrainClassExtension, TerrainExtensions);
            break;
        }

        case RTTI_TERRAINTYPE:
        {
            EXT_DESTROY(abstract, TerrainTypeClass, TerrainTypeClassExtension, TerrainTypeExtensions);
            break;
        }

        case RTTI_TIBERIUM:
        {
            EXT_DESTROY(abstract, TiberiumClass, TiberiumClassExtension, TiberiumExtensions);
            break;
        }

        case RTTI_UNIT:
        {
            EXT_DESTROY(abstract, UnitClass, UnitClassExtension, UnitExtensions);
            break;
        }

        case RTTI_UNITTYPE:
        {
            EXT_DESTROY(abstract, UnitTypeClass, UnitTypeClassExtension, UnitTypeExtensions);
            break;
        }

        case RTTI_VOXELANIMTYPE:
        {
            EXT_DESTROY(abstract, VoxelAnimTypeClass, VoxelAnimTypeClassExtension, VoxelAnimTypeExtensions);
            break;
        }

        case RTTI_WARHEADTYPE:
        {
            EXT_DESTROY(abstract, WarheadTypeClass, WarheadTypeClassExtension, WarheadTypeExtensions);
            break;
        }

        case RTTI_WAVE:
        {
            EXT_DESTROY(abstract, WaveClass, WaveClassExtension, WaveExtensions);
            break;
        }

        case RTTI_WEAPONTYPE:
        {
            EXT_DESTROY(abstract, WeaponTypeClass, WeaponTypeClassExtension, WeaponTypeExtensions);
            break;
        }

        default:
            DEBUG_ERROR("Destroy_Extension: No extension support for \"%s\" implemented!\n", Name_From_RTTI((RTTIType)abstract->What_Am_I()));
            break;

    };

    /**
     *  Clear the pointer in the abstract class.
     */
    Clear_Extension_Pointer(abstract);

    return true;
}


/**
 *  x
 * 
 *  @author: CCHyper
 */
bool Save_Extensions(IStream *pStm)
{
    ASSERT(pStm != nullptr);

    if (!pStm) {
        return false;
    }

    EXT_SAVE(AircraftClass, AircraftClassExtension, AircraftExtensions);
    EXT_SAVE(AircraftTypeClass, AircraftTypeClassExtension, AircraftTypeExtensions);
    EXT_SAVE(AnimClass, AnimClassExtension, AnimExtensions);
    EXT_SAVE(AnimTypeClass, AnimTypeClassExtension, AnimTypeExtensions);
    EXT_SAVE(BuildingClass, BuildingClassExtension, BuildingExtensions);
    EXT_SAVE(BuildingTypeClass, BuildingTypeClassExtension, BuildingTypeExtensions);
    EXT_SAVE(BulletTypeClass, BulletTypeClassExtension, BulletTypeExtensions);
    EXT_SAVE(CampaignClass, CampaignClassExtension, CampaignExtensions);
    EXT_SAVE(SideClass, SideClassExtension, SideExtensions);
    EXT_SAVE(HouseClass, HouseClassExtension, HouseExtensions);
    EXT_SAVE(HouseTypeClass, HouseTypeClassExtension, HouseTypeExtensions);
    EXT_SAVE(InfantryClass, InfantryClassExtension, InfantryExtensions);
    EXT_SAVE(InfantryTypeClass, InfantryTypeClassExtension, InfantryTypeExtensions);
    EXT_SAVE(IsometricTileTypeClass, IsometricTileTypeClassExtension, IsometricTileTypeExtensions);
    EXT_SAVE(OverlayTypeClass, OverlayTypeClassExtension, OverlayTypeExtensions);
    EXT_SAVE(ParticleSystemTypeClass, ParticleSystemTypeClassExtension, ParticleSystemTypeExtensions);
    EXT_SAVE(ParticleTypeClass, ParticleTypeClassExtension, ParticleTypeExtensions);
    EXT_SAVE(SmudgeTypeClass, SmudgeTypeClassExtension, SmudgeTypeExtensions);
    EXT_SAVE(SuperClass, SuperClassExtension, SuperExtensions);
    EXT_SAVE(SuperWeaponTypeClass, SuperWeaponTypeClassExtension, SuperWeaponTypeExtensions);
    EXT_SAVE(TerrainClass, TerrainClassExtension, TerrainExtensions);
    EXT_SAVE(TerrainTypeClass, TerrainTypeClassExtension, TerrainTypeExtensions);
    EXT_SAVE(TiberiumClass, TiberiumClassExtension, TiberiumExtensions);
    EXT_SAVE(UnitClass, UnitClassExtension, UnitExtensions);
    EXT_SAVE(UnitTypeClass, UnitTypeClassExtension, UnitTypeExtensions);
    EXT_SAVE(VoxelAnimTypeClass, VoxelAnimTypeClassExtension, VoxelAnimTypeExtensions);
    EXT_SAVE(WarheadTypeClass, WarheadTypeClassExtension, WarheadTypeExtensions);
    EXT_SAVE(WaveClass, WaveClassExtension, WaveExtensions);
    EXT_SAVE(WeaponTypeClass, WeaponTypeClassExtension, WeaponTypeExtensions);

    return true;
}


/**
 *  x
 * 
 *  @author: CCHyper
 */
bool Load_Extensions(IStream *pStm)
{
    ASSERT(pStm != nullptr);

    if (!pStm) {
        return false;
    }

    EXT_LOAD(AircraftClass, AircraftClassExtension, AircraftExtensions);
    EXT_LOAD(AircraftTypeClass, AircraftTypeClassExtension, AircraftTypeExtensions);
    EXT_LOAD(AnimClass, AnimClassExtension, AnimExtensions);
    EXT_LOAD(AnimTypeClass, AnimTypeClassExtension, AnimTypeExtensions);
    EXT_LOAD(BuildingClass, BuildingClassExtension, BuildingExtensions);
    EXT_LOAD(BuildingTypeClass, BuildingTypeClassExtension, BuildingTypeExtensions);
    EXT_LOAD(BulletTypeClass, BulletTypeClassExtension, BulletTypeExtensions);
    EXT_LOAD(CampaignClass, CampaignClassExtension, CampaignExtensions);
    EXT_LOAD(SideClass, SideClassExtension, SideExtensions);
    EXT_LOAD(HouseClass, HouseClassExtension, HouseExtensions);
    EXT_LOAD(HouseTypeClass, HouseTypeClassExtension, HouseTypeExtensions);
    EXT_LOAD(InfantryClass, InfantryClassExtension, InfantryExtensions);
    EXT_LOAD(InfantryTypeClass, InfantryTypeClassExtension, InfantryTypeExtensions);
    EXT_LOAD(IsometricTileTypeClass, IsometricTileTypeClassExtension, IsometricTileTypeExtensions);
    EXT_LOAD(OverlayTypeClass, OverlayTypeClassExtension, OverlayTypeExtensions);
    EXT_LOAD(ParticleSystemTypeClass, ParticleSystemTypeClassExtension, ParticleSystemTypeExtensions);
    EXT_LOAD(ParticleTypeClass, ParticleTypeClassExtension, ParticleTypeExtensions);
    EXT_LOAD(SmudgeTypeClass, SmudgeTypeClassExtension, SmudgeTypeExtensions);
    EXT_LOAD(SuperClass, SuperClassExtension, SuperExtensions);
    EXT_LOAD(SuperWeaponTypeClass, SuperWeaponTypeClassExtension, SuperWeaponTypeExtensions);
    EXT_LOAD(TerrainClass, TerrainClassExtension, TerrainExtensions);
    EXT_LOAD(TerrainTypeClass, TerrainTypeClassExtension, TerrainTypeExtensions);
    EXT_LOAD(TiberiumClass, TiberiumClassExtension, TiberiumExtensions);
    EXT_LOAD(UnitClass, UnitClassExtension, UnitExtensions);
    EXT_LOAD(UnitTypeClass, UnitTypeClassExtension, UnitTypeExtensions);
    EXT_LOAD(VoxelAnimTypeClass, VoxelAnimTypeClassExtension, VoxelAnimTypeExtensions);
    EXT_LOAD(WarheadTypeClass, WarheadTypeClassExtension, WarheadTypeExtensions);
    EXT_LOAD(WaveClass, WaveClassExtension, WaveExtensions);
    EXT_LOAD(WeaponTypeClass, WeaponTypeClassExtension, WeaponTypeExtensions);

    return true;
}
