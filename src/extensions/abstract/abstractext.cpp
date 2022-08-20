/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          ABSTRACTEXT.CPP
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

#include "abstractext.h"
#include "tibsun_globals.h"
#include "swizzle.h"
#include "asserthandler.h"
#include "debughandler.h"


/**
 *  x
 * 
 *  @author: CCHyper
 */
AbstractClassExtension::AbstractClassExtension(AbstractClass *this_ptr) :
    ThisPtr(this_ptr)
{
    ASSERT(ThisPtr != nullptr);
}


/**
 *  x
 * 
 *  @author: CCHyper
 */
AbstractClassExtension::AbstractClassExtension(const NoInitClass &noinit)
{
}


/**
 *  x
 * 
 *  @author: CCHyper
 */
AbstractClassExtension::~AbstractClassExtension()
{
    ThisPtr = nullptr;
}


/**
 *  Loads the object from the stream and requests a new pointer to
 *  the class we extended post-load.
 * 
 *  @author: CCHyper
 */
HRESULT AbstractClassExtension::Load(IStream *pStm)
{
    LONG id;
    HRESULT hr = pStm->Read(&id, sizeof(id), nullptr);
    DEBUG_INFO("AbstractClassExtension Read ID 0x%08X\n", id);
    if (FAILED(hr)) {
        return E_FAIL;
    }

    AbstractClass *thisptr = ThisPtr;

    ULONG size = Size_Of();
    ASSERT_FATAL(size != 0, "Loading a empty extension, what the fuck\n");
    hr = pStm->Read(this, size, nullptr);
    if (FAILED(hr)) {
        return E_FAIL;
    }

    ThisPtr = thisptr;
    /**
     *  Announce ourself to the swizzle manager.
     */
    SWIZZLE_HERE_I_AM(id, this);

    /**
     *  Request the pointer to the base class be remapped.
     */
    //SWIZZLE_REQUEST_POINTER_REMAP(ThisPtr); //fails to remap

#ifndef NDEBUG
    //EXT_DEBUG_INFO("Ext Load: ID 0x%08X Ptr 0x%08X ThisPtr 0x%08X\n", id, this, ThisPtr);
#endif

    return S_OK;
}


/**
 *  Saves the object to the stream.
 * 
 *  @author: CCHyper
 */
HRESULT AbstractClassExtension::Save(IStream *pStm, BOOL fClearDirty)
{
    if (!pStm) {
        return E_POINTER;
    }

    LONG id;
    SWIZZLE_FETCH_POINTER_ID(this, &id);
    HRESULT hr = pStm->Write(&id, sizeof(id), nullptr);
    DEBUG_INFO("AbstractClassExtension Written ID 0x%08X\n", id);
    if (FAILED(hr)) {
        return E_FAIL;
    }

    ULONG size = Size_Of();
    ASSERT_FATAL(size != 0, "Saving a empty extension, what the fuck\n");
    hr = pStm->Write(this, size, nullptr);
    if (FAILED(hr)) {
        return E_FAIL;
    }
    
#ifndef NDEBUG
    //EXT_DEBUG_INFO("Ext Save: ID 0x%08X Ptr 0x%08X ThisPtr 0x%08X\n", id, this, ThisPtr);
#endif

    return S_OK;
}
