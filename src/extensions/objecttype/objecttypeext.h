/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          OBJECTTYPEEXT.H
 *
 *  @author        CCHyper
 *
 *  @brief         Extended ObjectTypeClass class.
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
#include "objecttype.h"


class ObjectTypeClassExtension : public AbstractTypeClassExtension
{
    public:
        ObjectTypeClassExtension(ObjectTypeClass *this_ptr);
        ObjectTypeClassExtension(const NoInitClass &noinit);
        ~ObjectTypeClassExtension();

        virtual HRESULT Load(IStream *pStm) override;
        virtual HRESULT Save(IStream *pStm, BOOL fClearDirty) override;

        virtual void Detach(TARGET target, bool all = true) override;
        virtual void Compute_CRC(WWCRCEngine &crc) const override;

        virtual ObjectTypeClass *This() const override { return reinterpret_cast<ObjectTypeClass *>(AbstractTypeClassExtension::This()); }

        virtual const char *Name() const override { return reinterpret_cast<const ObjectTypeClass *>(This())->Name(); }
        virtual const char *Full_Name() const override { return reinterpret_cast<const ObjectTypeClass *>(This())->Full_Name(); }

        virtual const char *Graphic_Name() const { return reinterpret_cast<const ObjectTypeClass *>(This())->Name(); }
        virtual const char *Alpha_Graphic_Name() const { return reinterpret_cast<const ObjectTypeClass *>(This())->Full_Name(); }

        virtual bool Read_INI(CCINIClass &ini) override;

    public:
};
