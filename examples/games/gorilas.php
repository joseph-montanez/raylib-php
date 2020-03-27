<?php
/*******************************************************************************************
 *
 *   raylib - sample game: gorilas
 *
 *   Sample game Marc Palau and Ramon Santamaria
 *
 *   This game has been created using raylib v1.3 (www.raylib.com)
 *   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
 *
 *   Copyright (c) 2015 Ramon Santamaria (@raysan5)
 *
 ********************************************************************************************/

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
use raylib\Collision;
use raylib\Color;
use raylib\Draw;
use raylib\Input\Key;
use raylib\Input\Mouse;
use raylib\Rectangle;
use raylib\Text;
use raylib\Timming;
use raylib\Vector2;
use raylib\Window;

const MAX_BUILDINGS = 15;
const MAX_EXPLOSIONS = 200;
const MAX_PLAYERS = 2;

const BUILDING_RELATIVE_ERROR = 30;        // Building size random range %
const BUILDING_MIN_RELATIVE_HEIGHT = 20;        // Minimum height in % of the screenHeight
const BUILDING_MAX_RELATIVE_HEIGHT = 60;        // Maximum height in % of the screenHeight
const BUILDING_MIN_GRAYSCALE_COLOR = 120;        // Minimum gray color for the buildings
const BUILDING_MAX_GRAYSCALE_COLOR = 200;        // Maximum gray color for the buildings

const MIN_PLAYER_POSITION = 5;        // Minimum x position %
const MAX_PLAYER_POSITION = 20;        // Maximum x position %

const GRAVITY = 9.81;
const DELTA_FPS = 60;

const RAD2DEG = 57.2958;
const DEG2RAD = 0.0174533;

$rayWhite = new Color(245, 245, 245, 255);
$lightGray = new Color(200, 200, 200, 255);
$darkGray = new Color(80, 80, 80, 255);
$maroon = new Color(190, 33, 55, 255);
$gray = new Color(130, 130, 130, 255);
$red = new Color(230, 41, 55, 255);
$blue = new Color(0, 121, 241, 255);
$white = new Color(255, 255, 255, 255);
$gold = new Color(255, 203, 0, 255);
$lime = new Color(0, 158, 47, 255);
$darkBlue = new Color(0, 82, 172, 255);
$black = new Color(0, 0, 0, 255);
$violet = new Color(135, 60, 190, 255);
$pink = new Color(255, 109, 194, 255);

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
class Player
{
    public Vector2 $position;

    public Vector2 $size;

    public Vector2 $aimingPoint;
    public int $aimingAngle;
    public int $aimingPower;

    public Vector2 $previousPoint;
    public int $previousAngle;
    public int $previousPower;

    public Vector2 $impactPoint;

    public bool $isLeftTeam;                // This player belongs to the left or to the right team
    public bool $isPlayer;                  // If is a player or an AI
    public bool $isAlive;

    public function __construct()
    {
        $this->position = new Vector2(0, 0);
        $this->size = new Vector2(0, 0);
        $this->aimingPoint = new Vector2(0, 0);
        $this->previousPoint = new Vector2(0, 0);
        $this->impactPoint = new Vector2(0, 0);
    }
}

class Building
{
    public Rectangle $rectangle;
    public Color $color;

    public function __construct()
    {
        $this->rectangle = new Rectangle(0, 0, 0, 0);
    }
}

class Explosion
{
    public Vector2 $position;
    public int $radius;
    public bool $active;

    public function __construct()
    {
        $this->position = new Vector2(0, 0);
    }
}

class Ball
{
    public Vector2 $position;
    public Vector2 $speed;
    public int $radius;
    public bool $active;

    public function __construct()
    {
        $this->position = new Vector2(0, 0);
        $this->speed = new Vector2(0, 0);
    }
}

;

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
$screenWidth = 800;
$screenHeight = 450;

$gameOver = false;
$pause = false;

/**
 * @var \Player[]
 */
$player = [];
/**
 * @var \Building[]
 */
$building = [];
/**
 * @var \Explosion[]
 */
$explosion = [];
$ball = new Ball();

$playerTurn = 0;
$ballOnAir = false;

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
/*
static void InitGame(void);         // Initialize game
static void UpdateGame(void);       // Update game (one frame)
static void DrawGame(void);         // Draw game (one frame)
static void UnloadGame(void);       // Unload game
static void UpdateDrawFrame(void);  // Update and Draw (one frame)

// Additional module functions
static void InitBuildings(void);
static void InitPlayers(void);
static bool UpdatePlayer(int playerTurn);
static bool UpdateBall(int playerTurn);
*/

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
// Initialization (Note windowTitle is unused on Android)
//---------------------------------------------------------
Window::init($screenWidth, $screenHeight, "sample game: gorilas");

InitGame();


Timming::setTargetFPS(60);
//--------------------------------------------------------------------------------------

// Main game loop
while (!Window::shouldClose())    // Detect window close button or ESC key
{
    // Update and Draw
    //----------------------------------------------------------------------------------
    UpdateDrawFrame();
    //----------------------------------------------------------------------------------
}

// De-Initialization
//--------------------------------------------------------------------------------------
UnloadGame();         // Unload loaded data (textures, sounds, models...)

Window::close();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
function InitGame()
{
    global $ball, $ballOnAir, $explosion;

    // Init shoot
    $ball->radius = 10;
    $ballOnAir = false;
    $ball->active = false;

    InitBuildings();
    InitPlayers();

    // Init explosions
    for ($i = 0; $i < MAX_EXPLOSIONS; $i++) {
        $explosion[$i] = new Explosion();

        $explosion[$i]->position = new Vector2(0.0, 0.0);
        $explosion[$i]->radius = 30;
        $explosion[$i]->active = false;
    }
}

// Update game (one frame)
function UpdateGame()
{
    global $gameOver, $pause, $ballOnAir, $playerTurn, $player, $ball;

    if (!$gameOver) {
        if (Key::isPressed(Key::P)) {
            $pause = !$pause;
        }

        if (!$pause) {
            if (!$ballOnAir) { // If we are aiming
                $ballOnAir = UpdatePlayer($playerTurn);
            } else {
                if (UpdateBall($playerTurn)) { // If collision
                    // Game over logic
                    $leftTeamAlive = false;
                    $rightTeamAlive = false;

                    for ($i = 0; $i < MAX_PLAYERS; $i++) {
                        if ($player[$i]->isAlive) {
                            if ($player[$i]->isLeftTeam) {
                                $leftTeamAlive = true;
                            }
                            if (!$player[$i]->isLeftTeam) {
                                $rightTeamAlive = true;
                            }
                        }
                    }

                    if ($leftTeamAlive && $rightTeamAlive) {
                        $ballOnAir = false;
                        $ball->active = false;

                        $playerTurn++;

                        if ($playerTurn == MAX_PLAYERS) {
                            $playerTurn = 0;
                        }
                    } else {
                        $gameOver = true;

                        // if (leftTeamAlive) left team wins
                        // if (rightTeamAlive) right team wins
                    }
                }
            }
        }
    } else {
        if (Key::isPressed(Key::ENTER)) {
            InitGame();
            $gameOver = false;
        }
    }

}

// Draw game (one frame)
function DrawGame()
{
    global $rayWhite, $gameOver, $building, $explosion, $blue, $maroon, $ball, $player, $ballOnAir, $playerTurn, $gray, $darkBlue, $screenWidth, $screenHeight, $pause;

    Draw::begin();

    Draw::clearBackground($rayWhite);

    if (!$gameOver) {
        // Draw buildings
        for ($i = 0; $i < MAX_BUILDINGS; $i++) {
            Draw::rectangleRec($building[$i]->rectangle, $building[$i]->color);
        }

        // Draw explosions
        for ($i = 0; $i < MAX_EXPLOSIONS; $i++) {
            if ($explosion[$i]->active) Draw::circle($explosion[$i]->position->getX(), $explosion[$i]->position->getY(), $explosion[$i]->radius, $rayWhite);
        }

        // Draw players
        for ($i = 0; $i < MAX_PLAYERS; $i++) {
            if ($player[$i]->isAlive) {
                if ($player[$i]->isLeftTeam) {
                    Draw::rectangle(
                        $player[$i]->position->getX() - $player[$i]->size->getX() / 2,
                        $player[$i]->position->getY() - $player[$i]->size->getY() / 2,
                        $player[$i]->size->getX(),
                        $player[$i]->size->getY(),
                        $blue
                    );
                } else {
                    Draw::rectangle(
                        $player[$i]->position->getX() - $player[$i]->size->getX() / 2,
                        $player[$i]->position->getY() - $player[$i]->size->getY() / 2,
                        $player[$i]->size->getX(),
                        $player[$i]->size->getY(),
                        $blue
                    );
                }
            }
        }

        // Draw ball
        if ($ball->active) {
            Draw::circle($ball->position->getX(), $ball->position->getY(), $ball->radius, $maroon);
        }

        // Draw the angle and the power of the aim, and the previous ones
        if (!$ballOnAir) {
            // Draw shot information
            /*
            if ($player[$playerTurn].isLeftTeam)
            {
                DrawText(TextFormat("Previous Point %i, %i", (int)$player[$playerTurn].previousPoint.x, (int)$player[$playerTurn].previousPoint.y), 20, 20, 20, DARKBLUE);
                DrawText(TextFormat("Previous Angle %i", $player[$playerTurn].previousAngle), 20, 50, 20, DARKBLUE);
                DrawText(TextFormat("Previous Power %i", $player[$playerTurn].previousPower), 20, 80, 20, DARKBLUE);
                DrawText(TextFormat("Aiming Point %i, %i", (int)$player[$playerTurn].aimingPoint.x, (int)$player[$playerTurn].aimingPoint.y), 20, 110, 20, DARKBLUE);
                DrawText(TextFormat("Aiming Angle %i", $player[$playerTurn].aimingAngle), 20, 140, 20, DARKBLUE);
                DrawText(TextFormat("Aiming Power %i", $player[$playerTurn].aimingPower), 20, 170, 20, DARKBLUE);
            }
            else
            {
                DrawText(TextFormat("Previous Point %i, %i", (int)$player[$playerTurn].previousPoint.x, (int)$player[$playerTurn].previousPoint.y), screenWidth*3/4, 20, 20, DARKBLUE);
                DrawText(TextFormat("Previous Angle %i", $player[$playerTurn].previousAngle), screenWidth*3/4, 50, 20, DARKBLUE);
                DrawText(TextFormat("Previous Power %i", $player[$playerTurn].previousPower), screenWidth*3/4, 80, 20, DARKBLUE);
                DrawText(TextFormat("Aiming Point %i, %i", (int)$player[$playerTurn].aimingPoint.x, (int)$player[$playerTurn].aimingPoint.y), screenWidth*3/4, 110, 20, DARKBLUE);
                DrawText(TextFormat("Aiming Angle %i", $player[$playerTurn].aimingAngle), screenWidth*3/4, 140, 20, DARKBLUE);
                DrawText(TextFormat("Aiming Power %i", $player[$playerTurn].aimingPower), screenWidth*3/4, 170, 20, DARKBLUE);
            }
            */

            // Draw aim
            if ($player[$playerTurn]->isLeftTeam) {
                // Previous aiming
                Draw::triangle(
                    new Vector2($player[$playerTurn]->position->getX() - $player[$playerTurn]->size->getX() / 4, $player[$playerTurn]->position->getY() - $player[$playerTurn]->size->getY() / 4),
                    new Vector2($player[$playerTurn]->position->getX() + $player[$playerTurn]->size->getX() / 4, $player[$playerTurn]->position->getY() + $player[$playerTurn]->size->getY() / 4),
                    $player[$playerTurn]->previousPoint,
                    $gray
                );

                // Actual aiming
                Draw::triangle(
                    new Vector2($player[$playerTurn]->position->getX() - $player[$playerTurn]->size->getX() / 4, $player[$playerTurn]->position->getY() - $player[$playerTurn]->size->getY() / 4),
                    new Vector2($player[$playerTurn]->position->getX() + $player[$playerTurn]->size->getX() / 4, $player[$playerTurn]->position->getY() + $player[$playerTurn]->size->getY() / 4),
                    $player[$playerTurn]->aimingPoint,
                    $darkBlue
                );
            } else {
                // Previous aiming
                Draw::triangle(new Vector2($player[$playerTurn]->position->getX() - $player[$playerTurn]->size->getX() / 4, $player[$playerTurn]->position->getY() + $player[$playerTurn]->size->getY() / 4),
                    new Vector2($player[$playerTurn]->position->getX() + $player[$playerTurn]->size->getX() / 4, $player[$playerTurn]->position->getY() - $player[$playerTurn]->size->getY() / 4),
                    $player[$playerTurn]->previousPoint, $gray);

                // Actual aiming
                Draw::triangle(new Vector2($player[$playerTurn]->position->getX() - $player[$playerTurn]->size->getX() / 4, $player[$playerTurn]->position->getY() + $player[$playerTurn]->size->getY() / 4),
                    new Vector2($player[$playerTurn]->position->getX() + $player[$playerTurn]->size->getX() / 4, $player[$playerTurn]->position->getY() - $player[$playerTurn]->size->getY() / 4),
                    $player[$playerTurn]->aimingPoint, $maroon);
            }
        }

        if ($pause) {
            Text::draw("GAME PAUSED", $screenWidth / 2 - Text::measure("GAME PAUSED", 40) / 2, $screenHeight / 2 - 40, 40, $gray);
        }
    } else {
        Text::draw("PRESS [ENTER] TO PLAY AGAIN", Window::getScreenWidth() / 2 - Text::measure("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, Window::getScreenHeight() / 2 - 50, 20, $gray);
    }

    Text::drawFps(0, 0);

    Draw::end();
}

// Unload game variables
function UnloadGame()
{
    // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
function UpdateDrawFrame()
{
    UpdateGame();
    DrawGame();
}

//--------------------------------------------------------------------------------------
// Additional module functions
//--------------------------------------------------------------------------------------
function InitBuildings()
{
    global $screenWidth, $screenHeight, $building;

    // Horizontal generation
    $currentWidth = 0;

    // We make sure the absolute error randomly generated for each building, has as a minimum value the screenWidth.
    // This way all the screen will be filled with buildings. Each building will have a different, random width.

    $relativeWidth = 100 / (100 - BUILDING_RELATIVE_ERROR);
    $buildingWidthMean = ($screenWidth * $relativeWidth / MAX_BUILDINGS) + 1;        // We add one to make sure we will cover the whole screen.

    // Vertical generation
    $grayLevel = null;

    // Creation
    for ($i = 0; $i < MAX_BUILDINGS; $i++) {
        $building[$i] = new Building();

        // Horizontal
        $building[$i]->rectangle->setX($currentWidth);
        $building[$i]->rectangle->setWidth(rand($buildingWidthMean * (100 - BUILDING_RELATIVE_ERROR / 2) / 100 + 1, $buildingWidthMean * (100 + BUILDING_RELATIVE_ERROR) / 100));

        $currentWidth += $building[$i]->rectangle->getWidth();

        // Vertical
        $currentHeighth = rand(BUILDING_MIN_RELATIVE_HEIGHT, BUILDING_MAX_RELATIVE_HEIGHT);
        $building[$i]->rectangle->setY($screenHeight - ($screenHeight * $currentHeighth / 100));
        $building[$i]->rectangle->setHeight($screenHeight * $currentHeighth / 100 + 1);

        // Color
        $grayLevel = rand(BUILDING_MIN_GRAYSCALE_COLOR, BUILDING_MAX_GRAYSCALE_COLOR);
        $building[$i]->color = new Color($grayLevel, $grayLevel, $grayLevel, 255);
    }
}

function InitPlayers()
{
    global $player, $screenWidth, $building;

    for ($i = 0; $i < MAX_PLAYERS; $i++) {
        $player[$i] = new Player();

        $player[$i]->isAlive = true;

        // Decide the team of this player
        if ($i % 2 == 0) {
            $player[$i]->isLeftTeam = true;
        } else {
            $player[$i]->isLeftTeam = false;
        }

        // Now there is no AI
        $player[$i]->isPlayer = true;

        // Set size, by default by now
        $player[$i]->size = new Vector2 (40, 40);

        // Set position
        if ($player[$i]->isLeftTeam) {
            $player[$i]->position->setX(rand($screenWidth * MIN_PLAYER_POSITION / 100, $screenWidth * MAX_PLAYER_POSITION / 100));
        } else {
            $player[$i]->position->setX($screenWidth - rand($screenWidth * MIN_PLAYER_POSITION / 100, $screenWidth * MAX_PLAYER_POSITION / 100));
        }

        for ($j = 0; $j < MAX_BUILDINGS; $j++) {
            if ($building[$j]->rectangle->getX() > $player[$i]->position->getX()) {
                // Set the player in the center of the building
                $player[$i]->position->setX($building[$j - 1]->rectangle->getX() + $building[$j - 1]->rectangle->getWidth() / 2);
                // Set the player at the top of the building
                $player[$i]->position->setY($building[$j - 1]->rectangle->getY() - $player[$i]->size->getY() / 2);

                break;
            }
        }

        // Set statistics to 0
        $player[$i]->aimingPoint = clone $player[$i]->position;
        $player[$i]->previousAngle = 0;
        $player[$i]->previousPower = 0;
        $player[$i]->previousPoint = clone $player[$i]->position;
        $player[$i]->aimingAngle = 0;
        $player[$i]->aimingPower = 0;

        $player[$i]->impactPoint = new Vector2(-100, -100);
    }
}

function UpdatePlayer(int $playerTurn): bool
{
    global $player, $ball;

    $mousePos = Mouse::getPosition();

    /**
     * The player who's turn it is
     * @var \Player $currentPlayer
     */
    $currentPlayer = $player[$playerTurn];

    /**
     * The position of the current player
     *
     * @var \raylib\Vector2 $position
     */
    $position = $currentPlayer->position;

    // If we are aiming at the firing quadrant, we calculate the angle
    if ($mousePos->getY() <= $position->getY()) {
        // Left team
        if ($currentPlayer->isLeftTeam && $mousePos->getX() >= $position->getX()) {
            // Distance (calculating the fire power)
            $currentPlayer->aimingPower = sqrt(pow($position->getX() - $mousePos->getX(), 2) + pow($position->getY() - $mousePos->getY(), 2));
            // Calculates the angle via arcsin
            $currentPlayer->aimingAngle = asin(($position->getY() - $mousePos->getY()) / $currentPlayer->aimingPower) * RAD2DEG;
            // Point of the screen we are aiming at
            $currentPlayer->aimingPoint = $mousePos;

            // Ball fired
            if (Mouse::isButtonPressed(Mouse::LEFT_BUTTON)) {
                $currentPlayer->previousPoint = $currentPlayer->aimingPoint;
                $currentPlayer->previousPower = $currentPlayer->aimingPower;
                $currentPlayer->previousAngle = $currentPlayer->aimingAngle;
                $ball->position = clone $position;

                return true;
            }
        } // Right team
        elseif (!$currentPlayer->isLeftTeam && $mousePos->getX() <= $position->getX()) {
            // Distance (calculating the fire power)
            $currentPlayer->aimingPower = (int) sqrt(pow($position->getX() - $mousePos->getX(), 2) + pow($position->getY() - $mousePos->getY(), 2));
            // Calculates the angle via arcsin
            $currentPlayer->aimingAngle = (int) (asin(($position->getY() - $mousePos->getY()) / $currentPlayer->aimingPower) * RAD2DEG);
            // Point of the screen we are aiming at
            $currentPlayer->aimingPoint = clone $mousePos;

            // Ball fired
            if (Mouse::isButtonPressed(Mouse::LEFT_BUTTON)) {
                $currentPlayer->previousPoint = $currentPlayer->aimingPoint;
                $currentPlayer->previousPower = $currentPlayer->aimingPower;
                $currentPlayer->previousAngle = $currentPlayer->aimingAngle;
                $ball->position = clone $position;

                return true;
            }
        } else {
            $currentPlayer->aimingPoint = clone $position;
            $currentPlayer->aimingPower = 0;
            $currentPlayer->aimingAngle = 0;
        }
    } else {
        $currentPlayer->aimingPoint = clone $position;
        $currentPlayer->aimingPower = 0;
        $currentPlayer->aimingAngle = 0;
    }

    return false;
}

function UpdateBall(int $playerTurn): bool
{
    global $ball, $player, $screenWidth, $explosion, $building;

    static $explosionNumber = 0;

    $currentPlayer = $player[$playerTurn];

    // Activate ball
    if (!$ball->active) {
        if ($currentPlayer->isLeftTeam) {
            $ball->speed->setX(cos($currentPlayer->previousAngle * DEG2RAD) * $currentPlayer->previousPower * 3 / DELTA_FPS);
            $ball->speed->setY(-1 * sin($currentPlayer->previousAngle * DEG2RAD) * $currentPlayer->previousPower * 3 / DELTA_FPS);
            $ball->active = true;
        } else {
            $ball->speed->setX(-1 * cos($currentPlayer->previousAngle * DEG2RAD) * $currentPlayer->previousPower * 3 / DELTA_FPS);
            $ball->speed->setY(-1 * sin($currentPlayer->previousAngle * DEG2RAD) * $currentPlayer->previousPower * 3 / DELTA_FPS);
            $ball->active = true;
        }
    }

    $ball->position->setX($ball->position->getX() + $ball->speed->getX());
    $ball->position->setY($ball->position->getY() + $ball->speed->getY());
    $ball->speed->setY($ball->speed->getY() + GRAVITY / DELTA_FPS);

    // Collision
    if ($ball->position->getX() + $ball->radius < 0) {
        echo "$playerTurn's ball fell out of screen - 0\n";
        return true;
    } elseif ($ball->position->getX() - $ball->radius > $screenWidth) {
        echo "$playerTurn's ball fell out of screen - $screenWidth\n";
        return true;
    } else {
        // Player collision
        for ($i = 0; $i < MAX_PLAYERS; $i++) {
            if (Collision::checkCircleRec(
                $ball->position,
                $ball->radius,
                new Rectangle(
                    $player[$i]->position->getX() - $player[$i]->size->getX() / 2,
                    $player[$i]->position->getY() - $player[$i]->size->getY() / 2,
                    $player[$i]->size->getX(),
                    $player[$i]->size->getY()
                )
            )) {
                // We can't hit ourselves
                if ($i == $playerTurn) {
                    return false;
                } else {
                    // We set the impact point
                    $currentPlayer->impactPoint->setX($ball->position->getX());
                    $currentPlayer->impactPoint->setY($ball->position->getY() + $ball->radius);

                    // We destroy the player
                    $player[$i]->isAlive = false;
                    return true;
                }
            }
        }

        // Building collision
        // NOTE: We only check building collision if we are not inside an explosion
        for ($i = 0; $i < MAX_BUILDINGS; $i++) {
            if (Collision::checkCircles($ball->position, $ball->radius, $explosion[$i]->position, $explosion[$i]->radius - $ball->radius)) {
                return false;
            }
        }

        for ($i = 0; $i < MAX_BUILDINGS; $i++) {
            if (Collision::checkCircleRec($ball->position, $ball->radius, $building[$i]->rectangle)) {
                // We set the impact point
                $currentPlayer->impactPoint->setX($ball->position->getX());
                $currentPlayer->impactPoint->setY($ball->position->getY() + $ball->radius);

                // We create an explosion
                $explosion[$explosionNumber]->position = clone $currentPlayer->impactPoint;
                $explosion[$explosionNumber]->active = true;

                $explosionNumber++;

                return true;
            }
        }
    }

    return false;
}
