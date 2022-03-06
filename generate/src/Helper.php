<?php

namespace Raylib\Parser;

class Helper
{
    public static function isArray(string $type): bool
    {
        $isPrimitive = self::isPrimitive($type);
        $starCount   = substr_count($type, '*');

        if (!$isPrimitive && $starCount > 1) {
            return true;
        } else if (!$isPrimitive && $starCount === 1) {
            return false;
        } else if ($isPrimitive && $starCount === 1) {
            return true;
        } else {
            return false;
        }
    }

    public static function isPointer(string $type): bool
    {
        $isPrimitive = self::isPrimitive($type);
        $starCount   = substr_count($type, '*');

        if (!$isPrimitive && $starCount > 1) {
            return false;
        } else if (!$isPrimitive && $starCount === 1) {
            return true;
        } else if ($isPrimitive && $starCount === 1) {
            return false;
        } else {
            return false;
        }
    }

    public static function isPrimitive(string $type): bool
    {
        return (
            str_starts_with($type, 'int') ||
            str_starts_with($type, 'long') ||
            str_starts_with($type, 'unsigned') ||
            str_starts_with($type, 'const unsigned') ||
            str_starts_with($type, 'float') ||
            str_starts_with($type, 'double') ||
            str_starts_with($type, 'const char') ||
            str_starts_with($type, 'char') ||
            str_starts_with($type, 'void') ||
            str_starts_with($type, 'bool')
        );
    }

    public static function isFloat(string $type): bool
    {
        return str_starts_with($type, 'float') || str_starts_with($type, 'double');
    }

    public static function isInt(string $type): bool
    {
        return str_starts_with($type, 'int')
            || str_starts_with($type, 'short')
            || str_starts_with($type, 'long')
            || str_starts_with($type, 'unsigned short')
            || str_starts_with($type, 'unsigned int')
            || str_starts_with($type, 'const unsigned char')
            || str_starts_with($type, 'unsigned char');

    }

    public static function isString(string $type): bool
    {
        return str_starts_with($type, 'char')
            || str_starts_with($type, 'const char');

    }

    public static function toPhpType(Field $field)
    {
        if (Helper::isFloat($field->type) && !($field->isArray || $field->isPointer)) {
            $phpType = 'double';
        } elseif (Helper::isInt($field->type) && !($field->isArray || $field->isPointer)) {
            $phpType = 'zend_long';
        } elseif (Helper::isString($field->type)) {
            $phpType = 'zend_string *';
        } elseif ($field->isArray) {
            $phpType = 'HashTable *';
        } elseif ($field->type === 'bool') {
            $phpType = 'bool';
        } else {
            $phpType = 'zend_object *';
        }

        return $phpType;
    }

    public static function isBool(string $type)
    {
        return str_starts_with($type, 'bool');
    }

    public static function replaceAlias(array $aliases, string $type): string
    {

        $typePlain = trim(str_replace(['*'], '', $type));
        $parts     = explode('[', $typePlain);
        $typePlain = array_shift($parts);


        $aliasReferenceType = null;
        foreach ($aliases as $aliasKey => $aliasTypes) {
            foreach ($aliasTypes as $aliasType) {
                if ($aliasType === $typePlain) {
                    $aliasReferenceType = $aliasKey;
                }
            }
        }

        if ($aliasReferenceType) {
            return str_replace($typePlain, $aliasReferenceType, $type);
        }

        return $type;
    }

    /**
     * Windows Platform work around. Raylib functions collides with Windows's own functions and all the defines are
     * needed to bypass errors.
     *
     * @param $input
     *
     * @return array
     */
    public static function win32PreventCollision($input): array
    {
        $input[] = '/* If defined, the following flags inhibit definition of the indicated items.*/';
        $input[] = '#define NOGDICAPMASKS     // CC_*, LC_*, PC_*, CP_*, TC_*, RC_';
        $input[] = '#define NOVIRTUALKEYCODES // VK_*';
        $input[] = '#define NOWINMESSAGES     // WM_*, EM_*, LB_*, CB_*';
        $input[] = '#define NOWINSTYLES       // WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*';
        $input[] = '#define NOSYSMETRICS      // SM_*';
        $input[] = '#define NOMENUS           // MF_*';
        $input[] = '#define NOICONS           // IDI_*';
        $input[] = '#define NOKEYSTATES       // MK_*';
        $input[] = '#define NOSYSCOMMANDS     // SC_*';
        $input[] = '#define NORASTEROPS       // Binary and Tertiary raster ops';
        $input[] = '#define NOSHOWWINDOW      // SW_*';
        $input[] = '#define OEMRESOURCE       // OEM Resource values';
        $input[] = '#define NOATOM            // Atom Manager routines';
        $input[] = '#define NOCLIPBOARD       // Clipboard routines';
        $input[] = '#define NOCOLOR           // Screen colors';
        $input[] = '#define NOCTLMGR          // Control and Dialog routines';
        $input[] = '#define NODRAWTEXT        // DrawText() and DT_*';
        $input[] = '#define NOGDI             // All GDI defines and routines';
        $input[] = '#define NOKERNEL          // All KERNEL defines and routines';
        $input[] = '#define NOUSER            // All USER defines and routines';
        $input[] = '/*#define NONLS           // All NLS defines and routines*/';
        $input[] = '#define NOMB              // MB_* and MessageBox()';
        $input[] = '#define NOMEMMGR          // GMEM_*, LMEM_*, GHND, LHND, associated routines';
        $input[] = '#define NOMETAFILE        // typedef METAFILEPICT';
        $input[] = '#define NOMINMAX          // Macros min(a,b) and max(a,b)';
        $input[] = '#define NOMSG             // typedef MSG and associated routines';
        $input[] = '#define NOOPENFILE        // OpenFile(), OemToAnsi, AnsiToOem, and OF_*';
        $input[] = '#define NOSCROLL          // SB_* and scrolling routines';
        $input[] = '#define NOSERVICE         // All Service Controller routines, SERVICE_ equates, etc.';
        $input[] = '#define NOSOUND           // Sound driver routines';
        $input[] = '#define NOTEXTMETRIC      // typedef TEXTMETRIC and associated routines';
        $input[] = '#define NOWH              // SetWindowsHook and WH_*';
        $input[] = '#define NOWINOFFSETS      // GWL_*, GCL_*, associated routines';
        $input[] = '#define NOCOMM            // COMM driver routines';
        $input[] = '#define NOKANJI           // Kanji support stuff.';
        $input[] = '#define NOHELP            // Help engine interface.';
        $input[] = '#define NOPROFILER        // Profiler interface.';
        $input[] = '#define NODEFERWINDOWPOS  // DeferWindowPos routines';
        $input[] = '#define NOMCX             // Modem Configuration Extensions';
        $input[] = '#define VC_EXTRALEAN      // Maybe fix?';
        $input[] = '#define WIN32_LEAN_AND_MEAN // Maybe fix?';
        $input[] = '';
        $input[] = '/* Type required before windows.h inclusion  */';
        $input[] = 'typedef struct tagMSG* LPMSG;';
        $input[] = '';

        return $input;
    }
}
