/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          TIBERIUMEXT.CPP
 *
 *  @author        CCHyper
 *
 *  @brief         Extended TiberiumClass class.
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
#include "tiberiumext.h"
#include "tiberium.h"
#include "ccini.h"
#include "extension.h"
#include "asserthandler.h"
#include "debughandler.h"
#include "map.h"
#include "mouse.h"
#include "tibsun_globals.h"


 /**
   *  Class constructor.
   *
   *  @author: CCHyper
   */
TiberiumClassExtension::TiberiumClassExtension(const TiberiumClass *this_ptr) :
    AbstractTypeClassExtension(this_ptr)
{
    //if (this_ptr) EXT_DEBUG_TRACE("TiberiumClassExtension::TiberiumClassExtension - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    TiberiumExtensions.Add(this);
}


/**
 *  Class no-init constructor.
 *
 *  @author: CCHyper
 */
TiberiumClassExtension::TiberiumClassExtension(const NoInitClass &noinit) :
    AbstractTypeClassExtension(noinit)
{
    //EXT_DEBUG_TRACE("TiberiumClassExtension::TiberiumClassExtension(NoInitClass) - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


/**
 *  Class destructor.
 *
 *  @author: CCHyper
 */
TiberiumClassExtension::~TiberiumClassExtension()
{
    //EXT_DEBUG_TRACE("TiberiumClassExtension::~TiberiumClassExtension - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    TiberiumExtensions.Delete(this);
}


/**
 *  Retrieves the class identifier (CLSID) of the object.
 *
 *  @author: CCHyper
 */
HRESULT TiberiumClassExtension::GetClassID(CLSID *lpClassID)
{
    //EXT_DEBUG_TRACE("TiberiumClassExtension::GetClassID - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    if (lpClassID == nullptr) {
        return E_POINTER;
    }

    *lpClassID = __uuidof(this);

    return S_OK;
}


/**
 *  Initializes an object from the stream where it was saved previously.
 *
 *  @author: CCHyper
 */
HRESULT TiberiumClassExtension::Load(IStream *pStm)
{
    //EXT_DEBUG_TRACE("TiberiumClassExtension::Load - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    HRESULT hr = AbstractTypeClassExtension::Load(pStm);
    if (FAILED(hr)) {
        return E_FAIL;
    }

    new (this) TiberiumClassExtension(NoInitClass());

    return hr;
}


/**
 *  Saves an object to the specified stream.
 *
 *  @author: CCHyper
 */
HRESULT TiberiumClassExtension::Save(IStream *pStm, BOOL fClearDirty)
{
    //EXT_DEBUG_TRACE("TiberiumClassExtension::Save - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    HRESULT hr = AbstractTypeClassExtension::Save(pStm, fClearDirty);
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
int TiberiumClassExtension::Size_Of() const
{
    //EXT_DEBUG_TRACE("TiberiumClassExtension::Size_Of - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    return sizeof(*this);
}


/**
 *  Removes the specified target from any targeting and reference trackers.
 *
 *  @author: CCHyper
 */
void TiberiumClassExtension::Detach(TARGET target, bool all)
{
    //EXT_DEBUG_TRACE("TiberiumClassExtension::Detach - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


/**
 *  Compute a unique crc value for this instance.
 *
 *  @author: CCHyper
 */
void TiberiumClassExtension::Compute_CRC(WWCRCEngine &crc) const
{
    //EXT_DEBUG_TRACE("TiberiumClassExtension::Compute_CRC - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));
}


/**
 *  Fetches the extension data from the INI database.
 *
 *  @author: CCHyper
 */
bool TiberiumClassExtension::Read_INI(CCINIClass &ini)
{
    //EXT_DEBUG_TRACE("TiberiumClassExtension::Read_INI - Name: %s (0x%08X)\n", Name(), (uintptr_t)(This()));

    if (!AbstractTypeClassExtension::Read_INI(ini)) {
        return false;
    }

    const char *ini_name = Name();

    if (!ini.Is_Present(ini_name)) {
        return false;
    }

    return true;
}
DynamicVectorClass<AbstractClass *> &AllAbstracts = Make_Global<DynamicVectorClass<AbstractClass *>>(0x0080F588);
DynamicVectorClass<ViniferaTiberiumClass *> &ViniferaTiberiums = Make_Global<DynamicVectorClass<ViniferaTiberiumClass *>>(0x0080F408);

ViniferaTiberiumClass::ViniferaTiberiumClass(const char *name) :
    Type(TIBERIUM_NONE),
    SpreadCells(0),
    SpreadPercentage(0.1),
    GrowthCells(0),
    GrowthPercentage(0.1),
    Value(0),
    Power(0),
    Color(0),
    Image(nullptr),
    NumFrames(0),
    NumImages(0),
    NumSlopeFacings(0),
    SpreadDataCount(0),
    SpreadQueue(nullptr),
    SpreadState(nullptr),
    SpreadCellData(nullptr),
    SpreadTimer(Frame),
    GrowthDataCount(0),
    GrowthQueue(nullptr),
    GrowthState(nullptr),
    GrowthCellData(nullptr),
    GrowthTimer(Frame)
{
    Type = (TiberiumType)Tiberiums.Count();
    ViniferaTiberiums.Add(this);
    Debris.Clear();
    AllAbstracts.Add(this);
}

int CellStruct_totibarray_42B1C0(const Cell &cell)
{
    return ((cell.X - cell.Y + Map.MapSize.Width - 1) >> 1) + Map.MapSize.Width * (cell.X - Map.MapSize.Width + cell.Y - 1);
}

int two_times_width_times_height_plus_four()
{
    return 2 * Map.MapSize.Width * (Map.MapSize.Height + 4);
}

#ifndef OUTPUT_MANGLED_NAMES
#define OUTPUT_MANGLED_NAME(address, name) __pragma(message("    MakeName(" #address ", " "\"" name "\"" ");"))
#else
#define OUTPUT_MANGLED_NAME(address, name) 
#endif

#define DEFINE_IMPLEMENTATION(prototype, address, ...) \
    /*[[ noreturn ]]*/ __declspec(noinline) __declspec(naked) \
    prototype \
    { \
        OUTPUT_MANGLED_NAME(address, __FUNCDNAME__) \
        _asm { mov eax, address } \
        _asm { jmp eax } \
    }

DEFINE_IMPLEMENTATION(void ViniferaTiberiumClass::Queue_Spread_At_Cell(const Cell &cell), 0x00645C70);

class AAAAAA : public CellClass
{
public:
    int Get_Tiberium_To_Spawn() const;

};

DEFINE_IMPLEMENTATION(int AAAAAA::Get_Tiberium_To_Spawn() const, 0x0045AC10);

void ViniferaTiberiumClass::Grow()
{
#if 0
    signed __int64 v3; // rax
    signed int v4; // edi
    int v5; // eax
    int v6; // ebx
    int v7; // edi MAPDST
    QueueData *cell; // ebx MAPDST
    QueueData **v10; // eax
    CellClass *newcell; // ebp
    int v12; // eax
    QueueData *v14; // ebp MAPDST
    unsigned int v15; // ecx
    unsigned int v16; // edx
    QueueData **v17; // ebp
    QueueData *v18; // ebx
    unsigned int v19; // eax
    ViniferaPriorityQueueClass<QueueData *> *queue; // ecx MAPDST
    QueueData **v21; // eax
    signed int v22; // ebp
    QueueData *v23; // ebx
    int v24; // ebx
    signed int v25; // edx
    QueueData **v26; // eax
    QueueData *v27; // edi
    int v29; // [esp+10h] [ebp-14h]
    int v30; // [esp+14h] [ebp-10h]
    QueueData *v33; // [esp+1Ch] [ebp-8h]
    float v34; // [esp+20h] [ebp-4h]

    queue = GrowthQueue;
    if (!queue || !queue->ActiveCount || this->GrowthPercentage <= 0.00001) {
        return;
    }
    v3 = (signed __int64)((double)queue->ActiveCount * this->GrowthPercentage);
    if ((signed int)v3 < 5) {
        goto LABEL_49;
    }
    if ((signed int)v3 > 50) {
        v4 = 50;
        goto LABEL_10;
    }
    if ((signed int)v3 < 5) {
    LABEL_49:
        v4 = 5;
    } else {
        v4 = v3;
    }
LABEL_10:
    v5 = Scen->RandomNumber();
    v6 = this->GrowthQueue->ActiveCount;
    v7 = abs(v5) % v4 + 1;
    if (v6 > two_times_width_times_height_plus_four() - 2 * v7) {
        Recalc_Growth_Data();
    }

    queue = this->GrowthQueue;
    v30 = 0;
    if (queue->ActiveCount) {
        v10 = queue->Heap;
        cell = v10[1];
        v10[1] = v10[queue->ActiveCount];
        queue->Heap[queue->ActiveCount--] = 0;
        queue->Heapify_Down(1);
    } else {
        cell = 0;
        cell = 0;
    }
    if (v7 > 0) {
        while (1) {
            while (1) {
                if (!cell) {
                    return;
                }
                newcell = &Map[cell->Cell];
                if (((AAAAAA *)newcell)->Get_Tiberium_To_Spawn() == this->Type) {
                    newcell->Grow_Tiberium();
                    if (newcell->OverlayData < 11u) {
                        this->GrowthCellData[this->GrowthDataCount].Cell = cell->Cell;
                        this->GrowthCellData[this->GrowthDataCount].Score = (double)(Frame + abs(Scen->RandomNumber() % 50));
                        this->GrowthState[CellStruct_totibarray_42B1C0(cell->Cell)] = true;
                        v12 = this->GrowthDataCount;
                        queue = this->GrowthQueue;
                        v14 = &this->GrowthCellData[v12];
                        this->GrowthDataCount = v12 + 1;
                        v15 = queue->ActiveCount + 1;
                        v34 = v14->Score;
                        v16 = v15 >> 1;
                        if (v15 < queue->Capacity) {
                            for (; v15 > 1; v16 >>= 1) {
                                v17 = queue->Heap;
                                v18 = v17[v16];
                                if (v18->Score <= (double)v34) {
                                    break;
                                }
                                v17[v15] = v18;
                                v15 = v16;
                            }
                            queue->Heap[v15] = v14;
                            v19 = queue->MaxNodePointer;
                            ++queue->ActiveCount;
                            if ((unsigned int)v14 > v19) {
                                queue->MaxNodePointer = (unsigned int)v14;
                            }
                            if ((unsigned int)v14 < queue->MinNodePointer) {
                                queue->MinNodePointer = (unsigned int)v14;
                            }
                        }
                        Queue_Spread_At_Cell(cell->Cell);
                    } else {
                        this->GrowthState[CellStruct_totibarray_42B1C0(cell->Cell)] = 0;
                    }
                }
                if (++v30 >= v7) {
                    return;
                }
                queue = this->GrowthQueue;
                if (queue->ActiveCount) {
                    break;
                }
                cell = 0;
                cell = 0;
            }
            v21 = queue->Heap;
            v22 = 1;
            v23 = v21[1];
            v21[1] = v21[queue->ActiveCount];
            v33 = v23;
            queue->Heap[queue->ActiveCount] = 0;
            v24 = queue->ActiveCount - 1;
            queue->ActiveCount = v24;
            if (v24 < 2 || (v25 = 2, *(float *)(*((unsigned int *)queue->Heap + 1) + 4) <= (double)*(float *)(*((unsigned int *)queue->Heap + 2) + 4))) {
                v25 = 1;
            }
            if (v24 >= 3 && queue->Heap[v25]->Score > (double)*(float *)(*((unsigned int *)queue->Heap + 3) + 4)) {
                v25 = 3;
            } else if (v25 == 1) {
                goto LABEL_46;
            }
            do {
                v26 = queue->Heap;
                v27 = v26[v22];
                v26[v22] = v26[v25];
                v22 = v25;
                queue->Heap[v25] = v27;
                v29 = 2 * v25 + 1;
                if (2 * v25 <= queue->ActiveCount && queue->Heap[v25]->Score > (double)queue->Heap[2 * v25]->Score) {
                    v25 *= 2;
                }
                if (v29 <= queue->ActiveCount && queue->Heap[v25]->Score > (double)queue->Heap[v29]->Score) {
                    v25 = v29;
                }
            } while (v25 != v22);
        LABEL_46:
            cell = v33;
            cell = v33;
        }
    }
#endif
    int v4;

    if (!GrowthQueue || !GrowthQueue->Count() || GrowthPercentage <= 0.00001) {
        return;
    }

    signed __int64 v3 = (signed __int64)((double)GrowthQueue->ActiveCount * GrowthPercentage);
    if ((signed int)v3 < 5) {
        goto LABEL_49;
    }
    if ((signed int)v3 > 50) {
        v4 = 50;
        goto LABEL_10;
    }
    if ((signed int)v3 < 5) {
    LABEL_49:
        v4 = 5;
    } else {
        v4 = v3;
    }
LABEL_10:
    int count = abs(Scen->RandomNumber()) % v4 + 1;
    if (GrowthQueue->Count() > two_times_width_times_height_plus_four() - 2 * count) {
        Recalc_Growth_Data();
    }

    int i = 0;
    QueueData *cell = *GrowthQueue->Extract();

    if (count > 0)
    {
        while (true) {
            while (true) {

                if (!cell) {
                    return;
                }

                CellClass *newcell = &Map[cell->Cell];
                if (((AAAAAA *)newcell)->Get_Tiberium_To_Spawn() == Type) {

                    newcell->Grow_Tiberium();

                    if (newcell->OverlayData < 11) {
                        GrowthCellData[GrowthDataCount].Cell = cell->Cell;
                        GrowthCellData[GrowthDataCount].Score = (double)(Frame + abs(Scen->RandomNumber() % 50));
                        GrowthState[CellStruct_totibarray_42B1C0(cell->Cell)] = true;
                        QueueData *q = &GrowthCellData[GrowthDataCount++];

                        GrowthQueue->Insert(&q);
                        Queue_Spread_At_Cell(cell->Cell);
                    } else {
                        GrowthState[CellStruct_totibarray_42B1C0(cell->Cell)] = false;
                    }
                }
                if (++i >= count) {
                    return;
                }

                if (GrowthQueue->Count()) {
                    break;
                }

                cell = nullptr;
            }

            cell = *GrowthQueue->Extract();
        }
    }
}

void ViniferaTiberiumClass::Init_Growth_Data()
{
#if 0
    ViniferaTiberiumClass *v1; // edi
    ViniferaPriorityQueueClass<QueueData *> *v2; // eax
    int i; // ecx
    void **v4; // esi
    int v5; // eax
    QueueData *v6; // eax
    int v7; // eax
    ViniferaPriorityQueueClass<QueueData *> *v8; // esi
    int v9; // eax
    QueueData **v10; // eax
    int v11; // ecx
    int v12; // eax

    v1 = this;
    v2 = this->GrowthQueue;
    if (v2) {
        for (i = 0; i <= v2->ActiveCount; v2->Heap[i - 1] = 0) {
            ++i;
        }
        v2->ActiveCount = 0;
        v4 = (void **)v1->GrowthQueue;
        if (v4) {
            operator delete(v4[2]);
            operator delete(v4);
        }
        v1->GrowthQueue = 0;
    }

    if (v1->GrowthCellData) {
        operator delete(v1->GrowthCellData);
        v1->GrowthCellData = 0;
    }

    if (v1->GrowthState) {
        operator delete(v1->GrowthState);
        v1->GrowthState = 0;
    }

    v1->GrowthDataCount = 0;
    v5 = two_times_width_times_height_plus_four();
    v6 = (QueueData *)operator new(8 * v5);
    if (!v6) {
        v6 = 0;
    }
    v1->GrowthCellData = v6;
    v7 = two_times_width_times_height_plus_four();
    v1->GrowthState = (bool *)operator new(v7);
    v8 = (ViniferaPriorityQueueClass<QueueData *> *)operator new(0x14u);
    if (!v8) {
        v8 = 0;
        goto LABEL_18;
    }
    v9 = two_times_width_times_height_plus_four();
    v8->MaxNodePointer = 0;
    v8->MinNodePointer = -1;
    v8->ActiveCount = 0;
    v8->Capacity = v9;
    v10 = (QueueData **)operator new(4 * v9 + 4);
    v11 = v8->Capacity;
    v8->Heap = v10;
    v12 = 0;
    if (v11 < 0) {
    LABEL_18:
        v1->GrowthQueue = v8;
        Recalc_Growth_Data();
        return;
    }
    do {
        v8->Heap[++v12 - 1] = 0;
    } while (v12 <= v8->Capacity);
    v1->GrowthQueue = v8;
    Recalc_Growth_Data();
#endif
    Delete_Growth_Data();

    GrowthCellData = new QueueData[two_times_width_times_height_plus_four()];
    GrowthState = new bool[two_times_width_times_height_plus_four()];
    GrowthQueue = new ViniferaPriorityQueueClass<QueueData *>(two_times_width_times_height_plus_four());

    Recalc_Growth_Data();
}

void ViniferaTiberiumClass::Recalc_Growth_Data()
{
#if 0
    int v2 = 0;
    ViniferaPriorityQueueClass<QueueData *> *v3 = this->GrowthQueue;
    this->GrowthDataCount = 0;
    if (v3->ActiveCount >= 0) {
        do {
            v3->Heap[++v2 - 1] = 0;
        } while (v2 <= v3->ActiveCount);
    }
    v3->ActiveCount = 0;

    for (int i = two_times_width_times_height_plus_four() - 1; i >= 0; this->GrowthState[i + 1] = 0) {
        --i;
    }

    Map.Iterator_Reset();

    for (CellClass *j = Map.Iterator_Next_Cell(); j; j = Map.Iterator_Next_Cell()) {

        if (((AAAAAA *)j)->Get_Tiberium_To_Spawn() == Type && j->Can_Tiberium_Grow()) {
            Cell &v6 = j->Pos;

            GrowthCellData[GrowthDataCount].Cell = j->Pos;
            GrowthCellData[GrowthDataCount].Score = 0.0;

            int index = this->GrowthDataCount;
            ViniferaPriorityQueueClass<QueueData *> *pri_this = this->GrowthQueue;
            QueueData *pri_item = &this->GrowthCellData[index];
            this->GrowthDataCount = index + 1;
            unsigned int v10 = pri_this->ActiveCount + 1;
            float v15 = pri_item->Score;
            unsigned int v11 = v10 >> 1;
            if (v10 < pri_this->Capacity) {
                for (; v10 > 1; v11 >>= 1) {
                    QueueData **v12 = pri_this->Heap;
                    QueueData *v13 = v12[v11];
                    if (v13->Score <= (double)v15) {
                        break;
                    }
                    v12[v10] = v13;
                    v10 = v11;
                }
                pri_this->Heap[v10] = pri_item;
                ++pri_this->ActiveCount;

                if ((unsigned int)pri_item > pri_this->MaxNodePointer) {
                    pri_this->MaxNodePointer = (unsigned int)pri_item;
                }
                if ((unsigned int)pri_item < pri_this->MinNodePointer) {
                    pri_this->MinNodePointer = (unsigned int)pri_item;
                }
            }

            GrowthState[CellStruct_totibarray_42B1C0(v6)] = true;
        }
    }
#endif
    GrowthDataCount = 0;
    GrowthQueue->Clear();

    for (int i = two_times_width_times_height_plus_four() - 1; i >= 0; GrowthState[i + 1] = false) {
        --i;
    }
    Map.Iterator_Reset();

    for (CellClass *cell = Map.Iterator_Next_Cell(); cell; cell = Map.Iterator_Next_Cell()) {

        if (((AAAAAA *)cell)->Get_Tiberium_To_Spawn() == Type && cell->Can_Tiberium_Grow()) {
            Cell &v6 = cell->Pos;

            GrowthCellData[GrowthDataCount].Cell = cell->Pos;
            GrowthCellData[GrowthDataCount].Score = 0.0;
            QueueData *q = &GrowthCellData[GrowthDataCount++];
            GrowthQueue->Insert(&q);
            GrowthState[CellStruct_totibarray_42B1C0(v6)] = true;
        }
    }
}


void ViniferaTiberiumClass::Delete_Growth_Data()
{
#if 0
    if (GrowthQueue) {
        for (int i = 0; i <= GrowthQueue->ActiveCount; GrowthQueue->Heap[i - 1] = nullptr) {
            ++i;
        }

        GrowthQueue->ActiveCount = 0;

        if (GrowthQueue) {
            delete[] GrowthQueue->Heap;
            delete GrowthQueue;
        }

        GrowthQueue = nullptr;
    }

    if (GrowthCellData) {
        delete[] GrowthCellData;
        GrowthCellData = nullptr;
    }
    if (GrowthState) {
        delete[] GrowthState;
        GrowthState = nullptr;
    }

    GrowthDataCount = 0;
#endif
    if (GrowthQueue) {
        GrowthQueue->Clear();
        delete GrowthQueue;
    }

    if (GrowthCellData) {
        delete[] GrowthCellData;
        GrowthCellData = nullptr;
    }
    if (GrowthState) {
        delete[] GrowthState;
        GrowthState = nullptr;
    }

    GrowthDataCount = 0;
}

void ViniferaTiberiumClass::Queue_Growth_At_Cell(const Cell &cell)
{
#if 0
    int cell_index = CellStruct_totibarray_42B1C0(cell);

    if (Map[cell].OverlayData < 11) {

        if (GrowthDataCount > two_times_width_times_height_plus_four() - 10) {
            Recalc_Growth_Data();
        }

        GrowthCellData[GrowthDataCount].Cell = cell;
        GrowthCellData[GrowthDataCount].Score = (double)(Frame + abs(Scen->RandomNumber()) % 50);

        int v3 = GrowthDataCount;

        ViniferaPriorityQueueClass<QueueData *> *v4 = GrowthQueue;
        QueueData *v5 = &GrowthCellData[v3];

        GrowthDataCount = v3 + 1;


        unsigned int index = v4->ActiveCount + 1;
        float a2a = v5->Score;
        unsigned int parent_index = index >> 1;

        // PriorityQueueClass::Insert
        if (index < v4->Capacity) {
            for (; index > 1; parent_index >>= 1) {

                QueueData **heap = v4->Heap;
                QueueData *v9 = heap[parent_index];

                if (v9->Score <= (double)a2a) {
                    break;
                }
                heap[index] = v9;
                index = parent_index;
            }

            v4->Heap[index] = v5;
            ++v4->ActiveCount;

            if ((unsigned int)v5 > v4->MaxNodePointer) {
                v4->MaxNodePointer = (unsigned int)v5;
            }

            if ((unsigned int)v5 < v4->MinNodePointer) {
                v4->MinNodePointer = (unsigned int)v5;
            }
        }

        GrowthState[cell_index] = true;
    }
#endif

    int cell_index = CellStruct_totibarray_42B1C0(cell);

    if (Map[cell].OverlayData < 11) {

        if (GrowthDataCount > two_times_width_times_height_plus_four() - 10) {
            Recalc_Growth_Data();
        }

        GrowthCellData[GrowthDataCount].Cell = cell;
        GrowthCellData[GrowthDataCount].Score = (double)(Frame + abs(Scen->RandomNumber()) % 50);

        QueueData *q = &GrowthCellData[GrowthDataCount++];
        GrowthQueue->Insert(&q);
        GrowthState[cell_index] = true;
    }
}