/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          TACTICALEXT.CPP
 *
 *  @author        CCHyper
 *
 *  @brief         Extended Tactical class.
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
#include "tacticalext.h"
#include "tactical.h"
#include "wwcrc.h"
#include "vinifera_globals.h"
#include "tibsun_globals.h"
#include "colorscheme.h"
#include "rgb.h"
#include "wwfont.h"
#include "wwcrc.h"
#include "foot.h"
#include "unit.h"
#include "unittype.h"
#include "session.h"
#include "scenario.h"
#include "ebolt.h"
#include "house.h"
#include "housetype.h"
#include "super.h"
#include "superext.h"
#include "supertype.h"
#include "supertypeext.h"
#include "rules.h"
#include "rulesext.h"
#include "swizzle.h"
#include "vinifera_saveload.h"
#include "extension.h"
#include "asserthandler.h"
#include "debughandler.h"

#include "bsurface.h"
#include "drawshape.h"
#include "language.h"
#include "mouse.h"
#include "sidebar.h"
#include "spritecollection.h"
#include "tibsun_functions.h"
#include "vox.h"

int InstanceCount = 0;
/**
 *  Class constructor.
 *  
 *  @author: CCHyper
 */
TacticalExtension::TacticalExtension(const Tactical *this_ptr) :
    AbstractClassExtension(this_ptr, "TacticalExtension"),
    IsInfoTextSet(false),
    InfoTextBuffer(),
    InfoTextPosition(BOTTOM_LEFT),
    InfoTextNotifySound(VOC_NONE),
    InfoTextNotifySoundVolume(1.0f),
    InfoTextStyle(TPF_6PT_GRAD|TPF_DROPSHADOW),
    InfoTextTimer(0)
{
    //if (this_ptr) EXT_DEBUG_TRACE("TacticalExtension::TacticalExtension - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    TacticalMapExtension = this;
    InstanceCount++;
}


/**
 *  Class no-init constructor.
 *  
 *  @author: CCHyper
 */
TacticalExtension::TacticalExtension(const NoInitClass &noinit) :
    AbstractClassExtension(noinit),
    IsInfoTextSet(false),
    InfoTextTimer(noinit)
{
    //EXT_DEBUG_TRACE("TacticalExtension::TacticalExtension(NoInitClass) - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


/**
 *  Class destructor.
 *  
 *  @author: CCHyper
 */
TacticalExtension::~TacticalExtension()
{
    //EXT_DEBUG_TRACE("TacticalExtension::~TacticalExtension - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    TacticalMapExtension = nullptr;
    InstanceCount--;
}


/**
 *  Retrieves the class identifier (CLSID) of the object.
 *  
 *  @author: CCHyper
 */
HRESULT TacticalExtension::GetClassID(CLSID *lpClassID)
{
    //EXT_DEBUG_TRACE("TacticalExtension::GetClassID - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    if (lpClassID == nullptr) {
        return E_POINTER;
    }

    *lpClassID = __uuidof(this);

    return S_OK;
}


/**
 *  x
 *  
 *  @author: CCHyper
 */
HRESULT TacticalExtension::Load(IStream *pStm)
{
    //EXT_DEBUG_TRACE("TacticalExtension::Load - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    HRESULT hr = AbstractClassExtension::Internal_Load(pStm);
    if (FAILED(hr)) {
        return E_FAIL;
    }

    new (this) TacticalExtension(NoInitClass());
    
    return hr;
}


/**
 *  x
 *  
 *  @author: CCHyper
 */
HRESULT TacticalExtension::Save(IStream *pStm, BOOL fClearDirty)
{
    //EXT_DEBUG_TRACE("TacticalExtension::Save - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    HRESULT hr = AbstractClassExtension::Internal_Save(pStm, fClearDirty);
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
int TacticalExtension::Size_Of() const
{
    //EXT_DEBUG_TRACE("TacticalExtension::Size_Of - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    return sizeof(*this);
}


/**
 *  Removes the specified target from any targeting and reference trackers.
 *  
 *  @author: CCHyper
 */
void TacticalExtension::Detach(TARGET target, bool all)
{
    //EXT_DEBUG_TRACE("TacticalExtension::Detach - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


/**
 *  Compute a unique crc value for this instance.
 *  
 *  @author: CCHyper
 */
void TacticalExtension::Compute_CRC(WWCRCEngine &crc) const
{
    //EXT_DEBUG_TRACE("TacticalExtension::Compute_CRC - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


/**
 *  Draws the developer mode overlay.
 * 
 *  @authors: CCHyper
 */
void TacticalExtension::Draw_Debug_Overlay()
{
    RGBClass rgb_black(0,0,0);
    unsigned color_black = DSurface::RGB_To_Pixel(0, 0, 0);
    ColorScheme *text_color = ColorScheme::As_Pointer("White");

    int padding = 2;

    char buffer[256];
    std::snprintf(buffer, sizeof(buffer),
        "[%s] %3d %3d 0x%08X",
        strupr(Scen->ScenarioName),
        Session.DesiredFrameRate,
        FramesPerSecond,
        CurrentObjects.Count() == 1 ? CurrentObjects.Fetch_Head() : 0
    );

    /**
     * Fetch the text occupy area.
     */
    Rect text_rect;
    GradFont6Ptr->String_Pixel_Rect(buffer, &text_rect);

    /**
     *  Fill the background area.
     */
    Rect fill_rect;
    fill_rect.X = 160; // Width of Options tab, so we draw from there.
    fill_rect.Y = 0;
    fill_rect.Width = text_rect.Width+(padding+1);
    fill_rect.Height = 16; // Tab bar height
    CompositeSurface->Fill_Rect(fill_rect, color_black);

    /**
     *  Move rects into position.
     */
    text_rect.X = fill_rect.X+padding;
    text_rect.Y = 0;
    text_rect.Width += padding;
    text_rect.Height += 3;

    /**
     *  Draw the overlay text.
     */
    Fancy_Text_Print(buffer, CompositeSurface, &CompositeSurface->Get_Rect(),
        &Point2D(text_rect.X, text_rect.Y), text_color, COLOR_TBLACK, TextPrintType(TPF_6PT_GRAD|TPF_NOSHADOW));

    /**
     *  Draw the current frame number.
     */
    std::snprintf(buffer, sizeof(buffer), "%d", Frame);
    GradFont6Ptr->String_Pixel_Rect(buffer, &text_rect);

    fill_rect.Width = text_rect.Width+(padding+1);
    fill_rect.Height = 16;
    fill_rect.X = CompositeSurface->Get_Width()-fill_rect.Width;
    fill_rect.Y = 0;
    CompositeSurface->Fill_Rect(fill_rect, color_black);

    text_rect.X = CompositeSurface->Get_Width();
    text_rect.Y = 0;
    text_rect.Width += padding;
    text_rect.Height += 3;

    Fancy_Text_Print(buffer, CompositeSurface, &CompositeSurface->Get_Rect(),
        &Point2D(text_rect.X, text_rect.Y), text_color, COLOR_TBLACK, TextPrintType(TPF_RIGHT|TPF_6PT_GRAD|TPF_NOSHADOW));
}


#ifndef NDEBUG
/**
 *  Draws the current unit facing number.
 * 
 *  @author: CCHyper
 */
bool TacticalExtension::Debug_Draw_Facings()
{
    if (CurrentObjects.Count() != 1) {
        return false;
    }

    ObjectClass *object = CurrentObjects.Fetch_Head();
    if (object->What_Am_I() != RTTI_UNIT) {
        return false;
    }

    UnitClass *unit = reinterpret_cast<UnitClass *>(object);

    Point3D lept = unit->Class_Of()->Lepton_Dimensions();
    Point3D lept_center = Point3D(lept.X/2, lept.Y/2, lept.Z/2);

    Point3D pix = unit->Class_Of()->Pixel_Dimensions();
    Point3D pixel_center = Point3D(pix.X/2, pix.Y/2, pix.Z/2);

    Coordinate coord = unit->Center_Coord();

    Point2D screen = TacticalMap->func_60F150(coord);

    screen.X -= TacticalMap->field_5C.X;
    screen.Y -= TacticalMap->field_5C.Y;

    screen.X += TacticalRect.X;
    screen.Y += TacticalRect.Y;

    TempSurface->Fill_Rect(TacticalRect, Rect(screen.X, screen.Y, 2, 2), DSurface::RGB_To_Pixel(255,0,0));

    TextPrintType style = TPF_CENTER|TPF_FULLSHADOW|TPF_6POINT;
    WWFontClass *font = Font_Ptr(style);

    screen.Y -= font->Get_Char_Height()/2;

    char buffer1[32];
    char buffer2[32];

    std::snprintf(buffer1, sizeof(buffer1), "%d", unit->PrimaryFacing.Current().Get_Dir());
    std::snprintf(buffer2, sizeof(buffer2), "%d", unit->PrimaryFacing.Current().Get_Raw());

    Simple_Text_Print(buffer1, TempSurface, &TacticalRect, &screen, ColorScheme::As_Pointer("White"), style);

    screen.Y += 10;
    Simple_Text_Print(buffer2, TempSurface, &TacticalRect, &screen, ColorScheme::As_Pointer("White"), style);

    return true;
}
#endif


/**
 *  Draws the overlay for frame step mode.
 * 
 *  @authors: CCHyper
 */
void TacticalExtension::Draw_FrameStep_Overlay()
{
    RGBClass rgb_black(0,0,0);
    unsigned color_black = DSurface::RGB_To_Pixel(0, 0, 0);
    ColorScheme *text_color = ColorScheme::As_Pointer("White");

    int padding = 2;

    const char *text = "Frame Step Mode Enabled";

    /**
     * Fetch the text occupy area.
     */
    Rect text_rect;
    GradFont6Ptr->String_Pixel_Rect(text, &text_rect);

    /**
     *  Fill the background area.
     */
    Rect fill_rect;
    fill_rect.X = TacticalRect.X+TacticalRect.Width-text_rect.Width-(padding+1);
    fill_rect.Y = 16; // Tab bar height
    fill_rect.Width = text_rect.Width+(padding+1);
    fill_rect.Height = 16;
    CompositeSurface->Fill_Rect(fill_rect, color_black);

    /**
     *  Move rects into position.
     */
    text_rect.X = TacticalRect.X+TacticalRect.Width-1;
    text_rect.Y = fill_rect.Y;
    text_rect.Width += padding;
    text_rect.Height += 3;

    /**
     *  Draw the overlay text.
     */
    Fancy_Text_Print(text, CompositeSurface, &CompositeSurface->Get_Rect(),
        &Point2D(text_rect.X, text_rect.Y), text_color, COLOR_TBLACK, TextPrintType(TPF_RIGHT|TPF_6PT_GRAD|TPF_NOSHADOW));
}


/**
 *  Draw the overlay information text if set.
 * 
 *  @author: CCHyper
 */
void TacticalExtension::Draw_Information_Text()
{
    RGBClass rgb_black(0,0,0);
    unsigned color_black = DSurface::RGB_To_Pixel(0, 0, 0);
    ColorScheme *text_color = ColorScheme::As_Pointer("White");

    int padding = 2;

    const char *text = InfoTextBuffer.Peek_Buffer();
    if (!text) {
        return;
    }

    /**
     * Fetch the text occupy area.
     */
    Rect text_rect;
    GradFont6Ptr->String_Pixel_Rect(text, &text_rect);

    Rect fill_rect;

    TextPrintType style = InfoTextStyle;
    int pos_x = 0;
    int pos_y = 0;

    switch (InfoTextPosition) {

        default:
        case InfoTextPosType::TOP_LEFT:
            pos_x = TacticalRect.X;
            pos_y = TacticalRect.Y;
            
            /**
             *  Move rects into position.
             */
            fill_rect.X = pos_x;
            fill_rect.Y = pos_y;
            fill_rect.Width = text_rect.Width+(padding+1)+2;
            fill_rect.Height = text_rect.Height+1;

            text_rect.X = fill_rect.X+2;
            text_rect.Y = fill_rect.Y;
            text_rect.Width += padding;
            text_rect.Height += 3;

            break;

        case InfoTextPosType::TOP_RIGHT:
            pos_x = TacticalRect.X+TacticalRect.Width-text_rect.Width;
            pos_y = TacticalRect.Y;
            
            /**
             *  Move rects into position.
             */
            fill_rect.X = pos_x-5;
            fill_rect.Y = pos_y;
            fill_rect.Width = TacticalRect.X+TacticalRect.Width-text_rect.Width+3;
            fill_rect.Height = text_rect.Height+1;

            text_rect.X = TacticalRect.X+TacticalRect.Width-2;
            text_rect.Y = fill_rect.Y;
            text_rect.Width += padding;
            text_rect.Height += 3;

            style |= TPF_RIGHT;
            break;

        case InfoTextPosType::BOTTOM_LEFT:
            pos_x = 0;
            pos_y = TacticalRect.Y+TacticalRect.Height-text_rect.Height;
            
            /**
             *  Move rects into position.
             */
            fill_rect.X = pos_x;
            fill_rect.Y = pos_y;
            fill_rect.Width = text_rect.Width+(padding+1)+2;
            fill_rect.Height = text_rect.Height+1;

            text_rect.X = fill_rect.X+2;
            text_rect.Y = fill_rect.Y;
            text_rect.Width += padding;
            text_rect.Height += 3;

            break;

        case InfoTextPosType::BOTTOM_RIGHT:
            pos_x = TacticalRect.X+TacticalRect.Width-text_rect.Width;
            pos_y = TacticalRect.Y+TacticalRect.Height-text_rect.Height;

            /**
             *  Move rects into position.
             */
            fill_rect.X = pos_x-5;
            fill_rect.Y = pos_y;
            fill_rect.Width = TacticalRect.X+TacticalRect.Width-text_rect.Width+3;
            fill_rect.Height = text_rect.Height+1;

            text_rect.X = TacticalRect.X+TacticalRect.Width-2;
            text_rect.Y = fill_rect.Y;
            text_rect.Width += padding;
            text_rect.Height += 3;

            style |= TPF_RIGHT;

            break;

    };

    /**
     *  Fill the background area.
     */
    CompositeSurface->Fill_Rect_Trans(fill_rect, rgb_black, 50);

    /**
     *  Draw the overlay text.
     */
    Fancy_Text_Print(text, CompositeSurface, &CompositeSurface->Get_Rect(),
        &Point2D(text_rect.X, text_rect.Y), text_color, COLOR_TBLACK, style);
}

#define MAX_VISIBLE 8
enum
{
    OBJECT_HEIGHT = 24,				// Pixel height of each buildable object.
    OBJECT_WIDTH = 32,				// Pixel width of each buildable object.
    RESFACTOR = 2,
    BUTTON_SELECT = 2220,

};

bool Needs_Redrawing(SuperClass *sup)
{
    if (sup->Class->IsUseChargeDrain) {
        return true;
    }
    return sup->IsReady == 0;
}

const ShapeFileStruct *&RechargeClockShape = Make_Global<const ShapeFileStruct *>(0x0080B6D0);
const ShapeFileStruct *&ClockShape = Make_Global<const ShapeFileStruct *>(0x0080C23C);

DEFINE_IMPLEMENTATION(void Print_Cameo_Text(char *string, Point2D &a2, Rect &rect1, int max_width), 0x005F66E0);

class SuperBGadgetClass : public GadgetClass {
public:
    SuperBGadgetClass() : GadgetClass(0, 0, 1, 1, LEFTUP) {}
protected:
    virtual bool Draw_Me(bool forced = false) override;
    virtual bool Action(unsigned flags, KeyNumType &key) override;
};

//for debugging positions
bool SuperBGadgetClass::Draw_Me(bool forced)
{
    Rect rect;
    rect.X = X; // Width of Options tab, so we draw from there.
    rect.Y = Y;
    rect.Width = Width;
    rect.Height = Height; // Tab bar height
    CompositeSurface->Draw_Rect(rect, DSurface::RGB_To_Pixel(255,0,255));

    return GadgetClass::Draw_Me(forced);
}

bool SuperBGadgetClass::Action(unsigned, KeyNumType &)
{
    DEBUG_INFO("SuperBGadgetClass Action\n");
    Map.Override_Mouse_Shape(MOUSE_NORMAL, false);
    return(true);
}

SuperBGadgetClass SuperBackground;

class SuperSelectClass : public ControlClass
{
public:
    SuperSelectClass();
    SuperSelectClass(NoInitClass const &x) : ControlClass(x) {};

    virtual bool Draw_Me(bool forced = false) override;
    virtual bool Action(unsigned flags, KeyNumType &key) override;

    void Set_Owner(int index);

public:
    int Index;
};

DynamicVectorClass<int> SuperIndexes;

#include "event.h"
SuperSelectClass SelectButton[MAX_VISIBLE];

SuperSelectClass::SuperSelectClass() :
    ControlClass(0, 0, 0, (OBJECT_WIDTH - 1) *RESFACTOR, (OBJECT_HEIGHT - 1) *RESFACTOR, LEFTPRESS | RIGHTPRESS | LEFTUP),
    Index(0)
{
}
//for debugging positions
bool SuperSelectClass::Draw_Me(bool forced)
{
    //Rect rect;
    //rect.X = X; // Width of Options tab, so we draw from there.
    //rect.Y = Y;
    //rect.Width = Width;
    //rect.Height = Height; // Tab bar height
    //CompositeSurface->Draw_Rect(rect, 0);

    return ControlClass::Draw_Me(forced);
}
int IgnoreMouse;

bool SuperSelectClass::Action(unsigned flags, KeyNumType &key)
{
    DEBUG_INFO("Super Select Action\n");
    int index = Index;
    int oid = SuperIndexes[index];

    SpecialWeaponType spc = SPECIAL_NONE;

    Map.Override_Mouse_Shape(MOUSE_NORMAL);

    if (index < SuperIndexes.Count()) {
            spc = SpecialWeaponType(oid);
            DEBUG_INFO("Super Select Action Index Check\n");
    }

    if (spc != SPECIAL_NONE) {
        
        if (flags & LEFTUP) {
            DEBUG_INFO("Super Select Action Index LEFTUP Frame %d\n", Frame);
            //Map.Help_Text(SpecialWeaponHelp[spc]);
            flags &= ~LEFTUP;
            IgnoreMouse = Frame;
        }

        if (flags & RIGHTPRESS) {
            DEBUG_INFO("Super Select Action Index RIGHTPRESS Frame %d\n", Frame);
            Map.TargettingType = SPECIAL_NONE;
            IgnoreMouse = Frame;
        }

        if (flags & LEFTPRESS) {
            DEBUG_INFO("Super Select Action Index LEFTPRESS Frame %d\n", Frame);
            if ((unsigned)spc < SuperWeaponTypes.Count()) {
                SuperClass *super = PlayerPtr->SuperWeapon[spc];

                if (super->Is_Ready()) {
                    if (!super->Class->Action) {
                        Cell cell = 0;
                        OutList.Add(EventClass(PlayerPtr->ID, EventType::SPECIAL_PLACE, super->Class->Type, &cell));
                    }

                    Map.TargettingType = spc;
                    Unselect_All();
                    Speak(VOX_SELECT_TARGET);
                } else {
                    PlayerPtr->SuperWeapon[spc]->Impatient_Click();
                }
            }
            IgnoreMouse = Frame + 4;
        }
       
    }

    key = KN_NONE;
    ControlClass::Action(flags, key);
    return(true);
}

void SuperSelectClass::Set_Owner(int index)
{
    Index = index;
}

int SX = 5;
int SY = 30;


bool once = false;
void Draw_Superweapons()
{
   // SuperIndexes.Clear();

    if (!once){


        SuperBackground.Set_Position(SX, SY);
        SuperBackground.Set_Size(OBJECT_WIDTH * RESFACTOR, OBJECT_HEIGHT * RESFACTOR * 8);
        SuperBackground.Zap();
        Map.Add_A_Button(SuperBackground);

        //Activate
        for (int index = 0; index < MAX_VISIBLE; index++) {
            SelectButton[index].Zap();
            Map.Add_A_Button(SelectButton[index]);
        }

        //Init_IO
        for (int index = 0; index < MAX_VISIBLE; index++) {
            SuperSelectClass &g = SelectButton[index];
            g.ID = BUTTON_SELECT;
            g.X = SX;
            g.Y = ((OBJECT_HEIGHT * index) * RESFACTOR) + SY;
            g.Width = OBJECT_WIDTH * RESFACTOR;
            g.Height = OBJECT_HEIGHT * RESFACTOR;
            g.Set_Owner(index);
        }

        for (int j = 0; j < 75; ++j) {
            auto &b = Map.Column[1].Buildables[j];
            if (b.BuildableType == RTTI_SPECIAL) {
                SuperIndexes.Add(b.BuildableID);
            }
        }


        once = true;
    }

    for (int i = 0; i < SuperIndexes.Count(); ++i) {
        if (i >= 8) {
            break;
        }

        int index = SuperIndexes[i];
        if (index < SuperWeaponTypes.Count()) {
            SuperClass *sup = PlayerPtr->SuperWeapon[index];



            auto *shape = sup->Class->SidebarIcon;
            BSurface *image_surface = nullptr;
            auto *supertypeext = Extension::Fetch<SuperWeaponTypeClassExtension>(sup->Class);
            if (supertypeext->CameoImageSurface) {
                image_surface = supertypeext->CameoImageSurface;
            }

            bool not_redrawing = Needs_Redrawing(sup) == 0;
            bool  isready = sup->Is_Ready();
            const char *statestr = sup->Ready_String();
            int animstage = sup->Anim_Stage();

            char *string = sup->Class->FullName;

            Point2D pt(SelectButton[i].X, SelectButton[i].Y);
            Rect rect;
            rect.X = 0;
            rect.Y = 0;//SidebarRect.Y;
            rect.Width = SidebarRect.Width;
            rect.Height = SidebarRect.Height;

            /**
             *  Draw the cameo pcx image.
             */
            if (image_surface) {
                Rect pcxrect;
                pcxrect.X = rect.X + pt.X;
                pcxrect.Y = rect.Y + pt.Y;
                pcxrect.Width = image_surface->Get_Width();
                pcxrect.Height = image_surface->Get_Height();

                SpriteCollection.Draw(pcxrect, *CompositeSurface, *image_surface);
            } else {
                CC_Draw_Shape(CompositeSurface, CameoDrawer, shape, 0, &pt, &rect);
            }

            if (string) {
                auto *sbs = SidebarSurface;
                SidebarSurface = CompositeSurface;
                Point2D a2;
                a2.Y = pt.Y + 41;
                a2.X = pt.X;
                Print_Cameo_Text(string, a2, rect, 62);
                SidebarSurface = sbs;
            }


            if (statestr) {

                Point2D spt = pt;
                spt.X = pt.X + 30;
                spt.Y = pt.Y + 2;
                ColorScheme *color = ColorScheme::As_Pointer("LightBlue", 1);
                Fancy_Text_Print(statestr, CompositeSurface, &rect, &spt, color, 0, TPF_CENTER | TPF_FULLSHADOW | TPF_8POINT);
            }

            if (!not_redrawing) {
                if (isready) {
                    CC_Draw_Shape(CompositeSurface, SidebarDrawer, RechargeClockShape, animstage + 1, &pt, &rect, (SHAPE_400 | SHAPE_TRANS50));
                } else {
                    CC_Draw_Shape(CompositeSurface, SidebarDrawer, ClockShape, animstage + 1, &pt, &rect, (SHAPE_400 | SHAPE_TRANS50));
                }

            }

        } else {
            break;
        }

    }


    //Deactivate
    //for (int i = 0; i < MAX_VISIBLE; ++i) {
    //    Map.Remove_A_Button(SelectButton[i]);
    //}

    //SuperIndexes.Clear();
}
/**
 *  For drawing any new post-effects/systems.
 * 
 *  @authors: CCHyper
 */
void TacticalExtension::Render_Post()
{
    //EXT_DEBUG_TRACE("TacticalExtension::Render_Post - 0x%08X\n", (uintptr_t)(This()));

    /**
     *  Draw any new post effects here.
     */
    //DEV_DEBUG_INFO("Before EBoltClass::Draw_All\n");
    EBoltClass::Draw_All();
    //DEV_DEBUG_INFO("After EBoltClass::Draw_All\n");

    /**
     *  Draw any overlay text.
     */
    Draw_Super_Timers();

    if (GameActive && Frame > 2) {
        Draw_Superweapons();
    }
}


/**
 *  Prints a single super weapon timer to the tactical screen.
 * 
 *  @authors: CCHyper
 */
void TacticalExtension::Super_Draw_Timer(int row_index, ColorScheme *color, int time, const char *name, unsigned long *flash_time, bool *flash_state)
{
    static WWFontClass *_font = nullptr;

    TextPrintType style = TPF_8POINT|TPF_RIGHT|TPF_NOSHADOW|TPF_METAL12|TPF_SOLIDBLACK_BG;

    if (!_font) {
        _font = Font_Ptr(style);
    }

    char fullbuff[128];
    char namebuff[128];
    char timerbuff[128];
    int text_width = -1;
    int flash_delay = 500; // was 1000
    bool to_flash = false;
    unsigned color_black = DSurface::RGB_To_Pixel(0, 0, 0);
    RGBClass rgb_black(0, 0, 0);
    ColorScheme *white_color = ColorScheme::As_Pointer("White", 1);
    int background_tint = 50;

    long hours = (time / 60 / 60);
    long seconds = (time % 60);
    long minutes = (time / 60 % 60);

    if (hours) {
        std::snprintf(fullbuff, sizeof(fullbuff), "%s %d:%02d:%02d", name, hours, minutes, seconds);
        std::snprintf(namebuff, sizeof(namebuff), "%s", name);
        std::snprintf(timerbuff, sizeof(timerbuff), "%d:%02d:%02d", hours, minutes, seconds);
    } else {
        std::snprintf(fullbuff, sizeof(fullbuff), "%s %02d:%02d", name, minutes, seconds);
        std::snprintf(namebuff, sizeof(namebuff), "%s", name);
        std::snprintf(timerbuff, sizeof(timerbuff), "%02d:%02d", minutes, seconds);
    }

    /**
     *  Is it time to flash
     */
    if (!time) {
        if (flash_time && flash_state) {
            if (timeGetTime() >= *flash_time) {
                *flash_time = timeGetTime() + flash_delay;
                *flash_state = !*flash_state;
            }
            to_flash = *flash_state;
        }
    }

    Rect name_rect;
    _font->String_Pixel_Rect(namebuff, &name_rect);

    Rect timer_rect;
    _font->String_Pixel_Rect(timerbuff, &timer_rect);

    int font_width = _font->Get_Font_Width();
    int font_height = _font->Get_Font_Height();

    int y_pos = TacticalRect.Height - (row_index * (font_height + 2)) + 3;

    Point2D timer_point;
    timer_point.X = TacticalRect.Width - 4;
    timer_point.Y = y_pos;

    int x_offset = hours ? 56 : 38; // timer_rect.Width

    Point2D name_point;
    name_point.X = TacticalRect.Width - x_offset - 3;
    name_point.Y = y_pos;

    Rect fill_rect;
    fill_rect.X = TacticalRect.Width - (x_offset + name_rect.Width) - 4;
    fill_rect.Y = y_pos-1;
    fill_rect.Width = x_offset + name_rect.Width + 2;
    fill_rect.Height = timer_rect.Height + 2;

    //CompositeSurface->Fill_Rect(CompositeSurface->Get_Rect(), fill_rect, color_black);
    CompositeSurface->Fill_Rect_Trans(fill_rect, rgb_black, background_tint);

    Fancy_Text_Print(timerbuff, CompositeSurface, &CompositeSurface->Get_Rect(), 
        &timer_point, to_flash ? white_color : color, COLOR_TBLACK, style);

    Fancy_Text_Print(namebuff, CompositeSurface, &CompositeSurface->Get_Rect(), 
        &name_point, color, COLOR_TBLACK, style);
}


/**
 *  Draws super weapon timers to the tactical screen.
 * 
 *  @authors: CCHyper
 */
void TacticalExtension::Draw_Super_Timers()
{
    //EXT_DEBUG_TRACE("TacticalExtension::Draw_Super_Timers - 0x%08X\n", (uintptr_t)(This()));

    /**
     *  Super weapon timers are for multiplayer only.
     */
#if 0
    if (Session.Type == GAME_NORMAL) {
        return;
    }
#endif

    /**
     *  Does the game rules state that the super weapon timers should be shown?
     */
    if (!RuleExtension->IsShowSuperWeaponTimers) {
        return;
    }

    /**
     *  Has the user toggled the visibility of the super weapon timers?
     */
    if (!Vinifera_ShowSuperWeaponTimers) {
        return;
    }

    /**
     *  Non-release builds print the version information to the tactical view
     *  so we need to adjust the timers to print above this text.
     */
#ifdef RELEASE
    int row_index = 0;
#else
    int row_index = 3;
#endif

    /**
     *  Iterate over all active super weapons and print their recharge timers.
     */
    for (int i = 0; i < Supers.Count(); ++i) {

        SuperClass *super = Supers[i];
        SuperClassExtension *superext = Extension::Fetch<SuperClassExtension>(super);
        SuperWeaponTypeClassExtension *supertypeext = Extension::Fetch<SuperWeaponTypeClassExtension>(super->Class);

        /**
         *  Should we show the recharge timer for this super?
         */
        if (!supertypeext->IsShowTimer) {
            continue;
        }

        if (super->House->Class->IsMultiplayPassive) {
            continue;
        }

        /**
         *  Skip supers that are disabled.
         */
        if (!super->IsPresent) {
            continue;
        }

        if (super->Control.Value() != super->Class->RechargeTime) {

            Super_Draw_Timer(
                row_index++,
                ColorSchemes[super->House->RemapColor],
                super->Control.Value() / TICKS_PER_SECOND,
                super->Class->FullName,
                &superext->FlashTimeEnd,
                &superext->TimerFlashState
            );
        }

    }
}