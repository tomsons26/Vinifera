/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          BUILDINGEXT.H
 *
 *  @author        CCHyper
 *
 *  @brief         Extended AnimClass class.
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
#include "anim.h"


class AnimClass;
class HouseClass;


class DECLSPEC_UUID(UUID_ANIM_EXTENSION)
AnimClassExtension final : public ObjectClassExtension
{
    public:
        /**
         *  IPersist
         */
        IFACEMETHOD(GetClassID)(CLSID *pClassID);

        /**
         *  IPersistStream
         */
        IFACEMETHOD(Load)(IStream *pStm);
        IFACEMETHOD(Save)(IStream *pStm, BOOL fClearDirty);

    public:
        AnimClassExtension(const AnimClass *this_ptr = nullptr);
        AnimClassExtension(const NoInitClass &noinit);
        virtual ~AnimClassExtension();

        virtual int Size_Of() const override;
        virtual void Detach(TARGET target, bool all = true) override;
        virtual void Compute_CRC(WWCRCEngine &crc) const override;

        virtual AnimClass *This() const override { return reinterpret_cast<AnimClass *>(ObjectClassExtension::This()); }
        virtual const AnimClass *This_Const() const override { return reinterpret_cast<const AnimClass *>(ObjectClassExtension::This_Const()); }
        virtual ExtensionRTTIType What_Am_I() const override { return EXT_RTTI_ANIM; }

    public:
};
