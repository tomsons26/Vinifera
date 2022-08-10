/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          HOUSETYPEEXT_INIT.CPP
 *
 *  @author        CCHyper
 *
 *  @brief         Contains the hooks for initialising the extended HouseTypeClass.
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
#include "housetypeext_hooks.h"
#include "housetypeext.h"
#include "housetype.h"
#include "tibsun_globals.h"
#include "vinifera_util.h"
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
DECLARE_PATCH(_HouseTypeClass_Constructor_Patch)
{
    GET_REGISTER_STATIC(HouseTypeClass *, this_ptr, esi); // "this" pointer.
    GET_STACK_STATIC(const char *, ini_name, esp, 0xC); // ini name.
    static HouseTypeClassExtension *exttype_ptr;

    //EXT_DEBUG_TRACE("Creating HouseTypeClassExtension instance for \"%s\".\n", ini_name);

    /**
     *  Find existing or create an extended class instance.
     */
    exttype_ptr = Find_Or_Make_Extension<HouseTypeClassExtension>(this_ptr);
    if (!exttype_ptr) {
        DEBUG_ERROR("Failed to create HouseTypeClassExtensions instance for \"%s\"!\n", ini_name);
        ShowCursor(TRUE);
        MessageBoxA(MainWindow, "Failed to create HouseTypeClassExtensions instance!\n", "Vinifera", MB_OK|MB_ICONEXCLAMATION);
        Vinifera_Generate_Mini_Dump();
        Fatal("Failed to create HouseTypeClassExtensions instance!\n");
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
DECLARE_PATCH(_HouseTypeClass_NoInit_Constructor_Patch)
{
    GET_REGISTER_STATIC(HouseTypeClass *, this_ptr, esi);
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
DECLARE_PATCH(_HouseTypeClass_Destructor_Patch)
{
    GET_REGISTER_STATIC(HouseTypeClass *, this_ptr, esi);

    /**
     *  Remove the extended class from the global index.
     */
    Destroy_Extension<HouseTypeClassExtension>(this_ptr);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { mov edx, 0x007E21D0 } // HouseTypes.vtble
    _asm { mov edx, [edx] }
    JMP_REG(eax, 0x004CDE9E);
}


/**
 *  Patch for including the extended class members in the virtual destruction process.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_HouseTypeClass_Scalar_Destructor_Patch)
{
    GET_REGISTER_STATIC(HouseTypeClass *, this_ptr, esi);

    /**
     *  Remove the extended class from the global index.
     */
    Destroy_Extension<HouseTypeClassExtension>(this_ptr);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { mov edx, 0x007E21D0 } // HouseTypes.vtble
    _asm { mov edx, [edx] }
    JMP_REG(eax, 0x004CE60E);
}


/**
 *  Patch for including the extended class members when computing a unique crc value for this instance.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_HouseTypeClass_Compute_CRC_Patch)
{
    GET_REGISTER_STATIC(HouseTypeClass *, this_ptr, esi);
    GET_STACK_STATIC(WWCRCEngine *, crc, esp, 0x10);
    static HouseTypeClassExtension *exttype_ptr;

    /**
     *  Find the extension instance.
     */
    exttype_ptr = Fetch_Extension<HouseTypeClassExtension>(this_ptr);
    if (!exttype_ptr) {
        goto original_code;
    }

    /**
     *  Read type class detach.
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
DECLARE_PATCH(_HouseTypeClass_Read_INI_Patch)
{
    GET_REGISTER_STATIC(HouseTypeClass *, this_ptr, ebx);
    GET_STACK_STATIC(CCINIClass *, ini, ebp, 0x8); // Can't use ESI as its reused by this point.
    static HouseTypeClassExtension *exttype_ptr;

    /**
     *  Find the extension instance.
     */
    exttype_ptr = Fetch_Extension<HouseTypeClassExtension>(this_ptr);
    if (!exttype_ptr) {
        goto original_code;
    }

    /**
     *  Read type class ini.
     */
    exttype_ptr->Read_INI(*ini);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { mov al, 1 }
    _asm { pop edi }
    _asm { pop esi }
    _asm { pop ebx }
    _asm { mov esp, ebp }
    _asm { pop ebp }
    _asm { ret 4 }
}


/**
 *  Main function for patching the hooks.
 */
void HouseTypeClassExtension_Init()
{
    Patch_Jump(0x004CDE57, &_HouseTypeClass_Constructor_Patch);
    Patch_Jump(0x004CDE7A, &_HouseTypeClass_NoInit_Constructor_Patch);
    //Patch_Jump(0x004CDE98, &_HouseTypeClass_Destructor_Patch); // Destructor is actually inlined in scalar destructor!
    Patch_Jump(0x004CE608, &_HouseTypeClass_Scalar_Destructor_Patch);
    Patch_Jump(0x004CE2FE, &_HouseTypeClass_Compute_CRC_Patch);
    Patch_Jump(0x004CE1F3, &_HouseTypeClass_Read_INI_Patch);
}
