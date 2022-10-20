/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          RULESEXT_INIT.CPP
 *
 *  @author        CCHyper
 *
 *  @brief         Contains the hooks for initialising the extended RulesClass.
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
#include "rulesext_hooks.h"
#include "rulesext.h"
#include "rules.h"
#include "tibsun_globals.h"
#include "vinifera_util.h"
#include "extension.h"
#include "extension_globals.h"
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
DECLARE_PATCH(_RulesClass_Constructor_Patch)
{
    GET_REGISTER_STATIC(RulesClass *, this_ptr, esi); // "this" pointer.
    static RulesClassExtension *ext_ptr;

    /**
     *  Create the extended class instance.
     */
    ext_ptr = Extension::Singleton::Make<RulesClass, RulesClassExtension>(this_ptr);
    if (!ext_ptr) {
        DEBUG_ERROR("Failed to create RuleExtension instance for 0x%08X!\n", (uintptr_t)this_ptr);
        ShowCursor(TRUE);
        MessageBoxA(MainWindow, "Failed to create RuleExtension instance!\n", "Vinifera", MB_OK|MB_ICONEXCLAMATION);
        Vinifera_Generate_Mini_Dump();
        Fatal("Failed to create RuleExtension instance!\n");
        goto original_code; // Keep this for clean code analysis.
    }

    RuleExtension = ext_ptr;

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { mov eax, this_ptr }
    _asm { pop edi }
    _asm { pop esi }
    _asm { pop ebp }
    _asm { pop ebx }
    _asm { ret }
}


/**
 *  Patch for including the extended class members in the destruction process.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_RulesClass_Destructor_Patch)
{
    GET_REGISTER_STATIC(RulesClass *, this_ptr, esi);

    /**
     *  Remove the extended class instance.
     */
    Extension::Singleton::Destroy<RulesClass, RulesClassExtension>(RuleExtension);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { pop edi }
    _asm { pop esi }
    _asm { pop ebp }
    _asm { pop ebx }
    _asm { ret }
}


/**
 *  Patch for including the extended class members when initialsing rules data.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_RulesClass_Initialize_Patch)
{
    GET_STACK_STATIC(RulesClass *, this_ptr, esp, 0x10);
    GET_STACK_STATIC(CCINIClass *, ini, esp, 0x44);

    RuleExtension->Initialize(*ini);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { pop edi }
    _asm { pop esi }
    _asm { pop ebp }
    _asm { pop ebx }
    _asm { add esp, 0x130 }
    _asm { ret 4 }
}


/**
 *  Patch for including the extended class members when processing rules data.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_RulesClass_Process_Patch)
{
    GET_REGISTER_STATIC(RulesClass *, this_ptr, ebp);
    GET_REGISTER_STATIC(CCINIClass *, ini, esi);

    RuleExtension->Process(*ini);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { pop edi }
    _asm { pop esi }
    _asm { pop ebp }
    _asm { pop ebx }
    _asm { add esp, 0x20 }
    _asm { ret 4 }
}


/**
 *  Patch for including the extended class members when processing the MPlayer section.
 * 
 *  @warning: Do not touch this unless you know what you are doing!
 * 
 *  @author: CCHyper
 */
DECLARE_PATCH(_RulesClass_MPlayer_Patch)
{
    GET_REGISTER_STATIC(RulesClass *, this_ptr, esi);
    GET_REGISTER_STATIC(CCINIClass *, ini, edi);

    RuleExtension->MPlayer(*ini);

    /**
     *  Stolen bytes here.
     */
original_code:
    _asm { mov al, 1 }
    _asm { pop edi }
    _asm { pop esi }
    _asm { ret 4 }
}


/**
 *  Main function for patching the hooks.
 */
void RulesClassExtension_Init()
{
    Patch_Jump(0x005C59A1, &_RulesClass_Constructor_Patch);
    Patch_Jump(0x005C6120, &_RulesClass_Destructor_Patch);
    Patch_Jump(0x005C66FF, &_RulesClass_Initialize_Patch);
    Patch_Jump(0x005C6A4D, &_RulesClass_Process_Patch);
    Patch_Jump(0x005CC3BF, &_RulesClass_MPlayer_Patch);
}
