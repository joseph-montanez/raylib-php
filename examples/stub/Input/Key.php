<?php

namespace raylib\Input;


class Key
{
    const SPACE = 1;
    const ESCAPE = 1;
    const ENTER = 1;
    const TAB = 1;
    const BACKSPACE = 1;
    const INSERT = 1;
    const DELETE = 1;
    const RIGHT = 1;
    const LEFT = 1;
    const DOWN = 1;
    const UP = 1;
    const PAGE_UP = 1;
    const PAGE_DOWN = 1;
    const HOME = 1;
    const END = 1;
    const CAPS_LOCK = 1;
    const SCROLL_LOCK = 1;
    const NUM_LOCK = 1;
    const PRINT_SCREEN = 1;
    const PAUSE = 1;
    const F1 = 1;
    const F2 = 1;
    const F3 = 1;
    const F4 = 1;
    const F5 = 1;
    const F6 = 1;
    const F7 = 1;
    const F8 = 1;
    const F9 = 1;
    const F10 = 1;
    const F11 = 1;
    const F12 = 1;
    const LEFT_SHIFT = 1;
    const LEFT_CONTROL = 1;
    const LEFT_ALT = 1;
    const RIGHT_SHIFT = 1;
    const RIGHT_CONTROL = 1;
    const RIGHT_ALT = 1;

    const ZERO = 1;
    const ONE = 1;
    const TWO = 1;
    const THREE = 1;
    const FOUR = 1;
    const FIVE = 1;
    const SIX = 1;
    const SEVEN = 1;
    const EIGHT = 1;
    const NINE = 1;
    const A = 1;
    const B = 1;
    const C = 1;
    const D = 1;
    const E = 1;
    const F = 1;
    const G = 1;
    const H = 1;
    const I = 1;
    const J = 1;
    const K = 1;
    const L = 1;
    const M = 1;
    const N = 1;
    const O = 1;
    const P = 1;
    const Q = 1;
    const R = 1;
    const S = 1;
    const T = 1;
    const U = 1;
    const V = 1;
    const W = 1;
    const X = 1;
    const Y = 1;
    const Z = 1;

    /**
     * Detect if a key has been pressed once
     * @param int $key
     *
     * {@internal bool IsKeyPressed(int key) }}
     *
     * @return bool
     */
    public static function isPressed(int $key) : bool {}

    /**
     * Detect if a key is being pressed
     *
     * @param int $key
     *
     * {@internal bool IsKeyDown(int key) }}
     *
     * @return bool
     */
    public static function isDown(int $key) : bool {}

    /**
     * Detect if a key has been released once
     *
     * @param int $key
     *
     * {@internal bool IsKeyReleased(int key) }}
     *
     * @return bool
     */
    public static function isReleased(int $key) : bool {}

    /**
     * Detect if a key is NOT being pressed
     *
     * @param int $key
     *
     * {@internal bool IsKeyUp(int key) }}
     *
     * @return bool
     */
    public static function isUp(int $key) : bool {}

    /**
     * Get latest key pressed
     *
     * {@internal int GetKeyPressed(void) }}
     *
     * @return int
     */
    public static function getPressed() : int {}

    /**
     * Set a custom key to exit program (default is ESC)
     *
     * {@internal void SetExitKey(int key) }}
     *
     * @param int $key
     */
    public static function setExit(int $key) : void {}

}