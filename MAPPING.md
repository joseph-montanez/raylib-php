# raylib to PHP Mapping / Progress

This is a one to one mapping of each raylib function.

###  Window-related functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void InitWindow(int width, int height, const char *title) | raylib\Window::init() ||
| void CloseWindow(void);                                   | raylib\Window::close() ||
| bool IsWindowReady(void);                                 | raylib\Window::isReady() ||
| bool WindowShouldClose(void);                             | raylib\Window::shouldClose() ||
| bool IsWindowMinimized(void);                             | raylib\Window::isMinimized() ||
| void ToggleFullscreen(void);                              | raylib\Window::toggleFullscreen() ||
| void SetWindowIcon(Image image);                          | raylib\Window::setIcon(Image $image) ||
| void SetWindowTitle(const char *title);                   | raylib\Window::setTitle(string $title) ||
| void SetWindowPosition(int x, int y);                     | raylib\Window::setPosition(int $x, int $y) ||
| void SetWindowMonitor(int monitor);                       | raylib\Window::setMonitor(int $monitor) ||
| void SetWindowMinSize(int width, int height);             | raylib\Window::setMinSize(int $width, int $height) ||
| void SetWindowSize(int width, int height);                | raylib\Window::setSize(int $width, int $height) ||
| int GetScreenWidth(void);                                 | raylib\Window::getWidth() : int ||
| int GetScreenHeight(void);                                | raylib\Window::getHeight() : int ||

###  Cursor-related functions
| C API | PHP API | Comment |
|-------|---------|---------|
| void ShowCursor(void);                                      | raylib\Cursor::show() ||
| void HideCursor(void);                                      | raylib\Cursor::show() ||
| bool IsCursorHidden(void);                                  | raylib\Cursor::isHidden() ||
| void EnableCursor(void);                                    | raylib\Cursor::enable() ||
| void DisableCursor(void);                                   | raylib\Cursor::disable() ||

###  Drawing-related functions
| C API | PHP API | Comment |
|-------|---------|---------|
| void ClearBackground(Color color);                          | raylib\Draw::clearBackground(array $color); ||            
| void BeginDrawing(void);                                    | raylib\Draw::begin(void); ||                      
| void EndDrawing(void);                                      | raylib\Draw::end(void); ||                        
| void BeginMode2D(Camera2D camera);                          | raylib\Draw::beginMode2d(Camera2D $camera); ||
| void EndMode2D(void);                                       | raylib\Draw::endMode2d(void); ||
| void BeginMode3D(Camera camera);                            | raylib\Draw::beginMode3d(Camera camera); ||
| void End3dMode(void);                                       | raylib\Draw::endMode3d(void); ||
| void BeginTextureMode(RenderTexture2D target);              | raylib\Draw::beginTextureMode(RenderTexture2D $target); ||
| void EndTextureMode(void);                                  | raylib\Draw::endTextureMode(void); ||                    

###  Screen-space-related functions
| C API | PHP API | Comment |
|-------|---------|---------|
| Ray GetMouseRay(Vector2 mousePosition, Camera camera);      | TODO ||
| Vector2 GetWorldToScreen(Vector3 position, Camera camera);  | TODO ||
| Matrix GetCameraMatrix(Camera camera);                      | TODO ||

###  Timming-related functions
| C API | PHP API | Comment |
|-------|---------|---------|
| void SetTargetFPS(int fps);                                 | raylib\Timming::setTargetFPS(int $fps) ||
| int GetFPS(void);                                           | raylib\Timming::getFPS() : int || 
| float GetFrameTime(void);                                   | raylib\Timming::getFrameTime() : float ||
| double GetTime(void);                                       | raylib\Timming::getTime() : float ||

###  Color-related functions
| C API | PHP API | Comment |
|-------|---------|---------|
| float *ColorToFloat(Color color);                           | TODO ||
| int ColorToInt(Color color);                                | TODO ||
| Vector3 ColorToHSV(Color color);                            | TODO ||
| Color GetColor(int hexValue);                               | TODO ||
| Color Fade(Color color, float alpha);                       | TODO ||

###  Misc. functions
| C API | PHP API | Comment |
|-------|---------|---------|
| void ShowLogo(void);                                        | TODO ||
| void SetConfigFlags(unsigned char flags);                   | TODO ||
| void SetTraceLog(unsigned char types);                      | TODO ||
| void TraceLog(int logType, const char *text, ...);          | TODO ||
| void TakeScreenshot(const char *fileName);                  | TODO ||
| int GetRandomValue(int min, int max);                       | TODO ||

###  Files management functions
| C API | PHP API | Comment |
|-------|---------|---------|
| bool IsFileExtension(const char *fileName, const char *ext); | N/A | May implement, but really can be done in PHP |
| const char *GetExtension(const char *fileName);              | N/A | http://php.net/manual/en/function.pathinfo.php or SplFileInfo |
| const char *GetFileName(const char *filePath);               | N/A | http://php.net/manual/en/function.pathinfo.php or SplFileInfo |
| const char *GetDirectoryPath(const char *fileName);          | N/A | http://php.net/manual/en/function.pathinfo.php or SplFileInfo |
| const char *GetWorkingDirectory(void);                       | N/A | See getcwd() |
| bool ChangeDirectory(const char *dir);                       | N/A | See chdir() |
| bool IsFileDropped(void);                                    | TODO ||
| char **GetDroppedFiles(int *count);                          | TODO ||
| void ClearDroppedFiles(void);                                | TODO ||

###  Persistent storage management
| C API | PHP API | Comment |
|-------|---------|---------|
| void StorageSaveValue(int position, int value);             | N/A | May implement, See pack() |
| int StorageLoadValue(int position);                         | N/A | May implement, See unpack() |

###  Input Handling Functions (Module: core)

####  Input-related functions: keyboard
| C API | PHP API | Comment |
|-------|---------|---------|
| bool IsKeyPressed(int key);                             | raylib\Key::isPressed(int key) : bool ||
| bool IsKeyDown(int key);                                | raylib\Key::isDown(int key) : bool ||
| bool IsKeyReleased(int key);                            | raylib\Key::isReleased(int key) : bool ||
| bool IsKeyUp(int key);                                  | raylib\Key::isUp(int key) : bool ||
| int GetKeyPressed(void);                                | raylib\Key::getPressed(void) : int ||
| void SetExitKey(int key);                               | raylib\Key::setExit(int $key) | This may move to Window class |

####  Input-related functions: gamepads
| C API | PHP API | Comment |
|-------|---------|---------|
| bool IsGamepadAvailable(int gamepad);                   | TODO ||
| bool IsGamepadName(int gamepad, const char *name);      | TODO ||
| const char *GetGamepadName(int gamepad);                | TODO ||
| bool IsGamepadButtonPressed(int gamepad, int button);   | TODO ||
| bool IsGamepadButtonDown(int gamepad, int button);      | TODO ||
| bool IsGamepadButtonReleased(int gamepad, int button);  | TODO ||
| bool IsGamepadButtonUp(int gamepad, int button);        | TODO ||
| int GetGamepadButtonPressed(void);                      | TODO ||
| int GetGamepadAxisCount(int gamepad);                   | TODO ||
| float GetGamepadAxisMovement(int gamepad, int axis);    | TODO ||

####  Input-related functions: mouse
| C API | PHP API | Comment |
|-------|---------|---------|
| bool IsMouseButtonPressed(int button);                  | TODO ||
| bool IsMouseButtonDown(int button);                     | TODO ||
| bool IsMouseButtonReleased(int button);                 | TODO ||
| bool IsMouseButtonUp(int button);                       | TODO ||
| int GetMouseX(void);                                    | TODO ||
| int GetMouseY(void);                                    | TODO ||
| Vector2 GetMousePosition(void);                         | TODO ||
| void SetMousePosition(Vector2 position);                | TODO ||
| void SetMouseScale(float scale);                        | TODO ||
| int GetMouseWheelMove(void);                            | TODO ||

####  Input-related functions: touch
| C API | PHP API | Comment |
|-------|---------|---------|
| int GetTouchX(void);                                    | TODO ||
| int GetTouchY(void);                                    | TODO ||
| Vector2 GetTouchPosition(int index);                    | TODO ||

###  Gestures and Touch Handling Functions (Module: gestures)
| void SetGesturesEnabled(unsigned int gestureFlags);     | TODO ||
| bool IsGestureDetected(int gesture);                    | TODO ||
| int GetGestureDetected(void);                           | TODO ||
| int GetTouchPointsCount(void);                          | TODO ||
| float GetGestureHoldDuration(void);                     | TODO ||
| Vector2 GetGestureDragVector(void);                     | TODO ||
| float GetGestureDragAngle(void);                        | TODO ||
| Vector2 GetGesturePinchVector(void);                    | TODO ||
| float GetGesturePinchAngle(void);                       | TODO ||

###  Camera System Functions (Module: camera)
| C API | PHP API | Comment |
|-------|---------|---------|
| void SetCameraMode(Camera camera, int mode);                | TODO ||
| void UpdateCamera(Camera *camera);                          | TODO ||
| void SetCameraPanControl(int panKey);                       | TODO ||
| void SetCameraAltControl(int altKey);                       | TODO ||
| void SetCameraSmoothZoomControl(int szKey);                 | TODO ||
| void SetCameraMoveControls(int frontKey, int backKey, int rightKey, int leftKey, int upKey, int downKey);  | TODO ||  

###  Basic Shapes Drawing Functions (Module: shapes)

####  Basic shapes drawing functions
| C API | PHP API | Comment |
|-------|---------|---------|
|void DrawPixel(int posX, int posY, Color color);                                                   | raylib\Draw::pixel(int $posX, int $posY, array $color) | |
|void DrawPixelV(Vector2 position, Color color);                                                    | raylib\Draw::pixelV(array $position, array $color) | |
|void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);                | raylib\Draw::line(int $startPosX, int $startPosY, int $endPosX, int $endPosY, array $color) | |
|void DrawLineV(Vector2 startPos, Vector2 endPos, Color color);                                     | raylib\Draw::lineV(array $startPos, array $endPos, array $color) | |
|void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color);                       | raylib\Draw::lineEx(array $startPos, array $endPos, float $thick, array $color) | |
|void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color);                   | raylib\Draw::lineBezier(array $startPos, array $endPos, float $thick, array $color) | |
|void DrawCircle(int centerX, int centerY, float radius, Color color);                              | raylib\Draw::circle(int $centerX, int $centerY, float $radius, array $color) | |
|void DrawCircleGradient(int centerX, int centerY, float radius, Color color1, Color color2);       | raylib\Draw::circleGradient(int $centerX, int $centerY, float $radius, array $color1, array $color2) | |
|void DrawCircleV(Vector2 center, float radius, Color color);                                       | raylib\Draw::circleV(array $center, float $radius, array $color) | |
|void DrawCircleLines(int centerX, int centerY, float radius, Color color);                         | raylib\Draw::circleLines(int $centerX, int $centerY, float $radius, array $color) | |
|void DrawRectangle(int posX, int posY, int width, int height, Color color);                        | raylib\Draw::rectangle(int $posX, int $posY, int $width, int $height, array $color) | |
|void DrawRectangleV(Vector2 position, Vector2 size, Color color);                                  | raylib\Draw::rectangleV(array $position, array $size, array $color) | |
|void DrawRectangleRec(Rectangle rec, Color color);                                                 | raylib\Draw::rectangleRec(array $rec, array $color) | |
|void DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color);                 | raylib\Draw::rectanglePro(array $rec, array $origin, float $rotation, array $color) | |
|void DrawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2);| raylib\Draw::rectangleGradientV(int $posX, int $posY, int $width, int $height, array $color1, array $color2); | |
|void DrawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2);| raylib\Draw::rectangleGradientH(int $posX, int $posY, int $width, int $height, array $color1, array $color2); | |
|void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4);       | raylib\Draw::rectangleGradientEx(array $rec, array $col1, array $col2, array $col3, array $col4) | |
|void DrawRectangleLines(int posX, int posY, int width, int height, Color color);                   | raylib\Draw::rectangleLines(int $posX, int $posY, int $width, int $height, array $color) | |
|void DrawRectangleLinesEx(Rectangle rec, int lineThick, Color color);                              | raylib\Draw::rectangleLinesEx(array $rec, int $lineThick, array $color) | |
|void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                                | raylib\Draw::triangle(array $v1, array $v2, array $v3, array $color) | |
|void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                           | raylib\Draw::triangleLines(array $v1, array $v2, array $v3, array $color) | |
|void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);               | raylib\Draw::poly(array $center, int $sides, float $radius, float $rotation, array $color) | |
|void DrawPolyEx(Vector2 *points, int numPoints, Color color);                                      | raylib\Draw::polyEx(array $points, int $numPoints, array $color) | |
|void DrawPolyExLines(Vector2 *points, int numPoints, Color color);                                 | raylib\Draw::polyExLines(array $points, int $numPoints, array $color) | |

####  Basic shapes collision detection functions
| C API | PHP API | Comment |
|-------|---------|---------|
| bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2);                                           | TODO ||
| bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);        | TODO ||
| bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);                         | TODO ||
| Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2);                                         | TODO ||
| bool CheckCollisionPointRec(Vector2 point, Rectangle rec);                                         | TODO ||
| bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);                       | TODO ||
| bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3);               | TODO ||

## Texture Loading and Drawing Functions (Module: textures)

### Image/Texture2D data loading/unloading/saving functions
| C API | PHP API | Comment |
|-------|---------|---------|
| Image LoadImage(const char *fileName);                                                             | new raylib\Image(string $filename) ||
| Image LoadImageEx(Color *pixels, int width, int height);                                           | TODO ||
| Image LoadImagePro(void *data, int width, int height, int format);                                 | TODO ||
| Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);       | TODO ||
| void ExportImage(const char *fileName, Image image);                                               | TODO ||
| Texture2D LoadTexture(const char *fileName);                                                       | new raylib\Texture(string $fileName) ||
| Texture2D LoadTextureFromImage(Image image);                                                       | TODO ||
| RenderTexture2D LoadRenderTexture(int width, int height);                                          | new raylib\RenderTexture(int $width, int $height) ||
| void UnloadImage(Image image);                                                                     | N/A | Use unset() on class |
| void UnloadTexture(Texture2D texture);                                                             | N/A | Use unset() on class |
| void UnloadRenderTexture(RenderTexture2D target);                                                  | N/A | Use unset() on class |
| Color *GetImageData(Image image);                                                                  | TODO ||
| int GetPixelDataSize(int width, int height, int format);                                           | TODO ||
| Image GetTextureData(Texture2D texture);                                                           | TODO ||
| void UpdateTexture(Texture2D texture, const void *pixels);                                         | TODO ||


### Image manipulation functions
| C API | PHP API | Comment |
|-------|---------|---------|
| Image ImageCopy(Image image);                                                                                                    | raylib\Image::copy(array $image) : Image ||
| void ImageToPOT(Image *image, Color fillColor);                                                                                  | raylib\Image::toPOT(array $image, array $fillColor) ||
| void ImageFormat(Image *image, int newFormat);                                                                                   | raylib\Image::format(array $image, int $newFormat) ||
| void ImageAlphaMask(Image *image, Image alphaMask);                                                                              | raylib\Image::alphaMask(array $image, array $alphaMask) ||
| void ImageAlphaClear(Image *image, Color color, float threshold);                                                                | raylib\Image::alphaClear(array $image, array $color, float $threshold) ||
| void ImageAlphaCrop(Image *image, float threshold);                                                                              | raylib\Image::alphaCrop(array $image, float $threshold) ||
| void ImageAlphaPremultiply(Image *image);                                                                                        | raylib\Image::alphaPremultiply(array $image) ||
| void ImageCrop(Image *image, Rectangle crop);                                                                                    | raylib\Image::crop(array $image, array $crop) ||
| void ImageResize(Image *image, int newWidth, int newHeight);                                                                     | raylib\Image::resize(array $image, int $newWidth, int $newHeight) ||
| void ImageResizeNN(Image *image,int newWidth,int newHeight);                                                                     | raylib\Image::resizeNN(array $image,int $newWidth,int $newHeight) ||
| void ImageMipmaps(Image *image);                                                                                                 | raylib\Image::mipmaps(array $image) ||
| void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp);                                                          | raylib\Image::dither(array $image, int $rBpp, int $gBpp, int $bBpp, int $aBpp) ||
| Image ImageText(const char *text, int fontSize, Color color);                                                                    | raylib\Image::text(string $text, int $fontSize, array $color) : Image ||
| Image ImageTextEx(SpriteFont font, const char *text, float fontSize, int spacing, Color tint);                                   | raylib\Image::textEx(SpriteFont $font, string $text, float $fontSize, int $spacing, array $tint) : Image ||
| void ImageDraw(Image *dst, Image src, Rectangle srcRec, Rectangle dstRec);                                                       | raylib\Image::draw(array $dst, array $src, array $srcRec, array $dstRec) ||
| void ImageDrawRectangle(Image *dst, Vector2 position, Rectangle rec, Color color);                                               | raylib\Image::drawRectangle(array $dst, array $position, array $rec, array $color) ||
| void ImageDrawText(Image *dst, Vector2 position, const char *text, int fontSize, Color color);                                   | raylib\Image::drawText(array $dst, array $position, string $text, int $fontSize, array $color) ||
| void ImageDrawTextEx(Image *dst, Vector2 position, SpriteFont font, const char *text, float fontSize, int spacing, Color color); | raylib\Image::drawTextEx(array $dst, array $position, SpriteFont $font, string $text, float $fontSize, int $spacing, array $color) ||
| void ImageFlipVertical(Image *image);                                                                                            | raylib\Image::flipVertical(array $image) ||
| void ImageFlipHorizontal(Image *image);                                                                                          | raylib\Image::flipHorizontal(array $image) ||
| void ImageColorTint(Image *image, Color color);                                                                                  | raylib\Image::colorTint(array $image, array $color) ||
| void ImageColorInvert(Image *image);                                                                                             | raylib\Image::colorInvert(array $image) ||
| void ImageColorGrayscale(Image *image);                                                                                          | raylib\Image::colorGrayscale(array $image) ||
| void ImageColorContrast(Image *image, float contrast);                                                                           | raylib\Image::colorContrast(array $image, float $contrast) ||
| void ImageColorBrightness(Image *image, int brightness);                                                                         | raylib\Image::colorBrightness(array $image, int $brightness) ||

### Image generation functions
| C API | PHP API | Comment |
|-------|---------|---------|
| Image GenImageColor(int width, int height, Color color);                                           // Generate image: plain color
| Image GenImageGradientV(int width, int height, Color top, Color bottom);                           // Generate image: vertical gradient
| Image GenImageGradientH(int width, int height, Color left, Color right);                           // Generate image: horizontal gradient
| Image GenImageGradientRadial(int width, int height, float density, Color inner, Color outer);      // Generate image: radial gradient
| Image GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2);    // Generate image: checked
| Image GenImageWhiteNoise(int width, int height, float factor);                                     // Generate image: white noise
| Image GenImagePerlinNoise(int width, int height, int offsetX, int offsetY, float scale);           // Generate image: perlin noise
| Image GenImageCellular(int width, int height, int tileSize);                                       // Generate image: cellular algorithm. Bigger tileSize means bigger cells

### Texture2D configuration functions
| C API | PHP API | Comment |
|-------|---------|---------|
RLAPI void GenTextureMipmaps(Texture2D *texture);                                                        // Generate GPU mipmaps for a texture
RLAPI void SetTextureFilter(Texture2D texture, int filterMode);                                          // Set texture scaling filter mode
RLAPI void SetTextureWrap(Texture2D texture, int wrapMode);                                              // Set texture wrapping mode

### Texture2D drawing functions
| C API | PHP API | Comment |
|-------|---------|---------|
RLAPI void DrawTexture(Texture2D texture, int posX, int posY, Color tint);                               // Draw a Texture2D
RLAPI void DrawTextureV(Texture2D texture, Vector2 position, Color tint);                                // Draw a Texture2D with position defined as Vector2
RLAPI void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);  // Draw a Texture2D with extended parameters
RLAPI void DrawTextureRec(Texture2D texture, Rectangle sourceRec, Vector2 position, Color tint);         // Draw a part of a texture defined by a rectangle
RLAPI void DrawTexturePro(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Vector2 origin,     // Draw a part of a texture defined by a rectangle with 'pro' parameters
                    float rotation, Color tint);

//------------------------------------------------------------------------------------
// Font Loading and Text Drawing Functions (Module: text)
//------------------------------------------------------------------------------------

// SpriteFont loading/unloading functions
RLAPI SpriteFont GetDefaultFont(void);                                                                   // Get the default SpriteFont
RLAPI SpriteFont LoadSpriteFont(const char *fileName);                                                   // Load SpriteFont from file into GPU memory (VRAM)
RLAPI SpriteFont LoadSpriteFontEx(const char *fileName, int fontSize, int charsCount, int *fontChars);   // Load SpriteFont from file with extended parameters
RLAPI void UnloadSpriteFont(SpriteFont font);                                                            // Unload SpriteFont from GPU memory (VRAM)

// Text drawing functions
RLAPI void DrawFPS(int posX, int posY);                                                                  // Shows current FPS
RLAPI void DrawText(const char *text, int posX, int posY, int fontSize, Color color);                    // Draw text (using default font)
RLAPI void DrawTextEx(SpriteFont font, const char* text, Vector2 position,                               // Draw text using SpriteFont and additional parameters
                float fontSize, int spacing, Color tint);

// Text misc. functions
RLAPI int MeasureText(const char *text, int fontSize);                                                   // Measure string width for default font
RLAPI Vector2 MeasureTextEx(SpriteFont font, const char *text, float fontSize, int spacing);             // Measure string size for SpriteFont
RLAPI const char *FormatText(const char *text, ...);                                                     // Formatting of text with variables to 'embed'
RLAPI const char *SubText(const char *text, int position, int length);                                   // Get a piece of a text string
RLAPI int GetGlyphIndex(SpriteFont font, int character);                                                 // Returns index position for a unicode character on sprite font

//------------------------------------------------------------------------------------
// Basic 3d Shapes Drawing Functions (Module: models)
//------------------------------------------------------------------------------------

// Basic geometric 3D shapes drawing functions
RLAPI void DrawLine3D(Vector3 startPos, Vector3 endPos, Color color);                                    // Draw a line in 3D world space
RLAPI void DrawCircle3D(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color); // Draw a circle in 3D world space
RLAPI void DrawCube(Vector3 position, float width, float height, float length, Color color);             // Draw cube
RLAPI void DrawCubeV(Vector3 position, Vector3 size, Color color);                                       // Draw cube (Vector version)
RLAPI void DrawCubeWires(Vector3 position, float width, float height, float length, Color color);        // Draw cube wires
RLAPI void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color); // Draw cube textured
RLAPI void DrawSphere(Vector3 centerPos, float radius, Color color);                                     // Draw sphere
RLAPI void DrawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color);            // Draw sphere with extended parameters
RLAPI void DrawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color);         // Draw sphere wires
RLAPI void DrawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color); // Draw a cylinder/cone
RLAPI void DrawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color); // Draw a cylinder/cone wires
RLAPI void DrawPlane(Vector3 centerPos, Vector2 size, Color color);                                      // Draw a plane XZ
RLAPI void DrawRay(Ray ray, Color color);                                                                // Draw a ray line
RLAPI void DrawGrid(int slices, float spacing);                                                          // Draw a grid (centered at (0, 0, 0))
RLAPI void DrawGizmo(Vector3 position);                                                                  // Draw simple gizmo
//DrawTorus(), DrawTeapot() could be useful?

//------------------------------------------------------------------------------------
// Model 3d Loading and Drawing Functions (Module: models)
//------------------------------------------------------------------------------------

// Model loading/unloading functions
RLAPI Model LoadModel(const char *fileName);                                                            // Load model from files (mesh and material)
RLAPI Model LoadModelFromMesh(Mesh mesh);                                                               // Load model from generated mesh
RLAPI void UnloadModel(Model model);                                                                    // Unload model from memory (RAM and/or VRAM)

// Mesh loading/unloading functions
RLAPI Mesh LoadMesh(const char *fileName);                                                              // Load mesh from file
RLAPI void UnloadMesh(Mesh *mesh);                                                                      // Unload mesh from memory (RAM and/or VRAM)
RLAPI void ExportMesh(const char *fileName, Mesh mesh);                                                 // Export mesh as an OBJ file

// Mesh manipulation functions
RLAPI BoundingBox MeshBoundingBox(Mesh mesh);                                                           // Compute mesh bounding box limits
RLAPI void MeshTangents(Mesh *mesh);                                                                    // Compute mesh tangents
RLAPI void MeshBinormals(Mesh *mesh);                                                                   // Compute mesh binormals

// Mesh generation functions
RLAPI Mesh GenMeshPlane(float width, float length, int resX, int resZ);                                 // Generate plane mesh (with subdivisions)
RLAPI Mesh GenMeshCube(float width, float height, float length);                                        // Generate cuboid mesh
RLAPI Mesh GenMeshSphere(float radius, int rings, int slices);                                          // Generate sphere mesh (standard sphere)
RLAPI Mesh GenMeshHemiSphere(float radius, int rings, int slices);                                      // Generate half-sphere mesh (no bottom cap)
RLAPI Mesh GenMeshCylinder(float radius, float height, int slices);                                     // Generate cylinder mesh
RLAPI Mesh GenMeshTorus(float radius, float size, int radSeg, int sides);                               // Generate torus mesh
RLAPI Mesh GenMeshKnot(float radius, float size, int radSeg, int sides);                                // Generate trefoil knot mesh
RLAPI Mesh GenMeshHeightmap(Image heightmap, Vector3 size);                                             // Generate heightmap mesh from image data
RLAPI Mesh GenMeshCubicmap(Image cubicmap, Vector3 cubeSize);                                           // Generate cubes-based map mesh from image data

// Material loading/unloading functions
RLAPI Material LoadMaterial(const char *fileName);                                                      // Load material from file
RLAPI Material LoadMaterialDefault(void);                                                               // Load default material (Supports: DIFFUSE, SPECULAR, NORMAL maps)
RLAPI void UnloadMaterial(Material material);                                                           // Unload material from GPU memory (VRAM)

// Model drawing functions
RLAPI void DrawModel(Model model, Vector3 position, float scale, Color tint);                           // Draw a model (with texture if set)
RLAPI void DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis,
                       float rotationAngle, Vector3 scale, Color tint);                                 // Draw a model with extended parameters
RLAPI void DrawModelWires(Model model, Vector3 position, float scale, Color tint);                      // Draw a model wires (with texture if set)
RLAPI void DrawModelWiresEx(Model model, Vector3 position, Vector3 rotationAxis,
                            float rotationAngle, Vector3 scale, Color tint);                            // Draw a model wires (with texture if set) with extended parameters
RLAPI void DrawBoundingBox(BoundingBox box, Color color);                                               // Draw bounding box (wires)
RLAPI void DrawBillboard(Camera camera, Texture2D texture, Vector3 center, float size, Color tint);     // Draw a billboard texture
RLAPI void DrawBillboardRec(Camera camera, Texture2D texture, Rectangle sourceRec,
                            Vector3 center, float size, Color tint);                                    // Draw a billboard texture defined by sourceRec

// Collision detection functions
RLAPI bool CheckCollisionSpheres(Vector3 centerA, float radiusA, Vector3 centerB, float radiusB);       // Detect collision between two spheres
RLAPI bool CheckCollisionBoxes(BoundingBox box1, BoundingBox box2);                                     // Detect collision between two bounding boxes
RLAPI bool CheckCollisionBoxSphere(BoundingBox box, Vector3 centerSphere, float radiusSphere);          // Detect collision between box and sphere
RLAPI bool CheckCollisionRaySphere(Ray ray, Vector3 spherePosition, float sphereRadius);                // Detect collision between ray and sphere
RLAPI bool CheckCollisionRaySphereEx(Ray ray, Vector3 spherePosition, float sphereRadius,
                                     Vector3 *collisionPoint);                                          // Detect collision between ray and sphere, returns collision point
RLAPI bool CheckCollisionRayBox(Ray ray, BoundingBox box);                                              // Detect collision between ray and box
RLAPI RayHitInfo GetCollisionRayModel(Ray ray, Model *model);                                           // Get collision info between ray and model
RLAPI RayHitInfo GetCollisionRayTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3);                  // Get collision info between ray and triangle
RLAPI RayHitInfo GetCollisionRayGround(Ray ray, float groundHeight);                                    // Get collision info between ray and ground plane (Y-normal plane)

//------------------------------------------------------------------------------------
// Shaders System Functions (Module: rlgl)
// NOTE: This functions are useless when using OpenGL 1.1
//------------------------------------------------------------------------------------

// Shader loading/unloading functions
RLAPI char *LoadText(const char *fileName);                               // Load chars array from text file
RLAPI Shader LoadShader(const char *vsFileName, const char *fsFileName);  // Load shader from files and bind default locations
RLAPI Shader LoadShaderCode(char *vsCode, char *fsCode);                  // Load shader from code strings and bind default locations
RLAPI void UnloadShader(Shader shader);                                   // Unload shader from GPU memory (VRAM)

RLAPI Shader GetShaderDefault(void);                                      // Get default shader
RLAPI Texture2D GetTextureDefault(void);                                  // Get default texture

// Shader configuration functions
RLAPI int GetShaderLocation(Shader shader, const char *uniformName);              // Get shader uniform location
RLAPI void SetShaderValue(Shader shader, int uniformLoc, const float *value, int size); // Set shader uniform value (float)
RLAPI void SetShaderValuei(Shader shader, int uniformLoc, const int *value, int size);  // Set shader uniform value (int)
RLAPI void SetShaderValueMatrix(Shader shader, int uniformLoc, Matrix mat);       // Set shader uniform value (matrix 4x4)
RLAPI void SetMatrixProjection(Matrix proj);                              // Set a custom projection matrix (replaces internal projection matrix)
RLAPI void SetMatrixModelview(Matrix view);                               // Set a custom modelview matrix (replaces internal modelview matrix)
RLAPI Matrix GetMatrixModelview();                                        // Get internal modelview matrix

// Texture maps generation (PBR)
// NOTE: Required shaders should be provided
RLAPI Texture2D GenTextureCubemap(Shader shader, Texture2D skyHDR, int size);       // Generate cubemap texture from HDR texture
RLAPI Texture2D GenTextureIrradiance(Shader shader, Texture2D cubemap, int size);   // Generate irradiance texture using cubemap data
RLAPI Texture2D GenTexturePrefilter(Shader shader, Texture2D cubemap, int size);    // Generate prefilter texture using cubemap data
RLAPI Texture2D GenTextureBRDF(Shader shader, Texture2D cubemap, int size);         // Generate BRDF texture using cubemap data

// Shading begin/end functions
RLAPI void BeginShaderMode(Shader shader);                                // Begin custom shader drawing
RLAPI void EndShaderMode(void);                                           // End custom shader drawing (use default shader)
RLAPI void BeginBlendMode(int mode);                                      // Begin blending mode (alpha, additive, multiplied)
RLAPI void EndBlendMode(void);                                            // End blending mode (reset to default: alpha blending)

// VR control functions
RLAPI VrDeviceInfo GetVrDeviceInfo(int vrDeviceType);   // Get VR device information for some standard devices
RLAPI void InitVrSimulator(VrDeviceInfo info);          // Init VR simulator for selected device parameters
RLAPI void CloseVrSimulator(void);                      // Close VR simulator for current device
RLAPI bool IsVrSimulatorReady(void);                    // Detect if VR simulator is ready
RLAPI void SetVrDistortionShader(Shader shader);        // Set VR distortion shader for stereoscopic rendering
RLAPI void UpdateVrTracking(Camera *camera);            // Update VR tracking (position and orientation) and camera
RLAPI void ToggleVrMode(void);                          // Enable/Disable VR experience
RLAPI void BeginVrDrawing(void);                        // Begin VR simulator stereo rendering
RLAPI void EndVrDrawing(void);                          // End VR simulator stereo rendering

//------------------------------------------------------------------------------------
// Audio Loading and Playing Functions (Module: audio)
//------------------------------------------------------------------------------------

// Audio device management functions
RLAPI void InitAudioDevice(void);                                     // Initialize audio device and context
RLAPI void CloseAudioDevice(void);                                    // Close the audio device and context
RLAPI bool IsAudioDeviceReady(void);                                  // Check if audio device has been initialized successfully
RLAPI void SetMasterVolume(float volume);                             // Set master volume (listener)

// Wave/Sound loading/unloading functions
RLAPI Wave LoadWave(const char *fileName);                            // Load wave data from file
RLAPI Wave LoadWaveEx(void *data, int sampleCount, int sampleRate, int sampleSize, int channels); // Load wave data from raw array data
RLAPI Sound LoadSound(const char *fileName);                          // Load sound from file
RLAPI Sound LoadSoundFromWave(Wave wave);                             // Load sound from wave data
RLAPI void UpdateSound(Sound sound, const void *data, int samplesCount);// Update sound buffer with new data
RLAPI void UnloadWave(Wave wave);                                     // Unload wave data
RLAPI void UnloadSound(Sound sound);                                  // Unload sound

// Wave/Sound management functions
RLAPI void PlaySound(Sound sound);                                    // Play a sound
RLAPI void PauseSound(Sound sound);                                   // Pause a sound
RLAPI void ResumeSound(Sound sound);                                  // Resume a paused sound
RLAPI void StopSound(Sound sound);                                    // Stop playing a sound
RLAPI bool IsSoundPlaying(Sound sound);                               // Check if a sound is currently playing
RLAPI void SetSoundVolume(Sound sound, float volume);                 // Set volume for a sound (1.0 is max level)
RLAPI void SetSoundPitch(Sound sound, float pitch);                   // Set pitch for a sound (1.0 is base level)
RLAPI void WaveFormat(Wave *wave, int sampleRate, int sampleSize, int channels);  // Convert wave data to desired format
RLAPI Wave WaveCopy(Wave wave);                                       // Copy a wave to a new wave
RLAPI void WaveCrop(Wave *wave, int initSample, int finalSample);     // Crop a wave to defined samples range
RLAPI float *GetWaveData(Wave wave);                                  // Get samples data from wave as a floats array

// Music management functions
RLAPI Music LoadMusicStream(const char *fileName);                    // Load music stream from file
RLAPI void UnloadMusicStream(Music music);                            // Unload music stream
RLAPI void PlayMusicStream(Music music);                              // Start music playing
RLAPI void UpdateMusicStream(Music music);                            // Updates buffers for music streaming
RLAPI void StopMusicStream(Music music);                              // Stop music playing
RLAPI void PauseMusicStream(Music music);                             // Pause music playing
RLAPI void ResumeMusicStream(Music music);                            // Resume playing paused music
RLAPI bool IsMusicPlaying(Music music);                               // Check if music is playing
RLAPI void SetMusicVolume(Music music, float volume);                 // Set volume for music (1.0 is max level)
RLAPI void SetMusicPitch(Music music, float pitch);                   // Set pitch for a music (1.0 is base level)
RLAPI void SetMusicLoopCount(Music music, int count);                 // Set music loop count (loop repeats)
RLAPI float GetMusicTimeLength(Music music);                          // Get music time length (in seconds)
RLAPI float GetMusicTimePlayed(Music music);                          // Get current music time played (in seconds)

// AudioStream management functions
RLAPI AudioStream InitAudioStream(unsigned int sampleRate, unsigned int sampleSize,
                                  unsigned int channels);             // Init audio stream (to stream raw audio pcm data)
RLAPI void UpdateAudioStream(AudioStream stream, const void *data, int samplesCount); // Update audio stream buffers with data
RLAPI void CloseAudioStream(AudioStream stream);                      // Close audio stream and free memory
RLAPI bool IsAudioBufferProcessed(AudioStream stream);                // Check if any audio stream buffers requires refill
RLAPI void PlayAudioStream(AudioStream stream);                       // Play audio stream
RLAPI void PauseAudioStream(AudioStream stream);                      // Pause audio stream
RLAPI void ResumeAudioStream(AudioStream stream);                     // Resume audio stream
RLAPI bool IsAudioStreamPlaying(AudioStream stream);                  // Check if audio stream is playing
RLAPI void StopAudioStream(AudioStream stream);                       // Stop audio stream
RLAPI void SetAudioStreamVolume(AudioStream stream, float volume);    // Set volume for audio stream (1.0 is max level)
RLAPI void SetAudioStreamPitch(AudioStream stream, float pitch);      // Set pitch for audio stream (1.0 is base level)
