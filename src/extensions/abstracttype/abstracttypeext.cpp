/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          ABSTRACTTYPEEXT.CPP
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
#pragma once

#include "abstracttypeext.h"
#include "abstracttype.h"
#include "ccini.h"
#include "extension.h"


/**
 *  Class constructor.
 *  
 *  @author: CCHyper
 */
AbstractTypeClassExtension::AbstractTypeClassExtension(AbstractTypeClass *this_ptr) :
    AbstractClassExtension(this_ptr)
{
    //EXT_DEBUG_TRACE("AbstractTypeClassExtension constructor - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


/**
 *  Class no-init constructor.
 *  
 *  @author: CCHyper
 */
AbstractTypeClassExtension::AbstractTypeClassExtension(const NoInitClass &noinit) :
    AbstractClassExtension(noinit)
{
    //EXT_DEBUG_TRACE("AbstractTypeClassExtension no init constructor - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


/**
 *  Class destructor.
 *  
 *  @author: CCHyper
 */
AbstractTypeClassExtension::~AbstractTypeClassExtension()
{
    //EXT_DEBUG_TRACE("AbstractTypeClassExtension destructor - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


/**
 *  Fetches the extension data from the INI database.  
 *  
 *  @author: CCHyper
 */
bool AbstractTypeClassExtension::Read_INI(CCINIClass &ini)
{
    //EXT_DEBUG_TRACE("AbstractTypeClassExtension::Read_INI - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    const char *ini_name = Name();

    if (!ini.Is_Present(ini_name)) {
        return false;
    }

    return true;
}


/**
 *  x 
 *  
 *  @author: CCHyper
 */
const char *AbstractTypeClassExtension::Name() const
{
    //EXT_DEBUG_TRACE("AbstractTypeClassExtension::Name - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    const char *name = reinterpret_cast<const AbstractTypeClass *>(This())->Name();
    //EXT_DEBUG_INFO("AbstractTypeClassExtension: Name -> %s.\n", name);
    return name;
}


/**
 *  x 
 *  
 *  @author: CCHyper
 */
const char *AbstractTypeClassExtension::Full_Name() const
{
    //EXT_DEBUG_TRACE("AbstractTypeClassExtension::Full_Name - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    const char *name = reinterpret_cast<const AbstractTypeClass *>(This())->Full_Name();
    //EXT_DEBUG_INFO("AbstractTypeClassExtension: Full_Name -> %s.\n", name);
    return name;
}
