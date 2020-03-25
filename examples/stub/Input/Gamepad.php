<?php

namespace raylib\Input;

class Gamepad
{
    // Gamepad number
    const PLAYER1 = 0;
    const PLAYER2 = 1;
    const PLAYER3 = 2;
    const PLAYER4 = 3;

    // Gamepad Buttons
    // This is here just for error checking
    const BUTTON_UNKNOWN = 0;

    // This is normally a DPAD
    const BUTTON_LEFT_FACE_UP = 1;
    const BUTTON_LEFT_FACE_RIGHT = 2;
    const BUTTON_LEFT_FACE_DOWN = 3;
    const BUTTON_LEFT_FACE_LEFT = 4;

    // This normally corresponds with PlayStation and Xbox controllers
    // XBOX: [Y,X,A,B]
    // PS3: [Triangle,Square,Cross,Circle]
    // No support for 6 button controllers though..
    const BUTTON_RIGHT_FACE_UP = 5;
    const BUTTON_RIGHT_FACE_RIGHT = 6;
    const BUTTON_RIGHT_FACE_DOWN = 7;
    const BUTTON_RIGHT_FACE_LEFT = 8;

    // Triggers
    const BUTTON_LEFT_TRIGGER_1 = 9;
    const BUTTON_LEFT_TRIGGER_2 = 10;
    const BUTTON_RIGHT_TRIGGER_1 = 11;
    const BUTTON_RIGHT_TRIGGER_2 = 12;

    // These are buttons in the center of the gamepad
    const BUTTON_MIDDLE_LEFT = 13;     //PS3 Select
    const BUTTON_MIDDLE = 14;          //PS Button/XBOX Button
    const BUTTON_MIDDLE_RIGHT = 15;    //PS3 Start

    // These are the joystick press in buttons
    const BUTTON_LEFT_THUMB = 16;
    const BUTTON_RIGHT_THUMB = 17;

    // This is here just for error checking
    const AXIS_UNKNOWN = 0;

    // Left stick
    const AXIS_LEFT_X = 1;
    const AXIS_LEFT_Y = 2;

    // Right stick
    const AXIS_RIGHT_X = 3;
    const AXIS_RIGHT_Y = 4;

    // Pressure levels for the back triggers
    const AXIS_LEFT_TRIGGER = 5;      // [1..-1] (pressure-level)
    const AXIS_RIGHT_TRIGGER = 6;     // [1..-1] (pressure-level)


    /**
     * Detect if a gamepad is available
     *
     * @param int $gamepad
     *
     * {@internal RLAPI bool IsGamepadAvailable(int gamepad); }}
     *
     * @return bool
     */
    public static function isAvailable(int $gamepad): bool
    {
    }

    /**
     * Check gamepad name (if available)
     *
     * @param int $gamepad
     * @param string $name
     *
     * {@internal RLAPI bool IsGamepadName(int gamepad, const char *name); }}
     *
     * @return bool
     */
    public static function isName(int $gamepad, string $name): bool
    {
    }

    /**
     * Return gamepad internal name id
     *
     * @param int $gamepad
     *
     * {@internal RLAPI const char *GetGamepadName(int gamepad); }}
     *
     * @return string
     */
    public static function getName(int $gamepad): string
    {
    }

    /**
     * Detect if a gamepad button has been pressed once
     *
     * @param int $gamepad
     * @param int $button
     *
     * {@internal RLAPI bool IsGamepadButtonPressed(int gamepad, int button); }}
     *
     * @return bool
     */
    public static function isButtonPressed(int $gamepad, int $button): bool
    {
    }

    /**
     * Detect if a gamepad button is being pressed
     *
     * @param int $gamepad
     * @param int $button
     *
     * {@internal RLAPI bool IsGamepadButtonDown(int gamepad, int button); }}
     *
     * @return bool
     */
    public static function isButtonDown(int $gamepad, int $button): bool
    {
    }

    /**
     * Detect if a gamepad button has been released once
     *
     * @param int $gamepad
     * @param int $button
     *
     * {@internal RLAPI bool IsGamepadButtonReleased(int gamepad, int button); }}
     *
     * @return bool
     */
    public static function isButtonReleased(int $gamepad, int $button): bool
    {
    }

    /**
     * Detect if a gamepad button is NOT being pressed
     *
     * @param int $gamepad
     * @param int $button
     *
     * {@internal RLAPI bool IsGamepadButtonUp(int gamepad, int button); }}
     *
     * @return bool
     */
    public static function isButtonUp(int $gamepad, int $button): bool
    {
    }

    /**
     * Get the last gamepad button pressed
     *
     * {@internal RLAPI int GetGamepadButtonPressed(void); }}
     *
     * @return bool
     */
    public static function getButtonPressed(): bool
    {
    }

    /**
     * Return gamepad axis count for a gamepad
     *
     * @param int $gamepad
     *
     * {@internal RLAPI int GetGamepadAxisCount(int gamepad);  }}
     *
     * @return int
     */
    public static function getAxisCount(int $gamepad): int
    {
    }

    /**
     * Return axis movement value for a gamepad axis
     *
     * @param int $gamepad
     * @param int $axis
     *
     * {@internal RLAPI float GetGamepadAxisMovement(int gamepad, int axis); }}
     *
     * @return float
     */
    public static function getAxisMovement(int $gamepad, int $axis): float
    {
    }
}
