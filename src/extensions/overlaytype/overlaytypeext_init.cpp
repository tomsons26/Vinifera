/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          OVERLAYTYPEEXT_INIT.CPP
 *
 *  @author        CCHyper
 *
 *  @brief         Contains the hooks for initialising the extended OverlayTypeClass.
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
#include "overlaytypeext_hooks.h"
#include "overlaytypeext.h"
#include "overlaytype.h"
#include "tibsun_globals.h"
#include "vinifera_util.h"
#include "vinifera_globals.h"
#include "extension.h"
#include "fatal.h"
#include "debughandler.h"
#include "asserthandler.h"

#include "hooker.h"
#include "hooker_macros.h"


/**
 *  Patch for including the extended class members in the creation process.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_OverlayTypeClass_Constructor_Patch)
{
    GET_REGISTER_STATIC(OverlayTypeClass *, this_ptr, esi); // "this" pointer.
    GET_STACK_STATIC(const char *, ini_name, esp, 0xC); // ini name.
    static OverlayTypeClassExtension *exttype_ptr;

    /**
     *  If we are performing a load operation, the Windows API will invoke the
     *  constructors for us as part of the operation, so we can skip our hook here.
     */
    if (Vinifera_PerformingLoad) {
        goto original_code;
    }

    //EXT_DEBUG_TRACE("Creating OverlayTypeClassExtension instance for \"%s\".\n", ini_name);

    /**
     *  Find existing or create an extended class instance.
     */
    exttype_ptr = Extension::Make<OverlayTypeClassExtension>(this_ptr);
    if (!exttype_ptr) {
        DEBUG_ERROR("Failed to create OverlayTypeClassExtensions instance for \"%s\"!\n", ini_name);
        ShowCursor(TRUE);
        MessageBoxA(MainWindow, "Failed to create OverlayTypeClassExtensions instance!\n", "Vinifera", MB_OK|MB_ICONEXCLAMATION);
        Vinifera_Generate_Mini_Dump();
        Fatal("Failed to create OverlayTypeClassExtensions instance!\n");
        goto original_code; // Keep this for clean code analysis.
    }

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { mov eax, this_ptr }
    _asm { pop esi }
    _asm { pop ebx }
    _asm { ret 4 }
}


/**
 *  Patch for including the extended class members in the noinit creation process.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_OverlayTypeClass_NoInit_Constructor_Patch)
{
    GET_REGISTER_STATIC(OverlayTypeClass *, this_ptr, esi);
    GET_STACK_STATIC(const NoInitClass *, noinit_ptr, esp, 0x4);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { mov eax, this_ptr }
    _asm { pop esi }
    _asm { ret 4 }
}


/**
 *  Patch for including the extended class members in the destruction process.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_OverlayTypeClass_Destructor_Patch)
{
    GET_REGISTER_STATIC(OverlayTypeClass *, this_ptr, esi);

    /**
     *  Remove the extended class from the global index.
     */
    Extension::Destroy<OverlayTypeClassExtension>(this_ptr);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { mov edx, ds:0x007E22A0 } // OverlayTypes.vtble
    JMP_REG(eax, 0x0058D1A1);
}


/**
 *  Patch for including the extended class members in the virtual destruction process.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_OverlayTypeClass_Scalar_Destructor_Patch)
{
    GET_REGISTER_STATIC(OverlayTypeClass *, this_ptr, esi);

    /**
     *  Remove the extended class from the global index.
     */
    Extension::Destroy<OverlayTypeClassExtension>(this_ptr);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { mov edx, ds:0x007E22A0 } // OverlayTypes.vtble
    JMP_REG(eax, 0x0058DC91);
}


/**
 *  Patch for including the extended class members when computing a unique crc value for this instance.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_OverlayTypeClass_Compute_CRC_Patch)
{
    GET_REGISTER_STATIC(OverlayTypeClass *, this_ptr, esi);
    GET_STACK_STATIC(WWCRCEngine *, crc, esp, 0xC);
    static OverlayTypeClassExtension *exttype_ptr;

    /**
     *  Fetch the extension instance.
     */
    exttype_ptr = Extension::Fetch<OverlayTypeClassExtension>(this_ptr);

    /**
     *  Read type class compute crc.
     */
    exttype_ptr->Compute_CRC(*crc);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { pop edi }
    _asm { pop esi }
    _asm { ret 4 }
}


/**
 *  Patch for reading the extended class members from the ini instance.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_OverlayTypeClass_Read_INI_Patch)
{
    GET_REGISTER_STATIC(bool, is_a_rock, al);  // Return from INIClass::Get_Bool() for "IsARock".
    GET_REGISTER_STATIC(OverlayTypeClass *, this_ptr, esi);
    GET_REGISTER_STATIC(CCINIClass *, ini, ebx);
    static OverlayTypeClassExtension *exttype_ptr;

    /**
     *  Fetch the extension instance.
     */
    exttype_ptr = Extension::Fetch<OverlayTypeClassExtension>(this_ptr);

    /**
     *  Read type class ini.
     */
    exttype_ptr->Read_INI(*ini);

    /**
     *  Stolen bytes here.
     */
original_code:
    this_ptr->IsARock = is_a_rock;

    _asm { mov al, 1 }
    _asm { pop edi }
    _asm { pop ebp }
    _asm { pop esi }
    _asm { pop ebx }
    _asm { add esp, 0x280 }
    _asm { ret 4 }
}


/**
 *  Main function for patching the hooks.
 */
void OverlayTypeClassExtension_Init()
{
    Patch_Jump(0x0058D120, &_OverlayTypeClass_Constructor_Patch);
    Patch_Jump(0x0058D12D, &_OverlayTypeClass_Constructor_Patch);
    //Patch_Jump(0x0058D15A, &_OverlayTypeClass_NoInit_Constructor_Patch);
    //Patch_Jump(0x0058D19B, &_OverlayTypeClass_Destructor_Patch); // Destructor is actually inlined in scalar destructor!
    Patch_Jump(0x0058DC8B, &_OverlayTypeClass_Scalar_Destructor_Patch);
    //Patch_Jump(0x0058D7EA, &_OverlayTypeClass_Compute_CRC_Patch);
    Patch_Jump(0x0058D709, &_OverlayTypeClass_Read_INI_Patch);
}
