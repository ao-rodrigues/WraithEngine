//
// Object.h
// WraithEngine
//
// Created by Andre Rodrigues on 07/12/2022.
//

#pragma once

#include <functional>

namespace Wraith {

    template<typename T>
    class Object {
    public:
        static T Undefined;

        class Ref : public std::reference_wrapper<const T> {
        public:
            Ref() : std::reference_wrapper<const T>(Object<T>::Undefined) {}
            Ref(const T& obj) : std::reference_wrapper<const T>(obj) {}

            const T* operator->() const {
                return &std::reference_wrapper<const T>::get();
            }
        };

        class MutableRef : public std::reference_wrapper<T> {
        public:
            MutableRef() : std::reference_wrapper<T>(Object<T>::Undefined) {}
            MutableRef(T& obj) : std::reference_wrapper<T>(obj) {}

            T* operator->() {
                return &std::reference_wrapper<T>::get();
            }
        };

        virtual bool IsUndefined() const {
            return this == &Object<T>::Undefined;
        }
    };

    template<typename T>
    T Object<T>::Undefined = T();

}
