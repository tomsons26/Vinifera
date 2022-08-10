/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          INFANTRYEXT.H
 *
 *  @author        CCHyper
 *
 *  @brief         Extended InfantryClass class.
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

#include "footext.h"
#include "infantry.h"


class InfantryClass;
class HouseClass;


class InfantryClassExtension final : public FootClassExtension
{
    public:
        InfantryClassExtension(InfantryClass *this_ptr);
        InfantryClassExtension(const NoInitClass &noinit);
        ~InfantryClassExtension();

        virtual HRESULT Load(IStream *pStm) override;
        virtual HRESULT Save(IStream *pStm, BOOL fClearDirty) override;
        virtual int Size_Of() const override;

        virtual void Detach(TARGET target, bool all = true) override;
        virtual void Compute_CRC(WWCRCEngine &crc) const override;

        virtual InfantryClass *This() const override { return reinterpret_cast<InfantryClass *>(FootClassExtension::This()); }

        virtual ExtensionRTTIType What_Am_I() const override { return EXT_RTTI_INFANTRY; }

    public:
};
