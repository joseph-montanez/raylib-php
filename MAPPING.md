# raylib to PHP Mapping / Progress

This is a one to one mapping of each raylib function.

###  Window-related functions

| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void InitWindow(int width, int height, const char *title) | raylib\Window::init() ||
| RLAPI bool WindowShouldClose(void);                             | raylib\Window::shouldClose() ||
| RLAPI void CloseWindow(void);                                   | raylib\Window::close() ||
| RLAPI bool IsWindowReady(void);                                 | raylib\Window::isReady() : bool ||
| RLAPI bool IsWindowMinimized(void);                             | raylib\Window::isMinimized() : bool ||
| RLAPI bool IsWindowResized(void);                               | raylib\Window::isResized() : bool ||
| RLAPI bool IsWindowHidden(void);                                | raylib\Window::isHidden() : bool ||
| RLAPI bool IsWindowFullscreen(void);                            | raylib\Window::isWindowFullscreen() | Waiting on RayLib 3.0 release|
| RLAPI void UnhideWindow(void);                                  | raylib\Window::unhideWindow() ||
| RLAPI void HideWindow(void);                                    | raylib\Window::hideWindow() ||
| RLAPI void ToggleFullscreen(void);                              | raylib\Window::toggleFullscreen() ||
| RLAPI void SetWindowIcon(Image image);                          | raylib\Window::setIcon(Image $image) ||
| RLAPI void SetWindowTitle(const char *title);                   | raylib\Window::setTitle(string $title) ||
| RLAPI void SetWindowPosition(int x, int y);                     | raylib\Window::setPosition(int $x, int $y) ||
| RLAPI void SetWindowMonitor(int monitor);                       | raylib\Window::setMonitor(int $monitor) ||
| RLAPI void SetWindowMinSize(int width, int height);             | raylib\Window::setMinSize(int $width, int $height) ||
| RLAPI void SetWindowSize(int width, int height);                | raylib\Window::setSize(int $width, int $height) ||
| RLAPI void *GetWindowHandle(void);                              | N/A | At this time this will not be implemented as its OS dependant :( |
| RLAPI int GetScreenWidth(void);                                 | raylib\Window::getWidth() : int ||
| RLAPI int GetScreenHeight(void);                                | raylib\Window::getHeight() : int ||
| RLAPI int GetMonitorCount(void);                                | raylib\Window::getMonitorCount() : int ||
| RLAPI int GetMonitorWidth(int monitor);                         | raylib\Window::getMonitorWidth(int monitor) : int ||
| RLAPI int GetMonitorHeight(int monitor);                        | raylib\Window::getMonitorHeight(int monitor) : int ||
| RLAPI int GetMonitorPhysicalWidth(int monitor);                 | raylib\Window::getMonitorPhysicalWidth(int monitor) : int ||
| RLAPI int GetMonitorPhysicalHeight(int monitor);                | raylib\Window::getMonitorPhysicalHeight(int monitor) : int ||
| RLAPI Vector2 GetWindowPosition(void);                          | raylib\Window::getWindowPosition() : Vector2 ||
| RLAPI const char *GetMonitorName(int monitor);                  | raylib\Window::getMonitorName(int monitor) : string ||
| RLAPI const char *GetClipboardText(void);                       | raylib\Window::getClipboardText() : string ||
| RLAPI void SetClipboardText(const char *text);                  | raylib\Window::getMonitorCount(string $text) ||

###  Cursor-related functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void ShowCursor(void);                                      | raylib\Cursor::show() ||
| RLAPI void HideCursor(void);                                      | raylib\Cursor::show() ||
| RLAPI bool IsCursorHidden(void);                                  | raylib\Cursor::isHidden() ||
| RLAPI void EnableCursor(void);                                    | raylib\Cursor::enable() ||
| RLAPI void DisableCursor(void);                                   | raylib\Cursor::disable() ||

###  Drawing-related functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void ClearBackground(Color color);                          | raylib\Draw::clearBackground(array $color); ||            
| RLAPI void BeginDrawing(void);                                    | raylib\Draw::begin(void); ||                      
| RLAPI void EndDrawing(void);                                      | raylib\Draw::end(void); ||                        
| RLAPI void BeginMode2D(Camera2D camera3d);                        | raylib\Draw::beginMode2d(Camera2D $camera3d); ||
| RLAPI void EndMode2D(void);                                       | raylib\Draw::endMode2d(void); ||
| RLAPI void BeginMode3D(Camera camera3d);                          | raylib\Draw::beginMode3d(Camera camera3d); ||
| RLAPI void End3dMode(void);                                       | raylib\Draw::endMode3d(void); ||
| RLAPI void BeginTextureMode(RenderTexture2D target);              | raylib\RenderTexture::begind(); ||
| RLAPI void EndTextureMode(void);                                  | raylib\RenderTexture::end(void); ||                    
| RLAPI void BeginScissorMode(int x, int y, int width, int height); | raylib\Draw::beginScissorMode ||
| RLAPI void EndScissorMode(void);                                  | raylib\Draw::endScissorMode ||

###  Screen-space-related functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI Ray GetMouseRay(Vector2 mousePosition, Camera camera);                              | TODO ||
| RLAPI Matrix GetCameraMatrix(Camera camera);                                              | TODO ||
| RLAPI Matrix GetCameraMatrix2D(Camera2D camera);                                          | TODO ||
| RLAPI Vector2 GetWorldToScreen(Vector3 position, Camera camera);                          | TODO ||
| RLAPI Vector2 GetWorldToScreenEx(Vector3 position, Camera camera, int width, int height); | TODO ||
| RLAPI Vector2 GetWorldToScreen2D(Vector2 position, Camera2D camera);                      | TODO ||
| RLAPI Vector2 GetScreenToWorld2D(Vector2 position, Camera2D camera);                      | TODO ||

###  Timming-related functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void SetTargetFPS(int fps);  | raylib\Timming::setTargetFPS(int $fps) ||
| RLAPI int GetFPS(void);            | raylib\Timming::getFPS() : int || 
| RLAPI float GetFrameTime(void);    | raylib\Timming::getFrameTime() : float ||
| RLAPI double GetTime(void);        | raylib\Timming::getTime() : float ||

###  Color-related functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI int ColorToInt(Color color);                                | \raylib\Color->toInt(/raylib/Color $color) ||
| RLAPI Vector4 ColorNormalize(Color color);                        | \raylib\Color->normalize(/raylib/Color $color) : /raylib/Vector4 ||
| RLAPI Color ColorFromNormalized(Vector4 normalized);              | \raylib\Color::fromNormalized(/raylib/Vector4 $normalized) : /raylib/Color ||
| RLAPI Vector3 ColorToHSV(Color color);                            | \raylib\Color->toHSV(/raylib/Color $color) : /raylib/Vector3 ||
| RLAPI Color ColorFromHSV(Vector3 hsv);                            | \raylib\Color::fromHSV(/raylib/Vector4 $normalized) : /raylib/Color ||
| RLAPI Color GetColor(int hexValue);                               | \raylib\Color::fromInt(int $hexValue) : /raylib/Color ||
| RLAPI Color Fade(Color color, float alpha);                       | \raylib\Color->fade(float $alpha) : \raylib\Color | |

###  Misc. functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void SetConfigFlags(unsigned int flags);                    | \raylib\SetConfigFlags(int $flags) ||
| RLAPI void SetTraceLogLevel(int logType);                         | TODO ||
| RLAPI void SetTraceLogExit(int logType);                          | TODO ||
| RLAPI void SetTraceLogCallback(TraceLogCallback callback);        | TODO ||
| RLAPI void TraceLog(int logType, const char *text, ...);          | TODO ||
| RLAPI void TakeScreenshot(const char *fileName);                  | \raylib\TakeScreenshot(string $fileName) ||
| RLAPI int GetRandomValue(int min, int max);                       | see rand() ||

###  Files management functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI unsigned char *LoadFileData(const char *fileName, int *bytesRead);     | TODO | see file_get_contents() |
| RLAPI void SaveFileData(const char *fileName, void *data, int bytesToWrite); | TODO | see file_get_contents() |
| RLAPI char *LoadFileText(const char *fileName);                    | TODO | see file_get_contents() |
| RLAPI void SaveFileText(const char *fileName, char *text);         | TODO | see file_get_contents() |
| RLAPI bool FileExists(const char *fileName);                       | TODO | see file_exists() |
| RLAPI bool IsFileExtension(const char *fileName, const char *ext); | TODO | May implement, but really can be done in PHP |
| RLAPI bool DirectoryExists(const char *dirPath);                   | TODO | see is_dir() |
| RLAPI const char *GetExtension(const char *fileName);              | TODO | http://php.net/manual/en/function.pathinfo.php or SplFileInfo |
| RLAPI const char *GetFileName(const char *filePath);               | TODO | http://php.net/manual/en/function.pathinfo.php or SplFileInfo |
| RLAPI const char *GetFileNameWithoutExt(const char *filePath);     | TODO | http://php.net/manual/en/function.pathinfo.php or SplFileInfo |
| RLAPI const char *GetDirectoryPath(const char *filePath);          | TODO | http://php.net/manual/en/function.pathinfo.php or SplFileInfo |
| RLAPI const char *GetPrevDirectoryPath(const char *dirPath);       | TODO | see realpath() |
| RLAPI const char *GetWorkingDirectory(void);                       | TODO | http://php.net/manual/en/function.pathinfo.php or SplFileInfo |
| RLAPI char **GetDirectoryFiles(const char *dirPath, int *count);   | TODO | see scandir() |
| RLAPI void ClearDirectoryFiles(void);                              | TODO ||
| RLAPI bool ChangeDirectory(const char *dir);                       | TODO | see chdir() |
| RLAPI bool IsFileDropped(void);                                    | TODO ||
| RLAPI char **GetDroppedFiles(int *count);                          | TODO ||
| RLAPI void ClearDroppedFiles(void);                                | TODO ||
| RLAPI long GetFileModTime(const char *fileName);                   | TODO | see filemtime() |
| RLAPI unsigned char *CompressData(unsigned char *data, int dataLength, int *compDataLength);        | TODO ||
| RLAPI unsigned char *DecompressData(unsigned char *compData, int compDataLength, int *dataLength);  | TODO ||



###  Persistent storage management
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void StorageSaveValue(int position, int value);             | N/A | May implement, See pack() |
| RLAPI int StorageLoadValue(int position);                         | N/A | May implement, See unpack() |

###  Input Handling Functions (Module: core)

####  Input-related functions: keyboard
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI bool IsKeyPressed(int key);                             | raylib\Input\Key::isPressed(int key) : bool ||
| RLAPI bool IsKeyDown(int key);                                | raylib\Input\Key::isDown(int key) : bool ||
| RLAPI bool IsKeyReleased(int key);                            | raylib\Input\Key::isReleased(int key) : bool ||
| RLAPI bool IsKeyUp(int key);                                  | raylib\Input\Key::isUp(int key) : bool ||
| RLAPI void SetExitKey(int key);                               | raylib\Input\Key::setExit(int $key) | This may move to Window class |
| RLAPI int GetKeyPressed(void);                                | raylib\Input\Key::getPressed(void) : int ||

####  Input-related functions: gamepads
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI bool IsGamepadAvailable(int gamepad);                   | raylib\Input\Gamepad::isAvailable(int $gamepad) ||
| RLAPI bool IsGamepadName(int gamepad, const char *name);      | raylib\Input\Gamepad::isName(int $gamepad, string $name) | probably better off using stristr() |
| RLAPI const char *GetGamepadName(int gamepad);                | raylib\Input\Gamepad::getName(int $gamepad) : string ||
| RLAPI bool IsGamepadButtonPressed(int gamepad, int button);   | raylib\Input\Gamepad::isButtonPressed(int $gamepad, int $button) : bool ||
| RLAPI bool IsGamepadButtonDown(int gamepad, int button);      | raylib\Input\Gamepad::isButtonDown(int $gamepad, int $button) : bool ||
| RLAPI bool IsGamepadButtonReleased(int gamepad, int button);  | raylib\Input\Gamepad::isButtonReleased(int $gamepad, int $button) : bool ||
| RLAPI bool IsGamepadButtonUp(int gamepad, int button);        | raylib\Input\Gamepad::isButtonUp(int $gamepad, int $button) : bool ||
| RLAPI int GetGamepadButtonPressed(void);                      | raylib\Input\Gamepad::getButtonPressed() : int ||
| RLAPI int GetGamepadAxisCount(int gamepad);                   | raylib\Input\Gamepad::getAxisCount(int $gamepad) : int ||
| RLAPI float GetGamepadAxisMovement(int gamepad, int axis);    | raylib\Input\Gamepad::getAxisMovement(int $gamepad, int $axis) : float ||

####  Input-related functions: mouse
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI bool IsMouseButtonPressed(int button);                  | raylib\Input\Mouse::isButtonPressed(int $button) : bool ||
| RLAPI bool IsMouseButtonDown(int button);                     | raylib\Input\Mouse::isButtonDown(int $button) : bool ||
| RLAPI bool IsMouseButtonReleased(int button);                 | raylib\Input\Mouse::isButtonReleased(int $button) : bool ||
| RLAPI bool IsMouseButtonUp(int button);                       | raylib\Input\Mouse::isButtonUp(int $button) : bool ||
| RLAPI int GetMouseX(void);                                    | raylib\Input\Mouse::getX() : int ||
| RLAPI int GetMouseY(void);                                    | raylib\Input\Mouse::getY() : int ||
| RLAPI Vector2 GetMousePosition(void);                         | raylib\Input\Mouse::getPosition() : Vector2 ||
| RLAPI void SetMousePosition(Vector2 position);                | raylib\Input\Mouse::setPosition(Vector2 $position) ||
| RLAPI void SetMouseOffset(int offsetX, int offsetY);          | raylib\Input\Mouse::setOffset(int $offsetX, int $offsetY) ||
| RLAPI void SetMouseScale(float scaleX, float scaleY);         | raylib\Input\Mouse::setScale(float $scaleX, float $scaleY) ||
| RLAPI int GetMouseWheelMove(void);                            | raylib\Input\Mouse::getWheelMove() : int ||

####  Input-related functions: touch
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI int GetTouchX(void);                                    | TODO ||
| RLAPI int GetTouchY(void);                                    | TODO ||
| RLAPI Vector2 GetTouchPosition(int index);                    | TODO ||

###  Gestures and Touch Handling Functions (Module: gestures)
| RLAPI void SetGesturesEnabled(unsigned int gestureFlags);     | TODO ||
| RLAPI bool IsGestureDetected(int gesture);                    | TODO ||
| RLAPI int GetGestureDetected(void);                           | TODO ||
| RLAPI int GetTouchPointsCount(void);                          | TODO ||
| RLAPI float GetGestureHoldDuration(void);                     | TODO ||
| RLAPI Vector2 GetGestureDragVector(void);                     | TODO ||
| RLAPI float GetGestureDragAngle(void);                        | TODO ||
| RLAPI Vector2 GetGesturePinchVector(void);                    | TODO ||
| RLAPI float GetGesturePinchAngle(void);                       | TODO ||

###  Camera System Functions (Module: camera3d)
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void SetCameraMode(Camera camera, int mode);                | TODO ||
| RLAPI void UpdateCamera(Camera *camera);                          | TODO ||
| RLAPI void SetCameraPanControl(int panKey);                       | TODO ||
| RLAPI void SetCameraAltControl(int altKey);                       | TODO ||
| RLAPI void SetCameraSmoothZoomControl(int szKey);                 | TODO ||
| RLAPI void SetCameraMoveControls(int frontKey, int backKey, int rightKey, int leftKey, int upKey, int downKey); | TODO ||


###  Basic Shapes Drawing Functions (Module: shapes)

####  Basic shapes drawing functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void DrawPixel(int posX, int posY, Color color);                                                   | raylib\Draw::pixel(int $posX, int $posY, array $color) | |
| RLAPI void DrawPixelV(Vector2 position, Color color);                                                    | raylib\Draw::pixelV(\raylib\Vector2 $position, array $color) | |
| RLAPI void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);                | raylib\Draw::line(int $startPosX, int $startPosY, int $endPosX, int $endPosY, \raylib\Color $color) | |
| RLAPI void DrawLineV(Vector2 startPos, Vector2 endPos, Color color);                                     | raylib\Draw::lineV(\raylib\Vector2 $startPos, \raylib\Vector2 $endPos, array $color) | |
| RLAPI void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color);                       | raylib\Draw::lineEx(\raylib\Vector2 $startPos, \raylib\Vector2 $endPos, float $thick, \raylib\Color $color) | |
| RLAPI void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color);                   | raylib\Draw::lineBezier(\raylib\Vector2 $startPos, \raylib\Vector2 $endPos, float $thick, \raylib\Color $color) | |
| RLAPI void DrawCircle(int centerX, int centerY, float radius, Color color);                              | raylib\Draw::circle(int $centerX, int $centerY, float $radius, \raylib\Color $color) | |
| RLAPI void DrawCircleSector(Vector2 center, float radius, int startAngle, int endAngle, int segments, Color color);      | raylib\Draw::circleSector(\raylib\Vector2 $center, float $radius, int $startAngle, int $endAngle, int $segments, \raylib\Color $color) ||
| RLAPI void DrawCircleSectorLines(Vector2 center, float radius, int startAngle, int endAngle, int segments, Color color); | raylib\Draw::circleSectorLines(\raylib\Vector2 $center, float $radius, int $startAngle, int $endAngle, int $segments, \raylib\Color $color) ||
| RLAPI void DrawCircleGradient(int centerX, int centerY, float radius, Color color1, Color color2);       | raylib\Draw::circleGradient(int $centerX, int $centerY, float $radius, array $color1, array $color2) | |
| RLAPI void DrawCircleV(Vector2 center, float radius, Color color);                                       | raylib\Draw::circleV(array $center, float $radius, array $color) | |
| RLAPI void DrawCircleLines(int centerX, int centerY, float radius, Color color);                         | raylib\Draw::circleLines(int $centerX, int $centerY, float $radius, array $color) | |
| RLAPI void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color);              | raylib\Draw::ellipse(int $centerX, int $centerY, float $radiusH, float $radiusV, Color $color) ||
| RLAPI void DrawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color);         | raylib\Draw::ellipseLines(int $centerX, int $centerY, float $radiusH, float $radiusV, Color $color) ||
| RLAPI void DrawRing(Vector2 center, float innerRadius, float outerRadius, int startAngle, int endAngle, int segments, Color color);      | raylib\Draw::ring(\raylib\Vector2 $center, float $innerRadius, float $outerRadius, int $startAngle, int $endAngle, int $segments, \raylib\Color $color) ||
| RLAPI void DrawRingLines(Vector2 center, float innerRadius, float outerRadius, int startAngle, int endAngle, int segments, Color color); | raylib\Draw::ringLines(\raylib\Vector2 $center, float $innerRadius, float $outerRadius, int $startAngle, int $endAngle, int $segments, \raylib\Color $color) ||
| RLAPI void DrawRectangle(int posX, int posY, int width, int height, Color color);                        | raylib\Draw::rectangle(int $posX, int $posY, int $width, int $height, array $color) | |
| RLAPI void DrawRectangleV(Vector2 position, Vector2 size, Color color);                                  | raylib\Draw::rectangleV(array $position, array $size, array $color) | |
| RLAPI void DrawRectangleRec(Rectangle rec, Color color);                                                 | raylib\Draw::rectangleRec(array $rec, array $color) | |
| RLAPI void DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color);                 | raylib\Draw::rectanglePro(array $rec, array $origin, float $rotation, array $color) | |
| RLAPI void DrawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2);| raylib\Draw::rectangleGradientV(int $posX, int $posY, int $width, int $height, array $color1, array $color2); | |
| RLAPI void DrawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2);| raylib\Draw::rectangleGradientV(int $posX, int $posY, int $width, int $height, array $color1, array $color2) ||
| RLAPI void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4);       | raylib\Draw::rectangleGradientEx(\raylib\Rectangle $rec, \raylib\Color $col1, \raylib\Color $col2, \raylib\Color $col3, Color $col4) ||
| RLAPI void DrawRectangleLines(int posX, int posY, int width, int height, Color color);                   | raylib\Draw::rectangleLines(int $posX, int $posY, int $width, int $height, array $color) | |
| RLAPI void DrawRectangleLinesEx(Rectangle rec, int lineThick, Color color);                              | raylib\Draw::rectangleRec(array $rec, int $lineThick, array $color) | |
| RLAPI void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);              | \Draw::rectangleRounded(\raylib\Rectangle $rec, float $roundness, int $segments, \raylib\Color color) ||
| RLAPI void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, int lineThick, Color color); | \Draw::rectangleRoundedLines(\raylib\Rectangle $rec, float $roundness, int $segments, int $lineThick, \raylib\Color color) ||
| RLAPI void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                                | raylib\Draw::triangle(array $v1, array $v2, array $v3, array $color) | |
| RLAPI void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                           | raylib\triangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color) | |
| RLAPI void DrawTriangleFan(Vector2 *points, int numPoints, Color color);                                 | raylib\Draw::triangleFan(array $points, Color $gray) ||
| RLAPI void DrawTriangleStrip(Vector2 *points, int pointsCount, Color color);                             | raylib\Draw::triangleStrip(array $points, Color $gray) ||
| RLAPI void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);               | raylib\Draw::poly(\raylib\Vector2 $center, int $sides, float $radius, float $rotation, \raylib\Color $color) ||
| RLAPI void DrawPolyLines(Vector2 center, int sides, float radius, float rotation, Color color);          | raylib\Draw::polyLines(\raylib\Vector2 $center, int $sides, float $radius, float $rotation, \raylib\Color $color) ||

####  Basic shapes collision detection functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2);                                           | raylib\Collision\checkRecs(Rectangle $rec1, Rectangle $rec2) ||
| RLAPI bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);        | raylib\Collision\checkCircles(Vector2 center1, float radius1, Vector2 center2, float radius2) ||
| RLAPI bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);                         | raylib\Collision\checkCircleRec(Vector2 center, float radius, Rectangle rec) ||
| RLAPI Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2);                                         | raylib\Collision\getRec(Rectangle rec1, Rectangle rec2) ||
| RLAPI bool CheckCollisionPointRec(Vector2 point, Rectangle rec);                                         | raylib\Collision\checkPointRec(Vector2 point, Rectangle rec) ||
| RLAPI bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);                       | raylib\Collision\checkPointCircle(Vector2 point, Vector2 center, float radius) ||
| RLAPI bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3);               | raylib\Collision\checkPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3) ||

## Texture Loading and Drawing Functions (Module: textures)

### Image/Texture2D data loading/unloading/saving functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI Image LoadImage(const char *fileName);                                                             | new raylib\Image(string $filename) ||
| RLAPI Image LoadImageEx(Color *pixels, int width, int height);                                           | raylib\Image::fromColors(raylib\Color[] $pixels, int $width, int $height) ||
| RLAPI Image LoadImagePro(void *data, int width, int height, int format);                                 | TODO ||
| RLAPI Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);       | TODO ||
| RLAPI void ExportImage(const char *fileName, Image image);                                               | TODO ||
| RLAPI void ExportImageAsCode(Image image, const char *fileName);                                         | TODO ||
| RLAPI Texture2D LoadTexture(const char *fileName);                                                       | new raylib\Texture(string $fileName) ||
| RLAPI Texture2D LoadTextureFromImage(Image image);                                                       | raylib\Image->toTexture() : Texture ||
| RLAPI TextureCubemap LoadTextureCubemap(Image image, int layoutType);                                    | TODO ||
| RLAPI RenderTexture2D LoadRenderTexture(int width, int height);                                          | new raylib\RenderTexture(int $width, int $height) ||
| RLAPI void UnloadImage(Image image);                                                                     | N/A | Use unset() on class |
| RLAPI void UnloadTexture(Texture2D texture);                                                             | N/A | Use unset() on class |
| RLAPI void UnloadRenderTexture(RenderTexture2D target);                                                  | N/A | Use unset() on class |
| RLAPI Color *GetImageData(Image image);                                                                  | TODO ||
| RLAPI Vector4 *GetImageDataNormalized(Image image);                                                      | TODO ||
| RLAPI Rectangle GetImageAlphaBorder(Image image, float threshold);                                       | TODO ||
| RLAPI int GetPixelDataSize(int width, int height, int format);                                           | TODO ||
| RLAPI Image GetTextureData(Texture2D texture);                                                           | TODO ||
| RLAPI Image GetScreenData(void);                                                                         | TODO ||
| RLAPI void UpdateTexture(Texture2D texture, const void *pixels);                                         | TODO ||


### Image manipulation functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI Image ImageCopy(Image image);                                                                                                    | raylib\Image::copy(array $image) : Image ||
| RLAPI Image ImageFromImage(Image image, Rectangle rec);                                                                                | TODO ||
| RLAPI void ImageToPOT(Image *image, Color fillColor);                                                                                  | raylib\Image::toPot(array $image, array $fillColor) ||
| RLAPI void ImageFormat(Image *image, int newFormat);                                                                                   | raylib\Image::format(array $image, int $newFormat) ||
| RLAPI void ImageAlphaMask(Image *image, Image alphaMask);                                                                              | TODO ||
| RLAPI void ImageAlphaClear(Image *image, Color color, float threshold);                                                                | TODO ||
| RLAPI void ImageAlphaCrop(Image *image, float threshold);                                                                              | TODO ||
| RLAPI void ImageAlphaPremultiply(Image *image);                                                                                        | TODO ||
| RLAPI void ImageCrop(Image *image, Rectangle crop);                                                                                    | TODO ||
| RLAPI void ImageResize(Image *image, int newWidth, int newHeight);                                                                     | TODO ||
| RLAPI void ImageResizeNN(Image *image,int newWidth,int newHeight);                                                                     | TODO ||
| RLAPI void ImageResizeCanvas(Image *image, int newWidth, int newHeight, int offsetX, int offsetY, Color color);                        | TODO ||
| RLAPI void ImageMipmaps(Image *image);                                                                                                 | TODO ||
| RLAPI void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp);                                                          | TODO ||
| RLAPI Color *ImageExtractPalette(Image image, int maxPaletteSize, int *extractCount);                                                  | TODO ||
| RLAPI Image ImageText(const char *text, int fontSize, Color color);                                                                    | raylib\Image::fromDefaultFont(string $text, int $fontSize, Color $color) ||
| RLAPI Image ImageTextEx(SpriteFont font, const char *text, float fontSize, int spacing, Color tint);                                   | raylib\Image::fromFont(Font $font, string $text, float $fontSize, int $spacing, Color $tint) ||
| RLAPI void ImageDraw(Image *dst, Image src, Rectangle srcRec, Rectangle dstRec);                                                       | TODO ||
| RLAPI void ImageDrawRectangle(Image *dst, Vector2 position, Rectangle rec, Color color);                                               | TODO ||
| RLAPI void ImageDrawText(Image *dst, Vector2 position, const char *text, int fontSize, Color color);                                   | TODO ||
| RLAPI void ImageDrawTextEx(Image *dst, Vector2 position, SpriteFont font, const char *text, float fontSize, int spacing, Color color); | TODO ||
| RLAPI void ImageFlipVertical(Image *image);                                                                                            | TODO ||
| RLAPI void ImageFlipHorizontal(Image *image);                                                                                          | TODO ||
| RLAPI void ImageColorTint(Image *image, Color color);                                                                                  | TODO ||
| RLAPI void ImageColorInvert(Image *image);                                                                                             | TODO ||
| RLAPI void ImageColorGrayscale(Image *image);                                                                                          | TODO ||
| RLAPI void ImageColorContrast(Image *image, float contrast);                                                                           | TODO ||
| RLAPI void ImageColorBrightness(Image *image, int brightness);                                                                         | TODO ||

### Image generation functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI Image GenImageColor(int width, int height, Color color);                                           | TODO ||
| RLAPI Image GenImageGradientV(int width, int height, Color top, Color bottom);                           | TODO ||
| RLAPI Image GenImageGradientH(int width, int height, Color left, Color right);                           | TODO ||
| RLAPI Image GenImageGradientRadial(int width, int height, float density, Color inner, Color outer);      | TODO ||
| RLAPI Image GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2);    | TODO ||
| RLAPI Image GenImageWhiteNoise(int width, int height, float factor);                                     | TODO ||
| RLAPI Image GenImagePerlinNoise(int width, int height, int offsetX, int offsetY, float scale);           | TODO ||
| RLAPI Image GenImageCellular(int width, int height, int tileSize);                                       | TODO ||


### Texture2D configuration functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void GenTextureMipmaps(Texture2D *texture);                                                        | raylib\Texture->genMipmaps() ||
| RLAPI void SetTextureFilter(Texture2D texture, int filterMode);                                          | raylib\Texture->setFilter(int $filterMode) ||
| RLAPI void SetTextureWrap(Texture2D texture, int wrapMode);                                              | raylib\Texture->setWrap(int $wrapMode) ||

### Texture2D drawing functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void DrawTexture(Texture2D texture, int posX, int posY, Color tint);                               | raylib\Texture->draw() ||
| RLAPI void DrawTextureV(Texture2D texture, Vector2 position, Color tint);                                | raylib\Texture->drawV() ||
| RLAPI void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);  | raylib\Texture->drawEx() ||
| RLAPI void DrawTextureRec(Texture2D texture, Rectangle sourceRec, Vector2 position, Color tint);         | raylib\Texture->drawRec() ||
| RLAPI void DrawTexturePro(Texture2D texture, Rectangle sourceRec, Rectangle destRec, Vector2 origin,float rotation, Color tint); | raylib\Texture->drawPro(Rectangle $sourceRec, Rectangle $destRec, Vector2 $origin, float $rotation, Color $tint)  ||

## Font Loading and Text Drawing Functions (Module: text)

### Font loading/unloading functions

| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI Font GetFontDefault(void);                                                            | TODO ||
| RLAPI Font LoadFont(const char *fileName);                                                  | TODO ||
| RLAPI Font LoadFontEx(const char *fileName, int fontSize, int *fontChars, int charsCount);  | TODO ||
| RLAPI Font LoadFontFromImage(Image image, Color key, int firstChar);                        | TODO ||
| RLAPI CharInfo *LoadFontData(const char *fileName, int fontSize, int *fontChars, int charsCount, int type); | \raylib\CharInfo::fromFontData(string $fileName, int fontSize, int[] $fontChars, int type) ||
| RLAPI Image GenImageFontAtlas(const CharInfo *chars, Rectangle **recs, int charsCount, int fontSize, int padding, int packMethod); | TODO ||
| RLAPI void UnloadFont(Font font);                                                           | TODO ||

### Text drawing functions

| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void DrawFPS(int posX, int posY);                                                     | raylib\Text\drawFps(int $posX, int $posY)
| RLAPI void DrawText(const char *text, int posX, int posY, int fontSize, Color color);       | raylib\Text\draw(string $text, int $posX, int $posY, int $fontSize, Color $color)
| RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint);                | TODO ||
| RLAPI void DrawTextRec(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);   | TODO ||
| RLAPI void DrawTextRecEx(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint); | TODO ||
| RLAPI void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float scale, Color tint);   | TODO ||

### Text misc. functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI int MeasureText(const char *text, int fontSize);                                      | raylib\Text\measure(string $text, int $fontSize) ||
| RLAPI Vector2 MeasureTextEx(Font font, const char *text, float fontSize, float spacing);    | TODO ||
| RLAPI int GetGlyphIndex(Font font, int codepoint);                                          | TODO ||

### Text strings management functions (no utf8 strings, only byte chars)
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI int TextCopy(char *dst, const char *src);                                             | TODO ||
| RLAPI bool TextIsEqual(const char *text1, const char *text2);                               | TODO ||
| RLAPI unsigned int TextLength(const char *text);                                            | TODO ||
| RLAPI const char *TextFormat(const char *text, ...);                                        | TODO ||
| RLAPI const char *TextSubtext(const char *text, int position, int length);                  | TODO ||
| RLAPI char *TextReplace(char *text, const char *replace, const char *by);                   | TODO ||
| RLAPI char *TextInsert(const char *text, const char *insert, int position);                 | TODO ||
| RLAPI const char *TextJoin(const char **textList, int count, const char *delimiter);        | TODO ||
| RLAPI const char **TextSplit(const char *text, char delimiter, int *count);                 | TODO ||
| RLAPI void TextAppend(char *text, const char *append, int *position);                       | TODO ||
| RLAPI int TextFindIndex(const char *text, const char *find);                                | TODO ||
| RLAPI const char *TextToUpper(const char *text);                      | TODO ||
| RLAPI const char *TextToLower(const char *text);                      | TODO ||
| RLAPI const char *TextToPascal(const char *text);                     | TODO ||
| RLAPI int TextToInteger(const char *text);                            | TODO ||
| RLAPI char *TextToUtf8(int *codepoints, int length);                  | TODO ||

## UTF8 text strings management functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI int *GetCodepoints(const char *text, int *count);               | TODO ||
| RLAPI int GetCodepointsCount(const char *text);                       | TODO ||
| RLAPI int GetNextCodepoint(const char *text, int *bytesProcessed);    | TODO ||
| RLAPI const char *CodepointToUtf8(int codepoint, int *byteLength);    | TODO ||

## Basic 3d Shapes Drawing Functions (Module: models)

### Basic geometric 3D shapes drawing functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void DrawLine3D(Vector3 startPos, Vector3 endPos, Color color);                                    | TODO ||
| RLAPI void DrawPoint3D(Vector3 position, Color color);                                                   | TODO ||
| RLAPI void DrawCircle3D(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color); | TODO ||
| RLAPI void DrawCube(Vector3 position, float width, float height, float length, Color color);             | TODO ||
| RLAPI void DrawCubeV(Vector3 position, Vector3 size, Color color);                                       | TODO ||
| RLAPI void DrawCubeWires(Vector3 position, float width, float height, float length, Color color);        | TODO ||
| RLAPI void DrawCubeWiresV(Vector3 position, Vector3 size, Color color);                                  | TODO ||
| RLAPI void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color); | TODO ||
| RLAPI void DrawSphere(Vector3 centerPos, float radius, Color color);                                     | TODO ||
| RLAPI void DrawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color);            | TODO ||
| RLAPI void DrawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color);         | TODO ||
| RLAPI void DrawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color); | TODO ||
| RLAPI void DrawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color); | TODO ||
| RLAPI void DrawPlane(Vector3 centerPos, Vector2 size, Color color);                                      | TODO ||
| RLAPI void DrawRay(Ray ray, Color color);                                                                | TODO ||
| RLAPI void DrawGrid(int slices, float spacing);                                                          | TODO ||
| RLAPI void DrawGizmo(Vector3 position);                                                                  | TODO ||

## Model 3d Loading and Drawing Functions (Module: models)

### Model loading/unloading functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI Model LoadModel(const char *fileName);                                                            | TODO ||
| RLAPI Model LoadModelFromMesh(Mesh mesh);                                                               | TODO ||
| RLAPI void UnloadModel(Model model);                                                                    | TODO ||

### Mesh loading/unloading functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI Mesh *LoadMeshes(const char *fileName, int *meshCount);                                           | TODO ||
| RLAPI void ExportMesh(Mesh mesh, const char *fileName);                                                 | TODO ||
| RLAPI void UnloadMesh(Mesh mesh);                                                                       | TODO ||

### Material loading/unloading functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI Material *LoadMaterials(const char *fileName, int *materialCount);                                | TODO ||
| RLAPI Material LoadMaterialDefault(void);                                                               | TODO ||
| RLAPI void UnloadMaterial(Material material);                                                           | TODO ||
| RLAPI void SetMaterialTexture(Material *material, int mapType, Texture2D texture);                      | TODO ||
| RLAPI void SetModelMeshMaterial(Model *model, int meshId, int materialId);                              | TODO ||

### Model animations loading/unloading functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI ModelAnimation *LoadModelAnimations(const char *fileName, int *animsCount);                       | TODO ||
| RLAPI void UpdateModelAnimation(Model model, ModelAnimation anim, int frame);                           | TODO ||
| RLAPI void UnloadModelAnimation(ModelAnimation anim);                                                   | TODO ||
| RLAPI bool IsModelAnimationValid(Model model, ModelAnimation anim);                                     | TODO ||

### Mesh generation functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI Mesh GenMeshPoly(int sides, float radius);                                                        | TODO ||
| RLAPI Mesh GenMeshPlane(float width, float length, int resX, int resZ);                                 | TODO ||
| RLAPI Mesh GenMeshCube(float width, float height, float length);                                        | TODO ||
| RLAPI Mesh GenMeshSphere(float radius, int rings, int slices);                                          | TODO ||
| RLAPI Mesh GenMeshHemiSphere(float radius, int rings, int slices);                                      | TODO ||
| RLAPI Mesh GenMeshCylinder(float radius, float height, int slices);                                     | TODO ||
| RLAPI Mesh GenMeshTorus(float radius, float size, int radSeg, int sides);                               | TODO ||
| RLAPI Mesh GenMeshKnot(float radius, float size, int radSeg, int sides);                                | TODO ||
| RLAPI Mesh GenMeshHeightmap(Image heightmap, Vector3 size);                                             | TODO ||
| RLAPI Mesh GenMeshCubicmap(Image cubicmap, Vector3 cubeSize);                                           | TODO ||

### Mesh manipulation functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI BoundingBox MeshBoundingBox(Mesh mesh);                                                           | TODO ||
| RLAPI void MeshTangents(Mesh *mesh);                                                                    | TODO ||
| RLAPI void MeshBinormals(Mesh *mesh);                                                                   | TODO ||

### Model drawing functions
| C API | PHP API | Comment |
|-------|---------|---------|
RLAPI void DrawModel(Model model, Vector3 position, float scale, Color tint);                                                     | TODO ||
RLAPI void DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);      | TODO ||
RLAPI void DrawModelWires(Model model, Vector3 position, float scale, Color tint);                                                | TODO ||
RLAPI void DrawModelWiresEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint); | TODO ||
RLAPI void DrawBoundingBox(BoundingBox box, Color color);                                                                         | TODO ||
RLAPI void DrawBillboard(Camera camera, Texture2D texture, Vector3 center, float size, Color tint);                               | TODO ||
RLAPI void DrawBillboardRec(Camera camera, Texture2D texture, Rectangle sourceRec, Vector3 center, float size, Color tint);       | TODO ||

### Collision detection functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI bool CheckCollisionSpheres(Vector3 centerA, float radiusA, Vector3 centerB, float radiusB);       | TODO ||
| RLAPI bool CheckCollisionBoxes(BoundingBox box1, BoundingBox box2);                                     | TODO ||
| RLAPI bool CheckCollisionBoxSphere(BoundingBox box, Vector3 center, float radius);                      | TODO ||
| RLAPI bool CheckCollisionRaySphere(Ray ray, Vector3 center, float radius);                              | TODO ||
| RLAPI bool CheckCollisionRaySphereEx(Ray ray, Vector3 center, float radius, Vector3 *collisionPoint);   | TODO ||
| RLAPI bool CheckCollisionRayBox(Ray ray, BoundingBox box);                                              | TODO ||
| RLAPI RayHitInfo GetCollisionRayModel(Ray ray, Model model);                                            | TODO ||
| RLAPI RayHitInfo GetCollisionRayTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3);                  | TODO ||
| RLAPI RayHitInfo GetCollisionRayGround(Ray ray, float groundHeight);                                    | TODO ||

## Shaders System Functions (Module: rlgl)

### Shader loading/unloading functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI Shader LoadShader(const char *vsFileName, const char *fsFileName);  | TODO ||
| RLAPI Shader LoadShaderCode(const char *vsCode, const char *fsCode);      | TODO ||
| RLAPI void UnloadShader(Shader shader);                                   | TODO ||
| RLAPI Shader GetShaderDefault(void);                                      | TODO ||
| RLAPI Texture2D GetTextureDefault(void);                                  | TODO ||
| RLAPI Texture2D GetShapesTexture(void);                                   | TODO ||
| RLAPI Rectangle GetShapesTextureRec(void);                                | TODO ||
| RLAPI void SetShapesTexture(Texture2D texture, Rectangle source);         | TODO ||

### Shader configuration functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI int GetShaderLocation(Shader shader, const char *uniformName);      | TODO ||
| RLAPI void SetShaderValue(Shader shader, int uniformLoc, const void *value, int uniformType);               | TODO ||
| RLAPI void SetShaderValueV(Shader shader, int uniformLoc, const void *value, int uniformType, int count);   | TODO ||
| RLAPI void SetShaderValueMatrix(Shader shader, int uniformLoc, Matrix mat);         | TODO ||
| RLAPI void SetShaderValueTexture(Shader shader, int uniformLoc, Texture2D texture); | TODO ||
| RLAPI void SetMatrixProjection(Matrix proj);                              | TODO ||
| RLAPI void SetMatrixModelview(Matrix view);                               | TODO ||
| RLAPI Matrix GetMatrixModelview(void);                                    | TODO ||
| RLAPI Matrix GetMatrixProjection(void);                                   | TODO ||

### Texture maps generation (PBR)
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI Texture2D GenTextureCubemap(Shader shader, Texture2D map, int size);           | TODO ||
| RLAPI Texture2D GenTextureIrradiance(Shader shader, Texture2D cubemap, int size);    | TODO ||
| RLAPI Texture2D GenTexturePrefilter(Shader shader, Texture2D cubemap, int size);     | TODO ||
| RLAPI Texture2D GenTextureBRDF(Shader shader, int size);                             | TODO ||

### Shading begin/end functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void BeginShaderMode(Shader shader);                                | TODO ||
| RLAPI void EndShaderMode(void);                                           | TODO ||
| RLAPI void BeginBlendMode(int mode);                                      | TODO ||
| RLAPI void EndBlendMode(void);                                            | TODO ||

### VR control functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void InitVrSimulator(void);                       | TODO ||
| RLAPI void CloseVrSimulator(void);                      | TODO ||
| RLAPI void UpdateVrTracking(Camera *camera);            | TODO ||
| RLAPI void SetVrConfiguration(VrDeviceInfo info, Shader distortion);      | TODO ||
| RLAPI bool IsVrSimulatorReady(void);                    | TODO ||
| RLAPI void ToggleVrMode(void);                          | TODO ||
| RLAPI void BeginVrDrawing(void);                        | TODO ||
| RLAPI void EndVrDrawing(void);                          | TODO ||

## Audio Loading and Playing Functions (Module: audio)

### Audio device management functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void InitAudioDevice(void);                                     | raylib\Audio\initDevice() ||
| RLAPI void CloseAudioDevice(void);                                    | raylib\Audio\closeDevice() ||
| RLAPI bool IsAudioDeviceReady(void);                                  | raylib\Audio\isDeviceReady() ||
| RLAPI void SetMasterVolume(float volume);                             | raylib\Audio\setMasterVolume(float $volume) ||

### Wave/Sound loading/unloading functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI Wave LoadWave(const char *fileName);                               | new raylib\Wave(string $fileName) ||
| RLAPI Sound LoadSound(const char *fileName);                             | TODO ||
| RLAPI Sound LoadSoundFromWave(Wave wave);                                | TODO ||
| RLAPI void UpdateSound(Sound sound, const void *data, int samplesCount); | TODO ||
| RLAPI void UnloadWave(Wave wave);                                        | N/A | use built-in unset()|
| RLAPI void UnloadSound(Sound sound);                                     | TODO ||
| RLAPI void ExportWave(Wave wave, const char *fileName);                  | raylib\Wave\export(string $fileName) ||
| RLAPI void ExportWaveAsCode(Wave wave, const char *fileName);            | raylib\Wave\exportAsCode(string $fileName) ||

### Wave/Sound management functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI void PlaySound(Sound sound);                                    | TODO ||
| RLAPI void StopSound(Sound sound);                                    | TODO ||
| RLAPI void PauseSound(Sound sound);                                   | TODO ||
| RLAPI void ResumeSound(Sound sound);                                  | TODO ||
| RLAPI void PlaySoundMulti(Sound sound);                               | TODO ||
| RLAPI void StopSoundMulti(void);                                      | TODO ||
| RLAPI int GetSoundsPlaying(void);                                     | TODO ||
| RLAPI bool IsSoundPlaying(Sound sound);                               | TODO ||
| RLAPI void SetSoundVolume(Sound sound, float volume);                 | TODO ||
| RLAPI void SetSoundPitch(Sound sound, float pitch);                   | TODO ||
| RLAPI void WaveFormat(Wave *wave, int sampleRate, int sampleSize, int channels); | raylib\Wave\format(int $sampleRate, int $sampleSize, int $channels) ||
| RLAPI Wave WaveCopy(Wave wave);                                       | raylib\Wave\copy() ||
| RLAPI void WaveCrop(Wave *wave, int initSample, int finalSample);     | raylib\Wave\crop(int $initSample, int $finalSample) ||
| RLAPI float *GetWaveData(Wave wave);                                  | raylib\Wave\getData() ||

### Music management functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI Music LoadMusicStream(const char *fileName);                    | TODO ||
| RLAPI void UnloadMusicStream(Music music);                            | TODO ||
| RLAPI void PlayMusicStream(Music music);                              | TODO ||
| RLAPI void UpdateMusicStream(Music music);                            | TODO ||
| RLAPI void StopMusicStream(Music music);                              | TODO ||
| RLAPI void PauseMusicStream(Music music);                             | TODO ||
| RLAPI void ResumeMusicStream(Music music);                            | TODO ||
| RLAPI bool IsMusicPlaying(Music music);                               | TODO ||
| RLAPI void SetMusicVolume(Music music, float volume);                 | TODO ||
| RLAPI void SetMusicPitch(Music music, float pitch);                   | TODO ||
| RLAPI void SetMusicLoopCount(Music music, int count);                 | TODO ||
| RLAPI float GetMusicTimeLength(Music music);                          | TODO ||
| RLAPI float GetMusicTimePlayed(Music music);                          | TODO ||

### AudioStream management functions
| C API | PHP API | Comment |
|-------|---------|---------|
| RLAPI AudioStream InitAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels); | TODO ||
| RLAPI void UpdateAudioStream(AudioStream stream, const void *data, int samplesCount); | TODO ||
| RLAPI void CloseAudioStream(AudioStream stream);                      | TODO ||
| RLAPI bool IsAudioStreamProcessed(AudioStream stream);                | TODO ||
| RLAPI void PlayAudioStream(AudioStream stream);                       | TODO ||
| RLAPI void PauseAudioStream(AudioStream stream);                      | TODO ||
| RLAPI void ResumeAudioStream(AudioStream stream);                     | TODO ||
| RLAPI bool IsAudioStreamPlaying(AudioStream stream);                  | TODO ||
| RLAPI void StopAudioStream(AudioStream stream);                       | TODO ||
| RLAPI void SetAudioStreamVolume(AudioStream stream, float volume);    | TODO ||
| RLAPI void SetAudioStreamPitch(AudioStream stream, float pitch);      | TODO ||
| RLAPI void SetAudioStreamBufferSizeDefault(int size);                 | TODO ||
