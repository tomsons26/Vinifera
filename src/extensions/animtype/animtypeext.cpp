/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          ANIMTYPEEXT.CPP
 *
 *  @author        CCHyper
 *
 *  @brief         Extended AnimTypeClass class.
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
#include "animtypeext.h"
#include "animtype.h"
#include "ccini.h"
#include "wwcrc.h"
#include "extension.h"
#include "asserthandler.h"
#include "debughandler.h"


/**
 *  Class constructor.
 *  
 *  @author: CCHyper
 */
AnimTypeClassExtension::AnimTypeClassExtension(AnimTypeClass *this_ptr) :
    ObjectTypeClassExtension(this_ptr),
    IsHideIfNotTiberium(false),
    IsForceBigCraters(false),
    ZAdjust(0),
    AttachLayer(LAYER_NONE),
    ParticleToSpawn(PARTICLE_NONE),
    NumberOfParticles(0)
{
    //EXT_DEBUG_TRACE("AnimTypeClassExtension constructor - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


/**
 *  Class no-init constructor.
 *  
 *  @author: CCHyper
 */
AnimTypeClassExtension::AnimTypeClassExtension(const NoInitClass &noinit) :
    ObjectTypeClassExtension(noinit)
{
}


/**
 *  Class destructor.
 *  
 *  @author: CCHyper
 */
AnimTypeClassExtension::~AnimTypeClassExtension()
{
    //EXT_DEBUG_TRACE("AnimTypeClassExtension destructor - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


/**
 *  Initializes an object from the stream where it was saved previously.
 *  
 *  @author: CCHyper
 */
HRESULT AnimTypeClassExtension::Load(IStream *pStm)
{
    //EXT_DEBUG_TRACE("AnimTypeClassExtension::Size_Of - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    HRESULT hr = ObjectTypeClassExtension::Load(pStm);
    if (FAILED(hr)) {
        return E_FAIL;
    }

    new (this) AnimTypeClassExtension(NoInitClass());
    
    return hr;
}


/**
 *  Saves an object to the specified stream.
 *  
 *  @author: CCHyper
 */
HRESULT AnimTypeClassExtension::Save(IStream *pStm, BOOL fClearDirty)
{
    //EXT_DEBUG_TRACE("AnimTypeClassExtension::Size_Of - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    HRESULT hr = ObjectTypeClassExtension::Save(pStm, fClearDirty);
    if (FAILED(hr)) {
        return hr;
    }

    return hr;
}


/**
 *  Return the raw size of class data for save/load purposes.
 *  
 *  @author: CCHyper
 */
int AnimTypeClassExtension::Size_Of() const
{
    //EXT_DEBUG_TRACE("AnimTypeClassExtension::Size_Of - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    return sizeof(*this);
}


/**
 *  Removes the specified target from any targeting and reference trackers.
 *  
 *  @author: CCHyper
 */
void AnimTypeClassExtension::Detach(TARGET target, bool all)
{
    //EXT_DEBUG_TRACE("AnimTypeClassExtension::Detach - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


/**
 *  Compute a unique crc value for this instance.
 *  
 *  @author: CCHyper
 */
void AnimTypeClassExtension::Compute_CRC(WWCRCEngine &crc) const
{
    //EXT_DEBUG_TRACE("AnimTypeClassExtension::Compute_CRC - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    crc(AttachLayer);
    crc(NumberOfParticles);
}


/**
 *  Fetches the extension data from the INI database.  
 *  
 *  @author: CCHyper
 */
bool AnimTypeClassExtension::Read_INI(CCINIClass &ini)
{
    //EXT_DEBUG_TRACE("AnimTypeClassExtension::Read_INI - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    if (!ObjectTypeClassExtension::Read_INI(ini)) {
        return false;
    }

    const char *ini_name = Name();

    /**
     *  #issue-646
     * 
     *  Some animations in the vanilla game have a DetailLevel of 3, which is out
     *  of range and as a result do not play in-game. This makes sure the values
     *  are never outside of the expected range.
     */
    This()->DetailLevel = std::clamp(This()->DetailLevel, 0, 2);

    IsHideIfNotTiberium = ini.Get_Bool(ini_name, "HideIfNoTiberium", IsHideIfNotTiberium);
    IsForceBigCraters = ini.Get_Bool(ini_name, "ForceBigCraters", IsForceBigCraters);
    ZAdjust = ini.Get_Int(ini_name, "ZAdjust", ZAdjust);
    AttachLayer = ini.Get_LayerType(ini_name, "Layer", AttachLayer);
    ParticleToSpawn = ini.Get_ParticleType(ini_name, "SpawnsParticle", ParticleToSpawn);
    NumberOfParticles = ini.Get_Int(ini_name, "NumParticles", NumberOfParticles);
    
    return true;
}
