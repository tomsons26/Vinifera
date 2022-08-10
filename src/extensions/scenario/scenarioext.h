/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          SCENARIOEXT.H
 *
 *  @author        CCHyper
 *
 *  @brief         Extended ScenarioClass class.
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
#include <objidl.h>


class ScenarioClass;
class NoInitClass;
class WWCRCEngine;


class ScenarioClassExtension final
{
    public:
        ScenarioClassExtension(ScenarioClass *this_ptr);
        ScenarioClassExtension(const NoInitClass &noinit);
        ~ScenarioClassExtension();

        HRESULT Load(IStream *pStm);
        HRESULT Save(IStream *pStm, BOOL fClearDirty);
        int Size_Of() const;
        void Compute_CRC(WWCRCEngine &crc) const;

        void Init_Clear();

    public:

};


/**
 *  Global instance of the extended class.
 */
extern ScenarioClassExtension *ScenarioExtension;
