<?php

namespace raylib {
    class Vector2 {
        public float $x;
        public float $y;
        public function __construct() { }
    }
}

namespace raylib {
    class Vector3 {
        public float $x;
        public float $y;
        public float $z;
        public function __construct() { }
    }
}

namespace raylib {
    class Vector4 {
        public float $x;
        public float $y;
        public float $z;
        public float $w;
        public function __construct() { }
    }
}

namespace raylib {
    class Matrix {
        public float $m0;
        public float $m4;
        public float $m8;
        public float $m12;
        public float $m1;
        public float $m5;
        public float $m9;
        public float $m13;
        public float $m2;
        public float $m6;
        public float $m10;
        public float $m14;
        public float $m3;
        public float $m7;
        public float $m11;
        public float $m15;
        public function __construct() { }
    }
}

namespace raylib {
    class Color {
        public int $r;
        public int $g;
        public int $b;
        public int $a;
        public function __construct() { }
        public static function LIGHTGRAY(): Color { }
        public static function GRAY(): Color { }
        public static function DARKGRAY(): Color { }
        public static function YELLOW(): Color { }
        public static function GOLD(): Color { }
        public static function ORANGE(): Color { }
        public static function PINK(): Color { }
        public static function RED(): Color { }
        public static function MAROON(): Color { }
        public static function GREEN(): Color { }
        public static function LIME(): Color { }
        public static function DARKGREEN(): Color { }
        public static function SKYBLUE(): Color { }
        public static function BLUE(): Color { }
        public static function DARKBLUE(): Color { }
        public static function PURPLE(): Color { }
        public static function VIOLET(): Color { }
        public static function DARKPURPLE(): Color { }
        public static function BEIGE(): Color { }
        public static function BROWN(): Color { }
        public static function DARKBROWN(): Color { }
        public static function WHITE(): Color { }
        public static function BLACK(): Color { }
        public static function BLANK(): Color { }
        public static function MAGENTA(): Color { }
        public static function RAYWHITE(): Color { }
    }
}

namespace raylib {
    class Rectangle {
        public float $x;
        public float $y;
        public float $width;
        public float $height;
        public function __construct() { }
    }
}

namespace raylib {
    class Image {
        public array $data;
        public int $width;
        public int $height;
        public int $mipmaps;
        public int $format;
        public function __construct() { }
    }
}

namespace raylib {
    class Texture {
        public int $id;
        public int $width;
        public int $height;
        public int $mipmaps;
        public int $format;
        public function __construct() { }
    }
}

namespace raylib {
    class RenderTexture {
        public int $id;
        public \raylib\Texture $texture;
        public \raylib\Texture $depth;
        public function __construct() { }
    }
}

namespace raylib {
    class NPatchInfo {
        public \raylib\Rectangle $source;
        public int $left;
        public int $top;
        public int $right;
        public int $bottom;
        public int $layout;
        public function __construct() { }
    }
}

namespace raylib {
    class GlyphInfo {
        public int $value;
        public int $offsetX;
        public int $offsetY;
        public int $advanceX;
        public \raylib\Image $image;
        public function __construct() { }
    }
}

namespace raylib {
    class Font {
        public int $baseSize;
        public int $glyphCount;
        public int $glyphPadding;
        public \raylib\Texture $texture;
        public \raylib\Rectangle $recs;
        public \raylib\GlyphInfo $glyphs;
        public function __construct() { }
    }
}

namespace raylib {
    class Camera3D {
        public \raylib\Vector3 $position;
        public \raylib\Vector3 $target;
        public \raylib\Vector3 $up;
        public float $fovy;
        public int $projection;
        public function __construct() { }
    }
}

namespace raylib {
    class Camera2D {
        public \raylib\Vector2 $offset;
        public \raylib\Vector2 $target;
        public float $rotation;
        public float $zoom;
        public function __construct() { }
    }
}

namespace raylib {
    class Mesh {
        public int $vertexCount;
        public int $triangleCount;
        public array $vertices;
        public array $texcoords;
        public array $texcoords2;
        public array $normals;
        public array $tangents;
        public array $colors;
        public array $indices;
        public array $animVertices;
        public array $animNormals;
        public array $boneIds;
        public array $boneWeights;
        public int $vaoId;
        public array $vboId;
        public function __construct() { }
    }
}

namespace raylib {
    class Shader {
        public int $id;
        public array $locs;
        public function __construct() { }
    }
}

namespace raylib {
    class MaterialMap {
        public \raylib\Texture $texture;
        public \raylib\Color $color;
        public float $value;
        public function __construct() { }
    }
}

namespace raylib {
    class Material {
        public \raylib\Shader $shader;
        public \raylib\MaterialMap $maps;
        public float $params;
        public function __construct() { }
    }
}

namespace raylib {
    class Transform {
        public \raylib\Vector3 $translation;
        public \raylib\Vector4 $rotation;
        public \raylib\Vector3 $scale;
        public function __construct() { }
    }
}

namespace raylib {
    class BoneInfo {
        public string $name;
        public int $parent;
        public function __construct() { }
    }
}

namespace raylib {
    class Model {
        public \raylib\Matrix $transform;
        public int $meshCount;
        public int $materialCount;
        public \raylib\Mesh $meshes;
        public \raylib\Material $materials;
        public array $meshMaterial;
        public int $boneCount;
        public \raylib\BoneInfo $bones;
        public \raylib\Transform $bindPose;
        public function __construct() { }
    }
}

namespace raylib {
    class ModelAnimation {
        public int $boneCount;
        public int $frameCount;
        public \raylib\BoneInfo $bones;
        public array $framePoses;
        public function __construct() { }
    }
}

namespace raylib {
    class Ray {
        public \raylib\Vector3 $position;
        public \raylib\Vector3 $direction;
        public function __construct() { }
    }
}

namespace raylib {
    class RayCollision {
        public bool $hit;
        public float $distance;
        public \raylib\Vector3 $point;
        public \raylib\Vector3 $normal;
        public function __construct() { }
    }
}

namespace raylib {
    class BoundingBox {
        public \raylib\Vector3 $min;
        public \raylib\Vector3 $max;
        public function __construct() { }
    }
}

namespace raylib {
    class Wave {
        public int $frameCount;
        public int $sampleRate;
        public int $sampleSize;
        public int $channels;
        public array $data;
        public function __construct() { }
    }
}

namespace raylib {
    class AudioStream {
        public \raylib\rAudioProcessor $processor;
        public int $sampleRate;
        public int $sampleSize;
        public int $channels;
        public function __construct() { }
    }
}

namespace raylib {
    class Sound {
        public \raylib\AudioStream $stream;
        public int $frameCount;
        public function __construct() { }
    }
}

namespace raylib {
    class Music {
        public \raylib\AudioStream $stream;
        public int $frameCount;
        public bool $looping;
        public int $ctxType;
        public array $ctxData;
        public function __construct() { }
    }
}

namespace raylib {
    class VrDeviceInfo {
        public int $hResolution;
        public int $vResolution;
        public float $hScreenSize;
        public float $vScreenSize;
        public float $vScreenCenter;
        public float $eyeToScreenDistance;
        public float $lensSeparationDistance;
        public float $interpupillaryDistance;
        public float $lensDistortionValues;
        public float $chromaAbCorrection;
        public function __construct() { }
    }
}

namespace raylib {
    class VrStereoConfig {
        public \raylib\Matrix $projection;
        public \raylib\Matrix $viewOffset;
        public float $leftLensCenter;
        public float $rightLensCenter;
        public float $leftScreenCenter;
        public float $rightScreenCenter;
        public float $scale;
        public float $scaleIn;
        public function __construct() { }
    }
}

namespace raylib {
    class FilePathList {
        public int $capacity;
        public int $count;
        public string $paths;
        public function __construct() { }
    }
}

namespace raylib\ConfigFlags {
    const FLAG_VSYNC_HINT = 64;
    const FLAG_FULLSCREEN_MODE = 2;
    const FLAG_WINDOW_RESIZABLE = 4;
    const FLAG_WINDOW_UNDECORATED = 8;
    const FLAG_WINDOW_HIDDEN = 128;
    const FLAG_WINDOW_MINIMIZED = 512;
    const FLAG_WINDOW_MAXIMIZED = 1024;
    const FLAG_WINDOW_UNFOCUSED = 2048;
    const FLAG_WINDOW_TOPMOST = 4096;
    const FLAG_WINDOW_ALWAYS_RUN = 256;
    const FLAG_WINDOW_TRANSPARENT = 16;
    const FLAG_WINDOW_HIGHDPI = 8192;
    const FLAG_WINDOW_MOUSE_PASSTHROUGH = 16384;
    const FLAG_MSAA_4X_HINT = 32;
    const FLAG_INTERLACED_HINT = 65536;
}

namespace raylib\TraceLogLevel {
    const LOG_ALL = 0;
    const LOG_TRACE = 1;
    const LOG_DEBUG = 2;
    const LOG_INFO = 3;
    const LOG_WARNING = 4;
    const LOG_ERROR = 5;
    const LOG_FATAL = 6;
    const LOG_NONE = 7;
}

namespace raylib\KeyboardKey {
    const KEY_NULL = 0;
    const KEY_APOSTROPHE = 39;
    const KEY_COMMA = 44;
    const KEY_MINUS = 45;
    const KEY_PERIOD = 46;
    const KEY_SLASH = 47;
    const KEY_ZERO = 48;
    const KEY_ONE = 49;
    const KEY_TWO = 50;
    const KEY_THREE = 51;
    const KEY_FOUR = 52;
    const KEY_FIVE = 53;
    const KEY_SIX = 54;
    const KEY_SEVEN = 55;
    const KEY_EIGHT = 56;
    const KEY_NINE = 57;
    const KEY_SEMICOLON = 59;
    const KEY_EQUAL = 61;
    const KEY_A = 65;
    const KEY_B = 66;
    const KEY_C = 67;
    const KEY_D = 68;
    const KEY_E = 69;
    const KEY_F = 70;
    const KEY_G = 71;
    const KEY_H = 72;
    const KEY_I = 73;
    const KEY_J = 74;
    const KEY_K = 75;
    const KEY_L = 76;
    const KEY_M = 77;
    const KEY_N = 78;
    const KEY_O = 79;
    const KEY_P = 80;
    const KEY_Q = 81;
    const KEY_R = 82;
    const KEY_S = 83;
    const KEY_T = 84;
    const KEY_U = 85;
    const KEY_V = 86;
    const KEY_W = 87;
    const KEY_X = 88;
    const KEY_Y = 89;
    const KEY_Z = 90;
    const KEY_LEFT_BRACKET = 91;
    const KEY_BACKSLASH = 92;
    const KEY_RIGHT_BRACKET = 93;
    const KEY_GRAVE = 96;
    const KEY_SPACE = 32;
    const KEY_ESCAPE = 256;
    const KEY_ENTER = 257;
    const KEY_TAB = 258;
    const KEY_BACKSPACE = 259;
    const KEY_INSERT = 260;
    const KEY_DELETE = 261;
    const KEY_RIGHT = 262;
    const KEY_LEFT = 263;
    const KEY_DOWN = 264;
    const KEY_UP = 265;
    const KEY_PAGE_UP = 266;
    const KEY_PAGE_DOWN = 267;
    const KEY_HOME = 268;
    const KEY_END = 269;
    const KEY_CAPS_LOCK = 280;
    const KEY_SCROLL_LOCK = 281;
    const KEY_NUM_LOCK = 282;
    const KEY_PRINT_SCREEN = 283;
    const KEY_PAUSE = 284;
    const KEY_F1 = 290;
    const KEY_F2 = 291;
    const KEY_F3 = 292;
    const KEY_F4 = 293;
    const KEY_F5 = 294;
    const KEY_F6 = 295;
    const KEY_F7 = 296;
    const KEY_F8 = 297;
    const KEY_F9 = 298;
    const KEY_F10 = 299;
    const KEY_F11 = 300;
    const KEY_F12 = 301;
    const KEY_LEFT_SHIFT = 340;
    const KEY_LEFT_CONTROL = 341;
    const KEY_LEFT_ALT = 342;
    const KEY_LEFT_SUPER = 343;
    const KEY_RIGHT_SHIFT = 344;
    const KEY_RIGHT_CONTROL = 345;
    const KEY_RIGHT_ALT = 346;
    const KEY_RIGHT_SUPER = 347;
    const KEY_KB_MENU = 348;
    const KEY_KP_0 = 320;
    const KEY_KP_1 = 321;
    const KEY_KP_2 = 322;
    const KEY_KP_3 = 323;
    const KEY_KP_4 = 324;
    const KEY_KP_5 = 325;
    const KEY_KP_6 = 326;
    const KEY_KP_7 = 327;
    const KEY_KP_8 = 328;
    const KEY_KP_9 = 329;
    const KEY_KP_DECIMAL = 330;
    const KEY_KP_DIVIDE = 331;
    const KEY_KP_MULTIPLY = 332;
    const KEY_KP_SUBTRACT = 333;
    const KEY_KP_ADD = 334;
    const KEY_KP_ENTER = 335;
    const KEY_KP_EQUAL = 336;
    const KEY_BACK = 4;
    const KEY_MENU = 82;
    const KEY_VOLUME_UP = 24;
    const KEY_VOLUME_DOWN = 25;
}

namespace raylib\MouseButton {
    const MOUSE_BUTTON_LEFT = 0;
    const MOUSE_BUTTON_RIGHT = 1;
    const MOUSE_BUTTON_MIDDLE = 2;
    const MOUSE_BUTTON_SIDE = 3;
    const MOUSE_BUTTON_EXTRA = 4;
    const MOUSE_BUTTON_FORWARD = 5;
    const MOUSE_BUTTON_BACK = 6;
}

namespace raylib\MouseCursor {
    const MOUSE_CURSOR_DEFAULT = 0;
    const MOUSE_CURSOR_ARROW = 1;
    const MOUSE_CURSOR_IBEAM = 2;
    const MOUSE_CURSOR_CROSSHAIR = 3;
    const MOUSE_CURSOR_POINTING_HAND = 4;
    const MOUSE_CURSOR_RESIZE_EW = 5;
    const MOUSE_CURSOR_RESIZE_NS = 6;
    const MOUSE_CURSOR_RESIZE_NWSE = 7;
    const MOUSE_CURSOR_RESIZE_NESW = 8;
    const MOUSE_CURSOR_RESIZE_ALL = 9;
    const MOUSE_CURSOR_NOT_ALLOWED = 10;
}

namespace raylib\GamepadButton {
    const GAMEPAD_BUTTON_UNKNOWN = 0;
    const GAMEPAD_BUTTON_LEFT_FACE_UP = 1;
    const GAMEPAD_BUTTON_LEFT_FACE_RIGHT = 2;
    const GAMEPAD_BUTTON_LEFT_FACE_DOWN = 3;
    const GAMEPAD_BUTTON_LEFT_FACE_LEFT = 4;
    const GAMEPAD_BUTTON_RIGHT_FACE_UP = 5;
    const GAMEPAD_BUTTON_RIGHT_FACE_RIGHT = 6;
    const GAMEPAD_BUTTON_RIGHT_FACE_DOWN = 7;
    const GAMEPAD_BUTTON_RIGHT_FACE_LEFT = 8;
    const GAMEPAD_BUTTON_LEFT_TRIGGER_1 = 9;
    const GAMEPAD_BUTTON_LEFT_TRIGGER_2 = 10;
    const GAMEPAD_BUTTON_RIGHT_TRIGGER_1 = 11;
    const GAMEPAD_BUTTON_RIGHT_TRIGGER_2 = 12;
    const GAMEPAD_BUTTON_MIDDLE_LEFT = 13;
    const GAMEPAD_BUTTON_MIDDLE = 14;
    const GAMEPAD_BUTTON_MIDDLE_RIGHT = 15;
    const GAMEPAD_BUTTON_LEFT_THUMB = 16;
    const GAMEPAD_BUTTON_RIGHT_THUMB = 17;
}

namespace raylib\GamepadAxis {
    const GAMEPAD_AXIS_LEFT_X = 0;
    const GAMEPAD_AXIS_LEFT_Y = 1;
    const GAMEPAD_AXIS_RIGHT_X = 2;
    const GAMEPAD_AXIS_RIGHT_Y = 3;
    const GAMEPAD_AXIS_LEFT_TRIGGER = 4;
    const GAMEPAD_AXIS_RIGHT_TRIGGER = 5;
}

namespace raylib\MaterialMapIndex {
    const MATERIAL_MAP_ALBEDO = 0;
    const MATERIAL_MAP_METALNESS = 1;
    const MATERIAL_MAP_NORMAL = 2;
    const MATERIAL_MAP_ROUGHNESS = 3;
    const MATERIAL_MAP_OCCLUSION = 4;
    const MATERIAL_MAP_EMISSION = 5;
    const MATERIAL_MAP_HEIGHT = 6;
    const MATERIAL_MAP_CUBEMAP = 7;
    const MATERIAL_MAP_IRRADIANCE = 8;
    const MATERIAL_MAP_PREFILTER = 9;
    const MATERIAL_MAP_BRDF = 10;
}

namespace raylib\ShaderLocationIndex {
    const SHADER_LOC_VERTEX_POSITION = 0;
    const SHADER_LOC_VERTEX_TEXCOORD01 = 1;
    const SHADER_LOC_VERTEX_TEXCOORD02 = 2;
    const SHADER_LOC_VERTEX_NORMAL = 3;
    const SHADER_LOC_VERTEX_TANGENT = 4;
    const SHADER_LOC_VERTEX_COLOR = 5;
    const SHADER_LOC_MATRIX_MVP = 6;
    const SHADER_LOC_MATRIX_VIEW = 7;
    const SHADER_LOC_MATRIX_PROJECTION = 8;
    const SHADER_LOC_MATRIX_MODEL = 9;
    const SHADER_LOC_MATRIX_NORMAL = 10;
    const SHADER_LOC_VECTOR_VIEW = 11;
    const SHADER_LOC_COLOR_DIFFUSE = 12;
    const SHADER_LOC_COLOR_SPECULAR = 13;
    const SHADER_LOC_COLOR_AMBIENT = 14;
    const SHADER_LOC_MAP_ALBEDO = 15;
    const SHADER_LOC_MAP_METALNESS = 16;
    const SHADER_LOC_MAP_NORMAL = 17;
    const SHADER_LOC_MAP_ROUGHNESS = 18;
    const SHADER_LOC_MAP_OCCLUSION = 19;
    const SHADER_LOC_MAP_EMISSION = 20;
    const SHADER_LOC_MAP_HEIGHT = 21;
    const SHADER_LOC_MAP_CUBEMAP = 22;
    const SHADER_LOC_MAP_IRRADIANCE = 23;
    const SHADER_LOC_MAP_PREFILTER = 24;
    const SHADER_LOC_MAP_BRDF = 25;
}

namespace raylib\ShaderUniformDataType {
    const SHADER_UNIFORM_FLOAT = 0;
    const SHADER_UNIFORM_VEC2 = 1;
    const SHADER_UNIFORM_VEC3 = 2;
    const SHADER_UNIFORM_VEC4 = 3;
    const SHADER_UNIFORM_INT = 4;
    const SHADER_UNIFORM_IVEC2 = 5;
    const SHADER_UNIFORM_IVEC3 = 6;
    const SHADER_UNIFORM_IVEC4 = 7;
    const SHADER_UNIFORM_SAMPLER2D = 8;
}

namespace raylib\ShaderAttributeDataType {
    const SHADER_ATTRIB_FLOAT = 0;
    const SHADER_ATTRIB_VEC2 = 1;
    const SHADER_ATTRIB_VEC3 = 2;
    const SHADER_ATTRIB_VEC4 = 3;
}

namespace raylib\PixelFormat {
    const PIXELFORMAT_UNCOMPRESSED_GRAYSCALE = 1;
    const PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA = 2;
    const PIXELFORMAT_UNCOMPRESSED_R5G6B5 = 3;
    const PIXELFORMAT_UNCOMPRESSED_R8G8B8 = 4;
    const PIXELFORMAT_UNCOMPRESSED_R5G5B5A1 = 5;
    const PIXELFORMAT_UNCOMPRESSED_R4G4B4A4 = 6;
    const PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 = 7;
    const PIXELFORMAT_UNCOMPRESSED_R32 = 8;
    const PIXELFORMAT_UNCOMPRESSED_R32G32B32 = 9;
    const PIXELFORMAT_UNCOMPRESSED_R32G32B32A32 = 10;
    const PIXELFORMAT_COMPRESSED_DXT1_RGB = 11;
    const PIXELFORMAT_COMPRESSED_DXT1_RGBA = 12;
    const PIXELFORMAT_COMPRESSED_DXT3_RGBA = 13;
    const PIXELFORMAT_COMPRESSED_DXT5_RGBA = 14;
    const PIXELFORMAT_COMPRESSED_ETC1_RGB = 15;
    const PIXELFORMAT_COMPRESSED_ETC2_RGB = 16;
    const PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA = 17;
    const PIXELFORMAT_COMPRESSED_PVRT_RGB = 18;
    const PIXELFORMAT_COMPRESSED_PVRT_RGBA = 19;
    const PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA = 20;
    const PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA = 21;
}

namespace raylib\TextureFilter {
    const TEXTURE_FILTER_POINT = 0;
    const TEXTURE_FILTER_BILINEAR = 1;
    const TEXTURE_FILTER_TRILINEAR = 2;
    const TEXTURE_FILTER_ANISOTROPIC_4X = 3;
    const TEXTURE_FILTER_ANISOTROPIC_8X = 4;
    const TEXTURE_FILTER_ANISOTROPIC_16X = 5;
}

namespace raylib\TextureWrap {
    const TEXTURE_WRAP_REPEAT = 0;
    const TEXTURE_WRAP_CLAMP = 1;
    const TEXTURE_WRAP_MIRROR_REPEAT = 2;
    const TEXTURE_WRAP_MIRROR_CLAMP = 3;
}

namespace raylib\CubemapLayout {
    const CUBEMAP_LAYOUT_AUTO_DETECT = 0;
    const CUBEMAP_LAYOUT_LINE_VERTICAL = 1;
    const CUBEMAP_LAYOUT_LINE_HORIZONTAL = 2;
    const CUBEMAP_LAYOUT_CROSS_THREE_BY_FOUR = 3;
    const CUBEMAP_LAYOUT_CROSS_FOUR_BY_THREE = 4;
    const CUBEMAP_LAYOUT_PANORAMA = 5;
}

namespace raylib\FontType {
    const FONT_DEFAULT = 0;
    const FONT_BITMAP = 1;
    const FONT_SDF = 2;
}

namespace raylib\BlendMode {
    const BLEND_ALPHA = 0;
    const BLEND_ADDITIVE = 1;
    const BLEND_MULTIPLIED = 2;
    const BLEND_ADD_COLORS = 3;
    const BLEND_SUBTRACT_COLORS = 4;
    const BLEND_ALPHA_PREMULTIPLY = 5;
    const BLEND_CUSTOM = 6;
    const BLEND_CUSTOM_SEPARATE = 7;
}

namespace raylib\Gesture {
    const GESTURE_NONE = 0;
    const GESTURE_TAP = 1;
    const GESTURE_DOUBLETAP = 2;
    const GESTURE_HOLD = 4;
    const GESTURE_DRAG = 8;
    const GESTURE_SWIPE_RIGHT = 16;
    const GESTURE_SWIPE_LEFT = 32;
    const GESTURE_SWIPE_UP = 64;
    const GESTURE_SWIPE_DOWN = 128;
    const GESTURE_PINCH_IN = 256;
    const GESTURE_PINCH_OUT = 512;
}

namespace raylib\CameraMode {
    const CAMERA_CUSTOM = 0;
    const CAMERA_FREE = 1;
    const CAMERA_ORBITAL = 2;
    const CAMERA_FIRST_PERSON = 3;
    const CAMERA_THIRD_PERSON = 4;
}

namespace raylib\CameraProjection {
    const CAMERA_PERSPECTIVE = 0;
    const CAMERA_ORTHOGRAPHIC = 1;
}

namespace raylib\NPatchLayout {
    const NPATCH_NINE_PATCH = 0;
    const NPATCH_THREE_PATCH_VERTICAL = 1;
    const NPATCH_THREE_PATCH_HORIZONTAL = 2;
}

namespace {
/*
 * Initialize window and OpenGL context
 *
 * @param int $width
 * @param int $height
 * @param string $title
 *
 */
function InitWindow(int $width, int $height, string $title): void {  }

/*
 * Check if KEY_ESCAPE pressed or Close icon pressed
 *
 *
 */
function WindowShouldClose(): bool { return false; }

/*
 * Close window and unload OpenGL context
 *
 *
 */
function CloseWindow(): void {  }

/*
 * Check if window has been initialized successfully
 *
 *
 */
function IsWindowReady(): bool { return false; }

/*
 * Check if window is currently fullscreen
 *
 *
 */
function IsWindowFullscreen(): bool { return false; }

/*
 * Check if window is currently hidden (only PLATFORM_DESKTOP)
 *
 *
 */
function IsWindowHidden(): bool { return false; }

/*
 * Check if window is currently minimized (only PLATFORM_DESKTOP)
 *
 *
 */
function IsWindowMinimized(): bool { return false; }

/*
 * Check if window is currently maximized (only PLATFORM_DESKTOP)
 *
 *
 */
function IsWindowMaximized(): bool { return false; }

/*
 * Check if window is currently focused (only PLATFORM_DESKTOP)
 *
 *
 */
function IsWindowFocused(): bool { return false; }

/*
 * Check if window has been resized last frame
 *
 *
 */
function IsWindowResized(): bool { return false; }

/*
 * Check if one specific window flag is enabled
 *
 * @param int $flag
 *
 */
function IsWindowState(int $flag): bool { return false; }

/*
 * Set window configuration state using flags (only PLATFORM_DESKTOP)
 *
 * @param int $flags
 *
 */
function SetWindowState(int $flags): void {  }

/*
 * Clear window configuration state flags
 *
 * @param int $flags
 *
 */
function ClearWindowState(int $flags): void {  }

/*
 * Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
 *
 *
 */
function ToggleFullscreen(): void {  }

/*
 * Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
 *
 *
 */
function MaximizeWindow(): void {  }

/*
 * Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
 *
 *
 */
function MinimizeWindow(): void {  }

/*
 * Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
 *
 *
 */
function RestoreWindow(): void {  }

/*
 * Set icon for window (single image, RGBA 32bit, only PLATFORM_DESKTOP)
 *
 * @param \raylib\Image $image
 *
 */
function SetWindowIcon(\raylib\Image $image): void {  }

/*
 * Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)
 *
 * @param \raylib\Image $images
 * @param int $count
 *
 */
function SetWindowIcons(\raylib\Image $images, int $count): void {  }

/*
 * Set title for window (only PLATFORM_DESKTOP)
 *
 * @param string $title
 *
 */
function SetWindowTitle(string $title): void {  }

/*
 * Set window position on screen (only PLATFORM_DESKTOP)
 *
 * @param int $x
 * @param int $y
 *
 */
function SetWindowPosition(int $x, int $y): void {  }

/*
 * Set monitor for the current window (fullscreen mode)
 *
 * @param int $monitor
 *
 */
function SetWindowMonitor(int $monitor): void {  }

/*
 * Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
 *
 * @param int $width
 * @param int $height
 *
 */
function SetWindowMinSize(int $width, int $height): void {  }

/*
 * Set window dimensions
 *
 * @param int $width
 * @param int $height
 *
 */
function SetWindowSize(int $width, int $height): void {  }

/*
 * Get current screen width
 *
 *
 */
function GetScreenWidth(): int { return 0; }

/*
 * Get current screen height
 *
 *
 */
function GetScreenHeight(): int { return 0; }

/*
 * Get number of connected monitors
 *
 *
 */
function GetMonitorCount(): int { return 0; }

/*
 * Get current connected monitor
 *
 *
 */
function GetCurrentMonitor(): int { return 0; }

/*
 * Get specified monitor position
 *
 * @param int $monitor
 *
 */
function GetMonitorPosition(int $monitor): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Get specified monitor width (current video mode used by monitor)
 *
 * @param int $monitor
 *
 */
function GetMonitorWidth(int $monitor): int { return 0; }

/*
 * Get specified monitor height (current video mode used by monitor)
 *
 * @param int $monitor
 *
 */
function GetMonitorHeight(int $monitor): int { return 0; }

/*
 * Get specified monitor physical width in millimetres
 *
 * @param int $monitor
 *
 */
function GetMonitorPhysicalWidth(int $monitor): int { return 0; }

/*
 * Get specified monitor physical height in millimetres
 *
 * @param int $monitor
 *
 */
function GetMonitorPhysicalHeight(int $monitor): int { return 0; }

/*
 * Get specified monitor refresh rate
 *
 * @param int $monitor
 *
 */
function GetMonitorRefreshRate(int $monitor): int { return 0; }

/*
 * Get window position XY on monitor
 *
 *
 */
function GetWindowPosition(): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Get window scale DPI factor
 *
 *
 */
function GetWindowScaleDPI(): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Set clipboard text content
 *
 * @param string $text
 *
 */
function SetClipboardText(string $text): void {  }

/*
 * Enable waiting for events on EndDrawing(), no automatic event polling
 *
 *
 */
function EnableEventWaiting(): void {  }

/*
 * Disable waiting for events on EndDrawing(), automatic events polling
 *
 *
 */
function DisableEventWaiting(): void {  }

/*
 * Swap back buffer with front buffer (screen drawing)
 *
 *
 */
function SwapScreenBuffer(): void {  }

/*
 * Register all input events
 *
 *
 */
function PollInputEvents(): void {  }

/*
 * Wait for some time (halt program execution)
 *
 * @param float $seconds
 *
 */
function WaitTime(float $seconds): void {  }

/*
 * Shows cursor
 *
 *
 */
function ShowCursor(): void {  }

/*
 * Hides cursor
 *
 *
 */
function HideCursor(): void {  }

/*
 * Check if cursor is not visible
 *
 *
 */
function IsCursorHidden(): bool { return false; }

/*
 * Enables cursor (unlock cursor)
 *
 *
 */
function EnableCursor(): void {  }

/*
 * Disables cursor (lock cursor)
 *
 *
 */
function DisableCursor(): void {  }

/*
 * Check if cursor is on the screen
 *
 *
 */
function IsCursorOnScreen(): bool { return false; }

/*
 * Set background color (framebuffer clear color)
 *
 * @param \raylib\Color $color
 *
 */
function ClearBackground(\raylib\Color $color): void {  }

/*
 * Setup canvas (framebuffer) to start drawing
 *
 *
 */
function BeginDrawing(): void {  }

/*
 * End canvas drawing and swap buffers (double buffering)
 *
 *
 */
function EndDrawing(): void {  }

/*
 * Begin 2D mode with custom camera (2D)
 *
 * @param \raylib\Camera2D $camera
 *
 */
function BeginMode2D(\raylib\Camera2D $camera): void {  }

/*
 * Ends 2D mode with custom camera
 *
 *
 */
function EndMode2D(): void {  }

/*
 * Begin 3D mode with custom camera (3D)
 *
 * @param \raylib\Camera3D $camera
 *
 */
function BeginMode3D(\raylib\Camera3D $camera): void {  }

/*
 * Ends 3D mode and returns to default 2D orthographic mode
 *
 *
 */
function EndMode3D(): void {  }

/*
 * Begin drawing to render texture
 *
 * @param \raylib\RenderTexture $target
 *
 */
function BeginTextureMode(\raylib\RenderTexture $target): void {  }

/*
 * Ends drawing to render texture
 *
 *
 */
function EndTextureMode(): void {  }

/*
 * Begin custom shader drawing
 *
 * @param \raylib\Shader $shader
 *
 */
function BeginShaderMode(\raylib\Shader $shader): void {  }

/*
 * End custom shader drawing (use default shader)
 *
 *
 */
function EndShaderMode(): void {  }

/*
 * Begin blending mode (alpha, additive, multiplied, subtract, custom)
 *
 * @param int $mode
 *
 */
function BeginBlendMode(int $mode): void {  }

/*
 * End blending mode (reset to default: alpha blending)
 *
 *
 */
function EndBlendMode(): void {  }

/*
 * Begin scissor mode (define screen area for following drawing)
 *
 * @param int $x
 * @param int $y
 * @param int $width
 * @param int $height
 *
 */
function BeginScissorMode(int $x, int $y, int $width, int $height): void {  }

/*
 * End scissor mode
 *
 *
 */
function EndScissorMode(): void {  }

/*
 * Begin stereo rendering (requires VR simulator)
 *
 * @param \raylib\VrStereoConfig $config
 *
 */
function BeginVrStereoMode(\raylib\VrStereoConfig $config): void {  }

/*
 * End stereo rendering (requires VR simulator)
 *
 *
 */
function EndVrStereoMode(): void {  }

/*
 * Load VR stereo config for VR simulator device parameters
 *
 * @param \raylib\VrDeviceInfo $device
 *
 */
function LoadVrStereoConfig(\raylib\VrDeviceInfo $device): \raylib\VrStereoConfig { return new \raylib\VrStereoConfig; }

/*
 * Unload VR stereo config
 *
 * @param \raylib\VrStereoConfig $config
 *
 */
function UnloadVrStereoConfig(\raylib\VrStereoConfig $config): void {  }

/*
 * Load shader from files and bind default locations
 *
 * @param string $vsFileName
 * @param string $fsFileName
 *
 */
function LoadShader(string $vsFileName, string $fsFileName): \raylib\Shader { return new \raylib\Shader; }

/*
 * Load shader from code strings and bind default locations
 *
 * @param string $vsCode
 * @param string $fsCode
 *
 */
function LoadShaderFromMemory(string $vsCode, string $fsCode): \raylib\Shader { return new \raylib\Shader; }

/*
 * Check if a shader is ready
 *
 * @param \raylib\Shader $shader
 *
 */
function IsShaderReady(\raylib\Shader $shader): bool { return false; }

/*
 * Get shader uniform location
 *
 * @param \raylib\Shader $shader
 * @param string $uniformName
 *
 */
function GetShaderLocation(\raylib\Shader $shader, string $uniformName): int { return 0; }

/*
 * Get shader attribute location
 *
 * @param \raylib\Shader $shader
 * @param string $attribName
 *
 */
function GetShaderLocationAttrib(\raylib\Shader $shader, string $attribName): int { return 0; }

/*
 * Set shader uniform value (matrix 4x4)
 *
 * @param \raylib\Shader $shader
 * @param int $locIndex
 * @param \raylib\Matrix $mat
 *
 */
function SetShaderValueMatrix(\raylib\Shader $shader, int $locIndex, \raylib\Matrix $mat): void {  }

/*
 * Set shader uniform value for texture (sampler2d)
 *
 * @param \raylib\Shader $shader
 * @param int $locIndex
 * @param \raylib\Texture $texture
 *
 */
function SetShaderValueTexture(\raylib\Shader $shader, int $locIndex, \raylib\Texture $texture): void {  }

/*
 * Unload shader from GPU memory (VRAM)
 *
 * @param \raylib\Shader $shader
 *
 */
function UnloadShader(\raylib\Shader $shader): void {  }

/*
 * Get a ray trace from mouse position
 *
 * @param \raylib\Vector2 $mousePosition
 * @param \raylib\Camera3D $camera
 *
 */
function GetMouseRay(\raylib\Vector2 $mousePosition, \raylib\Camera3D $camera): \raylib\Ray { return new \raylib\Ray; }

/*
 * Get camera transform matrix (view matrix)
 *
 * @param \raylib\Camera3D $camera
 *
 */
function GetCameraMatrix(\raylib\Camera3D $camera): \raylib\Matrix { return new \raylib\Matrix; }

/*
 * Get camera 2d transform matrix
 *
 * @param \raylib\Camera2D $camera
 *
 */
function GetCameraMatrix2D(\raylib\Camera2D $camera): \raylib\Matrix { return new \raylib\Matrix; }

/*
 * Get the screen space position for a 3d world space position
 *
 * @param \raylib\Vector3 $position
 * @param \raylib\Camera3D $camera
 *
 */
function GetWorldToScreen(\raylib\Vector3 $position, \raylib\Camera3D $camera): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Get the world space position for a 2d camera screen space position
 *
 * @param \raylib\Vector2 $position
 * @param \raylib\Camera2D $camera
 *
 */
function GetScreenToWorld2D(\raylib\Vector2 $position, \raylib\Camera2D $camera): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Get size position for a 3d world space position
 *
 * @param \raylib\Vector3 $position
 * @param \raylib\Camera3D $camera
 * @param int $width
 * @param int $height
 *
 */
function GetWorldToScreenEx(\raylib\Vector3 $position, \raylib\Camera3D $camera, int $width, int $height): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Get the screen space position for a 2d camera world space position
 *
 * @param \raylib\Vector2 $position
 * @param \raylib\Camera2D $camera
 *
 */
function GetWorldToScreen2D(\raylib\Vector2 $position, \raylib\Camera2D $camera): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Set target FPS (maximum)
 *
 * @param int $fps
 *
 */
function SetTargetFPS(int $fps): void {  }

/*
 * Get current FPS
 *
 *
 */
function GetFPS(): int { return 0; }

/*
 * Get time in seconds for last frame drawn (delta time)
 *
 *
 */
function GetFrameTime(): float { return 0.00; }

/*
 * Get elapsed time in seconds since InitWindow()
 *
 *
 */
function GetTime(): float { return 0.00; }

/*
 * Get a random value between min and max (both included)
 *
 * @param int $min
 * @param int $max
 *
 */
function GetRandomValue(int $min, int $max): int { return 0; }

/*
 * Set the seed for the random number generator
 *
 * @param int $seed
 *
 */
function SetRandomSeed(int $seed): void {  }

/*
 * Takes a screenshot of current screen (filename extension defines format)
 *
 * @param string $fileName
 *
 */
function TakeScreenshot(string $fileName): void {  }

/*
 * Setup init configuration flags (view FLAGS)
 *
 * @param int $flags
 *
 */
function SetConfigFlags(int $flags): void {  }

/*
 * Set the current threshold (minimum) log level
 *
 * @param int $logLevel
 *
 */
function SetTraceLogLevel(int $logLevel): void {  }

/*
 * Open URL with default system browser (if available)
 *
 * @param string $url
 *
 */
function OpenURL(string $url): void {  }

/*
 * Export data to code (.h), returns true on success
 *
 * @param array $data
 * @param int $size
 * @param string $fileName
 *
 */
function ExportDataAsCode(array $data, int $size, string $fileName): bool { return false; }

/*
 * Unload file text data allocated by LoadFileText()
 *
 * @param string $text
 *
 */
function UnloadFileText(string $text): void {  }

/*
 * Save text data to file (write), string must be '\0' terminated, returns true on success
 *
 * @param string $fileName
 * @param string $text
 *
 */
function SaveFileText(string $fileName, string $text): bool { return false; }

/*
 * Check if file exists
 *
 * @param string $fileName
 *
 */
function FileExists(string $fileName): bool { return false; }

/*
 * Check if a directory path exists
 *
 * @param string $dirPath
 *
 */
function DirectoryExists(string $dirPath): bool { return false; }

/*
 * Check file extension (including point: .png, .wav)
 *
 * @param string $fileName
 * @param string $ext
 *
 */
function IsFileExtension(string $fileName, string $ext): bool { return false; }

/*
 * Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
 *
 * @param string $fileName
 *
 */
function GetFileLength(string $fileName): int { return 0; }

/*
 * Change working directory, return true on success
 *
 * @param string $dir
 *
 */
function ChangeDirectory(string $dir): bool { return false; }

/*
 * Check if a given path is a file or a directory
 *
 * @param string $path
 *
 */
function IsPathFile(string $path): bool { return false; }

/*
 * Load directory filepaths
 *
 * @param string $dirPath
 *
 */
function LoadDirectoryFiles(string $dirPath): \raylib\FilePathList { return new \raylib\FilePathList; }

/*
 * Load directory filepaths with extension filtering and recursive directory scan
 *
 * @param string $basePath
 * @param string $filter
 * @param bool $scanSubdirs
 *
 */
function LoadDirectoryFilesEx(string $basePath, string $filter, bool $scanSubdirs): \raylib\FilePathList { return new \raylib\FilePathList; }

/*
 * Unload filepaths
 *
 * @param \raylib\FilePathList $files
 *
 */
function UnloadDirectoryFiles(\raylib\FilePathList $files): void {  }

/*
 * Check if a file has been dropped into window
 *
 *
 */
function IsFileDropped(): bool { return false; }

/*
 * Load dropped filepaths
 *
 *
 */
function LoadDroppedFiles(): \raylib\FilePathList { return new \raylib\FilePathList; }

/*
 * Unload dropped filepaths
 *
 * @param \raylib\FilePathList $files
 *
 */
function UnloadDroppedFiles(\raylib\FilePathList $files): void {  }

/*
 * Get file modification time (last write time)
 *
 * @param string $fileName
 *
 */
function GetFileModTime(string $fileName): int { return 0; }

/*
 * Check if a key has been pressed once
 *
 * @param int $key
 *
 */
function IsKeyPressed(int $key): bool { return false; }

/*
 * Check if a key is being pressed
 *
 * @param int $key
 *
 */
function IsKeyDown(int $key): bool { return false; }

/*
 * Check if a key has been released once
 *
 * @param int $key
 *
 */
function IsKeyReleased(int $key): bool { return false; }

/*
 * Check if a key is NOT being pressed
 *
 * @param int $key
 *
 */
function IsKeyUp(int $key): bool { return false; }

/*
 * Set a custom key to exit program (default is ESC)
 *
 * @param int $key
 *
 */
function SetExitKey(int $key): void {  }

/*
 * Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
 *
 *
 */
function GetKeyPressed(): int { return 0; }

/*
 * Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
 *
 *
 */
function GetCharPressed(): int { return 0; }

/*
 * Check if a gamepad is available
 *
 * @param int $gamepad
 *
 */
function IsGamepadAvailable(int $gamepad): bool { return false; }

/*
 * Check if a gamepad button has been pressed once
 *
 * @param int $gamepad
 * @param int $button
 *
 */
function IsGamepadButtonPressed(int $gamepad, int $button): bool { return false; }

/*
 * Check if a gamepad button is being pressed
 *
 * @param int $gamepad
 * @param int $button
 *
 */
function IsGamepadButtonDown(int $gamepad, int $button): bool { return false; }

/*
 * Check if a gamepad button has been released once
 *
 * @param int $gamepad
 * @param int $button
 *
 */
function IsGamepadButtonReleased(int $gamepad, int $button): bool { return false; }

/*
 * Check if a gamepad button is NOT being pressed
 *
 * @param int $gamepad
 * @param int $button
 *
 */
function IsGamepadButtonUp(int $gamepad, int $button): bool { return false; }

/*
 * Get the last gamepad button pressed
 *
 *
 */
function GetGamepadButtonPressed(): int { return 0; }

/*
 * Get gamepad axis count for a gamepad
 *
 * @param int $gamepad
 *
 */
function GetGamepadAxisCount(int $gamepad): int { return 0; }

/*
 * Get axis movement value for a gamepad axis
 *
 * @param int $gamepad
 * @param int $axis
 *
 */
function GetGamepadAxisMovement(int $gamepad, int $axis): float { return 0.00; }

/*
 * Set internal gamepad mappings (SDL_GameControllerDB)
 *
 * @param string $mappings
 *
 */
function SetGamepadMappings(string $mappings): int { return 0; }

/*
 * Check if a mouse button has been pressed once
 *
 * @param int $button
 *
 */
function IsMouseButtonPressed(int $button): bool { return false; }

/*
 * Check if a mouse button is being pressed
 *
 * @param int $button
 *
 */
function IsMouseButtonDown(int $button): bool { return false; }

/*
 * Check if a mouse button has been released once
 *
 * @param int $button
 *
 */
function IsMouseButtonReleased(int $button): bool { return false; }

/*
 * Check if a mouse button is NOT being pressed
 *
 * @param int $button
 *
 */
function IsMouseButtonUp(int $button): bool { return false; }

/*
 * Get mouse position X
 *
 *
 */
function GetMouseX(): int { return 0; }

/*
 * Get mouse position Y
 *
 *
 */
function GetMouseY(): int { return 0; }

/*
 * Get mouse position XY
 *
 *
 */
function GetMousePosition(): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Get mouse delta between frames
 *
 *
 */
function GetMouseDelta(): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Set mouse position XY
 *
 * @param int $x
 * @param int $y
 *
 */
function SetMousePosition(int $x, int $y): void {  }

/*
 * Set mouse offset
 *
 * @param int $offsetX
 * @param int $offsetY
 *
 */
function SetMouseOffset(int $offsetX, int $offsetY): void {  }

/*
 * Set mouse scaling
 *
 * @param float $scaleX
 * @param float $scaleY
 *
 */
function SetMouseScale(float $scaleX, float $scaleY): void {  }

/*
 * Get mouse wheel movement for X or Y, whichever is larger
 *
 *
 */
function GetMouseWheelMove(): float { return 0.00; }

/*
 * Get mouse wheel movement for both X and Y
 *
 *
 */
function GetMouseWheelMoveV(): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Set mouse cursor
 *
 * @param int $cursor
 *
 */
function SetMouseCursor(int $cursor): void {  }

/*
 * Get touch position X for touch point 0 (relative to screen size)
 *
 *
 */
function GetTouchX(): int { return 0; }

/*
 * Get touch position Y for touch point 0 (relative to screen size)
 *
 *
 */
function GetTouchY(): int { return 0; }

/*
 * Get touch position XY for a touch point index (relative to screen size)
 *
 * @param int $index
 *
 */
function GetTouchPosition(int $index): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Get touch point identifier for given index
 *
 * @param int $index
 *
 */
function GetTouchPointId(int $index): int { return 0; }

/*
 * Get number of touch points
 *
 *
 */
function GetTouchPointCount(): int { return 0; }

/*
 * Enable a set of gestures using flags
 *
 * @param int $flags
 *
 */
function SetGesturesEnabled(int $flags): void {  }

/*
 * Check if a gesture have been detected
 *
 * @param int $gesture
 *
 */
function IsGestureDetected(int $gesture): bool { return false; }

/*
 * Get latest detected gesture
 *
 *
 */
function GetGestureDetected(): int { return 0; }

/*
 * Get gesture hold time in milliseconds
 *
 *
 */
function GetGestureHoldDuration(): float { return 0.00; }

/*
 * Get gesture drag vector
 *
 *
 */
function GetGestureDragVector(): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Get gesture drag angle
 *
 *
 */
function GetGestureDragAngle(): float { return 0.00; }

/*
 * Get gesture pinch delta
 *
 *
 */
function GetGesturePinchVector(): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Get gesture pinch angle
 *
 *
 */
function GetGesturePinchAngle(): float { return 0.00; }

/*
 * Update camera position for selected mode
 *
 * @param \raylib\Camera3D &$camera
 * @param int $mode
 *
 */
function UpdateCamera(\raylib\Camera3D &$camera, int $mode): void {  }

/*
 * Update camera movement/rotation
 *
 * @param \raylib\Camera3D &$camera
 * @param \raylib\Vector3 $movement
 * @param \raylib\Vector3 $rotation
 * @param float $zoom
 *
 */
function UpdateCameraPro(\raylib\Camera3D &$camera, \raylib\Vector3 $movement, \raylib\Vector3 $rotation, float $zoom): void {  }

/*
 * Set texture and rectangle to be used on shapes drawing
 *
 * @param \raylib\Texture $texture
 * @param \raylib\Rectangle $source
 *
 */
function SetShapesTexture(\raylib\Texture $texture, \raylib\Rectangle $source): void {  }

/*
 * Draw a pixel
 *
 * @param int $posX
 * @param int $posY
 * @param \raylib\Color $color
 *
 */
function DrawPixel(int $posX, int $posY, \raylib\Color $color): void {  }

/*
 * Draw a pixel (Vector version)
 *
 * @param \raylib\Vector2 $position
 * @param \raylib\Color $color
 *
 */
function DrawPixelV(\raylib\Vector2 $position, \raylib\Color $color): void {  }

/*
 * Draw a line
 *
 * @param int $startPosX
 * @param int $startPosY
 * @param int $endPosX
 * @param int $endPosY
 * @param \raylib\Color $color
 *
 */
function DrawLine(int $startPosX, int $startPosY, int $endPosX, int $endPosY, \raylib\Color $color): void {  }

/*
 * Draw a line (Vector version)
 *
 * @param \raylib\Vector2 $startPos
 * @param \raylib\Vector2 $endPos
 * @param \raylib\Color $color
 *
 */
function DrawLineV(\raylib\Vector2 $startPos, \raylib\Vector2 $endPos, \raylib\Color $color): void {  }

/*
 * Draw a line defining thickness
 *
 * @param \raylib\Vector2 $startPos
 * @param \raylib\Vector2 $endPos
 * @param float $thick
 * @param \raylib\Color $color
 *
 */
function DrawLineEx(\raylib\Vector2 $startPos, \raylib\Vector2 $endPos, float $thick, \raylib\Color $color): void {  }

/*
 * Draw a line using cubic-bezier curves in-out
 *
 * @param \raylib\Vector2 $startPos
 * @param \raylib\Vector2 $endPos
 * @param float $thick
 * @param \raylib\Color $color
 *
 */
function DrawLineBezier(\raylib\Vector2 $startPos, \raylib\Vector2 $endPos, float $thick, \raylib\Color $color): void {  }

/*
 * Draw line using quadratic bezier curves with a control point
 *
 * @param \raylib\Vector2 $startPos
 * @param \raylib\Vector2 $endPos
 * @param \raylib\Vector2 $controlPos
 * @param float $thick
 * @param \raylib\Color $color
 *
 */
function DrawLineBezierQuad(\raylib\Vector2 $startPos, \raylib\Vector2 $endPos, \raylib\Vector2 $controlPos, float $thick, \raylib\Color $color): void {  }

/*
 * Draw line using cubic bezier curves with 2 control points
 *
 * @param \raylib\Vector2 $startPos
 * @param \raylib\Vector2 $endPos
 * @param \raylib\Vector2 $startControlPos
 * @param \raylib\Vector2 $endControlPos
 * @param float $thick
 * @param \raylib\Color $color
 *
 */
function DrawLineBezierCubic(\raylib\Vector2 $startPos, \raylib\Vector2 $endPos, \raylib\Vector2 $startControlPos, \raylib\Vector2 $endControlPos, float $thick, \raylib\Color $color): void {  }

/*
 * Draw lines sequence
 *
 * @param \raylib\Vector2 $points
 * @param int $pointCount
 * @param \raylib\Color $color
 *
 */
function DrawLineStrip(\raylib\Vector2 $points, int $pointCount, \raylib\Color $color): void {  }

/*
 * Draw a color-filled circle
 *
 * @param int $centerX
 * @param int $centerY
 * @param float $radius
 * @param \raylib\Color $color
 *
 */
function DrawCircle(int $centerX, int $centerY, float $radius, \raylib\Color $color): void {  }

/*
 * Draw a piece of a circle
 *
 * @param \raylib\Vector2 $center
 * @param float $radius
 * @param float $startAngle
 * @param float $endAngle
 * @param int $segments
 * @param \raylib\Color $color
 *
 */
function DrawCircleSector(\raylib\Vector2 $center, float $radius, float $startAngle, float $endAngle, int $segments, \raylib\Color $color): void {  }

/*
 * Draw circle sector outline
 *
 * @param \raylib\Vector2 $center
 * @param float $radius
 * @param float $startAngle
 * @param float $endAngle
 * @param int $segments
 * @param \raylib\Color $color
 *
 */
function DrawCircleSectorLines(\raylib\Vector2 $center, float $radius, float $startAngle, float $endAngle, int $segments, \raylib\Color $color): void {  }

/*
 * Draw a gradient-filled circle
 *
 * @param int $centerX
 * @param int $centerY
 * @param float $radius
 * @param \raylib\Color $color1
 * @param \raylib\Color $color2
 *
 */
function DrawCircleGradient(int $centerX, int $centerY, float $radius, \raylib\Color $color1, \raylib\Color $color2): void {  }

/*
 * Draw a color-filled circle (Vector version)
 *
 * @param \raylib\Vector2 $center
 * @param float $radius
 * @param \raylib\Color $color
 *
 */
function DrawCircleV(\raylib\Vector2 $center, float $radius, \raylib\Color $color): void {  }

/*
 * Draw circle outline
 *
 * @param int $centerX
 * @param int $centerY
 * @param float $radius
 * @param \raylib\Color $color
 *
 */
function DrawCircleLines(int $centerX, int $centerY, float $radius, \raylib\Color $color): void {  }

/*
 * Draw ellipse
 *
 * @param int $centerX
 * @param int $centerY
 * @param float $radiusH
 * @param float $radiusV
 * @param \raylib\Color $color
 *
 */
function DrawEllipse(int $centerX, int $centerY, float $radiusH, float $radiusV, \raylib\Color $color): void {  }

/*
 * Draw ellipse outline
 *
 * @param int $centerX
 * @param int $centerY
 * @param float $radiusH
 * @param float $radiusV
 * @param \raylib\Color $color
 *
 */
function DrawEllipseLines(int $centerX, int $centerY, float $radiusH, float $radiusV, \raylib\Color $color): void {  }

/*
 * Draw ring
 *
 * @param \raylib\Vector2 $center
 * @param float $innerRadius
 * @param float $outerRadius
 * @param float $startAngle
 * @param float $endAngle
 * @param int $segments
 * @param \raylib\Color $color
 *
 */
function DrawRing(\raylib\Vector2 $center, float $innerRadius, float $outerRadius, float $startAngle, float $endAngle, int $segments, \raylib\Color $color): void {  }

/*
 * Draw ring outline
 *
 * @param \raylib\Vector2 $center
 * @param float $innerRadius
 * @param float $outerRadius
 * @param float $startAngle
 * @param float $endAngle
 * @param int $segments
 * @param \raylib\Color $color
 *
 */
function DrawRingLines(\raylib\Vector2 $center, float $innerRadius, float $outerRadius, float $startAngle, float $endAngle, int $segments, \raylib\Color $color): void {  }

/*
 * Draw a color-filled rectangle
 *
 * @param int $posX
 * @param int $posY
 * @param int $width
 * @param int $height
 * @param \raylib\Color $color
 *
 */
function DrawRectangle(int $posX, int $posY, int $width, int $height, \raylib\Color $color): void {  }

/*
 * Draw a color-filled rectangle (Vector version)
 *
 * @param \raylib\Vector2 $position
 * @param \raylib\Vector2 $size
 * @param \raylib\Color $color
 *
 */
function DrawRectangleV(\raylib\Vector2 $position, \raylib\Vector2 $size, \raylib\Color $color): void {  }

/*
 * Draw a color-filled rectangle
 *
 * @param \raylib\Rectangle $rec
 * @param \raylib\Color $color
 *
 */
function DrawRectangleRec(\raylib\Rectangle $rec, \raylib\Color $color): void {  }

/*
 * Draw a color-filled rectangle with pro parameters
 *
 * @param \raylib\Rectangle $rec
 * @param \raylib\Vector2 $origin
 * @param float $rotation
 * @param \raylib\Color $color
 *
 */
function DrawRectanglePro(\raylib\Rectangle $rec, \raylib\Vector2 $origin, float $rotation, \raylib\Color $color): void {  }

/*
 * Draw a vertical-gradient-filled rectangle
 *
 * @param int $posX
 * @param int $posY
 * @param int $width
 * @param int $height
 * @param \raylib\Color $color1
 * @param \raylib\Color $color2
 *
 */
function DrawRectangleGradientV(int $posX, int $posY, int $width, int $height, \raylib\Color $color1, \raylib\Color $color2): void {  }

/*
 * Draw a horizontal-gradient-filled rectangle
 *
 * @param int $posX
 * @param int $posY
 * @param int $width
 * @param int $height
 * @param \raylib\Color $color1
 * @param \raylib\Color $color2
 *
 */
function DrawRectangleGradientH(int $posX, int $posY, int $width, int $height, \raylib\Color $color1, \raylib\Color $color2): void {  }

/*
 * Draw a gradient-filled rectangle with custom vertex colors
 *
 * @param \raylib\Rectangle $rec
 * @param \raylib\Color $col1
 * @param \raylib\Color $col2
 * @param \raylib\Color $col3
 * @param \raylib\Color $col4
 *
 */
function DrawRectangleGradientEx(\raylib\Rectangle $rec, \raylib\Color $col1, \raylib\Color $col2, \raylib\Color $col3, \raylib\Color $col4): void {  }

/*
 * Draw rectangle outline
 *
 * @param int $posX
 * @param int $posY
 * @param int $width
 * @param int $height
 * @param \raylib\Color $color
 *
 */
function DrawRectangleLines(int $posX, int $posY, int $width, int $height, \raylib\Color $color): void {  }

/*
 * Draw rectangle outline with extended parameters
 *
 * @param \raylib\Rectangle $rec
 * @param float $lineThick
 * @param \raylib\Color $color
 *
 */
function DrawRectangleLinesEx(\raylib\Rectangle $rec, float $lineThick, \raylib\Color $color): void {  }

/*
 * Draw rectangle with rounded edges
 *
 * @param \raylib\Rectangle $rec
 * @param float $roundness
 * @param int $segments
 * @param \raylib\Color $color
 *
 */
function DrawRectangleRounded(\raylib\Rectangle $rec, float $roundness, int $segments, \raylib\Color $color): void {  }

/*
 * Draw rectangle with rounded edges outline
 *
 * @param \raylib\Rectangle $rec
 * @param float $roundness
 * @param int $segments
 * @param float $lineThick
 * @param \raylib\Color $color
 *
 */
function DrawRectangleRoundedLines(\raylib\Rectangle $rec, float $roundness, int $segments, float $lineThick, \raylib\Color $color): void {  }

/*
 * Draw a color-filled triangle (vertex in counter-clockwise order!)
 *
 * @param \raylib\Vector2 $v1
 * @param \raylib\Vector2 $v2
 * @param \raylib\Vector2 $v3
 * @param \raylib\Color $color
 *
 */
function DrawTriangle(\raylib\Vector2 $v1, \raylib\Vector2 $v2, \raylib\Vector2 $v3, \raylib\Color $color): void {  }

/*
 * Draw triangle outline (vertex in counter-clockwise order!)
 *
 * @param \raylib\Vector2 $v1
 * @param \raylib\Vector2 $v2
 * @param \raylib\Vector2 $v3
 * @param \raylib\Color $color
 *
 */
function DrawTriangleLines(\raylib\Vector2 $v1, \raylib\Vector2 $v2, \raylib\Vector2 $v3, \raylib\Color $color): void {  }

/*
 * Draw a triangle fan defined by points (first vertex is the center)
 *
 * @param \raylib\Vector2 $points
 * @param int $pointCount
 * @param \raylib\Color $color
 *
 */
function DrawTriangleFan(\raylib\Vector2 $points, int $pointCount, \raylib\Color $color): void {  }

/*
 * Draw a triangle strip defined by points
 *
 * @param \raylib\Vector2 $points
 * @param int $pointCount
 * @param \raylib\Color $color
 *
 */
function DrawTriangleStrip(\raylib\Vector2 $points, int $pointCount, \raylib\Color $color): void {  }

/*
 * Draw a regular polygon (Vector version)
 *
 * @param \raylib\Vector2 $center
 * @param int $sides
 * @param float $radius
 * @param float $rotation
 * @param \raylib\Color $color
 *
 */
function DrawPoly(\raylib\Vector2 $center, int $sides, float $radius, float $rotation, \raylib\Color $color): void {  }

/*
 * Draw a polygon outline of n sides
 *
 * @param \raylib\Vector2 $center
 * @param int $sides
 * @param float $radius
 * @param float $rotation
 * @param \raylib\Color $color
 *
 */
function DrawPolyLines(\raylib\Vector2 $center, int $sides, float $radius, float $rotation, \raylib\Color $color): void {  }

/*
 * Draw a polygon outline of n sides with extended parameters
 *
 * @param \raylib\Vector2 $center
 * @param int $sides
 * @param float $radius
 * @param float $rotation
 * @param float $lineThick
 * @param \raylib\Color $color
 *
 */
function DrawPolyLinesEx(\raylib\Vector2 $center, int $sides, float $radius, float $rotation, float $lineThick, \raylib\Color $color): void {  }

/*
 * Check collision between two rectangles
 *
 * @param \raylib\Rectangle $rec1
 * @param \raylib\Rectangle $rec2
 *
 */
function CheckCollisionRecs(\raylib\Rectangle $rec1, \raylib\Rectangle $rec2): bool { return false; }

/*
 * Check collision between two circles
 *
 * @param \raylib\Vector2 $center1
 * @param float $radius1
 * @param \raylib\Vector2 $center2
 * @param float $radius2
 *
 */
function CheckCollisionCircles(\raylib\Vector2 $center1, float $radius1, \raylib\Vector2 $center2, float $radius2): bool { return false; }

/*
 * Check collision between circle and rectangle
 *
 * @param \raylib\Vector2 $center
 * @param float $radius
 * @param \raylib\Rectangle $rec
 *
 */
function CheckCollisionCircleRec(\raylib\Vector2 $center, float $radius, \raylib\Rectangle $rec): bool { return false; }

/*
 * Check if point is inside rectangle
 *
 * @param \raylib\Vector2 $point
 * @param \raylib\Rectangle $rec
 *
 */
function CheckCollisionPointRec(\raylib\Vector2 $point, \raylib\Rectangle $rec): bool { return false; }

/*
 * Check if point is inside circle
 *
 * @param \raylib\Vector2 $point
 * @param \raylib\Vector2 $center
 * @param float $radius
 *
 */
function CheckCollisionPointCircle(\raylib\Vector2 $point, \raylib\Vector2 $center, float $radius): bool { return false; }

/*
 * Check if point is inside a triangle
 *
 * @param \raylib\Vector2 $point
 * @param \raylib\Vector2 $p1
 * @param \raylib\Vector2 $p2
 * @param \raylib\Vector2 $p3
 *
 */
function CheckCollisionPointTriangle(\raylib\Vector2 $point, \raylib\Vector2 $p1, \raylib\Vector2 $p2, \raylib\Vector2 $p3): bool { return false; }

/*
 * Check if point is within a polygon described by array of vertices
 *
 * @param \raylib\Vector2 $point
 * @param \raylib\Vector2 $points
 * @param int $pointCount
 *
 */
function CheckCollisionPointPoly(\raylib\Vector2 $point, \raylib\Vector2 $points, int $pointCount): bool { return false; }

/*
 * Check the collision between two lines defined by two points each, returns collision point by reference
 *
 * @param \raylib\Vector2 $startPos1
 * @param \raylib\Vector2 $endPos1
 * @param \raylib\Vector2 $startPos2
 * @param \raylib\Vector2 $endPos2
 * @param \raylib\Vector2 &$collisionPoint
 *
 */
function CheckCollisionLines(\raylib\Vector2 $startPos1, \raylib\Vector2 $endPos1, \raylib\Vector2 $startPos2, \raylib\Vector2 $endPos2, \raylib\Vector2 &$collisionPoint): bool { return false; }

/*
 * Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
 *
 * @param \raylib\Vector2 $point
 * @param \raylib\Vector2 $p1
 * @param \raylib\Vector2 $p2
 * @param int $threshold
 *
 */
function CheckCollisionPointLine(\raylib\Vector2 $point, \raylib\Vector2 $p1, \raylib\Vector2 $p2, int $threshold): bool { return false; }

/*
 * Get collision rectangle for two rectangles collision
 *
 * @param \raylib\Rectangle $rec1
 * @param \raylib\Rectangle $rec2
 *
 */
function GetCollisionRec(\raylib\Rectangle $rec1, \raylib\Rectangle $rec2): \raylib\Rectangle { return new \raylib\Rectangle; }

/*
 * Load image from file into CPU memory (RAM)
 *
 * @param string $fileName
 *
 */
function LoadImage(string $fileName): \raylib\Image { return new \raylib\Image; }

/*
 * Load image from RAW file data
 *
 * @param string $fileName
 * @param int $width
 * @param int $height
 * @param int $format
 * @param int $headerSize
 *
 */
function LoadImageRaw(string $fileName, int $width, int $height, int $format, int $headerSize): \raylib\Image { return new \raylib\Image; }

/*
 * Load image sequence from file (frames appended to image.data)
 *
 * @param string $fileName
 * @param array $frames
 *
 */
function LoadImageAnim(string $fileName, array $frames): \raylib\Image { return new \raylib\Image; }

/*
 * Load image from memory buffer, fileType refers to extension: i.e. '.png'
 *
 * @param string $fileType
 * @param array $fileData
 * @param int $dataSize
 *
 */
function LoadImageFromMemory(string $fileType, array $fileData, int $dataSize): \raylib\Image { return new \raylib\Image; }

/*
 * Load image from GPU texture data
 *
 * @param \raylib\Texture $texture
 *
 */
function LoadImageFromTexture(\raylib\Texture $texture): \raylib\Image { return new \raylib\Image; }

/*
 * Load image from screen buffer and (screenshot)
 *
 *
 */
function LoadImageFromScreen(): \raylib\Image { return new \raylib\Image; }

/*
 * Check if an image is ready
 *
 * @param \raylib\Image $image
 *
 */
function IsImageReady(\raylib\Image $image): bool { return false; }

/*
 * Unload image from CPU memory (RAM)
 *
 * @param \raylib\Image $image
 *
 */
function UnloadImage(\raylib\Image $image): void {  }

/*
 * Export image data to file, returns true on success
 *
 * @param \raylib\Image $image
 * @param string $fileName
 *
 */
function ExportImage(\raylib\Image $image, string $fileName): bool { return false; }

/*
 * Export image as code file defining an array of bytes, returns true on success
 *
 * @param \raylib\Image $image
 * @param string $fileName
 *
 */
function ExportImageAsCode(\raylib\Image $image, string $fileName): bool { return false; }

/*
 * Generate image: plain color
 *
 * @param int $width
 * @param int $height
 * @param \raylib\Color $color
 *
 */
function GenImageColor(int $width, int $height, \raylib\Color $color): \raylib\Image { return new \raylib\Image; }

/*
 * Generate image: vertical gradient
 *
 * @param int $width
 * @param int $height
 * @param \raylib\Color $top
 * @param \raylib\Color $bottom
 *
 */
function GenImageGradientV(int $width, int $height, \raylib\Color $top, \raylib\Color $bottom): \raylib\Image { return new \raylib\Image; }

/*
 * Generate image: horizontal gradient
 *
 * @param int $width
 * @param int $height
 * @param \raylib\Color $left
 * @param \raylib\Color $right
 *
 */
function GenImageGradientH(int $width, int $height, \raylib\Color $left, \raylib\Color $right): \raylib\Image { return new \raylib\Image; }

/*
 * Generate image: radial gradient
 *
 * @param int $width
 * @param int $height
 * @param float $density
 * @param \raylib\Color $inner
 * @param \raylib\Color $outer
 *
 */
function GenImageGradientRadial(int $width, int $height, float $density, \raylib\Color $inner, \raylib\Color $outer): \raylib\Image { return new \raylib\Image; }

/*
 * Generate image: checked
 *
 * @param int $width
 * @param int $height
 * @param int $checksX
 * @param int $checksY
 * @param \raylib\Color $col1
 * @param \raylib\Color $col2
 *
 */
function GenImageChecked(int $width, int $height, int $checksX, int $checksY, \raylib\Color $col1, \raylib\Color $col2): \raylib\Image { return new \raylib\Image; }

/*
 * Generate image: white noise
 *
 * @param int $width
 * @param int $height
 * @param float $factor
 *
 */
function GenImageWhiteNoise(int $width, int $height, float $factor): \raylib\Image { return new \raylib\Image; }

/*
 * Generate image: perlin noise
 *
 * @param int $width
 * @param int $height
 * @param int $offsetX
 * @param int $offsetY
 * @param float $scale
 *
 */
function GenImagePerlinNoise(int $width, int $height, int $offsetX, int $offsetY, float $scale): \raylib\Image { return new \raylib\Image; }

/*
 * Generate image: cellular algorithm, bigger tileSize means bigger cells
 *
 * @param int $width
 * @param int $height
 * @param int $tileSize
 *
 */
function GenImageCellular(int $width, int $height, int $tileSize): \raylib\Image { return new \raylib\Image; }

/*
 * Generate image: grayscale image from text data
 *
 * @param int $width
 * @param int $height
 * @param string $text
 *
 */
function GenImageText(int $width, int $height, string $text): \raylib\Image { return new \raylib\Image; }

/*
 * Create an image duplicate (useful for transformations)
 *
 * @param \raylib\Image $image
 *
 */
function ImageCopy(\raylib\Image $image): \raylib\Image { return new \raylib\Image; }

/*
 * Create an image from another image piece
 *
 * @param \raylib\Image $image
 * @param \raylib\Rectangle $rec
 *
 */
function ImageFromImage(\raylib\Image $image, \raylib\Rectangle $rec): \raylib\Image { return new \raylib\Image; }

/*
 * Create an image from text (default font)
 *
 * @param string $text
 * @param int $fontSize
 * @param \raylib\Color $color
 *
 */
function ImageText(string $text, int $fontSize, \raylib\Color $color): \raylib\Image { return new \raylib\Image; }

/*
 * Create an image from text (custom sprite font)
 *
 * @param \raylib\Font $font
 * @param string $text
 * @param float $fontSize
 * @param float $spacing
 * @param \raylib\Color $tint
 *
 */
function ImageTextEx(\raylib\Font $font, string $text, float $fontSize, float $spacing, \raylib\Color $tint): \raylib\Image { return new \raylib\Image; }

/*
 * Convert image data to desired format
 *
 * @param \raylib\Image &$image
 * @param int $newFormat
 *
 */
function ImageFormat(\raylib\Image &$image, int $newFormat): void {  }

/*
 * Convert image to POT (power-of-two)
 *
 * @param \raylib\Image &$image
 * @param \raylib\Color $fill
 *
 */
function ImageToPOT(\raylib\Image &$image, \raylib\Color $fill): void {  }

/*
 * Crop an image to a defined rectangle
 *
 * @param \raylib\Image &$image
 * @param \raylib\Rectangle $crop
 *
 */
function ImageCrop(\raylib\Image &$image, \raylib\Rectangle $crop): void {  }

/*
 * Crop image depending on alpha value
 *
 * @param \raylib\Image &$image
 * @param float $threshold
 *
 */
function ImageAlphaCrop(\raylib\Image &$image, float $threshold): void {  }

/*
 * Clear alpha channel to desired color
 *
 * @param \raylib\Image &$image
 * @param \raylib\Color $color
 * @param float $threshold
 *
 */
function ImageAlphaClear(\raylib\Image &$image, \raylib\Color $color, float $threshold): void {  }

/*
 * Apply alpha mask to image
 *
 * @param \raylib\Image &$image
 * @param \raylib\Image $alphaMask
 *
 */
function ImageAlphaMask(\raylib\Image &$image, \raylib\Image $alphaMask): void {  }

/*
 * Premultiply alpha channel
 *
 * @param \raylib\Image &$image
 *
 */
function ImageAlphaPremultiply(\raylib\Image &$image): void {  }

/*
 * Apply Gaussian blur using a box blur approximation
 *
 * @param \raylib\Image &$image
 * @param int $blurSize
 *
 */
function ImageBlurGaussian(\raylib\Image &$image, int $blurSize): void {  }

/*
 * Resize image (Bicubic scaling algorithm)
 *
 * @param \raylib\Image &$image
 * @param int $newWidth
 * @param int $newHeight
 *
 */
function ImageResize(\raylib\Image &$image, int $newWidth, int $newHeight): void {  }

/*
 * Resize image (Nearest-Neighbor scaling algorithm)
 *
 * @param \raylib\Image &$image
 * @param int $newWidth
 * @param int $newHeight
 *
 */
function ImageResizeNN(\raylib\Image &$image, int $newWidth, int $newHeight): void {  }

/*
 * Resize canvas and fill with color
 *
 * @param \raylib\Image &$image
 * @param int $newWidth
 * @param int $newHeight
 * @param int $offsetX
 * @param int $offsetY
 * @param \raylib\Color $fill
 *
 */
function ImageResizeCanvas(\raylib\Image &$image, int $newWidth, int $newHeight, int $offsetX, int $offsetY, \raylib\Color $fill): void {  }

/*
 * Compute all mipmap levels for a provided image
 *
 * @param \raylib\Image &$image
 *
 */
function ImageMipmaps(\raylib\Image &$image): void {  }

/*
 * Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
 *
 * @param \raylib\Image &$image
 * @param int $rBpp
 * @param int $gBpp
 * @param int $bBpp
 * @param int $aBpp
 *
 */
function ImageDither(\raylib\Image &$image, int $rBpp, int $gBpp, int $bBpp, int $aBpp): void {  }

/*
 * Flip image vertically
 *
 * @param \raylib\Image &$image
 *
 */
function ImageFlipVertical(\raylib\Image &$image): void {  }

/*
 * Flip image horizontally
 *
 * @param \raylib\Image &$image
 *
 */
function ImageFlipHorizontal(\raylib\Image &$image): void {  }

/*
 * Rotate image clockwise 90deg
 *
 * @param \raylib\Image &$image
 *
 */
function ImageRotateCW(\raylib\Image &$image): void {  }

/*
 * Rotate image counter-clockwise 90deg
 *
 * @param \raylib\Image &$image
 *
 */
function ImageRotateCCW(\raylib\Image &$image): void {  }

/*
 * Modify image color: tint
 *
 * @param \raylib\Image &$image
 * @param \raylib\Color $color
 *
 */
function ImageColorTint(\raylib\Image &$image, \raylib\Color $color): void {  }

/*
 * Modify image color: invert
 *
 * @param \raylib\Image &$image
 *
 */
function ImageColorInvert(\raylib\Image &$image): void {  }

/*
 * Modify image color: grayscale
 *
 * @param \raylib\Image &$image
 *
 */
function ImageColorGrayscale(\raylib\Image &$image): void {  }

/*
 * Modify image color: contrast (-100 to 100)
 *
 * @param \raylib\Image &$image
 * @param float $contrast
 *
 */
function ImageColorContrast(\raylib\Image &$image, float $contrast): void {  }

/*
 * Modify image color: brightness (-255 to 255)
 *
 * @param \raylib\Image &$image
 * @param int $brightness
 *
 */
function ImageColorBrightness(\raylib\Image &$image, int $brightness): void {  }

/*
 * Modify image color: replace color
 *
 * @param \raylib\Image &$image
 * @param \raylib\Color $color
 * @param \raylib\Color $replace
 *
 */
function ImageColorReplace(\raylib\Image &$image, \raylib\Color $color, \raylib\Color $replace): void {  }

/*
 * Unload color data loaded with LoadImageColors()
 *
 * @param \raylib\Color &$colors
 *
 */
function UnloadImageColors(\raylib\Color &$colors): void {  }

/*
 * Unload colors palette loaded with LoadImagePalette()
 *
 * @param \raylib\Color &$colors
 *
 */
function UnloadImagePalette(\raylib\Color &$colors): void {  }

/*
 * Get image alpha border rectangle
 *
 * @param \raylib\Image $image
 * @param float $threshold
 *
 */
function GetImageAlphaBorder(\raylib\Image $image, float $threshold): \raylib\Rectangle { return new \raylib\Rectangle; }

/*
 * Get image pixel color at (x, y) position
 *
 * @param \raylib\Image $image
 * @param int $x
 * @param int $y
 *
 */
function GetImageColor(\raylib\Image $image, int $x, int $y): \raylib\Color { return new \raylib\Color; }

/*
 * Clear image background with given color
 *
 * @param \raylib\Image &$dst
 * @param \raylib\Color $color
 *
 */
function ImageClearBackground(\raylib\Image &$dst, \raylib\Color $color): void {  }

/*
 * Draw pixel within an image
 *
 * @param \raylib\Image &$dst
 * @param int $posX
 * @param int $posY
 * @param \raylib\Color $color
 *
 */
function ImageDrawPixel(\raylib\Image &$dst, int $posX, int $posY, \raylib\Color $color): void {  }

/*
 * Draw pixel within an image (Vector version)
 *
 * @param \raylib\Image &$dst
 * @param \raylib\Vector2 $position
 * @param \raylib\Color $color
 *
 */
function ImageDrawPixelV(\raylib\Image &$dst, \raylib\Vector2 $position, \raylib\Color $color): void {  }

/*
 * Draw line within an image
 *
 * @param \raylib\Image &$dst
 * @param int $startPosX
 * @param int $startPosY
 * @param int $endPosX
 * @param int $endPosY
 * @param \raylib\Color $color
 *
 */
function ImageDrawLine(\raylib\Image &$dst, int $startPosX, int $startPosY, int $endPosX, int $endPosY, \raylib\Color $color): void {  }

/*
 * Draw line within an image (Vector version)
 *
 * @param \raylib\Image &$dst
 * @param \raylib\Vector2 $start
 * @param \raylib\Vector2 $end
 * @param \raylib\Color $color
 *
 */
function ImageDrawLineV(\raylib\Image &$dst, \raylib\Vector2 $start, \raylib\Vector2 $end, \raylib\Color $color): void {  }

/*
 * Draw a filled circle within an image
 *
 * @param \raylib\Image &$dst
 * @param int $centerX
 * @param int $centerY
 * @param int $radius
 * @param \raylib\Color $color
 *
 */
function ImageDrawCircle(\raylib\Image &$dst, int $centerX, int $centerY, int $radius, \raylib\Color $color): void {  }

/*
 * Draw a filled circle within an image (Vector version)
 *
 * @param \raylib\Image &$dst
 * @param \raylib\Vector2 $center
 * @param int $radius
 * @param \raylib\Color $color
 *
 */
function ImageDrawCircleV(\raylib\Image &$dst, \raylib\Vector2 $center, int $radius, \raylib\Color $color): void {  }

/*
 * Draw circle outline within an image
 *
 * @param \raylib\Image &$dst
 * @param int $centerX
 * @param int $centerY
 * @param int $radius
 * @param \raylib\Color $color
 *
 */
function ImageDrawCircleLines(\raylib\Image &$dst, int $centerX, int $centerY, int $radius, \raylib\Color $color): void {  }

/*
 * Draw circle outline within an image (Vector version)
 *
 * @param \raylib\Image &$dst
 * @param \raylib\Vector2 $center
 * @param int $radius
 * @param \raylib\Color $color
 *
 */
function ImageDrawCircleLinesV(\raylib\Image &$dst, \raylib\Vector2 $center, int $radius, \raylib\Color $color): void {  }

/*
 * Draw rectangle within an image
 *
 * @param \raylib\Image &$dst
 * @param int $posX
 * @param int $posY
 * @param int $width
 * @param int $height
 * @param \raylib\Color $color
 *
 */
function ImageDrawRectangle(\raylib\Image &$dst, int $posX, int $posY, int $width, int $height, \raylib\Color $color): void {  }

/*
 * Draw rectangle within an image (Vector version)
 *
 * @param \raylib\Image &$dst
 * @param \raylib\Vector2 $position
 * @param \raylib\Vector2 $size
 * @param \raylib\Color $color
 *
 */
function ImageDrawRectangleV(\raylib\Image &$dst, \raylib\Vector2 $position, \raylib\Vector2 $size, \raylib\Color $color): void {  }

/*
 * Draw rectangle within an image
 *
 * @param \raylib\Image &$dst
 * @param \raylib\Rectangle $rec
 * @param \raylib\Color $color
 *
 */
function ImageDrawRectangleRec(\raylib\Image &$dst, \raylib\Rectangle $rec, \raylib\Color $color): void {  }

/*
 * Draw rectangle lines within an image
 *
 * @param \raylib\Image &$dst
 * @param \raylib\Rectangle $rec
 * @param int $thick
 * @param \raylib\Color $color
 *
 */
function ImageDrawRectangleLines(\raylib\Image &$dst, \raylib\Rectangle $rec, int $thick, \raylib\Color $color): void {  }

/*
 * Draw a source image within a destination image (tint applied to source)
 *
 * @param \raylib\Image &$dst
 * @param \raylib\Image $src
 * @param \raylib\Rectangle $srcRec
 * @param \raylib\Rectangle $dstRec
 * @param \raylib\Color $tint
 *
 */
function ImageDraw(\raylib\Image &$dst, \raylib\Image $src, \raylib\Rectangle $srcRec, \raylib\Rectangle $dstRec, \raylib\Color $tint): void {  }

/*
 * Draw text (using default font) within an image (destination)
 *
 * @param \raylib\Image &$dst
 * @param string $text
 * @param int $posX
 * @param int $posY
 * @param int $fontSize
 * @param \raylib\Color $color
 *
 */
function ImageDrawText(\raylib\Image &$dst, string $text, int $posX, int $posY, int $fontSize, \raylib\Color $color): void {  }

/*
 * Draw text (custom sprite font) within an image (destination)
 *
 * @param \raylib\Image &$dst
 * @param \raylib\Font $font
 * @param string $text
 * @param \raylib\Vector2 $position
 * @param float $fontSize
 * @param float $spacing
 * @param \raylib\Color $tint
 *
 */
function ImageDrawTextEx(\raylib\Image &$dst, \raylib\Font $font, string $text, \raylib\Vector2 $position, float $fontSize, float $spacing, \raylib\Color $tint): void {  }

/*
 * Load texture from file into GPU memory (VRAM)
 *
 * @param string $fileName
 *
 */
function LoadTexture(string $fileName): \raylib\Texture { return new \raylib\Texture; }

/*
 * Load texture from image data
 *
 * @param \raylib\Image $image
 *
 */
function LoadTextureFromImage(\raylib\Image $image): \raylib\Texture { return new \raylib\Texture; }

/*
 * Load cubemap from image, multiple image cubemap layouts supported
 *
 * @param \raylib\Image $image
 * @param int $layout
 *
 */
function LoadTextureCubemap(\raylib\Image $image, int $layout): \raylib\Texture { return new \raylib\Texture; }

/*
 * Load texture for rendering (framebuffer)
 *
 * @param int $width
 * @param int $height
 *
 */
function LoadRenderTexture(int $width, int $height): \raylib\RenderTexture { return new \raylib\RenderTexture; }

/*
 * Check if a texture is ready
 *
 * @param \raylib\Texture $texture
 *
 */
function IsTextureReady(\raylib\Texture $texture): bool { return false; }

/*
 * Unload texture from GPU memory (VRAM)
 *
 * @param \raylib\Texture $texture
 *
 */
function UnloadTexture(\raylib\Texture $texture): void {  }

/*
 * Check if a render texture is ready
 *
 * @param \raylib\RenderTexture $target
 *
 */
function IsRenderTextureReady(\raylib\RenderTexture $target): bool { return false; }

/*
 * Unload render texture from GPU memory (VRAM)
 *
 * @param \raylib\RenderTexture $target
 *
 */
function UnloadRenderTexture(\raylib\RenderTexture $target): void {  }

/*
 * Generate GPU mipmaps for a texture
 *
 * @param \raylib\Texture &$texture
 *
 */
function GenTextureMipmaps(\raylib\Texture &$texture): void {  }

/*
 * Set texture scaling filter mode
 *
 * @param \raylib\Texture $texture
 * @param int $filter
 *
 */
function SetTextureFilter(\raylib\Texture $texture, int $filter): void {  }

/*
 * Set texture wrapping mode
 *
 * @param \raylib\Texture $texture
 * @param int $wrap
 *
 */
function SetTextureWrap(\raylib\Texture $texture, int $wrap): void {  }

/*
 * Draw a Texture2D
 *
 * @param \raylib\Texture $texture
 * @param int $posX
 * @param int $posY
 * @param \raylib\Color $tint
 *
 */
function DrawTexture(\raylib\Texture $texture, int $posX, int $posY, \raylib\Color $tint): void {  }

/*
 * Draw a Texture2D with position defined as Vector2
 *
 * @param \raylib\Texture $texture
 * @param \raylib\Vector2 $position
 * @param \raylib\Color $tint
 *
 */
function DrawTextureV(\raylib\Texture $texture, \raylib\Vector2 $position, \raylib\Color $tint): void {  }

/*
 * Draw a Texture2D with extended parameters
 *
 * @param \raylib\Texture $texture
 * @param \raylib\Vector2 $position
 * @param float $rotation
 * @param float $scale
 * @param \raylib\Color $tint
 *
 */
function DrawTextureEx(\raylib\Texture $texture, \raylib\Vector2 $position, float $rotation, float $scale, \raylib\Color $tint): void {  }

/*
 * Draw a part of a texture defined by a rectangle
 *
 * @param \raylib\Texture $texture
 * @param \raylib\Rectangle $source
 * @param \raylib\Vector2 $position
 * @param \raylib\Color $tint
 *
 */
function DrawTextureRec(\raylib\Texture $texture, \raylib\Rectangle $source, \raylib\Vector2 $position, \raylib\Color $tint): void {  }

/*
 * Draw a part of a texture defined by a rectangle with 'pro' parameters
 *
 * @param \raylib\Texture $texture
 * @param \raylib\Rectangle $source
 * @param \raylib\Rectangle $dest
 * @param \raylib\Vector2 $origin
 * @param float $rotation
 * @param \raylib\Color $tint
 *
 */
function DrawTexturePro(\raylib\Texture $texture, \raylib\Rectangle $source, \raylib\Rectangle $dest, \raylib\Vector2 $origin, float $rotation, \raylib\Color $tint): void {  }

/*
 * Draws a texture (or part of it) that stretches or shrinks nicely
 *
 * @param \raylib\Texture $texture
 * @param \raylib\NPatchInfo $nPatchInfo
 * @param \raylib\Rectangle $dest
 * @param \raylib\Vector2 $origin
 * @param float $rotation
 * @param \raylib\Color $tint
 *
 */
function DrawTextureNPatch(\raylib\Texture $texture, \raylib\NPatchInfo $nPatchInfo, \raylib\Rectangle $dest, \raylib\Vector2 $origin, float $rotation, \raylib\Color $tint): void {  }

/*
 * Get color with alpha applied, alpha goes from 0.0f to 1.0f
 *
 * @param \raylib\Color $color
 * @param float $alpha
 *
 */
function Fade(\raylib\Color $color, float $alpha): \raylib\Color { return new \raylib\Color; }

/*
 * Get hexadecimal value for a Color
 *
 * @param \raylib\Color $color
 *
 */
function ColorToInt(\raylib\Color $color): int { return 0; }

/*
 * Get Color normalized as float [0..1]
 *
 * @param \raylib\Color $color
 *
 */
function ColorNormalize(\raylib\Color $color): \raylib\Vector4 { return new \raylib\Vector4; }

/*
 * Get Color from normalized values [0..1]
 *
 * @param \raylib\Vector4 $normalized
 *
 */
function ColorFromNormalized(\raylib\Vector4 $normalized): \raylib\Color { return new \raylib\Color; }

/*
 * Get HSV values for a Color, hue [0..360], saturation/value [0..1]
 *
 * @param \raylib\Color $color
 *
 */
function ColorToHSV(\raylib\Color $color): \raylib\Vector3 { return new \raylib\Vector3; }

/*
 * Get a Color from HSV values, hue [0..360], saturation/value [0..1]
 *
 * @param float $hue
 * @param float $saturation
 * @param float $value
 *
 */
function ColorFromHSV(float $hue, float $saturation, float $value): \raylib\Color { return new \raylib\Color; }

/*
 * Get color multiplied with another color
 *
 * @param \raylib\Color $color
 * @param \raylib\Color $tint
 *
 */
function ColorTint(\raylib\Color $color, \raylib\Color $tint): \raylib\Color { return new \raylib\Color; }

/*
 * Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
 *
 * @param \raylib\Color $color
 * @param float $factor
 *
 */
function ColorBrightness(\raylib\Color $color, float $factor): \raylib\Color { return new \raylib\Color; }

/*
 * Get color with contrast correction, contrast values between -1.0f and 1.0f
 *
 * @param \raylib\Color $color
 * @param float $contrast
 *
 */
function ColorContrast(\raylib\Color $color, float $contrast): \raylib\Color { return new \raylib\Color; }

/*
 * Get color with alpha applied, alpha goes from 0.0f to 1.0f
 *
 * @param \raylib\Color $color
 * @param float $alpha
 *
 */
function ColorAlpha(\raylib\Color $color, float $alpha): \raylib\Color { return new \raylib\Color; }

/*
 * Get src alpha-blended into dst color with tint
 *
 * @param \raylib\Color $dst
 * @param \raylib\Color $src
 * @param \raylib\Color $tint
 *
 */
function ColorAlphaBlend(\raylib\Color $dst, \raylib\Color $src, \raylib\Color $tint): \raylib\Color { return new \raylib\Color; }

/*
 * Get Color structure from hexadecimal value
 *
 * @param int $hexValue
 *
 */
function GetColor(int $hexValue): \raylib\Color { return new \raylib\Color; }

/*
 * Get pixel data size in bytes for certain format
 *
 * @param int $width
 * @param int $height
 * @param int $format
 *
 */
function GetPixelDataSize(int $width, int $height, int $format): int { return 0; }

/*
 * Get the default Font
 *
 *
 */
function GetFontDefault(): \raylib\Font { return new \raylib\Font; }

/*
 * Load font from file into GPU memory (VRAM)
 *
 * @param string $fileName
 *
 */
function LoadFont(string $fileName): \raylib\Font { return new \raylib\Font; }

/*
 * Load font from file with extended parameters, use NULL for fontChars and 0 for glyphCount to load the default character set
 *
 * @param string $fileName
 * @param int $fontSize
 * @param array $fontChars
 * @param int $glyphCount
 *
 */
function LoadFontEx(string $fileName, int $fontSize, array $fontChars, int $glyphCount): \raylib\Font { return new \raylib\Font; }

/*
 * Load font from Image (XNA style)
 *
 * @param \raylib\Image $image
 * @param \raylib\Color $key
 * @param int $firstChar
 *
 */
function LoadFontFromImage(\raylib\Image $image, \raylib\Color $key, int $firstChar): \raylib\Font { return new \raylib\Font; }

/*
 * Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
 *
 * @param string $fileType
 * @param array $fileData
 * @param int $dataSize
 * @param int $fontSize
 * @param array $fontChars
 * @param int $glyphCount
 *
 */
function LoadFontFromMemory(string $fileType, array $fileData, int $dataSize, int $fontSize, array $fontChars, int $glyphCount): \raylib\Font { return new \raylib\Font; }

/*
 * Check if a font is ready
 *
 * @param \raylib\Font $font
 *
 */
function IsFontReady(\raylib\Font $font): bool { return false; }

/*
 * Unload font chars info data (RAM)
 *
 * @param \raylib\GlyphInfo $chars
 * @param int $glyphCount
 *
 */
function UnloadFontData(\raylib\GlyphInfo $chars, int $glyphCount): void {  }

/*
 * Unload font from GPU memory (VRAM)
 *
 * @param \raylib\Font $font
 *
 */
function UnloadFont(\raylib\Font $font): void {  }

/*
 * Export font as code file, returns true on success
 *
 * @param \raylib\Font $font
 * @param string $fileName
 *
 */
function ExportFontAsCode(\raylib\Font $font, string $fileName): bool { return false; }

/*
 * Draw current FPS
 *
 * @param int $posX
 * @param int $posY
 *
 */
function DrawFPS(int $posX, int $posY): void {  }

/*
 * Draw text (using default font)
 *
 * @param string $text
 * @param int $posX
 * @param int $posY
 * @param int $fontSize
 * @param \raylib\Color $color
 *
 */
function DrawText(string $text, int $posX, int $posY, int $fontSize, \raylib\Color $color): void {  }

/*
 * Draw text using font and additional parameters
 *
 * @param \raylib\Font $font
 * @param string $text
 * @param \raylib\Vector2 $position
 * @param float $fontSize
 * @param float $spacing
 * @param \raylib\Color $tint
 *
 */
function DrawTextEx(\raylib\Font $font, string $text, \raylib\Vector2 $position, float $fontSize, float $spacing, \raylib\Color $tint): void {  }

/*
 * Draw text using Font and pro parameters (rotation)
 *
 * @param \raylib\Font $font
 * @param string $text
 * @param \raylib\Vector2 $position
 * @param \raylib\Vector2 $origin
 * @param float $rotation
 * @param float $fontSize
 * @param float $spacing
 * @param \raylib\Color $tint
 *
 */
function DrawTextPro(\raylib\Font $font, string $text, \raylib\Vector2 $position, \raylib\Vector2 $origin, float $rotation, float $fontSize, float $spacing, \raylib\Color $tint): void {  }

/*
 * Draw one character (codepoint)
 *
 * @param \raylib\Font $font
 * @param int $codepoint
 * @param \raylib\Vector2 $position
 * @param float $fontSize
 * @param \raylib\Color $tint
 *
 */
function DrawTextCodepoint(\raylib\Font $font, int $codepoint, \raylib\Vector2 $position, float $fontSize, \raylib\Color $tint): void {  }

/*
 * Draw multiple character (codepoint)
 *
 * @param \raylib\Font $font
 * @param array $codepoints
 * @param int $count
 * @param \raylib\Vector2 $position
 * @param float $fontSize
 * @param float $spacing
 * @param \raylib\Color $tint
 *
 */
function DrawTextCodepoints(\raylib\Font $font, array $codepoints, int $count, \raylib\Vector2 $position, float $fontSize, float $spacing, \raylib\Color $tint): void {  }

/*
 * Measure string width for default font
 *
 * @param string $text
 * @param int $fontSize
 *
 */
function MeasureText(string $text, int $fontSize): int { return 0; }

/*
 * Measure string size for Font
 *
 * @param \raylib\Font $font
 * @param string $text
 * @param float $fontSize
 * @param float $spacing
 *
 */
function MeasureTextEx(\raylib\Font $font, string $text, float $fontSize, float $spacing): \raylib\Vector2 { return new \raylib\Vector2; }

/*
 * Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
 *
 * @param \raylib\Font $font
 * @param int $codepoint
 *
 */
function GetGlyphIndex(\raylib\Font $font, int $codepoint): int { return 0; }

/*
 * Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
 *
 * @param \raylib\Font $font
 * @param int $codepoint
 *
 */
function GetGlyphInfo(\raylib\Font $font, int $codepoint): \raylib\GlyphInfo { return new \raylib\GlyphInfo; }

/*
 * Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found
 *
 * @param \raylib\Font $font
 * @param int $codepoint
 *
 */
function GetGlyphAtlasRec(\raylib\Font $font, int $codepoint): \raylib\Rectangle { return new \raylib\Rectangle; }

/*
 * Unload UTF-8 text encoded from codepoints array
 *
 * @param string $text
 *
 */
function UnloadUTF8(string $text): void {  }

/*
 * Unload codepoints data from memory
 *
 * @param array $codepoints
 *
 */
function UnloadCodepoints(array $codepoints): void {  }

/*
 * Get total number of codepoints in a UTF-8 encoded string
 *
 * @param string $text
 *
 */
function GetCodepointCount(string $text): int { return 0; }

/*
 * Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
 *
 * @param string $text
 * @param array $codepointSize
 *
 */
function GetCodepoint(string $text, array $codepointSize): int { return 0; }

/*
 * Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
 *
 * @param string $text
 * @param array $codepointSize
 *
 */
function GetCodepointNext(string $text, array $codepointSize): int { return 0; }

/*
 * Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
 *
 * @param string $text
 * @param array $codepointSize
 *
 */
function GetCodepointPrevious(string $text, array $codepointSize): int { return 0; }

/*
 * Copy one string to another, returns bytes copied
 *
 * @param string $dst
 * @param string $src
 *
 */
function TextCopy(string $dst, string $src): int { return 0; }

/*
 * Check if two text string are equal
 *
 * @param string $text1
 * @param string $text2
 *
 */
function TextIsEqual(string $text1, string $text2): bool { return false; }

/*
 * Get text length, checks for '\0' ending
 *
 * @param string $text
 *
 */
function TextLength(string $text): int { return 0; }

/*
 * Append text at specific position and move cursor!
 *
 * @param string $text
 * @param string $append
 * @param array $position
 *
 */
function TextAppend(string $text, string $append, array $position): void {  }

/*
 * Find first text occurrence within a string
 *
 * @param string $text
 * @param string $find
 *
 */
function TextFindIndex(string $text, string $find): int { return 0; }

/*
 * Get integer value from text (negative values not supported)
 *
 * @param string $text
 *
 */
function TextToInteger(string $text): int { return 0; }

/*
 * Draw a line in 3D world space
 *
 * @param \raylib\Vector3 $startPos
 * @param \raylib\Vector3 $endPos
 * @param \raylib\Color $color
 *
 */
function DrawLine3D(\raylib\Vector3 $startPos, \raylib\Vector3 $endPos, \raylib\Color $color): void {  }

/*
 * Draw a point in 3D space, actually a small line
 *
 * @param \raylib\Vector3 $position
 * @param \raylib\Color $color
 *
 */
function DrawPoint3D(\raylib\Vector3 $position, \raylib\Color $color): void {  }

/*
 * Draw a circle in 3D world space
 *
 * @param \raylib\Vector3 $center
 * @param float $radius
 * @param \raylib\Vector3 $rotationAxis
 * @param float $rotationAngle
 * @param \raylib\Color $color
 *
 */
function DrawCircle3D(\raylib\Vector3 $center, float $radius, \raylib\Vector3 $rotationAxis, float $rotationAngle, \raylib\Color $color): void {  }

/*
 * Draw a color-filled triangle (vertex in counter-clockwise order!)
 *
 * @param \raylib\Vector3 $v1
 * @param \raylib\Vector3 $v2
 * @param \raylib\Vector3 $v3
 * @param \raylib\Color $color
 *
 */
function DrawTriangle3D(\raylib\Vector3 $v1, \raylib\Vector3 $v2, \raylib\Vector3 $v3, \raylib\Color $color): void {  }

/*
 * Draw a triangle strip defined by points
 *
 * @param \raylib\Vector3 $points
 * @param int $pointCount
 * @param \raylib\Color $color
 *
 */
function DrawTriangleStrip3D(\raylib\Vector3 $points, int $pointCount, \raylib\Color $color): void {  }

/*
 * Draw cube
 *
 * @param \raylib\Vector3 $position
 * @param float $width
 * @param float $height
 * @param float $length
 * @param \raylib\Color $color
 *
 */
function DrawCube(\raylib\Vector3 $position, float $width, float $height, float $length, \raylib\Color $color): void {  }

/*
 * Draw cube (Vector version)
 *
 * @param \raylib\Vector3 $position
 * @param \raylib\Vector3 $size
 * @param \raylib\Color $color
 *
 */
function DrawCubeV(\raylib\Vector3 $position, \raylib\Vector3 $size, \raylib\Color $color): void {  }

/*
 * Draw cube wires
 *
 * @param \raylib\Vector3 $position
 * @param float $width
 * @param float $height
 * @param float $length
 * @param \raylib\Color $color
 *
 */
function DrawCubeWires(\raylib\Vector3 $position, float $width, float $height, float $length, \raylib\Color $color): void {  }

/*
 * Draw cube wires (Vector version)
 *
 * @param \raylib\Vector3 $position
 * @param \raylib\Vector3 $size
 * @param \raylib\Color $color
 *
 */
function DrawCubeWiresV(\raylib\Vector3 $position, \raylib\Vector3 $size, \raylib\Color $color): void {  }

/*
 * Draw sphere
 *
 * @param \raylib\Vector3 $centerPos
 * @param float $radius
 * @param \raylib\Color $color
 *
 */
function DrawSphere(\raylib\Vector3 $centerPos, float $radius, \raylib\Color $color): void {  }

/*
 * Draw sphere with extended parameters
 *
 * @param \raylib\Vector3 $centerPos
 * @param float $radius
 * @param int $rings
 * @param int $slices
 * @param \raylib\Color $color
 *
 */
function DrawSphereEx(\raylib\Vector3 $centerPos, float $radius, int $rings, int $slices, \raylib\Color $color): void {  }

/*
 * Draw sphere wires
 *
 * @param \raylib\Vector3 $centerPos
 * @param float $radius
 * @param int $rings
 * @param int $slices
 * @param \raylib\Color $color
 *
 */
function DrawSphereWires(\raylib\Vector3 $centerPos, float $radius, int $rings, int $slices, \raylib\Color $color): void {  }

/*
 * Draw a cylinder/cone
 *
 * @param \raylib\Vector3 $position
 * @param float $radiusTop
 * @param float $radiusBottom
 * @param float $height
 * @param int $slices
 * @param \raylib\Color $color
 *
 */
function DrawCylinder(\raylib\Vector3 $position, float $radiusTop, float $radiusBottom, float $height, int $slices, \raylib\Color $color): void {  }

/*
 * Draw a cylinder with base at startPos and top at endPos
 *
 * @param \raylib\Vector3 $startPos
 * @param \raylib\Vector3 $endPos
 * @param float $startRadius
 * @param float $endRadius
 * @param int $sides
 * @param \raylib\Color $color
 *
 */
function DrawCylinderEx(\raylib\Vector3 $startPos, \raylib\Vector3 $endPos, float $startRadius, float $endRadius, int $sides, \raylib\Color $color): void {  }

/*
 * Draw a cylinder/cone wires
 *
 * @param \raylib\Vector3 $position
 * @param float $radiusTop
 * @param float $radiusBottom
 * @param float $height
 * @param int $slices
 * @param \raylib\Color $color
 *
 */
function DrawCylinderWires(\raylib\Vector3 $position, float $radiusTop, float $radiusBottom, float $height, int $slices, \raylib\Color $color): void {  }

/*
 * Draw a cylinder wires with base at startPos and top at endPos
 *
 * @param \raylib\Vector3 $startPos
 * @param \raylib\Vector3 $endPos
 * @param float $startRadius
 * @param float $endRadius
 * @param int $sides
 * @param \raylib\Color $color
 *
 */
function DrawCylinderWiresEx(\raylib\Vector3 $startPos, \raylib\Vector3 $endPos, float $startRadius, float $endRadius, int $sides, \raylib\Color $color): void {  }

/*
 * Draw a capsule with the center of its sphere caps at startPos and endPos
 *
 * @param \raylib\Vector3 $startPos
 * @param \raylib\Vector3 $endPos
 * @param float $radius
 * @param int $slices
 * @param int $rings
 * @param \raylib\Color $color
 *
 */
function DrawCapsule(\raylib\Vector3 $startPos, \raylib\Vector3 $endPos, float $radius, int $slices, int $rings, \raylib\Color $color): void {  }

/*
 * Draw capsule wireframe with the center of its sphere caps at startPos and endPos
 *
 * @param \raylib\Vector3 $startPos
 * @param \raylib\Vector3 $endPos
 * @param float $radius
 * @param int $slices
 * @param int $rings
 * @param \raylib\Color $color
 *
 */
function DrawCapsuleWires(\raylib\Vector3 $startPos, \raylib\Vector3 $endPos, float $radius, int $slices, int $rings, \raylib\Color $color): void {  }

/*
 * Draw a plane XZ
 *
 * @param \raylib\Vector3 $centerPos
 * @param \raylib\Vector2 $size
 * @param \raylib\Color $color
 *
 */
function DrawPlane(\raylib\Vector3 $centerPos, \raylib\Vector2 $size, \raylib\Color $color): void {  }

/*
 * Draw a ray line
 *
 * @param \raylib\Ray $ray
 * @param \raylib\Color $color
 *
 */
function DrawRay(\raylib\Ray $ray, \raylib\Color $color): void {  }

/*
 * Draw a grid (centered at (0, 0, 0))
 *
 * @param int $slices
 * @param float $spacing
 *
 */
function DrawGrid(int $slices, float $spacing): void {  }

/*
 * Load model from files (meshes and materials)
 *
 * @param string $fileName
 *
 */
function LoadModel(string $fileName): \raylib\Model { return new \raylib\Model; }

/*
 * Load model from generated mesh (default material)
 *
 * @param \raylib\Mesh $mesh
 *
 */
function LoadModelFromMesh(\raylib\Mesh $mesh): \raylib\Model { return new \raylib\Model; }

/*
 * Check if a model is ready
 *
 * @param \raylib\Model $model
 *
 */
function IsModelReady(\raylib\Model $model): bool { return false; }

/*
 * Unload model (including meshes) from memory (RAM and/or VRAM)
 *
 * @param \raylib\Model $model
 *
 */
function UnloadModel(\raylib\Model $model): void {  }

/*
 * Compute model bounding box limits (considers all meshes)
 *
 * @param \raylib\Model $model
 *
 */
function GetModelBoundingBox(\raylib\Model $model): \raylib\BoundingBox { return new \raylib\BoundingBox; }

/*
 * Draw a model (with texture if set)
 *
 * @param \raylib\Model $model
 * @param \raylib\Vector3 $position
 * @param float $scale
 * @param \raylib\Color $tint
 *
 */
function DrawModel(\raylib\Model $model, \raylib\Vector3 $position, float $scale, \raylib\Color $tint): void {  }

/*
 * Draw a model with extended parameters
 *
 * @param \raylib\Model $model
 * @param \raylib\Vector3 $position
 * @param \raylib\Vector3 $rotationAxis
 * @param float $rotationAngle
 * @param \raylib\Vector3 $scale
 * @param \raylib\Color $tint
 *
 */
function DrawModelEx(\raylib\Model $model, \raylib\Vector3 $position, \raylib\Vector3 $rotationAxis, float $rotationAngle, \raylib\Vector3 $scale, \raylib\Color $tint): void {  }

/*
 * Draw a model wires (with texture if set)
 *
 * @param \raylib\Model $model
 * @param \raylib\Vector3 $position
 * @param float $scale
 * @param \raylib\Color $tint
 *
 */
function DrawModelWires(\raylib\Model $model, \raylib\Vector3 $position, float $scale, \raylib\Color $tint): void {  }

/*
 * Draw a model wires (with texture if set) with extended parameters
 *
 * @param \raylib\Model $model
 * @param \raylib\Vector3 $position
 * @param \raylib\Vector3 $rotationAxis
 * @param float $rotationAngle
 * @param \raylib\Vector3 $scale
 * @param \raylib\Color $tint
 *
 */
function DrawModelWiresEx(\raylib\Model $model, \raylib\Vector3 $position, \raylib\Vector3 $rotationAxis, float $rotationAngle, \raylib\Vector3 $scale, \raylib\Color $tint): void {  }

/*
 * Draw bounding box (wires)
 *
 * @param \raylib\BoundingBox $box
 * @param \raylib\Color $color
 *
 */
function DrawBoundingBox(\raylib\BoundingBox $box, \raylib\Color $color): void {  }

/*
 * Draw a billboard texture
 *
 * @param \raylib\Camera3D $camera
 * @param \raylib\Texture $texture
 * @param \raylib\Vector3 $position
 * @param float $size
 * @param \raylib\Color $tint
 *
 */
function DrawBillboard(\raylib\Camera3D $camera, \raylib\Texture $texture, \raylib\Vector3 $position, float $size, \raylib\Color $tint): void {  }

/*
 * Draw a billboard texture defined by source
 *
 * @param \raylib\Camera3D $camera
 * @param \raylib\Texture $texture
 * @param \raylib\Rectangle $source
 * @param \raylib\Vector3 $position
 * @param \raylib\Vector2 $size
 * @param \raylib\Color $tint
 *
 */
function DrawBillboardRec(\raylib\Camera3D $camera, \raylib\Texture $texture, \raylib\Rectangle $source, \raylib\Vector3 $position, \raylib\Vector2 $size, \raylib\Color $tint): void {  }

/*
 * Draw a billboard texture defined by source and rotation
 *
 * @param \raylib\Camera3D $camera
 * @param \raylib\Texture $texture
 * @param \raylib\Rectangle $source
 * @param \raylib\Vector3 $position
 * @param \raylib\Vector3 $up
 * @param \raylib\Vector2 $size
 * @param \raylib\Vector2 $origin
 * @param float $rotation
 * @param \raylib\Color $tint
 *
 */
function DrawBillboardPro(\raylib\Camera3D $camera, \raylib\Texture $texture, \raylib\Rectangle $source, \raylib\Vector3 $position, \raylib\Vector3 $up, \raylib\Vector2 $size, \raylib\Vector2 $origin, float $rotation, \raylib\Color $tint): void {  }

/*
 * Upload mesh vertex data in GPU and provide VAO/VBO ids
 *
 * @param \raylib\Mesh &$mesh
 * @param bool $dynamic
 *
 */
function UploadMesh(\raylib\Mesh &$mesh, bool $dynamic): void {  }

/*
 * Unload mesh data from CPU and GPU
 *
 * @param \raylib\Mesh $mesh
 *
 */
function UnloadMesh(\raylib\Mesh $mesh): void {  }

/*
 * Draw a 3d mesh with material and transform
 *
 * @param \raylib\Mesh $mesh
 * @param \raylib\Material $material
 * @param \raylib\Matrix $transform
 *
 */
function DrawMesh(\raylib\Mesh $mesh, \raylib\Material $material, \raylib\Matrix $transform): void {  }

/*
 * Draw multiple mesh instances with material and different transforms
 *
 * @param \raylib\Mesh $mesh
 * @param \raylib\Material $material
 * @param \raylib\Matrix &$transforms
 * @param int $instances
 *
 */
function DrawMeshInstanced(\raylib\Mesh $mesh, \raylib\Material $material, \raylib\Matrix &$transforms, int $instances): void {  }

/*
 * Export mesh data to file, returns true on success
 *
 * @param \raylib\Mesh $mesh
 * @param string $fileName
 *
 */
function ExportMesh(\raylib\Mesh $mesh, string $fileName): bool { return false; }

/*
 * Compute mesh bounding box limits
 *
 * @param \raylib\Mesh $mesh
 *
 */
function GetMeshBoundingBox(\raylib\Mesh $mesh): \raylib\BoundingBox { return new \raylib\BoundingBox; }

/*
 * Compute mesh tangents
 *
 * @param \raylib\Mesh &$mesh
 *
 */
function GenMeshTangents(\raylib\Mesh &$mesh): void {  }

/*
 * Generate polygonal mesh
 *
 * @param int $sides
 * @param float $radius
 *
 */
function GenMeshPoly(int $sides, float $radius): \raylib\Mesh { return new \raylib\Mesh; }

/*
 * Generate plane mesh (with subdivisions)
 *
 * @param float $width
 * @param float $length
 * @param int $resX
 * @param int $resZ
 *
 */
function GenMeshPlane(float $width, float $length, int $resX, int $resZ): \raylib\Mesh { return new \raylib\Mesh; }

/*
 * Generate cuboid mesh
 *
 * @param float $width
 * @param float $height
 * @param float $length
 *
 */
function GenMeshCube(float $width, float $height, float $length): \raylib\Mesh { return new \raylib\Mesh; }

/*
 * Generate sphere mesh (standard sphere)
 *
 * @param float $radius
 * @param int $rings
 * @param int $slices
 *
 */
function GenMeshSphere(float $radius, int $rings, int $slices): \raylib\Mesh { return new \raylib\Mesh; }

/*
 * Generate half-sphere mesh (no bottom cap)
 *
 * @param float $radius
 * @param int $rings
 * @param int $slices
 *
 */
function GenMeshHemiSphere(float $radius, int $rings, int $slices): \raylib\Mesh { return new \raylib\Mesh; }

/*
 * Generate cylinder mesh
 *
 * @param float $radius
 * @param float $height
 * @param int $slices
 *
 */
function GenMeshCylinder(float $radius, float $height, int $slices): \raylib\Mesh { return new \raylib\Mesh; }

/*
 * Generate cone/pyramid mesh
 *
 * @param float $radius
 * @param float $height
 * @param int $slices
 *
 */
function GenMeshCone(float $radius, float $height, int $slices): \raylib\Mesh { return new \raylib\Mesh; }

/*
 * Generate torus mesh
 *
 * @param float $radius
 * @param float $size
 * @param int $radSeg
 * @param int $sides
 *
 */
function GenMeshTorus(float $radius, float $size, int $radSeg, int $sides): \raylib\Mesh { return new \raylib\Mesh; }

/*
 * Generate trefoil knot mesh
 *
 * @param float $radius
 * @param float $size
 * @param int $radSeg
 * @param int $sides
 *
 */
function GenMeshKnot(float $radius, float $size, int $radSeg, int $sides): \raylib\Mesh { return new \raylib\Mesh; }

/*
 * Generate heightmap mesh from image data
 *
 * @param \raylib\Image $heightmap
 * @param \raylib\Vector3 $size
 *
 */
function GenMeshHeightmap(\raylib\Image $heightmap, \raylib\Vector3 $size): \raylib\Mesh { return new \raylib\Mesh; }

/*
 * Generate cubes-based map mesh from image data
 *
 * @param \raylib\Image $cubicmap
 * @param \raylib\Vector3 $cubeSize
 *
 */
function GenMeshCubicmap(\raylib\Image $cubicmap, \raylib\Vector3 $cubeSize): \raylib\Mesh { return new \raylib\Mesh; }

/*
 * Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
 *
 *
 */
function LoadMaterialDefault(): \raylib\Material { return new \raylib\Material; }

/*
 * Check if a material is ready
 *
 * @param \raylib\Material $material
 *
 */
function IsMaterialReady(\raylib\Material $material): bool { return false; }

/*
 * Unload material from GPU memory (VRAM)
 *
 * @param \raylib\Material $material
 *
 */
function UnloadMaterial(\raylib\Material $material): void {  }

/*
 * Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...)
 *
 * @param \raylib\Material &$material
 * @param int $mapType
 * @param \raylib\Texture $texture
 *
 */
function SetMaterialTexture(\raylib\Material &$material, int $mapType, \raylib\Texture $texture): void {  }

/*
 * Set material for a mesh
 *
 * @param \raylib\Model &$model
 * @param int $meshId
 * @param int $materialId
 *
 */
function SetModelMeshMaterial(\raylib\Model &$model, int $meshId, int $materialId): void {  }

/*
 * Load model animations from file
 *
 * @param string $fileName
 * @param array &$animCount
 * @return \raylib\ModelAnimation[]
 *
 */
function LoadModelAnimations(string $fileName, array &$animCount): array { return []; }

/*
 * Update model animation pose
 *
 * @param \raylib\Model $model
 * @param \raylib\ModelAnimation $anim
 * @param int $frame
 *
 */
function UpdateModelAnimation(\raylib\Model $model, \raylib\ModelAnimation $anim, int $frame): void {  }

/*
 * Unload animation data
 *
 * @param \raylib\ModelAnimation $anim
 *
 */
function UnloadModelAnimation(\raylib\ModelAnimation $anim): void {  }

/*
 * Unload animation array data
 *
 * @param \raylib\ModelAnimation $animations
 * @param int $count
 *
 */
function UnloadModelAnimations(\raylib\ModelAnimation $animations, int $count): void {  }

/*
 * Check model animation skeleton match
 *
 * @param \raylib\Model $model
 * @param \raylib\ModelAnimation $anim
 *
 */
function IsModelAnimationValid(\raylib\Model $model, \raylib\ModelAnimation $anim): bool { return false; }

/*
 * Check collision between two spheres
 *
 * @param \raylib\Vector3 $center1
 * @param float $radius1
 * @param \raylib\Vector3 $center2
 * @param float $radius2
 *
 */
function CheckCollisionSpheres(\raylib\Vector3 $center1, float $radius1, \raylib\Vector3 $center2, float $radius2): bool { return false; }

/*
 * Check collision between two bounding boxes
 *
 * @param \raylib\BoundingBox $box1
 * @param \raylib\BoundingBox $box2
 *
 */
function CheckCollisionBoxes(\raylib\BoundingBox $box1, \raylib\BoundingBox $box2): bool { return false; }

/*
 * Check collision between box and sphere
 *
 * @param \raylib\BoundingBox $box
 * @param \raylib\Vector3 $center
 * @param float $radius
 *
 */
function CheckCollisionBoxSphere(\raylib\BoundingBox $box, \raylib\Vector3 $center, float $radius): bool { return false; }

/*
 * Get collision info between ray and sphere
 *
 * @param \raylib\Ray $ray
 * @param \raylib\Vector3 $center
 * @param float $radius
 *
 */
function GetRayCollisionSphere(\raylib\Ray $ray, \raylib\Vector3 $center, float $radius): \raylib\RayCollision { return new \raylib\RayCollision; }

/*
 * Get collision info between ray and box
 *
 * @param \raylib\Ray $ray
 * @param \raylib\BoundingBox $box
 *
 */
function GetRayCollisionBox(\raylib\Ray $ray, \raylib\BoundingBox $box): \raylib\RayCollision { return new \raylib\RayCollision; }

/*
 * Get collision info between ray and mesh
 *
 * @param \raylib\Ray $ray
 * @param \raylib\Mesh $mesh
 * @param \raylib\Matrix $transform
 *
 */
function GetRayCollisionMesh(\raylib\Ray $ray, \raylib\Mesh $mesh, \raylib\Matrix $transform): \raylib\RayCollision { return new \raylib\RayCollision; }

/*
 * Get collision info between ray and triangle
 *
 * @param \raylib\Ray $ray
 * @param \raylib\Vector3 $p1
 * @param \raylib\Vector3 $p2
 * @param \raylib\Vector3 $p3
 *
 */
function GetRayCollisionTriangle(\raylib\Ray $ray, \raylib\Vector3 $p1, \raylib\Vector3 $p2, \raylib\Vector3 $p3): \raylib\RayCollision { return new \raylib\RayCollision; }

/*
 * Get collision info between ray and quad
 *
 * @param \raylib\Ray $ray
 * @param \raylib\Vector3 $p1
 * @param \raylib\Vector3 $p2
 * @param \raylib\Vector3 $p3
 * @param \raylib\Vector3 $p4
 *
 */
function GetRayCollisionQuad(\raylib\Ray $ray, \raylib\Vector3 $p1, \raylib\Vector3 $p2, \raylib\Vector3 $p3, \raylib\Vector3 $p4): \raylib\RayCollision { return new \raylib\RayCollision; }

/*
 * Initialize audio device and context
 *
 *
 */
function InitAudioDevice(): void {  }

/*
 * Close the audio device and context
 *
 *
 */
function CloseAudioDevice(): void {  }

/*
 * Check if audio device has been initialized successfully
 *
 *
 */
function IsAudioDeviceReady(): bool { return false; }

/*
 * Set master volume (listener)
 *
 * @param float $volume
 *
 */
function SetMasterVolume(float $volume): void {  }

/*
 * Load wave data from file
 *
 * @param string $fileName
 *
 */
function LoadWave(string $fileName): \raylib\Wave { return new \raylib\Wave; }

/*
 * Load wave from memory buffer, fileType refers to extension: i.e. '.wav'
 *
 * @param string $fileType
 * @param array $fileData
 * @param int $dataSize
 *
 */
function LoadWaveFromMemory(string $fileType, array $fileData, int $dataSize): \raylib\Wave { return new \raylib\Wave; }

/*
 * Checks if wave data is ready
 *
 * @param \raylib\Wave $wave
 *
 */
function IsWaveReady(\raylib\Wave $wave): bool { return false; }

/*
 * Load sound from file
 *
 * @param string $fileName
 *
 */
function LoadSound(string $fileName): \raylib\Sound { return new \raylib\Sound; }

/*
 * Load sound from wave data
 *
 * @param \raylib\Wave $wave
 *
 */
function LoadSoundFromWave(\raylib\Wave $wave): \raylib\Sound { return new \raylib\Sound; }

/*
 * Checks if a sound is ready
 *
 * @param \raylib\Sound $sound
 *
 */
function IsSoundReady(\raylib\Sound $sound): bool { return false; }

/*
 * Unload wave data
 *
 * @param \raylib\Wave $wave
 *
 */
function UnloadWave(\raylib\Wave $wave): void {  }

/*
 * Unload sound
 *
 * @param \raylib\Sound $sound
 *
 */
function UnloadSound(\raylib\Sound $sound): void {  }

/*
 * Export wave data to file, returns true on success
 *
 * @param \raylib\Wave $wave
 * @param string $fileName
 *
 */
function ExportWave(\raylib\Wave $wave, string $fileName): bool { return false; }

/*
 * Export wave sample data to code (.h), returns true on success
 *
 * @param \raylib\Wave $wave
 * @param string $fileName
 *
 */
function ExportWaveAsCode(\raylib\Wave $wave, string $fileName): bool { return false; }

/*
 * Play a sound
 *
 * @param \raylib\Sound $sound
 *
 */
function PlaySound(\raylib\Sound $sound): void {  }

/*
 * Stop playing a sound
 *
 * @param \raylib\Sound $sound
 *
 */
function StopSound(\raylib\Sound $sound): void {  }

/*
 * Pause a sound
 *
 * @param \raylib\Sound $sound
 *
 */
function PauseSound(\raylib\Sound $sound): void {  }

/*
 * Resume a paused sound
 *
 * @param \raylib\Sound $sound
 *
 */
function ResumeSound(\raylib\Sound $sound): void {  }

/*
 * Check if a sound is currently playing
 *
 * @param \raylib\Sound $sound
 *
 */
function IsSoundPlaying(\raylib\Sound $sound): bool { return false; }

/*
 * Set volume for a sound (1.0 is max level)
 *
 * @param \raylib\Sound $sound
 * @param float $volume
 *
 */
function SetSoundVolume(\raylib\Sound $sound, float $volume): void {  }

/*
 * Set pitch for a sound (1.0 is base level)
 *
 * @param \raylib\Sound $sound
 * @param float $pitch
 *
 */
function SetSoundPitch(\raylib\Sound $sound, float $pitch): void {  }

/*
 * Set pan for a sound (0.5 is center)
 *
 * @param \raylib\Sound $sound
 * @param float $pan
 *
 */
function SetSoundPan(\raylib\Sound $sound, float $pan): void {  }

/*
 * Copy a wave to a new wave
 *
 * @param \raylib\Wave $wave
 *
 */
function WaveCopy(\raylib\Wave $wave): \raylib\Wave { return new \raylib\Wave; }

/*
 * Crop a wave to defined samples range
 *
 * @param \raylib\Wave &$wave
 * @param int $initSample
 * @param int $finalSample
 *
 */
function WaveCrop(\raylib\Wave &$wave, int $initSample, int $finalSample): void {  }

/*
 * Convert wave data to desired format
 *
 * @param \raylib\Wave &$wave
 * @param int $sampleRate
 * @param int $sampleSize
 * @param int $channels
 *
 */
function WaveFormat(\raylib\Wave &$wave, int $sampleRate, int $sampleSize, int $channels): void {  }

/*
 * Unload samples data loaded with LoadWaveSamples()
 *
 * @param array $samples
 *
 */
function UnloadWaveSamples(array $samples): void {  }

/*
 * Load music stream from file
 *
 * @param string $fileName
 *
 */
function LoadMusicStream(string $fileName): \raylib\Music { return new \raylib\Music; }

/*
 * Load music stream from data
 *
 * @param string $fileType
 * @param array $data
 * @param int $dataSize
 *
 */
function LoadMusicStreamFromMemory(string $fileType, array $data, int $dataSize): \raylib\Music { return new \raylib\Music; }

/*
 * Checks if a music stream is ready
 *
 * @param \raylib\Music $music
 *
 */
function IsMusicReady(\raylib\Music $music): bool { return false; }

/*
 * Unload music stream
 *
 * @param \raylib\Music $music
 *
 */
function UnloadMusicStream(\raylib\Music $music): void {  }

/*
 * Start music playing
 *
 * @param \raylib\Music $music
 *
 */
function PlayMusicStream(\raylib\Music $music): void {  }

/*
 * Check if music is playing
 *
 * @param \raylib\Music $music
 *
 */
function IsMusicStreamPlaying(\raylib\Music $music): bool { return false; }

/*
 * Updates buffers for music streaming
 *
 * @param \raylib\Music $music
 *
 */
function UpdateMusicStream(\raylib\Music $music): void {  }

/*
 * Stop music playing
 *
 * @param \raylib\Music $music
 *
 */
function StopMusicStream(\raylib\Music $music): void {  }

/*
 * Pause music playing
 *
 * @param \raylib\Music $music
 *
 */
function PauseMusicStream(\raylib\Music $music): void {  }

/*
 * Resume playing paused music
 *
 * @param \raylib\Music $music
 *
 */
function ResumeMusicStream(\raylib\Music $music): void {  }

/*
 * Seek music to a position (in seconds)
 *
 * @param \raylib\Music $music
 * @param float $position
 *
 */
function SeekMusicStream(\raylib\Music $music, float $position): void {  }

/*
 * Set volume for music (1.0 is max level)
 *
 * @param \raylib\Music $music
 * @param float $volume
 *
 */
function SetMusicVolume(\raylib\Music $music, float $volume): void {  }

/*
 * Set pitch for a music (1.0 is base level)
 *
 * @param \raylib\Music $music
 * @param float $pitch
 *
 */
function SetMusicPitch(\raylib\Music $music, float $pitch): void {  }

/*
 * Set pan for a music (0.5 is center)
 *
 * @param \raylib\Music $music
 * @param float $pan
 *
 */
function SetMusicPan(\raylib\Music $music, float $pan): void {  }

/*
 * Get music time length (in seconds)
 *
 * @param \raylib\Music $music
 *
 */
function GetMusicTimeLength(\raylib\Music $music): float { return 0.00; }

/*
 * Get current music time played (in seconds)
 *
 * @param \raylib\Music $music
 *
 */
function GetMusicTimePlayed(\raylib\Music $music): float { return 0.00; }

/*
 * Load audio stream (to stream raw audio pcm data)
 *
 * @param int $sampleRate
 * @param int $sampleSize
 * @param int $channels
 *
 */
function LoadAudioStream(int $sampleRate, int $sampleSize, int $channels): \raylib\AudioStream { return new \raylib\AudioStream; }

/*
 * Checks if an audio stream is ready
 *
 * @param \raylib\AudioStream $stream
 *
 */
function IsAudioStreamReady(\raylib\AudioStream $stream): bool { return false; }

/*
 * Unload audio stream and free memory
 *
 * @param \raylib\AudioStream $stream
 *
 */
function UnloadAudioStream(\raylib\AudioStream $stream): void {  }

/*
 * Check if any audio stream buffers requires refill
 *
 * @param \raylib\AudioStream $stream
 *
 */
function IsAudioStreamProcessed(\raylib\AudioStream $stream): bool { return false; }

/*
 * Play audio stream
 *
 * @param \raylib\AudioStream $stream
 *
 */
function PlayAudioStream(\raylib\AudioStream $stream): void {  }

/*
 * Pause audio stream
 *
 * @param \raylib\AudioStream $stream
 *
 */
function PauseAudioStream(\raylib\AudioStream $stream): void {  }

/*
 * Resume audio stream
 *
 * @param \raylib\AudioStream $stream
 *
 */
function ResumeAudioStream(\raylib\AudioStream $stream): void {  }

/*
 * Check if audio stream is playing
 *
 * @param \raylib\AudioStream $stream
 *
 */
function IsAudioStreamPlaying(\raylib\AudioStream $stream): bool { return false; }

/*
 * Stop audio stream
 *
 * @param \raylib\AudioStream $stream
 *
 */
function StopAudioStream(\raylib\AudioStream $stream): void {  }

/*
 * Set volume for audio stream (1.0 is max level)
 *
 * @param \raylib\AudioStream $stream
 * @param float $volume
 *
 */
function SetAudioStreamVolume(\raylib\AudioStream $stream, float $volume): void {  }

/*
 * Set pitch for audio stream (1.0 is base level)
 *
 * @param \raylib\AudioStream $stream
 * @param float $pitch
 *
 */
function SetAudioStreamPitch(\raylib\AudioStream $stream, float $pitch): void {  }

/*
 * Set pan for audio stream (0.5 is centered)
 *
 * @param \raylib\AudioStream $stream
 * @param float $pan
 *
 */
function SetAudioStreamPan(\raylib\AudioStream $stream, float $pan): void {  }

/*
 * Default size for new audio streams
 *
 * @param int $size
 *
 */
function SetAudioStreamBufferSizeDefault(int $size): void {  }

}
