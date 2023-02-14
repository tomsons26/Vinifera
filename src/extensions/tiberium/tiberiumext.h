/*******************************************************************************
/*                 O P E N  S O U R C E  --  V I N I F E R A                  **
/*******************************************************************************
 *
 *  @project       Vinifera
 *
 *  @file          TIBERIUMEXT.H
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
#pragma once

#include "abstracttypeext.h"
#include "tiberium.h"


class DECLSPEC_UUID(UUID_TIBERIUM_EXTENSION)
    TiberiumClassExtension final : public AbstractTypeClassExtension
{
    public:
        /**
         *  IPersist
         */
        IFACEMETHOD(GetClassID)(CLSID * pClassID);

        /**
         *  IPersistStream
         */
        IFACEMETHOD(Load)(IStream *pStm);
        IFACEMETHOD(Save)(IStream *pStm, BOOL fClearDirty);

    public:
        TiberiumClassExtension(const TiberiumClass *this_ptr = nullptr);
        TiberiumClassExtension(const NoInitClass &noinit);
        virtual ~TiberiumClassExtension();

        virtual int Size_Of() const override;
        virtual void Detach(TARGET target, bool all = true) override;
        virtual void Compute_CRC(WWCRCEngine &crc) const override;

        virtual TiberiumClass *This() const override { return reinterpret_cast<TiberiumClass *>(AbstractTypeClassExtension::This()); }
        virtual const TiberiumClass *This_Const() const override { return reinterpret_cast<const TiberiumClass *>(AbstractTypeClassExtension::This_Const()); }
        virtual RTTIType What_Am_I() const override { return RTTI_TIBERIUM; }

        virtual bool Read_INI(CCINIClass &ini) override;

    public:
};



template<typename T>
class ViniferaPriorityQueueClass
{
public:
    ViniferaPriorityQueueClass(int capacity);
    ~ViniferaPriorityQueueClass();

    void Clear();

    //private:
    unsigned int Heapify_Up(unsigned int index);
    void Heapify_Down(unsigned int index);

public:
    T *Extract();

    bool Insert(const T *node);

private:
    inline unsigned int Parent(unsigned int index) {
        return index / 2;
    }

    inline unsigned int Left(unsigned int index)
    {
        return 2 * index;
    }
    inline unsigned int Right(unsigned int index)
    {
        return 2 * index + 1;
    }

public:
    inline bool Is_Empty() const
    {
        return ActiveCount == 0;
    }

    inline unsigned int Count() { return ActiveCount; }

    //private:
    unsigned int ActiveCount;
    unsigned int Capacity;
    T *Heap;
    unsigned int MaxNodePointer;
    unsigned int MinNodePointer;
};
template <typename T>
ViniferaPriorityQueueClass<T>::ViniferaPriorityQueueClass(int capacity)
{
    MaxNodePointer = 0;
    MinNodePointer = -1;
    ActiveCount = 0;
    Capacity = capacity;
    Heap = new T[capacity + 1];

    //todo figure out how it was
    //int i = 0;
    //if ( Capacity >= 0 )
    //{
    //	do
    //	{
    //		Heap[++i - 1] = nullptr;
    //	}
    //	while ( i <= Capacity);
    //}

    for (int i = 0; i < Capacity + 1; ++i) {
        Heap[i] = 0;
    }
}



template <typename T>
unsigned int ViniferaPriorityQueueClass<T>::Heapify_Up(unsigned int index)
{
    unsigned int parent_index = Parent(index);
    while (index > 1 && Heap[parent_index] > Heap[index]) {
        Heap[index] = Heap[parent_index];//this should be a swap
        index = Parent(parent_index);
    }

    return index;
}

template <typename T>
inline void ViniferaPriorityQueueClass<T>::Heapify_Down(unsigned int index)
{
    //if (index > ActiveCount){
    //    return;
    //}

    unsigned int min_index = index;

    unsigned int left_index = Left(index);
    unsigned int right_index = Right(index);

    if (left_index <= ActiveCount && Heap[min_index] > Heap[left_index]) {
        min_index = left_index;
    }

    if (right_index <= ActiveCount && Heap[min_index] > Heap[right_index]) {
        min_index = right_index;
    }

    if (min_index != index) {
        T &tmp = Heap[index]; //swap
        Heap[index] = Heap[min_index];
        Heap[min_index] = tmp;
        Heapify_Down(min_index);
    }
}

template <typename T>
bool ViniferaPriorityQueueClass<T>::Insert(const T *node)
{
    unsigned int new_index = ActiveCount + 1;
    if (new_index < Capacity) {
        //while(new_index > 1) {
        //	parent_index = Parent(new_index);
        //	if (*Heap[parent_index] > *node) {
        //		T *tmp = Heap[new_index];
        //		Heap[new_index] = Heap[parent_index];
        //		new_index = parent_index;
        //	} else {       
        //      break;
        //  }
        //}
        //Heapify_Up(new_index);///the loop above appears to modify new_index.. is there a bug here....

        //implements a return to match original, todo verify this is logically correct as
        //this may be trashing the heap.......
        new_index = Heapify_Up(new_index);

        Heap[new_index] = *node;
        ++ActiveCount;

        if ((unsigned int)node > MaxNodePointer) {
            MaxNodePointer = (int)node;
        }
        if ((unsigned int)node < MinNodePointer) {
            MinNodePointer = (int)node;
        }

        return true;
    }

    return false;
}
//done, matches
template <typename T>
T *ViniferaPriorityQueueClass<T>::Extract()
{
    if (Is_Empty()) {
        return nullptr;
    }

    T &node = Heap[1];
    Heap[1] = Heap[ActiveCount];

    Heap[ActiveCount] = nullptr;

    ActiveCount--;

    Heapify_Down(1);

    return &node;
}

template <typename T>
ViniferaPriorityQueueClass<T>::~ViniferaPriorityQueueClass()
{
    delete[] Heap;
}

template <typename T>
void ViniferaPriorityQueueClass<T>::Clear()
{
    //original pseudo
    //for ( i = 0; i <= v2->ActiveCount; v2->Heap[i - 1] = 0 )
    //{
    //	++i;
    //}
    //v2->ActiveCount = 0;

    //todo verify may be size -  1 or start with 1
    //as heap[0] is special in some way
    for (int i = 0; i < ActiveCount + 1; ++i) {
        Heap[i] = nullptr;
    }
    ActiveCount = 0;
}


#include "abstracttype.h"
#include "typelist.h"
#include "ttimer.h"
#include "ftimer.h"


class OverlayTypeClass;
class AnimTypeClass;


class DECLSPEC_UUID("C53DD373-151E-11D2-8175-006008055BB5")
    ViniferaTiberiumClass : public AbstractTypeClass
{
public:
    /**
     *  IPersist
     */
     //IFACEMETHOD(GetClassID)(CLSID * pClassID);

     /**
      *  IPersistStream
      */
      //IFACEMETHOD(Load)(IStream * pStm);
      //IFACEMETHOD(Save)(IStream * pStm, BOOL fClearDirty);
      //IFACEMETHOD(GetSizeMax)(ULARGE_INTEGER * pcbSize);

public:
    ViniferaTiberiumClass(const char *ini_name = nullptr);
    ViniferaTiberiumClass(const NoInitClass & noinit);
    virtual ~ViniferaTiberiumClass() {}

    /**
     *  AbstractClass
     */
     //virtual void Detach(TARGET target, bool all = true) override;
     //virtual RTTIType Kind_Of() const override;
     //virtual int Size_Of(bool firestorm = false) const override;
     //virtual void Compute_CRC(WWCRCEngine & crc) const override;
     //virtual int Get_Heap_ID() const override;

     /**
      *  AbstractTypeClass
      */
      //virtual bool Read_INI(CCINIClass & ini) override;

      //void Spread_AI();
      //void Spread_Init_Clear();
      //void Spread();
      //// 006458F0
      //// 00645A30
      //// 00645BA0
      //// 00645C30
      //void Add_Spread_Cell(Cell & cell);
      //
      //void Growth_AI();
      //void Growth_Init_Clear();
      //void Grow();
      //// 00646080
      //// 006463D0
      //// 00646510
      //// 00646680
      //void Add_Growth_Cell(Cell & cell);
      //
      //static void Process(CCINIClass & ini);
      //
      //static void Init_Cells();
      //static void Init();
      //
      //static const TiberiumClass &As_Reference(TiberiumType type);
      //static const TiberiumClass *As_Pointer(TiberiumType type);
      //static const TiberiumClass &As_Reference(const char *name);
      //static const TiberiumClass *As_Pointer(const char *name);
      //static TiberiumType From_Name(const char *name);
      //static const char *Name_From(TiberiumType type);

    void Spread();
    void Init_Spread_Data();
    void Recalc_Spread_Data();
    void Delete_Spread_Data();
    void Queue_Spread_At_Cell(const Cell & cell);

    void Grow();
    void Init_Growth_Data();
    void Recalc_Growth_Data();
    void Delete_Growth_Data();
    void Queue_Growth_At_Cell(const Cell & cell);

    struct QueueData
    {
        Cell Cell;
        float Score;
    };

public:
    TiberiumType Type;
    int SpreadCells;
    double SpreadPercentage;
    int GrowthCells;
    double GrowthPercentage;
    int Value;
    int Power;
    int Color;
    TypeList<AnimTypeClass *> Debris;
    OverlayTypeClass *Image;
    int NumFrames;
    int NumImages;
    int NumSlopeFacings;
    int SpreadDataCount;
    ViniferaPriorityQueueClass<QueueData *> *SpreadQueue;
    bool *SpreadState;
    QueueData *SpreadCellData;
    CDTimerClass<FrameTimerClass> SpreadTimer;
    int GrowthDataCount;
    ViniferaPriorityQueueClass<QueueData *> *GrowthQueue;
    bool *GrowthState;
    QueueData *GrowthCellData;
    CDTimerClass<FrameTimerClass> GrowthTimer;
};
