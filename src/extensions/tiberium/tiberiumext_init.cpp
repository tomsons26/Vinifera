/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          TIBERIUMEXT_INIT.CPP
 *
 *  @author        CCHyper
 *
 *  @brief         Contains the hooks for initialising the extended TiberiumClass.
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
#include "tiberiumext_hooks.h"
#include "tiberiumext.h"
#include "tiberium.h"
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
DECLARE_PATCH(_TiberiumClass_Constructor_Patch)
{
    GET_REGISTER_STATIC(TiberiumClass *, this_ptr, esi); // "this" pointer.
    GET_STACK_STATIC(const char *, ini_name, esp, 0x10); // ini name.
    static TiberiumClassExtension *exttype_ptr;

    //EXT_DEBUG_TRACE("Creating TiberiumClassExtension instance for \"%s\".\n", ini_name);

    /**
     *  Find existing or create an extended class instance.
     */
    exttype_ptr = Find_Or_Make_Extension<TiberiumClassExtension>(this_ptr);
    if (!exttype_ptr) {
        DEBUG_ERROR("Failed to create TiberiumClassExtensions instance for \"%s\"!\n", ini_name);
        ShowCursor(TRUE);
        MessageBoxA(MainWindow, "Failed to create TiberiumClassExtensions instance!\n", "Vinifera", MB_OK|MB_ICONEXCLAMATION);
        Vinifera_Generate_Mini_Dump();
        Fatal("Failed to create TiberiumClassExtensions instance!\n");
        goto original_code; // Keep this for clean code analysis.
    }

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { mov eax, this_ptr }
    _asm { pop edi }
    _asm { pop esi }
    _asm { pop ebx }
    _asm { ret 4 }
}


/**
 *  Patch for including the extended class members in the destruction process.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_TiberiumClass_Destructor_Patch)
{
    GET_REGISTER_STATIC(TiberiumClass *, this_ptr, esi);

    /**
     *  Remove the extended class from the global index.
     */
    Destroy_Extension<TiberiumClassExtension>(this_ptr);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { mov edx, ds:0x0080F408 } // Tiberiums.vtble
    JMP_REG(eax, 0x00644A99);
}


/**
 *  Patch for including the extended class members to the base class detach process.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_TiberiumClass_Detach_Patch)
{
    GET_REGISTER_STATIC(TiberiumClass *, this_ptr, esi);
    GET_STACK_STATIC(TARGET, target, esp, 0x4);
    GET_STACK_STATIC8(bool, all, esp, 0x8);
    static TiberiumClassExtension *exttype_ptr;

    /**
     *  Fetch the extension instance.
     */
    exttype_ptr = Fetch_Extension<TiberiumClassExtension>(this_ptr);

    /**
     *  Read type class detach.
     */
    exttype_ptr->Detach(target, all);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { ret 8 }
}


/**
 *  Patch for including the extended class members when computing a unique crc value for this instance.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_TiberiumClass_Compute_CRC_Patch)
{
    GET_REGISTER_STATIC(TiberiumClass *, this_ptr, esi);
    GET_STACK_STATIC(WWCRCEngine *, crc, esp, 0xC);
    static TiberiumClassExtension *exttype_ptr;

    /**
     *  Fetch the extension instance.
     */
    exttype_ptr = Fetch_Extension<TiberiumClassExtension>(this_ptr);

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
DECLARE_PATCH(_TiberiumClass_Read_INI_Patch)
{
    GET_REGISTER_STATIC(TiberiumClass *, this_ptr, esi);
    GET_REGISTER_STATIC(CCINIClass *, ini, ebx);
    static TiberiumClassExtension *exttype_ptr;

    /**
     *  Fetch the extension instance.
     */
    exttype_ptr = Fetch_Extension<TiberiumClassExtension>(this_ptr);

    /**
     *  Read type class ini.
     */
    exttype_ptr->Read_INI(*ini);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { mov al, 1 }
    _asm { pop esi }
    _asm { pop ebx }
    _asm { add esp, 0x0BC }
    _asm { ret 4 }
}


/**
 *  Main function for patching the hooks.
 */
void TiberiumClassExtension_Init()
{
    Patch_Jump(0x00644A20, &_TiberiumClass_Constructor_Patch);
    Patch_Jump(0x00644A93, &_TiberiumClass_Destructor_Patch);
    Patch_Jump(0x00645326, &_TiberiumClass_Detach_Patch);
    Patch_Jump(0x00644FCA, &_TiberiumClass_Compute_CRC_Patch);
    Patch_Jump(0x00644E74, &_TiberiumClass_Read_INI_Patch);
}
