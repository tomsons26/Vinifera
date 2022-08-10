/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          ABSTRACTTYPEEXT.H
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


class AbstractTypeClass;
class CCINIClass;


class AbstractTypeClassExtension : public AbstractClassExtension
{
    public:
        AbstractTypeClassExtension(AbstractTypeClass *this_ptr);
        AbstractTypeClassExtension(const NoInitClass &noinit);
        virtual ~AbstractTypeClassExtension();

        virtual bool Read_INI(CCINIClass &ini);

        virtual const char *Name() const override;
        virtual const char *Full_Name() const override;

    private:
        AbstractTypeClassExtension(const AbstractTypeClassExtension &) = delete;
        void operator = (const AbstractTypeClassExtension &) = delete;

    public:
};
