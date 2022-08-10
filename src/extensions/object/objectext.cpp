/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          OBJECTEXT.H
 *
 *  @author        CCHyper
 *
 *  @brief         Extended ObjectClass class.
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

#include "objectext.h"
#include "objecttype.h"


/**
 *  Class constructor.
 *  
 *  @author: CCHyper
 */
ObjectClassExtension::ObjectClassExtension(ObjectClass *this_ptr) :
    AbstractClassExtension(this_ptr)
{
}


/**
 *  Class no-init constructor.
 *  
 *  @author: CCHyper
 */
ObjectClassExtension::ObjectClassExtension(const NoInitClass &noinit) :
    AbstractClassExtension(noinit)
{
}


/**
 *  Class destructor.
 *  
 *  @author: CCHyper
 */
ObjectClassExtension::~ObjectClassExtension()
{
}


/**
 *  Initializes an object from the stream where it was saved previously.
 *  
 *  @author: CCHyper
 */
HRESULT ObjectClassExtension::Load(IStream *pStm)
{
    //EXT_DEBUG_TRACE("ObjectClassExtension::Size_Of - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    HRESULT hr = AbstractClassExtension::Load(pStm);
    if (FAILED(hr)) {
        return E_FAIL;
    }
    
    return hr;
}



/**
 *  Saves an object to the specified stream.
 *  
 *  @author: CCHyper
 */
HRESULT ObjectClassExtension::Save(IStream *pStm, BOOL fClearDirty)
{
    //EXT_DEBUG_TRACE("ObjectClassExtension::Size_Of - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    HRESULT hr = AbstractClassExtension::Save(pStm, fClearDirty);
    if (FAILED(hr)) {
        return hr;
    }

    return hr;
}


/**
 *  Removes the specified target from any targeting and reference trackers.
 *  
 *  @author: CCHyper
 */
void ObjectClassExtension::Detach(TARGET target, bool all)
{
    //EXT_DEBUG_TRACE("ObjectClassExtension::Detach - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


/**
 *  Compute a unique crc value for this instance.
 *  
 *  @author: CCHyper
 */
void ObjectClassExtension::Compute_CRC(WWCRCEngine &crc) const
{
    //EXT_DEBUG_TRACE("ObjectClassExtension::Compute_CRC - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


const char *ObjectClassExtension::Name() const
{
    //EXT_DEBUG_TRACE("ObjectClassExtension::Name - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    return reinterpret_cast<const ObjectClass *>(This())->Class_Of()->Name();
}


const char *ObjectClassExtension::Full_Name() const
{
    //EXT_DEBUG_TRACE("ObjectClassExtension::Full_Name - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    return reinterpret_cast<const ObjectClass *>(This())->Class_Of()->Full_Name();
}
