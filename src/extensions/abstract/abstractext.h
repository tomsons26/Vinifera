/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          ABSTRACTEXT.H
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

#include "always.h"
#include "tibsun_defines.h"
#include "noinit.h"

#include <objidl.h> // for IStream.


class AbstractClass;
class WWCRCEngine;


/**
 *  
 */
typedef enum ExtensionRTTIType : char
{
    EXT_RTTI_NONE = -1,

    EXT_RTTI_AIRCRAFT = 0,
    EXT_RTTI_AIRCRAFTTYPE,
    EXT_RTTI_ANIM,
    EXT_RTTI_ANIMTYPE,
    EXT_RTTI_BUILDING,
    EXT_RTTI_BUILDINGTYPE,
    EXT_RTTI_BULLETTYPE,
    EXT_RTTI_CAMPAIGN,
    EXT_RTTI_SIDE,
    EXT_RTTI_HOUSE,
    EXT_RTTI_HOUSETYPE,
    EXT_RTTI_INFANTRY,
    EXT_RTTI_INFANTRYTYPE,
    EXT_RTTI_ISOTILETYPE,
    EXT_RTTI_OVERLAYTYPE,
    EXT_RTTI_PARTICLESYSTEMTYPE,
    EXT_RTTI_PARTICLETYPE,
    EXT_RTTI_SMUDGETYPE,
    EXT_RTTI_SUPER,
    EXT_RTTI_SUPERWEAPONTYPE,
    EXT_RTTI_TERRAIN,
    EXT_RTTI_TERRAINTYPE,
    EXT_RTTI_TIBERIUM,
    EXT_RTTI_UNIT,
    EXT_RTTI_UNITTYPE,
    EXT_RTTI_VOXELANIMTYPE,
    EXT_RTTI_WARHEADTYPE,
    EXT_RTTI_WAVE,
    EXT_RTTI_WEAPONTYPE,

    EXT_RTTI_COUNT
};


/**
 *  x
 */
class AbstractClassExtension
{
    public:
        AbstractClassExtension(AbstractClass *this_ptr);
        AbstractClassExtension(const NoInitClass &noinit);
        virtual ~AbstractClassExtension();

        /**
         *  Initializes an object from the stream where it was saved previously.
         */
        virtual HRESULT Load(IStream *pStm);

        /**
         *  Saves an object to the specified stream.
         */
        virtual HRESULT Save(IStream *pStm, BOOL fClearDirty);

        /**
         *  Return the raw size of class data for save/load purposes.
         *  
         *  @note: This must be overridden by the extended class!
         */
        virtual int Size_Of() const = 0;

        /**
         *  Removes the specified target from any targeting and reference trackers.
         *  
         *  @note: This must be overridden by the extended class!
         */
        virtual void Detach(TARGET target, bool all = true) = 0;

        /**
         *  Compute a unique crc value for this instance.
         *  
         *  @note: This must be overridden by the extended class!
         */
        virtual void Compute_CRC(WWCRCEngine &crc) const = 0;

        /**
         *  Access to the class instance we extend.
         */
        virtual AbstractClass *This() const { return ThisPtr; }

        /**
         *  Access to the extended class instance.
         */
        virtual ExtensionRTTIType What_Am_I() const = 0;

        /**
         *  x
         */
        virtual const char *Name() const = 0;

        /**
         *  x
         */
        virtual const char *Full_Name() const = 0;

    private:
        /**
         *  x
         */
        AbstractClass *ThisPtr;

    private:
        AbstractClassExtension(const AbstractClassExtension &) = delete;
        void operator = (const AbstractClassExtension &) = delete;

    public:
};
