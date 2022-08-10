/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          TERRAINTYPEEXT.H
 *
 *  @author        CCHyper
 *
 *  @brief         Extended TerrainTypeClass class.
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

#include "objecttypeext.h"
#include "terraintype.h"


class TerrainTypeClassExtension final : public ObjectTypeClassExtension
{
    public:
        TerrainTypeClassExtension(TerrainTypeClass *this_ptr);
        TerrainTypeClassExtension(const NoInitClass &noinit);
        ~TerrainTypeClassExtension();

        virtual HRESULT Load(IStream *pStm) override;
        virtual HRESULT Save(IStream *pStm, BOOL fClearDirty) override;
        virtual int Size_Of() const override;

        virtual void Detach(TARGET target, bool all = true) override;
        virtual void Compute_CRC(WWCRCEngine &crc) const override;

        virtual bool Read_INI(CCINIClass &ini) override;

        virtual TerrainTypeClass *This() const override { return reinterpret_cast<TerrainTypeClass *>(ObjectTypeClassExtension::This()); }

        virtual ExtensionRTTIType What_Am_I() const override { return EXT_RTTI_TERRAINTYPE; }

    public:
        /**
         *  Does this terrain object emit light?
         */
        bool IsLightEnabled;

        /**
         *  This terrain object radiates this amount of light.
         */
        int LightVisibility;

        /**
         *  The distance (in leptons) that this light is visible from.
         */
        int LightIntensity;

        /**
         *  The red tint of this terrain objects light.
         */
        int LightRedTint;

        /**
         *  The green tint of this terrain objects light.
         */
        int LightGreenTint;

        /**
         *  The blue tint of this terrain objects light.
         */
        int LightBlueTint;
};
