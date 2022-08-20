/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          EXT_HOOKS.CPP
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
#include "saveload_hooks.h"
#include "iomap.h"

/**
 *  Extended classes here.
 */
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

#include "objecttypeext_hooks.h"
#include "technotypeext_hooks.h"
#include "buildingtypeext_hooks.h"
#include "unittypeext_hooks.h"
#include "infantrytypeext_hooks.h"
#include "aircrafttypeext_hooks.h"
#include "warheadtypeext_hooks.h"
#include "weapontypeext_hooks.h"
#include "bullettypeext_hooks.h"
#include "supertypeext_hooks.h"
#include "voxelanimtypeext_hooks.h"
#include "animtypeext_hooks.h"
#include "particletypeext_hooks.h"
#include "particlesystypeext_hooks.h"
#include "isotiletypeext_hooks.h"
#include "overlaytypeext_hooks.h"
#include "smudgetypeext_hooks.h"
#include "terraintypeext_hooks.h"
#include "housetypeext_hooks.h"
#include "sideext_hooks.h"
#include "campaignext_hooks.h"
#include "tiberiumext_hooks.h"
//#include "taskforceext_hooks.h"
//#include "aitrigtypeext_hooks.h"
//#include "scripttypeext_hooks.h"
//#include "tagtypeext_hooks.h"
//#include "triggertypeext_hooks.h"

#include "technoext_hooks.h"
#include "footext_hooks.h"

#include "unitext_hooks.h"
#include "buildingext_hooks.h"
#include "aircraftext_hooks.h"
#include "infantryext_hooks.h"
#include "cellext_hooks.h"
#include "houseext_hooks.h"
#include "teamext_hooks.h"
#include "tactionext_hooks.h"
#include "factoryext_hooks.h"
#include "animext_hooks.h"
#include "bulletext_hooks.h"
#include "terrainext_hooks.h"
#include "superext_hooks.h"
#include "particlesysext_hooks.h"

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

#include "hooker.h"
#include "hooker_macros.h"
#include "swizzle.h"


/**
 *  This patch clears the DWORD at 0x10 (0x10 is "bool IsDirty") to use the space
 *  for storing a pointer to the extension class instance for this AbstractClass.
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_AbstractClass_Constructor_Extension)
{
    _asm { mov eax, ecx }
    _asm { xor ecx, ecx }

    _asm { mov [eax+0x8], 0xFFFFFFFF } // ID
    _asm { mov [eax+0x0C], ecx } // HeapID
    _asm { mov [eax+0x10], ecx } // IsDirty, now reused as a extension pointer.

    _asm { mov [eax+0x0], 0x006CAA6C } // offset const AbstractClass::`vftable'
    _asm { mov [eax+0x4], 0x006CAA54 } // offset const AbstractClass::`vftable' for IRTTITypeInfo

    _asm { retn }
}


/**
 *  This patch forces AbstractClass::IsDirty() to return true.
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_AbstractClass_IsDirty_Return_True)
{
    _asm { xor eax, eax }
    _asm { mov al, 1 }
    _asm { ret 4 }
}

bool &IsFS = Make_Global<bool>(0x007E497C);

class AbstractClassExtension;
extern DynamicVectorClass<AbstractClassExtension *> AllExtensions;

HRESULT STDMETHODCALLTYPE Abstract_Save(AbstractClass *This, IStream *pStm, BOOL fClearDirty)
{
    if (!pStm) {
        return E_POINTER;
    }

    ULONG id = (ULONG)This;
    HRESULT hr = pStm->Write(&id, sizeof(id), nullptr);
    if (hr < 0) {
        return hr;
    }

    hr = pStm->Write(This, This->Size_Of(false), nullptr);

    uintptr_t extension_address = (*(unsigned int *)((char *)This + 0x10));
    uintptr_t extension_id = -1;
    if (extension_address != 0) {
        extension_id = (uintptr_t)AllExtensions.ID((AbstractClassExtension *)extension_address);
        DEBUG_INFO("Saving Extension %X as ID %d\n", extension_address, extension_id);
    }
    
    hr = pStm->Write(&extension_id, sizeof(extension_id), nullptr);

    return hr;
}

HRESULT STDMETHODCALLTYPE Abstract_Load(AbstractClass *This, IStream *pStm)
{
    if (!pStm) {
        return E_POINTER;
    }

    ULONG id;
    HRESULT hr = pStm->Read(&id, sizeof(ULONG), nullptr);
    if (hr < 0) {
        return hr;
    }
    SwizzleManager.Here_I_Am((LONG)id, This);

    int heap_id = This->HeapID;

    hr = pStm->Read(This, This->Size_Of(IsFS), nullptr);

    This->HeapID = heap_id;


    uintptr_t extension_address = 0;
    uintptr_t extension_id = -1;

    hr = pStm->Read(&extension_id, sizeof(extension_id), nullptr);

    if (extension_id != -1) {
        extension_address = (uintptr_t)AllExtensions[extension_id];
        DEBUG_INFO("Loading Extension %X from ID %d\n", extension_address, extension_id);
    }

    (*(uintptr_t *)((char *)This + 0x10)) = extension_address;

    return hr;
}

static void Extension_Abstract_Hooks()
{
    Patch_Jump(0x00405B50, &_AbstractClass_Constructor_Extension);
    Patch_Jump(0x00405E00, &_AbstractClass_IsDirty_Return_True);

    Patch_Jump(0x00405CB0, &Abstract_Save);
    Patch_Jump(0x00405D10, &Abstract_Load);
    /**
     *  Removes the branch from AbstractClass::Abstract_Save which clears IsDirty.
     */
    Patch_Byte_Range(0x00405CF8, 0x90, 12);
}


void Extension_Hooks()
{
    FetchRes_Hooks();
    FilePCXExtension_Hooks();
    CCINIClassExtension_Hooks();
    RawFileClassExtension_Hooks();
    CCFileClassExtension_Hooks();
    CDExtension_Hooks();

    /**
     *  Hook the new save and load system in.
     */
    SaveLoad_Hooks();

    /**
     *  Hook in any new classes.
     */
    TheaterTypeClassExtension_Hooks();

    /**
     *  Dialogs and associated code.
     */
    SkirmishDialog_Hooks();

    /**
     *  Miscellaneous hooks
     */
    ToolTipManagerExtension_Hooks();
    CommandExtension_Hooks();
    MessageListClassExtension_Hooks();
    CombatExtension_Hooks();
    PlayMovieExtension_Hooks();
    VQAExtension_Hooks();
    TextLabelClassExtension_Hooks();
    DropshipExtension_Hooks();
    EndGameExtension_Hooks();

    /**
     *  Various functions.
     */
    GameInit_Hooks();
    MainLoop_Hooks();
    NewMenuExtension_Hooks();

    /**
     *  Command line option to disable all extensions.
     */
    const char *cmdline = GetCommandLineA();
    bool no_extensions = (std::strstr(cmdline, "-NO_EXT") != nullptr);
    if (no_extensions) {
        return;
    }

    /**
     *  Command line option to disable class extensions.
     */
    cmdline = GetCommandLineA();
    bool no_class_extensions = (std::strstr(cmdline, "-NO_CLASS_EXT") != nullptr);
    if (no_class_extensions) {
        return;
    }

    Extension_Abstract_Hooks();

    /**
     *  All game class extensions here.
     */
    CellClassExtension_Hooks();
    FactoryClassExtension_Hooks();
    TeamClassExtension_Hooks();
    EMPulseClassExtension_Hooks();
    WaveClassExtension_Hooks();
    TActionClassExtension_Hooks();
    ObjectTypeClassExtension_Hooks();
    TechnoClassExtension_Hooks();
    TechnoTypeClassExtension_Hooks();
    FootClassExtension_Hooks();
    BuildingClassExtension_Hooks();
    BuildingTypeClassExtension_Hooks();
    UnitClassExtension_Hooks();
    UnitTypeClassExtension_Hooks();
    InfantryClassExtension_Hooks();
    InfantryTypeClassExtension_Hooks();
    AircraftClassExtension_Hooks();
    AircraftTypeClassExtension_Hooks();

    WarheadTypeClassExtension_Hooks();
    WeaponTypeClassExtension_Hooks();
    BulletClassExtension_Hooks();
    BulletTypeClassExtension_Hooks();

    SuperClassExtension_Hooks();
    SuperWeaponTypeClassExtension_Hooks();
    VoxelAnimTypeClassExtension_Hooks();
    //AnimClassExtension_Hooks();
    //AnimTypeClassExtension_Hooks();

    ParticleTypeClassExtension_Hooks();
    ParticleSystemClassExtension_Hooks();
    ParticleSystemTypeClassExtension_Hooks();
    //IsometricTileTypeClassExtension_Hooks();

    TiberiumClassExtension_Hooks();

    OverlayTypeClassExtension_Hooks();
    SmudgeTypeClassExtension_Hooks();

    TerrainClassExtension_Hooks();
    TerrainTypeClassExtension_Hooks();

    HouseClassExtension_Hooks();
    HouseTypeClassExtension_Hooks();

    SideClassExtension_Hooks();
    CampaignClassExtension_Hooks();

    /**
     *  All global class extensions here.
     */
    OptionsClassExtension_Hooks();
    RulesClassExtension_Hooks();
    TacticalExtension_Hooks();
    ScenarioClassExtension_Hooks();
    SessionClassExtension_Hooks();
    DisplayClassExtension_Hooks();
    SidebarClassExtension_Hooks();
    ThemeClassExtension_Hooks();

    MultiMissionExtension_Hooks();

    MapSeedClassExtension_Hooks();
    MultiScoreExtension_Hooks();

}
