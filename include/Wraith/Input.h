//
// Input.h
// WraithEngine
//
// Created by Andre Rodrigues on 04/12/2022.
//

#pragma once

namespace Wraith::Input {

    enum class KeyCode : int {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,

        NumPad0,
        NumPad1,
        NumPad2,
        NumPad3,
        NumPad4,
        NumPad5,
        NumPad6,
        NumPad7,
        NumPad8,
        NumPad9,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,

        ArrowUp,
        ArrowDown,
        ArrowLeft,
        ArrowRight,

        Return,
        Backspace,
        Delete,
        Insert,
        Home,

        LShift,
        RShift,
        LCtrl,
        RCtrl,
        LAlt,
        RAlt,

        Tab,
        CapsLock,
        Space,

        Unknown,

        Count // Reserved: always keep as last
    };
    
    enum class MouseButton : int {
        Left,
        Right,
        Middle,

        Unknown,

        Count // Reserved: always keep as last
    };

}