# raylib to PHP Mapping / Progress

This is a one to one mapping of each raylib function.

##Window-related functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void InitWindow(int width, int height, const char *title); | raylib\Window::init() |  |
| bool WindowShouldClose(void); | raylib\Window::shouldClose() : bool |  |
| void CloseWindow(void); | raylib\Window::close() |  |
| bool IsWindowReady(void); | raylib\Window::isReady() : bool |  |
| bool IsWindowFullscreen(void); | raylib\Window::isWindowFullscreen() |  |
| bool IsWindowHidden(void); | raylib\Window::isHidden() : bool |  |
| bool IsWindowMinimized(void); | raylib\Window::isMinimized() : bool |  |
| bool IsWindowMaximized(void); | raylib\Window::isMaximized() : bool |  |
| bool IsWindowFocused(void); | raylib\Window::isFocused() : bool |  |
| bool IsWindowResized(void); | raylib\Window::isResized() : bool |  |
| bool IsWindowState(unsigned int flag); | raylib\Window::isState(int $flags) : bool |  |
| void SetWindowState(unsigned int flags); | raylib\Window::setState(int $flags) |  |
| void ClearWindowState(unsigned int flags); | raylib\Window::clearState(int $flags) |  |
| void ToggleFullscreen(void); | raylib\Window::toggleFullscreen() |  |
| void MaximizeWindow(void); | raylib\Window::maximize() |  |
| void MinimizeWindow(void); | raylib\Window::minimize() |  |
| void RestoreWindow(void); | raylib\Window::restore() |  |
| void SetWindowIcon(Image image); | raylib\Window::setIcon(\raylib\Image $image) |  |
| void SetWindowTitle(const char *title); | raylib\Window::setTitle(string $title) |  |
| void SetWindowPosition(int x, int y); | raylib\Window::setPosition(int $x, int $y) |  |
| void SetWindowMonitor(int monitor); | raylib\Window::setMonitor(int $monitor) |  |
| void SetWindowMinSize(int width, int height); | raylib\Window::setMinSize(int $width, int $height) |  |
| void SetWindowSize(int width, int height); | raylib\Window::setSize(int $width, int $height) |  |
| void *GetWindowHandle(void); | -- | Cannot Implement |
| int GetScreenWidth(void); | raylib\Window::getScreenWidth() : int  |  |
| int GetScreenHeight(void); | raylib\Window::getScreenHeight() : int  |  |
| int GetMonitorCount(void); | raylib\Window::getMonitorCount() : int  |  |
| Vector2 GetMonitorPosition(int monitor); | raylib\Window::getMonitorPosition(int $monitor) : \raylib\Vector2 |  |
| int GetMonitorWidth(int monitor); | raylib\Window::getMonitorWidth(int $monitor) : int  |  |
| int GetMonitorHeight(int monitor); | raylib\Window::getMonitorHeight(int $monitor) : int  |  |
| int GetMonitorPhysicalWidth(int monitor); | raylib\Window::getMonitorPhysicalWidth(int $monitor) : int  |  |
| int GetMonitorPhysicalHeight(int monitor); | raylib\Window::getMonitorPhysicalHeight(int $monitor) : int  |  |
| int GetMonitorRefreshRate(int monitor); | raylib\Window::getMonitorRefreshRate(int $monitor) : int  |  |
| Vector2 GetWindowPosition(void); | raylib\Window::getPosition() : \raylib\Vector2 |  |
| Vector2 GetWindowScaleDPI(void); | raylib\Window::getScaleDPI() : \raylib\Vector2 |  |
| const char *GetMonitorName(int monitor); | raylib\Window::getMonitorName(int $monitor) : string |  |
| void SetClipboardText(const char *text); | raylib\Window::setClipboardText(string $text) |  |
| const char *GetClipboardText(void); | raylib\Window::getClipboardText() : string |  |


##            

| C API | PHP API | Comment |
|-------|---------|---------|


##Cursor-related functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void ShowCursor(void); | raylib\Cursor::show() |  |
| void HideCursor(void); | raylib\Cursor::hide() |  |
| bool IsCursorHidden(void); | raylib\Cursor::isHidden() |  |
| void EnableCursor(void); | raylib\Cursor::enable() |  |
| void DisableCursor(void); | raylib\Cursor::disable() |  |


##bool IsCursorOnScreen(void)

| C API | PHP API | Comment |
|-------|---------|---------|


##            

| C API | PHP API | Comment |
|-------|---------|---------|


##Drawing-related functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void ClearBackground(Color color); | raylib\Draw::clearBackground(raylib\Color $color) |  |
| void BeginDrawing(void); | raylib\Draw::begin() |  |
| void EndDrawing(void); | raylib\Draw::end() |  |
| void BeginMode2D(Camera2D camera); | raylib\Draw::beginMode2d(raylib\Camera2D $camera2d) |  |
| void EndMode2D(void); | raylib\Draw::endMode2d() |  |
| void BeginMode3D(Camera3D camera); | raylib\Draw::beginMode3d(raylib\Camera3D camera3d) |  |
| void EndMode3D(void); | raylib\Draw::endMode3d() |  |
| void BeginTextureMode(RenderTexture2D target); | raylib\RenderTexture->begin() |  |
| void EndTextureMode(void); | raylib\RenderTexture->end() |  |
| void BeginScissorMode(int x, int y, int width, int height); | raylib\Draw::beginScissorMode() |  |
| void EndScissorMode(void); | raylib\Draw::endScissorMode() |  |


##Screen-space-related functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Ray GetMouseRay(Vector2 mousePosition, Camera camera); | TODO |  |
| Matrix GetCameraMatrix(Camera camera); | TODO |  |
| Matrix GetCameraMatrix2D(Camera2D camera); | TODO |  |
| Vector2 GetWorldToScreen(Vector3 position, Camera camera); | TODO |  |
| Vector2 GetWorldToScreenEx(Vector3 position, Camera camera, int width, int height); | TODO |  |
| Vector2 GetWorldToScreen2D(Vector2 position, Camera2D camera); | TODO |  |
| Vector2 GetScreenToWorld2D(Vector2 position, Camera2D camera); | TODO |  |


##Timing-related functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void SetTargetFPS(int fps); | raylib\Timming::setTargetFPS(int $fps) |  |
| int GetFPS(void); | raylib\Timming::getFPS() : int |  |
| float GetFrameTime(void); | raylib\Timming::getFrameTime() : float |  |
| double GetTime(void); | raylib\Timming::getTime() : float |  |


##            

| C API | PHP API | Comment |
|-------|---------|---------|


##Misc. functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void SetConfigFlags(unsigned int flags); | \raylib\SetConfigFlags(int $flags) |  |


##            

| C API | PHP API | Comment |
|-------|---------|---------|
| void SetTraceLogLevel(int logType); | TODO |  |
| void SetTraceLogExit(int logType); | TODO |  |
| void SetTraceLogCallback(TraceLogCallback callback); | TODO |  |
| void TraceLog(int logType, const char *text, ...); | TODO |  |


##            

| C API | PHP API | Comment |
|-------|---------|---------|
| void *MemAlloc(int size); | -- | unused |
| void MemFree(void *ptr); | -- | unused |
| void TakeScreenshot(const char *fileName); | \raylib\TakeScreenshot(string $fileName) |  |
| int GetRandomValue(int min, int max); | -- | see rand() |


##Files management functions

| C API | PHP API | Comment |
|-------|---------|---------|
| unsigned char *LoadFileData(const char *fileName, unsigned int *bytesRead); | -- | see file_get_contents() |
| void UnloadFileData(unsigned char *data); | -- | not needed |
| bool SaveFileData(const char *fileName, void *data, unsigned int bytesToWrite); | -- | see file_put_contents() |
| char *LoadFileText(const char *fileName); | -- | see file_get_contents() |
| void UnloadFileText(unsigned char *text); | -- | not needed |
| bool SaveFileText(const char *fileName, char *text); | -- | see file_put_contents() |
| bool FileExists(const char *fileName); | -- | see file_exists() |
| bool DirectoryExists(const char *dirPath); | -- | see is_dir() |
| bool IsFileExtension(const char *fileName, const char *ext); | -- | not needed |
| const char *GetFileExtension(const char *fileName); | -- | http://php.net/manual/en/function.pathinfo.php or SplFileInfo |
| const char *GetFileName(const char *filePath); | -- | http://php.net/manual/en/function.pathinfo.php or SplFileInfo |
| const char *GetFileNameWithoutExt(const char *filePath); | -- | http://php.net/manual/en/function.pathinfo.php or SplFileInfo |
| const char *GetDirectoryPath(const char *filePath); | -- | http://php.net/manual/en/function.pathinfo.php or SplFileInfo |
| const char *GetPrevDirectoryPath(const char *dirPath); | -- | http://php.net/manual/en/function.pathinfo.php or SplFileInfo |
| const char *GetWorkingDirectory(void); | -- | http://php.net/manual/en/function.getcwd.php |
| char **GetDirectoryFiles(const char *dirPath, int *count); | -- | http://php.net/manual/en/function.dir.php |
| void ClearDirectoryFiles(void); | -- | not needed |
| bool ChangeDirectory(const char *dir); | -- | http://php.net/manual/en/function.chdir.php |
| bool IsFileDropped(void); | TODO |  |
| char **GetDroppedFiles(int *count); | TODO |  |
| void ClearDroppedFiles(void); | TODO |  |
| long GetFileModTime(const char *fileName); | -- | http://php.net/manual/en/function.filemtime.php |
| unsigned char *CompressData(unsigned char *data, int dataLength, int *compDataLength); |  | http://php.net/manual/en/function.gzdeflate.php |
| unsigned char *DecompressData(unsigned char *compData, int compDataLength, int *dataLength); |  | http://php.net/manual/en/function.gzinflate.php |


##Input-related functions: keyboard

| C API | PHP API | Comment |
|-------|---------|---------|
| bool IsKeyPressed(int key); | raylib\Input\Key::isPressed(int $key) : bool |  |
| bool IsKeyDown(int key); | raylib\Input\Key::isDown(int $key) : bool |  |
| bool IsKeyReleased(int key); | raylib\Input\Key::isReleased(int $key) : bool |  |
| bool IsKeyUp(int key); | raylib\Input\Key::isUp(int $key) : bool |  |
| void SetExitKey(int key); | raylib\Input\Key::setExit(int $key) |  |
| int GetKeyPressed(void); | raylib\Input\Key::getPressed() : int |  |
| int GetCharPressed(void); | raylib\Input\Key::getKeyPressed() : int |  |


##Input-related functions: gamepads

| C API | PHP API | Comment |
|-------|---------|---------|
| bool IsGamepadAvailable(int gamepad); | raylib\Input\Gamepad::isAvailable(int $gamepad) : bool |  |
| bool IsGamepadName(int gamepad, const char *name); | raylib\Input\Gamepad::isName(int $gamepad) : bool |  |
| const char *GetGamepadName(int gamepad); | raylib\Input\Gamepad::getName(int $gamepad) : string |  |
| bool IsGamepadButtonPressed(int gamepad, int button); | raylib\Input\Gamepad::isButtonPressed(int $gamepad, int $button) : bool |  |
| bool IsGamepadButtonDown(int gamepad, int button); | raylib\Input\Gamepad::isButtonDown(int $gamepad, int $button) : bool |  |
| bool IsGamepadButtonReleased(int gamepad, int button); | raylib\Input\Gamepad::isButtonReleased(int $gamepad, int $button) : bool |  |
| bool IsGamepadButtonUp(int gamepad, int button); | raylib\Input\Gamepad::isButtonUp(int $gamepad, int $button) : bool |  |
| int GetGamepadButtonPressed(void); | raylib\Input\Gamepad::getButtonPressed() : int |  |
| int GetGamepadAxisCount(int gamepad); | raylib\Input\Gamepad::getAxisCount(int $gamepad) : int |  |
| float GetGamepadAxisMovement(int gamepad, int axis); | raylib\Input\Gamepad::getAxisMovement(int $gamepad, int $axis) : float |  |


##Input-related functions: mouse

| C API | PHP API | Comment |
|-------|---------|---------|
| bool IsMouseButtonPressed(int button); | raylib\Input\Mouse::isButtonPressed(int $button) : bool |  |
| bool IsMouseButtonDown(int button); | raylib\Input\Mouse::isButtonDown(int $button) : bool |  |
| bool IsMouseButtonReleased(int button); | raylib\Input\Mouse::isButtonReleased(int $button) : bool |  |
| bool IsMouseButtonUp(int button); | raylib\Input\Mouse::isButtonUp(int $button) : bool |  |
| int GetMouseX(void); | raylib\Input\Mouse::getX() : int |  |
| int GetMouseY(void); | raylib\Input\Mouse::getY() : int |  |
| Vector2 GetMousePosition(void); | raylib\Input\Mouse::getPosition() : Vector2 |  |
| void SetMousePosition(int x, int y); | raylib\Input\Mouse::setPosition(int $x, int $y) |  |
| void SetMouseOffset(int offsetX, int offsetY); | raylib\Input\Mouse::setOffset(int $offsetX, int $offsetY) |  |
| void SetMouseScale(float scaleX, float scaleY); | raylib\Input\Mouse::setScale(float $scaleX, float $scaleY) |  |
| float GetMouseWheelMove(void); | raylib\Input\Mouse::getWheelMove() : float |  |
| int GetMouseCursor(void); | raylib\Input\Mouse::getCursor() : int |  |
| void SetMouseCursor(int cursor); | raylib\Input\Mouse::setCursor(int $cursor) |  |


##Input-related functions: touch

| C API | PHP API | Comment |
|-------|---------|---------|
| int GetTouchX(void); | TODO |  |
| int GetTouchY(void); | TODO |  |
| Vector2 GetTouchPosition(int index); | TODO |  |


##Gestures and Touch Handling Functions (Module: gestures)

| C API | PHP API | Comment |
|-------|---------|---------|
| void SetGesturesEnabled(unsigned int gestureFlags); | TODO |  |
| bool IsGestureDetected(int gesture); | TODO |  |
| int GetGestureDetected(void); | TODO |  |
| int GetTouchPointsCount(void); | TODO |  |
| float GetGestureHoldDuration(void); | TODO |  |
| Vector2 GetGestureDragVector(void); | TODO |  |
| float GetGestureDragAngle(void); | TODO |  |
| Vector2 GetGesturePinchVector(void); | TODO |  |
| float GetGesturePinchAngle(void); | TODO |  |


##Camera System Functions (Module: camera)

| C API | PHP API | Comment |
|-------|---------|---------|
| void SetCameraMode(Camera camera, int mode); | TODO |  |
| void UpdateCamera(Camera *camera); | TODO |  |
| void SetCameraPanControl(int keyPan); | TODO |  |
| void SetCameraAltControl(int keyAlt); | TODO |  |
| void SetCameraSmoothZoomControl(int keySmoothZoom); | TODO |  |
| void SetCameraMoveControls(int keyFront, int keyBack, int keyRight, int keyLeft, int keyUp, int keyDown); | TODO |  |


##Basic shapes drawing functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void DrawPixel(int posX, int posY, Color color); | raylib\Draw::pixel(int $posX, int $posY, raylib\Color $color) |  |
| void DrawPixelV(Vector2 position, Color color); | raylib\Draw::pixelV(raylib\Vector2 $position, raylib\Color $color) |  |
| void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color); | raylib\Draw::line(int $startPosX, int $startPosY, int $endPosX, int $endPosY, raylib\Color $color) |  |
| void DrawLineV(Vector2 startPos, Vector2 endPos, Color color); | raylib\Draw::lineV(raylib\Vector2 $startPos, raylib\Vector2 $endPos, raylib\Color $color) |  |
| void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color); | raylib\Draw::lineEx(raylib\Vector2 $startPos, raylib\Vector2 $endPos, float $thick, raylib\Color $color) |  |
| void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color); | raylib\Draw::lineBezier(raylib\Vector2 $startPos, raylib\Vector2 $endPos, float $thick, raylib\Color $color) |  |
| void DrawLineStrip(Vector2 *points, int pointsCount, Color color); | TODO |  |
| void DrawCircle(int centerX, int centerY, float radius, Color color); | raylib\Draw::circle(int $centerX, int $centerY, float $radius, raylib\Color $color) |  |
| void DrawCircleSector(Vector2 center, float radius, int startAngle, int endAngle, int segments, Color color); | raylib\Draw::circleSector(raylib\Vector2 $center, float $radius, int $startAngle, int $endAngle, int $segments, raylib\Color $color) |  |
| void DrawCircleSectorLines(Vector2 center, float radius, int startAngle, int endAngle, int segments, Color color); | raylib\Draw::circleSectorLines(raylib\Vector2 $center, float $radius, int $startAngle, int $endAngle, int $segments, raylib\Color $color) |  |
| void DrawCircleGradient(int centerX, int centerY, float radius, Color color1, Color color2); | raylib\Draw::circleGradient(int $centerX, int $centerY, float $radius, raylib\Color $color1, raylib\Color $color2) |  |
| void DrawCircleV(Vector2 center, float radius, Color color); | raylib\Draw::circleV(raylib\Vector2 $center, float $radius, raylib\Color $color) |  |
| void DrawCircleLines(int centerX, int centerY, float radius, Color color); | raylib\Draw::circleLines(int $centerX, int $centerY, float $radius, raylib\Color $color) |  |
| void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color); | raylib\Draw::ellipse(int $centerX, int $centerY, float $radiusH, float $radiusV, raylib\Color $color) |  |
| void DrawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color); | raylib\Draw::ellipseLines(int $centerX, int $centerY, float $radiusH, float $radiusV, raylib\Color $color) |  |
| void DrawRing(Vector2 center, float innerRadius, float outerRadius, int startAngle, int endAngle, int segments, Color color); | raylib\Draw::ring(raylib\Vector2 $center, float $innerRadius, float $outerRadius, int $startAngle, int $endAngle, int $segments, raylib\Color $color) |  |
| void DrawRingLines(Vector2 center, float innerRadius, float outerRadius, int startAngle, int endAngle, int segments, Color color); | raylib\Draw::ringLines(raylib\Vector2 $center, float $innerRadius, float $outerRadius, int $startAngle, int $endAngle, int $segments, raylib\Color $color) |  |
| void DrawRectangle(int posX, int posY, int width, int height, Color color); | raylib\Draw::rectangle(int $posX, int $posY, int $width, int $height, raylib\Color $color) |  |
| void DrawRectangleV(Vector2 position, Vector2 size, Color color); | raylib\Draw::rectangleV(raylib\Vector2 $position, raylib\Vector2 $size, raylib\Color $color) |  |
| void DrawRectangleRec(Rectangle rec, Color color); | raylib\Draw::rectangleRec(raylib\Rectangle $rec, raylib\Color $color) |  |
| void DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color); | raylib\Draw::rectanglePro(raylib\Rectangle $rec, raylib\Vector2 $origin, float $rotation, raylib\Color $color) |  |
| void DrawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2); | raylib\Draw::rectangleGradientV(int $posX, int $posY, int $width, int $height, raylib\Color $color1, raylib\Color $color2) |  |
| void DrawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2); | raylib\Draw::rectangleGradientV(int $posX, int $posY, int $width, int $height, raylib\Color $color1, raylib\Color $color2) |  |
| void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4); | raylib\Draw::rectangleGradientEx(raylib\Rectangle $rec, raylib\Color $col1, raylib\Color $col2, raylib\Color $col3, raylib\Color $col4) |  |
| void DrawRectangleLines(int posX, int posY, int width, int height, Color color); | raylib\Draw::rectangleLines(int $posX, int $posY, int $width, int $height, raylib\Color $color) |  |
| void DrawRectangleLinesEx(Rectangle rec, int lineThick, Color color); | raylib\Draw::rectangleLinesEx(raylib\Rectangle $rec, int $lineThick, raylib\Color color) |  |
| void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color); | raylib\Draw::rectangleRounded(raylib\Rectangle $rec, float $roundness, int $segments, raylib\Color color) |  |
| void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, int lineThick, Color color); | raylib\Draw::rectangleRoundedLines(raylib\Rectangle $rec, float $roundness, int $segments, int $lineThick, raylib\Color color) |  |
| void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color); | raylib\Draw::triangle(raylib\Vector2 $v1, raylib\Vector2 $v2, raylib\Vector2 $v3, raylib\Color $color) |  |
| void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color); | raylib\triangleLines(raylib\Vector2 v1, raylib\Vector2 v2, raylib\Vector2 v3, raylib\Color color) |  |
| void DrawTriangleFan(Vector2 *points, int pointsCount, Color color); | raylib\Draw::triangleFan(raylib\Vector2[] $points, raylib\Color $color) |  |
| void DrawTriangleStrip(Vector2 *points, int pointsCount, Color color); | raylib\Draw::triangleStrip(raylib\Vector2[] $points, raylib\Color $color) |  |
| void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color); | raylib\Draw::poly(raylib\Vector2 $center, int $sides, float $radius, float $rotation, raylib\Color $color) |  |
| void DrawPolyLines(Vector2 center, int sides, float radius, float rotation, Color color); | raylib\Draw::polyLines(raylib\Vector2 $center, int $sides, float $radius, float $rotation, raylib\Color $color) |  |


##Basic shapes collision detection functions

| C API | PHP API | Comment |
|-------|---------|---------|
| bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2); | raylib\Collision\checkRecs(raylib\Rectangle $rec1, raylib\Rectangle $rec2) |  |
| bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2); | raylib\Collision\checkCircles(raylib\Vector2 center1, float radius1, raylib\Vector2 center2, float radius2) |  |
| bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec); | raylib\Collision\checkCircleRec(raylib\Vector2 center, float radius, raylib\Rectangle rec) |  |
| bool CheckCollisionPointRec(Vector2 point, Rectangle rec); | raylib\Collision\checkPointRec(raylib\Vector2 point, raylib\Rectangle rec) |  |
| bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius); | raylib\Collision\checkPointCircle(raylib\Vector2 point, raylib\Vector2 center, float radius) |  |
| bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3); | raylib\Collision\checkPointTriangle(raylib\Vector2 point, raylib\Vector2 p1, raylib\Vector2 p2, Vector2 p3) |  |
| bool CheckCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2 *collisionPoint); | TODO |  |
| Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2); | raylib\Collision\getRec(raylib\Rectangle rec1, raylib\Rectangle rec2) : raylib\Rectangle |  |


##Image loading functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Image LoadImage(const char *fileName); | new raylib\Image(string $filename) |  |
| Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize); | raylib\Image::fromRaw(string $fileName, int $width, int $height, int $format, int $headerSize) |  |
| Image LoadImageAnim(const char *fileName, int *frames); | TODO |  |
| Image LoadImageFromMemory(const char *fileType, const unsigned char *fileData, int dataSize); | TODO |  |
| void UnloadImage(Image image); | -- | unset($image) |
| bool ExportImage(Image image, const char *fileName); | raylib\Image->export(string $fileName) |  |
| bool ExportImageAsCode(Image image, const char *fileName); | raylib\Image->exportAsCode(string $fileName) |  |


##Image generation functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Image GenImageColor(int width, int height, Color color); | TODO |  |
| Image GenImageGradientV(int width, int height, Color top, Color bottom); | TODO |  |
| Image GenImageGradientH(int width, int height, Color left, Color right); | TODO |  |
| Image GenImageGradientRadial(int width, int height, float density, Color inner, Color outer); | TODO |  |
| Image GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2); | TODO |  |
| Image GenImageWhiteNoise(int width, int height, float factor); | TODO |  |
| Image GenImagePerlinNoise(int width, int height, int offsetX, int offsetY, float scale); | TODO |  |
| Image GenImageCellular(int width, int height, int tileSize); | TODO |  |


##Image manipulation functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Image ImageCopy(Image image); | raylib\Image->copy() : raylib\Image |  |
| Image ImageFromImage(Image image, Rectangle rec); | raylib\Image->fromImage(raylib\Image $image, raylib\Rectangle $rec) : raylib\Image |  |
| Image ImageText(const char *text, int fontSize, Color color); | raylib\Image->fromDefaultFont(string $text ,int $fontSize, raylib\Color $color) : raylib\Image |  |
| Image ImageTextEx(Font font, const char *text, float fontSize, float spacing, Color tint); | raylib\Image->fromFont(raylib\Font $font, string $text ,int $fontSize, float $spacing, raylib\Color $color) : raylib\Image |  |
| void ImageFormat(Image *image, int newFormat); | raylib\Image->format(int $newFormat) |  |
| void ImageToPOT(Image *image, Color fill); | raylib\Image->toPot(raylib\Color $fillColor) |  |
| void ImageCrop(Image *image, Rectangle crop); | raylib\Image->crop(raylib\Rectangle $crop) |  |
| void ImageAlphaCrop(Image *image, float threshold); | raylib\Image->alphaCrop(float $threshold) |  |
| void ImageAlphaClear(Image *image, Color color, float threshold); | raylib\Imag->alphaClear(raylib\Color $color, float $threshold) |  |
| void ImageAlphaMask(Image *image, Image alphaMask); | raylib\Image->alphaMask(raylib\Image $alphaMask) |  |
| void ImageAlphaPremultiply(Image *image); | raylib\Image->alphaPremultiply() |  |
| void ImageResize(Image *image, int newWidth, int newHeight); | raylib\Image->resize(int $newWidth, int $newHeight) |  |
| void ImageResizeNN(Image *image, int newWidth,int newHeight); | raylib\Image->resizeNearestNeighbor(int $newWidth, int $newHeight) |  |
| void ImageResizeCanvas(Image *image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill); | raylib\Image->resizeCanvas(int $newWidth, int $newHeight, int $offsetX, int $offsetY, raylib\Color $color) |  |
| void ImageMipmaps(Image *image); | raylib\Image->genMipmaps() |  |
| void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp); | raylib\Image->dither(int $rBpp, int $gBpp, int $bBpp, int $aBpp) |  |
| void ImageFlipVertical(Image *image); | raylib\Image->flipVertical() |  |
| void ImageFlipHorizontal(Image *image); | raylib\Image->flipHorizontal() |  |
| void ImageRotateCW(Image *image); | raylib\Image->rotateClockwise() |  |
| void ImageRotateCCW(Image *image); | raylib\Image->rotateCounterClockwise() |  |
| void ImageColorTint(Image *image, Color color); | raylib\Image->colorTint(raylib\Color color) |  |
| void ImageColorInvert(Image *image); | raylib\Image->colorInvert() |  |
| void ImageColorGrayscale(Image *image); | raylib\Image->colorGrayscale() |  |
| void ImageColorContrast(Image *image, float contrast); | raylib\Image->colorContrast(float $contrast) |  |
| void ImageColorBrightness(Image *image, int brightness); | raylib\Image->colorBrightness(int 4brightness) |  |
| void ImageColorReplace(Image *image, Color color, Color replace); | raylib\Imag->colorReplace(raylib\Color $color, raylib\Color $replace) |  |
| Color *LoadImageColors(Image image); | raylib\Image->getData() : \raylib\Color |  |
| Color *LoadImagePalette(Image image, int maxPaletteSize, int *colorsCount); | raylib\Image->getData(int $maxPaletteSize, int[] $colorsCount) : \raylib\Color |  |
| void UnloadImageColors(Color *colors); | -- | use unset() |
| void UnloadImagePalette(Color *colors); | -- | use unset() |
| Rectangle GetImageAlphaBorder(Image image, float threshold); | raylib\Imag->getAlphaBorder(float $threshold) : ralib\Rectangle |  |


##Image drawing functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void ImageClearBackground(Image *dst, Color color); | TODO |  |
| void ImageDrawPixel(Image *dst, int posX, int posY, Color color); | TODO |  |
| void ImageDrawPixelV(Image *dst, Vector2 position, Color color); | TODO |  |
| void ImageDrawLine(Image *dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color); | TODO |  |
| void ImageDrawLineV(Image *dst, Vector2 start, Vector2 end, Color color); | TODO |  |
| void ImageDrawCircle(Image *dst, int centerX, int centerY, int radius, Color color); | TODO |  |
| void ImageDrawCircleV(Image *dst, Vector2 center, int radius, Color color); | TODO |  |
| void ImageDrawRectangle(Image *dst, int posX, int posY, int width, int height, Color color); | TODO |  |
| void ImageDrawRectangleV(Image *dst, Vector2 position, Vector2 size, Color color); | TODO |  |
| void ImageDrawRectangleRec(Image *dst, Rectangle rec, Color color); | TODO |  |
| void ImageDrawRectangleLines(Image *dst, Rectangle rec, int thick, Color color); | TODO |  |
| void ImageDraw(Image *dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint); | TODO |  |
| void ImageDrawText(Image *dst, const char *text, int posX, int posY, int fontSize, Color color); | TODO |  |
| void ImageDrawTextEx(Image *dst, Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); | TODO |  |


##Texture loading functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Texture2D LoadTexture(const char *fileName); | new raylib\Texture(string $fileName) |  |
| Texture2D LoadTextureFromImage(Image image); | raylib\Image->toTexture() : raylib\Texture |  |
| TextureCubemap LoadTextureCubemap(Image image, int layoutType); | TODO |  |
| RenderTexture2D LoadRenderTexture(int width, int height); | new raylib\RenderTexture(int $width, int $height) |  |
| void UnloadTexture(Texture2D texture); | -- | unset($texture) |
| void UnloadRenderTexture(RenderTexture2D target); | -- | unset($renderTexture) |
| void UpdateTexture(Texture2D texture, const void *pixels); | TODO |  |
| void UpdateTextureRec(Texture2D texture, Rectangle rec, const void *pixels); | TODO |  |
| Image GetTextureData(Texture2D texture); | TODO |  |
| Image GetScreenData(void); | TODO |  |


##Texture configuration functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void GenTextureMipmaps(Texture2D *texture); | raylib\Texture->genMipmaps() |  |
| void SetTextureFilter(Texture2D texture, int filterMode); | raylib\Texture->setFilter(int $filterMode) |  |
| void SetTextureWrap(Texture2D texture, int wrapMode); | raylib\Texture->setWrap(int $wrapMode) |  |


##Texture drawing functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void DrawTexture(Texture2D texture, int posX, int posY, Color tint); | raylib\Texture->draw(int $posX, int $posY, raylib\Color $tint) |  |
| void DrawTextureV(Texture2D texture, Vector2 position, Color tint); | raylib\Texture->drawV(raylib\Vector $position, raylib\Color $tint) |  |
| void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint); | raylib\Texture->drawEx(raylib\Vector $position, float $rotation, float scale, raylib\Color $tint) |  |
| void DrawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint); | raylib\Texture->drawRec(raylib\Rectangle $rec, raylib\Vector $position, raylib\Color $tint) |  |
| void DrawTextureQuad(Texture2D texture, Vector2 tiling, Vector2 offset, Rectangle quad, Color tint); | raylib\Texture->drawQuad(raylib\Vector $tiling, raylib\Vector $offset, raylib\Rectangle $quad, raylib\Color $tint) |  |
| void DrawTextureTiled(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, float scale, Color tint); | raylib\Texture->drawTiled(raylib\Rectangle $source, raylib\Rectangle $dest, raylib\Vector $origin, float $rotation, float $scale, raylib\Color $tint) |  |
| void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint); | raylib\Texture->drawPro(raylib\Rectangle $source, raylib\Rectangle $dest, raylib\Vector $origin, float $rotation, raylib\Color $tint) |  |
| void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint); | TODO |  |


##Color/pixel related functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Color Fade(Color color, float alpha); | raylib\Color->fade(float $alpha) |  |
| int ColorToInt(Color color); | raylib\Color->toInt() |  |
| Vector4 ColorNormalize(Color color); | raylib\Color->normalize() |  |
| Color ColorFromNormalized(Vector4 normalized); | raylib\Color::fromNormalized(/raylib/Vector4 $normalized) : /raylib/Color |  |
| Vector3 ColorToHSV(Color color); | raylib\Color->toHSV() : /raylib/Vector3 |  |
| Color ColorFromHSV(float hue, float saturation, float value); | raylib\Color::fromHSV(float $hue, float $saturation, float $value) : /raylib/Color |  |
| Color ColorAlpha(Color color, float alpha); | TODO |  |
| Color ColorAlphaBlend(Color dst, Color src, Color tint); | TODO |  |
| Color GetColor(int hexValue); | raylib\Color::fromInt(int $hexValue) : /raylib/Color |  |
| Color GetPixelColor(void *srcPtr, int format); | TODO |  |
| void SetPixelColor(void *dstPtr, Color color, int format); | TODO |  |
| int GetPixelDataSize(int width, int height, int format); | TODO |  |


##Font loading/unloading functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Font GetFontDefault(void); | raylib\Font::fromDefault() : /raylib/Font |  |
| Font LoadFont(const char *fileName); | new raylib\Font(string $fileName) |  |
| Font LoadFontEx(const char *fileName, int fontSize, int *fontChars, int charsCount); | raylib\Font::fromCustom(string $fileName,  int $fontSize, int $fontChars, int $charsCount) |  |
| Font LoadFontFromImage(Image image, Color key, int firstChar); | TODO |  |
| Font LoadFontFromMemory(const char *fileType, const unsigned char *fileData, int dataSize, int fontSize, int *fontChars, int charsCount); | TODO |  |
| CharInfo *LoadFontData(const unsigned char *fileData, int dataSize, int fontSize, int *fontChars, int charsCount, int type); | raylib\CharInfo::fromFontData(string $fileName, int fontSize, int[] $fontChars, int type) |  |
| Image GenImageFontAtlas(const CharInfo *chars, Rectangle **recs, int charsCount, int fontSize, int padding, int packMethod); | TODO |  |
| void UnloadFontData(CharInfo *chars, int charsCount); | -- | use unset() |
| void UnloadFont(Font font); | -- | use unset() |


##Text drawing functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void DrawFPS(int posX, int posY); | raylib\Text::drawFps(int $posX, int $posY) |  |
| void DrawText(const char *text, int posX, int posY, int fontSize, Color color); | raylib\Text::draw(string $text, int $posX, int $posY, int $fontSize, raylib\Color $color) |  |
| void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); | raylib\Text::drawTextEx(raylib\Font $font, string $text, raylib\Vector2 $position, float $fontSize, float $spacing, raylib\Color $tint) |  |
| void DrawTextRec(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint); | TODO |  |
| void DrawTextRecEx(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint); | TODO |  |
| void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint); | TODO |  |


##Text misc. functions

| C API | PHP API | Comment |
|-------|---------|---------|
| int MeasureText(const char *text, int fontSize); | raylib\Text::measure(string $text, float $fontSize) |  |
| Vector2 MeasureTextEx(Font font, const char *text, float fontSize, float spacing); | raylib\Font->measureText(string $text, float $fontSize, float $spacing) |  |
| int GetGlyphIndex(Font font, int codepoint); | TODO |  |


##Text strings management functions (no utf8 strings, only byte chars)

| C API | PHP API | Comment |
|-------|---------|---------|
| int TextCopy(char *dst, const char *src); | -- |  |
| bool TextIsEqual(const char *text1, const char *text2); | -- |  |
| unsigned int TextLength(const char *text); | -- |  |
| const char *TextFormat(const char *text, ...); | -- |  |
| const char *TextSubtext(const char *text, int position, int length); | -- |  |
| char *TextReplace(char *text, const char *replace, const char *by); | -- |  |
| char *TextInsert(const char *text, const char *insert, int position); | -- |  |
| const char *TextJoin(const char **textList, int count, const char *delimiter); | -- |  |
| const char **TextSplit(const char *text, char delimiter, int *count); | -- |  |
| void TextAppend(char *text, const char *append, int *position); | -- |  |
| int TextFindIndex(const char *text, const char *find); | -- |  |
| const char *TextToUpper(const char *text); | -- |  |
| const char *TextToLower(const char *text); | -- |  |
| const char *TextToPascal(const char *text); | -- |  |
| int TextToInteger(const char *text); | -- |  |
| char *TextToUtf8(int *codepoints, int length); | -- |  |


##UTF8 text strings management functions

| C API | PHP API | Comment |
|-------|---------|---------|
| int *GetCodepoints(const char *text, int *count); | TODO |  |
| int GetCodepointsCount(const char *text); | TODO |  |
| int GetNextCodepoint(const char *text, int *bytesProcessed); | TODO |  |
| const char *CodepointToUtf8(int codepoint, int *byteLength); | TODO |  |


##Basic geometric 3D shapes drawing functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void DrawLine3D(Vector3 startPos, Vector3 endPos, Color color); | TODO |  |
| void DrawPoint3D(Vector3 position, Color color); | TODO |  |
| void DrawCircle3D(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color); | TODO |  |
| void DrawTriangle3D(Vector3 v1, Vector3 v2, Vector3 v3, Color color); | TODO |  |
| void DrawTriangleStrip3D(Vector3 *points, int pointsCount, Color color); | TODO |  |
| void DrawCube(Vector3 position, float width, float height, float length, Color color); | TODO |  |
| void DrawCubeV(Vector3 position, Vector3 size, Color color); | TODO |  |
| void DrawCubeWires(Vector3 position, float width, float height, float length, Color color); | TODO |  |
| void DrawCubeWiresV(Vector3 position, Vector3 size, Color color); | TODO |  |
| void DrawCubeTexture(Texture2D texture, Vector3 position, float width, float height, float length, Color color); | TODO |  |
| void DrawSphere(Vector3 centerPos, float radius, Color color); | TODO |  |
| void DrawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color); | TODO |  |
| void DrawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color); | TODO |  |
| void DrawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color); | TODO |  |
| void DrawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color); | TODO |  |
| void DrawPlane(Vector3 centerPos, Vector2 size, Color color); | TODO |  |
| void DrawRay(Ray ray, Color color); | TODO |  |
| void DrawGrid(int slices, float spacing); | TODO |  |
| void DrawGizmo(Vector3 position); | TODO |  |


##Model loading/unloading functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Model LoadModel(const char *fileName); | TODO |  |
| Model LoadModelFromMesh(Mesh mesh); | TODO |  |
| void UnloadModel(Model model); | TODO |  |
| void UnloadModelKeepMeshes(Model model); | TODO |  |


##Mesh loading/unloading functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Mesh *LoadMeshes(const char *fileName, int *meshCount); | TODO |  |
| void UnloadMesh(Mesh mesh); | TODO |  |
| bool ExportMesh(Mesh mesh, const char *fileName); | TODO |  |


##Material loading/unloading functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Material *LoadMaterials(const char *fileName, int *materialCount); | TODO |  |
| Material LoadMaterialDefault(void); | TODO |  |
| void UnloadMaterial(Material material); | TODO |  |
| void SetMaterialTexture(Material *material, int mapType, Texture2D texture); | TODO |  |
| void SetModelMeshMaterial(Model *model, int meshId, int materialId); | TODO |  |


##Model animations loading/unloading functions

| C API | PHP API | Comment |
|-------|---------|---------|
| ModelAnimation *LoadModelAnimations(const char *fileName, int *animsCount); | TODO |  |
| void UpdateModelAnimation(Model model, ModelAnimation anim, int frame); | TODO |  |
| void UnloadModelAnimation(ModelAnimation anim); | TODO |  |
| bool IsModelAnimationValid(Model model, ModelAnimation anim); | TODO |  |


##Mesh generation functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Mesh GenMeshPoly(int sides, float radius); | TODO |  |
| Mesh GenMeshPlane(float width, float length, int resX, int resZ); | TODO |  |
| Mesh GenMeshCube(float width, float height, float length); | TODO |  |
| Mesh GenMeshSphere(float radius, int rings, int slices); | TODO |  |
| Mesh GenMeshHemiSphere(float radius, int rings, int slices); | TODO |  |
| Mesh GenMeshCylinder(float radius, float height, int slices); | TODO |  |
| Mesh GenMeshTorus(float radius, float size, int radSeg, int sides); | TODO |  |
| Mesh GenMeshKnot(float radius, float size, int radSeg, int sides); | TODO |  |
| Mesh GenMeshHeightmap(Image heightmap, Vector3 size); | TODO |  |
| Mesh GenMeshCubicmap(Image cubicmap, Vector3 cubeSize); | TODO |  |


##Mesh manipulation functions

| C API | PHP API | Comment |
|-------|---------|---------|
| BoundingBox MeshBoundingBox(Mesh mesh); | TODO |  |
| void MeshTangents(Mesh *mesh); | TODO |  |
| void MeshBinormals(Mesh *mesh); | TODO |  |
| void MeshNormalsSmooth(Mesh *mesh); | TODO |  |


##Model drawing functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void DrawModel(Model model, Vector3 position, float scale, Color tint); | TODO |  |
| void DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint); | TODO |  |
| void DrawModelWires(Model model, Vector3 position, float scale, Color tint); | TODO |  |
| void DrawModelWiresEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint); | TODO |  |
| void DrawBoundingBox(BoundingBox box, Color color); | TODO |  |
| void DrawBillboard(Camera camera, Texture2D texture, Vector3 center, float size, Color tint); | TODO |  |
| void DrawBillboardRec(Camera camera, Texture2D texture, Rectangle source, Vector3 center, float size, Color tint); | TODO |  |


##Collision detection functions

| C API | PHP API | Comment |
|-------|---------|---------|
| bool CheckCollisionSpheres(Vector3 center1, float radius1, Vector3 center2, float radius2); | TODO |  |
| bool CheckCollisionBoxes(BoundingBox box1, BoundingBox box2); | TODO |  |
| bool CheckCollisionBoxSphere(BoundingBox box, Vector3 center, float radius); | TODO |  |
| bool CheckCollisionRaySphere(Ray ray, Vector3 center, float radius); | TODO |  |
| bool CheckCollisionRaySphereEx(Ray ray, Vector3 center, float radius, Vector3 *collisionPoint); | TODO |  |
| bool CheckCollisionRayBox(Ray ray, BoundingBox box); | TODO |  |
| RayHitInfo GetCollisionRayMesh(Ray ray, Mesh mesh, Matrix transform); | TODO |  |
| RayHitInfo GetCollisionRayModel(Ray ray, Model model); | TODO |  |
| RayHitInfo GetCollisionRayTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3); | TODO |  |
| RayHitInfo GetCollisionRayGround(Ray ray, float groundHeight); | TODO |  |


##Shader loading/unloading functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Shader LoadShader(const char *vsFileName, const char *fsFileName); | TODO |  |
| Shader LoadShaderCode(const char *vsCode, const char *fsCode); | TODO |  |
| void UnloadShader(Shader shader); | TODO |  |
| Shader GetShaderDefault(void); | TODO |  |
| Texture2D GetTextureDefault(void); | TODO |  |
| Texture2D GetShapesTexture(void); | TODO |  |
| Rectangle GetShapesTextureRec(void); | TODO |  |
| void SetShapesTexture(Texture2D texture, Rectangle source); | TODO |  |


##Shader configuration functions

| C API | PHP API | Comment |
|-------|---------|---------|
| int GetShaderLocation(Shader shader, const char *uniformName); | TODO |  |
| int GetShaderLocationAttrib(Shader shader, const char *attribName); | TODO |  |
| void SetShaderValue(Shader shader, int uniformLoc, const void *value, int uniformType); | TODO |  |
| void SetShaderValueV(Shader shader, int uniformLoc, const void *value, int uniformType, int count); | TODO |  |
| void SetShaderValueMatrix(Shader shader, int uniformLoc, Matrix mat); | TODO |  |
| void SetShaderValueTexture(Shader shader, int uniformLoc, Texture2D texture); | TODO |  |
| void SetMatrixProjection(Matrix proj); | TODO |  |
| void SetMatrixModelview(Matrix view); | TODO |  |
| Matrix GetMatrixModelview(void); | TODO |  |
| Matrix GetMatrixProjection(void); | TODO |  |


##Texture maps generation (PBR)

| C API | PHP API | Comment |
|-------|---------|---------|
| TextureCubemap GenTextureCubemap(Shader shader, Texture2D panorama, int size, int format); | TODO |  |
| TextureCubemap GenTextureIrradiance(Shader shader, TextureCubemap cubemap, int size); | TODO |  |
| TextureCubemap GenTexturePrefilter(Shader shader, TextureCubemap cubemap, int size); | TODO |  |
| Texture2D GenTextureBRDF(Shader shader, int size); | TODO |  |


##Shading begin/end functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void BeginShaderMode(Shader shader); | TODO |  |
| void EndShaderMode(void); | TODO |  |
| void BeginBlendMode(int mode); | TODO |  |
| void EndBlendMode(void); | TODO |  |


##VR control functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void InitVrSimulator(void); | TODO |  |
| void CloseVrSimulator(void); | TODO |  |
| void UpdateVrTracking(Camera *camera); | TODO |  |
| void SetVrConfiguration(VrDeviceInfo info, Shader distortion); | TODO |  |
| bool IsVrSimulatorReady(void); | TODO |  |
| void ToggleVrMode(void); | TODO |  |
| void BeginVrDrawing(void); | TODO |  |
| void EndVrDrawing(void); | TODO |  |


##Audio device management functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void InitAudioDevice(void); | raylib\Audio::initDevice() |  |
| void CloseAudioDevice(void); | raylib\Audio::closeDevice() |  |
| bool IsAudioDeviceReady(void); | raylib\Audio::isDeviceReady() |  |
| void SetMasterVolume(float volume); | raylib\Audio::setMasterVolume(float $volume) |  |


##Wave/Sound loading/unloading functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Wave LoadWave(const char *fileName); | new raylib\Wave(string $fileName) |  |
| Wave LoadWaveFromMemory(const char *fileType, const unsigned char *fileData, int dataSize); | TODO |  |
| Sound LoadSound(const char *fileName); | TODO |  |
| Sound LoadSoundFromWave(Wave wave); | TODO |  |
| void UpdateSound(Sound sound, const void *data, int samplesCount);// Update sound buffer with new data | TODO |  |
| void UnloadWave(Wave wave); | -- | use unset() |
| void UnloadSound(Sound sound); | -- | use unset() |
| bool ExportWave(Wave wave, const char *fileName); | raylib\Wave->export(string $fileName) |  |
| bool ExportWaveAsCode(Wave wave, const char *fileName); | raylib\Wave->exportAsCode(string $fileName) |  |


##Wave/Sound management functions

| C API | PHP API | Comment |
|-------|---------|---------|
| void PlaySound(Sound sound); | TODO |  |
| void StopSound(Sound sound); | TODO |  |
| void PauseSound(Sound sound); | TODO |  |
| void ResumeSound(Sound sound); | TODO |  |
| void PlaySoundMulti(Sound sound); | TODO |  |
| void StopSoundMulti(void); | TODO |  |
| int GetSoundsPlaying(void); | TODO |  |
| bool IsSoundPlaying(Sound sound); | TODO |  |
| void SetSoundVolume(Sound sound, float volume); | TODO |  |
| void SetSoundPitch(Sound sound, float pitch); | TODO |  |
| void WaveFormat(Wave *wave, int sampleRate, int sampleSize, int channels); | raylib\Wave->format(int $sampleRate, int $sampleSize, int $channels) |  |
| Wave WaveCopy(Wave wave); | raylib\Wave->copy() : raylib\Wave |  |
| void WaveCrop(Wave *wave, int initSample, int finalSample); | raylib\Wave\crop(int $initSample, int $finalSample) |  |
| float *LoadWaveSamples(Wave wave); | TODO |  |
| void UnloadWaveSamples(float *samples); | -- | use unset() |


##Music management functions

| C API | PHP API | Comment |
|-------|---------|---------|
| Music LoadMusicStream(const char *fileName); | TODO |  |
| void UnloadMusicStream(Music music); | TODO |  |
| void PlayMusicStream(Music music); | TODO |  |
| void UpdateMusicStream(Music music); | TODO |  |
| void StopMusicStream(Music music); | TODO |  |
| void PauseMusicStream(Music music); | TODO |  |
| void ResumeMusicStream(Music music); | TODO |  |
| bool IsMusicPlaying(Music music); | TODO |  |
| void SetMusicVolume(Music music, float volume); | TODO |  |
| void SetMusicPitch(Music music, float pitch); | TODO |  |
| float GetMusicTimeLength(Music music); | TODO |  |
| float GetMusicTimePlayed(Music music); | TODO |  |


##AudioStream management functions

| C API | PHP API | Comment |
|-------|---------|---------|
| AudioStream InitAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels); | TODO |  |
| void UpdateAudioStream(AudioStream stream, const void *data, int samplesCount); | TODO |  |
| void CloseAudioStream(AudioStream stream); | TODO |  |
| bool IsAudioStreamProcessed(AudioStream stream); | TODO |  |
| void PlayAudioStream(AudioStream stream); | TODO |  |
| void PauseAudioStream(AudioStream stream); | TODO |  |
| void ResumeAudioStream(AudioStream stream); | TODO |  |
| bool IsAudioStreamPlaying(AudioStream stream); | TODO |  |
| void StopAudioStream(AudioStream stream); | TODO |  |
| void SetAudioStreamVolume(AudioStream stream, float volume); | TODO |  |
| void SetAudioStreamPitch(AudioStream stream, float pitch); | TODO |  |
| void SetAudioStreamBufferSizeDefault(int size); | TODO |  |

Total: 471
Wont Implement: 49
Todo: 219
Mapped: 203
Done: 48%