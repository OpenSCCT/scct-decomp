#ifndef VERSUS_SCENE_LIST_H
#define VERSUS_SCENE_LIST_H

template<class T> struct TList {
    T Element;
    TList *Next;

    TList(T InElement, TList *InNext) : Element(InElement), Next(InNext) {}
};

#endif
